/***************************************************************************
                          bond.cpp  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include "bond.h"
#include "atom.h"
#include <fstream>
using namespace std;

int bond::bondsCreated = 0;
int bond::bondsDelete = 0;
bond::bond() {}
bond::bond(int num, atom *from, atom *to,  int order)
: Object()
{
  bondsCreated++;
  parent = NULL;
  this->num = num;
  this->from = from;
  this->to = to;
  //item = NULL;
  this->order = order;
  this->renderType = WIRE;
  selected = false;
  this->bcc = "no";
  this->defInc = 30.0; //used to specify default rotation for conf search dialog
  rotable = false;
  
  //Get Coords from atoms so that the length of the bond can be determined
  vector<float> Coord1, Coord2;
  from->getCoords(Coord1);
  to->getCoords(Coord2);

  calcDirCosines();
 
}
bond::~bond(){
}

bond &bond::operator=(const bond &bd) {
   if (this == &bd) return *this;
}

int bond::fromNum() 
{return from->getNum();};
string          bond::fromSym()                               {return from->getSym();};
atom            *bond::fromAtom()                             {return from;};

int             bond::toNum()                                 {return to->getNum();};
string          bond::toSym()                                 {return to->getSym();};
atom            *bond::toAtom()                               {return to;};
int             bond::getOrder()                              {return order;};

BONDRENDER      bond::getRenderType()                         {return renderType;};
void            bond::setRenderType(BONDRENDER renderType)    {this->renderType = renderType;};

int bond::getNum()  
{ return this->num; }


void            bond::setBondNum(int num)                     {this->num = num;};

//float bond::getCosineD() 
//{return this->d;};

//float           bond::getCosineLen()                              {return this->len;};

void bond::setOrder(int order) 
{ this->order = order; }

void bond::setNum(int num) 
{ this->num = num; }

int bond::rtti() 
{return 9;}

void bond::setSelected(bool selected)   {this->selected = selected;}

bool bond::isRotable()   {return rotable;}
void bond::setRotable(bool rot)   {this->rotable = rot;}
  
  
float bond::bondLength() {
   float length = 0;//distance(from->fCoords, to->fCoords);
   
   for (int i=0; i<3; i++) {
   	length += (from->fCoords[i]-to->fCoords[i]) * (from->fCoords[i]-to->fCoords[i]);
   }
   length = sqrt(length);
   return length;
}

void bond::updateBond() {
    //calcMidPoint();
    calcDirCosines();
    
    float *cd1, *cd2;
    cd1 = from->fCoords;
    cd2 = to->fCoords;
    //length = 0;
    //for (int i=0; i<3; i++) {
    //   length += (cd1[i] - cd2[i]) * (cd1[i]- cd2[i]);
    //}
    //length = sqrt(length);
    
}

int bond::getAtomNum(atom *at) {
  if (at == from)
    return to->getNum();
  if (at == to)
    return from->getNum();

  if (at != from && at != to) {
    return -1;  //This is an error
  }
}
/*
void  bond::calcMidPoint() {

  //vector<double> c1 = from->getCoords();
  //vector<double> c2 = to->getCoords();
  float *c1 = from->fCoords;
  float *c2 = to->fCoords;

 // for (int i=0; i <3; i++) {
//  	////////////cout << c1[i] << setw(12) << cp1[i] << setw(12) << c2[i] << setw(12) << cp2[i] << endl;
 // }
  //int test = 0;
  //cin >> test;
  
  mp[0] = (c1[0] + c2[0])*0.5;
  mp[1] = (c1[1] + c2[1])*0.5;
  mp[2] = (c1[2] + c2[2])*0.5;
  //////////////cout <<"atm1  "<< from->getSym() << from->fCoords[0] << setw(10) << from->fCoords[1] << setw(10) << from->fCoords[2] << endl;
  //////////////cout <<"atm2  "<< to->getSym() << to->fCoords[0] << setw(10) << to->fCoords[1] << setw(10) << to->fCoords[2] << endl;
  //////////////cout <<"midPoint: " << mp[0] << setw(10) << mp[1] << setw(10) << mp[2] << endl;
  //////////////cout << endl;
}
*/

void  bond::calcDirCosines() {
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

  //if (Coords2[2] == 0) Coords2[2] = .0001;
  zRot1 = ARCFIX*acos(Coords2[2]/len);
    
  if (Coords2[2] <= 0.0) {
    zRot1 = -zRot1;
  }

  
  xAxis = -Coords2[1]*Coords2[2];
  yAxis = Coords2[0]*Coords2[2];
  //THIS IS THE END OF THE WEB PAGE ROTATION METHOD

  if (order > 2) {
      atom *af = from;
      atom *at = to;
      atom *dbTemp = NULL;;
      float zRot = 0;
      if (af->atoms.size() != 0) {
        for (unsigned int i=0; i<af->atoms.size(); i++) {
          if (af->atoms[i] != to) {
            dbTemp = af->atoms[i];
            break;
          }
        }
      }
      if (/*order == 2 && */dbTemp != NULL) {
        float *Coords3 = dbTemp->get_fCoords();
        float tmp[3];

        tmp[0] =  Coords3[0] - Coords1[0];
        tmp[1] =  Coords3[1] - Coords1[1];
        tmp[2] =  Coords3[2] - Coords1[2];

        float Cross1[3], Cross2[3], tmp1[3];
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
}







































