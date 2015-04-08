/***************************************************************************
                          molecule.cpp  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include "molecule.h"
#include "mollistview.h"
#include "atom.h"
#include "bond.h"
#include "torsion.h"
#include "angle.h"
#include "nonbond.h"
#include "object.h"
#include <stack>
using std::stack;

#include "surfstruct.h"
int molecule::molCreate = 0;
int molecule::molDestroy = 0;

molecule::molecule()
: Object()
{
  surf.reset( new surface );
  molCreate++;
  atoms.reserve(50);
  parent = NULL;
  this->name = "mol";
  count++;
  this->molNumber = count;
  int num = 0;
  
  chargeType = "NONE";
  ffTypes    = "NONE";

  //initialize the potential energy of the molecule
  potEnergy.resize(6);
  for (int i=0; i<6; i++) potEnergy[i] = 0.0;
  
  molDisplayList = -1;

  isSelected = false;
}


molecule::~molecule(){
}

molecule &molecule::operator=(const molecule &mol) {
   if (this == &mol) {
       return *this;
    }
   /** This variable will tell us if that atoms are order
   *   If they are then we can speed up the addBond process
   *   We also order the atom numbers
   *   The original atom numbers are re-set at the end
   */
   const int size = mol.atoms.size();
   for (int i=0; i<mol.atoms.size(); i++) {
      atom *atm = mol.atoms[i];
      float *cd = atm->fCoords;
      int AN = atm->getAtomicNum();
      addAtom(atm->getNum(), atm->getSym(), cd[0], cd[1], cd[2], AN);
      atm->setCharge(atm->getCharge());
   }
   
   /** This section adds new bonds 
   *   This also takes care of setting the atom->atoms
   */
   for (int i=0; i<mol.bonds.size(); i++) {
      bond *bd = mol.bonds[i];
      int fNum = bd->fromAtom()->getNum();
      int tNum = bd->toAtom()->getNum();
      
      bond *newBond = addBond(bd->getNum(), fNum, tNum, bd->getOrder());
      if (newBond) newBond->defInc = bd->defInc;
   }
   
   /** Now lets reassign the atom's numbers */
   /*
   for (int i=0; i<mol.atoms.size(); i++) {
      atom *atm = mol.atoms[i];
      atm->setNum(nums[i]);
   }
   */
   /** Now lets set the molecules name */
   setName(mol.name);
}

/** This function works like A = A + B;
*    Both molecule's A and B must have an X atom
*/
molecule &molecule::operator+=(const molecule &mol) {
  return *this;
}
   
/** This function works like:  C = A + B;
*    Molecule's A and B must have an X atom
*/
molecule molecule::operator+(const molecule &mol) {
   molecule newMol = mol;
   newMol += *this;
   return newMol;
}

bool molecule::showSurface()
{ return surf->show; }

void molecule::hideSurface(bool hide)
{ surf->show = hide; }

int molecule::count = 0;

long int molecule::getCount() 
{ return count; };

long int molecule::getMolNumber()
{ return molNumber; };

void molecule::setName(string name) 
{ this->name = name; };

string molecule::getName() 
{ return name; };

int molecule::numOfChains() 
{ return 0; };

int molecule::numOfFragments() 
{ return 0; };

int molecule::getNumOfAtoms() 
{return this->atoms.size();};

int molecule::getNumOfBonds()
{ return this->bonds.size(); };

vector<atom *> molecule::getAtomList()
{ return atoms; };

vector<bond *> molecule::getBondList()                   
{ return bonds; };

void molecule::setNum(int num)                
{ this->num = num; };

int molecule::getNum()  
{ return this->num; };

int molecule::rtti() 
{ return 11; };

void	 molecule::unSelectAll() {
}

void molecule::selectAll() {
}

void  molecule::setSelected(bool bv, bool children) {
  if (children) {
     for (unsigned int i=0; i<atoms.size(); i++)  atoms[i]->setSelected(bv);
  }
  item->setSelected(bv);
}

void  molecule::setAtomToEnd() {
  this->currentAtom = atoms.end();
  currentAtom--;
}

void      molecule::setBondToEnd(){
  this->currentBond = bonds.end();
  currentBond--;
}

