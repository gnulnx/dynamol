/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "scriptatomtyper.h"
#include "scriptmolecule.h"
#include "scriptatom.h"

#include "molecule.h"
#include "bond.h"
#include "moladapter.h"
#include "atom.h"

#include "../dynatype/electrotopological.h"

//Dynatype Includes
#include "../dynatype/dtype.h"
#include "../dynatype/molecule.h"
#include "../dynatype/atom.h"
#include "../dynatype/bond.h"

//Dynaprint Includes
#include "../dynaprint/gaffsig.h"

#include <qmap.h>



scriptatomtyper::scriptatomtyper(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
   currMol = NULL;
   //currDT =  new dt::molecule;
   currDT.reset( new dt::molecule );
   AC.resize(118);
   ringCounts.resize(12);
   BOC.resize(3);
}


scriptatomtyper::~scriptatomtyper()
{
//   delete currDT;
}

void scriptatomtyper::prepMolecule(scriptmolecule *mol) {
   if (mol == currMol) 
      return;
   if (currDT) {
      //delete currDT;
      //currDT = new dt::molecule;
      currDT.reset( new dt::molecule );
   }
   
   
   currMol = mol;
   molAdapter::mol2molecule(currDT, mol->mol);
   dt::dType dt;
   dt.setPathLength(10);
   dt.setGaffTypes(currDT);
   molAdapter::update(mol->mol, currDT);
   zeroCounts();
   molecule *m = mol->mol;
   for (int i=0; i<m->atoms.size(); i++) {
      int an = m->atoms[i]->getAtomicNum();
      AC[an]++;  
   }
   for (int i=0; i<currDT->sortedRings.size(); i++) {
      int ringSize = currDT->sortedRings[i].size();
      if ( ringSize < ringCounts.size())
         ringCounts[ringSize]++;
   }
   ////////////cout <<"Ring counts done"<<endl;
   for (int i=0; i<m->bonds.size(); i++) {
      BOC[m->bonds[i]->order-1]++;
   }
   ////////////cout <<"Leaving scriptatomtyper::prepMolecule"<<endl;
}

void scriptatomtyper::zeroCounts() {
   for (int i=0; i<AC.size(); i++) {
      AC[i] = 0;
   }
   
   for (int i=0; i<ringCounts.size(); i++) {
      ringCounts[i] = 0;
   }
   
   for (int i=0; i<BOC.size(); i++) {
      BOC[i] = 0;
   }
}

int scriptatomtyper::ringCount(scriptmolecule *mol, int ringSize) {
   if (mol != currMol)
      prepMolecule(mol);
      
   if (ringSize < ringCounts.size()) 
      return ringCounts[ringSize];
      
   int count = 0;
   for (int i=0; i<currDT->sortedRings.size(); i++) {
      if (currDT->sortedRings[i].size() == ringSize)
         count++;
   }
   return count;
}

int scriptatomtyper::bondOrderCount(scriptmolecule *mol, int order) {
   if (order > 3)
      return 0;
   if (currMol != mol)
      prepMolecule(mol);
      
   return BOC[order-1];
}

int scriptatomtyper::atomCounts(scriptmolecule *mol, int AN) {
   ////////////cout <<"scriptatomtyper::atomCounts  "<< mol->getName() << endl;  
   ////////////cout <<"currMol: " << currMol << endl;
   if (AN > AC.size())
      return 0;
   if (currMol != mol) {
      ////////////cout <<"Prepping mol: " << mol->getName() << endl;
      prepMolecule(mol);
   }
      
   return AC[AN];
}

int scriptatomtyper::aromaticRingCount(scriptmolecule *mol) {
   if (currMol != mol)
      prepMolecule(mol);

   dt::dType dt;
   return dt.aromaticRingCount(currDT);
}


float scriptatomtyper::selectAE3(scriptmolecule *mol, int descNum) {
   static fp::gaffSig gs;
   static bool read = false;
   if (read == false) {
	gs.readSubSets(10000000);
        read = true;
   }
   //dt::molecule *dtmol = new dt::molecule;
   dt::molPtr dtmol( new dt::molecule );
   molAdapter::mol2molecule(dtmol, mol->mol);
   dt::dType dt;
   dt.setPathLength(10);
   dt.setGaffTypes(dtmol);
   
   QString FP = gs.runMol(dtmol, 3, false);
   QStringList list = QStringList::split(" ", FP);
   molAdapter::update(mol->mol, dtmol);

   for (int i=0; i<list.size(); i++) {
      int num = list[i].toInt();
      if (num == descNum) {
         atom *atm = mol->mol->atoms[i];
         atm->setSelected(true);
      } 
   }  

   return 0.0;
}

float scriptatomtyper::selectAE2(scriptmolecule *mol, int descNum) {
   static fp::gaffSig gs;
   static bool read = false;
   if (read == false) {
        gs.readSubSets(10000000);
        read = true;
   }
   //dt::molecule *dtmol = new dt::molecule;
   dt::molPtr dtmol( new dt::molecule );
   molAdapter::mol2molecule(dtmol, mol->mol);
   dt::dType dt;
   dt.setPathLength(10);
   dt.setGaffTypes(dtmol);

   QString FP = gs.runMol(dtmol, 2, false);
   QStringList list = QStringList::split(" ", FP);
   molAdapter::update(mol->mol, dtmol);
   ////cout << mol->getName() << endl;
   ////cout <<"fp: " << fp << "\t:" << list.size() << endl;

   for (int i=0; i<list.size(); i++) {
      int num = list[i].toInt();
      if (num == descNum) {
         atom *atm = mol->mol->atoms[i];
         atm->setSelected(true);
      }
   }

   return 0.0;
}







