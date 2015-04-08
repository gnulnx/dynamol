/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "energy.h"
#include "molview.h"
#include <cmath>
#include "linAlg.h"
#include "xmodelview.h"
#include "molchangeevent.h"
#include "qmessagebox.h"
#include "forcefield.h"
#include "conformation.h"
#include <qfile.h>
#include <qtextstream.h>

#include <qapplication.h>

#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "angle.h"
#include "torsion.h"
#include "nonbond.h"
#include "charge.h"
#include "xmodeldoc.h"
#include "charge.h"

#include "moladapter.h"

//Dynamol Computational Library Includes
#include "../dynacomp/energy.h"
#include "../dynacomp/molecule.h"

#define degToRad  3.1415926535/180


energyThread::energyThread(XmodelView *view, list<molecule *> &molList, string name) 
: dynoThread(NULL) 
{
   setName(name); 
   Energy = new energy(view, molList);
   //Energy = new energy();
   this->view = view;
}

energyThread::energyThread(XmodelView *view, string name) 
: dynoThread(NULL) 
{
  setName(name); 
   
   //Energy = new energy(view);

   //Dynacomp Based Energy
   dcEnergy = new dynacomp::energy();
   
   this->view = view;
}
energyThread::~energyThread() {delete Energy;}
int energyThread::rtti() {return 3;}
void energyThread::stopThread() 
{ 
   //Energy->stop = true;
   dcEnergy->stop = true;
}
void energyThread::setName(string name) {this->name = name;}
QString energyThread::getName() {return this->name;};

void energyThread::setUp(list<molecule *> *molList, string method, string ff, string chargeType, int maxIter, float rmsef, float maxForce, float minEDiff, string dieMethod, float dieValue) 
{

   //list<dynacomp::molecule *> *dcMolList = new list<dynacomp::molecule *>;
   dcMolList = new list<dynacomp::molecule *>;
   list<molecule *>::iterator iter = molList->begin();
   for (iter; iter != molList->end(); iter++) {
      molecule *mol = *iter;
      dynacomp::molecule *dcMol = new dynacomp::molecule;
      molAdapter::mol2dynacomp(dcMol, mol);
      dcMolList->push_back(dcMol);
   }
   dcEnergy->setUp(dcMolList, method, ff, chargeType,
                   maxIter, rmsef, maxForce, minEDiff);
   dcEnergy->dieSetup(dieMethod, dieValue);

   //Energy->setUp(molList, method, ff, chargeType,maxIter, rmsef, maxForce, minEDiff);
   //Energy->dieSetup(dieMethod, dieValue);
}



void energyThread::mcSetup(list<molecule *> *molList, string method, int maxIter, float Temp, string ffType, string chargeType, string fileName, int outIter) {
//  Energy->mcSetup(molList, method, maxIter, Temp, ffType, chargeType, fileName, outIter);
  dcMolList = new list<dynacomp::molecule *>;
   list<molecule *>::iterator iter = molList->begin();
   for (iter; iter != molList->end(); iter++) {
      molecule *mol = *iter;
      dynacomp::molecule *dcMol = new dynacomp::molecule;
      molAdapter::mol2dynacomp(dcMol, mol);
      dcMolList->push_back(dcMol);
   }
   dcEnergy->mcSetup(dcMolList, method, maxIter, Temp, ffType, chargeType, fileName, outIter);
}

void energyThread::mdSetup(list<molecule *> *molList, string method, int maxIter, float timeStep, string ffType, string chargeType, string fileName, int outIter) {
   //list<dynacomp::molecule *> *dcMolList = new list<dynacomp::molecule *>;
   dcMolList = new list<dynacomp::molecule *>;
   list<molecule *>::iterator iter = molList->begin();
   for (iter; iter != molList->end(); iter++) {
      molecule *mol = *iter;
      dynacomp::molecule *dcMol = new dynacomp::molecule;
      molAdapter::mol2dynacomp(dcMol, mol);
      dcMolList->push_back(dcMol);
   }
   dcEnergy->mdSetup(dcMolList, method, maxIter, timeStep, ffType, chargeType, fileName, outIter);
   //Energy->mdSetup(molList, method, maxIter, timeStep, ffType, chargeType, fileName, outIter);
}

void energyThread::dieSetup(string method, float value) {
   Energy->dieSetup(method, value);
}

void energyThread::run2() {
   vector<string> infoText;
   dcEnergy->setInfoText(view->viewer->infoText);
   if (!dcEnergy->run() ) {
      errorMsg = dcEnergy->getErrorMsg();
      displayErrors();
   }
}

void energyThread::run() 
{
   threadNum = count; 
   count++; 
   
   run2();
   list<dynacomp::molecule *>::iterator iter = dcMolList->begin();
   for (iter; iter != dcMolList->end(); iter++) {
      dynacomp::molecule *mol = *iter; 
      delete mol;
   }
   
   emit threadDone();
   
   molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1002));
   e->name = name;
   QApplication::postEvent(&view->jm, e);
   
};


//This is were the real energy class begins
energy::energy() 
//: QObject()
{
	rmsef = 0.5;
	maxForce = 0.1;
	minEDiff = .000005;
	Temp = 300;
	stop = false;
	//this->viewer->helloFromMolView();
	//ff = new forceField(viewer);
	ff = new forceField();
	heavyFreeze = false;
        view = NULL;
        viewer = NULL;
	/** This sets the default value of the dielectric constant */
        dielectric = 1.0;
        distDep = false;
        update = true;
};
energy::energy(XmodelView *view)
 //: QObject()
 {
 	this->view = view;
	this->viewer = view->viewer;
	stop = false;
	rmsef = 0.5;
	maxForce = 0.1;
	minEDiff = .000005;
	Temp = 300;	
	heavyFreeze = false;
	
	/** This sets the default value of the dielectric constant */
        dielectric = 1.0;
        distDep = false;
        update = true;
}

energy::energy(XmodelView *view, list<molecule *> &molList) 
//: QObject()
{
	
	this->view = view;
	this->viewer = view->viewer;
	this->molList = &molList;
	stop = false;
        update = true;
	//ff = new forceField(viewer);
}
void energy::setUpdate(bool update) { this->update = update;}

void energy::dieSetup(string method, float value) {
   if (method == "Constant") {
      dielectric = 1.0/value;
      distDep = false;
   } 
   else if (method == "Distant Dependant") {
      distDep = true;
      dielectric = 1.0; //Do this so that you don't multiply by -1
   }

}



int energy::run() {
   ff = new forceField();
   
   //Now we need to calculate the charges
   list<molecule *>::iterator iter = molList->begin();
   for (iter; iter != molList->end(); iter++) {
      molecule *mol = *iter;

      bool setChargeType = false;
      if (mol->chargeType != chargeType) {
         charge chg;
         chg.setUp(mol, chargeType);
         bool success = chg.run();
         if (!success) {
             return false;
         }
         setChargeType = true;
         mol->chargeType = chargeType;
      }
      
      //If the ffType is of then lets call dynamol && get the types
      string type = ffType;
      if (mol->ffTypes != type ) { 
      //Set the atom types
      if ( !ff->setAtomTypes(mol, type) ) {
         molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1008));
         e->name = "Bad_Atom_Type";
         e->postEvent();
         return -1;
      }
      }
      //Build the angles, torsions && nonBond lists
      if ( !ff->buildLists(mol, type) ) {
         return -1;
      }
   }     

   //This section sets up the molecules
   if (!setUpVectors(*molList)) {
      return false;
   }

   
   if (method == "SD") SD_minimize(maxIter, rmsef, maxForce, minEDiff);
   else if (method == "CG") CG_minimize(maxIter, rmsef, maxForce, minEDiff);
   else if (method == "MC") MC(maxIter, Temp);
   else if (method == "MCFB") MC_fb(maxIter, Temp);
   else if (method == "MCTR") MC_torsional(maxIter, Temp);
   else if (method == "MD") MD();
       
  
   return true;
}

