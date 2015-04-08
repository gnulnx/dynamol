/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc                                     *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef SCRIPTCONFORMATION_H
#define SCRIPTCONFORMATION_H

#include <qobject.h>
#include <vector>
#include "scriptobject.h"
#include <qvaluelist.h>
#include "scriptbondlist.h"
using namespace std;

class scriptmolecule;
class scriptbond;

/**
@author jfurr
*/
class scriptconformation  : public scriptObject
{
Q_OBJECT
public:
    scriptconformation(QObject *parent = 0, const char *name = 0);

    ~scriptconformation();
    
public slots:
   /** \breif perform a torsional rotation
   *
   *   This function rotates 'degrees' around specified bond.  Typical usage include:
   *   <pre>
   *   //example random rotation
   *   //Assumes you have a molecule in the molecular viewer
   *  
   *   var molList = molView.getCurrent();
   *   var mol = molList.getMol(0); //Should make sure molList is not size 0
   *   for (var i=0; i<mol.numOfBonds(); i++) {
   *      var bd = mol.getBond(i); 
   *      var degree = random() *360;
   *      Conf.rotateBond(mol, bd, degree);
   *    }
   *    </pre>
   */
   void rotateBond(scriptmolecule *mol, scriptbond *bd, float degree);
   
   
   /**  \brief Rotate the molecule
   *
   *    Rotate the molecule around the specified axis by the specified angle
   */
   void rotateMol(scriptmolecule *mol, float x, float y, float z, float angle);

   /** \brief Return a bondList of rotable bonds
    *
    * This function return the number of rotatable bonds 
    *
    * Typical usage:
    * <pre>
    * var bondList = conformation.getRotableBonds( mol );
    * <pre>
    */
   scriptbondlist *getRotableBonds(scriptmolecule *mol);



};

#endif





































