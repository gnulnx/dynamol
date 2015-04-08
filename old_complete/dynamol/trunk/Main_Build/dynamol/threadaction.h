/***************************************************************************
 *   Copyright (C) 2004 by jfurr                                           *
 *   jfurr@jabba.albmolecular.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, ||     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY || FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef THREADACTION_H
#define THREADACTION_H

#include <qaction.h>
#include "dynothread.h"
#include <iostream>

using namespace std;
/**
@author jfurr
*/
class threadAction : public QAction
{
Q_OBJECT
public:
    threadAction(QObject *parent = 0, const char *name = 0);
    threadAction(const QString & text, const QString & menuText, QKeySequence accel, QObject * parent, const char * name = 0, bool toggle = FALSE, dynoThread *thread = 0);
    
    ~threadAction();

//public slots:
//   void activate();
//signals:
//   void activated(dynoThread *thread);
   
private:
   dynoThread *thread;
   
  // void internalActivation();
};

#endif





































