/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "scriptselect.h"
#include "molview.h"
#include "xmodelview.h"
#include "scriptmolecule.h"
#include "scriptmollist.h"
#include "linAlg.h"

#include "protein.h"
#include "chain.h"
#include "fragment.h"
#include "molecule.h"
#include "atom.h"
#include "bond.h"

scriptselect::scriptselect(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
}


scriptselect::~scriptselect()
{
}


void scriptselect::clear()
{
   list<molecule *>::iterator molList;
   molList = viewer->renList->begin();
   
   for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     mol->setSelected(false, true);
   }
   viewer->updateGL();
}
void scriptselect::all()
{
   list<molecule *>::iterator molList;
   molList = viewer->renList->begin();
   
   for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     mol->setSelected(true, true);
   }
   viewer->updateGL();
}

void scriptselect::all(QString type)
{
   //string stringType = type;
   list<molecule *>::iterator molList;
   molList = viewer->renList->begin();
   
   for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     for (int i=0; i<mol->atoms.size(); i++) {
       atom *atm = mol->atoms[i];
       if (atm->getSym() == type) atm->setSelected(true);
     }
   }
   viewer->updateGL();
}

void scriptselect::invert() {
   list<molecule *>::iterator molList;
   molList = viewer->renList->begin();
   
   for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     for (int i=0; i<mol->atoms.size(); i++) {
       atom *atm = mol->atoms[i];
       if (atm->isSelected()) atm->setSelected(false);
       else atm->setSelected(true);
     }
   }
   viewer->updateGL(); 
}

void scriptselect::resNum(int num) {
 // ////////////cout <<"You are in scriptselect::res(int num)"<<endl;
  list<molecule *>::iterator molList;
  molList = viewer->renList->begin();
  
  for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     Object *obj = mol->lastParent();
     protein *prot = NULL;
     chain *ch = NULL;
     fragment *frag = NULL;
     if (obj != NULL && obj->rtti() == 14) prot = dynamic_cast<protein *>(obj);
     else if (obj != NULL && obj->rtti() == 13) ch = dynamic_cast<chain *>(obj);
     else if (obj != NULL && obj->rtti() == 12) ch = dynamic_cast<chain *>(obj);
     
     if (prot != NULL) {
       for (int i=0; i<prot->chains.size(); i++) {
         ch = prot->chains[i];
	 for (int j=0; j<ch->frags.size(); j++) {
	   frag = ch->frags[j];
	   if (frag->getNum() == num) frag->setSelected(true, true);
	 }
       }
    }
  }
  viewer->updateGL();
}

void scriptselect::resNum(int num, QString chainName) {
// ////////////cout <<"You are in scriptselect::res(int num, char *chainName)"<<endl;
  list<molecule *>::iterator molList;
  molList = viewer->renList->begin();
  
  for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     Object *obj = mol->lastParent();
     protein *prot = NULL;
     chain *ch = NULL;
     fragment *frag = NULL;
     if (obj != NULL && obj->rtti() == 14) prot = dynamic_cast<protein *>(obj);
     else if (obj != NULL && obj->rtti() == 13) ch = dynamic_cast<chain *>(obj);
     else if (obj != NULL && obj->rtti() == 12) ch = dynamic_cast<chain *>(obj);
     
     if (prot != NULL) {
       for (int i=0; i<prot->chains.size(); i++) {
         ch = prot->chains[i];
	 if (ch->getName() == chainName) {
	   for (int j=0; j<ch->frags.size(); j++) {
	     frag = ch->frags[j];
	     if (frag->getNum() == num) frag->setSelected(true, true);
	   }
	 }
       }
    }
  }
  
  viewer->updateGL();
}

void scriptselect::resType(QString resType) {
  //////////////cout <<"You are in scriptselect::res(char *type)"<<endl;
  list<molecule *>::iterator molList;
  molList = viewer->renList->begin();
  
  for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     Object *obj = mol->lastParent();
     protein *prot = NULL;
     chain *ch = NULL;
     fragment *frag = NULL;
     if (obj != NULL && obj->rtti() == 14) prot = dynamic_cast<protein *>(obj);
     else if (obj != NULL && obj->rtti() == 13) ch = dynamic_cast<chain *>(obj);
     else if (obj != NULL && obj->rtti() == 12) ch = dynamic_cast<chain *>(obj);
     
     if (prot != NULL) {
       for (int i=0; i<prot->chains.size(); i++) {
         ch = prot->chains[i];
	 for (int j=0; j<ch->frags.size(); j++) {
	   frag = ch->frags[j];
	   //////////////cout <<"frag->getName(): " << frag->getName() << endl;
	   if (frag->getName() == resType) frag->setSelected(true, true);
	 }
	
       }
    }
  }
  
  viewer->updateGL();
}
void scriptselect::resType(QString resType, QString chainName) {
  //////////////cout <<"You are in scriptselect::res(char *type, char *name)"<<endl;
  list<molecule *>::iterator molList;
  molList = viewer->renList->begin();
  
  for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     Object *obj = mol->lastParent();
     protein *prot = NULL;
     chain *ch = NULL;
     fragment *frag = NULL;
     if (obj != NULL && obj->rtti() == 14) prot = dynamic_cast<protein *>(obj);
     else if (obj != NULL && obj->rtti() == 13) ch = dynamic_cast<chain *>(obj);
     else if (obj != NULL && obj->rtti() == 12) ch = dynamic_cast<chain *>(obj);
     
     if (prot != NULL) {
       for (int i=0; i<prot->chains.size(); i++) {
         ch = prot->chains[i];
	 if (ch->getName() == chainName) {
	   for (int j=0; j<ch->frags.size(); j++) {
	     frag = ch->frags[j];
	     if (frag->getName() == resType) frag->setSelected(true, true);
	   }
	 }
       }
    }
  }
  
  viewer->updateGL();
}


