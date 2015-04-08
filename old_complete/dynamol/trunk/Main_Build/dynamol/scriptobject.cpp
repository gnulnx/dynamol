/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   email:  john.furr@dynamol.com                                           
 ***************************************************************************/
#include "scriptobject.h"

#include "xmodelview.h"
#include "molview.h"
#include "mollistview.h"

//This first section is all static data members
XmodelView *scriptObject::view = NULL;
molView *scriptObject::viewer = NULL;
molListView *scriptObject::listView = NULL;

void scriptObject::setParents(XmodelView *vw) {
   view = vw;
   listView = view->listView;
   viewer = vw->viewer;
}


//Now we start the real class stuff
scriptObject::scriptObject(QObject *parent, const char *name)
 : QObject(parent, name)
{
}


scriptObject::~scriptObject()
{
}







