double energy::psoEnergy() {
   bondStretchEnergy();
   angleBendEnergy();
   torsionalEnergy();
   nonBondEandF();

   energies[0] = 0.0;
   for (int i=1; i<6; i++) { 
      energies[0] += energies[i];
   }
  
   return energies[0];
}

double energy::molEnergy(molecule *mol) {
   //Make sure that the angles, torsions, && nonBonds are calculated in the molecule  
   if (mol->angles.size() == 0) mol->setAngles();
   if (mol->torsions.size() == 0) mol->setTorsions();
   if (mol->nonBonds.size() == 0) mol->setNonBonds(100);
 
   setAtoms(mol->atoms);
   setBonds(mol->bonds);
   setAngles(mol->angles);
   setTorsions(mol->torsions);
   setNonBonds(mol->nonBonds);

   //New Stuff
   setNonBonds(mol->nonbonds);
  
   bondStretchEnergy();
   angleBendEnergy();
   torsionalEnergy();
   nonBondEandF();
   
   energies[0] = 0.0;
   for (int i=1; i<6; i++) { 
      energies[0] += energies[i];
   }
   //energies[4] = energies[0] + energies[1] + energies[2] + energies[3];
    
   mol->potEnergy[0] = energies[0];
   mol->potEnergy[1] = energies[1];
   mol->potEnergy[2] = energies[2];
   mol->potEnergy[3] = energies[3];
   mol->potEnergy[4] = energies[4] + energies[5];
   //setInfoEnergy(0);
   this->setInfoToEnergy(-1);
   return energies[0];
}


void energy::setMol(molecule *mol)   {this->mol = mol;};

void energy::mcSetup(list<molecule *> *molList, string method, int maxIter, float Temp, string ffType, string chargeType, string fileName, int outIter) {
   this->Temp = Temp;
   this->maxIter = maxIter;
   this->method = method;
   this->chargeType = chargeType;
   this->ffType = ffType;
   this->molList = molList;
   this->outFile = fileName;
   this->outIter = outIter;
}

void energy::mdSetup(list<molecule *> *molList, string method, int maxIter, float timeStep, string ffType, string chargeType, string fileName, int outIter) {
   this->timeStep = timeStep;
   this->maxIter = maxIter;
   this->method = method;
   this->chargeType = chargeType;
   this->ffType = ffType;
   this->molList = molList;
   this->outFile = fileName;
   this->outIter = outIter;
}

void energy::setUp(list<molecule *> *molList, string method, string ffType, string chargeType, int maxIter, float rmsef, float maxForce, float minEDiff) {
	this->maxIter = maxIter;
	this->rmsef = rmsef;
	this->maxForce = maxForce;
	this->minEDiff = minEDiff;
	this->method = method;
	this->chargeType = chargeType;
	this->ffType = ffType;
	this->molList = molList;
}

void energy::setUp(molecule *mol, string method, string ffType, string chargeType, int maxIter, float rmsef, float maxForce, float minEDiff) {
   this->molList = new list<molecule *>;
   this->molList->push_back(mol);
   this->maxIter = maxIter;
   this->rmsef = rmsef;
   this->maxForce = maxForce;
   this->minEDiff = minEDiff;
   this->method = method;
   this->chargeType = chargeType;
   this->ffType = ffType;
   setUpVectors(*molList);
}

void energy::setUp(string method, string ff, string chargeType, int maxIter, float rmsef, float maxForce, float minEDiff) {
   this->maxIter = maxIter;
   this->rmsef = rmsef;
   this->maxForce = maxForce;
   this->minEDiff = minEDiff;
   this->method = method;
   this->chargeType = chargeType;
   this->ffType = ffType;
}

bool energy::setUpVectors(list<molecule *> &molList) {

   list<molecule *>::iterator molIter = molList.begin();
   list<molecule *> tmpList;


   int test = 0;
   for (molIter; molIter != molList.end(); molIter++) {
      molecule *mol = *molIter;
      setMol(mol);
   }

   //Now lets set up the vector<atom *> for the atoms
   atomVec.clear();
   molIter = molList.begin();
   for (molIter; molIter != molList.end(); molIter++) {
      molecule *mol = *molIter;
      for (int i=0; i<mol->atoms.size(); i++) {
         atomVec.push_back(mol->atoms[i]);
      }
   }
  	
   //Now lets set up the vector<bond *> for the bonds
   bondVec.clear();
   molIter = molList.begin();
   for (molIter; molIter != molList.end(); molIter++) {
      molecule *mol = *molIter;
      for (int i=0; i<mol->bonds.size(); i++) {
         bond *bd = mol->bonds[i];
	 bondVec.push_back(bd);
      }
   }
	  
   //Now lets set up the angle list
   angleVec.clear();
   molIter = molList.begin();
   for (molIter; molIter != molList.end(); molIter++) {
      molecule *mol = *molIter;
      for (int i=0; i<mol->angles.size(); i++) {
         angle *ang = mol->angles[i];
	 angleVec.push_back(mol->angles[i]);
      }
   }		  

   //Now lets set up the torsion list
   torVec.clear();
   molIter = molList.begin();
   for (molIter; molIter != molList.end(); molIter++) {
      molecule *mol = *molIter;
      for (int i=0; i<mol->torsions.size(); i++) {
       	torVec.push_back(mol->torsions[i]);
      }
   }
		
   //This section is not complete!!!!!
   //You need to add support for the mol-mol nonBonds
   //This will let you get the energy of the entire system
   nonbondVec.clear();
   molIter = molList.begin();
   for (molIter; molIter != molList.end(); molIter++) {
      molecule *mol = *molIter;
      for (int i=0; i<mol->nonBonds.size(); i++) {
         nonBond *nb = mol->nonBonds[i];
	 nonbondVec.push_back(mol->nonBonds[i]);
      }
   }

   nbVec = mol->nonbonds;
   return true;
}


void energy::setAtoms(vector<atom *> &Atoms)  
{this->atomVec = Atoms;};

void energy::setBonds(vector<bond *> &Bonds) 
{this->bondVec = Bonds;};

void energy::setAngles(vector<angle *> &Angles)  
{this->angleVec = Angles;};

void energy::setTorsions(vector<torsion *> &Torsions) 
{this->torVec = Torsions;};

void energy::setNonBonds(vector<nonBond *> &nonBonds)
{this->nonbondVec = nonBonds;}

void energy::setNonBonds(vector<dynabase::nonBond *> &nonBonds)
{
   this->nbVec = nonBonds;
}


energy::~energy()
{
}

void energy::freezeHeavy()   {this->heavyFreeze = true;};
void energy::unFreezeHeavy() {this->heavyFreeze = false;}

void energy::EandF() {
    clearForces(); 
    setAngleBendForces();
    setBondStretchForce();
    setTorsionalForces();
    
    bondStretchEnergy();
    angleBendEnergy();
    torsionalEnergy();

    try {
       nonBondEandF();
    } catch(int num) {
    }

    energies[0] = 0;
    for (int i=1; i<6; i++) 
    	energies[0] += energies[i];
}

void energy::EandF(vector<float> &Energies) {   
   clearForces(); 
   setAngleBendForces();

   try {
      setBondStretchForce();
   } catch (int num) {
   }

   setTorsionalForces();
   
    
   bondStretchEnergy();
   angleBendEnergy();
   torsionalEnergy();
   try {
      nonBondEandF();
   } catch(int num) {
   }
    
   Energies.resize(6);
   Energies[0] = 0.0;
   energies[0] = 0.0;
   for (int i=1; i<6; i++) { 
       energies[0] += energies[i];
       Energies[i] = energies[i];
       Energies[0] += energies[i];   
   }
}


