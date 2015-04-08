/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                        
 *   john.furr@dynamol.com                                                 
 ***************************************************************************/
#include "topological.h"
#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include <iostream>
#include <iomanip>
#include <math.h>
namespace dt {

Topological::Topological()
{
//   mol = NULL;
}


Topological::~Topological()
{
}

//molecule *Topological::getMol() {
molPtr Topological::getMol() {
   return mol;
}

//void Topological::setMol(molecule *mol) {
void Topological::setMol(molPtr mol) {
    this->mol = mol;
    setVDegree();
    setVVDegree();
    buildPaths(10);
}

/** This function sets the vertex degree of each atom */
void Topological::setVDegree() {
   if (mol == NULL)
      return;
      
   vDegree.clear();
      
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      //atom *atm = mol->atoms[i];
      atomPtr atm = mol->atoms[i];
      if (atm->getAN() != 1) {
                
         int count = 0;
         for (unsigned int i=0; i< atm->atoms.size(); i++) {
            //atom *tmp = atm->atoms[i];
            atomPtr tmp = atm->atoms[i].lock();
            if (tmp->getAN() != 1) 
               count++;
         }
         vDegree.push_back(count);
      } else {
         vDegree.push_back(-1);
      }
   }
}
    
/** This function sets the valence vertex degree of each atom */
void Topological::setVVDegree() {
   if (mol == NULL)  
      return;
      
   vvDegree.clear();
   
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      //atom *atm = mol->atoms[i];
      atomPtr atm = mol->atoms[i];
      float Zv = valenceCount(atm);
      //float Z  = atm->getAN();
      float H  = hydrogenCount(atm);
      
      //Handbook of molecular descriptor...alternate way
      //float vvD = (Zv - H) / (Z - Zv - 1);
      
      //This was the easy way and is what matched the table
      float vvD = Zv - H;
      vvDegree.push_back( vvD );
   }
}

//int Topological::valenceCount(atom *atm) {
int Topological::valenceCount(atomPtr atm) {
   if (atm->getAN() == 6) //carbon
      return 4;
   else if (atm->getAN() == 1) //hydrogen
      return 1;
   else if (atm->getAN() == 7) //nitrogen
      return 5;
   else if (atm->getAN() == 8) //oxygen
      return 6;
   else if (atm->getAN() == 16) //sulfer
      return 6;
   else if (atm->getAN() == 34) //selenium
      return 6;
   else if (atm->getAN() == 9) //flourine
      return 7;
   else if (atm->getAN() == 17) //chlorine
      return 7;
   else if (atm->getAN() == 35) //bromine 
      return 7;
   else if (atm->getAN() == 53) //iodine 
      return 7;
   else if (atm->getAN() == 15) //phosphorus 
      return 5;
   else if (atm->getAN() == 14) //silicone 
      return 4;
   else if (atm->getAN() == 5) //Borone
      return 3;
   else {
      ////cout <<"AN "<< atm->getAN() <<"  not found" << endl;
      return 0;
   }  
}



//int Topological::hydrogenCount(atom *atm) {
int Topological::hydrogenCount(atomPtr atm) {
   int count = 0;
   for (unsigned int i=0; i<atm->atoms.size(); i++) {
      atomPtr atm2 = atm->atoms[i].lock();
      if (atm2->getAN() == 1) {
         count++;
      }
   }
   return count;
}

//int Topological::pQN(atom *atm) {
int Topological::pQN(atomPtr atm) {
   if ( atm->getAN() <3) 
      return 1;
   
   if (atm->getAN() >= 3 && atm->getAN() <= 10)
      return 2;
   
   if (atm->getAN() >= 11 && atm->getAN() <=18)
      return 3;
   
   if (atm->getAN() >=19 && atm->getAN() <= 36)
      return 4;
      
   if (atm->getAN() >=37 && atm->getAN() <= 54)
      return 5;
      
   if (atm->getAN() >=55 && atm->getAN() <= 86)
      return 6;

   return -1;
}


