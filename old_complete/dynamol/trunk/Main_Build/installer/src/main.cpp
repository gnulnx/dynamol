/***************************************************************************
 *   Copyright (C) 2004 by jfurr                                           *
 *   jfurr@jabba.albmolecular.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <qapplication.h>
#include "installer.h"
#include <iostream>

using namespace std;

int main( int argc, char *argv[] ) {
    cout <<"Before QApplication"<<endl;
    QApplication a( argc, argv );
    cout <<"After QApplication"<<endl;
    installer * mw = new installer(argv[0]);
    cout <<"HERE 1"<<endl;
    mw->setCaption( "installer" );
    cout <<"HERE 2"<<endl;
    mw->show();
    cout <<"HERE 3"<<endl;
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    cout <<"HERE 4"<<endl;
    return a.exec();
}