double energy::nonBondEandF() {
   if (nonbondVec.size() == 0) {
      return 0.0;
   }

  /** Intitialize our energies.  energies[4] == elec   energies[5] == vdw */
    energies[4] = energies[5] = 0;
    
    double vdwE = 0;
    double chargeE = 0;
    for (int i=0; i<nonbondVec.size(); i++) {
	nonBond *nb = nonbondVec[i];
        //dynabase::nonBond *base = nb->_base;	
	atom *atm1 = nb->atm1;
	atom *atm2 = nb->atm2;

	if (!atm1->frozen || !atm2->frozen) {
	float *cd1 = atm1->fCoords;
	float *cd2 = atm2->fCoords;		
	
	double a = cd1[0] - cd2[0];
	double b = cd1[1] - cd2[1];
	double c = cd1[2] - cd2[2];
		
	double dist = (a*a + b*b + c*c);
        //double dist = nbVec->distance();
        if (dist < 100.0) {
	dist = sqrt(dist);	
	if (dist < .0000000001) {
	   dist = .0000000001;
	}
	dist = 1.0/dist;
		
	double dist2 = dist*dist;
	double dist3 = dist2*dist;
	double dist6 = dist3*dist3;
	double dist12 = dist6*dist6;

		
        // (sig1 + sig2)*.5
        //Sigma is read in as 1/2 sigma thus no divide 
        float sig = (atm1->getSigma() + atm2->getSigma());
   	float sig2 = sig*sig;
   	float sig3 = sig2*sig;

	double sigma6 = sig3*sig3;	
	double sigma12 = sigma6*sigma6;

        //Epsilon is mixed as sqrt(ep1*ep2)
        //Epsilon is saved as sqrt(ep) so no sqrt
	float epsilon = atm1->getEpsilon() *atm2->getEpsilon();
	float chrg = atm1->getCharge() * atm2->getCharge();
        double cForce = 0;
        if (distDep) { 
           cForce = 665.0*(chrg)*dist3;//*dielectric;
           chargeE = chrg * dist2;
        } else {
           cForce = 332.5*(chrg)*dist2 * dielectric;
           chargeE = chrg * dist;
        }

	double value = 24*epsilon*dist2*(2*(sigma12*dist12) -  (sigma6*dist6));
	
	double tot = (cForce + value)*nb->scaleFactor;
	double Force[3];
	
	Force[0] = a*tot;
	Force[1] = b*tot;
	Force[2] = c*tot;

        if (Force[0] != Force[0]) {
           throw -10;
	   return 0.0;
        }
        if (Force[1] != Force[1]) {
           throw -10;
	   return 0.0;
        }
        if (Force[2] != Force[2]) {
	   throw -10;
           return 0.0;
        }

	for (int i=0; i<3; i++) {
	   atm1->forces[i] += Force[i];
	   atm2->forces[i] -= Force[i];
	}
	
	if (sigma6 == 0 || sigma12 == 0) vdwE = 0;
	else vdwE = epsilon * (sigma12*dist12 - sigma6*dist6);

	energies[4] += chargeE*nb->scaleFactor;
	energies[5] += vdwE*nb->scaleFactor;
        }
        }
    }
    energies[4] *= 332.5*dielectric;
    energies[5] *= 4.0;
  
    return energies[4] + energies[5];

}

void energy::setConstDielectric(float die) {
   /** Division here for eficiency */
   dielectric = 1.0/die; 
}

   

double energy::bondStretchEnergy() {
    energies[1] = 0;
    if (bondVec.size() == 0) return 0.0;
    
    for (int i=0; i<bondVec.size(); i++) {
    	bond *bd = bondVec[i];
	atom *atm1 = bd->fromAtom();
	atom *atm2 = bd->toAtom();
	
	double dist = distance(atm1->fCoords, atm2->fCoords);
	if (dist < .0000001) dist = .0000001;
	double a = dist - bd->refLen;
	energies[1] += bd->K*(a*a);
    }
    return energies[1];
}

float energy::bondStretchEnergy(vector<bond *> &bondVec) {
    float energy = 0;
    if (bondVec.size() == 0) return 0.0;
    
    for (int i=0; i<bondVec.size(); i++) {
    	bond *bd = bondVec[i];
	atom *atm1 = bd->fromAtom();
	atom *atm2 = bd->toAtom();
	
	float dist = distance(atm1->fCoords, atm2->fCoords);
	if (dist < .0000001) dist = .0000001;
	float a = dist - bd->refLen;
	energy += bd->K*(a*a);
    }
    return energy;
}

double energy::angleBendEnergy() {
    energies[2] = 0;
    if (angleVec.size() == 0) return 0.0;
    
    for (int i=0; i<angleVec.size(); i++) {
    	angle *ang = angleVec[i];
	double Ang = ang->degree()*3.1415926535/180;
	
	if (Ang < .0001) Ang = .0001;
	double a = Ang - (3.1415926535/180*ang->refAngle);
	energies[2] += ang->K*(a*a);
    }
    return energies[2];
}

float energy::angleBendEnergy(vector<angle *> &angleVec) {
    float energy = 0;
    if (angleVec.size() == 0) return 0.0;
    
    for (int i=0; i<angleVec.size(); i++) {
    	angle *ang = angleVec[i];
	float Ang = ang->degree()*3.1415926535/180;
	
	if (Ang < .0001) Ang = .0001;
	float a = Ang - (3.1415926535/180*ang->refAngle);
	energy += ang->K*(a*a);
    }
    return energy;
}

double energy::torsionalEnergy() {
    energies[3] = 0;
    if (torVec.size() == 0) return 0.0;

    for (int i=0; i<torVec.size(); i++) {
        torsion *tor = torVec[i];
	   double theta = tor->degree()*degToRad;
	   double gamma = tor->gamma*degToRad;
	   double a = 1 + cos(tor->n*theta - gamma);
	   energies[3] += tor->V*a;//*180/3.1415926535;
    }
    return energies[3];
}

float energy::torsionalEnergy(bond *bd) {
   molecule *mol = dynamic_cast<molecule *>(bd->lastParent());
   if (mol->torsions.size()  == 0) return 0.0;
   atom *atm1 = bd->from;
   atom *atm2 = bd->to;
   vector<torsion *> torVec;
   for (int i=0; i<mol->torsions.size(); i++) {
      torsion *t = mol->torsions[i];
      int count = 0;
      if (t->atm2 == atm2 || t->atm2 == atm1) count++;
      if (t->atm3 == atm2 || t->atm3 == atm1) count++;
      
      if (count == 2) 
         torVec.push_back(t);
   }
   
   return torsionalEnergy(torVec);
}

float energy::torsionalEnergy(vector<torsion *> &torVec) {
    float energy = 0;
    if (torVec.size() == 0) return 0.0;
    for (int i=0; i<torVec.size(); i++) {
        torsion *tor = torVec[i];
        float theta = tor->degree()*degToRad;
	float gamma = tor->gamma*degToRad;
	float a = 1 + cos(tor->n*theta - gamma);
	energy += tor->V*a;//*180/3.1415926535;
    }
    return energy;
}

float energy::nonBondEnergy(vector<nonBond *> &nonBondVec) {
   float vdwE = 0;
   float chargeE = 0;	
   float tChargeE = 0;
   float tVanE = 0;
   for (int i=0; i<nonbondVec.size(); i++) {
      nonBond *nb = nonbondVec[i];
      atom *atm1 = nb->atm1;
      atom *atm2 = nb->atm2;
      if (!atm1->frozen || !atm2->frozen) {	
         float *cd1 = atm1->fCoords;
         float *cd2 = atm2->fCoords;		
	
         float a = cd1[0] - cd2[0];
         float b = cd1[1] - cd2[1];
         float c = cd1[2] - cd2[2];
		
         float dist = sqrt(a*a + b*b + c*c);
		
         if (dist < .0000000001) {
            dist = .0000000001;
         }
         dist = 1.0/dist;
		
         float dist2 = dist*dist;
         float dist3 = dist2*dist;
         float dist6 = dist3*dist3;
         float dist12 = dist6*dist6;
	
         float sig = (atm1->getSigma() + atm2->getSigma());
         //float sig = (atm1->sigma + atm2->sigma);
         float sig2 = sig*sig;
         float sig3 = sig2*sig;

         float sigma6 = sig3*sig3;	
         float sigma12 = sigma6*sigma6;
	
         float epsilon = atm1->getEpsilon() * atm2->getEpsilon();
         float chrg = atm1->getCharge() * atm2->getCharge();

         chargeE = chrg * dist;
        	
	if (sigma6 == 0 || sigma12 == 0) vdwE = 0;
	else vdwE = epsilon * (sigma12*dist12 - sigma6*dist6);
		
	
	
	tChargeE += chargeE*nb->scaleFactor;
	tVanE += vdwE*nb->scaleFactor;
        }
    }
    tChargeE *= 332.5*dielectric;
    tVanE *= 4.0;
    return tChargeE + tVanE;
}

