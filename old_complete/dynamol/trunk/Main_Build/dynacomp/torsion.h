/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef DYNACOMPTORSION_H
#define DYNACOMPTORSION_H

namespace dynacomp {
class atom;
/** \brief A Molecular Mechanics Torsion
*
*  Most (if not all) molecular mechanis/dynamics simulators require the definition of
*  molecular torsions.  This class acts as as a basic container to store force constants, and phase
*  angles that are specific to molecular mechanics torsion angles
*
*  @author jfurr
*/
class torsion
{
public:
   torsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4);
   ~torsion();
   
    /** \brief Return the torsion angle
   *
   *  This function returns the torsion angle in degrees
   */ 
   float degree();
   
    /** \brief Return true if both atoms are in the torsion
   *
   *  This function check to see if the two atoms are in the torsion.
   *  If they are it returns true.  If not it returns false
   */
   bool inTorsion(atom *a1, atom *a2);
protected:
   /** \brief The torsion assignment operator */
   torsion &operator=(const torsion &tor);
public:

   /** \brief the atoms in the torsion */
   atom *atm1, *atm2, *atm3, *atm4;
    
   /** Torsion parameters */
   float V, gamma;
   int n;
   
   /** \brief True if improper torsion */
   bool improper;
};

};  //End Namespace
#endif





































