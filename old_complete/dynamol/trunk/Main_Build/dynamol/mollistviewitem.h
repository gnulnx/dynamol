/***************************************************************************
                          atom.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/
#ifndef MOLLISTVIEWITEM_H
#define MOLLISTVIEWITEM_H

#include <qlistview.h>
#include "object.h"

#include <boost/shared_ptr.hpp>

class Object;
class molListView;
class molListViewItem;
typedef boost::shared_ptr<molListViewItem> listItemPtr;

class molListViewItem : public QListViewItem  {
public:
  molListViewItem(QListView *parent, QString &name, Object *obj); //This is the prefered method
  molListViewItem(molListViewItem *parent,  QString &name, Object *obj);
  ~molListViewItem();

  /**   This member function is used to set the Object pointer.  
  *     You should probably try && do this with the constructer
  *     as it will make the code a little bit cleaner && less verbose
  */
  void  setObject(Object *obj);

  /**   Returns a pointer to the object.  You should try && use polymorphism 
  *     here if you can.  If not remember that the Object class
  *     also contains the virtual int rtti() function to help out
  */
  Object  *getObject();

  int selected;
  
  molListViewItem *parent;
  molListView *mList;
private:
  Object *obj;

  
};

#endif





