void energy::setBondStretchForce() {
if (bondVec.size() == 0) return;
   //for (int i=0; i<mol->bonds.size(); i++) {
   for (int i=0; i<bondVec.size(); i++) {
      bond *bd = bondVec[i];
      //bond *bd = mol->bonds[i];
      atom *atm1 = bd->fromAtom();
      atom *atm2 = bd->toAtom();
		
      double dist = distance(atm1->fCoords, atm2->fCoords);	
		
      dist /= 1.0;
		
      double dedr = 2*bd->K*(dist - bd->refLen);
      double Forces[3];
      Forces[0] = -dedr * (atm1->fCoords[0] - atm2->fCoords[0]) * dist;
      Forces[1] = -dedr * (atm1->fCoords[1] - atm2->fCoords[1]) * dist;
      Forces[2] = -dedr * (atm1->fCoords[2] - atm2->fCoords[2]) * dist;
	
      if (Forces[0] != Forces[0] || Forces[1] != Forces[1] || Forces[2] != Forces[2]) {
         throw 10;
         return;
      }
		
      for (int i=0; i<3; i++) {
	 atm1->forces[i] += Forces[i];
	 atm2->forces[i] -= Forces[i];
      }
   }
}

void energy::setAngleBendForces() {
if (angleVec.size() == 0) return;
//for (int i=0; i<mol->angles.size(); i++) {

for (int i=0; i<angleVec.size(); i++) {
    	angle *ang = angleVec[i];
	//angle *ang = mol->angles[i];
	atom *atm1 = ang->front;
	atom *atm2 = ang->mid;
	atom *atm3 = ang->back;
	double deg = ang->degree();
	//double degToRad = 3.1415926535/180.0;

	double DEDTheta = 2*ang->K*(deg*degToRad - ang->refAngle*degToRad);
	double abDist = distance(atm1->fCoords, atm2->fCoords);
	double bcDist = distance(atm2->fCoords, atm3->fCoords);
	double acDist = distance(atm1->fCoords, atm3->fCoords);
	
	double theta = deg*degToRad;
	
	double sinTheta = sin(theta);
	double cosTheta = cos(theta);
	
	double div1 = 1.0/(sinTheta * abDist*abDist*bcDist);
	double div3 = 1.0/(sinTheta * bcDist*bcDist*abDist);
	
	double Forces1[3], Forces3[3], Forces2[3];
	Forces1[0] = -DEDTheta*( cosTheta*bcDist*(atm1->fCoords[0] - atm2->fCoords[0]) + abDist*(atm2->fCoords[0] - atm3->fCoords[0]) ) * div1;
	Forces1[1] = -DEDTheta*( cosTheta*bcDist*(atm1->fCoords[1] - atm2->fCoords[1]) + abDist*(atm2->fCoords[1] - atm3->fCoords[1]) ) * div1;
	Forces1[2] = -DEDTheta*( cosTheta*bcDist*(atm1->fCoords[2] - atm2->fCoords[2]) + abDist*(atm2->fCoords[2] - atm3->fCoords[2]) ) * div1;
	
	Forces3[0] = -DEDTheta*( cosTheta*abDist*(atm3->fCoords[0] - atm2->fCoords[0]) + bcDist*(atm2->fCoords[0] - atm1->fCoords[0]) ) * div3;
	Forces3[1] = -DEDTheta*( cosTheta*abDist*(atm3->fCoords[1] - atm2->fCoords[1]) + bcDist*(atm2->fCoords[1] - atm1->fCoords[1]) ) * div3;
	Forces3[2] = -DEDTheta*( cosTheta*abDist*(atm3->fCoords[2] - atm2->fCoords[2]) + bcDist*(atm2->fCoords[2] - atm1->fCoords[2]) ) * div3;
	
	double div2a = 1.0/(sinTheta*abDist*abDist*bcDist*bcDist);
	double div2b = 1.0/(sinTheta*abDist*bcDist);
	Forces2[0] = cosTheta*(abDist*abDist*(atm2->fCoords[0] - atm3->fCoords[0]) + bcDist*bcDist*(atm2->fCoords[0]-atm1->fCoords[0])) *div2a;
	
	Forces2[0] += ((atm1->fCoords[0] - 2*atm2->fCoords[0] + atm3->fCoords[0])) * div2b;
	
	Forces2[0] *= -DEDTheta;
	
	Forces2[1] = cosTheta*(abDist*abDist*(atm2->fCoords[1] - atm3->fCoords[1]) + bcDist*bcDist*(atm2->fCoords[1]-atm1->fCoords[1])) * div2a;
	
	Forces2[1] += ((atm1->fCoords[1] - 2*atm2->fCoords[1] + atm3->fCoords[1])) *div2b;
	
	Forces2[1] *= -DEDTheta;
	
	Forces2[2] = cosTheta*(abDist*abDist*(atm2->fCoords[2] - atm3->fCoords[2]) + bcDist*bcDist*(atm2->fCoords[2]-atm1->fCoords[2])) * div2a;
	
	Forces2[2] += ((atm1->fCoords[2] - 2*atm2->fCoords[2] + atm3->fCoords[2])) *div2b;
	
	Forces2[2] *= -DEDTheta;
	
	/*
	for (int i=0; i<3; i++) {
	   if (Forces1[i] > 10000000) Forces1[i] = 10000000;
	   else if (Forces1[i] < -10000000) Forces1[i] = -10000000;
	}
	for (int i=0; i<3; i++) {
	   if (Forces2[i] > 10000000) Forces2[i] = 10000000;
	   else if (Forces2[i] < -10000000) Forces2[i] = -10000000;
	}
	for (int i=0; i<3; i++) {
	   if (Forces3[i] > 10000000) Forces3[i] = 10000000;
	   else if (Forces3[i] < -10000000) Forces3[i] = -10000000;
	}
	*/

        
       	
	for (int i=0; i<3; i++) {
            if (Forces1[i] != Forces1[i] || Forces2[i] != Forces2[i] || Forces3[i] != Forces3[i]) {
            }
	    atm1->forces[i] += Forces1[i];
	    atm2->forces[i] += Forces2[i];
	    atm3->forces[i] += Forces3[i];
	}
    }      
}

