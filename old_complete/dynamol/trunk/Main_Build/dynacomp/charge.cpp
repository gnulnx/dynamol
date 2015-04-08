/********************************************
 *   Copyright (C) 2004 by Dynamol          *
 *   jjohn.furr@dynamol.com                 *
 ********************************************/
#include "charge.h"

//Dynacomp Includes
#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "am1_bcc.h"
#include "atomtyper.h"

//Dynabase Includes
#include "../dynabase/utility.h"

//Dynatype Includes
#include "../dynatype/dtype.h"
#include "../dynatype/molecule.h"

//Dynamol Convert Library
#include "../convert/convert.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
using std::ifstream;
using std::ofstream;
using std::endl;
using std::setw;
using std::ios;
using std::stringstream;
namespace dynacomp {

charge::charge()
{
   errorMsg = "";
}


charge::~charge()
{
}

string charge::getErrorMsg() 
{ return errorMsg; };

void charge::setUp(molecule *mol, string type) {
   this->mol = mol;
   errorMsg = "";
   mol->updateValence();
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


bool charge::run(molecule *mol, string type) {
   this->mol = mol;
   if (type == "BAD") {
      return false;
   }
   
   bool success;
   if (type == "AM1" || type == "MNDO3" || type == "PM3") {
      success = mopacCharges(type, false);
      avgEquivalentCharges(mol);
   } else if (type == "AM1-BCC") {
      success = AM1_BCC_Charges(true); //optimize = true
      avgEquivalentCharges(mol);
   } else if (type == "AM1-BCC-fast") {
      success = AM1_BCC_Charges(false); //optimize = false
      avgEquivalentCharges(mol);
   } else if (type == "AMBER") {
      success = amberChargesNew();
   }
   else if (type == "Current")
      return true;

   return success;
   //avgEquivalentCharges(mol);
}

void charge::avgEquivalentCharges(molecule *mol) {
   dt::molPtr dtmol( new dt::molecule );
   dt::convert::toDynatype(dtmol, mol);
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

/*
bool charge::run() {
   if (type == "BAD") {
      return false;
   }

   if (type == "AM1" || type == "MNDO3" || type == "PM3") 
      return mopacCharges(type, false);
   if (type == "AM1-BCC") 
      return AM1_BCC_Charges(false);
   if (type == "AMBER") 
      return amberChargesNew();
   if (type == "Current") 
      return true;
}
*/
bool charge::mopacCharges(string type, bool optimize) {  
   #ifdef LINUX
      system("rm -f mol.out mol.dat mol.arc mol.mno mol.end FOR011");
   #endif

   #ifdef WINDOWS
      system("del mol.out mol.dat mol.arc mol.mno mol.end FOR011");
   #endif

   ofstream outFile("mol.dat", ios::out); //LINUX
   if (!outFile) 
      return false;
  
   atomTyper typer;
   typer.setFormalCharges(mol); 
   int totalCharge = 0;
   for (int i=0; i<mol->atoms.size(); i++) {
      totalCharge += mol->atoms[i]->formalCharge;
   }	
   //Note eventually you will want to have CHARGE=n so that you can specify the total Charge on the molecule
   //if (totalCharge == 0) outFile << type<<" MMOK GEO-OK MMOK  "<<endl;
   //else  outFile << type<<" GEO-OK MMOK EF CHARGE="<<totalCharge<<endl;
//   outFile << type<<" MMOK GEO-OK CHARGE="<<totalCharge<<endl;
   outFile << type<<" MMOK GEO-OK PRECISE CHARGE="<<totalCharge << endl;
   outFile << "MOPAC "<<type<<" job run from the Dynamol software chargeBegin"<<endl;
   outFile << endl;
      
   outFile.precision(5);
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      float *cd = atm->fCoords;
      string scd0 = dynabase::setNum(cd[0]);
      string scd1 = dynabase::setNum(cd[1]);
      string scd2 = dynabase::setNum(cd[2]);
      if (optimize) {
         outFile << atm->getAN()
                 << setw(15) << scd0 << setw(5) << 1
                 << setw(15) << scd1 << setw(5) << 1
                 << setw(15) << scd2 << setw(5) << 1
                 << endl;
      } else { 
         outFile << atm->getAN()
                 << setw(15) << scd0 << setw(5) << 0
                 << setw(15) << scd1 << setw(5) << 0
                 << setw(15) << scd2 << setw(5) << 0
                 << endl;
     }
   }
   outFile.close();
   outFile.clear();
   system("mopac mol");
   #ifdef LINUX
      system("mopac mol");
   #endif
 
   #ifdef WINDOWS
      system("MOPAC.exe mol.dat");
   #endif

   ifstream inFile("mol.arc", ios::in); 
   //if mol.arc not found then post event that MOPAC is not found
   if (!inFile) {
      return false;
   }

   string tmp;

   int count = 0;
   while (inFile >> tmp) {
      if (inFile.eof()) {
         return false;
      }
      
      if (tmp == "chargeBegin") 
         count++;
      if (count == 2) 
         break;
   }

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

   mol->chargeType = type;

   inFile.close();
   inFile.clear();

   //CLEANUP THE DIRECTORY

   #ifdef LINUX
      system("rm -f mol.out mol.dat mol.arc mol.mno mol.end FOR011");
   #endif

   #ifdef WINDOWS
      system("del mol.out mol.dat mol.arc mol.mno, mol.end, FOR011");
   #endif

   return true;
}

bool charge::AM1_BCC_Charges(bool optimize) {
   if( !mopacCharges("AM1", optimize) ) {
      return false;
   }
   AM1_BCC am1_bcc;   
   am1_bcc.am1_bcc_Aromaticity(mol);
   am1_bcc.BCC_BondOrderString(mol);
   am1_bcc.BCC_AtomTypes(mol);
   if (!am1_bcc.BCC_getCorrections(mol) ) {
      cout <<"BCC_getCorrections failed"<<endl;
      return false;
   }
   
   return true;
}

bool charge::amberChargesNew() {
return true;
}

bool charge::chargeChain2(vector<molecule *> &frags) {
   //LINUX 2
   string Path = getenv("DYNAMOL");
   Path += "/ForceField/amber_03.in";

   //WINDOWS 1
   //string Path = "ForceField\\amber_03.in";

   ifstream inFile(Path.c_str(), ios::in);

   if (!inFile) {
      cout <<"amber_03.in File not opened"<<endl;
      return false;
   }
   vector<dynacomp::chargeStruct *> resTypes;
//   vector<chargeStruct *> resTypes;
   string tmp, atmType, ffType;
   float chg;

   dynacomp::chargeStruct *tmpStruc = NULL;
//   chargeStruct *tmpStruc = NULL;
   int a = 0;
   if (resTypes.size() == 0) {
      while (true) {
         getline(inFile, tmp);
         if (tmp == "END") {
            break;
         }

         if (tmp[0] == '#') {
            if (a > 0) {
             resTypes.push_back(tmpStruc);
            }
            a++;
            tmpStruc = new dynacomp::chargeStruct;
            //tmpStruc = new chargeStruct;
            tmpStruc->name = tmp;
            getline(inFile, tmp);
         }
         istringstream s1(tmp);
         s1 >> atmType >> ffType >> chg;
         atmType = tmp.substr(0,3); //this makes it match up with the way I read PDB files
         tmpStruc->atoms.push_back(atmType);
         tmpStruc->ff_type.push_back(ffType);
         tmpStruc->charge.push_back(chg);
      }
   }

   for (int i=0; i<frags.size(); i++) {
      chargeChain2(frags[i], resTypes);
   }
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
      nonStandardResidue(frag);
   }
}


void charge::chargeAlanine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   string search;
   if (ter == 0 ) search = "#ALANINE";
   else if (ter == 1) search = "#c-ALANINE";
   else if (ter == 2) search = "#n-ALANINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) { 
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
      if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ")
         atm->setSymbol("H  ");
      if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ")
         atm->setSymbol("HA ");
      if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ")
         atm->setSymbol("HB1");
   }

   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
         if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#GLYCINE";
   else if (ter == 1) search = "#c-GLYCINE";
   else if (ter == 2) search = "#n-GLYCINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#SERINE";
   else if (ter == 1) search = "#c-SERINE";
   else if (ter == 2) search = "#n-SERINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "OG ") atm->setSymbol("HG ");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   int ter = isTerminalFrag(frag);
   string search;
   if (ter == 0 ) search = "#THREONINE";
   else if (ter == 1) search = "#c-THREONINE";
   else if (ter == 2) search = "#n-THREONINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG2") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "OG1") atm->setSymbol("HG1");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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

