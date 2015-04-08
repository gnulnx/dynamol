/***************************************************************************
                          mollistviewatomitem.h  -  description
                             -------------------
    begin                : Sat Jul 19 2003
    copyright            : (C) 2003 by John Furr
    email                : jrflnx@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, ||     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MOLLISTVIEWATOMITEM_H
#define MOLLISTVIEWATOMITEM_H

#include <qlistview.h>
#include "mollistviewmolitem.h"

class atom;
//class molListViewMolItem;
/**
  *@author John Furr
  */

class molListViewAtomItem : public QListViewItem  {

public: 
	molListViewAtomItem(QListViewItem *parent);
  molListViewAtomItem(QListView *parent);
  molListViewAtomItem(QListView *parent, QString &name);
  molListViewAtomItem(molListViewMolItem *parent, QString &name);
	~molListViewAtomItem();

     /** Virtual function is overloaded to do runtime type identification
  */
  virtual int rtti() const;

  /** Used to the set the item (atom pointer)
  */
  void        setItem(atom *atm);

  /*  Used to return a pointer to the atom for which the item is used
  */
  atom  *getItem();
protected:
  atom *atm;
};

#endif





































