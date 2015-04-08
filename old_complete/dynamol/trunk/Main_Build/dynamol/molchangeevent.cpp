/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "molchangeevent.h"
#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "angle.h"
#include "torsion.h"
#include "nonbond.h"
#include "qsemaphore.h"
#include "qapplication.h"


jobManager *molChangeEvent::jm = NULL;

molChangeEvent::molChangeEvent(Type type, QSemaphore *wait_sem)
 : QCustomEvent(type)
{
  this->wait_sem = wait_sem;
  name = "none";
}

molChangeEvent::molChangeEvent(Type type)
 : QCustomEvent(type)
{
  name = "none";
}


molChangeEvent::~molChangeEvent()
{
}

void molChangeEvent::setMolecule(molecule *mol, vector<atom *> *newAtoms) {
  this->mol = mol;
  this->newAtoms = newAtoms;
}

void molChangeEvent::setJobManager(jobManager *JM) {
   jm = JM;
}

void molChangeEvent::postEvent() {
   QApplication::postEvent(jm, this);
}

void molChangeEvent::sendEvent() {
   QApplication::sendEvent(jm, this);
}

void molChangeEvent::setDisplayText(vector<string> &dt) {
   vector<QString> dt2;
   for (int i=0; i<dt.size(); i++)
      dt2.push_back(dt[i]);

   setDisplayText(dt2);
}

void molChangeEvent::setDisplayText(vector<QString> &dt) {
   displayText.clear();
   displayText = dt;
}






































