/****************************************
*   Copyright (C) 2004 by Dynamol Inc.
*   john.furr@dynamol.com
*
*****************************************/
#include "charge.h"
#include "atomtyper.h"
#include "chain.h"
#include "protein.h"
#include "molchangeevent.h"
#include "xmodelview.h"
#include <sstream>
#include <fstream>
#include "addh.h"
#include "runmopac.h"
#include "trashcan.h"

#include "moldb.h"

#include "fragment.h"
#include "molecule.h"
#include "atom.h"

#include <qapplication.h>
#include <qfile.h>

//dynatype includes
#include "../dynatype/dtype.h"
#include "../dynatype/molecule.h"
#include "moladapter.h"

//Dynacomp Includes
#include "../dynacomp/molecule.h"
#include "../dynacomp/charge.h"
#include "../dynacomp/compute.h"

using namespace std;

#include <qmessagebox.h>

//This is the charge thread wrapper section
int chargeThread::rtti() {return 2;}
chargeThread::chargeThread(XmodelView *view, const char *name) 
: dynoThread(NULL) {
   QString qname = name;
   setName(qname);


//NEXT TWO ARE OLDER
   //Charge = new charge;
   //Charge->calledFromThread = true;


   this->view = view;

}
chargeThread::~chargeThread() {/*delete Charge;*/}
void chargeThread::setUp(molecule *mol, string type) 
{ 
   this->type = type;
   this->mol = mol;

   //This is the older stuff
   //Charge->setUp(mol, type); 
};

void chargeThread::run() 
{
   QString text = "Calculating ";
   text += type;
   text += " Charges";
   vector<QString> lables;  lables.push_back(text);
   molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1010));
   e->setDisplayText(lables);
   e->sendEvent();

   //Charge->run();
   
   dynacomp::molecule *dc = new dynacomp::molecule;
   molAdapter::mol2dynacomp(dc, mol);
   dynacomp::Compute::charges(dc, type);
   molAdapter::dynacomp2mol(mol, dc);
   delete dc;

   lables.clear();
   e->setDisplayText(lables);
   e->sendEvent();

   if (wait_sem != NULL) {
      delete wait_sem;
      molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1002), wait_sem);
      e->name = name;
      QApplication::postEvent(&view->jm, e);
   } else {
      molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1002));
      e->name = name;
      QApplication::postEvent(&view->jm, e);
   }
}

void chargeThread::setName(QString name) 
{ this->name = name; }

QString chargeThread::getName() 
{ return this->name; }


//This is were the real charge class begins
charge::charge()
{ calledFromThread = false; }


charge::~charge()
{}

void charge::setUp(molecule *mol, string type) {
   this->mol = mol;
   //cout <<"charge::setUp: " << type << endl;
   mol->updateValence();
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
   //   //cout <<atm->getNum()<<"\t"<<atm->getSym()<<"\t"<< atm->valence << endl;
   }
   if (type == "AM1") this->type = type;
   else if (type == "MNDO" || type == "MNDO3") this->type = "MNDO3";
   else if (type == "PM3") this->type = type;
   else if (type == "AM1-BCC") this->type = type;
   else if (type == "AMBER") this->type = type;
   else if (type == "Current") this->type = type;
   else {
      this->type = "BAD";
      return;
   }
}

bool charge::run() {
   if (type == "BAD") {
      return false;
   }
  
   bool success = false;
   if (type == "AM1" || type == "MNDO3" || type == "PM3") 
      success = mopacCharges(type);
   if (type == "AM1-BCC") 
      success = AM1_BCC_Charges();
   if (type == "AMBER") 
      success = amberChargesNew();
   if (type == "Current") 
      return true;

   return success;
}

bool charge::AM1_BCC_Charges() {
   
   dynacomp::molecule *dc = new dynacomp::molecule;
   molAdapter::mol2dynacomp(dc, mol);
   dynacomp::Compute::charges(dc, "AM1-BCC");
   molAdapter::dynacomp2mol(mol, dc);
   delete dc;
   return true;
}

