/***************************************************************************
                          mollistviewmolitem.cpp  -  description
                             -------------------
    begin                : Sat Jul 19 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include "mollistviewmolitem.h"

molListViewMolItem::molListViewMolItem(QListView *parent) 
  : QListViewItem(parent)
{

}
molListViewMolItem::molListViewMolItem(QListViewItem *parent)
 : QListViewItem(parent)
{

}

molListViewMolItem::molListViewMolItem(QListView *parent, QString &name)
 : QListViewItem(parent, name)
{

}

molListViewMolItem::molListViewMolItem(molListViewMolItem * parent, QString &name)
: QListViewItem(parent, name)
{
}


molListViewMolItem::~molListViewMolItem(){
}

void          molListViewMolItem::setItem(molecule *mol)    {this->mol = mol;};
molecule    *molListViewMolItem::getItem()                {return this->mol;};
int             molListViewMolItem::rtti() const                        {return 10001;};





































