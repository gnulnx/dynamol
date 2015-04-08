/***************************************************************************
 *    Copyright (C) 2004 by Dynamol Inc.
 *    email:   john.furr@dynamol.com
 ***************************************************************************/
#ifndef SCRIPTHIDE_H
#define SCRIPTHIDE_H

#include <qobject.h>
#include "scriptobject.h"

using namespace std;

class molView;

/**
@author jfurr
*/
//class scripthide : public QObject
class scripthide : public scriptObject
{
Q_OBJECT
public:
    scripthide(QObject *parent = 0, const char *name = 0);

    ~scripthide();
    
public slots:
    /** \brief Hide selected Atoms
    *
    *    This function hides the selected atoms
    */
    void selected();
    
    /** \brief Distance based hide
    *
    *    This function hides all atoms beyond 'dist' of the selected atoms 
    */
    void beyond(float dist);
    
    /** \brief Hide hydrogens
    *    
    *    This hides all the hydrogen atoms 
    */
    void hydrogens();
    
    /** \brief Hide protein side chains
    *
    *    This hides all the side chains in a protein.  The displayed
    *    molecule must be a protein from the PDB format
    */
    void sideChains();
    
    /** \brief Hide backbond atoms
    *
    *    This hides all the backbond atoms in a protein. The displayed
    *    molecule must be a protein from the PDB format
    */ 
    void backbone();
    
    /** \brief Hide ribbons
    *
    *    This hides the ribbon model if one is showing.  The displayed
    *    molecule must be a protein from the PDB format
    */ 
    void ribbon();
    
private:

};

#endif





