/*
bool charge::AM1_BCC_Charges() {
   //////////cout <<"AM1_BCC_Charges()"<<endl;
   if( !mopacCharges("AM1") ) {
     //cout <<"Charges not calculated"<<endl;
     //QMessageBox::critical(0, "Dynamol", "mopac failed");
     return false;
   }

   am1_bcc.am1_bcc_Aromaticity(mol);
   am1_bcc.BCC_BondOrderString(mol);
   am1_bcc.BCC_AtomTypes(mol);
   
   if (!am1_bcc.BCC_getCorrections(mol) ) {
      //cout <<"corr failed"<<endl;
      QMessageBox::critical(0, "Dynamol", "corr failed");
      return false;
   }
   
   //This section assigns the atom equivalences 
   mol->chargeType = type;
   dt::molecule *dtmol = new dt::molecule();
   molAdapter::mol2molecule(dtmol, mol);
   dt::dType d;
   d.setGaffTypes(dtmol);
   molAdapter::update(mol, dtmol);
   delete dtmol;
   //molDB::writeSDFX("min.sdfx", mol, 0);
   //QString param = getenv("DYNAMOL");
   //param += "/bin/dynatype min.sdfx -p 10 -t PATHS_ONLY";
   //system(param.latin1());
   
   //////qDebug("Trying to average equivalent atom charges");
   ifstream inFile("equivs.txt", ios::in);
   if (inFile) {
      while (!inFile.eof() ) {
         string line;
         getline(inFile, line);
         stringstream sLine(line);
	 int num;
	 vector<int> equ; //equivelent atom numbers
	 while (sLine >> num) {
	    equ.push_back(num);
            ////////////cout <<"equ: " << num << endl;
	 }
         ////////////cout <<equ.size() << setw(12) << mol->atoms.size() << endl;
	 float avgCharge = 0;
	 for (int i=0; i<equ.size(); i++) {
	    atom *atm = mol->atoms[equ[i]-1];
            ////////////cout <<"atm->charge: " << atm->charge << endl;
            ////////////cout <<"atm->getNum(): " << atm->getNum() << setw(12)<<equ[i]-1<<endl;
	    avgCharge += atm->charge;
	 }
	 inFile.close();
	 avgCharge /= equ.size();
	 ////////////cout <<"HERE"<<endl;
	 for (int i=0; i<equ.size(); i++) {
	    atom *atm = mol->atoms[equ[i]-1];
	    atm->setCharge(avgCharge);
	 }
      }
   } else {
   }
  
   ////////////cout <<"Leaving charge stuff"<<endl;
   return true;
}
*/

bool charge::mopacCharges(string type) {
   dynacomp::molecule *dc = new dynacomp::molecule;
   molAdapter::mol2dynacomp(dc, mol);
   dynacomp::Compute::charges(dc, type);
   molAdapter::dynacomp2mol(mol, dc);
   delete dc;
   return true;
}

/*
bool charge::mopacCharges(string type) {
    QFile f("mol.dat");  f.remove();
	f.setName("mol.arc"); f.remove();
	f.setName("mol.mno"); f.remove();
	f.setName("mol.end"); f.remove();
	f.setName("FOR011"); f.remove();

   ofstream outFile("mol.dat", ios::out); //LINUX
       
   atomTyper typer;
   typer.setFormalCharges(mol); 
   int totalCharge = 0;
   for (int i=0; i<mol->atoms.size(); i++) {
      totalCharge += mol->atoms[i]->formalCharge;
   }	
      
   //Note eventually you will want to have CHARGE=n so that you can specify the total Charge on the molecule
   if (totalCharge == 0) outFile << type<<" GEO-OK MMOK EF  "<<endl;
   else  outFile << type<<" GEO-OK MMOK EF CHARGE="<<totalCharge<<endl;
   outFile << "MOPAC "<<type<<" job run from the Dynamol software chargeBegin"<<endl;
   outFile << endl;
      
   outFile.precision(5);

   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      float *cd = atm->fCoords;
      QString scd0; scd0.setNum(cd[0]).truncate(6);
      QString scd1; scd1.setNum(cd[1]).truncate(6);
      QString scd2; scd2.setNum(cd[2]).truncate(6);
      outFile << atm->getAtomicNum()
              << setw(10) << scd0 << setw(5) << 0  
              << setw(10) << scd1 << setw(5) << 0 
              << setw(10) << scd2 << setw(5) << 0 
              << endl;
   }
   outFile.close();
      
   
   //runMopac rm;
   //rm.start();
   //while (!rm.Done()) {}
   //LINUX 1
   system("mopac mol");
   
   //WINDOWS 1
   //system("mopac.exe mol.dat");

   //////////////cout <<"HERE"<< endl;
       
   ifstream inFile("mol.arc", ios::in); 
	   
   //if mol.arc not found then post event that MOPAC is not found
   if (!inFile) {
      molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1009));
      e->postEvent();
      return 0;
   }
 
   string tmp;
       
   int count = 0;
   while (inFile >> tmp) {
      if (tmp == "chargeBegin") count++;
	  if (count == 2) break;
   }

   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      int atmNum = 0;
      string sym;
      float charge = 0;
      float chargeDensity = 0;
      
      inFile >> sym; 
      for (int i=0; i<9; i++) inFile >> tmp;
         inFile >> charge;
		  
 	  //QString c; c.setNum(charge);
      //////qDebug(c);
      atm->setCharge(charge);
      //cout <<atm->getNum()<<"\t"<<atm->getSymbol()<<"\t"<<atm->charge<<endl;
   }
	   
   mol->chargeType = type;
   //////qDebug("Returning true fro mmopacCharges");
   
   //Now lets do all the clean up stuff
   //f.setName("mol.dat");  f.remove();
   //f.setName("mol.arc"); f.remove();
   //f.setName("mol.mno"); f.remove();
   //f.setName("mol.end"); f.remove();
   //f.setName("FOR011"); f.remove();
   return 1;
}
*/

