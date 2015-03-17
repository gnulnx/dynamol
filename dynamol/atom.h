/***************************************************************************
                          atom.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

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
