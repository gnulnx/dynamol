/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   email:  john.furr@dynamol.com
 ***************************************************************************/
#include "molcheck.h"
#include "molecule.h"
#include "atom.h"
#include <vector>

using namespace std;

molCheck::molCheck()
{
}


molCheck::~molCheck()
{
}


bool molCheck::singleAtomCheck(molecule *mol) {

   vector<atom *> atomsToDelete;
   for (int i=0; i<mol->atoms.size(); i++) {
       atom *atm = mol->atoms[i];
       
       //Check for no other bonded atoms.  You also
       //check to make sure that the moelcule has more than
       //one atom as you would want a water without H to pass
       if (atm->atoms.size() == 0 && mol->atoms.size() > 1) {
          atomsToDelete.push_back(atm);
       }
   }
   
   trash.empty(atomsToDelete);
   return true;
}

