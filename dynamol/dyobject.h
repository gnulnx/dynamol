/***************************************************************************
                          dyobject.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by John Furr
    email                : john.furr@gmail.com


    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/
#ifndef DYOBJECT_H
#define DYOBJECT_H

using namespace std;

namespace dynamol {

enum ObjectType { ATOM, BOND, MOLECULE, BASIC };

class DyObject {

public:

	DyObject(const DyObject &obj);
	DyObject(ObjectType=BASIC);
	bool operator==(DyObject const& dyobj) const { return true; }
	bool operator!=(DyObject const& dyobj) const { return false; }
	
	~DyObject();

	ObjectType Type;
	long int ObjectNum;
	static long int ObjectCount;
};

};
#endif
