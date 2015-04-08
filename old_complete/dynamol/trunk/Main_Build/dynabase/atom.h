/***************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   email:  john.furr@dynamol.com 
 ***************************************/
#ifndef DYNABASEATOM_H
#define DYNABASEATOM_H

//Dynabase Includes
#include "atomintstate.h"

//Standard Library Incudes
#include <vector>
#include <string>
using std::vector;
using std::string;

//BOOST INLCUDEs
#include <boost/shared_ptr.hpp>

/** \defgroup The Dynamol Base Library
*
*/   

/** \brief The Dynamol Base Library
*
*   \ingroup The Dynamol Base Library
*  The Dynamol base library contains basic low level funtionality.
*  It provides a very basic atom class which is maintained by the 
*  atomFlyWeightFactory class.  
*/
namespace dynabase {

class atomFlyWeightFactory;
/** \brief A very basic atom class
*
*  This dynabase::atom class provides a simple atom class
*  that is divided into a common set of intrinsic and extrinsic
*  states.  All of the accessor functions in this class should be
*  inline to minimize function call time as much as possible
*
*  @author John Furr
*/
class atom;
typedef boost::shared_ptr<dynabase::atom> atomPtr;
class atom {
friend class atomFlyWeightFactory;
public:
    atom(int num, string symbol, float x, float y, float z, int AN);

    ~atom();

   /** \brief Return the atomic mass
   *
   *  This function returns the atomic mass
   */
   inline float getMass()
   { return is->mass; }

   /** \brief return the vad der Walls radii
   *
   *  This function returns the van der Walls radii of the
   *  atom
   */
   inline float getRadii()
   { return is->radii; }

   /** \brief Return the atomic number
   *
   *  Function returns the atomic number
   */
   inline int getAtomicNum()
   { return is->AN; }

   /** \brief Return the atomic number
   *
   *  Like getAtomicNum but provided for convenience
   */
   inline int getAN()
   { return is->AN; }

   /** \brief Used to chage the atom type
   *
   *	Change the atom type.
   */
   void changeType(int AN, string &symbol);

   /** \brief Return the Name o the atom
   *
   *  this funtion returns the name of the atom
   *  The name is not the symbol
   */
   inline string getName()
   {  return is->Name; }

   /** \brief Return the atomic symbol
   *
   *  This function returns the atomic symbol 
   *  NOT the name
   */
   inline string getSymbol()
   {  return is->symbol; }

   /** \brief Change the atomic symbol
   *
   *   Use this function to change the atomic symbol  
   *   of the atom.  This is needed because of the way
   *   you handle PDB atom typing.
   */
   void setSymbol(string symbol); 

   /** \brief Return the Epsilon Value
   *
   *    This function returns the Molecular Mechanics
   *    epsilon value (well depth)
   */
   inline float getEpsilon()
   { return is->epsilon; }

   /** \brief Set the epsilon value
   *
   *    This function sets the approppriate epsilon value.
   *    It also updates checks to see if a new intrinsic state
   *    is needed
   */
   void setEpsilon(float epsilon);

   /** \brief Return the Sigma Value
   *
   *    This function returns the Molecular Mechanics
   *    sigma value (radii)
   */
   inline float getSigma()
   { return is->sigma; }

   /** \brief Set the sigma value
   *
   *    This function sets the approppriate sigma value.
   *    It also updates checks to see if a new intrinsic state
   *    is needed.   
   */
   void setSigma(float sigma);

   /** \brief Return the Molecular Mechanics Atom Type
   *
   *    This function returns the Molecular Mechanics
   *    force field atom type. 
   */
   inline string getFFType()
   { return is->ff_type; }

   /** \brief Set the Force Field Atom Type
   *
   *   This function is used to set the force field atom
   *   type.  It also checks to see if a new intrinsic state
   *   is needed
   */
   void setFFType(string ff_type);

   /** \brief Get the atom number
   *  
   *  This function returns the atom number
   *  In general this will corespond to the position
   *  the atom pointer is in the parents vector<atom *> container.
   */
   inline int getNum()
   { return num; }

   /** \brief Set the atom number
   *
   * Use this function to update the atoms number
   */
   inline void setNum(int Num)
   { num = Num; }

   /** \brief the atomic coods.  
   *
   *  Array size is 4 because many linear algebra operation just 
   *  work better on vectors of size 4
   */
  float fCoords[4];

  /** \brief Set the Atomic Charge
   *
   *  This variable sets the atomic charge 
   */
   inline void setCharge(float chg)
   { this->charge = chg; }

   /** \brief Return the atomic charge
    *
    *   Return the partial atomic charge
    */
    inline float getCharge() 
    { return charge; }

protected:
   /** \brief This is the intrinsic state of the atom
   *
   *  The intrinsic states of an atom are properties that
   *  do not change for a specific atom type.  In general
   *  the atom type is defined by the atomic number.  However
   *  it easy to imagine a case where force field types are used
   *  to determine various types.
   */
   //atomIntState *is;
   atomIntStatePtr is;


private:
   /** \brief A static atomFlyWeight Factory.
   *
   *  The reason it is static is because there should only ever
   *  be one constructed.
   */
   static atomFlyWeightFactory factory;

   /** \brief The atom number
   *
   *  In general this will corespond to the position
   *  the atom pointer is in the parents vector<atom *> container.
   */
   int num;

   /** \brief The partial Atomic Charge
   *
   *  This variable holds the partial atomic charge 
   */
   float charge;

};
};

#endif

