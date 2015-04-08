/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   email:  john.furr@dynamol.com
 ***************************************************************************/
#ifndef MOLCHECK_H
#define MOLCHECK_H

/**
@author jfurr
*/
#include "trashcan.h"

class molecule;

class molCheck{
public:
    molCheck();

    ~molCheck();
    
    /** \brief Single Atom Check
    *
    *   This function checks for atoms with no other bonded atoms
    *   This is probably a result of misdraw.
    *   If a singlet atom is found it is deleted
    */
    bool singleAtomCheck(molecule *mol);

private:
   TrashCan trash;
};

#endif


