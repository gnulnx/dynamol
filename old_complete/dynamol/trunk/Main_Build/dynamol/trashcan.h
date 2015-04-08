/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef TRASHCAN_H
#define TRASHCAN_H


#include <vector>
#include <set>
#include <map>

class Object;
class atom;
class bond;
class molecule;
class fragment;
class chain;
class protein;
using namespace std;
/**
@author jfurr
*/
class TrashCan{
public:
    TrashCan(vector<Object *> &objectVector);
    TrashCan(vector<fragment *> &fragVector);
    TrashCan(atom *atm);
    TrashCan(vector<atom *> &atomVector);
    TrashCan();
    ~TrashCan();
    
    /** This function empties the trash can
    *   It is called by the destructor 
    */
    void empty();
    
    /** \brief delete atoms
    *
    *    This function deletes the atoms in the vector
    */
    void empty(vector<atom *> &atToDel);
    
    /** this function is used to pass a set that should ojbects
    *   removed (if present) before any object deletion
    */
    void setCheck(set<molecule *> &setToCheck);

private:
   set<atom *> atomSet;
   set<bond *> bondSet;
   set<molecule *> molSet;
   set<fragment *> fragSet;
   map<fragment *, chain *> fragChainMap;
   map<fragment *, protein *> fragProtMap;
   set<chain *> chainSet;
   set<protein *> protSet;
   
   set<molecule *> *setToCheck;
   
   void deleteAtoms();
   void deleteMols();
   void deleteFrags();
   void deleteChains();
   void deleteProts();
};

#endif

















