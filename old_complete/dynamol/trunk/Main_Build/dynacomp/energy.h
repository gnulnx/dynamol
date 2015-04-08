/***********************************
 *   Copyright (C) 2004 Dynamol Inc.
 *   john.furr@dynamol.com  
 ************************************/
#ifndef DYNACOMPENERGY_H
#define DYNACOMPENERGY_H
//#include "dynothread.h"
#include <vector>
#include <list>
#include <string>
using std::vector;
using std::list;
using std::string;

//BOOST Includes
#include <boost/shared_ptr.hpp>

/**
@author jfurr
*/

namespace dynabase{
   class nonBond;
}

namespace dynacomp {

class molecule;
class atom;
class bond;
class angle;
class torsion;
class nonBond;

typedef boost::shared_ptr<molecule> molPtr;
typedef boost::shared_ptr<atom> atomPtr;
typedef boost::shared_ptr<bond> bondPtr;
typedef boost::shared_ptr<angle> anglePtr;
typedef boost::shared_ptr<torsion> torPtr;
typedef boost::shared_ptr<nonBond> nbPtr;

class energy;
class forceField;

 //This is the real energy class
class energy {
//
public:
    energy();
    //energy(XmodelView *view, list<molecule *> &molList);
    //energy(XmodelView *view);
    /** I think the constructor should divide the molList into various sections like
        vector<nonBond *>, vector<angle *>, vector<bond *> vector<torsion *>
	
	It will make the speed a little faster
    */
    
    bool run();
    
    /** This function sets up the electrostatic teatment */
    void dieSetup(string method, float value = 1);
    
   // virtual void start();
    
    void initSystem(list<molecule *> &molList, string method, int maxIter, float rmsef, float maxForce, float minEDiff);
    
    //Use this function to minimize a groupd of molecules together...protein/ligand.
    void setUp(list<molecule *> *molList, string method, string ff, string chargeType, int maxIter, float rmsef, float maxForce, float minEDiff);
    
	//Use this function to minimize a single molecule.
    void setUp(molecule *mol, string method, string ff, string chargeType, int maxIter, float rmsef, float maxForce, float minEDiff);

    //Use this function when you define the bonds/angle/torsions/nonBonds/  with calls to energy:;setBonds, etc...
	//See addH for an example for this function
    void setUp(string method, string ff, string chargeType, int maxIter, float rmsef, float maxForce, float minEDiff);

    
    /** This setup is used for performing a MC simulation */
    void mcSetup(list<molecule *> *molList, string method, int maxIter, float Temp, string ffType, string chargeType, string fileName, int outIter);
    
    /** This method is used for performing a md simulation */
    void mdSetup(list<molecule *> *molList, string method, int maxIter, float timeStep, string ffType, string chargeType, string fileName, int outIter);
    
    
    void setMol(molecule *mol); //this is temporary
    void setAtoms(vector<atom *> &Atoms);
    void setBonds(vector<bond *> &Bonds);
    void setAngles(vector<anglePtr> &Angles);
    void setTorsions(vector<torPtr> &Torsions);
    void setNonBonds(vector<nbPtr> &nonBonds);

    //This function looks deprecated
    //void setNonBonds(vector<dynabase::nonBond *> &nonBonds); 
    
    ~energy();
    
    /** This function sets a constant dielectric for the system */
    void setConstDielectric(float die);

    /** This function sets the molView infoText to the energy values */
    bool setInfoToEnergy(int iteration);
    
    /** this function return the energy of a single molecule 
    */
    double molEnergy(molecule *mol);
	//vector<double> molEnergy(molecule *mol);
    
    /** This function is used by the minimization routines */
    //double totalEnergy(molecule *mol, int iteration);
    
    float SD_minimize(int maxIter, float rmsef, float maxForce, float minEDiff);
    float CG_minimize(int maxIter, float rmsef, float maxForce, float minEDiff);
    
    
    float MC(int maxIter, float Temp);
    float MC_fb(int maxIter, float Temp);
    float MC_torsional(int maxIter, float Temp);
    
    float MD();
    float leapfrog();
    void initVelocity(vector<double> &vel, double vmag);
    void RandVec3(vector<double> &vec);
    
    void stochasticSearch(int maxIter);
    
    void freezeHeavy();
    void unFreezeHeavy();
    
    //public slots:
    bool setUpVectors(list<molecule *> &molList);
   
    void setUpdate(bool update);

   
    /** \brief Used to set the Info Text for Dynamol */
    void setInfoText(vector<string> &infoText);
    /** \brief This is a vector to strings that show the update */
    vector<string> *infoText;

   /** \brief Used to stop a simulation
   *
   *  A callign thread should set this value to true to
   *  stop the simulation early
   */
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
    *
    *   If any of the forces produce NaN then false is returned.
    *   otherwise true is retured
    */
    bool EandF(vector<float> &Energies);
    
   double bondStretchEnergy(vector<bond *> &bondVec);
   double angleBendEnergy(vector<anglePtr> &angleVec); 
   double torsionalEnergy(vector<torPtr> &torVec);
   
   /** This function builds a list of torsions from the bonds atoms and then
   *   Sends this list to the torsionalEnergy*vector<torsion *> &torVec function
   */
   float torsionalEnergy(bond *bd);
   
   /** this function assumes a constant dielectric of 1*/
   float nonBondEnergy(vector<nbPtr> &nonBondVec);
   
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
   
   /** \breif Return any error messages
   */
   string getErrorMsg();   
private:
    /** \brief An Error message string */
    string errorMsg;

    list<molecule *> *molList;
    molecule *mol; //This is temporary
    //molView *viewer;
    //XmodelView *view;
    
    float dielectric;
    
    /** This variable is used to determine if a distant dependant dielectric is used */
    bool distDep; 
    
    
    
    
    void messUpMol(molecule *mol, float amount);
    
    /** \brief The Bond Stretch Force
    *
    *   return false if the force is NaN.  
    *   return true otherwise
    */
    bool setBondStretchForce();
 
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

    double nonBondEandF_bsp(float maxDist);

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
    vector<anglePtr> angleVec;
    vector<torPtr> torVec;
    vector<nbPtr> nonbondVec;
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

}; // End Namespace
#endif

