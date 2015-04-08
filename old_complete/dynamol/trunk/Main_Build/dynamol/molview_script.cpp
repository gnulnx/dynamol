//Dynamol Includes
#include "molview_script.h"
#include "mollistview.h"
#include "molview.h"
#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "moladapter.h"

//Dynacomp Includes
#include "../dynacomp/molecule.h"
#include "../dynacomp/atom.h"
#include "../dynacomp/bond.h"

//Standard Library Includes
#include <vector>
#include <iostream>
#include <algorithm>

//Boost Includes
#include <boost/shared_ptr.hpp>

#ifdef WINDOWS
extern "C" __declspec(dllexport)
#endif
void numberList() {
    cout <<"This is the numberList...a Test Function"<<endl;
}

//#ifdef WINDOWS
//extern "C" __declspec(dllexport)
//#endif
molView *VIEWER = NULL;

//#ifdef WINDOWS
//extern "C" __declspec(dllexport)
//#endif
int molview_selectAll() 
{ return molViewScript::selectAll(); }

int molview_atomCount() 
{ return molViewScript::atomCount(); }


int molview_selectAtomType(std::string type)
{ return molViewScript::selectAtomType(type); }

int molview_selectInvert()
{return molViewScript::selectInvert();}

int molview_selectWithin(float ang)
{return molViewScript::selectWithin(ang);}

int molview_selectMol(int n)
{return molViewScript::selectMol(n);}

dynacomp::molecule *molview_getMol(int n)
{ return molViewScript::getMol(n); }

void molview_addMol(dynacomp::molecule *mol)
{ molViewScript::addMol(mol); }

molView *molViewScript::VIEWER = NULL;
molViewScript::molViewScript() {}
molViewScript::~molViewScript() {}
int molViewScript::selectAll() {
    std::cout <<"Hello form molViewScript::selectAll() " << std::endl;
    std::cout <<"VIEWER is: " << VIEWER << std::endl;
    if (!VIEWER) {
        cout <<"molView was not initialized"<<endl;
        return false;
    }

    std::list<molecule *> molList;
    VIEWER->getCurrentMolList(molList);
    std::list<molecule *>::iterator it = VIEWER->renList->begin();
    int count = 0;
    for (it; it != VIEWER->renList->end(); it++) {
        molecule *mol = *it;
        cout <<"Selecting: " << mol->getName() << endl;
        mol->setSelected(true, true);
	count += mol->atoms.size();
    }

    return count;
//    VIEWER->updateGL();

}

int molViewScript::selectAtomType(std::string type) 
{
    if (!VIEWER) {
        cout <<"molView was not initialized"<<endl;
        return -1;
    }

    for (unsigned int i=0; i<type.size(); i++) 
       type[i] = toupper(type[i]);
//    transform (type.begin(),type.end(), type.begin(), toupper);
    
    int count = 0;
    std::list<molecule *> molList;
    VIEWER->getCurrentMolList(molList);
    std::list<molecule *>::iterator it = VIEWER->renList->begin();
    for (it; it != VIEWER->renList->end(); it++) {
        molecule *mol = *it;
	for (int i=0; i<mol->atoms.size(); i++) {
	   if (mol->atoms[i]->getSymbol() == type) {
	      mol->atoms[i]->setSelected(true, true);
	      count++;
	   }
	}
    }

    cout <<"count is: " << count << endl;
    return count;
}

int molViewScript::atomCount()
{
    if (!VIEWER) {
        cout <<"molView was not initialized"<<endl;
        return -1;
    }

    int count = 0;
    std::list<molecule *> molList;
    VIEWER->getCurrentMolList(molList);
    std::list<molecule *>::iterator it = VIEWER->renList->begin();
    for (it; it != VIEWER->renList->end(); it++) {
        molecule *mol = *it;
	count += mol->atoms.size();
    }

    cout <<"Count is: " << count << endl;
    return count;
}


