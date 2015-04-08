/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "confswarm.h"

#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "moldb.h"
#include <iomanip>

confSwarm::confSwarm() {}

confSwarm::confSwarm( int popSize, float id, float c1, float c2, molecule *mol) 
{
   inertialDampener = id;
   globalPull = c1;
   localPull = c2;
   
   setMolecule(mol);
   if (rotBonds.size() == 0) {
      //cout <<"No rotable bonds.  exiting swarm simulation"<<endl;
      return;
   }
   Pop.resize(popSize);
   
   //cout <<"initializing swarm.. This could take a few minutes"<<endl;
   for (int i=0; i<Pop.size(); i++) {
      Pop[i].init( rotBonds.size() );
      //cout <<"i is: " << i << endl;
   }
   
   bestScore = 1000000000;
   ////cout <<"confSwarm: " << rotBonds.size() << endl;
   //int test = 0;
   //cin >> test;
}


confSwarm::~confSwarm()
{
}

void confSwarm::updateSwarmPositions() {
   //cout <<"confSwarm::updateSwarmPositions: " << Pop.size() << endl;
   for (int i=0; i<Pop.size(); i++) {
      Pop[i].updatePosition();
   }
}

void confSwarm::updateSwarmVelocities(float id, float c1, float c2) {
   avgVelocity = 0;
   //cout <<"confSwarm::updateSwarmVelocities " << Pop.size() << endl;
   for (int i=0; i<Pop.size(); i++) {
      avgVelocity += Pop[i].updateVelocity(id, c1, c2, bestParticle);
   }
   
   avgVelocity /= Pop.size();
}

void confSwarm::setMolecule(molecule *mol) {
  this->mol = mol;
  
  for (int i=0; i<mol->atoms.size(); i++) {
     float *cd = mol->atoms[i]->fCoords;
     origCoords.push_back(cd[0]);
     origCoords.push_back(cd[1]);
     origCoords.push_back(cd[2]);
  }
  
  Energy.setAtoms(mol->atoms);
  Energy.setBonds(mol->bonds);
  Energy.setAngles(mol->angles);
  Energy.setTorsions(mol->torsions);
  Energy.setNonBonds(mol->nonBonds);
  
  C.setRotableBonds(mol, rotBonds);
}
 
void confSwarm::restoreMol() {
   int count = 0;
   for (int i=0; i < mol->atoms.size(); i++) {
      float *cd = mol->atoms[i]->fCoords;
      for (int i=0; i<3; i++) {
         cd[i] = origCoords[count];
         count++;
      }
   }
}

float confSwarm::getAvgScore() {
   return avgScore;
}

float confSwarm::getBestScore() {
   return bestScore;
}

float confSwarm::getAvgVelocity() {
   return avgVelocity;
}

int confSwarm::rotBondNum() {
   return rotBonds.size();
}
    
void confSwarm::scoreSwarm() {
   currScores.resize(Pop.size());
   double tmpBest = 1000000000000.0;
   avgScore = 0;
   avgC1 = 0;
   avgC2 = 0;
   for (int i=0; i<Pop.size(); i++) {
      restoreMol();
      for (int j=0; j<rotBonds.size(); j++) {
         C.rotateBond(mol, rotBonds[j], Pop[i][j]);
      }
      
      currScores[i] = Energy.psoEnergy();
      //currScores[i] = Energy.molEnergy(mol);
      if (currScores[i] < tmpBest) {
         tmpBest = currScores[i];
         currentBestIndex = i;
      }
      
      avgC1 += Pop[i].c1;
      avgC2 += Pop[i].c2;
      
      if ( fabs(currScores[i] - Pop[i].bestEnergy) > .001) {
         ////cout <<"New Best for: " << i << "\t" << Pop[i].bestEnergy;
         Pop[i].bestEnergy = currScores[i];
         Pop[i].bestPos = Pop[i].currPos;
         Pop[i].c2 += .01;
         Pop[i].c1 -= .01;
         
         if (Pop[i].c1 < 0.0250)
            Pop[i].c1 = 0.025;
         if (Pop[i].c2 > 1.0)
            Pop[i].c2 = 1.0;
         ////cout <<"\t" << Pop[i].bestEnergy << endl;
      } else {
         Pop[i].c2 -= .01;
         Pop[i].c1 += .01;
         
         if (Pop[i].c2 < 0)
            Pop[i].c2 = 0;
         if (Pop[i].c1 > 1.0)
            Pop[i].c1 = 1.0;   
         
      }
         
      
      avgScore += currScores[i];
   }
   
   avgC1 /= Pop.size();
   avgC2 /= Pop.size();
 
   avgScore /= Pop.size();
   
   if (tmpBest < bestScore) {
      bestScore = tmpBest;
      bestParticle = Pop[ currentBestIndex ];
   }
   
}

void confSwarm::printAvgCValues() {
    //cout <<"Avg C Values: "<< avgC1 << "\t" << avgC2 <<endl;
}

void confSwarm::setToBest() {
   //cout << setw(12);
   for (int i=0; i<Pop.size(); i++) {
      //Pop[i] = bestParticle;
      for (int j=0; j<Pop[i].size(); j++) {
         Pop[i].currPos[j] = bestParticle[j];
         //cout << Pop[i][j] << setw(12);
      }
      //cout << endl;
   }
   
   //cout <<"That is the current population"<<endl;
   int test =0;
   cin >> test;
}


void confSwarm::saveAll(const char *fileName) {
   molDB db;
   //cout <<"You are in saveAll"<<endl;
   for (int i=0; i<Pop.size(); i++) {
      restoreMol();
      for (int j=0; j<rotBonds.size(); j++) {
         C.rotateBond(mol, rotBonds[j], Pop[i].bestPos[j]);
      }
      if (i == 0) 
         molDB::writeSDF(fileName, mol, 0);
      else
         molDB::writeSDF(fileName, mol, 1);
   }
   //cout <<"Leaving saveAll"<<endl;
}
 
void confSwarm::saveBest() {

   restoreMol();
   //cout <<"The best was: " << endl;
   //cout << setw(12);
   for (int j=0; j<rotBonds.size(); j++) {
      //cout << bestParticle[j] <<setw(12);
      C.rotateBond(mol, rotBonds[j], bestParticle[j]);
   }
   //cout << endl;
   molDB::writeSDF("pso_best.sdf", mol, 0);
}

void confSwarm::printPop() {
   //cout <<setw(12);
   for (int i=0; i<Pop.size(); i++) {
      for (int j=0; j<Pop[i].size(); j++) {
         //cout << Pop[i][j] <<setw(12);
      }
      //cout << endl;
   }
}

confParticle confSwarm::getBestPart() {
   return bestParticle;
}

void confSwarm::reset() {
  bestScore = 1000000000;
  for (int i=0; i<Pop.size(); i++) {
      Pop[i].init(rotBonds.size());
  }
}
