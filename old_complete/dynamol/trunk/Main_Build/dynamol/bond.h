/***************************************************************************
                          bond.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#ifndef BOND_H
#define BOND_H

//#include "atom.h"
#include <iomanip>
#include "object.h"
#include <string>

#include <math.h>
#include "enumTypes.h"

using namespace std;

/**
  *@author John Furr
  */
class atom;
//enum BONDRENDER;

class bond : public Object {
  friend class molecule;
  friend class molView;
  friend class forceField;
  friend class molDB;
  friend class atomTyper;
  friend class dynamics;
public: 
  static int bondsCreated;
  static int bondsDelete;
  bond();
  bond(int num, atom *from, atom *to, int order);
  virtual ~bond();
protected:
  bond &operator=(const bond &bd);
public:

  /*
  molecule *getParent();
  void setParent(molecule *mol);
  molecule *parent;
  */
  /** This is overloaded from the object class.  For bonds it returns 9 */
  virtual int rtti();
  
  bool selected;
  void setSelected(bool);
  
  /** This is stuff for setting up bond rotations and such. 
  *   I Think it will mostly be called from the conformation class
  */
  bool rotable;
  int defInc;
  bool isRotable();
  void setRotable(bool rot);
  
  /** This function return the atom num bonded to the atom pointed to by *at
      It return -1 if the call fails.  That is if there is no atom bonded to bond
  */
  int getAtomNum(atom *at);
  
  int fromNum();
  /** This function returns a pointer to the from atom.
  */
  atom *fromAtom();
  
  string fromSym();
  //vector<double> fromCoords();
  
  int     toNum();
  
  /** This function returns a pointer to the to atom.
  */
  atom   *toAtom();
  string  toSym();

  /** This function returns the bond order...1 single, 2 double, 3 triple
  */
  int     getOrder();

  /** This function returns the bond length
  */
  float  bondLength();
  //vector<double> toCoords();

  /** This function return the bond render type
  */
  BONDRENDER  getRenderType();

  /** This function sets the bond render type.  Currently either STICK || WIRE
  */
  void        setRenderType(BONDRENDER renderType);

  /** Returns the bond number;
  */
  int         getNum();

  /**   Used to change the bond number...This is needed int he protein reading routines
  */
  void        setBondNum(int num);

  /** This method calculates the direction cosines for the bond && store them in cosines[3] which is protected
  */
  void  calcDirCosines();

  /** This method sets the bond order */
  void setOrder(int order);
  
  /** This method is used to update all the dirCoses, length && such stuff 
  */
  void updateBond();
  
  /** This is used to set the bond number */
  void setNum(int num);

  string bcc;
public:
  /** This is the direction cosine length
 */ 
  float len;
  

  /**NEW STUFF FOR THE METHOD YOU FOUND ONLINE
  */
  float zRot1;

  //float zRot2;

  /** Axis of rotation
  */
  float yAxis, xAxis;

  /** This is a switch which determines wether || not the bond should be updated || not
  */
  //bool  update;

  /**  This is the bond order.  1 single...2 double...3 triple
  */
  int order;
  
  /** This is the forcefield ref Length 
  */
  float refLen;
  
  /** THis is the force field spring constant */
  float K;
  
  
public:
/**  This is the bond number
*/
  int num;

/** Pointer to the from atom
*/
  atom *from;
/** pointer to the to atom
*/
  atom *to;

  /** enum type used to determine how to render the bond
  */
  BONDRENDER renderType;
};

#endif





































