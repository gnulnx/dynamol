/***************************************************************************
                          atom.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef ATOM_H
#define ATOM_H

/** This is included so that each atom can have a pointer to the molecule it is a part of.
*/
#include <qlistview.h>     

#include <string>
#include <list>
#include <vector>

//This is only here for error messages
#include <iostream>

//Dynbase Includes
#include "../dynabase/atom.h"
//using dynabase::atom;

//BOOST INCLUDES
#include <boost/shared_ptr.hpp>

#include "enumTypes.h"
#include "object.h"

using namespace std;

class molListViewItem;
//class bond;
//class molecule;

class atom : public Object {//, public dynabase::ATOM {
//  friend class molecule;
  friend class chain;
  friend class protein;
  friend class fragment;
  friend class molView;
  friend class bond;
  friend class fragFactory;
  friend class atomTyper;
  friend class forceField;
  friend class molDB;
  friend class molListView;
  friend class angle;
  friend class torsion;
  friend class nonBond;
  friend class dynamics;
  friend class pickEngine;
public:
   static int atomsCreated;
   static int atomsDeleted;
   /**   Constructer gives atom basic initialization params.  
   *  You need to add a function which allows the type of 
   *  atom...something like:  
   *  atomType(int type, float radii, float sigma, etc...);
  */ 
  atom(int num, string symbol, float x, float y, float z, int atomicNum);
  atom(dynabase::atomPtr atm);
  virtual ~atom();

   /** \brief Return the _base ATOM class
   *
   *  Mainly used for internal purposes
   */
  //dynabase::atom *getBase();
  inline boost::shared_ptr< dynabase::atom > getBase()
  { return _base; }

protected:
  atom &operator=(const atom &atm);

//WRAPPER SECTION
private:
   //dynabase::atom *_base;
   boost::shared_ptr< dynabase::atom > _base;
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

  void changeType(string sym, int AN);
  // { _base->changeType(AN, sym); }
  
  inline void setCharge(float chg)
  { _base->setCharge(chg); }

  inline float getCharge()
  { return _base->getCharge(); }
//END WRAPPERSECTION
public:

  /** This function is used to change the atoms type */
//  void changeType(string sym, int AN);
  
  /** This function returns the atom symbol.  Usually 1 || 2 letters
  */
  string getSym();

  
  /** This is special for the atom class...others use the virtual from object */
  virtual void setParent(Object *parent);

  /** This sets the charge of the atom */
//  void  setCharge(float charge);
  
  /**   This function returns a vector of type double {vector<double>} containing the
        x, y, & z coords in the indices 0, 1, 2 respectively
  */
  void getCoords(vector<float> &coords);
  
  /**   This function returns a vector of int containing the atom numbers of the atoms to
        which it is bonded to
  */
  vector<int> bondedAtomNum();

  /** This funciton types the atoms int he molecule based on the TYPE parameter
  */
  void typeAtoms(PARAMETER par);

  /** This function returns the render type
  */
  ATOMRENDER getRenderType();

  /** This function sets the render type
  */
  void setRenderType(ATOMRENDER renderType);

  /** Sets the color back to the default type
  */
  void colorByElement();

  /** Toggle atom display.  TRUE || FALSE
  */
  void atomDisplay(bool display);

  /**   Return true if atom set to display, || false if hidden
  */
  bool getAtomDisplay();

  /** Returns 1 if atoms is hidden, && 0 if it is shown
  */
//  int hidden();

  /** hides/shows the atom..  1 to hide && 0 to show
  */
  //void              setHiddenState(int hide);

  /** This method returns the number of other atoms the current atom is bonded to.
  */
  int numOfConnections();

  /** This method pushes back a connected atom
  */
  bool addAtom(atom *);

  /** Sets the temp also known as the B-Factor
  */
  void setTemp(float temp);

  /** Returns the temp || B-factor
  */
  float getTemp();

  /** Set The atoms coords
  */
  void setCoords(float x, float y, float z);

  /** Sets the real state
  */
  //void setRealState(bool tf);

  /** Gets the real State;
  */
  //bool getRealState();

  /** Sets the selection state for the atom.  True is seleced, False is deselected
  */
  void setSelected(bool setState);
  
  /** This is derived from class object...you must keep it. */
  void setSelected(bool setState, bool children);

  /** Set molecule for which the atom is a part of
  */
  //void setMol(molecule *mol);

  /** Returns the molecule pointer.  This is used whenever you neeed to gather information
      about the molecule that the atom is atached to
  */
  //molecule        *getMol();

  /** Sets the molistViewAtomIten pointer
  */
  //void setItem(molListViewItem *item);

  /** returns a pointer to the molListViewAtom Item || null if the value is not set
  */
  //molListViewItem *getItem();

  /** Sets the atom color based on type
  */
  void  defaultColor();

  /** Returns 10 if the object is an atom
  */
  virtual int  rtti(); //reutns 10

  /** Sets the forcefield string type */
  //void setFFType(string ff_type);

  /** Checks to see if another atom is bonded to this one */
  bool isBondedTo(atom *atm);

  //######################## FLOATING PNT CONVERSION SECTION ##########################//
  float *get_fCoords();
  float *fCoords;

  //double  *get_dCoords();

  //float charge;
  float formalCharge;
  int valence;

  string atomType;
  string getAtomType();

  void setType(string type);

  int numOfHeavyAtoms();
  int numOfHydrogens();
  int numOfOxygen();

  /** This function will return the count count of bond Order for all the bonds to this atom
  */
  int totalBondOrder();
  
  /** This function simply sets the forces to 0
  */
  void zeroForces();
  
 public:
     vector<float> COLOR;//[4], 
	  vector<float> tmpColor;//[4];
     
     double forces[3];
     
     QString label;
 // ########################## END SECTION ###################################3
     
public:
  vector<atom *> atoms; 
  vector<angle *> angles;
  vector<torsion *> torsions;
  vector<bond *> bonds; 

  int color, currColor;

  float temp;
  bool aromatic;

  /** This variable is set if the atom is in a ring */
  bool inRing;
  string bcc;
  ATOMRENDER  renderType;
  
  /** This variable is used to fix/unfix atom positions in silmulations. 
  */
  bool frozen;  
  
  /** Forfield parameters 
  */
  //float sigma;
  //float epsilon;
  //float rmin;

  /** This variable is used to determine if the atom is a backbone, sidechain || non-protein atom */
  PROT_TYPE protType;

  /** Used to determine if that atom is displayed || not.  Not for determining if atom is really there.
      This statement mainly derives from the fact I was having issues with pdb fragment definitions not always being the
      correct length...which you have defined as the heavy atoms.  sometimes they are incomplete...and sometimes there had hydrogens.
  */
  bool  display;

  /** Determines if the atom is in the selected state || not
  */
  bool  selected;

  /** This atom determines if it is real || not
  */
  //bool  real;

  /** This is to see if it has been visited.  a multipurpouse variable. I am currently using it to determine rings */
  bool visited;

  vector<atom *> bondVisit;
 
  
private:
};

#endif





































