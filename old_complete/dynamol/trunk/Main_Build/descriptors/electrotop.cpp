/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "../dynatype/electrotopological.h" //from dynatype

//Dynamol Type Library Includes
#include "../dynatype/dtype.h"
#include "../dynatype/dtGaff.h"
#include "../dynatype/atom.h"
#include "../dynatype/molecule.h"

#include "electrotop.h"
#include <vector>
#include <iostream>
#include <iomanip>



using namespace std;

ElectroTop::ElectroTop()
 : Topo()
{
//   gaffEStateMap.clear();
//   gaffEStateCountMap.clear();
}


ElectroTop::~ElectroTop()
{
}

//void ElectroTop::calcDesc(set<QString> &desc, dt::molecule *mol) {
void ElectroTop::calcDesc(set<QString> &desc, dt::molPtr mol) {
//   gaffEStateMap.clear();
//   gaffEStateCountMap.clear();
   ////cout <<"Counts::calcDesc  "<< desc.size() << endl;
   ////cout <<"gaffEStateMap.size() "<< gaffEStateMap.size() << endl;
   ////cout <<"gaffEStateCountMap " << gaffEStateCountMap.size() << endl;
  // map<QString, float> testMap;
   ////cout <<"testMap.size(): " << endl;
   
   setGaffEStateSum(mol);
   //int test = 0;
   //cin >> test;
   
   set<QString>::iterator si;// = desc.begin();
   for (si=desc.begin(); si != desc.end(); si++) {
      QString funcName = *si;
      ////cout <<"FUNC NAME IS "<<funcName << endl;
      if (funcName == "i_EState") {
         mol->propMap[funcName] = getGaffEStateSum("i").latin1();
      }
      else if (funcName == "br_EState") {
         mol->propMap[funcName] = getGaffEStateSum("br").latin1();
      }
      else if (funcName == "cl_EState") {
         mol->propMap[funcName] = getGaffEStateSum("cl").latin1();
      }
      else if (funcName == "f_EState") {
         mol->propMap[funcName] = getGaffEStateSum("f").latin1();
      }
      else if (funcName == "p5_EState") {
         mol->propMap[funcName] = getGaffEStateSum("p5").latin1();
      }
      else if (funcName == "p4_EState") {
         mol->propMap[funcName] = getGaffEStateSum("p4").latin1();
      }
      else if (funcName == "p3_EState") {
         mol->propMap[funcName] = getGaffEStateSum("p3").latin1();
      }
      else if (funcName == "p2_EState") {
         mol->propMap[funcName] = getGaffEStateSum("p2").latin1();
      }
      else if (funcName == "ss_EState") {
         mol->propMap[funcName] = getGaffEStateSum("ss").latin1();
      }
      else if (funcName == "s6_EState") {
         mol->propMap[funcName] = getGaffEStateSum("s6").latin1();
      }
      else if (funcName == "s4_EState") {
         mol->propMap[funcName] = getGaffEStateSum("s4").latin1();
      }
      else if (funcName == "s2_EState") {
         mol->propMap[funcName] = getGaffEStateSum("s2").latin1();
      }
      else if (funcName == "sh_EState") {
         mol->propMap[funcName] = getGaffEStateSum("sh").latin1();
      }
      else if (funcName == "s2_EState") {
         mol->propMap[funcName] = getGaffEStateSum("s2").latin1();
      }
      else if (funcName == "os_EState") {
         mol->propMap[funcName] = getGaffEStateSum("os").latin1();
      }
      else if (funcName == "oh_EState") {
         mol->propMap[funcName] = getGaffEStateSum("oh").latin1();
      }
      else if (funcName == "o_EState") {
         mol->propMap[funcName] = getGaffEStateSum("o").latin1();
      }
      else if (funcName == "nb_EState") {
         mol->propMap[funcName] = getGaffEStateSum("nb").latin1();
      }
      else if (funcName == "no_EState") {
         mol->propMap[funcName] = getGaffEStateSum("no").latin1();
      }
      else if (funcName == "nh_EState") {
         mol->propMap[funcName] = getGaffEStateSum("nh").latin1();
      }
      else if (funcName == "na_EState") {
         mol->propMap[funcName] = getGaffEStateSum("na").latin1();
      }
      else if (funcName == "n4_EState") {
         mol->propMap[funcName] = getGaffEStateSum("n4").latin1();
      }
      else if (funcName == "n3_EState") {
         mol->propMap[funcName] = getGaffEStateSum("n3").latin1();
      }
      else if (funcName == "n2_EState") {
         mol->propMap[funcName] = getGaffEStateSum("n2").latin1();
      }
      else if (funcName == "n1_EState") {
         mol->propMap[funcName] = getGaffEStateSum("n1").latin1();
      }
      else if (funcName == "n_EState") {
         mol->propMap[funcName] = getGaffEStateSum("n").latin1();
      }
      else if (funcName == "ca_EState") {
         mol->propMap[funcName] = getGaffEStateSum("ca").latin1();
      }
      else if (funcName == "c3_EState") {
         mol->propMap[funcName] = getGaffEStateSum("c3").latin1();
      }
      else if (funcName == "c2_EState") {
         mol->propMap[funcName] = getGaffEStateSum("c2").latin1();
      }
      else if (funcName == "c1_EState") {
         mol->propMap[funcName] = getGaffEStateSum("c1").latin1();
      }
      else if (funcName == "c_EState") {
         mol->propMap[funcName] = getGaffEStateSum("c").latin1();
      }
      else if (funcName == "i_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("i").latin1();
      }
      else if (funcName == "br_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("br").latin1();
      }
      else if (funcName == "cl_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("cl").latin1();
      }
      else if (funcName == "f_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("f").latin1();
      }
      else if (funcName == "p5_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("p5").latin1();
      }
      else if (funcName == "p4_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("p4").latin1();
      }
      else if (funcName == "p3_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("p3").latin1();
      }
      else if (funcName == "p2_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("p2").latin1();
      }
      else if (funcName == "ss_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("ss").latin1();
      }
      else if (funcName == "s6_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("s6").latin1();
      }
      else if (funcName == "s4_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("s4").latin1();
      }
      else if (funcName == "s2_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("s2").latin1();
      }
      else if (funcName == "sh_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("sh").latin1();
      }
      else if (funcName == "s2_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("s2").latin1();
      }
      else if (funcName == "os_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("os").latin1();
      }
      else if (funcName == "oh_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("oh").latin1();
      }
      else if (funcName == "o_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("o").latin1();
      }
      else if (funcName == "nb_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("nb").latin1();
      }
      else if (funcName == "no_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("no").latin1();
      }
      else if (funcName == "nh_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("nh").latin1();
      }
      else if (funcName == "na_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("na").latin1();
      }
      else if (funcName == "n4_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("n4").latin1();
      }
      else if (funcName == "n3_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("n3").latin1();
      }
      else if (funcName == "n2_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("n2").latin1();
      }
      else if (funcName == "n1_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("n1").latin1();
      }
      else if (funcName == "n_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("n").latin1();
      }
      else if (funcName == "ca_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("ca").latin1();
      }
      else if (funcName == "c3_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("c3").latin1();
      }
      else if (funcName == "c2_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("c2").latin1();
      }
      else if (funcName == "c1_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("c1").latin1();
      }
      else if (funcName == "c_ESCount") {
         mol->propMap[funcName] = getGaffEStateCount("c").latin1();
      }
   }
}