void      molecule::removeAtom(atom *at) {
  vector<atom *>::iterator aIter = atoms.begin();
  while (aIter != atoms.end()) {
    if (*aIter == at) {
      atoms.erase(aIter);
      break;
    }
    aIter++;
  }  
  
  //Now lets remove all the associtated bonds
  molecule *parent = dynamic_cast<molecule *>(getParent());
  vector<bond *>::iterator bIter = bonds.begin();
  while (bIter != bonds.end()) {
     bond *bd = *bIter;
     if (bd->from == at || bd->to == at) {
       bonds.erase(bIter);
       if (!parent) delete bd;
     } else {  
       bIter++;
     }
  }
  //Recursivly delete atom from all parents veector<atom *> atoms lists.
   
  if (parent) parent->removeAtom(at); 
  
  //This is a testing ground
  for (int i=0; i < atoms.size(); i++) {
   atoms[i]->setNum(i+1);
  }
  
  for (int i=0; i<atoms.size(); i++) {
     atom *atm = atoms[i];
     atm->atoms.clear();
     atm->angles.clear();
     atm->bonds.clear();
  }
  
  for (int i=0; i<bonds.size(); i++) {
     bond *bd = bonds[i];
     bd->fromAtom()->addAtom(bd->toAtom());
     bd->toAtom()->addAtom(bd->fromAtom());
  }
}

void molecule::deleteBond(bond *bd) { 
  molecule *parent = dynamic_cast<molecule *>(getParent()); 
  vector<bond *>::iterator iter = bonds.begin();
  while (iter != bonds.end()) {
    if (*iter == bd) {
      bond *bd = *iter;
      bonds.erase(iter);
      if (!parent) delete bd;
      break;
    }
    iter++;
  }
  
  //recursivly delete all bonds from parents vector<bond *> bonds lists
  
  if (parent != NULL) {
    parent->deleteBond(bd); 
  }
};


void molecule::appendAtomList(vector<atom *> atomList) {
  vector<atom *>::iterator iter = atomList.begin();
  atom *ta; //temporary atom
  while (iter != atomList.end()) {
    ta = *iter;
    iter++;
  }
 this->atoms.insert(this->atoms.end(), atomList.begin(), atomList.end());
}

void molecule::appendBondList(vector<bond *> bondList) {
  this->bonds.insert(this->bonds.end(), bondList.begin(), bondList.end());
}

atom *molecule::addAtom(dynabase::atomPtr basePtr) 
{
	atom *at = new atom(basePtr);
	atoms.push_back(at);
	at->setParent(this);
	return at;
}
//Called from read_mol2
atom *molecule::addAtom(int num, string symbol, double x, double y, double z, int atomicNum) {
  float radii;
  for (int i=0; i<atoms.size(); i++) {
      if (atoms[i]->getNum() == num) {
	  return NULL;
      }
  }
  atom *at = new atom(num, symbol, x, y, z, atomicNum);
  atoms.push_back(at);
  //You don't want to reassign the rtti to a chain || protein
  if (rtti() == 11 || rtti() == 12) {
     at->setParent(this); 
  }
  numOfChildren++; //This only cooresponds to the number of atom children...actually the bonds are not treated as children at all right now...probalby never will be either.
  return at;
}

bond *molecule::addBond(int num, int from, int to, int order) {
  atom *hold1, *hold2, *tmp;
  int count = 0; //counter
  //First thing we do is make sure that the bond has not already been added
  for (currentBond = bonds.begin(); currentBond != bonds.end(); currentBond++) {
    bond *tmpbd = *currentBond;
    if (tmpbd->fromAtom()->getNum() == from && tmpbd->toAtom()->getNum() == to) {
      return NULL;
    } else if (tmpbd->fromAtom()->getNum() == to && tmpbd->toAtom()->getNum() == from) {
      return NULL;
    }
  } 
  bool c1 = false;
  bool c2 = false;
  bond *bd = NULL;
  for (currentAtom = atoms.begin(); currentAtom != atoms.end(); currentAtom++) {
    tmp = *currentAtom;
    if (tmp->getNum() == from) {
      if (c1 == false) hold1 = *currentAtom;
      c1 = true;
      count++;
    } else if (tmp->getNum() == to) {
      if (c2 == false) hold2 = *currentAtom;
      c2 = true;
      count++;
    } 

    //break out of for loop early once we have both atoms accounted for
    if (count == 2) {
      break;
    }
    
    if (c1 == true && c2 == true) break;
  }

  if (count < 2) {
     return NULL;
  } else {            
  //create new bond
  if (hold1->addAtom(hold2) && hold2->addAtom(hold1) ) {
    bd = new bond(num, hold1, hold2, order);
    bd->setParent(this);
    bonds.push_back(bd);
  }
  count = 0;
  }
  
  bd->setParent(this);
  return bd;
}

