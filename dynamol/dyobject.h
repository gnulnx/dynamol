/***************************************************************************
                          dyobject.h  -  description
                             -------------------
    begin                : Thu Jan 1 2008
    copyright            : (C) 2008 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

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
