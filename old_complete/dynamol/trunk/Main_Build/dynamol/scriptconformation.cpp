/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "scriptconformation.h"
#include "conformation.h"
#include "scriptmolecule.h"
#include "scriptbond.h"
#include "molview.h"

scriptconformation::scriptconformation(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
}


scriptconformation::~scriptconformation()
{
}

void scriptconformation::rotateBond(scriptmolecule *smol, scriptbond *sbd, float degree) {
   Conformation conf;
   conf.rotateBond(smol->mol, sbd->getBond() , degree);  
   viewer->update();
}

void scriptconformation::rotateMol(scriptmolecule *mol, float x, float y, float z, float angle) {
   Conformation conf;
   conf.rotMolecule(mol->mol, x, y, z, angle);
   viewer->update();
}

scriptbondlist *scriptconformation::getRotableBonds(scriptmolecule *mol) {
   ////////////cout <<"scriptconformation"<<endl;   
   Conformation conf;
   vector<bond *> Bonds;
   conf.setRotableBonds(mol->mol, Bonds);
   scriptbondlist *bList = new scriptbondlist;
   
   for (int i=0; i<Bonds.size(); i++) {
      scriptbond *sbd = new scriptbond;
      sbd->setBond(Bonds[i]);
      bList->push_back(sbd);
   }
   
   return bList;
}





