void energy::setTorsionalForces() {
   if (torVec.size() == 0) return;
   for (int i=0; i<torVec.size(); i++) {
        torsion *tor = torVec[i];

	atom *atm1 = tor->atm1;
	atom *atm2 = tor->atm2;
	atom *atm3 = tor->atm3;
	atom *atm4 = tor->atm4;
	
	float cd1[3], cd2[3];

    	float *a = atm1->fCoords;
    	float *b = atm2->fCoords;
    	float *c = atm3->fCoords;
    	float *d = atm4->fCoords;

    	//This section is were we calculate the torsion angle
	float orig[3]; orig[0] = 0; orig[1] = 0; orig[2] = 0;
   	float e[3], f[3];
   	vSub( a, b, cd1 );
   	vSub( c, b, cd2 );
   	vCross( cd1, cd2, e );

   	vSub( d, c, cd1 );
   	vSub( b, c, cd2 );
   	vCross( cd2, cd1, f );

    	float dp = vDot(e, f);
    	float l1 = vLength(e);
    	float l2 = vLength(f);
	
	float distE = distance(orig, e);
	float distE2 = distE*distE;
	
	float distF = distance(orig, f);
	float distF2 = distF*distF;
	
	float distEF = distE*distF;
	
	float tmp = dp/(l1*l2);
	//float cosTau = tmp;
    	if (tmp > 1 ) tmp = 1;
    	if (tmp < -1) tmp = -1;
    
	float tau = 0;
	//You may need to change this back to degree
	
	float tmp2[3];
	vSub(c, d, tmp2);
	float check = vDot(e, tmp2);
	
	double radToDeg = 180/3.1415926535;
        //double degToRad = 3.1415926535/180;
	if (check < 0) tau = acos(tmp);
	else           tau = (180 - acos(tmp)*radToDeg)*degToRad;

	tau = acos(tmp);
	
	double DEDTau = 0;
	if ((tau*radToDeg - tor->gamma) > 0) DEDTau = -tor->n*tor->V*sin(tor->n*(tau - tor->gamma*degToRad));
	else                                 DEDTau = tor->n*tor->V*sin(tor->n*(tau - tor->gamma*degToRad));
	
	//This is a torsional correction...trying to get the out of plane bending
	//DEDTau /= 3;
	//###################   This is atom 1 section.
	double F1[3];
	double denom;
	
	double sinTau = sin(tau);
	double cosTau = cos(tau);
	
	denom = sinTau*distE2*distF;
	
	if (denom < .000000001) { 
	   denom = 1.0/(.000000001);
	} else {
	    denom = 1.0/denom;
	}
	
	double TMP = cosTau*distF;
	double part0 = TMP*e[0];
	double part1 = TMP*e[1];
	double part2 = TMP*e[2];
	F1[0] = DEDTau*((c[2]-b[2])*(part1 - distE*f[1]) + (b[1]-c[1])*(part2 - distE*f[2]))*denom;	 
	F1[1] = DEDTau*((c[0]-b[0])*(part2 - distE*f[2]) + (b[2]-c[2])*(part0 - distE*f[0]))*denom;	
	F1[2] = DEDTau*((c[1]-b[1])*(part0 - distE*f[0]) + (b[0]-c[0])*(part1 - distE*f[1]))*denom;	
	
	for (int j=0; j<3; j++) atm1->forces[j] += F1[j];
	
	//#########################  This is atm b;
	double F2[3], denom2;
	//denom2 = sinTau*distE2*distF2;
	denom2 = denom/distF;
	
	//if (denom2 < .0000001) { denom2 = 1.0/.0000001;}
	//else { denom2 = 1.0/denom2;}
	
	//double part0a = part0*distF; //cosTau*distF2*e[0]
	//double part1a = part1*distF;  //cosTau*distF2*e[1]
	//double part2a = part2*distF;  //cosTau*distF2*e[2]
	
	double aPart1 = ((a[2]-c[2])*(cosTau*distF2*e[1] - distEF*f[1]) +
		      (d[2]-c[2])*(cosTau*distE2*f[1] - distEF*e[1]))*denom2;
		  
	double bPart1 = ((c[1]-d[1])*(cosTau*distE2*f[2] - distEF*e[2]) + 
		      (c[1]-a[1])*(cosTau*distF2*e[2] - distEF*f[2]))*denom2;
		      
	F2[0] = DEDTau*(aPart1 + bPart1);
	
	double aPart2 = ((a[0]-c[0])*(cosTau*distF2*e[2] - distEF*f[2]) +
		      (d[0]-c[0])*(cosTau*distE2*f[2] - distEF*e[2]))*denom2;
		  
	double bPart2 = ((c[2]-d[2])*(cosTau*distE2*f[0] - distEF*e[0]) + 
		      (c[2]-a[2])*(cosTau*distF2*e[0] - distEF*f[0]))*denom2;
		      
	F2[1] = DEDTau*(aPart2 + bPart2);
	
	double aPart3 = ((a[1]-c[1])*(cosTau*distF2*e[0] - distEF*f[0]) +
		      (d[1]-c[1])*(cosTau*distE2*f[0] - distEF*e[0]))*denom2;
		  
	double bPart3 = ((c[0]-d[0])*(cosTau*distE2*f[1] - distEF*e[1]) + 
		      (c[0]-a[0])*(cosTau*distF2*e[1] - distEF*f[1]))*denom2;
		      
	F2[2] = DEDTau*(aPart3 + bPart3);
	
	for (int j=0; j<3; j++) atm2->forces[j] += F2[j];
	
	//#########################  This is atm c;
	double F3[3], denom3;
	denom3 = denom2;
	
	double aaPart1 = ((b[2]-a[2])*(cosTau*distF2*e[1] - distEF*f[1]) +
			(b[2]-d[2])*(cosTau*distE2*f[1] - distEF*e[1]))*denom3;
			
	double bbPart1 = ((d[1]-b[1])*(cosTau*distE2*f[2] - distEF*e[2]) +
			(a[1]-b[1])*(cosTau*distF2*e[2] - distEF*f[2]))*denom3;
			
	F3[0] = DEDTau*(aaPart1 + bbPart1);
	
	double aaPart2 = ((b[0]-a[0])*(cosTau*distF2*e[2] - distEF*f[2]) +
			(b[0]-d[0])*(cosTau*distE2*f[2] - distEF*e[2]))*denom3;
			
	double bbPart2 = ((d[2]-b[2])*(cosTau*distE2*f[0] - distEF*e[0]) +
			(a[2]-b[2])*(cosTau*distF2*e[0] - distEF*f[0]))*denom3;
			
	F3[1] = DEDTau*(aaPart2 + bbPart2);
	
	double aaPart3 = ((b[1]-a[1])*(cosTau*distF2*e[0] - distEF*f[0]) +
			(b[1]-d[1])*(cosTau*distE2*f[0] - distEF*e[0]))*denom3;
			
	double bbPart3 = ((d[0]-b[0])*(cosTau*distE2*f[1] - distEF*e[1]) +
			(a[0]-b[0])*(cosTau*distF2*e[1] - distEF*f[1]))*denom3;
			
	F3[2] = DEDTau*(aaPart3 + bbPart3);
	
	for (int j=0; j<3; j++) atm3->forces[j] += F3[j];
	
	//########################### Thisis for atom e
	
	double F4[3], denom4;
	//denom4 = sinTau*distF2*distE;
	denom4 = denom2*distE;
	//if (denom4 < .0000001) { denom4 = 1.0/.0000001;}
	//else {denom4 = 1.0/denom4;}
	
	F4[0] = DEDTau*((c[2]-b[2])*(cosTau*distE*f[1] - distF*e[1]) +
		(b[1]-c[1])*(cosTau*distE*f[2] - distF*e[2]))*denom4;
	
	F4[1] = DEDTau*((c[0]-b[0])*(cosTau*distE*f[2] - distF*e[2]) +
		(b[2]-c[2])*(cosTau*distE*f[0] - distF*e[0]))*denom4;
		
	F4[2] = DEDTau*((c[1]-b[1])*(cosTau*distE*f[0] - distF*e[0]) +
		(b[0]-c[0])*(cosTau*distE*f[1] - distF*e[1]))*denom4;
		
	for (int j=0; j<3; j++) atm4->forces[j] += F4[j];
   }
}

void energy::setNonBondForces(molecule *mol) {
}

void energy::clearForces() {
	for (int i=0; i<atomVec.size(); i++) atomVec[i]->zeroForces();
}

void energy::messUpMol(molecule *mol, float amount) {
    for (int i=0; i<mol->atoms.size(); i++) {
	atom *atm = mol->atoms[i];
	for (int i=0; i<3; i++) {
	   int num = rand() % 2;
	   if (num == 0) atm->fCoords[i] += amount;
	   else atm->fCoords[i] -= amount;
	}		
    }	

}



