/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "scriptatom.h"
#include "atom.h"
#include <qvaluelist.h>
scriptatom::scriptatom(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
   atom *atm = NULL;
}


scriptatom::~scriptatom()
{
   atoms.clear();
}

void scriptatom::setAtom(atom *atm) { 
   this->atm = atm;
}


void scriptatom::printName() {
  if (atm != NULL) {
      ////cout << atm->getSym() << endl;
  }
}

bool scriptatom::isSelected() {
   return atm->isSelected();
}

void scriptatom::setCoords(QVariant array) {
   QValueList<QVariant> list = array.toList();
   atm->fCoords[0] = list[0].toDouble();
   atm->fCoords[1] = list[1].toDouble();
   atm->fCoords[2] = list[2].toDouble();
}

QVariant scriptatom::getCoords() {
   QValueList<QVariant> vl;
   vl.push_back(atm->fCoords[0]);
   vl.push_back(atm->fCoords[1]);
   vl.push_back(atm->fCoords[2]);

   QVariant v(vl);
   return v;
}

void scriptatom::setCharge(double charge) {
   atm->setCharge(charge);
}

double scriptatom::getCharge() {
   return atm->getCharge();
}

void scriptatom::setX( const double &x ) {atm->fCoords[0] = x;};
double scriptatom::getX() const {return atm->fCoords[0];};
   
void scriptatom::setY( const double &x ) {atm->fCoords[1] = x;};
double scriptatom::getY() const {return atm->fCoords[1];};
  
void scriptatom::setZ( const double &x ) {atm->fCoords[2] = x;};
double scriptatom::getZ() const {return atm->fCoords[2];};


QString scriptatom::getSym() 
{ return atm->getSymbol(); };

QString scriptatom::getType() 
{ return atm->getFFType(); }

int scriptatom::getNum()
{ return atm->getNum(); }

int scriptatom::atomicNum()
{ return atm->getAN(); }

double scriptatom::getMass() 
{ return atm->getMass(); }

double scriptatom::getPartialCharge() 
{ return atm->getCharge(); }

int scriptatom::getFormalCharge()
{ return atm->formalCharge; }

void scriptatom::setFormalCharge(int formalCharge)
{ atm->formalCharge = formalCharge; }

int scriptatom::getAtomsSize() 
{ return atm->atoms.size(); }

int scriptatom::numOfAtoms() 
{ return atm->atoms.size(); }

scriptatom *scriptatom::getAtom(int index) { 
   if (index >= atm->atoms.size()) {return NULL;}//return NULL;
   else {
      scriptatom *sAtm  = new scriptatom;
      sAtm->atm = atm->atoms[index];
      return sAtm;
   }
}

int scriptatom::vertexDegree() {
   if (atm->getAtomicNum() == 1)
      return 0;
      
   int count = 0;
   for (int i=0; i< atm->atoms.size(); i++) {
      atom *tmp = atm->atoms[i];
      if (tmp->getAtomicNum() != 1) 
         count++;
   }
   return count;
}

int scriptatom::valenceVertexDegree() {
  
   int Zv = valenceCount();
   int Z  = atomicNum();
   int H  = hydrogenCount();
   
   return (Zv - H) / (Z - Zv - 1);
   
}

int scriptatom::valenceCount() {
   if (atm->getAtomicNum() == 6) //carbon
      return 4;
   else if (atm->getAtomicNum() == 1) //hydrogen
      return 1;
   else if (atm->getAtomicNum() == 7) //nitrogen
      return 5;
   else if (atm->getAtomicNum() == 8) //oxygen
      return 6;
   else if (atm->getAtomicNum() == 16) //sulfer
      return 6;
   else if (atm->getAtomicNum() == 34) //selenium
      return 6;
   else if (atm->getAtomicNum() == 9) //flourine
      return 7;
   else if (atm->getAtomicNum() == 17) //chlorine
      return 7;
   else if (atm->getAtomicNum() == 35) //bromine 
      return 7;
   else if (atm->getAtomicNum() == 53) //iodine 
      return 7;
   else if (atm->getAtomicNum() == 15) //phosphorus 
      return 5;
   else if (atm->getAtomicNum() == 14) //silicone 
      return 4;
   else if (atm->getAtomicNum() == 5) //Borone
      return 3;
   else {
      //////////cout <<"Missing type for AN "<< atm->getAtomicNum() << "   scriptatom"<<endl;
      return 0;
   }  
}


int scriptatom::hydrogenCount() {
   int count = 0;
   for (int i=0; i<atm->atoms.size(); i++) {
      if (atm->atoms[i]->getAtomicNum() == 1) {
         count++;
      }
   }
   return count;
}

int scriptatom::pQN() {
   if ( atomicNum() <3) 
      return 1;
   
   if (atomicNum() >= 3 && atomicNum() <= 10)
      return 2;
   
   if (atomicNum() >= 11 && atomicNum() <=18)
      return 3;
   
   if (atomicNum() >=19 && atomicNum() <= 36)
      return 4;
      
   if (atomicNum() >=37 && atomicNum() <= 54)
      return 5;
      
   if (atomicNum() >=55 && atomicNum() <= 86)
      return 6;
}







































