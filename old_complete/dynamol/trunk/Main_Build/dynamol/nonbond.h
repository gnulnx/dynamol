/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef NONBOND_H
#define NONBOND_H

class atom;
/**
@author jfurr
*/
class nonBond
{
public:
   nonBond(atom *atm1, atom *atm2, bool isTorsion,
	   double sigma, double epsilon, double charge);
   ~nonBond();
   nonBond &operator=(const nonBond &nb);
   atom *atm1, *atm2;
    
   /** this is used for non bonds that are also torsions */
   //read older amber papers && OPLSAA papers...scale facte == 1/1.2;
   float scaleFactor;
};

#endif





































