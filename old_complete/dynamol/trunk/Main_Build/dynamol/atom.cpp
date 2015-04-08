/***************************************************************************
                          atom.cpp  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include "atom.h"
#include "molecule.h"
#include "bond.h"
#include <fstream>
using namespace std;

int atom::atomsCreated = 0;
int atom::atomsDeleted = 0;

atom::atom(int num, string symbol, float x, float y, float z, int atomicNum)
: Object()
//dynabase::ATOM(num, symbol, x, y, z, atomicNum)
{
   _base.reset( new dynabase::atom(num, symbol, x, y, z, atomicNum) );
  this->fCoords = _base->fCoords;

  atomsCreated++;
  parent = NULL;
  //item = NULL;
  forces[0] = 0;
  forces[1] = 0;
  forces[2] = 0;
  zeroForces();
  //Set atom properties
  this->renderType  =   PNT;
  this->display     =   true;
  this->inRing      =   false;
  this->frozen      =   false;

  //Color variables 
  this->color       =   getAN();
  this->currColor =   color;

  this->selected    =   false;
  this->protType    =   NON_PROTEIN;
  _base->setCharge( 0.0 );
  this->formalCharge = 0;
  this->aromatic = false;
  this->bcc = "no";
  this->atomType = "NONE";

  //COLOR SECTION
  COLOR.resize(4);
  tmpColor.resize(4);
  defaultColor();

  visited = false;
  valence = 0;
}

atom::atom(dynabase::atomPtr basePtr) 
{
	_base = basePtr;
	fCoords = _base->fCoords;

	atomsCreated++;
	parent = NULL;
	//item = NULL;
	forces[0] = 0;
	forces[1] = 0;
	forces[2] = 0;
	zeroForces();
	//Set atom properties
	this->renderType  =   PNT;
	this->display     =   true;
	this->inRing      =   false;
	this->frozen      =   false;

	//Color variables 
	this->color       =   getAN();
	this->currColor =   color;

	this->selected    =   false;
	this->protType    =   NON_PROTEIN;
	_base->setCharge( 0.0 );
	this->formalCharge = 0;
	this->aromatic = false;
	this->bcc = "no";
	this->atomType = "NONE";

	//COLOR SECTION
	COLOR.resize(4);
	tmpColor.resize(4);
	defaultColor();

	visited = false;
	valence = 0;
}

void atom::changeType(string symbol, int atomicNum) {
   _base->changeType(atomicNum, symbol);
   this->color = getAN();
   this->currColor = color;
   defaultColor();
}

atom::~atom()
{
   //ofstream outFile("destroy.txt", ios::app);
   //outFile <<"Destroying atom: " << objectNum <<"\t"<<this<< endl;
   //_base = NULL;
}

//dynabase::atom *atom::getBase() 
//{ return _base.get(); }


//This really does nothing right now.
atom &atom::operator=(const atom &atm) {
   if (this == &atm) 
      return *this;
}


string  atom::getSym() 
{return getSymbol();}

void  atom::getCoords(vector<float> &cd) 
{ 
   cd.resize(3);
   cd[0] = fCoords[0];
   cd[1] = fCoords[1];
   cd[2] = fCoords[2];
}

ATOMRENDER atom::getRenderType() 
{ return renderType; }

void atom::setRenderType(ATOMRENDER renderType) 
{ this->renderType = renderType; }

void atom::colorByElement() 
{ this->color = getAN(); }

void atom::atomDisplay(bool display)
{this->display = display;}

bool atom::getAtomDisplay() 
{ return this->display; }

int atom::numOfConnections() 
{ return atoms.size(); }

void atom::setTemp(float temp) 
{ this->temp = temp; }

float atom::getTemp() 
{ return this->temp; }

//void atom::setItem(molListViewItem *item) 
//{ this->item = item; }

//molListViewItem *atom::getItem() 
//{ return this->item; }

int atom::rtti() 
{ return 10; }

//void atom::setCharge(float charge) 
//{ this->charge = charge; }

string atom::getAtomType() 
{ return atomType; }

void atom::setType(string atomType) 
{ this->atomType = atomType; }

void atom::zeroForces()	
{ 
   for (int i=0; i<3; i++) 
      forces[i] = 0;
}

void  atom::setParent(Object *parent)  {
  if (parent->rtti() <= 12) {
     this->parent = parent;
  }
};

float       *atom::get_fCoords()         {return fCoords;};

int atom::totalBondOrder() {
  int num = 0;
  for (int i=0; i<bonds.size(); i++) num += bonds[i]->getOrder();
  return num;
}

int atom::numOfOxygen() {
  int num = 0;
  for (int i=0; i<atoms.size(); i++) 
	if (atoms[i]->getAN() == 8) 
		num++;
  return num;
}

int atom::numOfHeavyAtoms() {
    int num = 0;
    for (int i=0; i<atoms.size(); i++) if (atoms[i]->getAN() > 1) num++;
    return num;
}

int atom::numOfHydrogens() {
    int num = 0;
    for (int i=0; i<atoms.size(); i++) if (atoms[i]->getAN() == 1) num++;
    return num;
}

bool atom::isBondedTo(atom *atm) {
  for (int i=0; i<atoms.size(); i++)
    if (atm == atoms[i]) return true;
  return false;
}

void atom::defaultColor() {
  if (currColor == 6) {
      COLOR[0] = 0.55; COLOR[1] = 0.55; COLOR[2] = 0.55;  
    } else if (currColor == 7) {
      COLOR[0] = 0.0; COLOR[1] = 0.0; COLOR[2] = 1.0;
    } else if (currColor == 8) {
      COLOR[0] = 1.0; COLOR[1] = 0.00; COLOR[2] = 0.0;
    } else if (currColor == 9) { //Flourine
      COLOR[0] = 0.0; COLOR[1] = 1.0; COLOR[2] = 0.0;
    }  else if (currColor == 1) {
      COLOR[0] = 1.0; COLOR[1] = 1.0; COLOR[2] = 1.0;
    } else if (currColor == 15) {
     COLOR[0] = 0.65; COLOR[1] = 0.05; COLOR[2] = 1.0;
    } else if (currColor == 16) {
     COLOR[0] = 1.0; COLOR[1] = 1.0; COLOR[2] = 0.0;
    } else if (currColor == 17) { //Chlorine
     COLOR[0] = 0.0; COLOR[1] = 0.50; COLOR[2] = 0.0;
    } else if (currColor == 35) { //Bromine
     COLOR[0] = 0.8; COLOR[1] = 0.10; COLOR[2] = 0.0;
    } else if (currColor == -1) {
      COLOR[0] =  0.0; COLOR[1] = 0.85; COLOR[2] = 0.0;  //Select color is now GREEN
    } else if (currColor == -2) {
      COLOR[0] =  1.0; COLOR[1] = 1.0; COLOR[2] = 0.5; //yellow for highlighted objects...bond order guessing?
    } else if (getSymbol() == "X" || getSymbol() == "x") {
       COLOR[0] = 1.0; COLOR[1] = 0.5; COLOR[2] = 0.34;
    } else {
      COLOR[0] = 0.5; COLOR[1] = 0.5; COLOR[2] = 0.5;
    }

    COLOR[3] = 1.0;  //default alpha value of 1.  This makes it so that the atom is blended correctly
    for (int i=0; i<4; i++) 
       tmpColor[i] = COLOR[i];
}

/** This function is derived from class object...you must keep it 
    || modify all the code to use this function over the next one 
*/
void atom::setSelected(bool setState, bool children) {
   setSelected(setState);
}

