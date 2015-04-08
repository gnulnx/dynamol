/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef DYNACOMPNONBOND_H
#define DYNACOMPNONBOND_H

namespace dynacomp {
class atom;
/** \brief The Molecular Mechanis Non-Bonded Atoms
*
*  This class is used to hold a nonBonded pair of atoms.
*  All modern molecular mechanis forcefields include a non bonded
*  term.  
*
*  @author jfurr
*/
class nonBond
{
public:
   nonBond(atom *atm1, atom *atm2, bool isTorsion,
	   double sigma, double epsilon, double charge);
   ~nonBond();
   
   /** \brief The Non-Bonded Assignment Operator */
   nonBond &operator=(const nonBond &nb);
   atom *atm1, *atm2;
    
   /** this is used for non bonds that are also torsions */
   //read older amber papers && OPLSAA papers...scale facte == 1/1.2;
   float scaleFactor;
};

};// End Namespace
#endif





































