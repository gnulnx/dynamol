/*****************************************
 *   Copyright (C) 2004 by Dynamol       *
 *   email:  john.furr@dynamol.com       *
 *   *************************************/
//Dynatype includes
#include "molecule.h"
#include "bond.h"
#include "atom.h"

//Dynabase Includes
#include "../dynabase/atom.h"

//Dynamol Computational Library Includes
#include "torsion.h"
#include "angle.h"
#include "nonbond.h"

//Standard Library Includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using std::sort;
using std::setw;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

// C Includes
#include <math.h>

namespace dynacomp {


int molecule::molCount = 0;
	
molecule::molecule()
{
    /** Pyhon debug and test section */
   molCount++;
	
   name = "No Name";
   chargeType = "none";
   ffTypes = "none";
   potEnergy.resize(6);
}


molecule::~molecule()
{
    for (int i=0; i<atoms.size(); i++) {
       delete atoms[i];
    }

    for (int i=0; i<bonds.size(); i++) {
       delete bonds[i];
    }
    //for (int i=0; i<angles.size(); i++) { 
    //   delete angles[i];
    //}
    //for (int i=0; i<torsions.size(); i++) {
    //   delete torsions[i];
    //}
    //for (int i=0; i<nonBonds.size(); i++) {
    //   delete nonBonds[i];
   // }
}

/** This function has no check to for duplicate atoms...it is thus very fast 
  Make sure you only use trusted sdf or sdfx files 
*/

atom *molecule::addAtom
(int num, string sym, float x, float y, float z, int atomicNum) 
{
   atom *at = new atom(num, sym, x, y, z, atomicNum);
   atoms.push_back(at);
   at->setParent(this);
   return at;
}

atom *molecule::addAtom( boost::shared_ptr< dynabase::atom > basePtr ) {
   atom *at = new atom(basePtr);
   atoms.push_back(at);
   at->setParent(this);
   return at;
}

atom *molecule::getAtom(int index) {
   if (index < atoms.size())
      return atoms[index];
   else {
      cout <<"Index out of range.  Null returned"<<endl;
      return NULL;
   }
}


bond *molecule::addBond(int num, int from, int to, int order) {
   atom *hold1, *hold2, *tmp;
   hold1 = atoms[from-1]; 
   hold2 = atoms[to-1];
   hold1->addAtom(hold2);
   hold2->addAtom(hold1);
   bond *bd = new bond(num, hold1, hold2, order);
   bonds.push_back(bd);
   bd->setParent(this);
   return bd;
}

bond *molecule::getBond(int index) {
   if (index < bonds.size())
      return bonds[index];
   else {
      cout <<"Index out of range.  Null returned"<<endl;
      return NULL;
   }
}


bond *molecule::getBond(atom *atm1, atom *atm2) {
    for (int i=0; i<bonds.size(); i++) {
      if (bonds[i]->from == atm1 && bonds[i]->to == atm2) return bonds[i];
      if (bonds[i]->to == atm1 && bonds[i]->from == atm2) return bonds[i];
    }
    return NULL;
}

void molecule::setName(string molName)
{ name = molName; }

int molecule::setFormalCharges() {
   int totalCharge = 0;
   for (int i=0; i<atoms.size(); i++) {
      atom *atm = atoms[i];
      atm->formalCharge = 0;
      int valence = atm->atoms.size();

      int tbo = 0; //total bond order
      for (int j=0; j<atm->bonds.size(); j++) {
         tbo += atm->bonds[j]->order;
      }

      if (atm->getAN() == 6) 
         {atm->formalCharge = tbo - 4;}
      else if (atm->getAN() == 1) 
         {atm->formalCharge = tbo -1;}
      else if (atm->getAN() == 7) 
         {atm->formalCharge = tbo - 3;}
      else if (atm->getAN() == 8) 
         {atm->formalCharge = tbo -2;}
      else if (atm->getAN() == 15 && valence <=3) 
         {atm->formalCharge = tbo-3;}
      else if (atm->getAN() == 15 && valence <=5) 
         {atm->formalCharge = tbo-5;}
      else if (atm->getAN() == 16 && valence <=2) 
         {atm->formalCharge = tbo-2;}
      else if (atm->getAN() == 16 && valence <=4) 
         {atm->formalCharge = tbo-6;}
      else if (atm->getAN() == 9) 
         {atm->formalCharge = tbo -1;}
      else if (atm->getAN() == 35) 
         {atm->formalCharge = tbo -1;}
      else if (atm->getAN() == 17) 
         {atm->formalCharge = tbo -1;}
      else if (atm->getAN() == 53) 
         { atm->formalCharge = tbo -1;}
      else if (atm->getAN() == 14) 
         {atm->formalCharge = tbo - 4;}

      totalCharge += atm->formalCharge;
   }
   return totalCharge;
}

float molecule::molWeight() {
   float w = 0;
   for (int i=0; i<atoms.size(); i++) {
      w += atoms[i]->getMass();
   }
   return w;
}

void molecule::updateValence() {
   for (int i=0; i<atoms.size(); i++) {
      atom *atm = atoms[i];
      atm->valence = atm->atoms.size();
      int valence = atm->valence;

    //This section will determine the total bondORder of the bonds to the atom
    int bondOrderCount = 0;
    for (int j=0; j<atm->atoms.size(); j++) {
      bond *bd = getBond(atm, atm->atoms[j]);
      bondOrderCount += bd->order;
    }

   if (atm->getAtomicNum() == 6) 
      {atm->formalCharge = bondOrderCount - 4;}
   else if (atm->getAtomicNum() == 1) 
      {atm->formalCharge = bondOrderCount -1;}
   else if (atm->getAtomicNum() == 7) 
      {atm->formalCharge = bondOrderCount - 3;}
   else if (atm->getAtomicNum() == 8) 
      { atm->formalCharge = bondOrderCount -2;}
   else if (atm->getAtomicNum() == 15 && valence <=3)
      {atm->formalCharge = bondOrderCount-3;}
   else if (atm->getAtomicNum() == 15 && valence <=5)
      {atm->formalCharge = bondOrderCount-5;}
   else if (atm->getAtomicNum() == 16 && valence <=2)
      {atm->formalCharge = bondOrderCount-2;}
   else if (atm->getAtomicNum() == 16 && valence <=4)
      {atm->formalCharge = bondOrderCount-6;}
   else if (atm->getAtomicNum() == 9) 
      {atm->formalCharge = bondOrderCount -1;}
   else if (atm->getAtomicNum() == 35) 
      {atm->formalCharge = bondOrderCount -1;}
   else if (atm->getAtomicNum() == 17) 
      {atm->formalCharge = bondOrderCount -1;}
   else if (atm->getAtomicNum() == 53) 
      { atm->formalCharge = bondOrderCount -1;}
   else if (atm->getAtomicNum() == 14) 
      {atm->formalCharge = bondOrderCount - 4;}
 }
}

int molecule::setTorsions() {
    if (angles.size() == 0) {
	return 0;
    }

//    time_t t1 = time(NULL);
    //for (int i=0; i<torsions.size(); i++) {
    //   delete torsions[i];
   // }
  
    torsions.clear();

     //Lets also initialize our tails
     vector<bool> tails(atoms.size());
     for (int i=0; i<tails.size(); i++) {
        tails[i] = false;
     }
     
     vector<atom *> torStack;
     //Lets initialize the atom->bondVisit vector
     for (int i=0; i<atoms.size(); i++) {
        atom *tmp = atoms[i];
	tmp->bondVisit.resize(tmp->atoms.size());
	for (int j=0; j<tmp->bondVisit.size(); j++) {
	   tmp->bondVisit[j] = NULL;
	}
     }

     for (int i=0; i<atoms.size(); i++) {
       atoms[i]->visited = false;
     }
     
     
     for (int i=0; i<atoms.size(); i++) {
        atoms[i]->torsions.clear();
        torStack.push_back(atoms[i]);
	atoms[i]->visited = true;
	vector<torPtr> tmpTorsions;
	vector<atom *> tmpAtoms;
	tmpAtoms.push_back(atoms[i]);
	atom *start = atoms[i];
	while (!torStack.empty()) {
	   //If the stack has four lets make a torsion && remove the last element
	   if (torStack.size() == 4) {
	     if (!tails[torStack[3]->getNum()-1]) {
	       atom *atm1 = torStack[0];
	       atom *atm2 = torStack[1];
	       atom *atm3 = torStack[2];
	       atom *atm4 = torStack[3];
	       
	       torPtr t( new torsion(atm1, atm2, atm3, atm4) );
	       torsions.push_back(t);
	       atm1->torsions.push_back(t);
	       atm2->torsions.push_back(t);
	       atm3->torsions.push_back(t);
	       atm4->torsions.push_back(t);
	       tmpTorsions.push_back(t);
               //t->improper = false;
	       //}
	     }
	    
	     
	     atom *tmp = torStack[torStack.size()-1];
	     for (int j=0; j<tmp->bondVisit.size(); j++) {
	        tmp->bondVisit[j] = NULL;
	     }
	     torStack.pop_back();
	   }
	   
	   //get top of stack	
	   atom *curr = torStack[torStack.size()-1];
	
	   bool found = false;
	   for(int j=0; j<curr->atoms.size(); j++) {
	      atom *tmp = curr->atoms[j];
	      if (curr->bondVisit[j] == NULL && tmp != start) {
		curr->bondVisit[j] = tmp;
		torStack.push_back(tmp);
		tmpAtoms.push_back(tmp);
		for (int k=0; k<tmp->atoms.size(); k++) {
		  if (tmp->atoms[k] == curr) {
		     tmp->bondVisit[k] = curr;
		     break;
		  }
		}
		found = true;
		break;
	      } 
	   }
	    
	   if (!found) {
	      atom *tmp = torStack[torStack.size()-1];
	      for (int j=0; j<tmp->bondVisit.size(); j++) {
	        tmp->bondVisit[j] = NULL;
	      }
	      torStack.pop_back();
	   }
	   
	  
	}
	
	//Mark the atom as being an end torsion
	tails[atoms[i]->getNum()-1] = true;
	
	//Now clear all the atom visited
	for (int i=0; i<tmpAtoms.size(); i++) {
           atom *tmp = tmpAtoms[i];
	   for (int j=0; j<tmp->bondVisit.size(); j++) {
	      tmp->bondVisit[j] = NULL;
	   }
           
        }
     }
 
     
//    time_t t2 = time(NULL);

    for (int i=0; i<torsions.size(); i++) {
       atom *a1 = torsions[i]->atm1;
       atom *a2 = torsions[i]->atm2;
       atom *a3 = torsions[i]->atm3;
       atom *a4 = torsions[i]->atm4;
    }
    for (int i=0; i<atoms.size(); i++) {
       atoms[i]->visited = false;
     }
    
    // ################ IMPROPER TORSION SECTION ############
    
    for (int i=0; i<atoms.size(); i++) {
       atom *atm = atoms[i];
       if (atm->atoms.size() == 3 && atm->getAtomicNum() == 6) {
          torPtr t( new torsion(atm->atoms[0], atm->atoms[1], atm, atm->atoms[2]) );
          t->improper = true;
          torsions.push_back(t);
       }  
       if (atm->getAN() == 7 && atm->atoms.size() >=3) {
         torPtr t( new torsion(atm->atoms[0], atm->atoms[1], atm, atm->atoms[2]) );
         t->improper = true;
         torsions.push_back(t);
       }
    }

    return torsions.size();
}

int molecule::setAngles() {
  //################# RENUMBER SECTION ###################
  //This first section actually renumbers the atoms...This could become a problem
  for (int i=0; i < atoms.size(); i++) {
    atoms[i]->setNum(i+1);
  }
  
  for (int i=0; i<atoms.size(); i++) {
     atom *atm = atoms[i];
     for (int j=0; j<atm->atoms.size(); j++) {
       atm->atoms[j] = NULL;
     }
     atm->atoms.clear();
     for (int j=0; j<atm->angles.size(); j++) {
       atm->angles[j].reset();// = NULL;
     }
     atm->angles.clear();
     for (int j=0; j<atm->bonds.size(); j++) {
       atm->bonds[j] = NULL;
     }
     atm->bonds.clear();
  }
  
  for (int i=0; i<bonds.size(); i++) {
     bond *bd = bonds[i];
     bd->fromAtom()->addAtom(bd->toAtom());
     bd->toAtom()->addAtom(bd->fromAtom());
  }
  
  //################# End re-number section #############
  
  
    //First step is to clear any current angles;
//    time_t t1 = time(NULL);
   // for (int i=0; i<angles.size(); i++) {
   //   delete angles[i];
   // }
    angles.clear();
 
    vector<bool> tails(atoms.size());
     for (int i=0; i<tails.size(); i++) {
        tails[i] = false;
     }
     
     vector<atom *> angStack;
     //Lets initialize the atom->bondVisit vector
     for (int i=0; i<atoms.size(); i++) {
        atom *tmp = atoms[i];
	tmp->bondVisit.resize(tmp->atoms.size());
	for (int j=0; j<tmp->bondVisit.size(); j++) {
	   tmp->bondVisit[j] = NULL;
	}
     }

     for (int i=0; i<atoms.size(); i++) {
        atoms[i]->angles.clear();
        angStack.push_back(atoms[i]);
	atoms[i]->visited = true;
	vector<anglePtr> tmpAngles;
	vector<atom *> tmpAtoms;
	tmpAtoms.push_back(atoms[i]);
	while (!angStack.empty()) {
	   //If the stack has four lets make a torsion && remove the last element
	   if (angStack.size() == 3) {
	     if (!tails[angStack[2]->getNum()-1]) {
	       atom *atm1 = angStack[0];
	       atom *atm2 = angStack[1];
	       atom *atm3 = angStack[2];
	       //angle *ang = new angle(atm1, atm2, atm3);
          anglePtr ang( new angle(atm1, atm2, atm3) );
	       angles.push_back(ang);
	       atm1->angles.push_back(ang);
	       atm2->angles.push_back(ang);
	       atm2->angles.push_back(ang);
	       tmpAngles.push_back(ang);
	     }
	     
	     atom *tmp = angStack[angStack.size()-1];
	     for (int j=0; j<tmp->bondVisit.size(); j++) {
	        tmp->bondVisit[j] = NULL;
	     }
	     angStack.pop_back();
	   }
	   
	   //get top of stack	
	   atom *curr = angStack[angStack.size()-1];
	   bool found = false;
	   for(int j=0; j<curr->atoms.size(); j++) {
	      atom *tmp = curr->atoms[j];
	      if (curr->bondVisit[j] == NULL) {
		   curr->bondVisit[j] = tmp;
		   angStack.push_back(tmp);
		   tmpAtoms.push_back(tmp);
		   for (int k=0; k<tmp->atoms.size(); k++) {
		   if (tmp->atoms[k] == curr) {
		      tmp->bondVisit[k] = curr;
		      break;
		   }
		}

		found = true;
		break;
	      } 
	   } 
	   if (!found) {
	      atom *tmp = angStack[angStack.size()-1];
	      for (int j=0; j<tmp->bondVisit.size(); j++) {
	        tmp->bondVisit[j] = NULL;
	      }
	      angStack.pop_back();
	   }  
	}
	
	//Mark the atom as being an end torsion
	if ( (atoms[i]->getNum() -1) <=atoms.size())
	   tails[atoms[i]->getNum()-1] = true;
	
	//Now clear all the atom visited
	for (int i=0; i<tmpAtoms.size(); i++) {
           atom *tmp = tmpAtoms[i];
	   for (int j=0; j<tmp->bondVisit.size(); j++) {
	      tmp->bondVisit[j] = NULL;
 	   }
        }
     }
     
  
    return angles.size();
}

int molecule::setNonBonds(float cutoff) {
   //for (int i=0; i<nonBonds.size(); i++) {
   //  delete nonBonds[i];
  // }
   nonBonds.clear();
   
   int count = 0;
   for (int i=0; i<atoms.size(); i++) {
      atom *ai = atoms[i];
      for (int j=i+1; j<atoms.size(); j++) {
        atom *aj = atoms[j];
	bool isNonBond = true;
	bool isTor = false;
	for (int k=0; k<ai->atoms.size(); k++) {
	   if (ai->atoms[k] == aj) {
	     isNonBond = false;
	     break;
	   }
	}
	if (isNonBond) {
	  for (int k=0; k<ai->angles.size(); k++) {
	     atom *back = ai->angles[k].lock()->back;
	     if (back == aj) {
	       isNonBond = false;
	       break;
	     }
	  } 
	}
	if (isNonBond) {
	  for (int k=0; k<ai->torsions.size(); k++) {
	    atom *atm4 = ai->torsions[k]->atm4;
	    if (atm4 == aj) {
	      isTor = true;
	    }
	  }
	}
	
	if (isNonBond) {
          double sig = ai->getSigma() + aj->getSigma();
          double eps = ai->getEpsilon() * aj->getEpsilon();
          double chg = ai->getCharge()*aj->getCharge();
          float *cd1 = ai->fCoords;
          float *cd2 = aj->fCoords;
          float a = cd1[0] - cd2[0];
          float b = cd1[1] - cd2[1];
          float c = cd1[2] - cd2[2];
          float dist = sqrt(a*a + b*b + c*c);
          if ( dist < 10) {
             //nonBond *nb = new nonBond(ai, aj, isTor, sig, eps, chg);
             nbPtr nb( new nonBond(ai, aj, isTor, sig, eps, chg));
             nonBonds.push_back(nb);
          }
	}      
      }
   }
   return 0;  //Why return zero?
}
};