void scriptselect::atomNum(int num) {
  list<molecule *>::iterator molList;
  molList = viewer->renList->begin();
  
  for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     for (int i=0; i<mol->atoms.size(); i++) {
        atom *atm = mol->atoms[i];
	if (atm->getNum() == num) atm->setSelected(true);
     }       
  }
  
  viewer->updateGL();
}

void scriptselect::atomType(QString type) {
 list<molecule *>::iterator molList;
  molList = viewer->renList->begin();
  string sType = type;
  int typeNum;
  if (sType == "C" || sType == "c") typeNum = 6;
  else if (sType == "N" || sType == "n") typeNum = 7;
  else if (sType == "O" || sType== "o") typeNum = 8;
  else if (sType == "P" || sType == "p") typeNum = 15;
  else if (sType == "S" || sType == "s") typeNum = 16;
  else if (sType == "Cl" || sType == "cl" || type == "CL") typeNum = 17;
  else if (sType == "CA" || sType == "Ca" || sType == "ca") typeNum = 20;
  else if (sType == "NA" || sType == "Na" || sType == "na") typeNum = 11;
  else if (sType == "k" || sType == "K") typeNum = 19;
  else if (sType == "Li" || sType == "LI" || sType == "li") typeNum = 3;
  else if (sType == "H" || sType ==  "h") typeNum = 1;
  else if (sType == "Rb" || sType == "rb" || sType == "RB") typeNum = 37;
  else if (sType == "MG" || sType == "mg" || sType == "Mg") typeNum = 12;
  
  for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     for (int i=0; i<mol->atoms.size(); i++) {
        atom *atm = mol->atoms[i];
	string tmp = atm->getSym();
	
	if (atm->getAtomicNum() == typeNum) atm->setSelected(true);
     }       
  }
  
  viewer->updateGL();
}

scriptmolecule *scriptselect::mol(QString molName) {
  list<molecule *>::iterator molList;
  molList = viewer->renList->begin();
  for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     if (mol->getName() == molName) {
     	mol->setSelected(true, true);
	scriptmolecule *smol = new scriptmolecule(mol);
//	smol->setMolecule(mol);
	smol->fromMolView = true;
	//smol->setXmodelView(this->viewer);
	viewer->updateGL();
	return smol;
     }
  }
  viewer->updateGL();
  return NULL;
}

void scriptselect::mol(scriptmolecule *smol) {
  list<molecule *>::iterator molList;
  molList = viewer->renList->begin();
  for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     if (mol == smol->mol) mol->setSelected(true, true);
  }
  viewer->updateGL();
}

scriptmollist *scriptselect::current() {
 scriptmollist *scriptList = new scriptmollist;
 list<molecule *>::iterator molList;
  molList = viewer->renList->begin();
  for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     if (mol != NULL) {
       mol->setSelected(true, true);
       scriptmolecule *smol = new scriptmolecule(mol);
//       smol->setMolecule(mol);
       //smol->setXmodelView(viewer);
       scriptList->push_back(smol);
     }
  }
  viewer->updateGL();
  
  return scriptList;
}

void scriptselect::within(float dist) {
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
   
   //Now lets do the distance check and select the atoms
   molList = viewer->renList->begin();
   for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     for (int i=0; i<mol->atoms.size(); i++) {
        atom *atm1 = mol->atoms[i];
	int within = 0;
	for (int j=0; j<selectedAtoms.size(); j++) {
	   atom *atm2 = selectedAtoms[j];
	   float DIST = distance(atm1->fCoords, atm2->fCoords);
	   if ( DIST < dist) {
	      within = 1;
	      break;
	   }	
	}
	if(within == 1) {
	   atm1->setSelected(true, true);
	}
     }
   }
   viewer->updateGL();
}
    

void scriptselect::within(float dist, scriptmolecule *mol) {
   list<molecule *>::iterator molList;
   molList = viewer->renList->begin();
   
   for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol1 = *molList;
     for (int i=0; i<mol1->atoms.size(); i++) {
        atom *atm1 = mol1->atoms[i];
	int within = 0;
	for (int j=0; j<mol->mol->atoms.size(); j++) {
	   atom *atm2 = mol->mol->atoms[j];
	   float DIST = distance(atm1->fCoords, atm2->fCoords);
	   if ( DIST < dist) {
	      within = 1;
	      break;
	   }	
	}
	if(within == 1) {
	   atm1->setSelected(true, true);
	}
     }
   }
   viewer->updateGL();
}




