//void ElectroTop::setGaffEStateSum(dt::molecule *mol) {
void ElectroTop::setGaffEStateSum(dt::molPtr mol) {
   vector<float> ES;

   dt::electroTopological et;
   
   et.setMol(mol, ES);
  
   map<string, string> basicMap;
   dt::dtGaff::getBasicTypeMap2(basicMap);
 
   gaffEStateMap.clear();
   gaffEStateCountMap.clear();
    
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
     
      string type = mol->atoms[i]->type;
      if ( basicMap.find(type) != basicMap.end()) {
         QString newType = basicMap[type];
         if (gaffEStateMap.find(newType) == gaffEStateMap.end()) {
            gaffEStateMap[newType] = ES[i];
	    gaffEStateCountMap[newType] = 1;
         } else {
            gaffEStateMap[newType] += ES[i];
            gaffEStateCountMap[newType] += 1;
         }         
      }
   }
   
}

QString ElectroTop::getGaffEStateSum(QString type) {
   if (gaffEStateMap.find(type) == gaffEStateMap.end()) {
      return "0";
   }
     
   QString num;
   num.setNum(gaffEStateMap[type]);
   return num;
}

QString ElectroTop::getGaffEStateCount(QString type) {
   if (gaffEStateCountMap.find(type) == gaffEStateCountMap.end()) {
      return "0";
   }

   QString num;
   num.setNum(gaffEStateCountMap[type]);
   return num;
}












