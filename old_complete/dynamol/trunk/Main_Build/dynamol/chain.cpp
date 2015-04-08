/***************************************************************************
                          chain.cpp  -  description
                             -------------------
    begin                : Sun Feb 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include "chain.h"
#include "protein.h"
#include "fragment.h"
#include "atom.h"
#include "bond.h"

int chain::chainCreate = 0;
int chain::chainDestroy = 0;
bool chain::lock = false;
   
chain::chain()
: molecule()
{
  chainCreate++;
  rib = NULL;
  ribList = -1;
}
chain::~chain(){
}

//void chain::setParent(molecule *parent)
//{  this->parent = parent; }

//molecule *chain::getParent()
//{  return parent; }

chain &chain::operator=(const chain &ch) {
   for (int i=ch.frags.size()-1; i>=0; i--) {
      fragment *frag = new fragment;
      *frag = *ch.frags[i];
      this->addFrag(frag);   
   }
   
      /** You also had to sort out the atom number issue */
   vector<atom *> tmpAtom;
   for (int i=0; i<ch.atoms.size(); i++) {
     for (int j=0; j<this->atoms.size(); j++) {
        if (ch.atoms[i]->getNum() == this->atoms[j]->getNum()) {
           tmpAtom.push_back(this->atoms[j]);
           break;
        }
     }
   }
   
   for (int i=0; i<this->atoms.size(); i++) {
     this->atoms[i] = tmpAtom[i];
   }
   
   /**Now you need to sort the bond lists
   * Had to do this for the conformational search
   * and will probably have to do it for all other algorithms as well
   */
   vector<bond *> tmpBond;
   for (int i=0; i<ch.bonds.size(); i++) {
      int of = ch.bonds[i]->fromAtom()->getNum();
      int ot = ch.bonds[i]->toAtom()->getNum();
      for (int j=0; j<this->bonds.size(); j++) {
         int nf = this->bonds[j]->fromAtom()->getNum();
         int nt = this->bonds[j]->toAtom()->getNum();
         if (of == nf && ot == nt) {
            tmpBond.push_back(this->bonds[j]);
            break;
         }
      }
   }
   
   for (int i=0; i<this->bonds.size(); i++) {
      this->bonds[i] = tmpBond[i];
   }
  
   if (this == &ch) return *this;
}

void chain::removeFrag(fragment *fr) {
  if (!lock) {
  deque<fragment *>::iterator fIter = frags.begin();
  while (fIter != frags.end()) {
    if (*fIter == fr) {
      frags.erase(fIter);
      break;
    }
    fIter++;
  }
  }
}

int   chain::numOfFragments()               {return frags.size();};
int   chain::numOfFrags()                   {return frags.size();};
int   chain::rtti()                         {return 13;};
void          chain::setRibbon(ribbon *rib)            {this->rib = rib;};
ribbon      *chain::getRibbon()                          {return rib;};

void  chain::addFrag(fragment *frag){
   int test =0;

   deque<fragment *>::iterator iter = frags.begin();
   fragment *fr1, *fr2;
   bond *bd;
   if (frags.size() > 0) fr1 = frags[0];
   atom *atm1, *atm2;
   float *cor1, *cor2;
  
   if (frag->getNumOfAtoms() != 1) {
    
   //Make bonds between fragments based on a distance criteria
   if (frags.size() > 0) {
      int bondNum = bonds.size();
    
      int breakOut = 1;
      atom *holdAtm1, *holdAtm2;
      holdAtm1 = holdAtm2 = NULL; //initialize them to NULL
      float smallest = 1000;

      for (unsigned int i=0; i<fr1->atoms.size(); i++) {
         atm1 = fr1->atoms[i];
         cor1 = atm1->get_fCoords();

         for (unsigned int j=0; j<frag->atoms.size(); j++) {
         atm2 = frag->atoms[j];
         cor2 = atm2->get_fCoords();
         if (atm2->getAtomicNum() != 1) {
            float a =  cor1[0]-cor2[0];
            float b =  cor1[1]-cor2[1];
            float c =  cor1[2]-cor2[2];
            float distance = sqrt( a*a + b*b + c*c);
            if (distance < 2.5 && distance != 0) {
               smallest = distance;
               if (atm1->getAtomicNum() != 1 && atm2->getAtomicNum() != 1 && distance < 2.0) {
	      	      
	           if (atm1->addAtom(atm2) && atm2->addAtom(atm1) ) {
	              bd = new bond(bondNum, atm1, atm2, 1);
                      bonds.push_back(bd);
	              bd->setParent(frag);
	           }
               }
               if (distance > 12.0) {
                  break;
               }
            }
         }
         }
      }
   }
  }

  frags.push_front(frag);

  appendAtomList(*frag->getAtomList());
  appendBondList(*frag->getBondList());

  frag->setParent(this);
}



void    chain::setFragsToBegin()     {this->currentFrag = frags.begin();};
fragment *chain::getCurrentFrag()    {return *currentFrag;};

int     chain::nextFrag() {
  currentFrag++;
  if (currentFrag != frags.end()) {
    return 1;
  } else {
    return 0;
  }
};
int     chain::prevFrag() {
  currentFrag--;
  if (currentFrag != frags.begin())
    return 1;
  else
    return 0;
}


void chain::setSelected(bool state, bool children) {
  if (this->numOfFragments() != 0) {
    this->setFragsToBegin();
    for (;;) {
      getCurrentFrag()->getItem()->setSelected(state);
      getCurrentFrag()->setSelected(state, children);
      if (!nextFrag())
        break;
    }
  }

}






































