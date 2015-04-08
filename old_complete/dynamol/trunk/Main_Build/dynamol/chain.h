/***************************************************************************
                          chain.h  -  description
                             -------------------
    begin                : Sun Feb 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef CHAIN_H
#define CHAIN_H

/** Base Class Include */
#include "molecule.h"

#include <list>
#include <deque>

using namespace std;

class molView;
class protein;
class ribbon;
class bond;
/**
  *@author John Furr
  */

/** A Chain is both a special kind of molecule && a container for fragments which are themselves
    special molecules
*/
class chain : public molecule {
  friend class molView;
  friend class protein;
  friend class pdbReader;
  friend class ribbon;
public: 
   static int chainCreate;
   static int chainDestroy;
   static bool lock;
   chain();
   virtual ~chain();
   chain &operator=(const chain &ch);
protected:
   
public:
   
   virtual int numOfFragments();

  void        addFrag(fragment *frag);
  int         numOfFrags();

  void        setFragsToBegin();
  fragment   *getCurrentFrag();
  int         nextFrag();
  int         prevFrag();

  void          setRibbon(ribbon *rib);
  ribbon      *getRibbon();
  
  /** This function is responsible for removing the fragment fr from chains
   list of fragments
  */
  void removeFrag(fragment *ch);

  virtual void setSelected(bool state, bool children);

  virtual int rtti(); //Returns 13

  deque<fragment *>            frags;
protected:
  deque<fragment *>::iterator  currentFrag;                                
  

  list<bond *>                hetBonds;

  ribbon *rib;
  int ribList;
  
};

#endif





































