/***************************************************************************
                          atomtyper.cpp  -  description
                             -------------------
    begin                : Wed Dec 3 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@Dynamol.com
 ***************************************************************/


#include "atomtyper.h"
#include "molecule.h"
#include "linAlg.h"
#include "moldb.h"
#include "charge.h"
#include "quat.h"
#include "am1_bcc.h"
#include <deque>
#include <algorithm>
#include "atom.h"
#include "bond.h"

using namespace std;


atomTyper::atomTyper(){
  //Energy = new energy();
}
atomTyper::~atomTyper(){
  //delete Energy;
}

int atomTyper::getTotalBondOrder(atom *atm, molecule *mol) {
	int totBondOrder = 0;
	for (int i=0; i<atm->atoms.size(); i++) {
		bond *bd = mol->getBond(atm, atm->atoms[i]);
		if (bd != NULL) totBondOrder += bd->order;
	}
	
	return totBondOrder;
}

void atomTyper::assignAromaticity_AM1_BCC(molecule *mol, vector< vector<atom *> > &rings) {
     
      AM1_BCC am1_bcc;
      //am1_bcc.am1_bcc_Aromaticity(mol);
      setAromatic(mol, rings);
      //////////////cout <<"Used setAromaticity...atomType::assignAromaticity"<<endl;
      //int test = 0;
      //cin >> test;
}


void atomTyper::findAllRings2(molecule *mol, vector< vector<atom *> > &rings, int maxRingSize) {
    //////////////cout <<"findAllRings2"<<endl;
    vector< bitset<maxRingBits> > allRings;
    //I Think that you will need to go both ways here bucko!

    stack<atom *> ringStack;
    int tmpRing = maxRingSize;
  for (int ringSize=3; ringSize<tmpRing; ringSize++) {
    maxRingSize = ringSize;
   
    //Now serach for the rings using a stack
    for (int i=0; i<mol->atoms.size(); i++) {

      //Initiallize the visited variable to false
      for (int j=0; j<mol->atoms.size(); j++) {
        atom *atm = mol->atoms[j];
        atm->visited = false;
      }

      //Set base atom
      atom *baseAtm = mol->atoms[i];
      //Make sure stack is empty
      while (!ringStack.empty()) ringStack.pop();

      //Add base atom to stack.
      ringStack.push(baseAtm);
      ringStack.top()->visited = true;

      //First go one way.
      int prevStackSize = -10;
      while (!ringStack.empty()) {
          
          atom *tmpAtm = ringStack.top();
          prevStackSize = ringStack.size();
          int bonded = 0;
          for (int j=0; j<tmpAtm->atoms.size(); j++) {
              atom *tmp = tmpAtm->atoms[ j ];
              if (ringStack.size() == ringSize && tmp->getNum() == baseAtm->getNum()) {
                bitset<maxRingBits>  aRing;
                vector<atom *> atomRing;
                while (!ringStack.empty()) {
                  aRing.set(ringStack.top()->getNum()-1);
                  atomRing.push_back(ringStack.top());
                 
                  ringStack.pop();
                }
                int repeat = 0;
                for (int j=0; j<allRings.size(); j++) {
                  bitset<maxRingBits> tmp = allRings[j] ^ aRing;
                  if (tmp.count() == 0) { //IT WAS A REPEAT RING
                    for (int k=atomRing.size()-1; k>=0; k--) {
                      ringStack.push(atomRing[k]);
                    }

                    repeat = 1;
                    break;
                  }
                }
                if (repeat == 0) {//add the ring
                  ////////////////cout <<"A new ring of size: " << aRing.count() << endl;
                  allRings.push_back(aRing);
                  rings.push_back(atomRing);
                  break; //leave for loop
                }
             
               
              }  else if (tmp->visited == false) {
                ringStack.push(tmp);
                tmp->visited = true;
                bonded = 1;
                break;
              }
          }

          if ((ringStack.size() > ringSize) || (ringStack.size() != 0 && ringStack.size() == prevStackSize) )  {
            ringStack.pop();
          }          
      }//END WHILE

      //Initiallize the visited variable to false
      for (int j=0; j<mol->atoms.size(); j++) {
        atom *atm = mol->atoms[j];
        atm->visited = false;
      }

      //Set base atom
      baseAtm = mol->atoms[i];
      //Make sure stack is empty
      while (!ringStack.empty()) ringStack.pop();

      //Add base atom to stack.
      ringStack.push(baseAtm);
      ringStack.top()->visited = true;

      //First go one way.
      prevStackSize = -10;
      while (!ringStack.empty()) {

          atom *tmpAtm = ringStack.top();
          prevStackSize = ringStack.size();
          int bonded = 0;
          for (int j=tmpAtm->atoms.size()-1; j>=0; j--) {
              atom *tmp = tmpAtm->atoms[ j ];
              if (ringStack.size() == ringSize && tmp->getNum() == baseAtm->getNum()) {
                bitset<maxRingBits>  aRing;
                vector<atom *> atomRing;
                while (!ringStack.empty()) {
                  aRing.set(ringStack.top()->getNum()-1);
                  atomRing.push_back(ringStack.top());

                  ringStack.pop();
                }
                int repeat = 0;
                for (int j=0; j<allRings.size(); j++) {
                  bitset<maxRingBits> tmp = allRings[j] ^ aRing;
                  if (tmp.count() == 0) { //IT WAS A REPEAT RING
                    //RE-ADD THE ATOMS TO THE STACK
                    for (int k=atomRing.size()-1; k>=0; k--) {
                      ringStack.push(atomRing[k]);
                    }

                    repeat = 1;
                    break;
                  }
                }
                if (repeat == 0) {//add the ring
                  allRings.push_back(aRing);
                  rings.push_back(atomRing);
                  break; //leave for loop
                }


              }  else if (tmp->visited == false) {
                ringStack.push(tmp);
                tmp->visited = true;
                bonded = 1;
                break;
              }
          }

          if ((ringStack.size() > ringSize) || (ringStack.size() != 0 && ringStack.size() == prevStackSize) )  {
              atom *prev = ringStack.top();
              ringStack.pop();
          }
      }//END WHILE
      
    } //END FOR
 }
 for (int i=0; i<rings.size(); i++) {
   for (int j=0; j<rings[i].size(); j++) {
     rings[i][j]->inRing = true;
   }
 }
 //////////////cout <<"Leaving atomTyper::findAllRings2"<<endl;
}



