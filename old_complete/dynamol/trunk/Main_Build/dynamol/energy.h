/***************************************************************************
 *   Copyright (C) 2004 Dynamol Inc.                                        *
 *   john.furr@dynamol.com                                                  *
 *                                                                          *
 ****************************************************************************/
#ifndef ENERGY_H
#define ENERGY_H
#include "dynothread.h"
#include <vector>
#include <list>
using std::list;
/**
@author jfurr
*/

class molView;
class molecule;
class energy;
class XmodelView;
class forceField;
class atom;
class bond;
class angle;
class torsion;
class nonBond;

namespace dynabase{
   class nonBond;
}

namespace dynacomp {
   class energy;
   class molecule;
}

//This is theenrgyThread wrapper class
class energyThread :public dynoThread {
   public:
   energyThread( 
               XmodelView *view, 
               string name
               );

   energyThread( 
               XmodelView *view, 
               std::list<molecule *> &molList, 
               string name
               );

   ~energyThread();
   
   void setUp( 
             std::list<molecule *> *molList,  
             string method, 
             string ff, 
             string chargeType, 
             int maxIter, 
             float rmsef, 
             float maxForce, 
             float minEDiff, 
             string dieMethod, 
             float dieValue
             );

   void mcSetup( 
               std::list<molecule *> *molList, 
               string method, 
               int maxIter, 
               float Temp, 
               string ffType, 
               string chargeType, 
               string fileName, 
               int outIter
               );

   void mdSetup( 
               std::list<molecule *> *molList, 
               string method, 
               int maxIter, 
               float timeStep, 
               string ffType, 
               string chargeType, 
               string fileName, 
               int outIter
               );
   
   
   void dieSetup( 
                string method, 
                float value = 1
                );

   void run();

   void run2();//This is for testing purposes

   virtual QString getName();

   virtual void setName( string name );

   virtual void stopThread();

   virtual int rtti(); //returns 3;

private:

   energy *Energy;
   dynacomp::energy *dcEnergy;
   std::list<dynacomp::molecule *> *dcMolList; 
   XmodelView *view;
};

 
 //This is the real energy class
class energy {// : public QObject {
friend class energyThread;
//Q_OBJECT
public:
    energy();
    energy(XmodelView *view, std::list<molecule *> &molList);
    energy(XmodelView *view);
    /** I think the constructor should divide the molList into various sections like
        vector<nonBond *>, vector<angle *>, vector<bond *> vector<torsion *>
	
	It will make the speed a little faster
    */
    
    int run();
    
    /** This function sets up the electrosttic teatment */
    //void dieSetup(string method, float value = 1);
    void dieSetup(string method, float value = 1);
    
   // virtual void start();
    
    void initSystem(std::list<molecule *> &molList, string method, int maxIter, float rmsef, float maxForce, float minEDiff);
    
    //Use this function to minimize a groupd of molecules together...protein/ligand.
    void setUp(std::list<molecule *> *molList, string method, string ff, string chargeType, int maxIter, float rmsef, float maxForce, float minEDiff);
    
	//Use this function to minimize a single molecule.
    void setUp(molecule *mol, string method, string ff, string chargeType, int maxIter, float rmsef, float maxForce, float minEDiff);

    //Use this function when you define the bonds/angle/torsions/nonBonds/  with calls to energy:;setBonds, etc...
	//See addH for an example for this function
    void setUp(string method, string ff, string chargeType, int maxIter, float rmsef, float maxForce, float minEDiff);

    
    /** This setup is used for performing a MC simulation */
    void mcSetup(std::list<molecule *> *molList, string method, int maxIter, float Temp, string ffType, string chargeType, string fileName, int outIter);
    
    /** This method is used for performing a md simulation */
    void mdSetup(std::list<molecule *> *molList, string method, int maxIter, float timeStep, string ffType, string chargeType, string fileName, int outIter);
    
    
    void setMol(molecule *mol); //this is temporary
    void setAtoms(vector<atom *> &Atoms);
    void setBonds(vector<bond *> &Bonds);
    void setAngles(vector<angle *> &Angles);
    void setTorsions(vector<torsion *> &Torsions);
    void setNonBonds(vector<nonBond *> &nonBonds);
    void setNonBonds(vector<dynabase::nonBond *> &nonBonds); 
    
