/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "confparticle.h"
#include <iostream>
#include "math.h"

//confParticl::count = 0;
confParticle::confParticle()
{
}

void confParticle::init(int size)
{

   //count++;
   //ID = count;
   currPos.resize(size);
   bestPos.resize(size);
   velocity.resize(size);
   
   for (int i=0; i< size; i++) {
      currPos[i] = rand() % 360;
      velocity[i] = rand() % 180;
   }
   
   prevPos = currPos;
   prevVel = velocity;
   
   bestPos = currPos;
   bestEnergy = 100000000;
   currEnergy = 100000000;
   
   c1 = c2 = 1.0;
   
}

void confParticle::setPulls(float c1, float c2) {
   this->c1 = c1;
   this->c2 = c2;
}

float confParticle::getGlobalPull() {
  return c1;
}

float confParticle::getLocalPull() {
   return c2;
}

void confParticle::randomVel() {
   for (int i=0; i< velocity.size(); i++) {
      velocity[i] = rand() % 180;
   }   
}

void confParticle::operator=(const confParticle &part) {
  currPos = part.currPos;
  prevPos = part.prevPos;
  prevVel = part.prevVel;
  bestPos = part.bestPos;
  velocity = part.velocity;
  bestPos = part.bestPos;
  bestEnergy = part.bestEnergy;
  currEnergy = part.currEnergy;
}

float confParticle::operator[](int index) {
  if (index >= currPos.size()) {
     //cout <<"Index out of range  "<<index <<"\t" << currPos.size() <<endl;
     return 0;
  }
  ////cout <<"Here: " << index << "\t" << currPos.size() << endl;
  return currPos[index];
}

int confParticle::size() {
   return currPos.size();
}


confParticle::~confParticle()
{
}

void confParticle::updatePosition() {
   ////cout <<"confParticle::updatePosition"<<endl;
   //int j=0; 
   //cin >> j;
   for (int i=0; i< currPos.size(); i++) {
      currPos[i] = currPos[i] + velocity[i];
   }
}
    

double confParticle::updateVelocity(float w, float c1, float c2, confParticle &best) {
   ////cout <<"HERE  "<< best.size() << "\t" << currPos.size() << "\t"<<bestPos.size() << endl;
   //int u=0; 
   //cin >> u;
   double avgDiff = 0;
   for (int i=0; i< velocity.size(); i++) {
      float r1 = rand() % 10000000;
      float r2 = rand() % 10000000;
      r1 /= 10000000;
      r2 /= 10000000;
      double nv = w*(velocity[i] + r1*this->c1*(best[i] - currPos[i]) + r2*this->c2*(bestPos[i] - currPos[i]));
      
      avgDiff += fabs(velocity[i] - nv);
      velocity[i] = nv;
      
   }
   ////cout << this->c1 << "\t" << this->c2 << endl;
   

   return avgDiff/velocity.size();
}



