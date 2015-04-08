/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "scriptenergy.h"

#include "scriptmolecule.h"
#include "scriptatom.h"
#include "scriptbond.h"
#include "molecule.h"

#include "molview.h"
#include "xmodelview.h"
#include "mollistview.h"

#include "qapplication.h"

scriptenergy::scriptenergy(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
   chargeType = "Default";
}


scriptenergy::~scriptenergy()
{
}


double scriptenergy::cgMin(scriptmolecule *mol, float maxIter, float rmsef, float maxForce, float minEDiff) {

   QString ffType;
   if (mol->mol->rtti() == 11) { 
      ffType = "GAFF";
   } else {
      ffType = "AMBER_03";
   }

      
   if (mol->mol->atoms.size() < 200 && mol->mol->rtti() == 11 && chargeType == "Default") {
      chargeType = "AM1-BCC";
   } else if (mol->mol->rtti() > 12) {
      chargeType = "AMBER";
   } 
   
   list<molecule *> molList;
   molList.push_back(mol->mol);
      
   if (!inListView) {
    listView->addMolecule(mol->mol);
    inListView = true;
  } else {
  }
  ////////////cout <<"Calling energyThreadJob: " << chargeType << endl; 
  et = new energyThread(view, "CG Minmize");
  view->jm.registerJob(et);
  ////cout <<"chargeType: " << chargeType << endl;
  ////////////cout <<"ffType: " << ffType << endl;
  chargeType = "Current";
  et->setUp(viewer->renList, "CG", ffType, chargeType, maxIter, 
            rmsef, maxForce, minEDiff, "Constant", 1);

  ////cout <<"Starting ET"<<endl; 
  et->start();
  ////cout <<"et started()"<<endl;
 
  viewer->startAutoUpdate(50);
  //////////cout <<"Running through the loop"<<endl;
  while ( et->running()) {
     view->mainApp->processEvents();
  }
  ////cout <<"Never ever got this far"<<endl;
  //delete et;
  return mol->mol->potEnergy[0];
  
}

void scriptenergy::setChargeType(QString type) {
   this->chargeType = type;
}






























