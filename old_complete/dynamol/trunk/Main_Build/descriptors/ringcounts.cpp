/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "ringcounts.h"
#include <iostream>
#include <iomanip>

//Dynamol Type Library Includes
#include "../dynatype/molecule.h"
#include "../dynatype/dtype.h"

using namespace std;
ringCounts::ringCounts()
:Counts()
{
}


ringCounts::~ringCounts()
{
}
//void ringCounts::calcDesc(set<QString> &desc, molecule *mol) {
void ringCounts::calcDesc(set<QString> &desc, dt::molPtr mol) {
   ////cout <<"Counts::calcDesc  "<< desc.size() << endl;
   clearCounts();
   countRingTypes(mol);
   
   set<QString>::iterator si;// = desc.begin();
   for (si=desc.begin(); si != desc.end(); si++) {
      QString funcName = *si;
      ////cout <<"FUNC NAME IS "<<funcName << endl;
      if (funcName == "ring3") {
         mol->propMap[funcName] = nRings(mol, 3).latin1();
      }
      else if (funcName == "ring4") {
         mol->propMap[funcName] = nRings(mol, 4).latin1();
      }
      else if (funcName == "ring5") {
         mol->propMap[funcName] = nRings(mol, 5).latin1();
      }
      else if (funcName == "ring6") {
         mol->propMap[funcName] = nRings(mol, 6).latin1();
      }
      if (funcName == "ring7") {
         mol->propMap[funcName] = nRings(mol, 7).latin1();
      }
      if (funcName == "ring8") {
         mol->propMap[funcName] = nRings(mol, 8).latin1();
      }
      if (funcName == "ring9") {
         mol->propMap[funcName] = nRings(mol, 9).latin1();
      }
      if (funcName == "ring10") {
         mol->propMap[funcName] = nRings(mol, 10).latin1();
      }
      else if (funcName == "aroCount") {
         mol->propMap[funcName] = nRings(mol, 0).latin1();
      }
   }
      
}
void ringCounts::clearCounts() {
   rCounts.clear();
   
   rCounts.resize(12);
   for (unsigned int i=0; i<rCounts.size(); i++) 
      rCounts[i] = 0;
}

//void ringCounts::countRingTypes(molecule *mol) {
void ringCounts::countRingTypes(dt::molPtr mol) {
   for (unsigned int i=0; i<mol->sortedRings.size(); i++) {
      unsigned int ringSize = mol->sortedRings[i].size();
      if ( ringSize < rCounts.size())
         rCounts[ringSize]++;
   }
   dt::dType dt;
   rCounts[0] = dt.aromaticRingCount(mol);
}

//QString ringCounts::nRings(molecule *mol, int size) {
QString ringCounts::nRings(dt::molPtr mol, int size) {
   QString num;
   num.setNum(rCounts[size]);
   return num;
}



