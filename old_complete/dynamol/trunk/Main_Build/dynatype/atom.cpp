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

//class dynabase::atom;

namespace dt 
{

atom::atom()
{
  type = "none";
}
atom::atom(int num, string sym, float x, float y, float z, int atomicNum)
{
   _base.reset( new dynabase::atom(num, sym, x, y, z, atomicNum) ); 
 
   Coords = _base->fCoords;

  type = "none";
  
  charge = 0;
  changed = false;
}

atom::atom(dynabase::atomPtr atm)
{
   _base = atm;
   Coords = _base->fCoords;
   type = "none";
   charge = 0;
   changed = false;
}

atom::~atom()
{
}

bool atom::addAtom(atomWPtr at) {
  atoms.push_back(at);
  return true;
}

}

























