/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com      
 ***************************************************************************/
#ifndef DTATOM_H
#define DTATOM_H

//Standard Library Includes
#include <string>
#include <vector>
using std::string;
using std::vector;

//Dynamol Base Library Includes
#include "../dynabase/atom.h"

//BOOST Includes
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>


//class dynabase::atom;

namespace dt {

class atom;
typedef boost::shared_ptr<dt::atom> atomPtr;
typedef boost::weak_ptr<dt::atom> atomWPtr;

class bond;
typedef boost::shared_ptr<dt::bond> bondPtr;
typedef boost::weak_ptr<dt::bond> bondWPtr;

class atom {
friend class molecule;
friend class bond;
public:
    atom();
    atom(int num, string sym, float x, float y, float z, int atomicNum);

    atom(dynabase::atomPtr atm);
	
	inline boost::shared_ptr< dynabase::atom > getBase()
	{ return _base; }

    //bool addAtom(atom *at);
    bool addAtom(atomWPtr at);

    ~atom();
    
    /** This is the atom array...er dequeu */
   //vector<atom *> atoms;
   vector<atomWPtr> atoms;
   
   /** This is the bond array...er deque */
   //vector<bond *> bonds;
   vector<bondWPtr> bonds;
   
   /** These are the coords */
   //vector<float> Coords;
   float *Coords;

public:   
   /** This will hold the forcefield atom type */
   string type;
   
   /* Various types that are used in the sdfx file */
   string fragName;
   string chainName;
   string ribType;
   
   vector<float> pathScores;
   
   /* This is the atomic dtRings the should be stored with 0 as first atom */
   vector< vector<int> > dtRings;
     
  /** This vector will contain various atom properties
      RG1-RG9    Ring size
      NG         non-ring atom
      AR1-AR5    Aromatic property...see "ATOMTYPE_GFF.DEF"
      SB         Single Bond
      DB         Double Bond
      TB         Triple bond
      AB         Aromatic Bond
      DL         delocalized bond ( 9 in AM1-BCC)
      sb         single bond, including aromatic single, delocalize singbond (9 in AM1-BCC)
      db         Double Bond, including aromatic double bond
      tb         Trible bond
  */      
  vector<string> atomProps;
  
  /** This will be true if the Group Type has been changed...false otherwise */
  bool changed;
  
  /** This holds the partial dtCharge of the atom */
  float charge;
 
  /** Parity bit fro mSD Files */
  int parity; 
//BEGIN WRAPPER SECTION
private:
   dynabase::atomPtr _base;
public:
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
//END WRAPPER SECTION   
};
}
#endif



























