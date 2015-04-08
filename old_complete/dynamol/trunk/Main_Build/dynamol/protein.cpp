/***************************************************************************
                          protein.cpp  -  description
                             -------------------
    begin                : Sun Feb 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include "protein.h"
#include "chain.h"
#include "fragment.h"
#include "atom.h"
#include "bond.h"

#include "trashcan.h"

int protein::protCreate = 0;
int protein::protDestroy = 0;

bool protein::lock = false;

protein::protein()
: molecule()
{
  protCreate++;
  this->name = "protein";
  this->parent = NULL;
}
protein::~protein(){

}

protein &protein::operator=(const protein &prot) {
   for (int i=0; i<prot.chains.size(); i++) {
      chain *ch = new chain;
      *ch = *prot.chains[i];
      this->addChain(ch);  
   }
   
   vector<atom *> tmpAtom;
   for (int i=0; i<prot.atoms.size(); i++) {
     for (int j=0; j<this->atoms.size(); j++) {
        if (prot.atoms[i]->getNum() == this->atoms[j]->getNum()) {
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
   for (int i=0; i<prot.bonds.size(); i++) {
      int of = prot.bonds[i]->fromAtom()->getNum();
      int ot = prot.bonds[i]->toAtom()->getNum();
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
   if (this == &prot) return *this;
}

void protein::removeChain(chain *ch) {
  if (!lock) {
  deque<chain *>::iterator cIter = chains.begin();
  while (cIter != chains.end()) {
    if (*cIter == ch) {
      chains.erase(cIter);
      break;
    }
    cIter++;
  }
  }
}

int     protein::numOfChains()                  {return chains.size();}; 

int     protein::rtti()                          {return 14;}; 

void    protein::addChain(chain *ch) {
  /* This first section chekcs to see if the first && last fragmet have atoms that should be bonded together
  */
  fragment *frag1 = ch->frags[0];
  float *cor1, *cor2;
  float smallest = 1000000;
  int  bondNum = ch->bonds.size();
  fragment *frag2 = ch->frags[ch->frags.size()-1];
  for (int i=0; i<frag1->atoms.size(); i++) {
    atom *atm1 = frag1->atoms[i];
    cor1 =atm1->get_fCoords();
    for (int j=0; j<frag2->atoms.size(); j++) {
      atom *atm2 = frag2->atoms[ j ];
      cor2 = atm2->get_fCoords();
      float a =  cor1[0]-cor2[0];
      float b =  cor1[1]-cor2[1];
      float c =  cor1[2]-cor2[2];
      float distance = sqrt( a*a + b*b + c*c);
      if (distance < 2.5 && distance != 0) {
            if (atm1->getAtomicNum() != 1 && atm2->getAtomicNum() != 1 && distance < 2.0) {
	      
	      if (atm1->addAtom(atm2) && atm2->addAtom(atm1) ) {
                bond *bd = new bond(bondNum, atm1, atm2, 1);
	        ch->bonds.push_back(bd);
      	        bd->setParent(ch);
	      }
              
              i=1000000;
              j=1000000;
            }
      }
    }
  }

  //Check to see if the chain mainly contains waters
  int waterCount = 0;
  for (int i=0; i<ch->frags.size(); i++) {
      if (ch->frags[i]->getName() == "water") {
          waterCount++;
      }
 }
 if (waterCount > ch->frags.size()/2) {
     ch->setName("Waters");
 }
  
  //Now we add the chain to the protein
  chains.push_back(ch); //ad the chain
  ch->setParent(this);
  appendAtomList(ch->getAtomList());  //add the bonds from the chain to the bonds of the protein
  appendBondList(ch->getBondList());  //add the atoms from the chain to the atoms of the protein
  
}
  

void	protein::addChain(chain *ch, vector<string> hetAtoms, vector<string> conectVec) {
    cout <<"protein addChain 2"<<endl;
    chains.push_front(ch);
    ch->setParent(this);
    
    string x, y, z, num, tmpFactor, name;
    int NUMBER;
    float temp;
    double X, Y, Z;
    
    //This part is for hetAtoms only.
    fragment *tmpFrag = new fragment();
    for (unsigned int i=0; i<hetAtoms.size(); i++) {
       x = hetAtoms[i].substr(30, 8);
       y =hetAtoms[i].substr(38, 8);
       z = hetAtoms[i].substr(46, 8);
       num = hetAtoms[i].substr(6, 5);
       name = hetAtoms[i].substr(12, 4);

       X = atof(x.c_str());
       Y = atof(y.c_str());
       Z = atof(z.c_str());
       NUMBER = atoi(num.c_str());

       tmpFactor = hetAtoms[i].substr(60, 7);
       temp = atof(tmpFactor.c_str());
       appendAtom(NUMBER, name, X, Y, Z, temp, tmpFrag);
    }

    //This part calls the addConect routine which sets up the hetATM CONECT table;
    addConect(tmpFrag, conectVec);
 
   
   if (hetAtoms.size() != 0) {
     this->appendAtomList(*tmpFrag->getAtomList());
     this->appendBondList(*tmpFrag->getBondList());
     ch->addFrag(tmpFrag);
   } else {
     this->appendAtomList(ch->getAtomList()); 
     this->appendBondList(ch->getBondList());
   }  
}

