/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "scriptmolview.h"
#include "scriptmollist.h"
#include "scriptmolecule.h"
#include "molview.h"
#include "xmodelview.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

scriptmolview::scriptmolview(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
   //////////////cout <<"scriptmolview->view: " << this->view << endl;
}


scriptmolview::~scriptmolview()
{
}


scriptmollist *scriptmolview::getCurrent() {
   scriptmollist *molList = new scriptmollist;
  
   list<molecule *>::iterator molIter = viewer->renList->begin();
   int molNum = viewer->renList->size();
   for (molIter; molIter != viewer->renList->end(); molIter++) {
      molecule *mol = *molIter;
      scriptmolecule *smol = new scriptmolecule(mol);
      molList->push_back(smol);
   }

   return molList;
}

scriptmollist *scriptmolview::getMols() {
   scriptmollist *molList = new scriptmollist;
  
   list<molecule *>::iterator molIter = viewer->renList->begin();
   int molNum = viewer->renList->size();
   for (molIter; molIter != viewer->renList->end(); molIter++) {
      molecule *mol = *molIter;
      scriptmolecule *smol = new scriptmolecule(mol);
      molList->push_back(smol);
   }

   return molList;
}


void scriptmolview::addSphere(float x, float y, float z, float radius) {
   viewer->addSphere(x, y, z, radius);
   viewer->updateGL();
}

void scriptmolview::clearSpheres() {
   viewer->SPHERES.clear();
   viewer->updateGL();
}





