void  atom::setSelected(bool setState) {
   if (!setState && parent != NULL) {;
      parent->getItem()->setSelected(false);
      for (int i=0; i<4; i++) 
         COLOR[i] = tmpColor[i];
   } 
   else if (setState == true && parent != NULL) {
      if (COLOR[0] != 0.0 && COLOR[1] != 0.85 && COLOR[2] != 0.0 && COLOR[3] != 1.0) {
         for (int i=0; i<4; i++) 
            tmpColor[i] = COLOR[i];
      }
    
      COLOR[0] = 0.0; 
      COLOR[1] = 0.85; 
      COLOR[2] = 0.0; 
      COLOR[3] = 1.0;
   }
   item->setSelected(setState);
}

void atom::setCoords(float x, float y, float z) {
  fCoords[0] = x;
  fCoords[1] = y;
  fCoords[2] = z;

}

//This function returns a vector of atom numbers that are bonded to current atom
vector<int> atom::bondedAtomNum() {
   vector<int> returnVec(bonds.size());
   for (unsigned int i=0; i<bonds.size(); i++) {
      returnVec[i] = bonds[i]->getAtomNum(this);
   }

   return returnVec;
}


//I don't think that you are using this function right now
bool  atom::addAtom(atom *at) {
   for (unsigned int i=0; i<atoms.size(); i++) {
      if (atoms[i] == at)
         return false;
   }

   atoms.push_back(at);
   return true;
}






















