/***************************************************************************
                          xmodeldoc.h  -  description
                             -------------------
    begin                : Sat Feb 21 06:29:20 EST 2004
    copyright            : (C) 2004 by John Furr
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, ||     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef XMODELDOC_H
#define XMODELDOC_H
//#include "mollistview.h"

// include files for QT
#include <qobject.h>

#include <list>
#include <qstring.h>
#include "moldb.h"
using namespace std;


/**
  * the Document Class
  */

  class molecule;

class XmodelDoc : public QObject
{
  Q_OBJECT

  public:
    XmodelDoc();
    ~XmodelDoc();
    void newDoc();
    bool save();
    bool saveAs(QString &filename, list<molecule *> &renList);
    bool load(QString &filename);
    bool isModified() const;

  signals:
    void documentChanged();

  protected:
    bool modified;

  public:
    molDB db;
};

#endif





































