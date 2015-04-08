/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "atomsig2.h"
#include <iostream>
#include <qstringlist.h>
#include <map>

//Dynamol Type Library Includes
#include "../dynatype/molecule.h"

using namespace std;

atomSig2::atomSig2()
 : atomEnv()
{
}


atomSig2::~atomSig2()
{
}

//void atomSig2::calcDesc(set<QString> &desc, dt::molecule *mol) {
void atomSig2::calcDesc(set<QString> &desc, dt::molPtr mol) {
   QString gds = gs.runMol(mol, 2, false);

   QStringList gList = QStringList::split(" ", gds);

   // Setup the count vector
   vector<int> countVec(100000);
   for (int i=0; i<100000; i++) {
      countVec[i] = 0;
   }

   //convert fingerprint to int and increment countVec indices
   ////cout <<"Converting: " << mol->name <<" to fpNums"<<endl;
   for (unsigned int i=0; i<gList.size(); i++) {
      int num = gList[i].toInt();
      //cout << num << " ";
      if (num != -1 && num < (int)countVec.size()) {
         countVec[num]++;
      }
   }
   //Now start calculating the descriptors
   
   set<QString>::iterator si;// = desc.begin();
   for (si=desc.begin(); si != desc.end(); si++) {
       QStringList qList = QStringList::split("_", *si);
       int num = qList[1].toInt();
       if (num != -1 && num < (int)countVec.size()) {
          QString qNum; qNum.setNum(countVec[num-1]);
          mol->propMap[*si] = qNum.latin1();
       }       
   }
  
}



