/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "torsion.h"
#include "atom.h"
#include "linAlg.h"

namespace dynacomp {

torsion::torsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4)
{
   this->atm1 = atm1;
   this->atm2 = atm2;
   this->atm3 = atm3;
   this->atm4 = atm4;
	
   V = 0;
   gamma = 0;
   n = 0;

   improper = false;
}


torsion::~torsion()
{
   atm1 = atm2 = atm3 =atm4 = NULL;
}

torsion &torsion::operator=(const torsion &tor) {
if (this == &tor) return *this;   
}


float torsion::degree() {
	float angle = 0;
	float mag1, mag3, dotProd, mp[3], trMid[3];

	float *cPtr1, *cPtr2, *cPtr3, *cPtr4;
	float cd1[3], cd2[3];

	cPtr1 = atm1->fCoords;
	cPtr2 = atm2->fCoords;
	cPtr3 = atm3->fCoords;
	cPtr4 = atm4->fCoords;

	//This section is were we calculate the torsion angle
	float cross1[3], cross2[3];
	vSub( cPtr1, cPtr2, cd1 );
	vSub( cPtr3, cPtr2, cd2 );
	vCross( cd1, cd2, cross1 );

	vSub( cPtr4, cPtr3, cd1 );
	vSub( cPtr2, cPtr3, cd2 );
	vCross( cd2, cd1, cross2 );

	float dp = vDot(cross1, cross2);
	float l1 = vLength(cross1);
	float l2 = vLength(cross2);

	float tmp = dp/(l1*l2);
	if (tmp > 1 ) tmp = 1;
	if (tmp < -1) tmp = -1;
    
	angle = 57.2958*acos(tmp);
	return angle;
}

bool torsion::inTorsion(atom *a1, atom *a2) {
   int count = 0;
   if (a1 == atm1 || a1 == atm2 || a1 == atm3 || a1 == atm4) count++;
   if (a2 == atm1 || a2 == atm2 || a2 == atm3 || a2 == atm4) count++;

   if (count == 2) return true;
   return false;
}

};//End Namespace

























































