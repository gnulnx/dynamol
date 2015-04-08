/***************************************************************************
                          molecule.cpp  -  description
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
#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "linAlg.h"
#include "enumTypes.h"

namespace dynamol {

molecule::~molecule() {}

molecule::molecule(string name)
: DyObject()
{
	this->name = name;
	PyObject = false;
	Center[0] = Center[1] = Center[2] = 0.0;
}

molecule::molecule(int PyObject) 
: DyObject()
{
    cout <<"You are in molecule::molecule(int PyObject): "<< this << endl;
	this->PyObject = PyObject;
	Center[0] = Center[1] = Center[2] = 0.0;
    this->name = "Python molecule";
}

molecule::molecule(const molecule &mol)
: DyObject()
{
	
	name = mol.name;
	PyObject = false;
	BondArraySize = mol.BondArraySize;
	BondVertexArray = mol.BondVertexArray;
	BondColorArray = mol.BondColorArray;

	AtomArraySize = mol.AtomArraySize;
	AtomVertexArray = mol.AtomVertexArray;
	AtomColorArray = mol.AtomColorArray;

	TriangleArraySize = mol.TriangleArraySize;
	StickTriangleArray = mol.StickTriangleArray;
	StickNormalArray = mol.StickNormalArray;
	StickColorArray = mol.StickColorArray;

	for (int i=0; i<3; i++)
		Center[i] = mol.Center[i];

	for (int i=0; i<mol.atoms.size(); i++) {
		atom *ATM = mol.atoms[i];
		atom *atm = addAtom(ATM->num, ATM->symbol, ATM->fCoords[0], ATM->fCoords[1], ATM->fCoords[2]);		
	}

	for (int i=0; i<mol.bonds.size(); i++) {
		bond *BD = mol.bonds[i];
		bond *bd = addBond(BD->num, BD->from->num, BD->to->num, BD->order);
	}
}

void molecule::SetName(string name)
{	this->name = name; }

vector<atom> molecule::getAtomObjs() {
	AtomObjs.clear();
	for (int i=0; i<atoms.size(); i++)
		AtomObjs.push_back(*atoms[i]);

	return AtomObjs;
}

vector<bond> molecule::getBondObjs() {
	BondObjs.clear();
	for (int i=0; i<bonds.size(); i++) 
		BondObjs.push_back(*bonds[i]);

	return BondObjs;
}

atom *molecule::addAtom(int num, string symbol, float x, float y, float z, int atomicNum) {
	//NOTE: You need to find a faster safer way to check for dups...try a map or something
	/*
	for (int i=0; i<atoms.size(); i++) {
		//if (atoms[i]->getNum() == num) {
		if (atoms[i]->num == num) {
			return NULL;
		}
	}
	*/
	atom *at = new dynamol::atom(num, symbol, x, y, z, atomicNum);
	atoms.push_back(at);
	at->parent = this;
	return at;
}

bond *molecule::addBond(int num, int from, int to, int order) {
	atom *hold1, *hold2;
	
	// THIS IS FAST CHECK CODE RIGHT HERE
	hold1 = atoms[from-1];
	hold2 = atoms[to-1];
	hold1->addAtom(hold2);
	hold2->addAtom(hold1);
	bond *bd = new bond(num, hold1, hold2, order);
	bd->parent = this;
	bonds.push_back(bd);
	
	
	bd->parent = this;
	return bd;
}             

vector<float> molecule::getCenter() {
	vector<float> Center;
	Center.resize(3);
	float totX, totY, totZ;
    totX = totY = totZ = 0.0;

    for (unsigned int i=0; i<atoms.size(); i++) {
        atom *atm = atoms[i];
        totX += atm->fCoords[0];
        totY += atm->fCoords[1];
        totZ += atm->fCoords[2];
    }

    Center[0] = totX/atoms.size();
    Center[1] = totY/atoms.size();
    Center[2] = totZ/atoms.size();
	
	return Center;
}



void molecule::CenterMol() {
	vector<float> C = getCenter();	
	Center[0] = C[0];
	Center[1] = C[1];
	Center[2] = C[2];
	
	for (unsigned int i=0; i<atoms.size(); i++) {
		atom *atm = atoms[i];
		float *cd = atm->fCoords;
		cd[0] = cd[0] - Center[0];
		cd[1] = cd[1] - Center[1];
		cd[2] = cd[2] - Center[2];
	}

}

void molecule::DeCenterMol() {
	
	for (unsigned int i=0; i<atoms.size(); i++) {
		atom *atm = atoms[i];
		float *cd = atm->fCoords;
		cd[0] = cd[0] - Center[0];
		cd[1] = cd[1] - Center[1];
		cd[2] = cd[2] - Center[2];
	}	

}