void charge::avgEquivalentCharges(molecule *mol) {
   //dt::molecule *dtmol = new dt::molecule;
   dt::molPtr dtmol( new dt::molecule );
   molAdapter::mol2molecule(dtmol, mol);
   dt::dType d;
   vector< vector<int> > equivs;
   d.getEquivalents(dtmol, equivs, -1);
   for (int i=0; i<equivs.size(); i++) {
      float chgTotal = 0;
      for (int j=0; j<equivs[i].size(); j++) {
         chgTotal += mol->atoms[ equivs[i][j] ]->getCharge();
      }
      float chgAvg = chgTotal/equivs[i].size();

      for (int j=0; j<equivs[i].size(); j++) {
         mol->atoms[equivs[i][j]]->setCharge(chgAvg);
      }
   }
}

void charge::mopacMin(string type) {
      //First lets delete all the old mopac files
   QFile f("mol.dat"); f.remove();
   f.setName("mol.arc"); f.remove();
   f.setName("mol.mno"); f.remove();
   f.setName("mol.end"); f.remove();
   f.setName("FOR011"); f.remove();

   ofstream outFile("mol.dat", ios::out);

   //atomTyper typer;
   //typer.setFormalCharges(mol);     
   int totalCharge = 0;
   for (int i=0; i<mol->atoms.size(); i++) {
      totalCharge += mol->atoms[i]->formalCharge;
   }	

   ////cout <<"Formal Charge
    
      //Note eventually you will want to have CHARGE=n so that you can specify the total Charge on the molecule
       if (totalCharge == 0) outFile << type<<" GEO-OK MMOK EF  "<<endl;
       else  outFile << type<<" GEO-OK MMOK EF CHARGE="<<totalCharge<<endl;
       outFile << "MOPAC "<<type<<" job run from the Dynamol software chargeBegin"<<endl;
       outFile << endl;
      
       outFile.precision(5);
       
       vector<float> zeroCoords(3);
       float *cd = mol->atoms[0]->fCoords;
       for (int i=0; i<3; i++) zeroCoords[i] = cd[i];

       for (int i=0; i<mol->atoms.size(); i++) {
         atom *atm = mol->atoms[i];
         float *cd = atm->fCoords;
         QString scd0; scd0.setNum(cd[0]).truncate(6);
         QString scd1; scd1.setNum(cd[1]).truncate(6);
         QString scd2; scd2.setNum(cd[2]).truncate(6);
         outFile << atm->getAtomicNum()
                   << setw(10) << scd0 << setw(5) << 1  // Cd[0] && 0 for yes optimization of coord 
                   << setw(10) << scd1 << setw(5) << 1  // Cd[1] && 0 for yes optimization of coord
                   << setw(10) << scd2 << setw(5) << 1  // Cd[2] && 0 for yes optimization of coord 
                    << endl;
       }
      
      #ifdef LINUX
         system("mopac mol"); 
      #endif

      #ifdef WINDOWS
         system("mopac.exe mol.dat"); 
      #endif
       //Now lets read the charges back in
       outFile.close();

       ifstream inFile("mol.arc", ios::in);
       if (!inFile) {
          molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1009));
	  e->postEvent();
	  return;
       }

       string tmp;
       int count = 0;
       while (inFile >> tmp) {
          if (tmp == "chargeBegin") count++;
		  if (count == 2) break;
       }
	  
       QString error = "mopacMin tmp is ";
       error += tmp;
       for (int i=0; i<mol->atoms.size(); i++) {
          atom *atm = mol->atoms[i];
          int atmNum = 0;
          string sym;
          float charge = 0;
          float chargeDensity = 0;

          inFile >> sym; 
	  for (int i=0; i<9; i++) 
	     inFile >> tmp;
		 
	  inFile >> charge;
	  atm->setCharge(charge);
       }
       
      inFile.close();
      inFile.open("mol.mno", ios::in);
      if (!inFile) {
        return;
      }
      count = 0;
       while (inFile >> tmp) {
          if (tmp == "COORDINATES") count++;
		  if (count == 2) break;
       }

       getline(inFile, tmp);
       getline(inFile, tmp);
       getline(inFile, tmp);
       getline(inFile, tmp);
       
       float num, x, y, z;
       string sym;
       for (int i=0; i<mol->atoms.size(); i++) {
          inFile >> num >> sym >> x >> y >> z;
          atom *atm = mol->atoms[i];
          atm->setCoords(x, y, z);
       
       }
       
       //Now lets translate the whole molecule back to the zero coord
      for (int i=0; i<mol->atoms.size(); i++) {
         float *cd = mol->atoms[i]->fCoords;
         for (int j=0; j<3; j++) cd[j] += zeroCoords[j];
      }

	  inFile.close();
   f.setName("mol.dat"); f.remove();
   f.setName("mol.arc"); f.remove();
   f.setName("mol.mno"); f.remove();
   f.setName("mol.end"); f.remove();
   f.setName("FOR011"); f.remove();
}