void charge::chargeLeucine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   string search;
   if (ter == 0 ) search = "#LEUCINE";
   else if (ter == 1) search = "#c-LEUCINE";
   else if (ter == 2) search = "#n-LEUCINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG ") atm->setSymbol("HG ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD1") atm->setSymbol("HD1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD2") atm->setSymbol("HD2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#ISOLEUCINE";
   else if (ter == 1) search = "#c-ISOLEUCINE";
   else if (ter == 2) search = "#n-ISOLEUCINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG2") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG1") atm->setSymbol("HG1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD1") atm->setSymbol("HD1");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#VALINE";
   else if (ter == 1) search = "#c-VALINE";
   else if (ter == 2) search = "#n-VALINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG2") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG1") atm->setSymbol("HG1");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#ASPARAGINE";
   else if (ter == 1) search = "#c-ASPARAGINE";
   else if (ter == 2) search = "#n-ASPARAGINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") 
     	atm->setSymbol("H  ");
     else if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") 
     	atm->setSymbol("HA ");
     else if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ")
     	atm->setSymbol("HB2");
     else if (atNum == 1 && atm->atoms[0]->getSymbol() == "ND2")
     	atm->setSymbol("HD2"); 
   }

   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#GLUTAMINE";
   else if (ter == 1) search = "#c-GLUTAMINE";
   else if (ter == 2) search = "#n-GLUTAMINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
       if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG ") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "NE2") atm->setSymbol("HE2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#ARGININE";
   else if (ter == 1) search = "#c-ARGININE";
   else if (ter == 2) search = "#n-ARGININE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
       if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG ") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD ") atm->setSymbol("HD2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "NE ") atm->setSymbol("HE ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "NH1") atm->setSymbol("HH1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "NH2") atm->setSymbol("HH2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#TRYPTOPHAN";
   else if (ter == 1) search = "#c-TRYPTOPHAN";
   else if (ter == 2) search = "#n-TRYPTOPHAN";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD1") atm->setSymbol("HD1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "NE1") atm->setSymbol("HE1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CZ2") atm->setSymbol("HZ2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CH2") atm->setSymbol("HH2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CZ3") atm->setSymbol("HZ3");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CE3") atm->setSymbol("HE3");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#PHENYLALANINE";
   else if (ter == 1) search = "#c-PHENYLALANINE";
   else if (ter == 2) search = "#n-PHENYLALANINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
       if (dynabase::inString(data[i]->name, search)) {
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
         int atNum = atm->getAN();
         if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ")atm->setSymbol("H  ");
         if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
         if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
         if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD1") atm->setSymbol("HD1");
         if (atNum == 1 && atm->atoms[0]->getSymbol() == "CE1") atm->setSymbol("HE1");
         if (atNum == 1 && atm->atoms[0]->getSymbol() == "CZ ") atm->setSymbol("HZ ");
         if (atNum == 1 && atm->atoms[0]->getSymbol() == "CE2") atm->setSymbol("HE2");
         if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD2") atm->setSymbol("HD2");
      }
      for (int i=0; i<frag->atoms.size(); i++) {
         atom *atm = frag->atoms[i];
         for (int j=0; j<struc->atoms.size(); j++) {
            if (atm->getSymbol() == struc->atoms[j]) {
	       atm->setCharge(struc->charge[j]);
	       atm->setFFType(struc->ff_type[j]);	
	    }
         }
      }  
   } else {
     this->nonStandardResidue(frag); 
   } 
}

