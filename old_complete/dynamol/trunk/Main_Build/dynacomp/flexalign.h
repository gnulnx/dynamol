/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   email:  john.furr@dynamol.com
 ***************************************************************************/
#ifndef DYNACOMPFLEXALIGN_H
#define DYNACOMPFLEXALIGN_H

#include <vector>
#include <map>
#include <string>
using std::map;
using std::multimap;
using std::vector;
using std::string;

//Boost Includes
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
class flexAlign;

/** Class point will be used to define sets of points to use in 
*   during the flexible alignment procedure
*/
class point {
   float *coords;
   bool isAro;
   float charge;
   float sigma;
};

/**
@author jfurr
*/
class flexAlign{
friend class flexAlignThread;
public:
    flexAlign();

    ~flexAlign();

    /** \brief Set the Dynamol InfoText Vector
    *
    *   This function sets the dynamol information text in the main screen
    */
    void setInfoText(vector<string> &infoText);

    /** \brief This is a vector to strings that show the update */
    vector<string> *infoText;

   /** This function is used to add a molecules
   *   atoms, bonds, torsions, and nonbonds to
   *   the appropriate lists
   */
   void addMolToSet(molecule *);
  
   /** \brief Clear the current set of atom, bond, angles, torsion, nb's 
   */
   void clearCurrentSet(); 

    void setUp(map<string, string> Params);   
	void PrintParams(); 
    /** \brief Run the alignment
    *
    *    Called after all the alignment parameters have been set.  
    *    This function is usually called from  a flexible alignment 
    *    thread.
    *
    *    The function takes a multimap as a parameter. The poseMap will return 
    *    the coordinates for the various poses mapped to their scores. 
    *    It is up to the calling function to determine what to do with this
    *    information
    */
    bool run(multimap<float, vector<float> > &poseMap);

    /** \brief Check and Save the Pose
    *
    *   Check to see if the pose is less than the min RMSE error of each
    *   of the other poses.  If it is then save it.  If it is very close
    *   to another structure then you should save the one with the best 
    *   score.
    */
    void savePose(multimap<float, vector<float> > &poseMap, float rmse, float tanimoto);
   
    /** \brief Set the template molecule 
    *
    *    The template molecule is the one to which you are aligning
    */
    void setTemplateMolecule(molecule *mol);

    /** \brief Set the alignee
    *
    *    This is the molecule that is moving.  The one that gets aligned
    */
    void setMoleculeToAlign(molecule *mol);
    
    /** \brief Score the alignment
   *
   *    This function scores the alignment
   *    sa = p1p2 exp(-.20 r^2)
   *    
   *    I returns false if the score fails...for example NaN
   *    reached during force calculation
   */
   bool scoreAlignment(molecule *mol1, molecule *mol2, float &score);
   
   /** \brief Minimize
   *
   *    This performs a conjugate gradient minization over
   *    The various forces
   */
   float minimize(molecule *mol, int maxIter, 
                  float rmsef, float maxForce, float minEDiff);

     /** \brief Align molecule centers
   *
   *   Aligns mol2 center of mass with mol1 center of mass
   *   This only perfoms X, Y, Z, transformations
   */
   void alignCenters(molecule *mol1, molecule *mol2); 

   /** \brief Randomize the starting molecule
   *
   *    This function randomly perturbs all rotable bonds
   *    It also randomly rotates the molecule in space
   */
   void randMol(molecule *mol, molecule *mol1);
   
   /** \brief Used to stop the runnignn thread
   *
   *    This variable is set by a flexAlign thread to stop the simulation
   */
   bool stop;

protected:

   /** \brief  The template molecule
   *
   *    pointer to the template molecule
   */
   molecule *templ; 

   /** \brief The molecule to align
   *
   *    Pointer to the molecule which is being aligned
   */
   molecule *toAlign; //Molecule to align
   
   /** Data structure that will hold the points used during the 
   *   alignment procedure 
   */
   vector<point *> Points;
   
   /** \brief Perturb the molecule Coordinates
   *
   *    This function perturbs the coordinates of the molecule
   *    within the range (-n/2, n/2)
   */
   void perturb(molecule *mol, float n);
   
   /** \brief Molecular Mechanics Energy 
   *
   *    This function calculated the molecular mechanics energy.
   *    It will also apply all the relative forces to the atoms
   */
   void mmEnergy(molecule *mol, vector<float> &energies);
   
   
private:

