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
//#include <qmessagebox.h>

//#include <qfile.h>
#include "moldb.h"
#include "molchangeevent.h"

#include "gaff.h"
#include "amber.h"
#include "torsion.h"

#include <iomanip>
#include "charge.h"

#include "../dynatype/dtype.h"
#include "../dynatype/molecule.h"
#include "moladapter.h"

#include <qmessagebox.h>

forceField::forceField() 
{
   gaffTyper = NULL;
   amberTyper = NULL;
}

forceField::~forceField(){
}

bool forceField::setAtomTypes(molecule *mol, string &type) {
   //If molecule does not have the correct types the call dynatype && set them  
   if (mol->ffTypes != type) {
      dt::dType d;
      //dt::molecule *dtmol = new dt::molecule;
      dt::molPtr dtmol( new dt::molecule );
      molAdapter::mol2molecule(dtmol, mol);
      if (type == "GAFF") {
         d.setGaffTypes(dtmol);
      }
      if ( type == "AMBER_03")
         d.setAmber03Types(dtmol);
         
      molAdapter::update(mol, dtmol);
      //delete dtmol;
       bool badType = false;
         vector<QString> badTypes;
         for (int i=0; i<mol->atoms.size(); i++) {
            atom *atm = mol->atoms[i];
            QString type = atm->getFFType();
            //mol->atoms[i]->getFFType() = types[i].latin1();
            if (type == "none") {
               //////////cout <<"Bad type " << atm->getFFtype() << endl;
               QString num; num.setNum(mol->atoms[i]->getNum());
               molecule *tmpMol = dynamic_cast<molecule *>(atm->getParent());
               QString molName = tmpMol->getName();
               QString error = molName + ": atom " + num + "("+ atm->getSym() +")";
               badTypes.push_back(error);
            }
         }
         //////////cout <<"HERE 1"<<endl;
         if (badTypes.size() > 0) {
            //////////cout <<"You are in badTypes"<<endl;
            QString error = "Dynamol encountered problems typing the following atoms\n";
            for (int i=0; i<badTypes.size(); i++) {
              error += badTypes[i] +"\n";
              //////////cout << badTypes[i] << endl;
            }
            
            //return false;
            molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1003));
            e->Msg = error;
            e->postEvent();
            return false;
         }
         //////////cout <<"HERE 2"<<endl;
         mol->ffTypes = type;         
      }   
      //////////cout <<"HERE 3"<<endl;
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
   //////////cout <<"HERE 4"<<endl;
   if (badType) {
      return false;
   }
   //////////cout <<"HERE 5"<<endl;
   return true;
}

bool forceField::setCharges(molecule *mol, string &type) {

	return false;
}


bool forceField::buildLists(molecule *mol, string &type) {
//   if (type == "GAFF")
//     gaffTyper = new gaff;
//   if (type== "AMBER_03")
//      amberTyper = new amber;

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
      if (type == "GAFF")
         gaffTyper = new gaff;
      if (type== "AMBER_03")
         amberTyper = new amber;

      int badIndex = -1;
      if (!setBonds(mol->bonds, type, badIndex)) {
	 //cout <<"set bonds failed"<<endl;	  
         if (badIndex != -1) {
            molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1004));
            e->bd = mol->bonds[badIndex];          
	    e->postEvent();
	    mol->ffTypes = "NONE";
 	    bond *bd = mol->bonds[badIndex];
            ofstream outFile("bad_bonds.txt", ios::app);
            outFile << mol->getName() <<setw(12) << bd->from->getFFType();
            outFile << setw(12) << bd->to->getFFType() << endl;

         }
         if (gaffTyper)
            delete gaffTyper;
         if (amberTyper);
            delete amberTyper;
         return false;
      }
        
      if (!setAngles(mol->angles, type, badIndex)) {
         //cout <<"Set angles failed"<<endl;
         if (badIndex != -1) {
            mol->ffTypes = "NONE";
            molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1005));
            e->ang = mol->angles[badIndex];
            angle *ang = mol->angles[badIndex];
            e->postEvent();
            ofstream outFile("bad_angles.txt", ios::app);
            outFile << mol->getName() <<setw(12) << ang->front->getFFType();
            outFile << setw(12) << ang->mid->getFFType();
            outFile << setw(12) << ang->back->getFFType() << endl;
         }
         if (gaffTyper)
            delete gaffTyper;
         if (amberTyper);
            delete amberTyper;
         return false;
      }

      if (!setTorsions(mol->torsions, type, badIndex)) {
         //cout <<"set torsions failed"<<endl;
         if (badIndex != -1) {
            molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1006));
            e->tor = mol->torsions[badIndex];
            e->postEvent();
         }
         if (gaffTyper)
            delete gaffTyper;
         if (amberTyper);
            delete amberTyper;
         return false;
      }
      if (!setNonBonds(mol, type, badIndex)) {
         //cout <<"setNonBonds failed"<<endl;
         if (badIndex != -1) {
            molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1007));
            e->nb = mol->nonBonds[badIndex];
            e->postEvent();
         }
         if (gaffTyper)
            delete gaffTyper;
         if (amberTyper);
            delete amberTyper;
         return false;
      }
   } 

//   if (gaffTyper)
//      delete gaffTyper;
//   if (amberTyper);
//      delete amberTyper;
   //Have the molecule determine all the angles, torsions, and nonBonds
   //if (mol->angles.size() == 0)
   //{mol->setAngles(); setTypes = true;}

   //if (mol->torsions.size() == 0)
   //{mol->setTorsions(); setTypes = true;}

   if (mol->nonBonds.size() == 0)
   {mol->setNonBonds(100); setTypes = true;}

   return true;
}

bool forceField::setBonds(vector<bond *> &Bonds, string &method, int &badIndex) {  //cout <<"Method: " << method << endl;
   if (method == "GAFF") {  
      if (!gaffTyper) gaffTyper = new gaff;
      return gaffTyper->setBonds(Bonds, badIndex);
   }
   else if (method == "AMBER_03" ) {
      if (!amberTyper) amberTyper = new amber; 
      return amberTyper->setBonds(Bonds, badIndex);
   }
   else {
   }
}

bool forceField::setAngles(vector<angle *> &Angles, string &method, int &badIndex) { 
   if (method == "GAFF") {
       if (!gaffTyper) gaffTyper = new gaff;
       return gaffTyper->setAngles(Angles, badIndex);
   }
   else if (method == "AMBER_03" ) {
       if (!amberTyper) amberTyper = new amber;
       return amberTyper->setAngles(Angles, badIndex);
   }
   else {
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
   }
}

bool forceField::setTorsions(vector<torsion *> &Torsions, string &method, int &badIndex) {
  if (method == "GAFF") {
     if (!gaffTyper) gaffTyper = new gaff;
     return gaffTyper->setTorsions(Torsions, badIndex);
   }
   else if (method == "AMBER_03" ) {
      if (!amberTyper) amberTyper = new amber;
      return amberTyper->setTorsions(Torsions, badIndex);
   }
   else {
   }
}


















































