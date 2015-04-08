/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef ADDH_H
#define ADDH_H

#include "dynothread.h"
#include <vector>
#include <qstring.h>

//BOOST Includes
#include <boost/shared_ptr.hpp>

class	XmodelView;
using namespace std;
/**
@author jfurr
*/

class molecule;
class atom;
class bond;

class angle;
typedef boost::shared_ptr<angle> anglePtr;

class torsion;
typedef boost::shared_ptr<torsion> torPtr;

class QSemaphore;
class QWaitCondition;
class addH : public dynoThread
{
Q_OBJECT
public:
    addH();

    ~addH();

    virtual void run(); //This is were it all begins    
    virtual void stopThread();
    void setUp(QSemaphore *wait_sem, XmodelView *view, QString optimiztion, list<molecule *> &molList);
    
    
    
    void  addHydrogens(molecule *mol, vector<atom *> &newAtoms);
signals:
    void atomAdded(vector<atom *> &, molecule *);  
  
private:
    void bondHydrogen(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms);

    /** This handy function will check the axis to make sure that it has a magnitude before
         normalizing it
    */
    void axisCheck(vector<float> &axis); 
 
    void addOne(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms);
    void addTet_H(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms);
    void addTrig_H(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms);
    void waterH(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms);
    void hydroxylH(atom *atm, molecule *mol, int num, vector<atom *> &newAtoms, float angle);
  
   
    void  checkBondOrder(molecule *mol);
    
    /** this function is a catch all for the various prepping techniques you might
    *   need to do to a molecule so that it can make it all the way through the
    *   atome typing procedure
    */
    void prepMolecule(molecule *mol);
    
    void buildAngleVec(vector<bond *> &bonds, molecule *mol, vector<angle *> &angles);
    void buildTorVec(vector<angle *> &angles, molecule *mol, vector<torsion *> &torsions);
    void addTorsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4, vector<torsion *> &torsions);
    int getTotalBondOrder(atom *atm);
    
    list<molecule *> molList;
    QString optimization;
    
    XmodelView *view;
    QWaitCondition *update;
    QSemaphore *wait_sem;
    
    void setNoOptimze(bool opt);
    bool noOptimize;
};

#endif





































