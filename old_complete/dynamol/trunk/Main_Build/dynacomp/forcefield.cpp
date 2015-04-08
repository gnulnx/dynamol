/***************************************************************************
                          forcefield.cpp  -  description
                             -------------------
    begin                : Sun Feb 22 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : John.furr@dynamol.com
 ***************************************************************************/

#include "forcefield.h"
#include <cmath>
#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "angle.h"

#include "gaff.h"
#include "amber.h"
#include "torsion.h"

#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;
#include "charge.h"

#include "../dynatype/dtype.h"
#include "../dynatype/molecule.h"

//Dynamol Convert Library
#include "../convert/convert.h"
//#include "moladapter.h"

//Dynamol base Library Includes
#include "../dynabase/utility.h"


namespace dynacomp {
forceField::forceField() 
{
   gaffTyper = NULL;
   amberTyper = NULL;
   errorMsg = "";
}

forceField::~forceField(){
}

string forceField::getErrorMsg() 
{ return errorMsg; }

bool forceField::setAtomTypes(molecule *mol, string &type) {
   //If molecule does not have the correct types the call dynatype && set them   
   if (mol->ffTypes != type) {
      dt::dType d;
      dt::molPtr dtmol( new dt::molecule );
      dt::convert::toDynatype(dtmol, mol);
      if (type == "GAFF") {
         d.setGaffTypes(dtmol);
      }
      if ( type == "AMBER_03") {
         d.setAmber03Types(dtmol);
      }
  
      dt::convert::update(mol, dtmol);
      bool badType = false;
      vector<string> badTypes;
      for (int i=0; i<mol->atoms.size(); i++) {
         atom *atm = mol->atoms[i];
         string type = atm->getFFType();
         if (type == "none") {
            string num = dynabase::setNum(mol->atoms[i]->getNum());
            molecule *tmpMol = atm->getParent();
            string molName = tmpMol->getName();
            string error = molName + ": atom " + num + "("+ atm->getSymbol() +")";
            badTypes.push_back(error);
         }
      }
      
	  if (badTypes.size() > 0) {
         string error = "Dynamol encountered problems typing the following atoms\n";
         for (int i=0; i<badTypes.size(); i++) {
            error += badTypes[i] +"\n";
         }
         cout <<"Those weere the errors: " << error << endl;
         int test = 0;
         cin >> test;
         return false;
      }
      mol->ffTypes = type;         
   }   
   mol->ffTypes = type;
    
   bool badType = false;
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      if (atm->getFFType() == "*") {   
         molecule *parent = dynamic_cast<molecule *>(atm->getParent());
         if (parent->atoms.size() != 1) { 
            badType = true;
         }
      }
   }
   if (badType) {
      cout <<"Bad Type: returning false"<<endl;
      return false;
   }
   return true;
}

bool forceField::setCharges(molecule *mol, string &type) {

	return false;
}


bool forceField::buildLists(molecule *mol, string &type) {
   bool setTypes = false;
   if (mol->ffTypes != type) 
      setTypes = true;

   if (mol->angles.size() == 0) 
   {mol->setAngles(); setTypes = true;}

   if (mol->torsions.size() == 0) 
   {mol->setTorsions(); setTypes = true;}

   if (mol->nonBonds.size() == 0) 
   {setTypes = true;}

   if (mol->torsions.size() == 0)
   { setTypes = true; }

   if (setTypes) {
      if (type == "GAFF") {
         gaffTyper = new gaff;
      }
      if (type== "AMBER_03") {
         amberTyper = new amber;
      }   

      int badIndex = -1;
      if (!setBonds(mol->bonds, type, badIndex)) {
         if (gaffTyper)
            delete gaffTyper;
         if (amberTyper);
            delete amberTyper;
         return false;
      }

      if (!setAngles(mol->angles, type, badIndex)) {
         /*
         if (badIndex != -1) {
            mol->ffTypes = "NONE";
            anglePtr ang = mol->angles[badIndex];
            ofstream outFile("bad_angles.txt", ios::app);
            outFile << mol->getName() <<setw(12) << ang->front->getFFType();
            outFile << setw(12) << ang->mid->getFFType();
            outFile << setw(12) << ang->back->getFFType() << endl;
         }
         */
         if (gaffTyper)
            delete gaffTyper;
         if (amberTyper);
            delete amberTyper;
         return false;
      }
      if (!setTorsions(mol->torsions, type, badIndex)) {
         if (gaffTyper)
            delete gaffTyper;
         if (amberTyper);
            delete amberTyper;
         return false;
      }
      if (!setNonBonds(mol, type, badIndex)) {
         if (gaffTyper)
            delete gaffTyper;
         if (amberTyper);
            delete amberTyper;
         return false;
      }
   } 
   if (mol->nonBonds.size() == 0)
   {mol->setNonBonds(100); setTypes = true;}
   return true;
}

