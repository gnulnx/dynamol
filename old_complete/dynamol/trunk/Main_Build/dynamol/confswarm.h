/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef CONFSWARM_H
#define CONFSWARM_H

#include "confparticle.h"
#include <vector>
#include "conformation.h"
#include "energy.h"

using namespace std;

class molecule;
class bond;
/**
@author jfurr
*
*   This class holds the population of confParticles which are used during a 
*   particle swarm conformational analysis.
*/
class confSwarm{
public:
   confSwarm();
   confSwarm( int popSize, float id, float c1, float c2, molecule *mol );

   virtual ~confSwarm();
    
   void updateSwarmPositions();
   void updateSwarmVelocities(float id, float c1, float c2);
   
   /** \brief Score the confomations
   *
   *   This function scores the various conformations from each
   *   particle
   */
   virtual void scoreSwarm();
    
   /** brief Set the molecule to perform the analysis on
   *
   *   This is the molecule that you perform the conformational
   *   analysis on.  The original coordinates are saved in the
   *   origCoords vector. At the end of the analysis the molecule
   *   should be unchanged
   */
   virtual void setMolecule(molecule *mol);
    
   /** \brief Print the population
   *
   *    This function will print out the population
   */
   void printPop();
    
   /** \brief This function saves the final set of particles
   *
   *    Save the final set of particles
   */
   void saveAll(const char *fileName);
    
   /** \brief Save the best conformation to pso_best.sdf
   *
   *    Saves the best conformation found during the run to pso_best.sdf
   */
   void saveBest();
    
   /** \brief return the average score
   *
   *    This funcion returns the average score
   */
   float getAvgScore();
    
   /** \brief Return the best score
   *
   *   This function returns the best score
   */
   float getBestScore();
    
   /** \brief Return the average velocity
   *
   *    this function returns the aerage velocity.  Average angle change
   */
   float getAvgVelocity();
    
   /** \brief Return the number of rotable bonds
   *
   *    return the number of rotating bonds in the molecule
   */
   int rotBondNum();
    
   /** \brief Return the best Particle
   *
   *    This function returns the best particle
   */
   confParticle getBestPart();
   
   /** \brief Reset the bestScore
   *
   *    This function resets the particles information
   */
   void reset();
    
   /** \brief Set all particles to the current best
   *
   *    This function sets all the particles to the current best position
   */
   void setToBest();
   
   /** \brief Print the avgCValues
   *
   *    Prints the average C Values
   */ 
   void printAvgCValues();
    
   /** \brief restore molecule to original state
   *
   *    This function is used to restore the molecule to it's original
   *    state;
   */
   void restoreMol();
   
    /** \brief Variables holds the averge the individual particle c values
   *
   *    Variables holds the averge the individual particle c values
   */   
   float avgC1;
   float avgC2;
private:
 ;
   
   vector<confParticle> Pop;
   confParticle bestParticle;
   

   molecule *mol;
protected:
   vector<float> origCoords;
   vector<bond *> rotBonds;
   
   Conformation C;
   energy Energy;
   
   double bestScore;
   vector<double> currScores;
   double currBest;
   double currentBestIndex;
   
   /** \brief The average Score 
   *
   *    The average energy for each conformation in the run
   */
   double avgScore;
   
   /** \brief The average velocity
   *
   *    the average velocity
   */
   double avgVelocity;
   
   double inertialDampener;
   double globalPull;
   double localPull;
};

#endif