bool atomTyper::isAmine_N(atom *atm) {
  if (atm->getAtomicNum() != 7) return false;
  for (int i=0; i<atm->atoms.size(); i++) {
    atom *tmpAtm = atm->atoms[i];
    if (tmpAtm->getAtomicNum() != 1 || tmpAtm->getAtomicNum() != 6) {return false;}
    else if (tmpAtm->getAtomicNum() == 6) {//Now check to make sure it is not an amide
      for (int j=0; j<tmpAtm->bonds.size(); j++) {
        bond *bd = tmpAtm->bonds[j];
        if (bd->order == 2) return false;
      }
    
    }
  }
  return true;
}

bool atomTyper::isAmide_N(atom *atm) {
  if (atm->getAtomicNum() != 7) return false;
  //////////////cout <<"CHECKING IF AOM IS AMIDE "<<atm->getNum() <<"\t"<<atm->valence << endl;
  for (int i=0; i<atm->atoms.size(); i++) {
    
    atom *tmpAtm = atm->atoms[i];
    //////////////cout <<"tmpAtm->getSym(): " << tmpAtm->getSym() << endl;
    //if (tmpAtm->getSym() != "H" && tmpAtm->getSym() != "C") {return false;}
    if (tmpAtm->getAtomicNum() == 6) {//Now check to make sure it is not an amide
      //////////////cout <<"Yeah you are still here with atm: " << atm->getNum() << endl;
      
      for (int j=0; j<tmpAtm->bonds.size(); j++) {
        //////////////cout <<"YOU DID AT LEAST CHECK THIS SECTION "  << endl;
        bond *bd = tmpAtm->bonds[j];
        if (bd->order == 2) {
          //////////////cout <<"Yeah man the bond order was 2: " << bd->from->getSym()<<"\t"<<bd->to->getSym()<<endl;
          if (bd->from->getAtomicNum() == 8 && bd->from->atoms.size() == 1) return true;
          if (bd->to->getAtomicNum() == 8 && bd->to->atoms.size() == 1) return true;
          //////////////cout <<"No man you did not ever get to this point!"<<endl;
        }
      }

    }
  }
  return false;
}

