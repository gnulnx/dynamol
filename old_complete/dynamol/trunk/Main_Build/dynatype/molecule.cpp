/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   **********************************************************************/
//Dynatype includes
#include "molecule.h"
#include "bond.h"
#include "atom.h"

//Dynamol Base Library Includes
#include "../dynabase/atom.h"

//Standard Library Includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using std::sort;
using std::setw;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;


namespace dt {

molecule::molecule()
{
   chargeType = "none";
   ffType = "none";
}


molecule::~molecule()
{
}

void molecule::setName(string name) 
{ this->name = name; }

/** This function has no check to for duplicate atoms...it is thus very fast 
  Make sure you only use trusted sdf or sdfx files 
*/
atomPtr molecule::addAtom(int num, string sym, double x, double y, double z, int atomicNum) {
  atomPtr at( new atom(num, sym, x, y, z, atomicNum) );
  atoms.push_back(at);
  return at;
}

atomPtr molecule::addAtom(dynabase::atomPtr atm) {
   atomPtr at( new atom(atm) );
   atoms.push_back(at);
   return at;
}

bondPtr molecule::addBond(int num, int from, int to, int order) {
  atomPtr hold1;
  atomPtr hold2;

  hold1 = atoms[from-1];
  hold2 = atoms[to-1];
  hold1->addAtom(hold2);
  hold2->addAtom(hold1);
  bondPtr bd( new bond(num, hold1, hold2, order) );
  hold1->bonds.push_back(bd);
  hold2->bonds.push_back(bd);
  bonds.push_back(bd);
  return bd;
}

bool molecule::addRing(vector<int> &R) {
   vector<int> tmpR = R;
   sort(tmpR.begin(), tmpR.end());
   for (int i=0; i<sortedRings.size(); i++)
      if (sortedRings[i] == tmpR) 
         return false;

   unsortedRings.push_back(R);
   sortedRings.push_back(tmpR);
   return true;
}

bondPtr molecule::getBond(atomPtr atm1, atomPtr atm2) {
   bondPtr blank;
   for (int i=0; i<bonds.size(); i++) {
      if (bonds[i]->from.lock() == atm1 && bonds[i]->to.lock() == atm2) 
         return bonds[i];
      if (bonds[i]->to.lock() == atm1 && bonds[i]->from.lock() == atm2) 
         return bonds[i];
   }
   return blank;
}

float molecule::molWeight() {
   float w = 0;
   for (int i=0; i<atoms.size(); i++) {
      w += atoms[i]->getMass();
   }
   return w;
}

};






