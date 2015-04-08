/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "objectfactory.h"
#include "scriptmollist.h"
#include "scriptmolecule.h"
#include "scriptmollist.h"
#include "scriptcharge.h"
#include "scriptbond.h"
#include "scriptatom.h"
#include "scriptenergy.h"
#include "scriptbondlist.h"


objectFactory::objectFactory(XmodelView *viewer)
 : QSObjectFactory()
{
   this->viewer = viewer;
}


objectFactory::~objectFactory()
{
}


QObject *objectFactory::create ( const QString & className, const QSArgumentList & arguments, QObject * context ) {
    if( className == "mol" ) {
      return new scriptmolecule(); 
      //scriptmolecule *mol = new scriptmolecule();
      //mol->setXmodelView(viewer);
      //return mol;
    }
      
    if ( className == "atom")
       return new scriptatom();
       
    if ( className == "bond")
       return new scriptbond();
       
    if (className == "charge")
       return new scriptcharge();
        
    if ( className == "Energy") 
       return new scriptenergy();
    
    if (className == "Molecule") 
       return new scriptmolecule();

   if (className == "MolList") 
       return new scriptmollist();

   if (className == "BondList") 
       return new scriptbondlist();
     
    return NULL;
}






