bool charge::amberChargesNew() {
   vector<molecule *> frags;
   if(mol->rtti() == 14) {
      protein *prot = dynamic_cast<protein *>(mol);
      for (int i=0; i<prot->chains.size(); i++) {
         for (int j=0; j<prot->chains[i]->frags.size(); j++) {
            molecule *mol = prot->chains[i]->frags[j];
            ////cout <<"Pushing back frag: " << mol->getName() <<endl;
            frags.push_back(prot->chains[i]->frags[j]);
         }
      }
   }
   if (mol->rtti() == 13) {
      chain *ch = dynamic_cast<chain *>(mol);
      for (int i=0; i<ch->frags.size(); i++) {
         frags.push_back(ch->frags[i]);
      }
   }
   dynacomp::charge *CHARGE = new dynacomp::charge;
   vector<dynacomp::molecule *> dcFrags;
   for (int i=0; i<frags.size(); i++) {
      dynacomp::molecule *dc = new dynacomp::molecule;
      molAdapter::mol2dynacomp(dc, frags[i]);
      dcFrags.push_back(dc);
   }  
   CHARGE->chargeChain2(dcFrags);
   for (int i=0; i<frags.size(); i++) {
      molAdapter::dynacomp2mol(frags[i], dcFrags[i]);
      delete dcFrags[i];
   }
  return true;
}

//void charge::chargeChain2(chain *ch, vector<chargeStruct *> &data) {
void charge::chargeChain2(molecule *frag, vector<chargeStruct *> &data) {
   if (frag->getName() == "ALA") chargeAlanine2(frag, data);
   else  if (frag->getName() == "GLY") chargeGlycine2(frag, data);
   else if (frag->getName() == "SER") chargeSerine2(frag, data);
   else if (frag->getName() == "THR") chargeThreonine2(frag, data);
   else if (frag->getName() == "LEU") chargeLeucine2(frag, data);
   else if (frag->getName() == "ILE") chargeIsoleucine2(frag, data);
   else if (frag->getName() == "VAL") chargeValine2(frag, data);
   else if (frag->getName() == "ASN") chargeAsparagine2(frag, data);
   else if (frag->getName() == "GLN") chargeGlutamine2(frag, data);
   else if (frag->getName() == "ARG") chargeArginine2(frag, data);
   else if (frag->getName() == "HIS") chargeHistidine(frag, data);
   else if (frag->getName() == "TRP") chargeTryptophan2(frag, data);
   else if (frag->getName() == "PHE") chargePhenylalanine2(frag, data);
   else if (frag->getName() == "TYR") chargeTyrosine2(frag, data);
   else if (frag->getName() == "GLU") chargeGlutamate(frag, data);
   else if (frag->getName() == "ASP") chargeAspartate2(frag, data);
   else if (frag->getName() == "LYS") chargeLysine2(frag, data);
   else if (frag->getName() == "PRO") chargeProline2(frag, data);
   else if (frag->getName() == "CYS") chargeCysteine2(frag, data);
   else if (frag->getName() == "MET") chargeMethionine2(frag, data);
   else if (frag->getName() == "water") chargeWater2(frag, data);
   else {
      //cout <<"Non Standard Residue"<<endl;
      nonStandardResidue(frag);
   }
}


void charge::chargeAlanine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#ALANINE";
   else if (ter == 1) search = "#c-ALANINE";
   else if (ter == 2) search = "#n-ALANINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
   //This checks to make sure that he fragment has 
   // the correct number of atoms.
   //If not is prints out a warning message
   if (checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      int atNum = atm->getAtomicNum();
      if (atNum == 1 && atm->atoms[0]->getSym() == "N  ")
         atm->setSymbol("H  ");
      if (atNum == 1 && atm->atoms[0]->getSym() == "CA ")
         atm->setSymbol("HA ");
      if (atNum == 1 && atm->atoms[0]->getSym() == "CB ")
         atm->setSymbol("HB1");
   }

   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
         if (atm->getSym() == struc->atoms[j]) {
            atm->setCharge(struc->charge[j]);
	     atm->setFFType(struc->ff_type[j]);
	     break;	
         }
      }
   }
   } else {
     this->nonStandardResidue(frag);

   }
}

void charge::chargeGlycine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#GLYCINE";
   else if (ter == 1) search = "#c-GLYCINE";
   else if (ter == 2) search = "#n-GLYCINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if (checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   } 
   } else {
     this->nonStandardResidue(frag);
   
   }  
}

void charge::chargeSerine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#SERINE";
   else if (ter == 1) search = "#c-SERINE";
   else if (ter == 2) search = "#n-SERINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "OG ") atm->setSymbol("HG ");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeThreonine2(molecule *frag, vector<chargeStruct *> &data) {
   //////////////cout <<"charge::chargeThreonine2"<<endl;
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#THREONINE";
   else if (ter == 1) search = "#c-THREONINE";
   else if (ter == 2) search = "#n-THREONINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {

   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG2") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "OG1") atm->setSymbol("HG1");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
   //////////////cout <<"Leaving threaonine stuff"<<endl;
}

void charge::chargeLeucine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#LEUCINE";
   else if (ter == 1) search = "#c-LEUCINE";
   else if (ter == 2) search = "#n-LEUCINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }

   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {

   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG ") atm->setSymbol("HG ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD1") atm->setSymbol("HD1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD2") atm->setSymbol("HD2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeIsoleucine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#ISOLEUCINE";
   else if (ter == 1) search = "#c-ISOLEUCINE";
   else if (ter == 2) search = "#n-ISOLEUCINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG2") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG1") atm->setSymbol("HG1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD1") atm->setSymbol("HD1");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeValine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#VALINE";
   else if (ter == 1) search = "#c-VALINE";
   else if (ter == 2) search = "#n-VALINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG2") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG1") atm->setSymbol("HG1");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
}