   /** \brief  Energy Class 
   * 
   *    You use the enrgy class to do MD, minimization extra 
   */
   energy *Energy;

   /** \brief Make the exp() lookup table 
   *
   *    This is used to make scoring alignments faster.  basically you pre calculate
   *    all the exp(-r^2) parts.
   */
   vector<double> expLookup;
   
   /** \brief Prep the molecule
   *
   *   This function preps the molecule
   *   Charges, atom types, etc...
   *   Ths function is expected to evolve over time
   *
   *   It should return false if any step of the prep fails..true otherwise
   */
   bool prepMolecule(molecule *mol);
   
   /** \brief Calculate alignment tanimoto
   *
   *  This function is used to calculate the alignment
   *  tanimoto for the two molecules
   */
   float tanimoto(molecule *tmpl, molecule *toAlign);
                     
   /** \brief Molecule Dynamic Align
   *
   *    Try to align the molecules using molecular dynamics
   */
   bool leapfrog(molecule *mol, int maxIter);
 
   /** \brief update atom positions
   *
   *   This function moves the atoms based on the current forces
   */
   void moveAtomsSD(molecule *mol, const double &stepSize, double rms);
   
   /** \brief Clear the Atomic Forces 
   *
   *    this function is used to clear the atomic forces
   */
   void clearForces(molecule *mol);

   
   float aroW;
   float sigW;
   float sameW;
   float chgW; 
   float temp;
   float alpha;

   map<string, string> Params;

   vector<float> prevCoords;

   /** \brief Cope the current Coords
   *
   *   This function copies the current coordinates of the alignee
   *   to the prev Coords vector.  This is used to reinstate the molecule
   *   in the event of a NaN or inf calculation
   */
   void copyCurrent();

   /** \brief Reset the molecule to the last set of goo coords
   *
   *   This function restores the molecule to the last good state it 
   *   was in.
   */
   void restoreCoords();

   /** These are the vectors that you do energy stuff on */ 
   vector<atom *> allAtoms;
   vector<bond *> allBonds;
   vector<anglePtr> allAngles;
   vector<torPtr> allTors;
   vector<nbPtr> allNB;

   /** \breif The Maximum MD steps
   */
   int maxMD;
   
   /** \brief The Maximum Minimization Steps
   */
   int maxMin; 

   /** \brief The Dielectric Constant for the Simulation
   */
   float dielec;

   /** \brief The number of poses to keep
   *
   *   This is the number of poses that should be kept for 
   *   each molecule
   */
   int poseNum;

   /** \brief Minimum Tanimoto Term
   *
   *   If this value is set to a positive number
   *   then the simulation stops once a pose 
   *   has been found with a tanimoto greater
   *   than the set value
   */
   float tanTerm;

   /** \brief The Charges to use
   *
   *  The Atomic Charges to use.  Set as Current if  you don't 
   *  want to calculate charges
   */
   string chargeType;

   /** \brief Iterations per molecule
   *
   *  The maximum number of iterations per molecule
   */
   int Iter;

   /** \brief Flex the template molecule
   *
   *  If this variable is set to true then the template
   *  molecule will be set to true
   */
   bool tempFlex;

   /** \brief The RMSE cutoff for energy minimizatio
   */
   float rmse;

   /** \brief The max allowed force in energy minimization
   */
   float maxForce;

   /** \brief Minimum allowed Energy Charge 
   */
   float minE;

   /** \brief Dynamic Anneal Iterations..also calculated averages
   */
   int dynIter;

   /** \brief The Anneal ammount.  
   *
   *  Annealing takes place every dynIter iterations
   */
   float annealPercent;


   /** \brief this vector is used to track the average RMSE
   *   of the atomic coords.  it can be used for both the 
   *   template and the align or only the align
   */
   vector<float> avgRMSECoords;

   /** \brief  The current pose must be greater the poseRMSE for all poses
   *   already stored.
   */    
   float poseRMSE;

   /** \brief This is the rmsePose used to terminate the MD simulations 
   */
   float rmseCoords;

   //Return the RMSE of the two vectors
   float RMSE(vector<float> &p1, vector<float> &p2);

   /** \brief The current run's best Score  
   */
   float bestTan;  

	/** \brief if true only a single minimization is performed.  No MD simulation
	*	If this parameter is true or 1 then the two molecules are only minized.
	*   no MD simulation is performed...this is good for cleaning up alignments
	*/
	bool MinOnly; 
};

};//END NAMESPACE
#endif

