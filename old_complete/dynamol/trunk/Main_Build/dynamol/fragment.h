/***************************************************************************
                          fragment.h  -  description
                             -------------------
    begin                : Sun Feb 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : jphn.furr@dynamol.com
 ***************************************************************************/


#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "molecule.h"
#include "enumTypes.h"
/**
  *@author John Furr
  */

#include <string>
  
  using namespace std;
/**
  A fragment is a molecule && inhertis from class molecule...A fragment will defined as an
  aminoacid, a neucleic acid, benzene ring,
*/

class chain;
class protein;
class atom;
class bond;

class fragment : public molecule  {
  friend class pdbReader;
  friend class protein;
  friend class chain;
public:
  static int fragCreate;
  static int fragDestroy;
  fragment();
  virtual ~fragment();
  fragment &operator=(const fragment &frag);
protected:
  
public:

  vector<atom *>  *getAtomList();
  vector<bond *>  *getBondList();

  /** This returns the PDB fragment number */
   int getFragNum();
   void setFragNum(int fragNum);
   
   virtual string getType();
   virtual int rtti(); //returns 12

   /** This is a special function for adding a new atom to an already contructed fragment
   Part of it';s function is to update the atoms && bonds of all it's parents as well as add it to the molListView */
    virtual atom *addNewAtom(int num, string type, double x, double y, double z, int atomicNum);

    /** Like the above function only for bonds */
    virtual bond *addNewBond(atom *from, atom *to, int order);
   FRAG_TYPE type;
   
   bool nTer;
   bool cTer;
protected:
  string fragType;
  int fragNum;



};

#endif





































