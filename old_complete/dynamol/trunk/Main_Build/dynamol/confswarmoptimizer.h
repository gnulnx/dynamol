/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef CONFSWARMOPTIMIZER_H
#define CONFSWARMOPTIMIZER_H
#include <qstring.h>
#include "dynothread.h"
#include "confparticle.h"

class XmodelView;
class confSwarmOptimizer;
class molecule;
class confSwarm;

class csoThread : public dynoThread {
   public:
   csoThread(XmodelView *view, QString name);
   csoThread();
   ~csoThread();
   
   void run();
   void setMolecule(molecule *mol);
   void init(float id, float c1, float c2, int popSize, int Gen);
   virtual QString getName();
   virtual void setName(QString name);
   virtual void stopThread();
   virtual int rtti(); //returns 3;
private:
   molecule *mol;
   confSwarmOptimizer *cso;
   XmodelView *view;
};

/**
@author jfurr
*/
class confSwarmOptimizer{
friend class csoThread;
public:
   confSwarmOptimizer();

   ~confSwarmOptimizer();
   
   /** \brief Used to set the default molecule 
   *
   *    Set the molecule that pso will search over
   */
   void setMolecule(molecule *mol);
   
   
   /** \brief  Run the simulation
   *
   *    Call this after setMolecule() and init()
   */
   void run();
protected:

   /** \brief Set the pso run parameters 
   *
   *    Set the run parameters
   */
   void init(float id, float c1, float c2, int popSize, int Gen);
   

  
   float id;
   float c1;
   float c2;
   int popSize;
   int gen;

   confParticle globalParticle;
   double globalBest;

private:
   confSwarm *cs;
    /** \brief molecule that pso is searching
   */
   molecule *mol;

};

#endif

