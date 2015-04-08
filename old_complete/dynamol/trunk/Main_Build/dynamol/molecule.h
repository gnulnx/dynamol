/***************************************************************************
                          molecule.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef MOLECULE_H
#define MOLECULE_H

#include "object.h"
#include <list>
#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::list;

//BOOST Includes
#include <boost/shared_ptr.hpp>

//Dynbase Includes
#include "../dynabase/atom.h"

//SURFACE INCLUDES
class molListViewItem;
class surface;

//Dynamol Base Library Forward Declarations
namespace dynabase {
   class nonBond;
}


/**
  *@author John Furr
  */

class atom;
class bond;
class torsion;
class angle;
class nonBond;

class molecule : public Object {
  friend class molView;
  friend class fragment;
  friend class chain;
  friend class protein;
  friend class fragFactory;
  friend class ribbon;
  friend class atomTyper;
  friend class forceField;
  friend class pickEngine;
  friend class molDB;
  friend class molListView;
  friend class dynamics;
  
public: 
   molecule();
   virtual ~molecule();
/*  
   virtual molecule *getParent();
   void setParent(molecule *parent);
   molecule *parent;
 */
   /** This does a simple molecule copy Currently only atoms and bonds are copied
   */
   virtual molecule &operator=(const molecule &mol);
   
   /** This function will add two molecules together
      *  A = A + B
      *  Atom A must have an X atom as must atom B
   */
   molecule &operator+=(const molecule &mol);
   
   /** This function adds two molecules together and returns a new
   *   molecule.  C = A + B.
   *   Neither atom A nor atom B is modified 
   */
   molecule operator+(const molecule &mol);
   
  /** This method simply adds a new atom to th molecule.
      You will need to implement a typeAtoms routine
      Maybe with enum {MM2, MM#, OPLSAA, etc...
  */  
  virtual atom *addAtom(int num, string type, double x, double y, double z, int atomicNum);
  virtual atom *addAtom(dynabase::atomPtr base);
  
  static int molCreate;
  static int molDestroy;

  /** This method adds the bonds to the molecule..  I believe that bonds are added double...That is
      they are defined in a redundant way.  At some point I think you will want to fix this problem.
      As bad as this sounds graphics are not to slow at this point so it is probably not worht worrying
      right now....Hoever if you continue to build code base off of this then it will only be harder to
      to fix later

      This function is also responsible for setting up the connection vector<atom *> atoms in the atom class
  */
  bond *addBond(int num, int from, int to, int order);

  /** This method updates the valence && sets the formal Charge as it goes */
  void updateValence();

  /** \brief Returns the molecular weight
  *  
  *   Returns the molecular weight
  */
  float molWeight();

  /** This method adds a new distance */
  void addDistance(atom *atm1, atom *atm2);

  /** This function deletes a distance */
  void delDistance(atom *atm1, atom *atm2);

  /** This method adds a new Angle */
  void addAngle(atom *atm1, atom *atm2, atom *atm3);

  /** This function deletes an Angle */
  void delAngle(atom *atm1, atom *atm2, atom *atm3);