void charge::chargeAsparagine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#ASPARAGINE";
   else if (ter == 1) search = "#c-ASPARAGINE";
   else if (ter == 2) search = "#n-ASPARAGINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }   
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") 
     	atm->setSymbol("H  ");
     else if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") 
     	atm->setSymbol("HA ");
     else if (atNum == 1 && atm->atoms[0]->getSym() == "CB ")
     	atm->setSymbol("HB2");
     else if (atNum == 1 && atm->atoms[0]->getSym() == "ND2")
     	atm->setSymbol("HD2"); 
   }

   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeGlutamine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#GLUTAMINE";
   else if (ter == 1) search = "#c-GLUTAMINE";
   else if (ter == 2) search = "#n-GLUTAMINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }   
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG ") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "NE2") atm->setSymbol("HE2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeArginine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#ARGININE";
   else if (ter == 1) search = "#c-ARGININE";
   else if (ter == 2) search = "#n-ARGININE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }   
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG ") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD ") atm->setSymbol("HD2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "NE ") atm->setSymbol("HE ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "NH1") atm->setSymbol("HH1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "NH2") atm->setSymbol("HH2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   } 
   } else {
     this->nonStandardResidue(frag);
   
   }  
}

void charge::chargeTryptophan2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#TRYPTOPHAN";
   else if (ter == 1) search = "#c-TRYPTOPHAN";
   else if (ter == 2) search = "#n-TRYPTOPHAN";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }   
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD1") atm->setSymbol("HD1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "NE1") atm->setSymbol("HE1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CZ2") atm->setSymbol("HZ2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CH2") atm->setSymbol("HH2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CZ3") atm->setSymbol("HZ3");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CE3") atm->setSymbol("HE3");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   } 
   } else {
     this->nonStandardResidue(frag);
   
   }  
}

void charge::chargePhenylalanine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#PHENYLALANINE";
   else if (ter == 1) search = "#c-PHENYLALANINE";
   else if (ter == 2) search = "#n-PHENYLALANINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
   //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   //cout <<"Before chechFragment"<<endl;
   if ( checkFragment(frag, struc) ) {
      //cout <<"Check frag was true"<<endl;
      //first thing that we need to do is change the H atom types;
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         int atNum = atm->getAN();
	 //cout <<"Atomic Number was: " << atNum << endl;
         //cout <<"Number of bonded atoms: " << atm->atoms.size() << endl;
         //cout <<"Symbol: " << atm->atoms[0]->getSymbol() << endl;
         //cout <<"Symbol: " << atm->atoms[0]->getSym() << endl;
         if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") {
		//cout <<"Before atom->setSymbol()"<<endl;
		atm->setSymbol("H  ");
                //cout <<"After atm->setSymbol()"<<endl;
         }
         if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
         if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
         if (atNum == 1 && atm->atoms[0]->getSym() == "CD1") atm->setSymbol("HD1");
         if (atNum == 1 && atm->atoms[0]->getSym() == "CE1") atm->setSymbol("HE1");
         if (atNum == 1 && atm->atoms[0]->getSym() == "CZ ") atm->setSymbol("HZ ");
         if (atNum == 1 && atm->atoms[0]->getSym() == "CE2") atm->setSymbol("HE2");
         if (atNum == 1 && atm->atoms[0]->getSym() == "CD2") atm->setSymbol("HD2");
         //cout <<"HERE: " << i << "\t" << frag->atoms.size() << endl;
      }
      //cout <<"YOu set all the symbols"<<endl;
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         for (int j=0; j<struc->atoms.size(); j++) {
            if (atm->getSym() == struc->atoms[j]) {
	       atm->setCharge(struc->charge[j]);
	       atm->setFFType(struc->ff_type[j]);	
	    }
         }
      }  
      //cout <<"And no you are here as well"<<endl;
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeTyrosine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#TYROSINE";
   else if (ter == 1) search = "#c-TYROSINE";
   else if (ter == 2) search = "#n-TYROSINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD1") atm->setSymbol("HD1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CE1") atm->setSymbol("HE1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "OH ") atm->setSymbol("HH ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CE2") atm->setSymbol("HE2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD2") atm->setSymbol("HD2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeGlutamate(molecule *frag, vector<chargeStruct *> &data) {
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     if (atm->getAtomicNum() == 1 && atm->atoms[0]->getAtomicNum() == 8) {
         chargeGlutamate_neut(frag, data); 
	 return;
     } else {
         chargeGlutamate_pos(frag, data);
	 return;
     }
   }
}

