/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
      email:   john.furr@dynamol.com
 ***************************************************************************/
#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H

#include <qobject.h>


class XmodelView;
class molView;
class molListView;
/**
@author jfurr
*/
class scriptObject : public QObject
{
Q_OBJECT
public:
    scriptObject(QObject *parent = 0, const char *name = 0);

    virtual ~scriptObject();

    
public:
   static void setParents(XmodelView *view);
   static XmodelView *view;
   static molView *viewer;
   static molListView *listView;
};

#endif





































