/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "atom.h"
#include "bond.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;
namespace dynacomp 
{

atom::atom(dynabase::atomPtr basePtr) {
   //_base.reset( atm );
   _base = basePtr;
   fCoords = _base->fCoords;

   formalCharge = 0;
   //charge = 0.0;
   parent = NULL;
   frozen = false;
   fragName = "";
}
atom::atom(int num, string sym, float x, float y, float z, int atomicNum)
{

   _base.reset( new dynabase::atom(num, sym, x, y, z, atomicNum) );
   fCoords = _base->fCoords;

   formalCharge = 0;
   //charge = 0.0;
   frozen = false;
   fragName = "";
}


atom::~atom()
{
}

bool  atom::addAtom(atom *at) {
  atoms.push_back(at);
  return true;
}

atom *atom::getAtom(int index) {
   if (index < atoms.size())
      return atoms[index];
   else {
      cout <<"atom::getAtom index out of range"<<endl;
      return NULL;
   }
}

void atom::setType(string atomType) 
{ this->atomType = atomType; }

int atom::numOfHeavyAtoms() {
   int num = 0;
   for (int i=0; i<atoms.size(); i++) 
      if (atoms[i]->getAN() > 1) 
         num++;
   return num;
}

int atom::numOfHydrogens() {
   int num = 0;
   for (int i=0; i<atoms.size(); i++) 
      if (atoms[i]->getAN() == 1) 
         num++;
   return num;
}

int atom::totalBondOrder() {
   int num = 0;
   for (int i=0; i<bonds.size(); i++) 
      num += bonds[i]->getOrder();
   return num;
}

int atom::numOfOxygen() {
   int num = 0;
   for (int i=0; i<atoms.size(); i++) 
      if (atoms[i]->getAN() == 8) 
         num++;
   return num;
}

void atom::setParent(molecule *mol) {
   this->parent = mol;
}

}//END DYNACOMP NAMESPACE

























