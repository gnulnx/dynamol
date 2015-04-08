/***************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   email:  john.furr@dynamol.com 
 ***************************************/
#ifndef DYNABASEATOMINTSTATE_H
#define DYNABASEATOMINTSTATE_H

//C++ Standard Library Include Files
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dynabase {

/** \brief Intrinsic Atomic States Variables
*  
*  The intrinsic state of an atom is the state that is shared
*  among atoms of the same type.  The basic idea to to provde an
*  effecient method of storing and accessing the atom properties.
*  Some types of intrinsic state are totally static.  That is they never
*  change.  Othes types of intrinsic state varables are Dynamic.  Dynamic
*  state variables should howver sill be limited to very basic sets of
*  information such as molecular mechanics force field atom types and non
*  bond parameters.   You should strive to keep them as few as possible.
*  Since all Dynamic state variables have to be added to the operator== 
*  function the potential arrises to hurt performance.  Note as it stands
*  right now Dynamol is much more memory efficient than it was before and
*  It is able to read in molecules much faster.
*
*  @author John Furr
*/
class atomIntState;
typedef boost::shared_ptr<dynabase::atomIntState> atomIntStatePtr;

class atomIntState {
friend class atomFlyWeightFactory;
friend class atom;
public:
   atomIntState() { numRefObjects = 0;}
   ~atomIntState() {}

//protected:

   /** \brief Count of atoms using this state
   *
   *  This keeps a count of the atoms using this particular
   *  state. When it is zero you may safely delete it.
   *  This number is incremented by atomFlyWieght Factory
   *  However you will have to decrement it in the atom classes...
   *  ....Nah I don't like this...not very encapsulated at all.
   */
   int numRefObjects;

   /** \brief Overload boolean equals operator
   *
   *  This function is responsible for determining
   *  if the atomIntState has been used before.
   *  Is is only used by the atomFlyWeightClass.
   *  <pre>
   *  Any new variables that you want to use as a means of
   *  creating and managing new intrinsic atom states should
   *  be taked care of in this function.
   *  </pre> 
   */
   inline bool operator==(const atomIntState &state) {
      if (AN != state.AN)
         return false;
      if (symbol != state.symbol)
         return false;
      if (ff_type != state.ff_type)
	 return false;
      if (sigma != state.sigma)
         return false;
      if (epsilon != state.epsilon)
         return false;

      return true;
   }

   /** \brief Atomic Number
   *
   *  This variable holds the atomic number of the atom
   */;
   int AN;

   /** \brief The Atomic Mass
   *
   *  This variable holds the atomic mass
   */
   float mass;

   /** \brief The van der Walls Radii
   *
   *  This variable holds the van der Walls Radii
   */
   float radii;

   /** \brief The Name of the atom
   *
   *  The name of the atom.  Not the same as
   *  the atomic symbol
   */
   string Name;

//THIS SECTION STARS DYNAMIC INTRINSIC VARIABLES
   /** \brief The Atomic Symbol
   *
   *  This is the atomic symbol
   *  <pre>
   *  examples:
   *  Carbon = C
   *  Nitrogen = N
   *  Oxygen = O
   *  etc...
   *  </pre>
   */
   string symbol;

   /** \brief The Molecular Mechanics Forcefield Type
   *
   *  This is the molecular mechanics force field type
   */
   string ff_type;

   /** \brief The Molecular Mechanics Atomic Radius
   *
   *  This is forcefield sigma value in the Lennard Jones
   *  equation
   */
   float sigma;

   /** \brief The Molecular Mechanics Well Depth
   *
   *  This is the foce field epsilon value from the Lennard Jones
   *  equation
   */
   float epsilon;

};

}

#endif

