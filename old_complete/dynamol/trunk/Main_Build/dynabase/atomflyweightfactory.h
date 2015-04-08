/***************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   email:  john.furr@dynamol.com 
 ***************************************/
#ifndef DYNABASEATOMFLYWEIGHTFACTORY_H
#define DYNABASEATOMFLYWEIGHTFACTORY_H

//Standard Library Includes
#include <set>
#include <vector>
#include <map>
#include <string>
using std::set;
using std::vector;
using std::map;
using std::string;

#include "atomintstate.h"


namespace dynabase {
struct atomIntState;
class atom;
/** \brief The Atom Fly Weight Factory
*
*  All atoms contain a set of basic information which
*  Is specific to an individual atom.  For example all
*  Nitrogen atoms have an atomic number of 7 and a mass of 14.
*  In order to conserve space all of the intrinsic states of 
*  a nitrogen atom need only be created once.  Thus the 
*  atomFlyWeightFactory is responsible for creating and maintaining
*  the basic atom intrinisc state variables.  This class is a private
*  static member of class dynabase::atom.  If you would like to add new
*  intrinsic state information to the atom class you will need to do 
*  a couple of things.
*  <pre><ul>
*  <li>Add new state variables to atomIntState</li>
*  <li>Provide assesor functons in class atom</li>
*  </ul><pre>
*
*  If you add an new dynamic intrinsic state then you will need to
*  add it to the operator== function in atomIntState.
*
*  @author John Furr
*/
class atomFlyWeightFactory{
public:
   atomFlyWeightFactory();

   ~atomFlyWeightFactory();

   /** \brief Get the intrinsic state.
   *
   *  Returns the inrinsic state of the atom with
   *  Atomic number <i>n</i>
   */
   void setIntState( atom *atm, int AN, 
                             string symbol="*",
                             string ff_type = "*",
                             float sigma = 0.0,
                             float epsilon = 0.0);

private:
   /** \brief Return the name of the atom
   *
   *   This function returns the name of the atom.
   *   It is a work in progress.  If the current name is not found
   *   it will return "None" 
   */
   string getName(int atomicNum);

   /** \brief Return the van der Walls radii
   *
   *   This function returns the default van der walls radii
   *   for the atom with atomic num <i> atomicNum </i>
   */
   float getvdwRadii(int atomicNun);

   /** \brief Return the atomic Mass
   *
   *   This function returns the atomic weight of the
   *   atom with atomic num <i>atomicNum</i>
   */
   float getAtomicMass(int atomicNum);

   /** \brief Storage of pre defind states
   *
   *  This is an efficient way of determining
   *  wether or not the intrinsic state has
   *  been defined before
   */
   //vector<atomIntState *> preDefinedStates;
   vector<atomIntStatePtr> preDefinedStates;
};

}

#endif

