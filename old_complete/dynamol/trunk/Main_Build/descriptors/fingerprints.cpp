/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "fingerprints.h"
#include <iostream>

//Dynamol Type Library Includes
#include "../dynatype/molecule.h"

using namespace std;

FingerPrints::FingerPrints()
 : Desc()
{
   gs.readSubSets(-1);
}


FingerPrints::~FingerPrints()
{
}

//void FingerPrints::calcDesc(set<QString> &desc, dt::molecule *mol) {
void FingerPrints::calcDesc(set<QString> &desc, dt::molPtr mol) {
   ////cout <<"CalcDesc"<<endl;
   set<QString>::iterator si;// = desc.begin();
   for (si=desc.begin(); si != desc.end(); si++) {
      QString funcName = *si;
      if (funcName == "gafffp") {
         mol->propMap["gafffp"] = gs.runMol(mol, 3, true);
      }
   }
}



