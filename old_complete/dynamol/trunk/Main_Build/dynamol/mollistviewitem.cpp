/***************************************************************************
                          mollistviewitem.cpp  -  description
                             -------------------
    begin                : Fri Jul 25 2003
    copyright            : (C) 2003 by John Furr
    email                : jrflnx@yahoo.com
 ***************************************************************************/

#include "mollistviewitem.h"
#include "mollistview.h"
#include <queue>

using namespace std;


molListViewItem::molListViewItem(QListView *parent, QString &name, Object *obj)
: QListViewItem(parent, name)
{
 
  this->mList = dynamic_cast<molListView *>(parent);
  this->parent = NULL; //becaues parent is a molListViewItem
  this->obj = obj;
}


molListViewItem::molListViewItem(molListViewItem *parent,  QString &name, Object *obj)
:QListViewItem(parent, name)
{
  this->obj = obj;  //initialize the Object pointer
  this->parent = parent;
  mList = dynamic_cast<molListView *>(parent->listView());
  
}


molListViewItem::~molListViewItem(){
  obj = NULL;

  for (int i=0; i<mList->selQueue.size(); i++) {
    if (mList->selQueue[i] == this) {
       mList->selQueue[i] = NULL;
       break;
    }
  }

}

void  molListViewItem::setObject(Object *obj) {
  this->obj = obj;
}

Object  *molListViewItem::getObject() {
  return obj;
}





































