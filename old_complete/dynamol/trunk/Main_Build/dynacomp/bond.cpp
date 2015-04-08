/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "bond.h"
#include "atom.h"

namespace dynacomp {

bond::bond(int num, atom *from, atom *to,  int order) {
   this->from = from;
   this->to = to;
   this->num = num;
   this->order = order;
}

bond::~bond()
{
}

};




























