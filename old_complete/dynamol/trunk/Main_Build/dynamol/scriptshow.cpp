/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "scriptshow.h"
#include "molview.h"

#include <vector>
#include <list>
#include <string>
#include <iostream>

#include "atom.h"

scriptshow::scriptshow(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
}


scriptshow::~scriptshow()
{
}

void scriptshow::all() {
   list<molecule *>::iterator molList;
   molList = viewer->renList->begin();
   
   for (molList; molList != viewer->renList->end(); molList++) {
     molecule *mol = *molList;
     for (int i=0; i < mol->atoms.size(); i++) {
       atom *atm = mol->atoms[i];
       atm->display = 1;
     }
   
   }
   
   viewer->updateGL();
}






































