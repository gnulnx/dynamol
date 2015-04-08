/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "scriptbond.h"
#include "scriptatom.h"

#include "atom.h"
#include "bond.h"
#include "linAlg.h"

scriptbond::scriptbond(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
   bd = NULL;
}


scriptbond::~scriptbond()
{
}

void scriptbond::setBond(bond *bd)	{this->bd = bd;}

void scriptbond::setAtoms(scriptatom *from, scriptatom *to) {
    this->from = from;
    from->atoms.push_back(to);

    this->to = to;
    to->atoms.push_back(from);
}
  
int scriptbond::order()	{
   if (bd != NULL)
      return bd->order;
   else 
      return 0;
}

double scriptbond::length() {
   float *cd1 = bd->fromAtom()->fCoords;
   float *cd2 = bd->toAtom()->fCoords;
   
   return distance(cd1, cd2);
}

bond *scriptbond::getBond() {
   return bd;
}

scriptatom *scriptbond::fromAtom() { 
   return to;
}

scriptatom *scriptbond::toAtom()   { 
   return to;
}




































