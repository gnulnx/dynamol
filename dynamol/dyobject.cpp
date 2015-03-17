/***************************************************************************
                          dyobject.cpp  -  description
                             -------------------
    begin                : Thu Jan 1 2008
    copyright            : (C) 2008 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include "dyobject.h"
#include <iostream>
using namespace std;
namespace dynamol {

long int DyObject::ObjectCount = 0;


DyObject::~DyObject() {

}

DyObject::DyObject(const DyObject &obj) 
{
	Type = obj.Type;
	ObjectNum = ObjectCount;
	ObjectCount++;
}

DyObject::DyObject(ObjectType type) 
{
	this->Type = type;
	ObjectNum = ObjectCount;
	ObjectCount++;
}


}; // End dynamol namespace