int  atomTyper::heavyAtoms(atom *atm) {
   int num = 0;
   for (int i=0; i<atm->atoms.size(); i++) {
      atom *tmp = atm->atoms[i];
      if (tmp->getAtomicNum() != 1) num++;
   }
   return num;
}

bool atomTyper::isNitro_N(atom *atm) {
  if (atm->getAtomicNum() != 7) return false;
  if (atm->atoms.size() != 3) return false;
  ////////////////cout <<"You are checking to see if this is a Nitro Nitrogen now"<<endl;
  //Count oxygens first
  int count = 0;
  for (int i=0; i<atm->atoms.size(); i++) {
     atom *tmpAtom = atm->atoms[i];
     if (tmpAtom->getAN() == 8)
       count++;
  }
  if(count != 2) return false;
   
  int gate = 0;
  for (int i=0; i<atm->atoms.size(); i++) {
    atom *tmpAtm = atm->atoms[i];
    if (tmpAtm->getAtomicNum() == 8 && tmpAtm->atoms.size() != 1) return false;
    if (tmpAtm->getAtomicNum() == 6) gate = 1;
  }
  if (gate == 1) return true;
}

bool atomTyper::isNitro_O(atom *atm) {
  if (atm->getAtomicNum() != 8) return false;
  if (atm->atoms.size() != 1) return false;
  ////////////////cout <<"You are checking to see if this is a Nitro Nitrogen now"<<endl;
  int gate = 0;
  for (int i=0; i<atm->atoms.size(); i++) {
    atom *tmpAtm = atm->atoms[i];
    if (tmpAtm->getAtomicNum() == 7) {
      int oxyCount = 0;
      for (int j=0; j<tmpAtm->atoms.size(); j++) {
        atom *holdAtm = tmpAtm->atoms[j];
        if (holdAtm->getAtomicNum() == 8 && holdAtm->atoms.size() == 1) oxyCount++;
      }
      
      if (oxyCount == 2) return true;
    }
  }

  return false;
}

bool atomTyper::isEster_O(atom *atm) {
  if (atm->getAtomicNum() != 8) return false;
  if (atm->atoms.size() != 2) return false;

  if (atm->atoms[0]->getAtomicNum() != 6 || atm->atoms[1]->getAtomicNum() != 6) return false;

  for (int i=0; i<atm->atoms.size(); i++) {
    atom *tmpAtm = atm->atoms[i];
    for (int j=0; j<tmpAtm->bonds.size(); j++) {
      bond *bd = tmpAtm->bonds[j];
      if (bd->order == 2) {
        if (bd->from->getAtomicNum() == 8 && bd->from->atoms.size() == 2) return true;
        if (bd->to->getAtomicNum() == 8 && bd->to->atoms.size() == 2) return true;
      }
    }
  }
}


bool atomTyper::isCarboxyilicAcid_C(atom *atm) {
  if (atm->getAtomicNum() != 6) return false;
  if (atm->atoms.size() != 3) return false;

  int oCount = 0;
  for (int i=0; i<atm->atoms.size(); i++) {
    atom *tmpAtm = atm->atoms[i];
    if (tmpAtm->getAtomicNum() == 8 && tmpAtm->atoms.size() == 2) oCount++;
  }

  if (oCount == 2) return true;

  return false;
}

bool atomTyper::isCarboxyilicAcid_O(atom *atm) {
  if (atm->getAtomicNum() != 8) return false;
  if (atm->atoms.size() != 1) return false;

  if (isCarboxyilicAcid_C(atm->atoms[0]) ) return true;
  
  
  return false;
}

bool atomTyper::isDelocalized(bond *bd) {
  atom *from = bd->from;
  atom *to = bd->to;
  ////////////////cout <<"<---------------  atomTyper::isDelocalized(): " << endl;
  if ( (isNitro_N(from) && isNitro_O(to) ) || ( isNitro_N(to) && isNitro_O(from) ) ) return true;
  if ( (isCarboxyilicAcid_C(from) && isCarboxyilicAcid_O(to) ) || ( isCarboxyilicAcid_C(to) && isCarboxyilicAcid_O(from) ) ) return true;

  return false;
}