    ~energy();
    
    /** This function sets a constant dielectric for the system */
    void setConstDielectric(float die);

    /** This function sets the molView infoText to the energy values */
    bool setInfoToEnergy(int iteration);
    
    /** this function return the energy of a single molecule 
    */
    double molEnergy(molecule *mol);
    
    /** This function is used by the minimization routines */
    //double totalEnergy(molecule *mol, int iteration);
    
    float SD_minimize(int maxIter, float rmsef, float maxForce, float minEDiff);
    float CG_minimize(int maxIter, float rmsef, float maxForce, float minEDiff);
    
    
    float MC(int maxIter, float Temp);
    float MC_fb(int maxIter, float Temp);
    float MC_torsional(int maxIter, float Temp);
    
    float MD();
    float leapfrog();
    void initVelocity(vector<double> &vel);
    void RandVec3(vector<double> &vec);
    
    void stochasticSearch(int maxIter);
    
    void freezeHeavy();
    void unFreezeHeavy();
    
    //public slots:
    bool setUpVectors(std::list<molecule *> &molList);
   
    void setUpdate(bool update);
protected:
   bool stop;
   
   /** This parameter determines if an energy update will be displayed in the molView windows...by defaul it's value is true.  Use setUpdate to change 
   */
   bool update;
public:   
   /** \brief call all force and energy function
    *
    *    Like the private function but this one takes a 
    *    vector<float> as an argument.  The vector will
    *    be populated with the current run energies
    *
    *    vector<float> Energies(6);
    *    Energies[0] = Total Potential Energy
    *    Energies[1] = Bond Stretch Energy
    *    Energies[2] = Angle Bend Energy
    *    Energies[3] = Torsional Energy
    *    Energies[4] = Charge Energy
    *    Energies[5] = van der Walls Energy
    */
    void EandF(vector<float> &Energies);
    
   float bondStretchEnergy(vector<bond *> &bondVec);
   float angleBendEnergy(vector<angle *> &angleVec); 
   float torsionalEnergy(vector<torsion *> &torVec);
   
   /** This function builds a list of torsions from the bonds atoms and then
   *   Sends this list to the torsionalEnergy*vector<torsion *> &torVec function
   */
   float torsionalEnergy(bond *bd);
   
   /** this function assumes a constant dielectric of 1*/
   float nonBondEnergy(vector<nonBond *> &nonBondVec);
   
   /** \brief Energy Specific for psoConf
   *
   *    This function is specific
   */
   double psoEnergy();
   
   double nonBondEnergy();
   double angleBendEnergy();
   double bondStretchEnergy();
   double torsionalEnergy();
   
   /** \brief Clear the AtomicForces
   *
   */
   void clearForces();
   
private:
    std::list<molecule *> *molList;
    molecule *mol; //This is temporary
    molView *viewer;
    XmodelView *view;
    
    float dielectric;
    
    /** This variable is used to determine if a distant dependant dielectric is used */
    bool distDep; 
    
    
    
    
    void messUpMol(molecule *mol, float amount);
    void setBondStretchForce();
    void setAngleBendForces();
    void setTorsionalForces();
    void setNonBondForces(molecule *mol);
    
    /** \breif call all force and energy functions
    *    
    *    This function is mainly an internal function as 
    *    The user really has no way to gain access to the
    *     various energy terms
    */
    void EandF();
        
    double nonBondEandF();
    double nonBondEandF_optimize();
    
    void moveAtomsSD(double stepSize);
    
    double rms;
    double stepSize;
    
    int iteration;
    
    forceField *ff;
    
    bool heavyFreeze;
    float Temp;
    
    vector<atom *> atomVec;
    vector<bond *> bondVec;
    vector<angle *> angleVec;
    vector<torsion *> torVec;
    vector<nonBond *> nonbondVec;
    vector<dynabase::nonBond *> nbVec;
    
    
    float rmsef, maxForce, minEDiff;
    float timeStep;
    int maxIter;
    string method, chargeType, ffType, outFile;
    
    int outIter;

    float energies[6];
    //QProcess *proc;
    //public slots:
};


#endif





































