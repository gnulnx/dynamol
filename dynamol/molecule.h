/***************************************************************************
                          molecule.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef DYNAMOL_MOLECULE_H
#define DYNAMOL_MOLECULE_H

#include "dyobject.h"

#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::cout;
using std::endl;

namespace dynamol {
class atom;
class bond;
//atom *atom_get(vector<atom *> &Atoms, int i)
//{
//	return Atoms[i];
//};
enum RenderType {WIRE, STICK, CPK};

class molecule : public DyObject {
public:
	/* Call molecule(string name) from all C++ code.  You must explicitly create a string object
	//  string name; molecule *mol = new molecule(name)
	//  NOT
	//  molecule *mol = new moleucle("name")...defaults ot bool constructor
	*/
	molecule(string name);
	/** this function should only be called from python code.
	//  The point of all this is so that Molecule objects created in python	
	//  and passed to C++ full have a deep copy because python will want to delete that
	//  object at the end of it's life cycle.
	*/
	molecule(int PyObject=1);

	molecule(const molecule &mol);

	~molecule();
	
	//This is a variable that determines if the molecule was created in Python or C++
	int PyObject;

	// Functions to export to Python
	void SetName(string name);
	string GetName() { return this->name; }

	atom *addAtom(int num, string type, float x, float y, float z, int atomicNum=-1);
	bond *addBond(int num, int from, int to, int order);

	// atoms is used by C++
	// AtomObjs is used by Python 
	vector<atom *> atoms;
	vector<atom> AtomObjs;	

	// bonds is used by C++
	// BondObjs is used by Python
	vector<bond *> bonds;
	vector<bond> BondObjs;

	// Used by python extension to gain
	// access to atom and bond pointers
	vector<atom> getAtomObjs();
	vector<bond> getBondObjs();

	int BondArraySize;
	vector<float> BondVertexArray;
	vector<float> BondColorArray;

	int AtomArraySize;
	vector<float> AtomVertexArray;
	vector<float> AtomColorArray;

	int TriangleArraySize;
	vector<float> StickTriangleArray;
	vector<float> StickNormalArray;
	vector<float> StickColorArray;

	string name;

	void solidCylinder(double x, double y, double z, double radius,
           double height, int n_subdivision_steps);
	
	void BuildVertexArrays(RenderType modelType, vector<float> &center);
	void WireFrameModel(vector<float> &center);
	void StickModel(vector<float> &center);
	/** SetNewCenter */
	void SetNewCenter(float x, float y, float z);

	/** This returns the center coords for the molecule */
	vector<float> getCenter();

	/** This function will center the molecule at 0, 0, 0 */
	void CenterMol();
	
	/** this function will center teh molecule at Center[0], Center[1], Center[2] 
	*   You must cal CenterMol before you cann DeCenterMol
	*/
	void DeCenterMol();
	//vector<float> Center;
	float Center[3];
};

};

#endif