int molViewScript::selectInvert() {
    if (!VIEWER) {
        cout <<"molView was not initialized"<<endl;
        return -1;
    }

    int count = 0;
    std::list<molecule *> molList;
    VIEWER->getCurrentMolList(molList);
    std::list<molecule *>::iterator it = VIEWER->renList->begin();
    for (it; it != VIEWER->renList->end(); it++) {
        molecule *mol = *it;
	for (int i=0; i<mol->atoms.size(); i++) {
           atom *atm = mol->atoms[i];
	   if (atm->isSelected()) 
	      atm->setSelected(false);
	   else {
	      atm->setSelected(true);
	      count++;
	   }
	}
    }
   return count;
}

int molViewScript::selectWithin(float ang) {
    if (!VIEWER) {
        cout <<"molView was not initialized"<<endl;
        return -1;
    }

    int count = 0;
    std::list<molecule *> molList;
    VIEWER->getCurrentMolList(molList);
    std::list<molecule *>::iterator it = VIEWER->renList->begin();
    for (it; it != VIEWER->renList->end(); it++) {
        molecule *mol = *it;
	std::vector<atom *> selectedAtoms;
	for (int i=0; i<mol->atoms.size(); i++) {
           atom *atm = mol->atoms[i];
	   if (atm->isSelected()) 
	      selectedAtoms.push_back(atm);
	}

        for (int i=0; i<selectedAtoms.size(); i++) {
	   atom *atm = selectedAtoms[i];
	   float *cd1 = atm->fCoords;
        for (int j=0; j<mol->atoms.size(); j++) {
           float *cd2 = mol->atoms[j]->fCoords;
	   float a = cd1[0] - cd2[0];
	   float b = cd1[1] - cd2[1];
	   float c = cd1[2] - cd2[2];
	   float dist = sqrt(a*a +b*b + c*c);
	   if (dist <= ang)
	      mol->atoms[j]->setSelected(true, true);
	} 
	}
    }
   return -1;
}

int molViewScript::selectMol(int n) {
    if (!VIEWER) {
        cout <<"molView was not initialized"<<endl;
        return -1;
    }

    int count = 0;
    std::list<molecule *> molList;
    VIEWER->getCurrentMolList(molList);
    std::list<molecule *>::iterator it = VIEWER->renList->begin();
    if (n >= VIEWER->renList->size())
       return 0;

    for (int i=1; i<=n; i++) 
       it++;
    
    molecule *mol = *it;
    mol->setSelected(true, true);
   return mol->atoms.size();
}

dynacomp::molecule *molViewScript::getMol(int n) {
	cout <<"You are in molViewScript::getMol"<<endl;
 	if (!VIEWER) {
		cout <<"molView was not initialized"<<endl;
		return NULL;
	}

	int count = 0;
	std::list<molecule *> molList;
	VIEWER->getCurrentMolList(molList);
	std::list<molecule *>::iterator it = VIEWER->renList->begin();
	if (n >= VIEWER->renList->size())
    	return NULL;

	for (int i=1; i<=n; i++) 
    	it++;
    
	molecule *mol = *it;
	cout <<"mol->atoms.size() nextline"<<endl;
	cout <<mol->atoms.size() << endl; 
	dynacomp::molecule *dcMol = new dynacomp::molecule;
	molAdapter::mol2dynacomp(dcMol, mol);
	cout <<"Number of atoms in dcMol: "<< dcMol->atoms.size() << endl;
	return dcMol;
}

void molViewScript::addMol(dynacomp::molecule *dcMol) {
	cout <<"You are in molViewScript::addMol"<<endl;
	if (VIEWER == NULL)
		return;
	
	molecule *mol = new molecule;
	cout <<"Right before molAdapter::dynacomp2mol"<<endl;
	cout <<"dcMol->atoms.size(): "<< dcMol->atoms.size() << endl;
	cout <<"dcMol->bonds.size(): " << dcMol->bonds.size() << endl;
	molAdapter::dynacomp2molecule(mol, dcMol);
	cout <<"MOLECULE->atoms: " << mol->atoms.size() << endl;
	cout<<"MOLECULE->bonds: " << mol->bonds.size() << endl;
	cout <<"Now calling addMolecule"<<endl;
	VIEWER->listView->addMolecule(mol, false);
//	VIEWER->addMol(mol, true);
//	VIEWER->listView->renList.clear();
//	VIEWER->lisView->renList.push_back(mol);
//	VIEWER->molView->setMolList(&VIEWER->listView->renList);
	cout <<"Leaving molViewScript::addMol"<<endl;
}