void molecule::SetNewCenter(float x, float y, float z)
{
	for (int i=0; i<BondVertexArray.size(); i=i+3) {
		BondVertexArray[i] -= x;
		BondVertexArray[i+1] -= y;
		BondVertexArray[i+2] -=z;
	}
}

void molecule::BuildVertexArrays(RenderType modelType, vector<float> &center) {
	if (modelType == WIRE)
		WireFrameModel(center);

	StickModel(center);
}

void molecule::WireFrameModel(vector<float> &center) {
	//####### SECTION 1.  Build Bond Vertex Array's #############
	BondVertexArray.clear();
	BondColorArray.clear();
	BondArraySize = 0;
	for (unsigned int i=0; i<bonds.size(); i++) {
		bond *bd = bonds[i];
		atom *from = bd->from;
		atom *to = bd->to;
		float *fColor = from->COLOR;
		float *tColor = to->COLOR;
			
		float c1[3], c2[3], midPoint[3];
		for (int j=0; j<3; j++) {
			c1[j] = from->fCoords[j] - center[j];
			c2[j] = to->fCoords[j] - center[j];
			midPoint[j] = 0.5*(c1[j]+c2[j]);
		}
		
		if (bd->order == 1 || bd->order == 3) {	
			if ((fColor[0] == tColor[0]) && (fColor[1] == tColor[1]) && (fColor[2] == tColor[2])) {	
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(c1[j]);
					BondColorArray.push_back(from->COLOR[j]);
				}
		
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(c2[j]);
					BondColorArray.push_back(to->COLOR[j]);
				}
				BondArraySize += 2;
			} else {
				for (int j=0; j<3; j++) 
					midPoint[j] = (c1[j]+c2[j])*0.5;
				
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(c1[j]);
					BondColorArray.push_back(from->COLOR[j]);
				}

				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(midPoint[j]);
					BondColorArray.push_back(from->COLOR[j]);
				}

				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(midPoint[j]);
					BondColorArray.push_back(to->COLOR[j]);
				}

				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(c2[j]);
					BondColorArray.push_back(to->COLOR[j]);
				}

				BondArraySize += 4;
			}
		} 
		if (bd->order > 1) {
			atom *dbTemp = NULL;;
			if (from->atoms.size() != 0) {
				for (unsigned int i=0; i<from->atoms.size(); i++) {
					if (from->atoms[i] != to) {
						dbTemp = from->atoms[i];
						break;
					}
				}
			}
			if (dbTemp == NULL) {
				if (to->atoms.size() != 0) {
					for (unsigned int i=0; i<to->atoms.size(); i++) {
						if (to->atoms[i] != from) {
							dbTemp = to->atoms[i];
							break;
						}
					}
				}
			}
			
			float tmp[3], tmp1[3];	
			float *Coords1 = c1;//from->fCoords;
			float *Coords2 = c2;//to->fCoords;
			float Cross1[3], Cross2[3];
			float MP1[3], MP2[3];
			if (dbTemp != NULL) {
				float Coords3[3];
				for (int j=0; j<3; j++)
					Coords3[j] = dbTemp->fCoords[j];

				tmp[0] =  Coords3[0] - Coords1[0];
				tmp[1] =  Coords3[1] - Coords1[1];
				tmp[2] =  Coords3[2] - Coords1[2];

				tmp1[0] =  Coords2[0] - Coords1[0];
				tmp1[1] =  Coords2[1] - Coords1[1];
				tmp1[2] =  Coords2[2] - Coords1[2];

				midPoint[0] =tmp1[0]*0.5;
				midPoint[1] =tmp1[1]*0.5;
				midPoint[2] =tmp1[2]*0.5;

				Cross1[0] = (tmp[1]*tmp1[2])-(tmp[2]*tmp1[1]);
				Cross1[1] = (tmp[2]*tmp1[0])-(tmp[0]*tmp1[2]);
				Cross1[2] = (tmp[0]*tmp1[1])-(tmp[1]*tmp1[0]);

				Cross2[0] = (Cross1[1]*tmp1[2])-(Cross1[2]*tmp1[1]);
				Cross2[1] = (Cross1[2]*tmp1[0])-(Cross1[0]*tmp1[2]);
				Cross2[2] = (Cross1[0]*tmp1[1])-(Cross1[1]*tmp1[0]);

				float Cross2Mag = sqrt(Cross2[0]*Cross2[0] + Cross2[1]*Cross2[1] + Cross2[2]*Cross2[2]);
				Cross2Mag = .05/Cross2Mag;
				Cross2[0] *= (Cross2Mag);
				Cross2[1] *= (Cross2Mag);
				Cross2[2] *= (Cross2Mag);

				for (int j=0; j<3; j++) {
					MP1[j] = 0.5*((Cross2[j]+Coords1[j])+(Cross2[j]+Coords2[j]));
					MP2[j] = 0.5*((-Cross2[j]+Coords1[j])+(-Cross2[j]+Coords2[j]));
				}
				
			} 

			if (fColor[0] == tColor[0] && fColor[1] == tColor[1] && fColor[2] == tColor[2]) {
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(Cross2[j]+Coords1[j]);
					BondColorArray.push_back(from->COLOR[j]);	
				}
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(Cross2[j]+Coords2[j]);
					BondColorArray.push_back(to->COLOR[j]);
				}
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(-Cross2[j]+Coords1[j]);
					BondColorArray.push_back(from->COLOR[j]);
				}
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(-Cross2[j]+Coords2[j]);
                    BondColorArray.push_back(to->COLOR[j]);
				}
				BondArraySize +=4;
			} else {	
				
				//Draw First half
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(Cross2[j]+Coords1[j]);
					BondColorArray.push_back(from->COLOR[j]);
				}
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(MP1[j]);
					BondColorArray.push_back(from->COLOR[j]);	
				}
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(MP1[j]);
					BondColorArray.push_back(to->COLOR[j]);
				}
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(Cross2[j]+Coords2[j]);
					BondColorArray.push_back(to->COLOR[j]);
				}
				
				//Draw Second Half
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(-Cross2[j]+Coords1[j]);
					BondColorArray.push_back(from->COLOR[j]);
				}
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(MP2[j]);
					BondColorArray.push_back(from->COLOR[j]);
				}
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(MP2[j]);
					BondColorArray.push_back(to->COLOR[j]);
				}
				for (int j=0; j<3; j++) {
					BondVertexArray.push_back(-Cross2[j]+Coords2[j]);
					BondColorArray.push_back(to->COLOR[j]);
				}	
				BondArraySize += 8;
			}
		}
	}	

	//######### SECTION 2.  Build Atom Vertex Array's ########
	AtomVertexArray.clear();
	AtomColorArray.clear();
	AtomArraySize = 0;
	for (int i=0; i<atoms.size(); i++) {
		float c1[3];
        for (int j=0; j<3; j++) {
            c1[j] = atoms[i]->fCoords[j] - center[j];
			AtomVertexArray.push_back(c1[j]);
			AtomColorArray.push_back(atoms[i]->COLOR[j]);
        }
		AtomArraySize += 1;
	}

}
void molecule::StickModel(vector<float> &center) {
	solidCylinder(1.2, -5.0, 2.3, 1.0, 10.0, 10);	
}

