/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "scripthide.h"
#include "molview.h"
#include "linAlg.h"

//Do you really need these?
#include <vector>
#include <list>
#include <string>
#include <iostream>

#include "molecule.h"
#include "atom.h"

scripthide::scripthide(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
}


scripthide::~scripthide()
{
}



void scripthide::selected() {
   list<molecule *>::iterator molList;
   molList = viewer->renList->begin();
   
   for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     for (int i=0; i<mol->atoms.size(); i++) {
        atom *atm = mol->atoms[i];
	if (atm->isSelected()) atm->display = 0;
     }
   }
   viewer->updateGL();
}

void scripthide::beyond(float dist) {
   vector<atom *> selectedAtoms;
   
   list<molecule *>::iterator molList;
   molList = viewer->renList->begin();
   
   for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     for (int i=0; i<mol->atoms.size(); i++) {
        atom *atm = mol->atoms[i];
	if (atm->isSelected()) selectedAtoms.push_back(atm);
     }
   }
   
   
   molList = viewer->renList->begin();
   
   for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     for (int i=0; i<mol->atoms.size(); i++) {
        atom *atm1 = mol->atoms[i];
	int within = 0;
	for (int j=0; j<selectedAtoms.size(); j++) {
	   atom *atm2 = selectedAtoms[j];
	   if (distance(atm1->fCoords, atm2->fCoords) < dist) {
	      within = 1;
	      break;
	   }	
	}
	if(within == 0) atm1->display = 0;
     }
   }
   viewer->updateGL();
}

void scripthide::hydrogens() {
   viewer->setDisplay(HIDE_HYDROGEN);
}

void scripthide::sideChains() {
   viewer->setDisplay(HIDE_SIDE_CHAIN);
}
    
void scripthide::backbone() {
   viewer->setDisplay(HIDE_BACKBONE);
}

void scripthide::ribbon() {
  viewer->setDisplay(HIDE_RIBBON);
}


































