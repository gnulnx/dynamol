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
#include "threadaction.h"

threadAction::threadAction(QObject *parent, const char *name)
 : QAction(parent, name)
{
}

threadAction::threadAction(const QString &text, const QString &menuText, QKeySequence accel, QObject *parent, const char *name, bool toggle, dynoThread *thread) 
: QAction(text, menuText, accel, parent, name, toggle)
{
   this->thread = thread;
}


threadAction::~threadAction()
{
}
/*
void threadAction::activate()
{
    ////////////cout <<"You arein activate"<<endl;
    if ( isToggleAction() ) {
        return;
    }
    emit activated(thread);
}

void threadAction::internalActivation()
{
    if ( isToggleAction() )
        setOn( !isOn() );
    emit activated(thread);
}

*/





