void energy::stochasticSearch(int maxIter) {
	float bestE = 100000;
	vector< float > bestCoords;
	for (int i=0; i<maxIter; i++) {
		float currE = CG_minimize(maxIter, .05, 0.1, .005);
		if (currE < bestE) {
		   bestE = currE;
		   bestCoords.clear();
		   list<molecule *>::iterator molIter = molList->begin();
		   for (molIter; molIter != molList->end(); molIter++) {
	    	   molecule *mol = *molIter;
		   for (int j=0; j<mol->atoms.size(); j++) {
			for (int k=0; k<3; k++) bestCoords.push_back(mol->atoms[j]->fCoords[k]);
			
		   }
		   }
			
		}
	}
	
	int count = 0;
	list<molecule *>::iterator molIter = molList->begin();
	for (molIter; molIter != molList->end(); molIter++) {
	molecule *mol = *molIter;
	for (int i=0; i<mol->atoms.size(); i++) {
	   atom *atm = mol->atoms[i];
	   for (int j=0; j<3; j++) {atm->fCoords[j] = bestCoords[count]; count++;}
	}
	}
}


float energy::SD_minimize(int maxIter, float rmsef, float maxForce, float minEDiff) {
	static int minCount = 0;
	//messUpMol(mol, 10);
	stepSize = .000001;
	double currE = 0;
	    
	    double initEnergy = 1000000;//totalEnergy(mol, 0);
	    double prevRMS = 5000000;
	    currE = initEnergy;
	    int count = 0;
	    iteration = 0;
	    for (int iteration=0; iteration<maxIter; iteration++) {  
				
		//vector<float> energies(5);
		//EandF(energies);
		EandF();
		currE = energies[4];
		
		mol->potEnergy[0] = energies[0];
    		mol->potEnergy[1] = energies[1];
    		mol->potEnergy[2] = energies[2];
    		mol->potEnergy[3] = energies[3];
    		mol->potEnergy[4] = energies[4] + energies[5];
	
		rms = 0;
		
		//Determine the gamma && rms parametes
		double top, bottom, top2;
		top = bottom = 0;
		float largestForce = -1000;
		for (int j=0; j<atomVec.size(); j++) {
		   atom *atm = atomVec[j];
		   for (int k=0; k<3; k++) {
			rms  += atm->forces[k]*atm->forces[k];
			float tmp = abs(atm->forces[k]);
			if (tmp > maxForce) largestForce = tmp;
		   }
		}
		
		rms = sqrt(rms/(3*atomVec.size()));

		if (iteration % 1 == 0) {
        //	   for (int i=0; i< 6; i++) ////////////cout << setw(12) << energies[i];
	//	   ////////////cout << setw(12) <<  rms << setw(12) << stepSize << endl;  
		   setInfoToEnergy(iteration); 
		}
		
		if (rms < rmsef && largestForce < maxForce) {
		   break;
		}
		
		float eDiff = abs(currE-initEnergy);
		if (eDiff < minEDiff && rms < 0.5) {
		  break;
		}
	
		moveAtomsSD(stepSize);
		if ( currE < initEnergy) {
			stepSize *= 1.2;
			if (stepSize > .5 ) stepSize = .5;
		} else {
			stepSize *= 0.5;
			if (stepSize < .000001) stepSize = .000001;	
		}		
		prevRMS = rms;
		initEnergy = currE;
	    }

	return currE;
}

float energy::CG_minimize(int maxIter, float rmsef, float maxForce, float minEDiff) {

   static int minCount = 0;
   clearForces();
	

   stepSize = .0001;
   double currE = 0;
   vector< vector<double> > prevForces(atomVec.size());
   vector< vector<double> > prevDir(atomVec.size());
   vector< vector<double> > currDir(atomVec.size());
   for (int i=0; i<prevForces.size(); i++) {
      for (int j=0; j<3; j++) {
         prevForces[i].push_back(0);
	 prevDir[i].push_back(0);
	 currDir[i].push_back(0);
      }
		
		
   }

   double initEnergy = 1000000;//totalEnergy(mol, 0);
   double prevRMS = 5000000;
   currE = initEnergy;
   int count = 0;
   iteration = 0;
   for (iteration=0; iteration<maxIter; iteration++) { 
      if (stop == true) break;		
      
      EandF();
      currE = energies[0];
	
      mol->potEnergy[0] = energies[0];
      mol->potEnergy[1] = energies[1];
      mol->potEnergy[2] = energies[2];
      mol->potEnergy[3] = energies[3];
      mol->potEnergy[4] = energies[4] + energies[5];
      rms = 0;
      if (iteration % 10 == 0) 
         setInfoToEnergy(iteration);
      //Determine the gamma && rms parametes
      double top, bottom, top2;
      top = bottom = 0;
      double largestForce = -100;
      for (int j=0; j<atomVec.size(); j++) {
         atom *atm = atomVec[j];
         for (int k=0; k<3; k++) {
            if (atm->forces[k] != atm->forces[k]) {
                QMessageBox::critical(0, "Error", "NaN in CG_minimize.  Operation will not continue");
                return 0.0;
            }

	    top  += atm->forces[k]*atm->forces[k];
	    top2 += (atm->forces[k] - prevForces[j][k])*atm->forces[k];
	    bottom += prevForces[j][k] * prevForces[j][k];
            double tmp = abs(atm->forces[k]);
            if (tmp > maxForce) largestForce = tmp;
         }
      }
      double gamma = 0;
		
      if (bottom == 0) gamma = 0.0;  //gradient was zero
      else gamma = top/bottom;
      if (gamma > 1) gamma = 1;
	
      double currRMS = 0;
      for (int j=0; j<currDir.size(); j++) {
         atom *atm = atomVec[j];
	 for (int k=0; k<3; k++) {
            currDir[j][k] = atm->forces[k] + gamma*prevDir[j][k];
            currRMS += currDir[j][k] * currDir[j][k];
            prevForces[j][k] = atm->forces[k];
	    atm->forces[k] = currDir[j][k]; //This assignment makes it possible to use moveAtomsSD(stepSize)
	    prevDir[j][k] = currDir[j][k];
         }    
      }

      currRMS = sqrt(currRMS/(3*atomVec.size()));
      rms = sqrt(top/(3*atomVec.size()));
		                
		
      if (rms < rmsef && largestForce < maxForce) {
	 break;
      }
		
      float eDiff = abs(currE-initEnergy);
      if (eDiff < minEDiff && rms < 0.5 ) {
         if (update) {
         }
         break;
      }
 
      moveAtomsSD(stepSize);
      if ( currE < initEnergy) {
         stepSize *= 1.2;
	 if (stepSize > .5 ) stepSize = .5;
      } else {
	 stepSize *= 0.5;
         if (stepSize < .00001) stepSize = .00001;	
      }		
   
      prevRMS = rms;
      initEnergy = currE;
   }
    
   setInfoToEnergy(iteration);

   return currE;
}