bond *molecule::getBond(atom *atm1, atom *atm2) {
    for (int i=0; i<bonds.size(); i++) {
      if (bonds[i]->from == atm1 && bonds[i]->to == atm2) return bonds[i];
      if (bonds[i]->to == atm1 && bonds[i]->from == atm2) return bonds[i];
    }
    return NULL;
}

atom *molecule::getCurrentAtom() 
{return *currentAtom;};

void molecule::setAtomToBegin() 
{currentAtom = atoms.begin();};

int molecule::nextAtom() {
  currentAtom++;
  if (currentAtom != atoms.end()) {
    return 1;
  } else {
    return 0;
  }
}

int molecule::prevAtom() {
  currentAtom--;
  if (currentAtom != atoms.begin())
    return 1;
  else
    return 0;
}

void molecule::printAtoms() {
  for (int i=0; i<atoms.size(); i++) {
    atom *at = atoms[i];
  }
}

bond *molecule::getCurrentBond() 
{return *currentBond;};

void molecule::setBondToBegin() 
{currentBond = bonds.begin();};

int molecule::nextBond() {
  currentBond++;
  if (currentBond != bonds.end())
    return 1;
  else
    return 0;
}

int molecule::prevBond() {
  currentBond--;
  if (currentBond != bonds.begin())
    return 1;
  else
    return 0;
}


vector<float> molecule::centroid() {
  float minX, maxX, minY, maxY, minZ, maxZ;

  minX = minY = minZ = 100000;
  maxX = maxY = maxZ = -100000;

  for (int i=0; i<atoms.size(); i++) {
    atom *at = atoms[i];
    float *coordHold = at->fCoords;
      if (coordHold[0] <minX)
        minX = coordHold[0];
      if (coordHold[0] > maxX)
        maxX = coordHold[0];

      if (coordHold[1] <minY)
        minY = coordHold[1];
      if (coordHold[1] > maxY)
        maxY = coordHold[1];

      if (coordHold[2] <minZ)
        minZ = coordHold[2];
      if (coordHold[2] > maxZ)
        maxZ = coordHold[2];

  }
  vector<float> hold;
  hold.push_back((minX+maxX)/2);
  hold.push_back((minY+maxY)/2);
  hold.push_back((minZ+maxZ)/2);
  hold.push_back(minZ);
  hold.push_back(maxZ);

  return hold;
}


atom *molecule::returnAtom(int num) {
  atom *hold = getCurrentAtom(); //hold current atom pointer position
  for (int i=0; i<atoms.size(); i++) {
    atom *at = atoms[i];
    if (at->getNum() == num) {
      return at; //return pointer to atom number {num}
    }
  }
  *currentAtom = hold;
  return NULL;
}

void molecule::createNurb() {
  int count = 0;
  for (unsigned int i=0; i<4; i++) {
   for (unsigned int j=0; j<4; j++) {
    for (unsigned int k=0; k<3; k++) {
      float tmp = rand() % 100;
      nurb[i][j][k] = tmp;
    }
   }    
  }
}

void molecule::updateBondedAtoms() {
  if (atoms.size() < 2) {
    return;
  }
  for (unsigned int i=0; i<atoms.size(); i++) {
    atoms[i]->atoms.clear();
  }
  for (int i=0; i<bonds.size(); i++) {
     bond *bd = bonds[i];
     bd->from->addAtom(bd->to);
     bd->to->addAtom(bd->from);
  }
}


