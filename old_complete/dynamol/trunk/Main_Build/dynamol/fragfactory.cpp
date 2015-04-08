/***************************************************************************
                          fragfactory.cpp  -  description
                             -------------------
    begin                : Thu Feb 5 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include <qmessagebox.h>
#include "fragment.h"
#include "pdbreadfrag.h"
#include "fragfactory.h"
#include "moldb.h"

#include "atom.h"
#include "bond.h"


fragFactory::fragFactory(){
}
fragFactory::~fragFactory(){
}

fragment *fragFactory::getNewFrag(string type, vector<string> *fragInfo) {
  fragment *frag = NULL;
  if (frag != NULL) {
    checkFrag_2(frag, *fragInfo);
  } else {
    frag = new fragment();
    buildFrag(frag, *fragInfo);
    if (type == "HOH") frag->setName("water");
  }
  if (frag->getNumOfBonds() > 0) {
    frag->setBondToBegin();
    for (;;) {
      bond *bd = frag->getCurrentBond();
      //bd->calcMidPoint();
      bd->calcDirCosines();
      if (!frag->nextBond())
        break;
    }
  }
  
  for (int i=0; i<frag->atoms.size(); i++) {
    atom *atm = frag->atoms[i];
    if (atm->getSym() == "C  " || atm->getSym() == "N  " || atm->getSym() == "O  " || atm->getSym() == "CA ") {
      atm->protType = BACKBONE;
    } else {
      atm->protType = SIDE_CHAIN;
    }
  }
  return frag;
}

void fragFactory::checkFrag_2(fragment *frag, vector< string > &fr) {
  int test =0;

  string x, y, z, tmpFactor;
  float X, Y, Z;
  float temp;
  vector<double> tmpD;

  atom *at;
  int number = 0;
  if (fr.size() < frag->getNumOfAtoms()) {
    number = fr.size();
  } else {
    number = frag->getNumOfAtoms();
  }

  int NUMBER;
  string num;
  int i=0;
  //for (;;) {
  for (int i=0; i<frag->atoms.size(); i++) {
    if (i < number) {
      x = fr[i].substr(30, 8);
      y = fr[i].substr(38, 8);
      z = fr[i].substr(46, 8);
      num = fr[i].substr(6, 5);

      X = atof(x.c_str());
      Y = atof(y.c_str());
      Z = atof(z.c_str());
      NUMBER = i; //fragments have atoms that are numbered differently

      tmpFactor = fr[i].substr(60, 7);
      temp = atof(tmpFactor.c_str());

      at = frag->atoms[i];
      at->setCoords(X, Y, Z);

      at->setTemp(temp);
      at->setNum(NUMBER);

      i++;
    } else {
      at = frag->atoms[i];
      frag->setBondToEnd();
      bond *bdc;
      for (;;) {
        bdc = frag->getCurrentBond();
        if (at == bdc->toAtom()) {
          frag->deleteBond(bdc);
          break;
        }
        if (!frag->prevBond()) {
          break;
        }

      }

      frag->removeAtom(at);

    }

  }
  if (frag->getNumOfAtoms() < fr.size()) {
    for (int i=frag->getNumOfAtoms(); i<fr.size(); i++) {
      int atomNum = frag->atoms.size()+1;
      int bondNum = frag->bonds.size()+1;
      string atomType = fr[i].substr(12,4);
      x = fr[i].substr(30, 8);
      y = fr[i].substr(38, 8);
      z = fr[i].substr(46, 8);
		  num = fr[i].substr(6, 5);

      X = atof(x.c_str());
      Y = atof(y.c_str());
      Z = atof(z.c_str());
      NUMBER = atoi(num.c_str());
      atom *atm;
      int atomicNum = molDB::SYM2AN(atomType);
      atm = frag->addAtom(atomNum, atomType, X, Y, Z, atomicNum);
      
      //Now lets create the bond.
      vector<float> cor1, cor2;
      atm->getCoords(cor2);
      float smallest = 100;
      atom *hold, *tmp;
      int count = 0;
      for (int i=0; i<frag->atoms.size(); i++) {
	tmp = frag->atoms[i];
        count++;
        tmp->getCoords(cor1);
        double distance = sqrt((cor1[0]-cor2[0])*(cor1[0]-cor2[0]) + (cor1[1]-cor2[1])*(cor1[1]-cor2[1]) + (cor1[2]-cor2[2])*(cor1[2]-cor2[2]));
        if (distance < smallest && distance != 0) {
           smallest = distance;
           hold = tmp;
        }   
      } 

      if (atm->addAtom(hold) && hold->addAtom(atm) ) {
        bond *bd = new bond(bondNum, atm, hold, 1);
        frag->bonds.push_back(bd);
        bd->setParent(frag);
      } 
    }
  }
}

void fragFactory::buildFrag(fragment *frag, vector<string> &fragInfo) {
  string x, y, z, tmpFactor, num;
  double X, Y, Z;
  float temp;
  if (fragInfo.size() == 1) {
      int atomNum = frag->getNumOfAtoms();
      int bondNum = frag->getNumOfBonds();

      string atomType;
      if (fragInfo[0][12] == ' ')
         atomType = fragInfo[0].substr(13,3);
      else
         atomType = fragInfo[0].substr(12,3);

      x = fragInfo[0].substr(30, 8);
      y = fragInfo[0].substr(38, 8);
      z = fragInfo[0].substr(46, 8);
      num = fragInfo[0].substr(6, 5);

      X = atof(x.c_str());
      Y = atof(y.c_str());
      Z = atof(z.c_str());
      int NUMBER = atoi(num.c_str());
      //int atomicNum = getAtomicNum(atomType);
      int atomicNum = molDB::SYM2AN(atomType);
      atom *tmpAtom = frag->addAtom(atomNum, atomType, X, Y, Z, atomicNum);
  }

  if (fragInfo.size() > 1) { 
     string resName = fragInfo[0].substr(17,3);
     frag->setName(resName);
     for (unsigned int i=0; i< fragInfo.size(); i++) {
        int atomNum = frag->getNumOfAtoms();
        int bondNum = frag->getNumOfBonds();
        string atomType = fragInfo[i].substr(13,3);
        checkResidue(frag, atomType);
        x = fragInfo[i].substr(30, 8);
        y = fragInfo[i].substr(38, 8);
        z = fragInfo[i].substr(46, 8);
        num = fragInfo[i].substr(6, 5);

        X = atof(x.c_str());
        Y = atof(y.c_str());
        Z = atof(z.c_str());
        int NUMBER = atoi(num.c_str());
     
        //int atomicNum = getAtomicNum(atomType);
        int atomicNum = molDB::SYM2AN(atomType);
        atom *tmpAtom = frag->addAtom(atomNum, atomType, X, Y, Z, atomicNum);

        //tmpAtom->setColor(-2);
        vector<float> cor1;
        tmpAtom->getCoords(cor1);
        int smallest = 10000;

        atom *holdAtm, *atm;
        if (i != 0) { //make sure there is more than 1 atom added to the fragment first.
	   for (int i=0; i<frag->atoms.size(); i++) {
              //atm = frag->getCurrentAtom();
	      atm = frag->atoms[i];
              vector<float> cor2;
              atm->getCoords(cor2);
              float distance = sqrt( (cor1[0]-cor2[0])*(cor1[0]-cor2[0]) + (cor1[1]-cor2[1])*(cor1[1]-cor2[1]) 
                                     + (cor1[2]-cor2[2])*(cor1[2]-cor2[2]));

              if ((distance < 2.0 || ((atm->getAN() >= 15 || tmpAtom->getAN() >= 15) && distance < 2.45) )&& distance != 0) {
		 if ((atm->getAN() == 1 || tmpAtom->getAN() == 1) && distance > 1.4) {
                 
	         //if (((atm->getAN() == 1 && tmpAtom->getAN() <15) 
                 //   ||(tmpAtom->getAN() == 1 && atm->getAN() < 15)) && distance > 1.4) {
	         } else {
                    smallest = distance;
                    holdAtm = atm;
                    if (atm->getAtomicNum() != 1 || tmpAtom->getAtomicNum() != 1) {
	      
              
  	               if (atm->addAtom(tmpAtom) && tmpAtom->addAtom(atm) ) {
	                  bond *bd = new bond(bondNum, atm, tmpAtom, 1);
	                  int tmpOrder = detBondOrder(bd);
                          bd->setParent(frag);
	                  frag->bonds.push_back(bd);
	               } else {
	               }	     
                    }
                 }       
	      }    
           }
           //bond *bd = new bond(bondNum, atm, holdAtm, 1);
           //frag->addBond(bd);
         }
       }
  }
}


int fragFactory::detBondOrder(bond *bd) { 
   atom *atm1 = bd->fromAtom();
   atom *atm2 = bd->toAtom();
   
   molecule *par = dynamic_cast<molecule *>(atm2->getParent());
   if (par == NULL) {
       cout <<"Par was null: " << endl;
       return -1;
   }
   string sym1 = atm1->getSym();
   string sym2 = atm2->getSym();
   //Check for the carbonyl types first
   if (par->getName() == "ALA" || par->getName() == "CYS" 
     ||par->getName() == "ASP" || par->getName() == "GLU"
     ||par->getName() == "PHE" || par->getName() == "GLY"
     ||par->getName() == "HIS" || par->getName() == "ILE"
     ||par->getName() == "LYS" || par->getName() == "LEU"
     ||par->getName() == "MET" || par->getName() == "ASN"
     ||par->getName() == "PRO" || par->getName() == "GLN"
     ||par->getName() == "ARG" || par->getName() == "SER"
     ||par->getName() == "SER" || par->getName() == "THR"
     ||par->getName() == "VAL" || par->getName() == "TRP" 
     ||par->getName() == "TYR") {
   	if (atm1->getSym() == "C  " && atm2->getSym() == "O  ") bd->setOrder(2);
   	if (atm2->getSym() == "C  " && atm1->getSym() == "O  ") bd->setOrder(2);
   }
   //Tyrosine/Phynelalanine ring system stuff
   if (par->getName() == "TYR" || par->getName() == "PHE") {
   	if (sym1 == "CG " && sym2 == "CD1") bd->setOrder(2);
   	if (sym2 == "CG " && sym1 == "CD1") bd->setOrder(2);
   
   	if (sym1 == "CD2" && sym2 == "CE2") bd->setOrder(2);
   	if (sym2 == "CD2" && sym1 == "CE2") bd->setOrder(2);
   
   	if (sym1 == "CZ " && sym2 == "CE1") bd->setOrder(2);
   	if (sym2 == "CZ " && sym1 == "CE1") bd->setOrder(2);

        if (atm1->getSym() == "C  " && atm2->getSym() == "O  ") bd->setOrder(2);
        if (atm2->getSym() == "C  " && atm1->getSym() == "O  ") bd->setOrder(2);
   }
   
   //Arginine
   if (par->getName() == "ARG") {
   	if (sym1 == "NE " && sym2 == "CZ ") bd->setOrder(2);
   	if (sym2 == "NE " && sym1 == "CZ ") bd->setOrder(2);
   }
   
   //Asparagin
   //if (par->getName() == "ARG") {
   //	if (sym1 == "NH2" && sym2 == "CZ ") bd->setOrder(2);
   //	if (sym2 == "NH2" && sym1 == "CZ ") bd->setOrder(2);
   //}
   //Aspartic Acid
   if (par->getName() == "ASN" || par->getName() == "ASP") {
   	if (sym1 == "OD1" && sym2 =="CG ") bd->setOrder(2);
   	if (sym2 == "OD1" && sym1 =="CG ") bd->setOrder(2);
   }
   //Glutamic acid
   if (par->getName() == "GLU" || par->getName() == "GLN") {
   	if (sym1 == "OE1" && sym2 =="CD ") bd->setOrder(2);
   	if (sym2 == "OE1" && sym1 =="CD ") bd->setOrder(2);
   }
   //Histidine defualts to the epsilon
   if (par->getName() == "HIS") {
   	if (sym1 == "CG " && sym2 == "CD2") bd->setOrder(2);
   	if (sym2 == "CG " && sym1 == "CD2") bd->setOrder(2);
   
   	if (sym1 == "ND1" && sym2 == "CE1") bd->setOrder(2);
   	if (sym2 == "ND1" && sym1 == "CE1") bd->setOrder(2);
	
	//uncomment these to default to delta histidine
	//if (sym2 == "CE1" && sym1 == "NE2") bd->setOrder(2);
	//if (sym1 == "CE1" && sym2 == "NE2") bd->setOrder(2);
   }
   
   //Typrophan
   if (par->getName() == "TRP") {
   	if (sym1 == "CZ3" && sym2 == "CE3") bd->setOrder(2);
	if (sym2 == "CZ3" && sym1 == "CE3") bd->setOrder(2);
	
	if (sym1 == "CH2" && sym2 == "CZ2") bd->setOrder(2);
	if (sym2 == "CH2" && sym1 == "CZ2") bd->setOrder(2);
	
	if (sym1 == "CD2" && sym2 == "CE2") bd->setOrder(2);
	if (sym2 == "CD2" && sym1 == "CE2") bd->setOrder(2);
	
	if (sym1 == "CG " && sym2 == "CD1") bd->setOrder(2);
	if (sym2 == "CG " && sym1 == "CD1") bd->setOrder(2);
	
   }
  return 1;
}

void fragFactory::checkResidue(fragment *frag, string &atomType) {
   if (frag->getName() == "ASN" && atomType == "OD2") {
      if (QMessageBox::question(0, "PDB Error", "ASN is defined like ASP in the PDB file. \nDo you want to makethis residue ASN or ASP?\nDynamol recommends staying with ASN.",
            "&ASN",  "&ASP", QString::null, 0, 1 ) )  {
            ////////////cout <<"Changing to ASP"<<endl;
       frag->setName("ASP");
      } else {
         ////////////cout <<"Makeing a real ASN"<<endl;
    atomType = "ND2";
      }
   }
}




