bool forceField::setBonds(vector<bond *> &Bonds, string &method, int &badIndex) {
   if (method == "GAFF") { 
      if (!gaffTyper) 
         gaffTyper = new gaff;

      if (!gaffTyper->setBonds(Bonds, badIndex)) {
         errorMsg = gaffTyper->getErrorMsg();
         return false;
      } 
      return true;
   }
   else if (method == "AMBER_03" ) {
      if (!amberTyper) 
         amberTyper = new amber;
      if ( !amberTyper->setBonds(Bonds, badIndex) ) {
         errorMsg = amberTyper->getErrorMsg();
         return false;
      }
      return true;
   }
   else {
      errorMsg = "Force Field Type ";
      errorMsg += method + " is not suported";
      return false;
   }
}

bool forceField::setAngles(vector<anglePtr> &Angles, string &method, int &badIndex) { 
   if (method == "GAFF") { 
       if (!gaffTyper) 
          gaffTyper = new gaff;
       if (!gaffTyper->setAngles(Angles, badIndex) ) {
          errorMsg = gaffTyper->getErrorMsg();
          return false;
       }
       return true;
   }
   else if (method == "AMBER_03" ) {
       if (!amberTyper) 
          amberTyper = new amber;
       if ( !amberTyper->setAngles(Angles, badIndex) ) {
          errorMsg = amberTyper->getErrorMsg();
          return false;
       }
       return true;
   }
   else {
      errorMsg = "Force Field Type ";
      errorMsg += method + " is not suported";
      return false;
   }
}

bool forceField::setNonBonds(molecule *mol, string &method, int &badIndex) {    
   if (method == "GAFF") {
      if (!gaffTyper) gaffTyper = new gaff;
      return gaffTyper->setNonBonds(mol, badIndex);
   }
   else if (method == "AMBER_03" ) {
      if (!amberTyper) amberTyper = new amber;
      return amberTyper->setNonBonds(mol, badIndex);
   }
   else {
      errorMsg = "Force Field Type ";
      errorMsg += method + " is not suported";
      return false;
   }
}

bool forceField::setTorsions(vector<torPtr> &Torsions, string &method, int &badIndex) {
  if (method == "GAFF") {
     if (!gaffTyper) 
        gaffTyper = new gaff;
   
     if ( !gaffTyper->setTorsions(Torsions, badIndex) ) {
        errorMsg = gaffTyper->getErrorMsg();
        return false;
     }   
     return true;
   }
   else if (method == "AMBER_03" ) {
      if (!amberTyper) 
         amberTyper = new amber;
      if ( !amberTyper->setTorsions(Torsions, badIndex) ) {
         errorMsg = amberTyper->getErrorMsg();
         return false;
      }
      return true;
   }
   else {
      errorMsg = "Force Field Type ";
      errorMsg += method + " is not suported";
      return false;
   }
}

};//End Namespace