  /** This method adds a new Torsion */
  void addTorsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4);

  /** This function deletes a Torsion */
  void delTorsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4);

  /** Sets the molecules name
  */
  void    setName(string name);

  /**   return the molecules name
  */
  string   getName();

  /**   Appends atom list
  */
  void    appendAtomList(vector<atom *> atomList);

  /**   Appends the bond list
  */
  void    appendBondList(vector<bond *> bondList);

  /**   This gets the list of atoms;
  */
  vector<atom *>  getAtomList();
  
  /** This function should replace addPropValuePair(QString, QString) */
  void addPropValuePair(QString name, QString value, QString type = "s");
  
  /** This function will get the property type store in propTypeMap
  *   It will be on of i/f/d/s.  Of if the property is not present it 
  *   will return 'none'
  */
  QString getPropType(QString propName);
  
  /** This function returns the value of the property 
  *   If the property is not found the function returns not_fond
  */
  QString getPropValue(QString property);
  
  /** This function clears the propMap and the propTypeMap */
  void clearPropMap();  
 
  /** This is designed to replace propertyData and propertyName 
  *   <pre>
  *   propMap[logP] = 5.8;
  *   </pre>
  */
  map<QString, QString> propMap;
  
  /** This is designed to replace propertyType 
  *   You should store th eproperty name and it's type i/f/d/s like:
  *   propTypeMap[logP] = "i";
  */
  map<QString, QString> propTypeMap;
  
     
  /** This will hold the type of charges the molecule has...the default is NONE */
  string chargeType;
  
  /**This string holds the forcefield for which the parameters..bonds, angles, torsions, nonbonds are derived.  The defualt is NONE */
  string ffTypes;
  
  /** This vectro contains the tot, bond, angle, torsion energies
  */
  vector<float> potEnergy;

  /** This gets the bond list
  */
  vector<bond *>  getBondList();

  bond *getBond(atom *atm1, atom *atm2);

  /** Return the centroid of the current atom
  */
  vector<float> centroid();
  
  /** This function returns the center of the visible atoms */
  //vector<float> visibleCenter();

  /** Create a nurb object
  */
  void createNurb();

  /** Return a pointer to the curent atom in list<atom *> atoms
  */
  atom *getCurrentAtom();

  /** Returns the number of chains
  */
  virtual int numOfChains();

  /** Returns the number of fragments
  */
  virtual int numOfFragments();

  /** reuturns the integers 11 for runtime type identification
  */
  virtual int rtti();
  
  
  /**   returns a pointer to the atom with atom number {num}
  */
  atom *returnAtom(int num);
  void setAtomToBegin();
  void  setAtomToEnd();
  int nextAtom();
  int prevAtom();
  void printAtoms();

  bond *getCurrentBond();
  void  setBondToBegin();
  void  setBondToEnd();
  int nextBond();
  int prevBond();
  

  /** Returns the total number of molecules that have been created during the current session
  */
  static long int getCount();

  /** Returns the current molecules number
  */
  long int  getMolNumber();

  /** Returns the number of atoms in the molecule
  */
  virtual int       getNumOfAtoms();

  /** Returns the number of bonds in the molecule
  */
  virtual int       getNumOfBonds();

  /** Deletes the atom pointed to by the iterator *iter
  */
  virtual void              removeAtom(atom *at);

  /** Removes the bond && deletes it.
  */
  virtual void              deleteBond(bond *bd);

  /** 	Void  unselect all atoms
  */
  void					unSelectAll();

  /**   Select all atoms in the molecule
  */
  void          selectAll();

  /** Set the molecule number;
  */
  void          setNum(int num);

  /** This function returns the number of selected atoms in the molecule */
  int numOfSelectedAtoms();

  /** Get the molecule number
  */
  int           getNum();

    /** Sets the molistViewAtomIten pointer
  */
//  void          setItem(molListViewItem *item);

  /** Responsible for selected the molecule including all it's atoms.  it is also responsible for
      making sure that the molListItem is selected
  */
  void  setSelected(bool bv, bool children);

  /** returns a pointer to the molListViewAtom Item || null if the value is not set
  */
  //molListViewItem *getItem();

  /** Update the vector<atoms *> in each of the molecule atoms
  */

  void updateBondedAtoms();

  /* Check to see if the bond is delocalized...example carboxy || nitro */
  bool isDeloc(bond *bd);

  /** Set the ribbon pointer to point to a ribbon */
  //void  setRibbon(ribbon *rib);

  /** return the ribbon pointer */
  ribbon *getRibbon();

  /** This varialbe is used to determine if the molecule has a display list || not.
    when there is no display list associated with this molecule then thisnumber should be -1
    Other wise it will contain the number of the display list
  */
   int molDisplayList;

     /** this vector holds the current distances (for rendering) for the molecule */
   vector< vector<atom *> > dist;

   /** This vector holds the current angles (for rendering) in the molecule */
   vector< vector<atom *> > ang;

   /** This vector holds the current Torsions (for rendering) in the molecule */
   vector< vector<atom *> > tor;
  
  vector<atom *>::iterator currentAtom;
  vector<bond *>::iterator currentBond;
  
  /** This function is used to set || reset all of the angle's in the molecule atom*. atom *, atom *
  	It returns the total number of angles in the molecule
	It returns the number of Angles
  */
  int setAngles();
  
  /** This function is used to set the nonBonded Terms of the molecule
  	It return the number of nonBOnds
  */
  int setNonBonds(float cutoff);
  
  /** This function is used to set the Torsional terms of the molecule
  It returns the number of torsions
  */
  int setTorsions();
  
  /** This is a utility function which returns true if it is a bond 
  */
  bool isBond(atom *atm1, atom *atm2);
  
  
  /* These are you fundamental molecule components */
  vector<atom *>  atoms;
  vector<bond *>  bonds;
  vector<angle *> angles;
  vector<torsion *> torsions;
  vector<nonBond *> nonBonds;
  vector<dynabase::nonBond *> nonbonds;

  bool showSurface();
  void hideSurface(bool hide);

  boost::shared_ptr<surface> surf;
private:
  torsion *addMolTor(atom *atm1, atom *atm2, atom *atm3, atom *atm4);
 
  
protected:
   

  float nurb[4][4][3];

  int molNum;

  /** This is the molecule number as it is read in.....you made this for fragments...so you
      would know that the frag number wa
  */
  int num;  

  string name;
    
  /** Unique molecule number derived from count
  */
  long int molNumber;

  /** used to assign unique mol numbers to each molecule used
  */
  static int count;

  /** Pointer to the molListViewItem which contains this molecule
  */
  //molListViewItem *item;
public:
   bool isSelected;
};

#endif





