void charge::chargeTyrosine2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   string search;
   if (ter == 0 ) search = "#TYROSINE";
   else if (ter == 1) search = "#c-TYROSINE";
   else if (ter == 2) search = "#n-TYROSINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
       if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD1") atm->setSymbol("HD1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CE1") atm->setSymbol("HE1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "OH ") atm->setSymbol("HH ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CE2") atm->setSymbol("HE2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD2") atm->setSymbol("HD2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#GLUTAMIC ACID";
   else if (ter == 1) search = "#c-GLUTAMIC ACID";
   else if (ter == 2) search = "#n-GLUTAMIC ACID";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
       if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG ") atm->setSymbol("HG2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#GLUTAMIC ACID";
   else if (ter == 1) search = "#c-GLUTAMIC ACID";
   else if (ter == 2) search = "#n-GLUTAMIC ACID";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
       if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG ") atm->setSymbol("HG2");
     //if (atNum == 1 && atm->atoms[0]->getSymbol() == "OE2") atm->setSymbol("HO ");
     //You think this will work better if some adds an H by hand
     if (atNum == 1 && atm->atoms[0]->getAtomicNum() == 8) atm->setSymbol("HO ");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#ASPARTIC ACID";
   else if (ter == 1) search = "#c-ASPARTIC ACID";
   else if (ter == 2) search = "#n-ASPARTIC ACID";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#LYSINE";
   else if (ter == 1) search = "#c-LYSINE";
   else if (ter == 2) search = "#n-LYSINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG ") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD ") atm->setSymbol("HD2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CE ") atm->setSymbol("HE2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "NZ ") atm->setSymbol("HZ1");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#PROLINE";
   else if (ter == 1) search = "#c-PROLINE";
   else if (ter == 2) search = "#n-PROLINE";
   chargeStruct *struc = NULL;

   for (int i=0; i<data.size(); i++) {
      //if (data[i]->name.contains(search)) {
      if (dynabase::inString(data[i]->name, search)) {
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
      if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ")
         atm->setSymbol("H  ");
      if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD ")
         atm->setSymbol("HD2");
      if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG ")
         atm->setSymbol("HG2");
      if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ")
         atm->setSymbol("HB2");
      if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ")
         atm->setSymbol("HA ");
   }

   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
         if (atm->getSymbol() == struc->atoms[j]) {
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

void charge::chargeCysteine2(molecule *frag, vector<chargeStruct *> &data) {
  //We need to check for CS-SC disulfide bridge
  /*
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
	      ////////////cout <<"You did make it here"<<endl;
	      if (chAtm->atoms.size() == 1) {
	         chargeCysteine2_negative(frag, data);
		 return;
	      }
	      for (int j=0; j<chAtm->atoms.size(); j++) {
	        if (chAtm->atoms[j]->getAtomicNum() == 16) {
		  chAtm->setSelected(true);
		  chAtm->atoms[j]->setSelected(true);
		  ////////////cout <<"Calling the disulfide"<<endl;
		  chargeCysteine2_disulfide(frag, data);
		  return;
		}
	      }
	      
	   }
        }
       }
     }
  }
  */
  cout <<"You still need to fix check for Disulfide bonds"<<endl;
  chargeCysteine_normal(frag, data);
  
}

void charge::chargeCysteine_normal(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   string search;
   if (ter == 0 ) search = "#CYSTEINE";
   else if (ter == 1) search = "#c-CYSTEINE";
   else if (ter == 2) search = "#n-CYSTEINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "SG ") atm->setSymbol("HG ");
   }
   
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#CYSTINE(S-S BRIDGE)";
   else if (ter == 1) search = "#c-CYSTINE(S-S BRIDGE)";
   else if (ter == 2) search = "#n-CYSTINE(S-S BRIDGE)";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#METHIONINE";
   else if (ter == 1) search = "#c-METHIONINE";
   else if (ter == 2) search = "#n-METHIONINE";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CG ") atm->setSymbol("HG2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CE ") atm->setSymbol("HE1");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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

void charge::chargeHistidine(molecule *frag, vector<chargeStruct *> &data) {
   int a = 0;
   int b = 0;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     if (atm->getAtomicNum() == 1 && atm->atoms[0]->getSymbol() == "ND1") a++;
     if (atm->getAtomicNum() == 1 && atm->atoms[0]->getSymbol() == "NE2") b++;
   }
   
   if (a == 1 && b == 1) chargeHistidine_Plus2(frag, data);
   if (a == 0 && b == 1) chargeHistidine_Epsilon2(frag, data);
   if (a == 1 && b == 0) chargeHistidine_Delta2(frag, data);
     
}
void charge::chargeHistidine_Plus2(molecule *frag, vector<chargeStruct *> &data) {
   int ter = isTerminalFrag(frag);
   string search;
   if (ter == 0 ) search = "#HISTIDINE PLUS";
   else if (ter == 1) search = "#c-HISTIDINE PLUS";
   else if (ter == 2) search = "#n-HISTIDINE PLUS";
   chargeStruct *struc = NULL;
   
   for (int i=0; i<data.size(); i++) {
       if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "ND1") atm->setSymbol("HD1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CE1") atm->setSymbol("HE1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "NE2") atm->setSymbol("HE2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD2") atm->setSymbol("HD2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#HISTIDINE EPSILONH";
   else if (ter == 1) search = "#c-HISTIDINE EPSILONH";
   else if (ter == 2) search = "#n-HISTIDINE EPSILONH";
   chargeStruct *struc = NULL;
    
    for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
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
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CE1") atm->setSymbol("HE1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "NE2") atm->setSymbol("HE2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD2") atm->setSymbol("HD2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
   string search;
   if (ter == 0 ) search = "#HISTIDINE DELTAH";
   else if (ter == 1) search = "#c-HISTIDINE DELTAH";
   else if (ter == 2) search = "#n-HISTIDINE DELTAH";
   chargeStruct *struc = NULL;
    
   for (int i=0; i<data.size(); i++) {
     //if (data[i]->name.contains(search)) {
     if (dynabase::inString(data[i]->name, search)) {
       struc = data[i];
       break;
     }
   } 
    //This checks makes sure the fragment has the correct number of atoms.
   //If not is prints out a warning message
  // //////////cout <<"chargeHistidine_Delta2"<<endl;
   if (checkFragment(frag, struc) ) {
   
   //first thing that we need to do is change the H atom types;
   for (int i=0; i<frag->atoms.size(); i++) {
     atom *atm = frag->atoms[i];
     int atNum = atm->getAtomicNum();
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "N  ") atm->setSymbol("H  ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CA ") atm->setSymbol("HA ");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CB ") atm->setSymbol("HB2");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "ND1") atm->setSymbol("HD1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CE1") atm->setSymbol("HE1");
     if (atNum == 1 && atm->atoms[0]->getSymbol() == "CD2") atm->setSymbol("HD2");
   }
   
   for (int i=0; i<frag->atoms.size(); i++) {
      atom *atm = frag->atoms[i];
      for (int j=0; j<struc->atoms.size(); j++) {
        if (atm->getSymbol() == struc->atoms[j]) {
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
        if (atm->getSymbol() == struc->atoms[j]) {
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
   //First lets check for lone H atoms..they will be deleteg...
   
   for (int i=0; i<frag->atoms.size(); i++) {   
      atom *atm = frag->atoms[i];
      if (atm->atoms.size() == 0 && atm->getAtomicNum() == 1) {
         cout <<"Found Lone H Atom: " << atm->getNum() <<"\t" << frag->getName() <<endl;
         //TrashCan t(atm); 
         //t.empty();
      }
   }
   
   if (frag->atoms.size() != struc->atoms.size()) {
     bool isTerminal = false;
     for (int i=0; i<frag->atoms.size(); i++) {
        if (frag->atoms[i]->getSymbol() == "OXT") {
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
         //molecule *ch = dynamic_cast<molecule *>(frag->getParent());
         return false;
      }
   }
   
   return true;
}

int charge::isTerminalFrag(molecule *frag) {
    //check for n-terminal
    int hCount = 0;
    for (int i=0; i<frag->atoms[0]->atoms.size(); i++) {
       atom *atm = frag->atoms[0]->atoms[i];
       if (atm->getAtomicNum() == 1) 
          hCount++;
    }
    if (hCount >= 2) {
	return 2;
    }
    if (hCount >= 1 && frag->getName() == "PRO") {
        //out <<"Fragment was n-Terminal: " << frag->getName() << endl;
	return 2;
    }
    
    //Now check for c-terminal
    for (int i=0; i<frag->atoms.size(); i++) {
       atom *atm = frag->atoms[i];
       if (atm->getSymbol() == "OXT") {
          return 1;
       }
    }
    //Wasn't a terminal atom
    return 0;
}

void charge::nonStandardResidue(molecule *frag) {
   //This first line checks for metals...but allows waters.
  //////////cout <<"NOt using this function right now."<<endl;
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
     }
  }
  cout <<"Leaving nonStandard"<<endl;
  return;
}

}