void molecule::solidCylinder(double tx, double ty, double tz, double radius, double height, int n_subdivision_steps)
{
	TriangleArraySize = 0;
	int i,n;
	double theta, d_theta;
	double z_bottom,z_top;
	int MAX_NUM_SUBDIVISION = 1000;
	double px[MAX_NUM_SUBDIVISION],py[MAX_NUM_SUBDIVISION];
	double nx[MAX_NUM_SUBDIVISION],ny[MAX_NUM_SUBDIVISION];

	n = (n_subdivision_steps > MAX_NUM_SUBDIVISION) ? MAX_NUM_SUBDIVISION : n_subdivision_steps;

	/* approximation of the circle with polyline */
	d_theta = 2*PI/n;
	for(theta=0,i=0;i<n;++i, theta+=d_theta)
	{
		nx[i] = radius*cos(theta);
		ny[i] = radius*sin(theta);
		px[i] = nx[i]+tx;
		py[i] = ny[i]+ty;

		StickTriangleArray.push_back(px[i]);
		StickTriangleArray.push_back(py[i]);
		StickTriangleArray.push_back(z_bottom);

		StickNormalArray.push_back(nx[i]);
		StickNormalArray.push_back(ny[i]);
		StickNormalArray.push_back(0);	

		StickColorArray.push_back(0.0);
		StickColorArray.push_back(0.0);
		StickColorArray.push_back(1.0);	

		StickTriangleArray.push_back(px[i]);
		StickTriangleArray.push_back(py[i]);
		StickTriangleArray.push_back(z_top);
	
		StickNormalArray.push_back(nx[i]);
		StickNormalArray.push_back(ny[i]);
		StickNormalArray.push_back(0);

		StickColorArray.push_back(0.0);
		StickColorArray.push_back(0.0);
		StickColorArray.push_back(1.0);

		TriangleArraySize += 2;	
	}

	/* cylinder is centered at 0,0,0 and is aligned along Z */
	z_top = tz+height;
	z_bottom = tz;
}

} //End Namespace
