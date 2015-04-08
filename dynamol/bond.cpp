/***************************************************************************
                          bond.cpp  -  description
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

#include "bond.h"
#include "atom.h"
#include "enumTypes.h"
#include <fstream>

using namespace std;

#include <math.h>

namespace dynamol {

bond::bond(const bond &bd)
: DyObject()
{
	num = bd.num;
	order = bd.order;
	selected = bd.selected;

	// Note 1)  atom *from and atom *to need to be updated in the molecule copy costructor
}

bond::~bond(){}

bond::bond(int num, atom *from, atom *to,  int order)
: DyObject()
{
	//Do you really need this?
	this->num = num;
	this->from = from;
	this->to = to;
	this->order = order;
	this->selected = false;
	calcDirCosines();
}

/** This method calculates the direction cosines for the bond && store them in cosines[3] which is protected
  */
void  bond::calcDirCosines() {
	/*
	vector<float> Coords1(3), Coords2(3);

	float *cd1 = from->fCoords;
	float *cd2 = to->fCoords;

	for (int i=0; i<3; i++)
		Coords1[i] = cd1[i];
	for (int i=0; i<3; i++)
		Coords2[i] = cd2[i];

	len = sqrt( (Coords2[0]-Coords1[0])*(Coords2[0]-Coords1[0]) + (Coords2[1]-Coords1[1])*(Coords2[1]-Coords1[1]) + (Coords2[2]-Coords1[2])*(Coords2[2]-Coords1[2]) );
	Coords2[0] = Coords2[0]-Coords1[0]; Coords2[1] = Coords2[1]-Coords1[1]; Coords2[2] = Coords2[2]-Coords1[2];
	Coords1[0] = Coords1[0]-Coords1[0]; Coords1[1] = Coords1[1]-Coords1[1]; Coords1[2] = Coords1[2]-Coords1[2];

	//Figure out direction cosines
	float len1 = sqrt( (Coords2[0]-Coords1[0])*(Coords2[0]-Coords1[0])
					+ (Coords2[1]-Coords1[1])*(Coords2[1]-Coords1[1])
					+ (Coords2[2]-Coords1[2])*(Coords2[2]-Coords1[2]) );

	float cosines[3];
	cosines[0] = 0;  cosines[1] = Coords2[1]/len1; cosines[2] = Coords2[2]/len1;
	float d = sqrt(cosines[1]*cosines[1] + cosines[2]*cosines[2]);

	//THIS FOR THE WEB PAGE METHOD OF ROTATION

	zRot1 = ARCFIX*acos(Coords2[2]/len);

	if (Coords2[2] <= 0.0) {
		zRot1 = -zRot1;
	}


	xAxis = -Coords2[1]*Coords2[2];
	yAxis = Coords2[0]*Coords2[2];
	//THIS IS THE END OF THE WEB PAGE ROTATION METHOD

	if (order > 2) {
		atom *af = from;
		//atom *at = to;
		atom *dbTemp = NULL;;
		//float zRot = 0;
		if (af->atoms.size() != 0) {
			for (unsigned int i=0; i<af->atoms.size(); i++) {
				if (af->atoms[i] != to) {
					dbTemp = af->atoms[i];
					break;
				}
			}
		}
		if (dbTemp != NULL) {
			float *Coords3 = dbTemp->fCoords;
			float tmp[3];
			cout <<"Yep you are here: " << endl;
			//for (int j=0;j<3; j++) {
			//	cout << tmp1[j] << endl;
			//}
			//int test = 0;
			//cin >> test;
			tmp[0] =  Coords3[0] - Coords1[0];
			tmp[1] =  Coords3[1] - Coords1[1];
			tmp[2] =  Coords3[2] - Coords1[2];

			float Cross1[3], Cross2[3];
			float tmp1[] = {0.0, 0.0, 0.0};

			Cross1[0] = (tmp[1]*Coords2[2])-(tmp[2]*Coords2[1]);// - Coords1[0];
			Cross1[1] = (tmp[2]*Coords2[0])-(tmp[0]*Coords2[2]);// - Coords1[1];
			Cross1[2] = (tmp[0]*Coords2[1])-(tmp[1]*Coords2[0]);// - Coords1[2];

			Cross2[0] = (Cross1[1]*tmp1[2])-(Cross1[2]*tmp1[1]);// - Coords1[0];
			Cross2[1] = (Cross1[2]*tmp1[0])-(Cross1[0]*tmp1[2]);// - Coords1[1];
			Cross2[2] = (Cross1[0]*tmp1[1])-(Cross1[1]*tmp1[0]);// - Coords1[2];

			float Cross2Mag = sqrt(Cross2[0]*Cross2[0] + Cross2[1]*Cross2[1] + Cross2[2]*Cross2[2]);

			Cross2[0] /= (Cross2Mag/.10) + Coords1[0];
			Cross2[1] /= (Cross2Mag/.10) + Coords1[1];
			Cross2[2] /= (Cross2Mag/.10) + Coords1[2];
		}
	}
	*/
}

}