void charge::chargeGlutamate_pos(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#GLUTAMIC ACID";
   else if (ter == 1) search = "#c-GLUTAMIC ACID";
   else if (ter == 2) search = "#n-GLUTAMIC ACID";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG ") atm->setSymbol("HG2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   } 
   } else {
     this->nonStandardResidue(frag);
   
   } 
}
void charge::chargeGlutamate_neut(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#GLUTAMIC ACID";
   else if (ter == 1) search = "#c-GLUTAMIC ACID";
   else if (ter == 2) search = "#n-GLUTAMIC ACID";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
   
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG ") atm->setSymbol("HG2");
     //if (atNum == 1 && atm->atoms[0]->getSym() == "OE2") atm->setSymbol("HO ");
     //You think this will work better if some adds an H by hand
     if (atNum == 1 && atm->atoms[0]->getAtomicNum() == 8) atm->setSymbol("HO ");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeAspartate2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#ASPARTIC ACID";
   else if (ter == 1) search = "#c-ASPARTIC ACID";
   else if (ter == 2) search = "#n-ASPARTIC ACID";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   }  
}


void charge::chargeLysine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#LYSINE";
   else if (ter == 1) search = "#c-LYSINE";
   else if (ter == 2) search = "#n-LYSINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG ") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD ") atm->setSymbol("HD2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CE ") atm->setSymbol("HE2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "NZ ") atm->setSymbol("HZ1");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }
   } else {
     this->nonStandardResidue(frag);
   }
}

void charge::chargeProline2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#PROLINE";
   else if (ter == 1) search = "#c-PROLINE";
   else if (ter == 2) search = "#n-PROLINE";
   chargeStruct *struc = NULL;

   for (int i=0; i<data.size(); i++) {
      if (data[i]->name.contains(search)) {
         struc = data[i];
         break;
      }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      int atNum = atm->getAtomicNum();
      if (atNum == 1 && atm->atoms[0]->getSym() == "N  ")
         atm->setSymbol("H  ");
      if (atNum == 1 && atm->atoms[0]->getSym() == "CD ")
         atm->setSymbol("HD2");
      if (atNum == 1 && atm->atoms[0]->getSym() == "CG ")
         atm->setSymbol("HG2");
      if (atNum == 1 && atm->atoms[0]->getSym() == "CB ")
         atm->setSymbol("HB2");
      if (atNum == 1 && atm->atoms[0]->getSym() == "CA ")
         atm->setSymbol("HA ");
   }

   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
         if (atm->getSym() == struc->atoms[j]) {
            atm->setCharge(struc->charge[j]);
	     atm->setFFType(struc->ff_type[j]);
	     break;	
         }
      }
   } 
   } else {
     this->nonStandardResidue(frag);
   }
}

//void charge::chargeCysteine(molecule *frag, vector<string> &data){
void charge::chargeCysteine2(molecule *frag, vector<chargeStruct *> &data) {
  //We need to check for CS-SC disulfide bridge
  chain *ch = NULL;
  for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     if (atm->getAtomicNum() == 16) {
       if(frag->getParent() != NULL)
         ch = dynamic_cast<chain *>(frag->getParent()); 
       if (ch != NULL) {
         for (int i=0; i<ch->atoms.size(); i++) {
           atom *chAtm = ch->atoms[i];
	   if (chAtm == atm) {
	      //////////////cout <<"You did make it here"<<endl;
	      if (chAtm->atoms.size() == 1) {
	         chargeCysteine2_negative(frag, data);
		 return;
	      }
	      for (int j=0; j<chAtm->atoms.size(); j++) {
	        if (chAtm->atoms[j]->getAtomicNum() == 16) {
		  chAtm->setSelected(true);
		  chAtm->atoms[j]->setSelected(true);
		  //////////////cout <<"Calling the disulfide"<<endl;
		  chargeCysteine2_disulfide(frag, data);
		  return;
		}
	      }
	      
	   }
        }
       }
     }
  }
  chargeCysteine_normal(frag, data);
  
}

void charge::chargeCysteine_normal(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#CYSTEINE";
   else if (ter == 1) search = "#c-CYSTEINE";
   else if (ter == 2) search = "#n-CYSTEINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
   
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "SG ") atm->setSymbol("HG ");
   }
   
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeCysteine2_disulfide(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#CYSTINE(S-S BRIDGE)";
   else if (ter == 1) search = "#c-CYSTINE(S-S BRIDGE)";
   else if (ter == 2) search = "#n-CYSTINE(S-S BRIDGE)";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
   
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeCysteine2_negative(molecule *frag, vector<chargeStruct *> &data) {
   chargeStruct *struc = NULL;
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name == "#CYSTEINE with negative charge") {
       struc = data[i];
       break;
     }
   }
   
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc)) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

void charge::chargeMethionine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#METHIONINE";
   else if (ter == 1) search = "#c-METHIONINE";
   else if (ter == 2) search = "#n-METHIONINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
      
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CG ") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CE ") atm->setSymbol("HE1");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   }
   } else {
     this->nonStandardResidue(frag);
   
   } 
   
   //Check for NH2 ending group...I believe this is specific to the AMBER_03
   
   //vector<int> index;
   //for (int i=0; i<frag->atoms[0]->atoms.size(); i++) {
   //   atom *atm = frag->atoms[0]->atoms[i];
   //   if (atm->getAtomicNum() == 1)  index.push_back(i);
   //}
   //if (index.size() == 2) {
   //   frag->atoms[0]->setCharge(-0.46300);
   //   frag->atoms[ index[0] ]->setCharge(0.23150);
   //   frag->atoms[ index[1] ]->setCharge(0.23150);
   //}	  
   
}

