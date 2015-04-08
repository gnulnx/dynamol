/***************************************************************************
                          mollistviewatomitem.cpp  -  description
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

#include "mollistviewatomitem.h"


molListViewAtomItem::molListViewAtomItem(QListViewItem * parent)
: QListViewItem(parent)
 {
}
molListViewAtomItem::~molListViewAtomItem(){
}


molListViewAtomItem::molListViewAtomItem(QListView *parent)
 : QListViewItem(parent)
{
}


molListViewAtomItem::molListViewAtomItem(molListViewMolItem * parent, QString &name)
: QListViewItem(parent, name)
{
}

molListViewAtomItem::molListViewAtomItem(QListView *parent, QString &name)
 : QListViewItem(parent, name)
 
{

}


void          molListViewAtomItem::setItem(atom *atm)              {this->atm = atm;};
atom          *molListViewAtomItem::getItem()                         {return this->atm;};
int              molListViewAtomItem::rtti() const                                {return 10002;}





































