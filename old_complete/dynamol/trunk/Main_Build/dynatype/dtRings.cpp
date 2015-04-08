/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "dtRings.h"
#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include <iostream>
#include <iomanip>
#include <fstream>

namespace dt {
	
//Rings::Rings(molecule *mol)
Rings::Rings(molPtr mol)
{
   this->mol = mol;
   //Makes dtRings gor from smallest to largest
   sortRingSizes();
   setRingTypes();
   setAromaticity();
   setBondType();
   
   for (int i=0; i<mol->atoms.size(); i++) {
      atomPtr atm = mol->atoms[i]; 
   }
}

Rings::Rings() {};


Rings::~Rings()
{
}

void Rings::sortRingSizes() {
   vector<int> hold;
   
   for (int i=0; i<mol->unsortedRings.size(); i++) {
     int iSize = mol->unsortedRings[i].size();
     for (int j=i+1; j< mol->unsortedRings.size(); j++) {
        int jSize = mol->unsortedRings[j].size();
        if (iSize > jSize) {
          hold = mol->unsortedRings[i];
          mol->unsortedRings[i] = mol->unsortedRings[j];
          mol->unsortedRings[j] = hold;
        }
     }
   }
}

void Rings::setRingTypes() {
  for (int i=0; i<mol->unsortedRings.size(); i++) {
     int size = mol->unsortedRings[i].size();
     //exclude all dtRings size 9 or smaller
     if (size <= 9) {
        string sSize = "";
        if (size == 3) sSize = "RG3";
        else if (size == 4) sSize = "RG4";
        else if (size == 5) sSize = "RG5";
        else if (size == 6) sSize = "RG6";
        else if (size == 7) sSize = "RG7";
        else if (size == 8) sSize = "RG8";
        else if (size == 9) sSize = "RG9";
        for (int j=0; j<mol->unsortedRings[i].size(); j++) {
          //atom *atm = mol->atoms[mol->unsortedRings[i][j]];
          atomPtr atm = mol->atoms[mol->unsortedRings[i][j]];
          atm->atomProps.push_back(sSize);
        }
     }
  }
  for (int i=0; i<mol->atoms.size(); i++) {
    //atom *atm = mol->atoms[i];
    atomPtr atm = mol->atoms[i];
    if (atm->atomProps.size() == 0) atm->atomProps.push_back("NG");
  }
}

void Rings::setAromaticity() {
  ////////cout <<"Set Aromaticity"<<endl;
  //First we need to determine the total number of planar and C4 atoms in the dtRings
  for (int i=0; i<mol->unsortedRings.size(); i++) {
     int size = mol->unsortedRings[i].size();
     int planarCount = 0;
     int aliphaticCount = 0;  
     for (int j=0; j<mol->unsortedRings[i].size(); j++) {
          //atom *atm = mol->atoms[mol->unsortedRings[i][j]];
          atomPtr atm = mol->atoms[mol->unsortedRings[i][j]];
          if ( isAliphatic(atm) ) aliphaticCount++;
          else if ( isPlanar(atm) ) planarCount++;
     }
     
     if (aliphaticCount == size) typeAliphatic(mol->unsortedRings[i]);
     else if (planarCount == size) typePlanar(mol->unsortedRings[i]);
     else typeOther(mol->unsortedRings[i]);
  }
}

//bool Rings::isAliphatic(atom *atm) {
bool Rings::isAliphatic(atomPtr atm) {
  if (atm->getAN() == 6 && atm->atoms.size() == 4) 
     return true;
     
  return false;
}

//bool Rings::isPlanar(atom *atm) {
bool Rings::isPlanar(atomPtr atm) {
   if (atm->getAN() == 6 && atm->atoms.size() == 3) return true;
   else if (atm->getAN() == 7 && atm->atoms.size() == 2) return true;
   else if (atm->getAN() == 7 && atm->atoms.size() == 3) return true;
   else if (atm->getAN() == 7 && atm->atoms.size() == 4) return true;
   else if (atm->getAN() == 8 && atm->atoms.size() == 2) return true;
   else if (atm->getAN() == 15 && atm->atoms.size() == 2) return true;
   else if (atm->getAN() == 15 && atm->atoms.size() == 3) return true;
   else if (atm->getAN() == 16 && atm->atoms.size() == 2) return true;
   else return false;
}

void Rings::typeAliphatic(vector<int> &ring) {
  for (int i=0; i<ring.size(); i++) {
    //atom *atm = mol->atoms[ring[i]];
    atomPtr atm = mol->atoms[ring[i]];
    atm->atomProps.push_back("AR5");
  }
}

void Rings::typePlanar(vector<int> &ring) {
   int outside = 0;
   int pure = 0;
   for (int i=0; i<ring.size(); i++) {
     //atom *atm = mol->atoms[ring[i]];
     atomPtr atm = mol->atoms[ring[i]];
     if ( isPure(atm) ) pure++;
     if ( hasOutside(atm) ) outside++;
   }
   
   //Check for a pure aromatic ring
   if (pure == ring.size() && outside == 0) {
      for (int i=0; i<ring.size(); i++) {
        //atom *atm = mol->atoms[ring[i]];
        atomPtr atm = mol->atoms[ring[i]];
        atm->atomProps.push_back("AR1");
      }
   } else {
      for (int i=0; i<ring.size(); i++) {
         //atom *atm = mol->atoms[ring[i]];
         atomPtr atm = mol->atoms[ring[i]];
         if ( hasOutside(atm) ) atm->atomProps.push_back("AR3");
         else atm->atomProps.push_back("AR2");
      }
   }
}

//bool Rings::isPure(atom *atm) {
bool Rings::isPure(atomPtr atm) {
  if (atm->getAN() == 6 && atm->atoms.size() == 3) return true;
  else if (atm->getAN() == 7 && atm->atoms.size() == 2) return true;
  //Check for special nitrogen case;
  int tbo = 0;
  for (int i=0; i<atm->bonds.size(); i++) {
    bondPtr bd = atm->bonds[i].lock();
    tbo += bd->order;
    //tbo += atm->bonds[i]->order;
  }
  if (tbo == 4 && atm->getAN() == 7 && atm->atoms.size() == 3) return true;
  return false;
}

//bool Rings::hasOutside(atom *atm) {
bool Rings::hasOutside(atomPtr atm) {
   for (int i=0; i<atm->bonds.size(); i++) {
      //bond *bd = atm->bonds[i];
      bondPtr bd = atm->bonds[i].lock();
      //atom *from = bd->from;
      atomPtr from = bd->from.lock();
      //atom *to = bd->to;
      atomPtr to = bd->to.lock();
      if (from == atm) {
         if ( bd->order == 2 && to->atomProps[0] == "NG" ) return true;
      }
      else if (to == atm) {
         if ( bd->order == 2 && from->atomProps[0] == "NG" ) return true;
      } else {
         ////////cout <<"Problemo! "<< atm->num << setw(12) << from->num<< setw(12) << to->num<<endl;
      }
   }
   
   return false;
}

void Rings::typeOther(vector<int> &ring) {
for (int i=0; i<ring.size(); i++) {
    //atom *atm = mol->atoms[ring[i]];
    atomPtr atm = mol->atoms[ring[i]];
    atm->atomProps.push_back("AR4");
  }
}

void Rings::setBondType() {
   for (int i=0; i<mol->atoms.size(); i++) {
      //atom *atm = mol->atoms[i];
      atomPtr atm = mol->atoms[i];
      for (int j=0; j<atm->bonds.size(); j++) {
         //bond *bd = atm->bonds[j];
         bondPtr bd = atm->bonds[j].lock();
         if (bd->order == 2) atm->atomProps.push_back("db");
         else if (bd->order == 1) atm->atomProps.push_back("sb");
      }
   }
}

bool Rings::isAromaticBond(bond *bd) {
   //atom *atm1 = bd->from;
   //atom *atm2 = bd->to;
   atomPtr atm1 = bd->from.lock();
   atomPtr atm2 = bd->to.lock();   

   int count = 0;
   for (int i=0; i<atm1->atomProps.size() ; i++) {
      if (atm1->atomProps[i] == "AR1") {count++; break;} 
      else if (atm1->atomProps[i] == "AR2") {count++; break;}
      else if (atm1->atomProps[i] == "AR3") {count++; break;}
   }
   
   for (int i=0; i<atm2->atomProps.size() ; i++) {
      if (atm2->atomProps[i] == "AR1") {count++; break;} 
      else if (atm2->atomProps[i] == "AR2") {count++; break;}
      else if (atm2->atomProps[i] == "AR3") {count++; break;}
   }
   
   if (count == 2) return true;
   
   return false;
}

//int Rings::aromaticRingCount(molecule *mol) {
int Rings::aromaticRingCount(molPtr mol) {
   
   int count = 0;
  
   for (int i=0; i<mol->sortedRings.size(); i++) {
      int e = piElectronCount(mol, mol->sortedRings[i]);
      if (e == 6 || e == 10 || e == 18) {
         count++;
      }
   }
   return count;
}

//int Rings::piElectronCount(molecule *mol, vector<int> ring) 
int Rings::piElectronCount(molPtr mol, vector<int> ring)
{
   int pi = 0;
   for (int i=0; i<ring.size(); i++) {
      // atom *atm = mol->atoms[ring[i]];
      atomPtr atm = mol->atoms[ring[i]];
	   int an = atm->getAN();
	   int order = getTotalBondOrder(mol, atm);
	   int bonds = atm->atoms.size();
	   int tmp = order-bonds;
	   if (an == 6) {//It is a carbon
         if (tmp == 0) pi+= 0;
	      if (tmp == 1) pi+= 1;
	   } else
	   if (an == 7) { //it is a nitrogen
	      if (order == 3) {
              
	      if (tmp == 0) pi+=2;
	      if (tmp == 1) {
            pi+=1;
         }
	   }
	} else 
	if (an == 8) { //It is an oxygen
	  if (order == 2 && tmp == 0) pi+= 2;
	} else
	if (an == 16) { //It is a sulfer
	   if (order == 2 && tmp == 0) pi+= 2;
	}
	
	//Now lets do exocyclic check
	for (int i=0; i < atm->atoms.size(); i++) {
	  //atom *tmp = atm->atoms[i];
     atomPtr tmp = atm->atoms[i].lock();
	  //bond *bd = mol->getBond(atm, tmp);
     bondPtr bd = mol->getBond(atm, tmp);
	  if (bd->order == 2) {
	    int an = tmp->getAN();
	    if (an == 8 || an == 7 || an == 16) {
	      bool inRing = false;
	      for (int j=0; j<ring.size(); j++) {
            if (tmp->getNum()-1 == ring[j]) {
		  inRing = true;
		  break;
		}
	      }
	      if (!inRing)
	         pi -= 1;
	    }
	  }	  
	}
     }
     
  return pi;
}

//int Rings::getTotalBondOrder(molecule *mol, atom *atm) {
//int Rings::getTotalBondOrder(molecule *mol, atomPtr atm) { 
int Rings::getTotalBondOrder(molPtr mol, atomPtr atm) {
   int totalBondOrder = 0;
   for (int i=0; i<atm->atoms.size(); i++) {
      //bond *bd = mol->getBond(atm, atm->atoms[i].lock());
      bondPtr bd = mol->getBond(atm, atm->atoms[i].lock());
      if (bd != NULL) { 
      	totalBondOrder += bd->order;
      } 
   }
   return totalBondOrder;
}

} //end namespace dt

























