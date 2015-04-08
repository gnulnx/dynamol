/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "scriptmollist.h"
#include <iostream>
#include "molecule.h"
#include "qmessagebox.h"

scriptmollist::scriptmollist(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
   //////////////cout <<"scriptmollist->view: " <<this->view << endl;
}

scriptmollist::~scriptmollist()
{
}


scriptmolecule *scriptmollist::getMol(int index) {
   if (index < molList.size()) {
	return molList[index];
   } else {
	QMessageBox::critical(0, "Out of Range", "Your index is out of range");  
      	return NULL;
   }
}

    
void scriptmollist::push_back(scriptmolecule *mol) {molList.push_back(mol);}
void scriptmollist::push_front(scriptmolecule *mol) {molList.push_front(mol);}

scriptmolecule *scriptmollist::pop_back() 
{
   scriptmolecule *mol = molList.back();
   molList.pop_back();
   return mol;
}

scriptmolecule *scriptmollist::pop_front() 
{
   scriptmolecule *mol = molList.front();
   molList.pop_front();
   return mol;
}
    
scriptmolecule *scriptmollist::front() { return molList.front(); }
scriptmolecule *scriptmollist::back() { return molList.back(); } 

    
    
    
    
    
    




