void    protein::reNumberBonds() {
   this->setBondToBegin();
   bond *bnd;
   int count = 1;
   for (;;) {
     bnd = this->getCurrentBond();
     bnd->setBondNum(count);
     count++;
     if (!this->nextBond())
       break;
   }
}


void 	protein::appendAtom(int &num, string &name, double &X, double &Y, double &Z, float &temp, fragment *ch)  {
	if (name == "CA  ") {
		ch->addAtom(num, name, X, Y, Z, 20);
	} else if (name == "FE  ") {
		ch->addAtom(num, name, X, Y, Z, 26);
	} else if (name == "ZN  ") {
		ch->addAtom(num, name, X, Y, Z, 30);
	} else  if (name[1] == 'C') {
		ch->addAtom(num, name, X, Y, Z, 6);
	} else if (name[1] == 'O') {
		ch->addAtom(num, name, X, Y, Z, 8);
	} else if (name[1] == 'N') {
		ch->addAtom(num, name, X, Y, Z, 7);
	} else if (name[1] == 'H') {
		ch->addAtom(num, name, X, Y, Z, 1);
	}  else {
		return;
	}	 

	atom *at = ch->returnAtom(num);
	at->setTemp(temp);
        vector<float> tmpCoords;
        at->getCoords(tmpCoords);
        this->addAtom(at->getNum(), at->getSym(), tmpCoords[0], tmpCoords[1], tmpCoords[2], at->getAtomicNum());
}


void			protein::addConect(fragment *frag, vector<string> conect) {
	string tmp;
	int currentAtom, atom1, atom2, atom3, atom4;

	for (unsigned int i=0; i<conect.size(); i++) {
		tmp = conect[i].substr(6, 5);
		currentAtom = atoi(tmp.c_str());

		tmp = conect[i].substr(11, 5);
		atom1 = atoi(tmp.c_str());

		tmp = conect[i].substr(16, 5);
		atom2 = atoi(tmp.c_str());

		tmp = conect[i].substr(21, 5);
		atom3 = atoi(tmp.c_str());

		tmp = conect[i].substr(26, 5);
		atom4 = atoi(tmp.c_str());
       		int numOfBonds = frag->getNumOfBonds();
    		bond *tmpBond;
		if (atom1 != 0) {
        		tmpBond = frag->addBond(numOfBonds+1, currentAtom, atom1, 1);
       			if (tmpBond != NULL) {
        	}
		}
		numOfBonds = frag->getNumOfBonds();
		if (atom2 != 0) {
       		   tmpBond = frag->addBond(numOfBonds+1, currentAtom, atom2, 1);
		}
		numOfBonds = frag->getNumOfBonds();
		if (atom3 != 0) {
       		   frag->addBond(numOfBonds+1, currentAtom, atom3, 1);
		}
		numOfBonds = frag->getNumOfBonds();
		if (atom4 != 0) {
       		   frag->addBond(numOfBonds+1, currentAtom, atom4, 1);
		}			
	}
	
}


void      protein::setChainsToBegin()  {this->currentChain = chains.begin();};
chain     *protein::getCurrentChain()  {return *currentChain;};

int      protein::nextChain() {
  currentChain++;
  if (currentChain != chains.end()) {
    return 1;
  } else {
    return 0;
  }
  
};

int      protein::prevChain() {
  currentChain--;
  if (currentChain != chains.begin())
    return 1;
  else
    return 0;
  
};

void protein::setSelected(bool state, bool children) {

  setChainsToBegin();
  chain *tmp;
  for (;;) {
    tmp = getCurrentChain();
    tmp->getItem()->setSelected(state);
    tmp->setSelected(state, children);
    if (!nextChain())
      break;
  }
  
}


          
void protein::metalCheck() {
   bool metalChain = false;
   chain *metal;
   vector<fragment *> newFrags;
   vector<fragment *> fragsToDel;
   for (int i=0; i<chains.size(); i++) {
      for (int j=0; j<chains[i]->frags.size(); j++) {
         if (chains[i]->frags[j]->atoms.size() == 1) {
            atom *atm = chains[i]->frags[j]->atoms[0];
            if (atm->getAtomicNum() != 8) { //water check
                if (!metalChain) {
                   metal = new chain;
                   metal->setName("Metals");
                   metalChain = true;
                   
     		}
		int num = atm->getNum();
                int AN = atm->getAtomicNum();
                fragment *frag = new fragment;
                frag->setName(atm->getSym());
                frag->setNum(chains[i]->frags[j]->getNum());
		frag->addAtom(num, atm->getSym(), atm->fCoords[0], atm->fCoords[1], atm->fCoords[2], AN);
        	//metal->addFrag(frag);        
                newFrags.push_back(frag);
                fragsToDel.push_back(chains[i]->frags[j]);
            }
         }

      }

   }

  TrashCan t(fragsToDel);
  fragsToDel.clear();
   for (int i=0; i<newFrags.size(); i++) {
      metal->addFrag(newFrags[i]);
   }

   if (newFrags.size() == 0) return;
   else addChain(metal);
}



