bool atomTyper::isLactoneCarbonylOxygen(atom *atm) {
  if (atm->getAtomicNum() != 8) return false;

  atom *cAtm, *oAtm;
  //Now lets check to see if the COO part is there before ring check
  for (int i=0; i<atm->atoms.size(); i++) {
    atom *tmp = atm->atoms[i];
    if (tmp->getAtomicNum() == 6) {
      int check = 0;
      for (int j = 0; j<tmp->atoms.size(); j++) {
        if (tmp->atoms[j]->getAtomicNum() == 8 && tmp->atoms[j] != atm) {
          cAtm = tmp;
          oAtm = tmp->atoms[j];
          check = 1;
        }
      }
      if (check == 1) break;
    }
  }
  molecule *mol = dynamic_cast<molecule *>(atm->parent);

  vector< vector<atom *> > rings;
  this->findAllRings2(mol, rings, 8);

  ////////////////cout <<"POTENTIAL LACTONE!"<<endl;

  for (int i=0; i<rings.size(); i++) {
    int count = 0;
    for (int j=0; j<rings[i].size(); j++) {
      if (rings[i][j] == cAtm || rings[i][j] == oAtm) count++;
     
    }
    if (count == 2) return true;
  }
  return false;
  //for (int i=0; i<
}



bool atomTyper::isLactamCarbonylOxygen(atom *atm) {
  if (atm->getAtomicNum() != 8) return false;

  atom *cAtm, *nAtm;
  //Now lets check to see if the COO part is there before ring check
  for (int i=0; i<atm->atoms.size(); i++) {
    atom *tmp = atm->atoms[i];
    if (tmp->getAtomicNum() == 6) {
      int check = 0;
      for (int j = 0; j<tmp->atoms.size(); j++) {
        if (tmp->atoms[j]->getAtomicNum() == 7) {
          cAtm = tmp;
          nAtm = tmp->atoms[j];
          check = 1;
        }
      }
      if (check == 1) break;
    }
  }
  molecule *mol = dynamic_cast<molecule *>(atm->parent);

  vector< vector<atom *> > rings;
  this->findAllRings2(mol, rings, 8);

  ////////////////cout <<"POTENTIAL LACTONE!"<<endl;

  for (int i=0; i<rings.size(); i++) {
    int count = 0;
    for (int j=0; j<rings[i].size(); j++) {
      if (rings[i][j] == cAtm || rings[i][j] == nAtm) count++;

    }
    if (count == 2) {
      //////////////cout <<"It is a lactam: " << endl;
      return true;
    }
  }
  return false;
  //for (int i=0; i<
}

string atomTyper::atomicNumToString(int num) {
    string sym;
    if (num == 1) sym = "H";
      else if (num == 2) sym = "He";
      else if (num == 3) sym = "Li";
      else if (num == 4) sym = "Be";
      else if (num == 5) sym = "B";
      else if (num == 6) sym = "C";
      else if (num == 7) sym = "N";
      else if (num == 8) sym = "O";
      else if (num == 9) sym = "F";
      else if (num == 10) sym = "Ne";
      else if (num == 11) sym = "Na";
      else if (num == 12) sym = "Mg";
      else if (num == 13) sym = "Al";
      else if (num == 14) sym = "Si";
      else if (num == 15) sym = "P";
      else if (num == 16) sym = "S";
      else if (num == 17) sym = "Cl";
      else if (num == 18) sym = "Ar";
      else if (num == 19) sym = "K";
      else if (num == 20) sym = "Ca";
      else if (num == 21) sym = "Sc";
      else if (num == 22) sym = "Ti";
      else if (num == 23) sym = "V";
      else if (num == 24) sym = "Cr";
      else if (num == 25) sym = "Mn";
      else if (num == 26) sym = "Fe";
      else if (num == 27) sym = "Co";
      else if (num == 28) sym = "Ni";
      else if (num == 29) sym = "Cu";
      else if (num == 30) sym = "Zn";
      else if (num == 31) sym = "Ga";
      else if (num == 32) sym = "Ge";
      else if (num == 33) sym = "As";
      else if (num == 34) sym = "Se";
      else if (num == 35) sym = "Br";
      else if (num == 36) sym = "Kr";
      else if (num == 37) sym = "Rb";
      else if (num == 38) sym = "Sr";
      else if (num == 39) sym = "Y";
      else if (num == 40) sym = "Zr";
      else if (num == 41) sym = "Nb";
      else if (num == 42) sym = "Mo";
      else if (num == 43) sym = "Tc";
      else if (num == 44) sym = "Ru";
      else if (num == 45) sym = "Rh";
      else if (num == 46) sym = "Pd";
      else if (num == 47) sym = "Ag";
      else if (num == 48) sym = "Cd";
      else if (num == 49) sym = "In";
      else if (num == 50) sym = "Sn";
      else if (num == 51) sym = "Sb";
      else if (num == 52) sym = "Te";
      else if (num == 53) sym = "I";
      else if (num == 54) sym = "Xe";

      return sym;
}

