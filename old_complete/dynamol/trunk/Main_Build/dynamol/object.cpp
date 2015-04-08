/***************************************************************************
                          object.cpp  -  description
                             -------------------
    begin                : Fri Jul 25 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ************************************************************************/

#include "object.h"
#include <fstream>
using namespace std;

int Object::objectCount = 0;
int Object::objectCreate = 0;
int Object::objectDestroy = 0;
vector<Object *> Object::registry;

Object::Object(){
  //item = NULL; //initialize item to NULL
  parent = NULL;
  objectNum = objectCount;
  objectCount++;
  objectCreate++;
  selected = false;
  numOfChildren = 0;
  selectedChildren = 0;
  registry.push_back(this); //add yourself to the class registry
}
Object::Object(Object *parent) {
  this->parent = parent;  //set parent to parent Object
  //item = NULL; //initialize item to NULL
  objectNum = objectCount;
  objectCount++;
  objectCreate++;
  selected = false;
}

Object::~Object(){
   parent = NULL;
   registry[objectNum] = NULL;
   objectDestroy++;
}

Object &Object::operator=(const Object &obj) {
  //Do you need to update the registrY???? be sure && check
  if (this == &obj) return *this;
}

void Object::updateRegistry() {
   
   ////////////cout <<"registry size: " << registry.size() << endl;
   int incr = 0;
   vector<Object *>::iterator iter = registry.begin();
   while (iter != registry.end()) {
      Object *tmp = *iter;
      if (tmp == NULL) {
          registry.erase(iter);
	  if (iter == registry.end()) break;
	  incr++;
	  iter--;
      } else {
        tmp->objectNum -= incr;
      }
      iter++;      
   }
   objectCount = registry.size();
   ////////////cout <<"registry.size(): " << registry.size() << endl;
   
}

void  Object::setItem(molListViewItem *itm)  
{ 
   item.reset(itm); 
//this->item = item; 
};

void Object::setParent(Object *parent) 
{ this->parent = parent; };

int Object::rtti() 
{ return 1; };

Object  *Object::getParent()
{ return parent; }

int Object::getObjectNum() 
{ return objectNum; };

molListViewItem *Object::getItem()
{ 
   return item.get();
   //return item; 
};

Object *Object::getObject(int pos) 
{ return registry[pos]; };

void Object::addChild()
{ this->numOfChildren++; };

void  Object::childSelected() {
  this->selectedChildren++;
  if (selectedChildren == numOfChildren) {
    setSelected(true, true);
    item->setSelected(true);
    //////////////cout <<"Object::childSelected()---in HERE"<<endl;
  }

  //////////////cout <<"number of childer: " << numOfChildren << endl;
  //////////////cout <<"selected children: " << selectedChildren << endl;
}

void  Object::childDeSelected() {
  if (selectedChildren == numOfChildren) {
    setSelected(false, true);
    //////////////cout <<"Object::childDeSelected() ---- in HERE"<<endl;
  }
  if (selectedChildren > 0) {
    this->selectedChildren--;
  }

}

//bool  Object::isSelected()                                         {return selected;};

bool  Object::isSelected() {
  return item->isSelected();
}

void  Object::setSelected(bool bv, bool children)    {
  selected = bv;
  Object *tmp = getParent();
  if (tmp != NULL) {
    if (bv == true)
      tmp->selectedChildren++;
    else
      tmp->selectedChildren--;
  }    
}

Object *Object::lastParent() {
   Object *tmp = parent;
   if (!parent) return this;
   while (true) {
   	Object *tmp2 = tmp->getParent();
	if (!tmp2) return tmp;
	tmp = tmp2;
   }
   return tmp;
}









































