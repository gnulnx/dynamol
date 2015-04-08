/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                        
 *   john.furr@dynamol.com                                                 
 ***************************************************************************/
#include "dtPaths.h"
#include "molecule.h"
#include "atom.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

namespace dt {
	
Paths::Paths(molPtr mol, int pathLength)
{
   this->mol = mol;
   findTerms();
   maxPath = pathLength;
   if (maxPath == -1) 
      maxPath = 100000000;
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
     path.clear();
     baseAtom = mol->atoms[i];
     path.push_back(baseAtom);
     findPaths(baseAtom);
     sort(baseAtom->pathScores.begin(), baseAtom->pathScores.end());
   }
}

void Paths::findPaths(atomPtr currAtom) {
  if (currAtom == baseAtom && path.size() != 1) {
    //You have found a base atom ring ring.
    path.pop_back();
    vector<int> R(path.size());
    for (unsigned int i=0; i<path.size(); i++) {
      R[i] = path[i]->getNum()-1;
    }
    mol->addRing(R);
    return;
  }
  if (isTerminal(currAtom) || (int)path.size() > maxPath ) {
    float score = scorePath();
    baseAtom->pathScores.push_back(score);
    path.pop_back();
    return;
  }
  if (isPathRing(currAtom) ) {
    path.pop_back();
    return;
  }
  for (unsigned int i=0; i<currAtom->atoms.size(); i++) {
    atomPtr atm = currAtom->atoms[i].lock();
    if (path.size() == 1) {
      path.push_back(atm);
      findPaths(atm); 
    } 
    else if (atm != path[path.size()-2]) { 
      path.push_back(atm);
      findPaths(atm);    
    } 
  }
  path.pop_back();
}


float Paths::scorePath() {
   float score = 0;
   for (unsigned int i=0; i<path.size(); i++) {
      int index = i+1;
      score += (index*0.11 + path[i]->getAN()*0.08);
   }
   return score;
}

//bool Paths::isTerminal(atom *currAtom) {
bool Paths::isTerminal(atomPtr currAtom) {
  if (currAtom == baseAtom) return false;
  for (unsigned int i=0; i<term.size(); i++) 
    if (currAtom == term[i]) {
       ////////cout <<"Found terminal atom: " << currAtom->num << endl;
       return true;
    }
     
   return false; 
}

//bool Paths::isPathRing(atom *currAtom) {
bool Paths::isPathRing(atomPtr currAtom) {
   if (path.size() == 1) 
      return false;

   //minus one becuase you already pushed this atom on the stak
   int size = path.size()-1;

   for (int i=0; i<size; i++) 
      if (currAtom == path[i]) 
         return true;

   return false;
}

void Paths::findTerms() {
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      //atom *atm = mol->atoms[i];
      atomPtr atm = mol->atoms[i];
      if (atm->atoms.size() == 1) 
         term.push_back(atm);
   }
}
Paths::~Paths()
{
}

}


























