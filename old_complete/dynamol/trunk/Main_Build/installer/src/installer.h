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

#ifndef INSTALLER_H
#define INSTALLER_H

#include <qmainwindow.h>
#include <qstring.h>


class installer: public QMainWindow
{
    Q_OBJECT

public:
    installer(QString fileName);
    ~installer();
    
    void createDir();
    void copyStuff();
    void updateProfile();
           
    QString fileName;
    QString installDir;
    
    /** This function simple reads int he profile file and skips over any old dynamol lines */
    bool checkProfileFile(QString file);
};


#endif
