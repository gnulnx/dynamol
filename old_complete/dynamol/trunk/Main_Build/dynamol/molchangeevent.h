/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef MOLCHANGEEVENT_H
#define MOLCHANGEEVENT_H

#include <qevent.h>
#include <vector>
#include <iostream>
#include <qstring.h>
#include "jobmanager.h"

using namespace std;

class molecule;
class atom;
class bond;
class angle;
class torsion;
class nonBond;

class QSemaphore;
/**
@author jfurr
*/
class molChangeEvent : public QCustomEvent
{
//Q_OBJECT
public:
    molChangeEvent(Type type, QSemaphore *wait_sem);
    molChangeEvent(Type type);

    ~molChangeEvent();

    void setMolecule(molecule *mol, vector<atom *> *newAtoms);
    static void setJobManager(jobManager *jm);
    static jobManager *jm;
    
    /** This function posts the event and then QApplication deletes it when done 
    *   Read the QApplication::postEvent documentation
    */
    void postEvent();
    
    /** This function sends the event but QApplications performs no clean up 
    **  Read the QApplication::sendEvent Documentation
    */
    void sendEvent();
   
    void setDisplayText(vector<string> &dt); 
    void setDisplayText(vector<QString> &dt);
    
    /** \brief Using this to pass a set of molecule to render
    */
    vector<molecule *> molVec; 
    molecule *mol;
    atom *atm;
    bond *bd;
    angle *ang;
    torsion *tor;
    nonBond *nb;
    QString name;
    vector<atom *> *newAtoms;
    
    vector<QString> displayText;
    
    QString Msg; //show this message in a QMessageBox
    
    QSemaphore *wait_sem;
    
};

#endif





































