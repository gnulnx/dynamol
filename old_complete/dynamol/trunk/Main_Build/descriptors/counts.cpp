/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "counts.h"
#include <iostream>
#include "../dynatype/molecule.h"
#include "../dynatype/bond.h"
#include "../dynatype/atom.h"

//Dynamol Type Library Includes
#include "../dynatype/molecule.h"
#include "../dynatype/bond.h"
#include "../dynatype/atom.h"
using namespace std;

Counts::Counts()
: Constitutional()
{
   //vector<int> BC(3);
   //vector<int> ANC;
   //vector<QString> gaffC;  
}



Counts::~Counts()
{
}


//void Counts::calcDesc(set<QString> &desc, dt::molecule *mol) {
void Counts::calcDesc(set<QString> &desc, dt::molPtr mol) {
   clearCounts();
   countBondTypes(mol);
   countAtomTypes(mol);
   
   set<QString>::iterator si;// = desc.begin();
   for (si=desc.begin(); si != desc.end(); si++) {
      QString funcName = *si;
      if (funcName == "nTriple") {
         mol->propMap[funcName] = nBond(mol, 3).latin1();
      }
      else if (funcName == "nDouble") {
         mol->propMap[funcName] = nBond(mol, 2).latin1();
      }
      else if (funcName == "nSingle") {
         mol->propMap[funcName] = nBond(mol, 1).latin1();
      }
      else if (funcName == "Hyd_Heavy_Ratio") {
         float ratio = hAtomCount/totalAtomCount;
         QString num; num.setNum(ratio);
         mol->propMap[funcName] = num.latin1();
      }
      else if (funcName == "nCarbon") {
         mol->propMap[funcName] = nAtom(mol, 6).latin1();
      }
      else if (funcName == "nNitrogen") {
         mol->propMap[funcName] = nAtom(mol, 7).latin1();
      }
      else if (funcName == "nOxygen") {
         mol->propMap[funcName] = nAtom(mol, 8).latin1();
      }
      else if (funcName == "nSulfer") {
         mol->propMap[funcName] = nAtom(mol, 16).latin1();
      }
      else if (funcName == "nPhosporus") {
         mol->propMap[funcName] = nAtom(mol, 15).latin1();
      }
      else if (funcName == "nChlorine") {
         mol->propMap[funcName] = nAtom(mol, 17).latin1();
      }
      else if (funcName == "nFlourine") {
         mol->propMap[funcName] = nAtom(mol, 9).latin1();
      }
      else if (funcName == "nBromine") {
         mol->propMap[funcName] = nAtom(mol, 35).latin1();
      }
      else if (funcName == "nIodine") {
         mol->propMap[funcName] = nAtom(mol, 53).latin1();
      }
      else if (funcName == "nHydrogen") {
         mol->propMap[funcName] = nAtom(mol, 1).latin1();
      }
      
   }
   ////cout <<"Leaving Counts::calcDesc"<<endl;
}

void Counts::clearCounts() {
   BC.clear();
   ANC.clear();
   gaffC.clear();
   totalAtomCount = 0;
   hAtomCount = 0;
   
   BC.resize(3);
   for (unsigned int i=0; i<BC.size(); i++) 
      BC[i] = 0;
       
   ANC.resize(118);
   for (unsigned int i=0; i<ANC.size(); i++)
      ANC[i] = 0;
      
   

}

//void Counts::countBondTypes(dt::molecule *mol) {
void Counts::countBondTypes(dt::molPtr mol) {
   for (unsigned int i=0; i<mol->bonds.size();  i++) {
      int order = mol->bonds[i]->order;
      BC[order-1]++; 
   }
}

//void Counts::countAtomTypes(dt::molecule *mol) {
void Counts::countAtomTypes(dt::molPtr mol) {
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      int an = mol->atoms[i]->getAN();
      if (an == 1) 
         hAtomCount++;
      else
         totalAtomCount++;
         
      QString ft = mol->atoms[i]->type;
      ANC[an-1]++;
   }
}


/*
void Counts::inputParser(set<QString> &input) {

}
*/

//QString Counts::nBond(dt::molecule *mol, int order) {
QString Counts::nBond(dt::molPtr mol, int order) {
   QString num;
   num.setNum(BC[order-1]);
   return num;
}

//QString Counts::nAtom(dt::molecule *mol, int AN) {
QString Counts::nAtom(dt::molPtr mol, int AN) {
   QString num;
   num.setNum(ANC[AN-1]);
   return num;
}






