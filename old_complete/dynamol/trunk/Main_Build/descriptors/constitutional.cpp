/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "constitutional.h"
#include <iostream>
using namespace std;

//Dynamol Type Library Includes
#include "../dynatype/molecule.h"

Constitutional::Constitutional()
: Desc()
{
   
}


Constitutional::~Constitutional()
{
}

//void Constitutional::calcDesc(set<QString> &desc, molecule *mol) {
void Constitutional::calcDesc(set<QString> &desc, dt::molPtr mol) {
  set<QString>::iterator si = desc.begin();
   for (si; si != desc.end(); si++) {
      QString funcName = *si;
      if (funcName == "molWeight") {
         molWeight(mol);
      }
   }
  
}

//void Constitutional::molWeight(molecule *mol) {
void Constitutional::molWeight(dt::molPtr mol) {
   float wt = mol->molWeight();
   QString num; num.setNum(wt);
   mol->propMap["molWeight"] = num.latin1();
}