void atomTyper::type_mol2(molecule *mol) {
  for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
       //////////////cout <<"type Before: " << atm->getAtomType() << endl;
      if (atm->getAtomicNum() == 6) {//carbon type
        int ha = atm->numOfHeavyAtoms();
        int tbo = atm->totalBondOrder();
        if ( (tbo - ha) == 0) atm->setType("C.3");
        else if ( (tbo - ha) == 1) atm->setType("C.2");
        else if ( (tbo - ha) == 2) atm->setType("C.1");
        else {
          //////////////cout <<"No matching mol2 type found...setting to C.3" << endl;
          atm->setType("C.3");
        }
        //You still need support for C.ar && C.cat types

      } else  if (atm->getAtomicNum() == 7) {//Nitrogen type
        int ha = atm->numOfHeavyAtoms();
        int tbo = atm->totalBondOrder();
        if ( (tbo - ha) == 0) atm->setType("N.3");
        else if ( (tbo - ha) == 1) atm->setType("N.2");
        else if ( (tbo - ha) == 2) atm->setType("N.1");
        else if ( tbo == 4) atm->setType("N.4");
        else {
          //////////////cout <<"No matching mol2 type found...setting to N.3" << endl;
          atm->setType("N.3");
        }
        //You still need support for N.ar && N.cat && a few other N types

      } else  if (atm->getAtomicNum() == 8) {//Oxygen type
        int ha = atm->numOfHeavyAtoms();
        int tbo = atm->totalBondOrder();
        if ( (tbo - ha) == 0) atm->setType("O.3");
        else if ( (tbo - ha) == 1) atm->setType("O.2");
        else {
          //////////////cout <<"No matching mol2 type found...setting to O.3" << endl;
          atm->setType("O.3");
        }
        //You still need support for other O types

      } else if (atm->getAtomicNum() == 15) {//phosporous type
         atm->setType("P.3"); //odd that they only have P3 type???

      } else if (atm->getAtomicNum() == 16) {//sulfer type
        int ha = atm->numOfHeavyAtoms();
        int tbo = atm->totalBondOrder();
        int on = atm->numOfOxygen();
        if (ha == 4 && tbo == 6 && on == 2) atm->setType("S.O2");
        else if (ha == 3 && tbo == 4 && on == 1) atm->setType("S.O");
        else if ( (ha - ha) == 0) atm->setType("S.3");
        else if ( (tbo - ha) == 1) atm->setType("S.2");
        else {
          //////////////cout <<"No matching mol2 type found...setting to S.3" << endl;
          atm->setType("S.3");
        }
        //You still need support for other S types

      } else  if (atm->getAtomicNum() == 1) atm->setType("H");
        else  if (atm->getAtomicNum() == 9) atm->setType("F");
        else if (atm->getAtomicNum() == 17) atm->setType("Cl");
        else if (atm->getAtomicNum() == 35) atm->setType("Br");
        else if (atm->getAtomicNum() == 53) atm->setType("I");
        else if (atm->getAtomicNum() == 14) atm->setType("Li");
        else if (atm->getAtomicNum() == 3) atm->setType("Li");
        else if (atm->getAtomicNum() == 11) atm->setType("Na");
        else if (atm->getAtomicNum() == 19) atm->setType("K");
        else if (atm->getAtomicNum() == 20) atm->setType("Ca");
        else if (atm->getAtomicNum() == 13) atm->setType("Al");
        else atm->setType("Du");//

      // NOTE THERE SHOULD ALSO BE A LONE PAIR ATOM TYPE
       //////////////cout <<"type After: " << atm->getAtomType() << endl;
  } 
}