void charge::chargeHistidine(molecule *frag, vector<chargeStruct *> &data) {
   int a = 0;
   int b = 0;
   //////////////cout <<"chargeHistidine"<<endl;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     if (atm->getAtomicNum() == 1 && atm->atoms[0]->getSym() == "ND1") a++;
     if (atm->getAtomicNum() == 1 && atm->atoms[0]->getSym() == "NE2") b++;
   }
   
   if (a == 1 && b == 1) chargeHistidine_Plus2(frag, data);
   if (a == 0 && b == 1) chargeHistidine_Epsilon2(frag, data);
   if (a == 1 && b == 0) chargeHistidine_Delta2(frag, data);
     
}
void charge::chargeHistidine_Plus2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#HISTIDINE PLUS";
   else if (ter == 1) search = "#c-HISTIDINE PLUS";
   else if (ter == 2) search = "#n-HISTIDINE PLUS";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
   //////////////cout <<"chargeHistidine_Plus2: "<< search << endl;
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   //////////////cout <<"Checked Fragment"<<endl;
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "ND1") atm->setSymbol("HD1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CE1") atm->setSymbol("HE1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "NE2") atm->setSymbol("HE2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD2") atm->setSymbol("HD2");
   }
   
   //////////////cout <<"Changed Types " << endl;
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType( struc->ff_type[j] );
	   break;	
	}
      }
   }  
   } else {
     this->nonStandardResidue(frag);
   } 
}

void charge::chargeHistidine_Epsilon2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#HISTIDINE EPSILONH";
   else if (ter == 1) search = "#c-HISTIDINE EPSILONH";
   else if (ter == 2) search = "#n-HISTIDINE EPSILONH";
   chargeStruct *struc = NULL;
    
    for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   }
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CE1") atm->setSymbol("HE1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "NE2") atm->setSymbol("HE2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD2") atm->setSymbol("HD2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType( struc->ff_type[j] );
	   break;	
	}
      }
   } 
   } else {
     this->nonStandardResidue(frag);
   }
}

void charge::chargeHistidine_Delta2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   QString search;
   if (ter == 0 ) search = "#HISTIDINE DELTAH";
   else if (ter == 1) search = "#c-HISTIDINE DELTAH";
   else if (ter == 2) search = "#n-HISTIDINE DELTAH";
   chargeStruct *struc = NULL;
    
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name.contains(search)) {
       struc = data[i];
       break;
     }
   } 
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
  // ////////////cout <<"chargeHistidine_Delta2"<<endl;
   if (checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSym() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSym() == "ND1") atm->setSymbol("HD1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CE1") atm->setSymbol("HE1");
     if (atNum == 1 && atm->atoms[0]->getSym() == "CD2") atm->setSymbol("HD2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   } 
   } else {
     this->nonStandardResidue(frag);
   
   } 
}



void charge::chargeWater2(molecule *frag, vector<chargeStruct *> &data) {
   chargeStruct *struc = NULL;
   for (int i=0; i<data.size(); i++) {
     if (data[i]->name == "#WATER, TIP3P MODEL") {
       struc = data[i];
       break;
     }
   }
   
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
   if ( checkFragment(frag, struc) ) {
   

   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     
     if (atm->getAtomicNum() == 8) atm->setSymbol("O  ");
     else if (atm->getAtomicNum() == 1) atm->setSymbol("H1 ");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSym() == struc->atoms[j]) {
	   atm->setCharge(struc->charge[j]);
	   atm->setFFType(struc->ff_type[j]);
	   break;	
	}
      }
   } 
   } else {
     this->nonStandardResidue(frag);
   
   } 
}

bool charge::checkFragment(molecule *frag, chargeStruct *struc) {
   //First lets check for lone H atoms..they wil be deleteg...
   for (int i=0; i<frag->atoms.size(); i++) {   
      atom *atm = frag->atoms[i];
      if (atm->atoms.size() == 0 && atm->getAtomicNum() == 1) {
         TrashCan t(atm); 
         t.empty();
      }
   }

   if (frag->atoms.size() != struc->atoms.size()) {
     bool isTerminal = false;
     for (int i=0; i<frag->atoms.size(); i++) {
        if (frag->atoms[i]->getSym() == "OXT") {
	   isTerminal = true;
	}
     }

     //Now check for mis-labled aspragine
     //***NOTE TO SELF  You are not sure about this block
      if (frag->getName() == "ASN" && 
          struc->atoms.size() - frag->atoms.size()) 
      {

      }

      //THis will return false...forcing the residue to be typed with gaff
      if (!isTerminal) {
         molecule *ch = dynamic_cast<molecule *>(frag->getParent());
         return false;
      }
   }
   //cout <<"Leaving checkFragment"<<endl;
   return true;
}

