/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef CONFPARTICLE_H
#define CONFPARTICLE_H

#include <vector>
using namespace std;
/**
@author jfurr
*
*  This class servers as a conformation particle.
*   It is used to perform particle swarm conformational analysis
*/
class confParticle{
public:
    confParticle();
    /** \brief particle constructor
    *
    *   The initializer takes 1 arguent which specifies the number of rotable bonds.
    *   This corresponds to the size of the position and velocity vectors
    */
    virtual void init(int size);

    ~confParticle();
    
    /** \brief Assignment operator
    *
    *   This operator is used to copy a conf particle
    */
    void operator=(const confParticle &part);
    
    /** \brief Random access opertator
    *
    *    Provide random access to the currPos vector
    */
    float operator[](int index);
    
    /** \brief Update particle positions
    *
    *    This function performs:
    *    Xnew = Xold + vel
    */
    void updatePosition();
    
    /** \brief Update the velocity vector
    *
    *   Vnew = Vold*w + c1 *(Gbest - X) + c2*(Pbest - X)
    */
    double updateVelocity(float w, float c1, float c2, confParticle &best);
    
    /** \brief Return the size of the particle vector
    *
    *   Returns the size of the particles vector
    */
    int size();
    
    /** \brief randomize the velocity vector
    *
    *    Randomize the velocity vector
    */
    virtual void randomVel();
    
    /** \brief Set the global and local pulls 
    *
    *   Set the c1(global) and c2(local) pull variables
    */
    void setPulls(float c1, float c2);
    
    /** \brief Return the global pull value
    *
    *    Return the global pull value 
    */
    float getGlobalPull();
    
    /** \brief return the local pull value
    *
    *    return the local pull  value
    */
    float getLocalPull();
    
    vector<float> currPos;
    vector<float> bestPos;
    
    vector<float> prevPos;
    vector<float> prevVel;
   // static int count;
    int ID;

public:
   
   
   vector<float> velocity;
   
   float currEnergy;
   float bestEnergy;
   
   /** \brief Global Weight 
   *
   *    This variable determines the global pull on the particle
   */
   float c1;
   
   /** \brief Local Weight
   *
   *   This variable deterimines the local pull on the particle
   */
   float c2;
};

#endif