void atomTyper::setAromatic(molecule *mol, vector< vector<atom *> > &rings) {
    //////////////cout <<"atomTyper::setAromatic"<<endl;
    int test = 0;
    cin >> test;
    vector< vector<atom *> > five, six, seven, eight;
    
    findAllRings2(mol, rings, 8);
    for (int i=0; i<rings.size(); i++) {
        if (rings[i].size() == 5) five.push_back(rings[i]);
        else if (rings[i].size() == 6) six.push_back(rings[i]);
        else if (rings[i].size() == 7) seven.push_back(rings[i]);
	else if (rings[i].size() == 8) eight.push_back(rings[i]);
    }

    //Huckels Rule.  4n +2 pi electrons.
    //nitrogen can donate 1 && it can donate 2 depending on how it is used...don't forget pyridone
    //and cumarin cases
    
    for (int i=0; i<rings.size(); i++) {
      int e = piElectronCount(mol, rings[i]);
      
      if (e == 6 || e == 10 || e == 18) {
        for (int j=0; j<rings[i].size(); j++) {
	  rings[i][j]->aromatic = true;	
	}
      
      }
      ////////////////cout <<"HERE: " << rings[i].size() << setw(12)<<e<<endl;
      //int test = 0;
      //cin >> test;
    }
    
}

int atomTyper::piElectronCount(molecule *mol, vector<atom *> ring) {
  int pi = 0;
     for (int i=0; i<ring.size(); i++) {
        atom *atm = ring[i];
	int an = atm->getAtomicNum();
	int order = getTotalBondOrder(mol, atm);
	int bonds = atm->atoms.size();
	int tmp = order-bonds;
	if (an == 6) {//It is a carbon
	   if (tmp == 0) pi+= 0;
	   if (tmp == 1) pi+= 1;
	} else
	if (an == 7) { //it is a nitrogen
	   if (order == 3) {
	      if (tmp == 0) pi+=2;
	      if (tmp == 1) pi+=1;
	   }
	} else 
	if (an == 8) { //It is an oxygen
	  if (order == 2 && tmp == 0) pi+= 2;
	} else
	if (an == 16) { //It is a sulfer
	   if (order == 2 && tmp == 0) pi+= 2;
	}
	
	//Now lets do exocyclic check
	for (int i=0; i < atm->atoms.size(); i++) {
	  atom *tmp = atm->atoms[i];
	  bond *bd = mol->getBond(atm, tmp);
	  if (bd->order == 2) {
	    int an = tmp->getAtomicNum();
	    if (an == 8 || an == 7 || an == 16) {
	      bool inRing = false;
	      for (int i=0; i<ring.size(); i++) {
	        if (tmp == ring[i]) {
		  inRing = true;
		  break;
		}
	      }
	      if (!inRing)
	         pi -= 1;
	    }
	  }	  
	}
     }
     
  return pi;
}

/** Currently we only set bond orders for carbon nitrogen && oxygen */
void atomTyper::setFormalCharges(molecule *mol) {
   for (int i=0; i<mol->atoms.size(); i++) {
        atom *atm = mol->atoms[i];
	atm->formalCharge;
	int an = atm->getAtomicNum();
	int order = getTotalBondOrder(mol, atm);
	int bonds = atm->atoms.size();
	atm->formalCharge = 0;
	if (an == 6) {//It is a carbon
	  atm->formalCharge = order-4;
	  //////////////cout <<atm->getNum() << setw(12) << atm->formalCharge << endl;
	} else
	if (an == 7) { //it is a nitrogen
	   atm->formalCharge = order-3;
	   //////////////cout <<atm->getNum() << setw(12) << atm->formalCharge << endl;
	} else 
	if (an == 8) { //It is an oxygen
	   atm->formalCharge = order-2;
	   //////////////cout <<atm->getNum() << setw(12) << atm->formalCharge << endl;
	} else
	if (an == 16) { //It is a sulfer
	   
	   //////////////cout <<atm->getNum() << setw(12) << atm->formalCharge << endl;
	}
   
   }
//   int test = 0;
//   cin >> test;
}

