/***************************************************************************
                          bond.h  -  description
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

#ifndef BOND_H
#define BOND_H

#include "dyobject.h"

namespace dynamol {

class atom;
class molecule;

class bond : public DyObject {
public:
	bond(const bond &bd);
	bond(int num, atom *from, atom *to, int order);
	~bond();
	bool operator==(bond const& bd) const { return true; }
	bool operator!=(bond const& bd) const { return false; }
	/** This method calculates the direction cosines for the 
		bond && store them in cosines[3] which is protected
	*/
	void  calcDirCosines();

	/* Pointers to the bonded atoms */
	atom *from, *to;
	atom *getFrom() { return from; }
	atom *getTo() {return to; }
	/* Pointer to the parent molecule */
	molecule *parent;
	molecule *getParent() { return parent; }
	
	/* The bond order */
	int order;

	/* The bond number in the molecule */
	int num;

	/* Has the bond been selected in the veiwer */
	bool selected;

	/** This is the direction cosine length */
	float len;
	/**NEW STUFF FOR THE METHOD YOU FOUND ONLINE */
	float zRot1;
	/** Axis of rotation */
	float yAxis, xAxis;

};
};
#endif
