/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "functional_groups.h"
#include "../dynatype/molecule.h"
#include "../dynatype/atom.h"

Functional_Groups::Functional_Groups()
 : Desc()
{
}


Functional_Groups::~Functional_Groups()
{
}

//void Functional_Groups::calcDesc(set<QString> &desc, dt::molecule *mol) {
void Functional_Groups::calcDesc(set<QString> &desc, dt::molPtr mol) {
   set<QString>::iterator si;// = desc.begin();
   for (si=desc.begin(); si != desc.end(); si++) {
      QString funcName = *si;
      if (funcName == "nEsters") {
         mol->propMap[funcName] = countType("os", mol).latin1();
      }
      else if (funcName == "nOH") {
         mol->propMap[funcName] = countType("oh", mol).latin1();
      }
      else if (funcName == "nSH") {
         mol->propMap[funcName] = countType("sh", mol).latin1();
      }
   }
}


//QString Functional_Groups::countType(string type, dt::molecule *mol) {
QString Functional_Groups::countType(string type, dt::molPtr mol) {
   int count = 0;
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      if (mol->atoms[i]->type == type)
         count++;
   }
   QString num; num.setNum(count);
   return num;
}


