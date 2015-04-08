/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "angle.h"
#include "atom.h"
#include "linAlg.h"

angle::angle(atom *front, atom *mid, atom *back)
{
	if (front == NULL || mid == NULL || back == NULL) {
		////////////cout<<"One of the angle atoms was NULL...exiting"<<endl;
		exit(0);
	}
	this->front = front;
	this->mid = mid;
	this->back = back;
	
	K = 0.001;
	refAngle = 0.001;	
	
	stepSize = .000001;
	prevEnergy = 1000000;
	
}

	

angle::~angle()
{
   front = mid = back = NULL;
}

angle &angle::operator=(const angle &ang) {
   if (this == &ang) return *this;
}


float angle::degree() {
    float *cPtr1 = front->fCoords;
    float *cPtr2 = mid->fCoords;
    float *cPtr3 = back->fCoords;
    return angleDegrees(cPtr1, cPtr2, cPtr3);
}







































