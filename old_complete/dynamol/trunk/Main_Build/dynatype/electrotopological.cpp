/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         
 *   john.furr@dynamol.com                                                
 ***************************************************************************/
#include "electrotopological.h"

#include "molecule.h"
#include "atom.h"
#include <iostream>
#include <iomanip>
namespace dt {
electroTopological::electroTopological()
 : Topological()
{
//   mol = NULL;   
}

//void electroTopological::setMol(molecule *mol, vector<float> &ES) {
void electroTopological::setMol(molPtr mol, vector<float> &ES) {
   this->mol = mol;
   setIState();
   setEState();
   
   ES.clear();
   ES = eStates;
}

electroTopological::~electroTopological()
{
}

void electroTopological::setIState() {
   if (mol == NULL) 
      return;
      
   setVDegree();
   setVVDegree();   
   
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      //atom *atm = mol->atoms[i];
      atomPtr atm = mol->atoms[i];
      float iState = 0;
      if (atm->getAN() != 1 /*&& (atm->atoms.size() == 1 && atm->atoms[0]->getAN() == 1)*/) {
         int L = pQN(atm);
         float vvD = vvDegree[i];
         float vD = vDegree[i];
      
         iState = ( (2.0/L)*(2.0/L) * vvD +1 ) / vD;
      }
      iMap[atm] = iState;
      //////cout <<"iState for: " << atm->type << setw(12) << pQN(atm)<<setw(12);
      //////cout <<vvDegree[i]<<setw(12)<<vDegree[i]<<setw(12) << iState << endl;
   }
}

void electroTopological::setEState() {
    for (unsigned int i=0; i<mol->atoms.size(); i++) {
	//atom *atm = mol->atoms[i];
        atomPtr atm = mol->atoms[i];
	currEState = 0;

       	if (atm->getAN() != 1) {
	   currAtom = atm;

	  
	   visitedAtoms.clear();
	   searchDepth.clear();
	   searchDepth[atm] = 0;	
	   searchQueu.clear();

	   searchQueu.push_back(atm);
	   while ( !searchQueu.empty() ) {
     	       //atom *curr = searchQueu[0];
               atomPtr curr = searchQueu[0];
	       searchQueu.pop_front();
	       visit(curr);
	   }
	}

        //////cout <<"currEState for: " << atm->num << setw(12) << currEState;
	currEState += iMap[atm];
	//////cout << setw(12) << currEState << endl;
	eStates.push_back( currEState );
  
    }
}

//void electroTopological::visit(atom *atm) {
void electroTopological::visit(atomPtr atm) {
    if ( visitedAtoms.find(atm) != visitedAtoms.end() ) {
	return;
    }
 
    visitedAtoms.insert(atm);

    for (unsigned int i=0; i<atm->atoms.size(); i++) {
	//atom *tmp = atm->atoms[i];
        atomPtr tmp = atm->atoms[i].lock();
	
	if (checkAtom(tmp)) {
	   searchDepth[tmp] = searchDepth[atm]+1;
           calcEState(tmp);
	   searchQueu.push_back(tmp);
        }
    }

}

//bool electroTopological::checkAtom(atom *atm) {
bool electroTopological::checkAtom(atomPtr atm) {
   if (atm->getAN() == 1)
	return false;

   if ( visitedAtoms.find(atm) != visitedAtoms.end() )
	return false;

   return true;
}

//void electroTopological::calcEState( atom *atm ) {
void electroTopological::calcEState( atomPtr atm ) {
   float top = (iMap[currAtom] - iMap[atm] );
   float bottom = searchDepth[atm]+1;
   bottom *= bottom;
   currEState += top/bottom; 
}

} //end namespace dt;






