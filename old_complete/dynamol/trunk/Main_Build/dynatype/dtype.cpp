/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                     
 *   email:  john.furr@dynamol.com
 ***************************************************************************/
#include "dtype.h"
#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "dtReader.h"
#include "dtAmber_03.h"
#include "dtPaths.h"
#include "dtRings.h"
#include "dtGaff.h"
#include "dtReader.h"
#include "dtPaths.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
namespace dt {
	
dType::dType()
{
   pathLength = -1;
}


dType::~dType()
{
}

void dType::getEquivalents(molPtr mol, vector< vector< int > > &equivs, int pathLength) {
   Paths P(mol, pathLength);
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      atomPtr ai = mol->atoms[i];
      vector<int> eq;
      for (unsigned int j=i+1; j<mol->atoms.size(); j++) {
         atomPtr aj = mol->atoms[j];
	 if (aj->pathScores == ai->pathScores) 
            eq.push_back(j);
      }
      if (eq.size() >0 ) {
         eq.push_back(i);
         equivs.push_back(eq);
      }
   }
}

void dType::setGaffTypes(molPtr mol) {
   Paths P(mol, pathLength);
   ofstream outFile("equivs.txt", ios::out);
   outFile << setw(12);
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      atomPtr ai = mol->atoms[i];
      vector<int> equivs;
      for (unsigned int j=i+1; j<mol->atoms.size(); j++) {
         atomPtr aj = mol->atoms[j];
	      if (aj->pathScores == ai->pathScores) {
	         equivs.push_back(j+1);
	      }
      }

      if (equivs.size() != 0) {
         outFile <<i+1 << setw(12);
	      for (unsigned int j=0; j < equivs.size(); j++) {
	         outFile << equivs[j] << setw(12);
	      }
         outFile << endl;
      }
   }
   outFile.clear();
   outFile.close();

   Rings R(mol);
   
   dtGaff G(mol);

	
   //You should really move this to the correct place
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      mol->atoms[i]->setFFType(mol->atoms[i]->type); 
   }
}

void dType::setAmber03Types(molPtr mol) {
   Rings R(mol);
   AMBER_03 A(mol);
}

molPtr dType::readSDFX(string fileName) {
   molPtr mol( new molecule );
   if (dtReader::readSDFX(fileName, mol)) {
      return mol;
   }
   return mol; 
}

void dType::writeSDFX(string fileName, molPtr mol, int append) {
   dtReader::writeSDFX(fileName.c_str(), mol, append);
}

void dType::setPathLength(int pLength) {
   this->pathLength = pLength;
}


int dType::aromaticRingCount(molPtr mol) {
   boost::shared_ptr<Rings> r( new Rings );
   return r->aromaticRingCount(mol);
}

}//end namespace dt





