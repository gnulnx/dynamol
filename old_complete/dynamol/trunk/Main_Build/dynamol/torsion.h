/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef TORSION_H
#define TORSION_H



class atom;
/**
@author jfurr
*/
class torsion
{
public:
   torsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4);
   ~torsion();
protected:
   torsion &operator=(const torsion &tor);
public:

    atom *atm1, *atm2, *atm3, *atm4;
    
    float V, gamma;
    int n;
    
    float degree();

   bool improper;
    
    bool inTorsion(atom *a1, atom *a2);
};

#endif





