int atomTyper::getTotalBondOrder(molecule *mol, atom *atm) {
  
   int totalBondOrder = 0;
   for (int i=0; i<atm->atoms.size(); i++) {
      bond *bd = mol->getBond(atm, atm->atoms[i]);
      if (bd != NULL) { 
      	totalBondOrder += bd->getOrder();
      } else {
        ////////////////cout << atm->getNum() << setw(12) << atm->atoms[i]->getNum() << endl;
      }
   }
   return totalBondOrder;
}

string atomTyper::chirality(atom *atm) {
   //First check for a chiral center...breadth first search
   if (atm->atoms.size() < 4) return "N";
   ////////////cout <<"atomTyper::chirality"<<endl;
   //SetUp initial priorities
   vector<int> priority(atm->atoms.size());
   vector< deque<atom *> > QUEUs(atm->atoms.size());
   
   for (int i=0; i<atm->atoms.size(); i++) {
      atom *tmpAtm = atm->atoms[i];
      priority[i] = assignPriority(tmpAtm);
      deque<atom *> atomQueu;
      atomQueu.push_back(atm);
      QUEUs.push_back(atomQueu);
   }
   
   vector<int> sameIndex;
   checkPriority(priority, sameIndex);
   ////////////cout <<"Back from checkPriority"<<endl;
   return "N";
}

void atomTyper::checkPriority(vector<int> &priority, vector<int> &sameIndex) 
{
   ////////////cout<<"Check priority "<<priority.size() << endl;
   sort(priority.begin(), priority.end());
   for (int i=0; i<priority.size(); i++) {
      ////////////cout << priority[i] << endl;
   }
   ////////////cout <<"Leaving checkPriority"<<endl;
}

int atomTyper::assignPriority(atom *atm) {
   int pri = 0;
   for (int i=0; i<atm->atoms.size(); i++) {
      pri += atm->atoms[i]->getAtomicNum();
   }
   return pri;
}



void atomTyper::gaff2Mol2(molecule *mol) {
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      string t = atm->getFFType();
           
      if (t == "c3" || t == "cx" || t == "cy")
         atm->setFFType("C.3");
      else if (t == "c2" || t == "cu" || t == "cv" || t == "c" || t == "ce" || t == "cf" || t == "cd" || t == "cc")
         atm->setFFType("C.2");
      else if (t == "c1" || t == "cg" || t == "ch") {
         atm->setFFType("C.1");
      }
      else if (t == "ca" || t== "cp" || t == "cq")
         atm->setFFType("C.ar");
      else if (t == "n1")
         atm->setFFType("N.1");
      else if (t == "n2")
         atm->setFFType("N.2");
      else if (t == "n3")
         atm->setFFType("N.3");
      else if (t == "n4")
         atm->setFFType("N.4");
      else if (t == "n")
         atm->setFFType("N.am");
      else if (t == "nb")
         atm->setFFType("N.ar");
      else if (t == "na")
         atm->setFFType("N.pl3");
      else if (t == "os" || t == "oh")
         atm->setFFType("O.3");
      else if (t == "o")
         atm->setFFType("O.2");
      else if (t == "s2")
         atm->setFFType("S.2");
      else if (t == "s3")
         atm->setFFType("S.3");
      else if (t == "s4")
         atm->setFFType("S.O");
      else if (t == "s6")
         atm->setFFType("S.O2");
   
      else if (t == "f")
         atm->setFFType("F");
      else if (t == "cl")
         atm->setFFType("Cl");
      else if (t == "br")
         atm->setFFType("Br");
      else if (t == "i")
         atm->setFFType("I");
        
     if (atm->getAtomicNum() == 1)
      atm->setFFType("H");
     if (atm->getAtomicNum() == 15)
      atm->setFFType("P.3");   
   
   }
}





























