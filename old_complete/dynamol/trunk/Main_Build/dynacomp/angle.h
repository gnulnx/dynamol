/*****************************************
 *   Copyright (C) 2004 by Dynamol       *
 *   email:  john.furr@dynamol.com       *
 *   *************************************/
#ifndef DYNACOMPANGLE_H
#define DYNACOMPANGLE_H

namespace dynacomp {
class atom;
/** \brief A Molecular Mechanis/Dynamics Angle class
*
*  Most (all) Modern Molecular Mechanics Force Fields have an angle term
*  This class provides the necassary equilibrium angles and force constants
*  that are used in these calculations
@author jfurr
*/
class angle
{
public:
    angle(atom *front, atom *mid, atom *back);
    ~angle();
    
   /** \brief The Degree of the Angle
   *
   *  This function returns the angle in Degrees
   */
   float degree();  
protected:
   /** \brief The Angle assignment operator
   *
   *  This is the angle assignment operator
   */
   angle &operator=(const angle &ang);
public:
    atom *front, *mid, *back;
    float refAngle;
    float actualAngle;
    float K;
    float stepSize;
    float prevEnergy;
};

}//End Namespace
#endif





































