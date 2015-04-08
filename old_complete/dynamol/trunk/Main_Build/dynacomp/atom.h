/***************************************
 *   Copyright (C) 2004 by Dynamol Inc.*
 *   john.furr@dynamol.com             *
 ***************************************/
#ifndef DYNACOMPATOM_H
#define DYNACOMPATOM_H

//Dynbase Includes
#include "../dynabase/atom.h"

//BOOST INCLUDES
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <string>
#include <vector>
using namespace std;

namespace dynacomp {

class molecule;
class bond;

class torsion;
typedef boost::shared_ptr<dynacomp::torsion> torWPtr;

class angle;
typedef boost::weak_ptr<dynacomp::angle> angleWPtr;

class atom;
typedef boost::shared_ptr<dynacomp::atom> atomPtr;

class atom {
friend class molecule;
friend class bond;
public:
   atom(int num, string sym, float x, float y, float z, int atomicNum);
   atom(dynabase::atomPtr atm);

   float &operator[](int index)
   { if (index < 3 && fCoords) return fCoords[index]; }

   bool addAtom(atom *at);

   ~atom();

    /** This is the atom array...er dequeu */
   vector<atom *> atoms;

   /** \brief Return the number of atoms
   *
   *   This is the number of atoms bonded to atm
   */
   inline int numAtoms()
   { return atoms.size(); }

   atom *getAtom(int index);

   /** This is the bond array...er deque */
   vector<bond *> bonds;

   /** \brief Return the number of bonds
   *
   *   This is the number of bonds the atom is connected to
   */
   inline int numBonds()
   { return bonds.size(); }

   /** These are the coords */
   float *fCoords;
   float *getCoords()
   { return fCoords; }

   vector< vector<int> > rings;
   
   /** This is the formal charge of the atom */
   int formalCharge;

   /** This is the parity bit from sd files */
   int parity;

  
   //AM1-BCC Specific stuff
   /** \brief Bond Charge Correction variable
   *
   *  This variable is used in the AM1-BCC charge routines
   */
   string bcc;
   
   /** \brief Atom valence.  
   *
   *  Used in am1_bcc stuff
   */
   int valence;
   
   /** \brief Aromiticity of the atom 
   */
   bool aromatic;
  
   /** \brief The Atomic Forces
   *
   *   This is the force array used by the energy classes
   */
   double forces[3];

   /** \brief Freeze Atom
   *
   *   When set to true the atom will be frozen
   *   during energy calculations
   */
   bool frozen;

   inline void zeroForces()
   { forces[0] = forces[1] = forces[2] = 0.0; }
 
   bool visited;
   bool inRing;
   
   //void atom::setType(string atomType);
   void setType(string atomType);
   string atomType;

   int numOfHeavyAtoms();
   int numOfHydrogens();
   int totalBondOrder();
   int numOfOxygen();
   
   
//END AM1-BCC stuff

   void setParent(molecule *mol);
   
   inline molecule *getParent()
   { return parent; }

   molecule *parent;

   vector<atom *> bondVisit;

   string fragName;
private:
   /** \brief Dynamol Base Atom Smart Pointer
   *
   *   This variable holds a smart pointer to the dynamol
   *   base atom.  The dynamol base atom contains common
   *   intrinsic and extrinsic states that are common 
   *   across all atom types
   */
   dynabase::atomPtr _base;
public:
   /** \brief Return a smart pointer to the dynabase::atom
   *
   *   This function returns the dynabase::atom smart pointer
   */
   inline dynabase::atomPtr getBase()
   { return _base; }

   inline int getAN()
   { return _base->getAN(); }

   inline int getAtomicNum()
   { return _base->getAN(); }

   inline void setFFType(string ff_type)
   { _base->setFFType(ff_type); }

   inline string getFFType()
   { return _base->getFFType(); }

   inline string getSymbol()
   { return _base->getSymbol(); };

   inline void setSymbol(string symbol)
   { _base->setSymbol(symbol); }

   inline float getSigma()
   { return _base->getSigma(); }

   inline void setSigma(float sigma)
   { _base->setSigma(sigma); }

   inline float getEpsilon()
   { return _base->getEpsilon(); }

   inline void setEpsilon(float sigma)
   { _base->setEpsilon(sigma); }
   
   inline float getRadii()
   { return _base->getRadii(); }

   inline float getMass()
   { return _base->getMass(); }

   inline int getNum()
   { return _base->getNum(); }

   inline void setNum(int Num)
   { _base->setNum(Num); }

   inline void setCharge(float chg)
   { _base->setCharge(chg); }

   inline float getCharge()
   { return _base->getCharge(); }

   vector<torWPtr> torsions;
   vector<angleWPtr> angles;
};
}
#endif






