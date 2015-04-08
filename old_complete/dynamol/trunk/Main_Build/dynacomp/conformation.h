/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef DYNACOMPCONFORMATION_H
#define DYNACOMPCONFORMATION_H


#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <string>
using std::vector;
using std::list;
using std::deque;
using std::string;

//BOOST Includes
#include <boost/shared_ptr.hpp>

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
class Conformation;
/**
@author jfurr
*/


struct confNode {
   vector<float> angles;
   vector<confNode *> neigh;
   float energy;
};

struct clusterNode {
    list<confNode *> nodes;
    vector<clusterNode *> neigh;
};

struct distPair {
   confNode *n1;
   confNode *n2;
   float dist;
};


class Conformation
{

public:
    Conformation();

    ~Conformation();
    /** This is used to setup the conformation generator */
    bool setUp(list<molecule *> *molList, vector<bond *> &rotBonds, string outFile);
    
    /** This function will generate {n} random conformations of the molecule and */
    //void randomConf(string outFile, molecule *mol, int n, int clusterNum=10, bool min=true,float cutoff=10, float rmse=.001, float minE=.001, float maxForce=.001, int maxIter=5000);

    /** This is used to setup the energy function */
    void eSetup(bool min, float cutoff,  int clusterNum, float rmse, float minE, float maxForce, int maxIter);
    
    /** This function sets up the rotable bonds and assings from and to atom positions */
    void setRotableBonds(molecule *mol, vector<bond *> &BONDS);
    
    /** This function is used to order the bonds.  It sets the from atom to be the one
    *   that is attached to the largest part of the molecule..and the to atom to be 
    *   the one with the shortest part of the molecule.
    *   In addition this function sets the atomsToRotate to all of the atoms on the
    *   'to' side of the bond 
    */
    void orderBonds();
    
    /** This function returns the total number of atoms that are connected to atom atm
    *   This function is used in conjunction with orderBonds
    */
    int connectedAtoms(atom *atm, atom *other, vector<atom *> &atmsToRotate);
   
    
    /** This function builds the list of atoms that should be moved for each rotableBond */
    void buildAtomLists(vector<bond *> &BONDS);
    
    /**This function performs a quick nonBond vdw Check */
    float nonBondCheck(vector<nbPtr> &nonBonds, float cutoff);
    
    /** This function generates a list of essential nonBond terms
    *   Ideally it should really speed up the nonBondCheck function
    */
    void buildNonBondList(molecule *tmpMol, vector<nbPtr> &nonBonds, vector<nbPtr> &frozenNb);
    
    void buildTorsionList(vector<torPtr> &tors, vector<torPtr> &frozTor);
    
    /** This will run the job once it has been setup with setUp*/
    void run();
   
    /** \brief temporary function name */
    //void run2(int num);   
 
    /** This function makes sure that the molecules you plan to use have 
    *   atom types as well as bond, angle, torsion, and nonBond lists
    */
    bool prepMolList(list<molecule *> &molList);
    
    /** These two functions combined perform a rotation about a bond */
    void rotateBond(molecule *mol, bond *bd, float degree);
    void applyRot(molecule *mol, bond *bd, vector<float> &fM);
    
    /**Like the above two functions except these functions assume that the atomsToRotate
    *  vector has been built.  This can be done with a call to orderBonds ()
    */
    void rotateBond(bond *bd, float degree);
    void applyRot(bond *bd, vector<float> &fM);

    /** This performs a systematic search */
    void systematicSearch(molecule *mol, vector<bond *> &rotBonds, string outFile);
    
    /** This assigns the current coords to a molecule 
     *  Use the getMolCoords to build your vector<float> coords    
    */
    void setMolCoords(molecule *mol, const vector<float> &coords);
    
    /** This stores the molecules current coords in the vector<float> coords 
    *   Use the setMol coords to reassign these coords to the molecule 
    */
    void getMolCoords(const molecule *mol, vector<float> &coords);
    
    /** Build the newBond list */
    void setNewBonds(vector<bond *> &newBonds, vector<bond *> &currBonds, molecule *oldMol, molecule *newMol);
   
    /** \brief Rotate the molecule
    *
    *    This function apples a rotation matrix to the moelcule
    */
    void rotMolecule(molecule *mol, vector<float> &fM);
    
    /** \brief Rotate the molecule
    *
    *   Tis function lets you specify a rotation axis and angle to apply to a molecule
    */
    void rotMolecule(molecule *mol, float x, float y, float z, float angle);
 
    /**This function constructs a tree to determine the conformations.
    *  The function returns a list of nodes which contain an vector<float> angles
    *  That can be used to grab the current rotable bonds with.
    *  The reason for this approach was memory management.  You would run 
    *  Our of memory trying to store all the coordinates the other way.
    */
    confNode *buildConfList(deque<confNode *> &confList);
    
    /** This function clusters the conformations by angle */
    void clusterByAngle(deque<confNode *> &nodeList, 
                        int numOfClusters, 
                        deque<confNode *> &best, 
                        deque< deque< deque<confNode *> > > &clusters 
                        );
        
    bool stop;
    
    list<molecule *> *molList;
    vector<bond *> rotBonds;
    vector< vector<atom* > > atomsToRotate;
    string outFile;
    
    bool min;
    float cutoff; 
    int clusterNum;
    float rmse;
    float minE;
    float maxForce;
    int maxIter;

//ERROR Message stuff
   string getErrorMsg();
   string errorMsg;
};

};//End Namespace
#endif





