void molecule::updateValence() {
 for (int i=0; i<atoms.size(); i++) {
    atom *atm = atoms[i];
    int valence = atm->atoms.size();
    atm->valence = valence;

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

int molecule::numOfSelectedAtoms() {
  int num = 0;
  for (int i=0; i<atoms.size(); i++)
    if (atoms[i]->isSelected()) num++;

  return num;
}

bool molecule::isDeloc(bond *bd) {
  //First Check for nitro
  return false;
}

void molecule::addDistance(atom *atm1, atom *atm2) {
    //first check to make sure that the distance is not already present
    for (int i=0; i<dist.size(); i++) {
      if (dist[i][0] == atm1 && dist[i][1] == atm2) return; //distance was present
      if (dist[i][1] == atm1 && dist[i][0]== atm2) return; //distance was present
    }

    vector<atom *> tmp(2);
    tmp[0] = atm1;
    tmp[1]= atm2;

    dist.push_back(tmp);
}

void molecule::delDistance(atom *atm1, atom *atm2) {

  vector< vector<atom*> >::iterator itRem = dist.begin();
  for (int i=0; i<dist.size(); i++) {      
      if (dist[i][0] == atm1 && dist[i][1] == atm2) {dist.erase(itRem+i); return;}
      if (dist[i][1] == atm1 && dist[i][0]== atm2) {dist.erase(itRem+i); return;}
  }
}


void molecule::addAngle(atom *atm1, atom *atm2, atom *atm3) {
  vector<atom *> tmp(3);
  tmp[0] = atm1;
  tmp[1] = atm2;
  tmp[2] = atm3;
  ang.push_back(tmp);
}


void molecule::delAngle(atom *atm1, atom *atm2, atom *atm3) {
  vector< vector<atom*> >::iterator itRem = ang.begin();
  for (int i=0; i<ang.size(); i++) {
      if (ang[i][0] == atm1 && ang[i][1] == atm2 && ang[i][2] == atm3) {ang.erase(itRem+i); return;}
      if (ang[i][0] == atm1 && ang[i][2] == atm2 && ang[i][1] == atm3) {ang.erase(itRem+i); return;}
      if (ang[i][1] == atm1 && ang[i][0] == atm2 && ang[i][2] == atm3) {ang.erase(itRem+i); return;}
      if (ang[i][1] == atm1 && ang[i][2] == atm2 && ang[i][0] == atm3) {ang.erase(itRem+i); return;}
      if (ang[i][2] == atm1 && ang[i][0] == atm2 && ang[i][1] == atm3) {ang.erase(itRem+i); return;}
      if (ang[i][2] == atm1 && ang[i][1] == atm2 && ang[i][0] == atm3) {ang.erase(itRem+i); return;}
  }
}

/** This method adds a new Torsion */
void molecule::addTorsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4) {
  vector<atom *> tmp(4);
  tmp[0] = atm1;
  tmp[1] = atm2;
  tmp[2] = atm3;
  tmp[3] = atm4;

  tor.push_back(tmp);
}

  /** This function deletes a Torsion */
void molecule::delTorsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4) {
  vector< vector<atom*> >::iterator itRem = tor.begin();
  int match = 0;
  for (int i=0; i<tor.size(); i++) {
      match = 0;
      for (int j = 0; j<4; j++) {
        if ( atm1 == tor[i][j] ) match++;
        else if ( atm2 == tor[i][j] ) match++;
        else if ( atm3 == tor[i][j] ) match++;
        else if ( atm4 == tor[i][j] ) match++;
      }
      if ( match == 4 ) {
        tor.erase( itRem+i );
        return;
      } 
  }
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
       atm->angles[j] = NULL;
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
    for (int i=0; i<angles.size(); i++) {
      delete angles[i];
    }
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
	vector<angle *> tmpAngles;
	vector<atom *> tmpAtoms;
	tmpAtoms.push_back(atoms[i]);
	while (!angStack.empty()) {
	   if (angStack.size() == 3) {
	     if (!tails[angStack[2]->getNum()-1]) {
	       atom *atm1 = angStack[0];
	       atom *atm2 = angStack[1];
	       atom *atm3 = angStack[2];
	       angle *ang = new angle(atm1, atm2, atm3);
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
     
     
//     time_t t2 = time(NULL);
    return angles.size();
}

int molecule::setTorsions() {

    if (angles.size() == 0) {
	return 0;
    }

//    time_t t1 = time(NULL);
    for (int i=0; i<torsions.size(); i++) {
       delete torsions[i];
    }
  
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
	vector<torsion *> tmpTorsions;
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
	       
	       torsion *t = new torsion(atm1, atm2, atm3, atm4);
	       torsions.push_back(t);
	       atm1->torsions.push_back(t);
	       atm2->torsions.push_back(t);
	       atm3->torsions.push_back(t);
	       atm4->torsions.push_back(t);
	       tmpTorsions.push_back(t);
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
          torsion *t = new torsion(atm->atoms[0], atm->atoms[1], atm, atm->atoms[2]);
          t->improper = true;
          torsions.push_back(t);
       }  
       if (atm->getAN() == 7 && atm->atoms.size() >=3) {
         torsion *t = new torsion(atm->atoms[0], atm->atoms[1], atm, atm->atoms[2]);
         t->improper = true;
         torsions.push_back(t);
       }
    }

    return torsions.size();
}

int molecule::setNonBonds(float cutoff) {
//   time_t t1 = time(NULL);
   for (int i=0; i<nonBonds.size(); i++) {
     delete nonBonds[i];
   }
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
	     atom *back = ai->angles[k]->back;
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
          nonBond *nb = new nonBond(ai, aj, isTor, sig, eps, chg);
          nonBonds.push_back(nb);
	}      
      }
   }
   return 0;  //Why return zero?
}


