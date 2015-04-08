/***************************************************************************
                          object.h  -  description
                             -------------------
    begin                : Fri Jul 25 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#ifndef OBJECT_H
#define OBJECT_H

#include "mollistviewitem.h"
#include <iostream>
#include <vector>
using namespace std;

//BOOST Includes
#include <boost/shared_ptr.hpp>

class molListViewItem;
typedef boost::shared_ptr<molListViewItem> listViewItemPtr;
/**
  *@author John Furr
  */



class Object {
  friend class pickEngine;
  friend class TrashCan;
public: 
   
  /** Keep track of the number of objects that have been created
  */
  static int objectCount;
  static int objectCreate;
  static int objectDestroy;
  
   /** Object constructer
   */
   Object();

   /** Overlaoded constructor for convenience
   */
   Object(Object *parent);

   /**   Virtual destructer...remember to make changes to all inherited classes
          For instance class molecule needs to loop through all atoms && bonds && delete each one accordingly
   */
   virtual ~Object();
   
   Object &operator=(const Object &obj);

  /**  This function should be used to determine runtime type information.  Class Object returns a value of 1.
      You should make derived classes like molecule, atom, bond, etc...all return different values.
      //See derived class files for exact implementation
  */
  virtual int rtti();

  /**  Virtual function which controls the molListViewItem->setSelected method.  Make sure derived classes handle it right
  */ 
  virtual void setSelected(bool bv, bool children);

  /**  returns true if the object is selected.  Otherwise it returns false. Simply calls QListViewItem->isSelected()
 */
  bool  isSelected();

  /** This method sets the parent object.  Probably better to eventually take care of this with the constructer
  */
  void  setParent(Object *parent);

  /** Returns the object parent....thus an atom callling getParent like atom->getParent would return the molecule
  */
  Object  *getParent();

  /** Returns a pointer the the molListViewItem {item}
  */
  molListViewItem *getItem();

  /** Return the object number
  */
  int getObjectNum();
  
  /** This memeber function sets the item pointer to the molListViewItem *item which holds the Object *
  */
  void setItem(molListViewItem *item);

  /** This function returns the object from the registry that is specified at position "pos" in the registry vector
  */
  Object  *getObject(int pos);

  /** This function increments the total number of children
  */
  void  addChild();

  /** Tell the object that one of it's children has been selected
  */
  void  childSelected();

  /** Tell the object that one of it's children has been de-selected
  */
  void  childDeSelected();
  
  /** Returns the highest parent for the current object */
  Object *lastParent();
  
  /** This should be called after objects are deleted...it renumbers && deletes various registry components */
  static void updateRegistry();

protected:
  /** This variable holds a pointer to the molListView Item which holds the Object in the molListVIew if such an item exsists
  */
  //molListViewItem *item;
  listViewItemPtr item;

//private:
  /** This holds a pointer to the parent Object if such an object exsists otherwise it's value is NULL;
  */
  Object *parent;

protected:

  /**    Hopefully this will become a registry for objects were the objects are hashed with their integer values....
          Since each object has a unique identifier that starts at zero && and autoincrements then we can simply call the object number
          in the vector && have it give us the object we desire.....might try making this a constant size to help performance
  */
  static vector<Object *> registry;

  /** This assigns a unique number ot each object based on the objectCount
  */
  int objectNum;

  bool  selected;

  /** This is an integer value which cooresponds to the number of children this object has
  */
  int numOfChildren;

  /** This is an integer value cooresponding to the number of children that are selected
  */
  int selectedChildren;

};

#endif





































