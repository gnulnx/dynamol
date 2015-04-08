/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef SCRIPTENERGY_H
#define SCRIPTENERGY_H

#include <qobject.h>
#include <qstring.h>
#include "energy.h"
#include "scriptobject.h"

class scriptmolecule;

/**
@author jfurr
*/
class scriptenergy : public scriptObject
{
Q_OBJECT
public:
    scriptenergy(QObject *parent = 0, const char *name = 0);

    ~scriptenergy();

    /** this variable is used to determine if the molecule has been added to the list view || not */
    bool inListView;
public slots:

    /** \brief Minimize a molecule
    *
    *    This function is used to minimize the molecule "mol" using the conjugent gradients method.
    *    The other four parameters all control convergence.  The maxIter parameter specifies the
    *    maximum number of iterations, rmsef is the root mean square error allowed on the forces. 
    *    If the error drops below this point the algortihm terminates.  The maxForce value is the
    *    maximum allowed force.  The algorithm is not allowed to terminate until this value drops
    *    below it's value unless the maxIter value is reached. The minEDiff parameter tells the
    *    algorithm to terminate if the minimum difference in energy is less than the value specified. 
    *
    *    This function will default to the gaff force field for small molecules using the AM1-BCC
    *    charges.  It will use the AMBER_03 force field for proteins.  Currently Dynamol only
    *    supports these two force fields.  However if you want to change the charges used for the
    *    small molecule then use the setChargeType() function first.  The setChargeType() function
    *    sets the default value.
    */
    double cgMin(scriptmolecule *mol, float maxIter, float rmsef, float maxForce, float minEDiff);

    /** \brief Specify the charges
    *
    *    This function is used to set the defualt charge type for use with small molecules. 
    *    The possible types include "AM1", "AM1-BCC", "MNDO", and "PM3". The cgMin function
    *    defaults to AM1-BCC for small molecules.  If you want to minimize with a different 
    *    charge set then you should call this function before cgMin()
    */
    void setChargeType(QString type);
    
 private:
    QString chargeType;
    
    energyThread *et;
};

#endif






