void Topological::buildPaths(int depth) {
    this->maxDepth = depth;
    stackMode = true;
    hSupressMode=true;
   
    ////cout <<"buildPaths: " << mol->atoms.size() << endl;
    //int test = 0;
    //Paths.clear();
    
    for (unsigned int i=0; i<mol->atoms.size(); i++) {
        //atom *atm = mol->atoms[i]; 
        atomPtr atm = mol->atoms[i];
        if (atm->getAN() != 1) {
	        currAtom = atm;
	        //prevAtom = NULL;
	        DEQUE.clear();
	        DEQUE.push_front(atm);
	        //set<atom *> path( DEQUE.begin(), DEQUE.end() );
           set<atomPtr> path( DEQUE.begin(), DEQUE.end() );
           Paths.insert(path);
	        pathVisit(atm); 
	     }
    }
   ////cout <<"Total Paths: "<< Paths.size() << endl;
}


//void Topological::pathVisit(atom *atm) {
void Topological::pathVisit(atomPtr atm) {
   static int count = 0;
   //if (atm == prevAtom)
	//return;
   if (DEQUE.size() == 0)	
	return;

   if ((int)DEQUE.size() >= maxDepth) {
        DEQUE.pop_front();
	return;
   }
   
   for (unsigned int i=0; i<atm->atoms.size(); i++) {
      //atom *tmp = atm->atoms[i];
      atomPtr tmp = atm->atoms[i].lock();
      if ( checkAtom(tmp) && tmp != atm ) {
	      DEQUE.push_front(tmp);
	      //set<atom *> path( DEQUE.begin(), DEQUE.end() );
         set<atomPtr> path( DEQUE.begin(), DEQUE.end() );
         Paths.insert(path);
	      prevAtom = atm;
	      count++;
         pathVisit(tmp);
      }
   }

   DEQUE.pop_front();	
}

//bool Topological::checkAtom(atom *atm) {
bool Topological::checkAtom(atomPtr  atm) {
   if (atm == prevAtom) {
	DEQUE.pop_front();
	return false;
   }
   //Check to see if the atom has already been visited
   if ( stackMode ) {
      for (unsigned int i=0; i<DEQUE.size(); i++) {
         if (atm == DEQUE[i]) {
	         DEQUE.pop_front();
  	         return false;  
	      }
      }
   }

   if (hSupressMode && atm->getAN() == 1)
      return false;

  cout <<"Topological::checkAtom End of Control Path"<<endl;      
   
}

float Topological::conV( int depth ) {
   if (mol == NULL) {
      ////cout <<"Mol was NULL...returning"<<endl;
      return -1;  
   }
    
   float cv = 0;

   //vector< set<atom *> > pathV(Paths.begin(), Paths.end());
   vector< set<atomPtr> > pathV(Paths.begin(), Paths.end());
   for (unsigned int i=0; i<pathV.size(); i++) {
    	if ((int)pathV[i].size() == depth) {
	   //vector<atom *> pv(pathV[i].begin(), pathV[i].end());
      vector<atomPtr> pv(pathV[i].begin(), pathV[i].end());
	   float num = 1;
	   for (unsigned int j=0; j<pv.size(); j++) {
	      num *= vDegree[ pv[j]->getNum()-1 ];
	   }
	   cv += 1.0 /(sqrt(num));
	}
   }

    return cv;
}

float Topological::conVV( int depth) {
   if (mol == NULL)
      return -1;  
  
    
   float cv = 0;
   //vector< set<atom *> > pathV(Paths.begin(), Paths.end());
   vector< set<atomPtr> > pathV(Paths.begin(), Paths.end());
   for (unsigned int i=0; i<pathV.size(); i++) {
    	if ((int)pathV[i].size() == depth) {
	      //vector<atom *> pv(pathV[i].begin(), pathV[i].end());
         vector<atomPtr> pv(pathV[i].begin(), pathV[i].end());
	      float num = 1;
	      for (unsigned int j=0; j<pv.size(); j++) {
	         num *= vvDegree[ pv[j]->getNum()-1 ];
	      }
	      cv += 1.0 /(sqrt(num));
	   }
   }
    
   return cv;
}


} //end namespace






