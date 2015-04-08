/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "nonbond.h"
#include "atom.h"

nonBond::nonBond(atom *atm1, atom *atm2,  bool isTorsion,
		 double sigma, double epsilon, double charge)
{
   this->atm1 = atm1;
   this->atm2 = atm2;

   //if (isTorsion) scaleFactor = 1.0/2.0;
   if (isTorsion) scaleFactor = 1.0/1.2;
   else scaleFactor = 1.0;
}


nonBond::~nonBond()
{
  atm1 = atm2 = NULL;
}

nonBond &nonBond::operator=(const nonBond &nb) {
   if (this == &nb) return *this;
}








































