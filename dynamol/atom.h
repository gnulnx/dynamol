/***************************************************************************
                          atom.h  -  description
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

#ifndef ATOM_H
#define ATOM_H

#include <vector>
#include <string>
#include <iostream>
#include "dyobject.h"
using std::vector;
using std::string;
using std::iostream;
using namespace std;

namespace dynamol {

class molecule;
class atom : public DyObject {
public:
	
	atom(const atom &atm);
	atom(int num, string symbol, float x, float y, float z, int atomicNum=-1);
	bool operator==(atom const& atm) const { return true; }
	bool operator!=(atom const& atm) const { return false; }
	
	~atom();

	/** This method pushes back a connected atom */
	bool addAtom(atom *);

	/* This is called to set the default color of the atom */
	void defaultColor();

	/* This convers the symbol to the atomic number */
	int SYM2AN(string type);

	/* Atomic Coordinates */
	float fCoords[3];

	/* Color value. 4Th value controls transparency */
	float COLOR[4];

	/** Bonded Atoms */
	vector<atom *> atoms;

	/* Atom number in the Molecule */
	int num;

	/* Atomic Number */
	int AN;

	/* String for the Atomic Symbol */
	string symbol;

	/* Pointer to the Parent Molecule */
	molecule *parent;
	molecule *getParent();
};

};
#endif