void energy::moveAtomsSD(double stepSize) {
   for (int i=0; i<atomVec.size(); i++) {
      atom *atm = atomVec[i];
      if (!atm->frozen) {
         atm->fCoords[0] += stepSize*atm->forces[0]/rms;
         atm->fCoords[1] += stepSize*atm->forces[1]/rms;
         atm->fCoords[2] += stepSize*atm->forces[2]/rms;
      }
    }
}
float energy::MC_fb(int maxIter, float temp) {
   view->doc->db.writeSDF(outFile.c_str(), mol, 0);
   //float temp = 300;
   //messUpMol(mol, 10);
   float stepSize = .0001;
   //vector<float> energies(5);
   //EandF(energies);
   EandF();
   float currE = energies[0];
	
   mol->potEnergy[0] = energies[0];
   mol->potEnergy[1] = energies[1];
   mol->potEnergy[2] = energies[2];
   mol->potEnergy[3] = energies[3];
   mol->potEnergy[4] = energies[4] + energies[5];
   float prevE = currE;
   
   float accept = 1;
   float reject = 1;
   
   float const2 = 1.0/100000000;
   
   float boltzman = 1.0/(.001987*temp);
		
    mol->potEnergy[0] = energies[4];
    mol->potEnergy[1] = energies[0];
    mol->potEnergy[2] = energies[1];
    mol->potEnergy[3] = energies[2];
    mol->potEnergy[4] = energies[3];
   int atomNum = 0;
   for (int i=0; i<1000000; i++) {
      if (stop == true) break;
      if (i % 100 == 0) {
         
	 float ratio = accept/reject;
	 mol->potEnergy[0] = energies[4];
         mol->potEnergy[1] = energies[0];
         mol->potEnergy[2] = energies[1];
         mol->potEnergy[3] = energies[2];
         mol->potEnergy[4] = energies[3];
	 accept = 1;
	 reject = 1;
	 
	 if (ratio > .5) stepSize -= .001;
	 if (ratio < .5) stepSize += .001;
         setInfoToEnergy(iteration);	 
	 
      }
      //atomNum = rand() % atomVec.size();
      vector<float> cd1(3), cd2(3);
      cd1[0] = -atomVec[atomNum]->forces[0];
      cd1[1] = -atomVec[atomNum]->forces[1];
      cd1[2] = -atomVec[atomNum]->forces[2];
      
      float ran[3];
      for (int i=0; i<3; i++) {
         ran[i] = rand() % 100000; 
	 ran[i] /= 100000;
      }
      normalizef(cd1);
      cd2 = cd1;
      for (int i=0; i<3; i++) {
         float param1 = (ran[i]-cd1[i]) * (ran[i]-cd1[i]);
         cd1[i] = exp(-param1/8.0)/(2.0*2.0);
	 if (rand() % 2 == 0) cd1[i] = cd2[i] + cd1[i];
	 else cd1[i] = cd2[i] - cd1[i];
      }
      normalizef(cd1);
      
      float len = vLength(&cd1[0]);
      
      float *atmCd = atomVec[atomNum]->fCoords;
      float coorHold[3];
      coorHold[0] = atmCd[0];
      coorHold[1] = atmCd[1];
      coorHold[2] = atmCd[2];
      
      
      atmCd[0] += stepSize*cd1[0];
      atmCd[1] += stepSize*cd1[1];
      atmCd[2] += stepSize*cd1[2];
   
      EandF();
      //EandF(energies);
      currE = energies[0];
      
      if (currE > prevE) { //Do matropolis critieris
         float num = rand() % 1000000;
	 num /= 1000000;
	 
	 float test = (currE - prevE)*boltzman;///(.001987*temp);
	 if (num > exp(-test)) {
	   atmCd[0] = coorHold[0];
	   atmCd[1] = coorHold[1];
	   atmCd[2] = coorHold[2];
	   
	   reject++;
	 } else {
	   prevE = currE;
	   accept++;
	 }
      } else {
         prevE = currE;
	 accept++;
      }
      atomNum++;
      if (atomNum == atomVec.size())  atomNum = 0;
      int test = 0;
   }
   return 0.0;
}
float energy::MC(int maxIter, float temp) {  
   view->doc->db.writeSDF(outFile.c_str(), mol, 0);
   float stepSize = .01;
   float tempReduce = temp/maxIter;

   EandF();
   float currE = energies[0];
   float prevE = currE;
   float accept = 1;
   float reject = 1;
   float const2 = 1.0/100000000;
   float boltzman = 1.0/(.001987*temp);
		
   mol->potEnergy[0] = energies[0];
   mol->potEnergy[1] = energies[1];
   mol->potEnergy[2] = energies[2];
   mol->potEnergy[3] = energies[3];
   mol->potEnergy[4] = energies[4] + energies[5];

   int atomNum = 0;
   for (int i=0; i<maxIter; i++) {
      if (stop == true) break;
      if (i % 10 == 0) {
         
	 float ratio = accept/reject;
	 if (i % 10 == 0) {
	   mol->potEnergy[0] = energies[0];
           mol->potEnergy[1] = energies[1];
           mol->potEnergy[2] = energies[2];
           mol->potEnergy[3] = energies[3];
           mol->potEnergy[4] = energies[4] + energies[5]; 
	 }
	 accept = 1;
	 reject = 1;
	 
	 if (ratio > .5) stepSize -= .01;
	 if (ratio < .5) stepSize += .01; 
	 setInfoToEnergy(iteration);
      }
      
      if (i % outIter == 0) {
        view->doc->db.writeSDF(outFile.c_str(), mol, 1);
      }
      atomNum = rand() % atomVec.size();
      vector<float> cd(3);
      cd[0] = rand() % 100000000;
      cd[1] = rand() % 100000000;
      cd[2] = rand() % 100000000;
      
      cd[0] = 2*(cd[0]*const2) -1;
      cd[1] = 2*(cd[1]*const2) -1;
      cd[2] = 2*(cd[2]*const2) -1;      
      
      normalizef(cd);
      
      while (atomVec[atomNum]->frozen) {
         atomNum++;
         if (atomNum == atomVec.size())  atomNum = 0;
      }
      
      float *atmCd = atomVec[atomNum]->fCoords;
      float coorHold[3];
      coorHold[0] = atmCd[0];
      coorHold[1] = atmCd[1];
      coorHold[2] = atmCd[2];
      
      atmCd[0] += stepSize*cd[0];
      atmCd[1] += stepSize*cd[1];
      atmCd[2] += stepSize*cd[2];

      energies[1] = bondStretchEnergy();
      energies[2] = angleBendEnergy();
      energies[3] = torsionalEnergy();
      energies[4] = nonBondEandF();
      energies[0] = energies[1] + energies[2] + energies[3] + energies[4];
      
      currE = energies[0];
      
      if (currE > prevE) { //Do metropolis critieris
         float num = rand() % 1000000;
	 num /= 1000000;
	 
	 float test = (currE - prevE)*boltzman;///(.001987*temp);
	 if (num > exp(-test)) {
	   atmCd[0] = coorHold[0];
	   atmCd[1] = coorHold[1];
	   atmCd[2] = coorHold[2];
	   
	   reject++;
	 } else {
	   prevE = currE;
	   accept++;
	 }
      } else {
         prevE = currE;
	 accept++;
      }
      atomNum++;
      if (atomNum == atomVec.size())  atomNum = 0;
      int test = 0;
      temp = temp-tempReduce;
   }

   return 0.0; //Returning for visual studio
}

float energy::MC_torsional(int maxIter, float temp) {
   Conformation C;
   vector<bond *> rotBonds;
   vector<molecule *> molVec(molList->begin(), molList->end());
   for (int i=0; i<molVec.size(); i++) {
      molecule *mol = molVec[i];  
      C.setRotableBonds(mol, rotBonds);
   }
   if (rotBonds.size() == 0) {
     return 0.0;
   }
   view->doc->db.writeSDF(outFile.c_str(), dynamic_cast<molecule *>(rotBonds[0]->getParent()), 0);
   //C.setUp(molList, rotBonds, string outFile)
   float rotInc = 1.0;
   float tempReduce = 0.0;//temp/maxIter;
   EandF();
   float currE = energies[0];
   float prevE = currE;
   float accept = 1;
   float reject = 1;
   float const2 = 1.0/100000000;
   float boltzman = 1.0/(.001987*temp);
		
   mol->potEnergy[0] = energies[0];
   mol->potEnergy[1] = energies[1];
   mol->potEnergy[2] = energies[2];
   mol->potEnergy[3] = energies[3];
   mol->potEnergy[4] = energies[4] + energies[5];
   int atomNum = 0;
   for (int i=0; i<maxIter; i++) {
      if (stop == true) break;
      if (i % 10 == 0) {
         
	 float ratio = accept/reject;
	 if (i % 10 == 0) {
           mol->potEnergy[3] = energies[3];
           mol->potEnergy[4] = energies[4] + energies[5]; 
	 }
	 accept = 1;
	 reject = 1;
	 
	 if (ratio > .5) rotInc -= 0.25;
	 if (ratio < .5) rotInc += 0.25; 
         
         if (rotInc > 2) rotInc = 2.0;
         if (rotInc < -2) rotInc = -2.0;
	 setInfoToEnergy(i);
      }
      
      if (i % outIter == 0) {
        view->doc->db.writeSDF(outFile.c_str(), mol, 1);
      }
      
      bond *bd = rotBonds[rand() % rotBonds.size()];
      C.rotateBond(dynamic_cast<molecule *>(bd->getParent()), bd, rotInc);
      torsionalEnergy();
      nonBondEandF();
      energies[0] = energies[1] + energies[2] + energies[3];// + energies[5]/100.0;
      
      currE = energies[0];
      
      if (currE > prevE) { //Do metropolis critieris
         float num = rand() % 1000000;
	 num /= 1000000;
	 
	 float test = (currE - prevE)*boltzman;///(.001987*temp);
	 if (num > exp(-test)) {
	   C.rotateBond(dynamic_cast<molecule *>(bd->getParent()),bd, -rotInc);	   
	   reject++;
	 } else {
	   prevE = currE;
	   accept++;
	 }
      } else {
         prevE = currE;
	 accept++;
      }
      atomNum++;
      if (atomNum == atomVec.size())  atomNum = 0;
   }
   return 0.0;
}

