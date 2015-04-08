/***************************************************************************
                          mollistviewmolitem.h  -  description
                             -------------------
    begin                : Sat Jul 19 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#ifndef MOLLISTVIEWMOLITEM_H
#define MOLLISTVIEWMOLITEM_H

#include <qlistview.h>

class molecule;

/**
  *@author John Furr
  */

class molListViewMolItem : public QListViewItem  {

public: 
  molListViewMolItem(QListView *parent);
  molListViewMolItem(QListView *parent, QString &name);
  molListViewMolItem(QListViewItem *parent);
  molListViewMolItem(molListViewMolItem *parent, QString &name);
	~molListViewMolItem();

  /** Virtual function is overloaded to do runtime type identification
  */
  virtual  int rtti() const;

  /** Used to the set the item (molecule pointer)
  */
  void        setItem(molecule *mol);

  /*  Used to return a pointer to the molecule for which the item is used
  */
  molecule  *getItem();
protected:
  molecule *mol;
};

#endif





































