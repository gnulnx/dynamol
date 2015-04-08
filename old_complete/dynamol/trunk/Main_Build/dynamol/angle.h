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
#ifndef ANGLE_H
#define ANGLE_H

class atom;
/**
@author jfurr
*/
class angle
{
public:
    angle(atom *front, atom *mid, atom *back);
    ~angle();
protected:
    angle &operator=(const angle &ang);
public:
    atom *front, *mid, *back;
    float refAngle;
    float actualAngle;
    float K;
    
    float degree();    
    
    float stepSize;
    float prevEnergy;
};
#endif




