void energy::RandVec3(vector<double> &vec) {
   double x, y, s;
   s = 2.0;

   while (s > 1.0) {
      double ran1 = rand() % 1000000; ran1 /=1000000;
      double ran2 = rand() % 1000000; ran2 /=1000000;
      x = 2.0*ran1-1;
      y = 2.0*ran2-1;
      s = x*x + y*y;
   }    
 
   vec[2] = 1.0 - (2.0*s);
   s = 2.0 * sqrt(1.0-s); 
   vec[0] = s*x;
   vec[1] = s*y;
}

void energy::initVelocity(vector<double> &vel) {
   double vMag = 0.50;
   vector<double> vSum(3);
   for (int i=0; i<3; i++) vSum[i] = 0.0;
   
   int numAtom = vel.size()/3; 
   int count = 0;
   for (int i=0; i<numAtom; i++) {
      vector<double> e(3);
      RandVec3(e);
      for(int j=0; j<3; j++) {
         vel[count] = vMag*e[j];
         vSum[j] += vel[count];
      }
   }

   for (int i=0; i<vSum.size(); i++) 
      vSum[i] /= numAtom;

   count = 0;
   for (int i=0; i<numAtom; i++) {
      for (int j=0; j<3; j++) {
         vel[count] -= vSum[j];
      }
   }
}

float energy::leapfrog() {
   vector<double> vel(atomVec.size()*3);
   vector<double> acc(atomVec.size()*3);

   //Initialize velocities
   initVelocity(vel);
   double timeStep = 0.02;
   
   for (int i=0; i<100000; i++) {
      EandF();  
      int count = 0; 
      for (int j=0; j<atomVec.size(); j++) {
         //Move forward
         float *cd = atomVec[j]->fCoords;
         double *force = atomVec[j]->forces;
         double mass = atomVec[j]->getMass();
         for (int k=0; k<3; k++) {
            acc[count] = force[k]/mass;
            vel[count] = vel[count] + timeStep*acc[count];
            cd[k] += timeStep*vel[count];
            count++;
         }
      }
      if (stop == true) break;
   }

   return 0.0;
}

float energy::MD() {
   leapfrog();
   return 0.0;
   //return 0;
   //vector<float> energies(5);
   ofstream outFile("dyn.out", ios::out);
	for (int i=0; i<atomVec.size(); i++) {
	  atom *atm = atomVec[i];
	  outFile <<atm->getNum() << setw(12) << atm->getSigma() << setw(12)<<atm->getEpsilon();
	  outFile <<setw(12) << atm << endl;//atm->charge << endl;
	}
   //EandF(energies); //Get initiali energy
   EandF();
   //vector< vector<float> > prevCoords(atomVec.size()), curCoords(atomVec.size());
   vector< vector<double> > prevCoords(atomVec.size()), curCoords(atomVec.size());

   double avgTemp = 0;
   for (int i=0; i<atomVec.size(); i++) {
     float *cd = atomVec[i]->fCoords;
     prevCoords[i].resize(3);
     curCoords[i].resize(3);
     for (int j=0; j<3; j++) {
	    float num = 0;
	    for (int k=0; k<12; k++) {
		   float ran = rand() % 1000000; 
		   ran /= 1000000;
		   num += (ran);
	    }
	    num -= 6;
	    num /= 100;
	    prevCoords[i][j] = cd[j]-num;
	    curCoords[i][j] = cd[j];
     }
   }
 
   float bestMin = 1000;
   timeStep = .0002;
   float simTemp = 500.0;
   int tAdjust = 0;

   for (int i=1; i<maxIter; i++) {
      if (i % 100 == 0) {
 
         avgTemp /= 100;
         
         if (avgTemp < simTemp) {
            tAdjust = 1;
         } else if (avgTemp > simTemp) {
            tAdjust = -1;
         } else {
            tAdjust = 0;
         }

         avgTemp = 0;
      }
      
      
      
      //This is the NaN check....you had a hard time using a QMessage box here...seg fault && shit
      for (int i=0; i<4; i++) {
         if (!(energies[i] == energies[i]) ) {
            return -10;
         }
      }
      for (int j=0; j<atomVec.size(); j++) {
         float *cd = atomVec[j]->fCoords;
	 double *force = atomVec[j]->forces;
	 for (int k=0; k<3; k++) {
            double accel = 0.0;
            accel =  (force[k]*timeStep/atomVec[j]->getMass());
            cd[k] = (2.0*curCoords[j][k] - prevCoords[j][k]) + accel;///atomVec[j]->atomicNum*2;
            double velocity = ( curCoords[j][k]-prevCoords[j][k] );
            avgTemp += velocity*velocity;
	    prevCoords[j][k] = curCoords[j][k];
	    curCoords[j][k] = cd[k];
	 }
	 
      }

    avgTemp /= mol->atoms.size()*3;
    if (stop == true) break;
     
      EandF();
   }   
}

bool energy::setInfoToEnergy(int iteration) {
   if (update == false) return false;
   QString tmp;
   vector<QString> infoText;
   if (iteration != -1) {
      infoText.resize(7);
      
      infoText[0].append("Iteration:    ");
      tmp.setNum(iteration);
      infoText[0].append(tmp);
   
      infoText[1].append("Total Energy:    ");
      tmp.setNum(energies[0]);
      infoText[1].append(tmp);
   
      infoText[2].append("Bond-Stretch:    ");
      tmp.setNum(energies[1]);
      infoText[2].append(tmp);
   
      infoText[3].append("Angle-Bend:      ");
      tmp.setNum(energies[2]);
      infoText[3].append(tmp);
   
      infoText[4].append("Torsion:            ");
      tmp.setNum(energies[3]);
      infoText[4].append(tmp);
   
      infoText[5].append("Electrostatic:        ");
      tmp.setNum(energies[4]);
      infoText[5].append(tmp);
      
      infoText[6].append("van der Waals:        ");
      tmp.setNum(energies[5]);
      infoText[6].append(tmp);
   } else {
      infoText.resize(6);
      
      infoText[0].append("Total Energy:    ");
      tmp.setNum(energies[0]);
      infoText[0].append(tmp);
   
      infoText[1].append("Bond-Stretch:    ");
      tmp.setNum(energies[1]);
      infoText[1].append(tmp);
   
      infoText[2].append("Angle-Bend:      ");
      tmp.setNum(energies[2]);
      infoText[2].append(tmp);
   
      infoText[3].append("Torsion:            ");
      tmp.setNum(energies[3]);
      infoText[3].append(tmp);
   
      infoText[4].append("Electrostatic:        ");
      tmp.setNum(energies[4]);
      infoText[4].append(tmp);
      
      infoText[5].append("van der Waals:        ");
      tmp.setNum(energies[5]);
      infoText[5].append(tmp);
   
   }
   if (this->viewer) {
      this->viewer->setInfoText(infoText);
   } else {
      molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1010));
      e->setDisplayText(infoText);
      e->sendEvent();
   }

   return true;
}











































