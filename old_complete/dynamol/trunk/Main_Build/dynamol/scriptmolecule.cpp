/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "scriptmolecule.h"
#include "charge.h"
#include "addh.h"
#include "molecule.h"
#include "molview.h"
#include "xmodelview.h"
#include "scriptbond.h"
#include "scriptatom.h"
#include "forcefield.h"
#include "energy.h"
#include "bond.h"
#include <qeventloop.h>

#include "scriptlistview.h"

#include <list>
#include <map>

#include "mollistview.h"
#include "qapplication.h"
#include "trashcan.h"

using namespace std;


scriptmolecule::scriptmolecule(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
   mol = new molecule;
   fromMolView = false;
   inListView = false;
}

scriptmolecule::scriptmolecule(molecule *mol, QObject *parent, const char *name) 
: scriptObject(parent, name)
{
   this->mol = mol;
   /** The atom map is used to accurately construct the atom and bond lists 
   */
   map<atom *, scriptatom *> atomMap;
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      scriptatom *sAtm = new scriptatom;
      sAtm->setAtom(atm);
      atoms.push_back(sAtm);
      atomMap[atm] = sAtm;
   }
   
   for (int i=0; i<mol->bonds.size(); i++) {
      bond *bd = mol->bonds[i];
      scriptbond *sBd = new scriptbond;
      sBd->setBond(bd);
      bonds.push_back(sBd);
      scriptatom *from = atomMap[bd->fromAtom()];
      scriptatom *to = atomMap[bd->toAtom()];
      sBd->setAtoms(from, to);
   }
   fromMolView = false;
   inListView = false;
}


scriptmolecule::~scriptmolecule()
{
   for (int i=0; i<atoms.size(); i++) {
      delete atoms[i];
   }
   for (int i=0; i<bonds.size(); i++) {
      delete bonds[i];
   }
   
   vector<Object *> molToDelete;
   molToDelete.push_back(mol);
   TrashCan t( molToDelete );
   t.empty();
}

scriptmolecule *scriptmolecule::copy() {
   scriptmolecule *smol = new scriptmolecule;
   *smol->mol = *this->mol;
   return smol;
}

/*
void scriptmolecule::setMolecule(molecule *mol) {this->mol = mol;};
*/
void scriptmolecule::printName() {
  if (mol == NULL) {
	////////////cout <<"No name has been assigned"<<endl;
  }
  else {
	////////////cout <<mol->getName() << endl;
  }
}

void scriptmolecule::setName(QString name) {
   mol->setName(name.latin1());
}


scriptatom *scriptmolecule::getAtom(int num) {
   ////////////cout <<"scriptmolecule::getAtom: " << atoms.size() << endl;
   if (num >= atoms.size()) return NULL;
   //scriptatom *sAtm = new scriptatom;
   ////////////cout <<"retuning atoms[num]: " << atoms[num]->getSym() << endl;
   return atoms[num];
//   sAtm->setAtom(mol->atoms[num]);
   //return sAtm;
}

scriptbond *scriptmolecule::getBond(int num) {
//   //////////cout <<"bonds.size():  " << bonds.size() << endl;
   if (num >= bonds.size()) return NULL;
   return bonds[num];
   //scriptbond *bd = new scriptbond;
   //bd->setBond(mol->bonds[num]);
   //return bd;
}

int scriptmolecule::numOfAtoms() 
{return mol->atoms.size();};


void scriptmolecule::addCharges(QString type) {
   charge Charge;
   Charge.setUp(this->mol, type.latin1());
   Charge.run();
}

void scriptmolecule::addHyd() {
   addH H;
   if (viewer != NULL) {
      //view->addHydrogens(mol, "NONE");
      vector<atom *> newAtoms;
      H.addHydrogens(mol, newAtoms);
      
   }

   if (viewer == NULL) {
   } else {
      viewer->updateGL();
   }  
}

double scriptmolecule::quickMin() {
         
   QString minMethod = "CG";
   QString ffType = "GAFF";
   QString chargeType = "AM1-BCC";
   
   list<molecule *> molList;
   molList.push_back(mol);
   
   
   int maxIter = 3000;
   float rmsef = .1;
   float maxForce = .1;
   float minEDiff = 0.000;
   
   if (!inListView) {
    //////////////cout <<"Adding mol to listView "<< listView << endl;
    listView->addMolecule(mol);
    inListView = true;
  } else {
    //////////////cout <<"No molecule to add to molList"<<endl;
  }
 
  et = new energyThread(view, "QuickMin");
  view->jm.registerJob(et);
  et->setUp(viewer->renList, minMethod, ffType, chargeType, maxIter, 
            rmsef, maxForce, minEDiff, "Constant", 1);

  et->start();
 
  viewer->startAutoUpdate(50);
  while ( et->running()) {
     view->mainApp->processEvents();
  }

  return mol->potEnergy[0];
}

double scriptmolecule::potE() {
   //this->Energy.
   //////////////cout <<"scriptmolecule::potE"<<endl;
   int as = mol->angles.size();
   int ts = mol->torsions.size();
   int ns = mol->nonBonds.size();
   if (as == 0 || ts == 0 || ns == 0) {
      mol->setAngles();
      mol->setTorsions();
      mol->setNonBonds(1000);
      
      string type = "GAFF"; //Shouldn't you be checking for someting more appropriate here     
      forceField ff;
      ff.setAtomTypes(mol, type);
      ff.buildLists(mol, type);
   }
   
   
   energy E;
   double totEnergy = E.molEnergy(mol);
   return totEnergy;
}

QString scriptmolecule::getName() {
  QString name = mol->getName();
  return name;
}

int scriptmolecule::numOfBonds() {return mol->bonds.size(); }

void scriptmolecule::addPropValuePair(QString Name, QString Value, QString propType) {
   this->mol->addPropValuePair(Name, Value);
}

QString scriptmolecule::getPropValue(QString Name) {
   QString value = mol->getPropValue(Name);
   return value;
}

QString scriptmolecule::getPropType(QString Type) {
   QString type = mol->getPropType(Type);
   return type;
}

int scriptmolecule::numOfProperties() {
	return mol->propMap.size();
}

double scriptmolecule::molWeight() {
    return mol->molWeight();
}
