int charge::isTerminalFrag(molecule *frag) {
    //check for n-terminal
    int hCount = 0;
    for (int i=0; i<frag->atoms[0]->atoms.size(); i++) {
       atom *atm = frag->atoms[0]->atoms[i];
       if (atm->getAtomicNum() == 1) hCount++;
    }
    if (hCount >= 2) {
    	////cout <<"Fragment was n-Terminal: " << frag->getName() << endl;
	return 2;
    }
    if (hCount >= 1 && frag->getName() == "PRO") {
        //out <<"Fragment was n-Terminal: " << frag->getName() << endl;
	return 2;
    }
    
    //Now check for c-terminal
    for (int i=0; i<frag->atoms.size(); i++) {
       atom *atm = frag->atoms[i];
       if (atm->getSym() == "OXT") {
          return 1;
       }
    }
    //Wasn't a terminal atom
    return 0;
}

void charge::nonStandardResidue(molecule *frag) {
   //This first line checks for metals...but allows waters.
  ////////////cout <<"\ncharge::nonStandardResidue"<<endl; 
  ////////////cout <<"NOt using this function right now."<<endl;
  for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     if (atm->getFFType() == "N") atm->setCharge(-0.447);
     else if (atm->getFFType() == "CT") atm->setCharge(-0.053);
     else if (atm->getFFType() == "C") atm->setCharge(0.65);
     else if (atm->getFFType() == "O") atm->setCharge(-0.5512);
     else if (atm->getFFType() == "H") atm->setCharge(0.279);
     else if (atm->getFFType() == "HO") atm->setCharge(0.414);
     else if (atm->getFFType() == "HC") atm->setCharge(0.040);
     else if (atm->getFFType() == "H1") atm->setCharge(0.094);
     else if (atm->getFFType() == "H2") atm->setCharge(0.124);
     else {
       //cout <<"No charge for atomType: " << atm->getFFType() << setw(12) << atm->getFFType().size() << endl;
     }
  }
  //cout <<"Leaving nonStandard"<<endl;
  return;

  if (frag->atoms.size() == 1 && frag->atoms[0]->getAtomicNum() != 8) {
      return;
   }
   molecule *parent = dynamic_cast<molecule *>(frag->getParent());

   //First we must make sure that the fragment has the correct number of hydrogens
   addH hAdd;
   vector<atom *> newAtoms;
   int atomsBefore = frag->atoms.size();
  
   hAdd.addHydrogens(frag, newAtoms);
   int atomsAfter = frag->atoms.size();

   charge c;
   c.setUp(frag, "AM1-BCC");
   c.run();
   int NEW = atomsAfter-atomsBefore;
   for (int i=0; i<NEW; i++) {
      //delete frag->atoms[ frag->atoms.size()-1 ];   
      TrashCan t(frag->atoms[frag->atoms.size()-1]);
      t.empty();
   }
   //////////cout <<"Probably will not see this"<<endl;
   if (frag->atoms[0]->getAtomicNum() == 7) {
      frag->atoms[0]->setFFType("N");
   }
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      //////////////cout <<atm->ff_type << setw(12);
      if (atm->getFFType() == "c") atm->setFFType("C");
      if (atm->getFFType() == "c3") atm->setFFType("CT");
      if (atm->getFFType() == "ca") atm->setFFType( "CA");
      if (atm->getFFType() == "c1") atm->setFFType("CZ");
      if (atm->getFFType() == "c2") atm->setFFType("C");

      if (atm->getFFType() == "o") atm->setFFType("O");
      if (atm->getFFType() == "oh") atm->setFFType("OH");
      if (atm->getFFType() == "os") atm->setFFType("OS");
      if (atm->getFFType() == "ow") atm->setFFType("OW");

      if (atm->getFFType() == "p5") atm->setFFType("P");
      if (atm->getFFType() == "ss") atm->setFFType("S");
      if (atm->getFFType() == "f") atm->setFFType("F");
      if (atm->getFFType() == "cl") atm->setFFType("Cl");
      if (atm->getFFType() == "br") atm->setFFType("Br");
      if (atm->getFFType() == "i" ) atm->setFFType("I");

      if (atm->getFFType() == "n") atm->setFFType("N");
      if (atm->getFFType() == "n3") atm->setFFType("NT");
      if (atm->getFFType() == "nh") atm->setFFType("NT");
      if (atm->getFFType() == "n4") atm->setFFType("N3");

      if (atm->getFFType() == "hn") atm->setFFType("H");
      else if (atm->getFFType() == "h1") atm->setFFType("H1");
      else if (atm->getFFType() == "h2") atm->setFFType("H2");
      else if (atm->getFFType() == "h3") atm->setFFType("H3");
      else if (atm->getFFType() == "hc") atm->setFFType("HC");
      else if (atm->getFFType() == "hx") atm->setFFType("HC");
      else if (atm->getFFType() == "h4") atm->setFFType("H4");
      else if (atm->getFFType() == "h5") atm->setFFType("H5");
      else if (atm->getFFType() == "hw") atm->setFFType("HW");
      else if (atm->getFFType() == "ho") atm->setFFType("HO");
      else if (atm->getFFType() == "hs") atm->setFFType("HS");
      else if (atm->getFFType() == "hp") atm->setFFType("HP");
      else if (atm->getFFType() == "ha") atm->setFFType("HA");
   }
}





