//I think that you can delete this function now that you have a much better
// torsion perception algorithm
torsion *molecule::addMolTor(atom *atm1, atom *atm2, atom *atm3, atom *atm4) {
	if (torsions.size() == 0) {
		torsion *tor = new torsion(atm1, atm2, atm3, atm4);
		torsions.push_back(tor);
		//////////////cout <<"Adding new Torsion"<<endl;
		return tor;
	}
	
	
	for (int i=0; i<torsions.size(); i++) {
		atom *tor1 = torsions[i]->atm1;
		atom *tor2 = torsions[i]->atm2;
		atom *tor3 = torsions[i]->atm3;
		atom *tor4 = torsions[i]->atm4;
		int count = 0;
		if (tor1 == atm1 || tor1 == atm2 || tor1 == atm3 || tor1 == atm4) count++;
		if (tor2 == atm1 || tor2 == atm2 || tor2 == atm3 || tor2 == atm4) count++;
		if (tor3 == atm1 || tor3 == atm2 || tor3 == atm3 || tor3 == atm4) count++;
		if (tor4 == atm1 || tor4 == atm2 || tor4 == atm3 || tor4 == atm4) count++;
		
		if (count == 4) return NULL;
	}
	
	//////////////cout <<"Adding new torsion"<<endl;
	torsion *tor = new torsion(atm1, atm2, atm3, atm4);
	torsions.push_back(tor);
	return tor;
	
}

bool molecule::isBond(atom *atm1, atom *atm2) {
    for (int i=0; i<bonds.size(); i++) {
    	bond *bd = bonds[i];
	if (bd->fromAtom() == atm1 && bd->toAtom() == atm2) return true;
	if (bd->fromAtom() == atm2 && bd->toAtom() == atm1) return true;
    }
    return false;
}

void molecule::addPropValuePair(QString name, QString value, QString type) {
   propMap[name] = value;
   propTypeMap[name] = type;
}

QString molecule::getPropValue(QString propName) {
   QString value = propMap[propName];
   if (value == "") 
      return "none";
      
   return value;
}

QString molecule::getPropType(QString propName) {
   QString type = propTypeMap[propName];
   if (type == "") 
      return "none";
      
   return type;
}

void molecule::clearPropMap() {
   propMap.clear();
   propTypeMap.clear();
}

float molecule::molWeight() {
   float w = 0;
   for (int i=0; i<atoms.size(); i++) {
      w += atoms[i]->getMass();
   }
   return w;
}















































