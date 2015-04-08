/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc                                     *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "am1_bcc.h"
#include "molecule.h"
#include "atomtyper.h"

#include <fstream>
#include <sstream>

#include "molecule.h"
#include "atom.h"
#include "bond.h"

using namespace std;

AM1_BCC::AM1_BCC()
{
}


AM1_BCC::~AM1_BCC()
{
}

void AM1_BCC::am1_bcc_Aromaticity(molecule *mol) {
   //First lets update the valence counts on all atoms
   mol->updateValence();
      //We begin by setting all aromativ atom types to false;
   for (int i=0; i<mol->atoms.size(); i++) 
      mol->atoms[i]->aromatic = false;

   vector< vector<atom *> > rings, ringsFive, ringsSix, ringsSeven;

   atomTyper *typer = new atomTyper;
   typer->findAllRings2(mol, rings, 8);

   for (int i=0; i<rings.size(); i++) {
      if (rings[i].size() == 5) 
         ringsFive.push_back(rings[i]);
      else if (rings[i].size() == 6) 
         ringsSix.push_back(rings[i]);
      else if (rings[i].size() == 7) 
         ringsSeven.push_back(rings[i]);
   }

   //This section checks for rule number one page 1626 of paper;
   //Determine if the six membered rings is alternating double && single bonds
   BCC_ringRuleOne(mol, ringsSix);
   //Must loop over rule two because their are special cases were
   // rings wouldn't get typet...think fused tricyclic
   for (int i=0; i<ringsSix.size(); i++) {
      BCC_ringRuleTwo(mol, ringsSix);

       //This ruls is included just in case....might need to check again
      BCC_ringRuleTwoPointFive(mol, ringsSix); 
   }
   BCC_ringRuleThree(mol, ringsSix);
   BCC_ringRuleThree(mol, ringsSix);
   BCC_ringRuleFour(mol, ringsSeven);
   BCC_ringRuleFive(mol, ringsFive);
}


void AM1_BCC::BCC_ringRuleOne(molecule *mol, vector< vector<atom *> > &ringsSix) {
      
      for (int i = 0; i < ringsSix.size(); i++) {
        bool aro = false;
        atom *atm1 = ringsSix[i][0];  
        atom *atm2 = ringsSix[i][1];
        atom *atm3 = ringsSix[i][2];
        atom *atm4 = ringsSix[i][3];
        atom *atm5 = ringsSix[i][4];
        atom *atm6 = ringsSix[i][5];
        
        if (xAtomCheck(atm1) && xAtomCheck(atm2) && xAtomCheck(atm3) && xAtomCheck(atm4) && xAtomCheck(atm5) && xAtomCheck(atm6) ) {
            bond *bd1 = mol->getBond(atm1, atm2);
            if (bd1 == NULL) {return;}

            bond *bd2 = mol->getBond(atm2, atm3);
            if (bd2 == NULL) {return;}

            bond *bd3 = mol->getBond(atm3, atm4);
            if (bd3 == NULL) {return;}

            bond *bd4 = mol->getBond(atm4, atm5);
            if (bd4 == NULL) {return;}

            bond *bd5 = mol->getBond(atm5, atm6);
            if (bd5 == NULL) {return;}

            bond *bd6 = mol->getBond(atm6, atm1);
            if (bd6 == NULL) {return;}

            if (bd1->order == 1 && bd2->order == 2 && bd3->order == 1 && bd4->order == 2 && bd5->order ==1 && bd6->order==2) 
               aro = true;
            if (bd1->order == 2 && bd2->order == 1 && bd3->order == 2 && bd4->order == 1 && bd5->order ==2 && bd6->order==1) 
               aro = true;

          if (aro == true) {
            atm1->aromatic = true; 
            atm2->aromatic = true; 
            atm3->aromatic = true; 
            atm4->aromatic = true; 
            atm5->aromatic = true; 
            atm6->aromatic = true; 
            aro = false;
          }
        } 
      }

      //SHOULD PROBABLY COME BACK UP HERE AND REMOVE THESE RINGS
}

void AM1_BCC::BCC_ringRuleTwo(molecule *mol, vector< vector<atom *> > &ringsSix) {
    for (int i = 0; i < ringsSix.size(); i++) {
        bool aro = false;
        atom *atm1 = ringsSix[i][0];
        atom *atm2 = ringsSix[i][1];
        atom *atm3 = ringsSix[i][2];
        atom *atm4 = ringsSix[i][3];
        atom *atm5 = ringsSix[i][4];
        atom *atm6 = ringsSix[i][5];

        if (xAtomCheck(atm1) && xAtomCheck(atm2) && xAtomCheck(atm3) && xAtomCheck(atm4) && xAtomCheck(atm5) && xAtomCheck(atm6) ) {
            int doubleCount = 0;
            vector<int> dBond(6);
            bond *bd1 = mol->getBond(atm1, atm2);
            if (bd1 == NULL) {return;}
            if (bd1->order == 2) {doubleCount++; dBond[0] = 1;} else {dBond[0] = 0;}
            
            bond *bd2 = mol->getBond(atm2, atm3);
            if (bd2 == NULL) {return;}
            if (bd2->order == 2) {doubleCount++; dBond[1] = 1;} else {dBond[1] = 0;}
            
            bond *bd3 = mol->getBond(atm3, atm4);
            if (bd3 == NULL) {return;}
            if (bd3->order == 2) {doubleCount++; dBond[2] = 1;} else {dBond[2] = 0;}
            
            bond *bd4 = mol->getBond(atm4, atm5);
            if (bd4 == NULL) {return;}
            if (bd4->order == 2) {doubleCount++; dBond[3] = 1;} else {dBond[3] = 0;}
            
            bond *bd5 = mol->getBond(atm5, atm6);
            if (bd5 == NULL) {return;}
            if (bd5->order == 2) {doubleCount++; dBond[4] = 1;} else {dBond[4] = 0;}
            
            bond *bd6 = mol->getBond(atm6, atm1);
            if (bd6 == NULL) {return;}
            if (bd6->order == 2) {doubleCount++; dBond[5] = 1;} else {dBond[5] = 0;}

            //////////////cout <<"doubleCount: " << doubleCount << endl;
            if (doubleCount == 2) {
              ////////////cout <<"You are in the right ring"<<endl;
              if (dBond[0] == 1 && dBond[2] == 1)
                if (atm5->aromatic && atm6->aromatic) aro = true;
                
              if (dBond[1] == 1 && dBond[3] == 1)
                if (atm1->aromatic && atm6->aromatic) aro = true;
                
              if (dBond[2] == 1 && dBond[4] == 1) 
                if (atm1->aromatic && atm2->aromatic) aro = true;
                
              if (dBond[3] == 1 && dBond[5] == 1) 
                if (atm2->aromatic && atm3->aromatic) aro = true;
                
              if (dBond[4] == 1 && dBond[0] == 1) 
                if (atm3->aromatic && atm4->aromatic) aro = true;

               if (dBond[5] == 1 && dBond[1] == 1) 
                if (atm4->aromatic && atm5->aromatic) aro = true;

              if (aro == true) {
                atm1->aromatic = true;
                atm2->aromatic = true;
                atm3->aromatic = true;
                atm4->aromatic = true;
                atm5->aromatic = true;
                atm6->aromatic = true; 
                aro = false;
              }
            }
        }
    }
}

void AM1_BCC::BCC_ringRuleTwoPointFive(molecule *mol, vector< vector<atom *> > &ringsSix) {
    for (int i = 0; i < ringsSix.size(); i++) {
        bool aro = false;
        atom *atm1 = ringsSix[i][0];
        atom *atm2 = ringsSix[i][1];
        atom *atm3 = ringsSix[i][2];
        atom *atm4 = ringsSix[i][3];
        atom *atm5 = ringsSix[i][4];
        atom *atm6 = ringsSix[i][5];

        if (xAtomCheck(atm1) && xAtomCheck(atm2) && xAtomCheck(atm3) && xAtomCheck(atm4) && xAtomCheck(atm5) && xAtomCheck(atm6) ) {
            int doubleCount = 0;
            vector<int> dBond(6);
            bond *bd1 = mol->getBond(atm1, atm2);
            if (bd1 == NULL) {return;}
            if (bd1->order == 2) {doubleCount++; dBond[0] = 1;} else {dBond[0] = 0;}

            bond *bd2 = mol->getBond(atm2, atm3);
            if (bd2 == NULL) {return;}
            if (bd2->order == 2) {doubleCount++; dBond[1] = 1;} else {dBond[1] = 0;}

            bond *bd3 = mol->getBond(atm3, atm4);
            if (bd3 == NULL) {return;}
            if (bd3->order == 2) {doubleCount++; dBond[2] = 1;} else {dBond[2] = 0;}

            bond *bd4 = mol->getBond(atm4, atm5);
            if (bd4 == NULL) {return;}
            if (bd4->order == 2) {doubleCount++; dBond[3] = 1;} else {dBond[3] = 0;}

            bond *bd5 = mol->getBond(atm5, atm6);
            if (bd5 == NULL) {return;}
            if (bd5->order == 2) {doubleCount++; dBond[4] = 1;} else {dBond[4] = 0;}

            bond *bd6 = mol->getBond(atm6, atm1);
            if (bd6 == NULL) {return;}
            if (bd6->order == 2) {doubleCount++; dBond[5] = 1;} else {dBond[5] = 0;}

            if (doubleCount == 2) {

               if (dBond[0] == 1 && dBond[3] == 1)
                if (atm3->aromatic && atm6->aromatic) aro = true;

               if (dBond[1] == 1 && dBond[4] == 1)
                if (atm1->aromatic && atm4->aromatic) aro = true;

               if (dBond[2] == 1 && dBond[5] == 1)
                if (atm2->aromatic && atm5->aromatic) aro = true;

              if (aro == true) {
                atm1->aromatic = true;
                atm2->aromatic = true;
                atm3->aromatic = true;
                atm4->aromatic = true;
                atm5->aromatic = true;
                atm6->aromatic = true;
    
                aro = false;
              }
            }
        }
    }
}

void AM1_BCC::BCC_ringRuleThree(molecule *mol, vector< vector< atom *> > &ringsSix) {
    for (int i = 0; i < ringsSix.size(); i++) {
        bool aro = false;
        atom *atm1 = ringsSix[i][0];
        atom *atm2 = ringsSix[i][1];
        atom *atm3 = ringsSix[i][2];
        atom *atm4 = ringsSix[i][3];
        atom *atm5 = ringsSix[i][4];
        atom *atm6 = ringsSix[i][5];

        if (xAtomCheck(atm1) && xAtomCheck(atm2) && xAtomCheck(atm3) && xAtomCheck(atm4) && xAtomCheck(atm5) && xAtomCheck(atm6) ) {
            int doubleCount = 0;
            vector<int> dBond(6);
            
            bond *bd1 = mol->getBond(atm1, atm2);
            if (bd1 == NULL) {return;}
            if (bd1->order == 2) {doubleCount++; dBond[0] =1;} else {dBond[0] =0;}

            bond *bd2 = mol->getBond(atm2, atm3);
            if (bd2 == NULL) {return;}
            if (bd2->order == 2) {doubleCount++; dBond[1] =1;} else {dBond[1] =0;}

            bond *bd3 = mol->getBond(atm3, atm4);
            if (bd3 == NULL) {return;}
            if (bd3->order == 2) {doubleCount++; dBond[2] =1;} else {dBond[2] =0;}

            bond *bd4 = mol->getBond(atm4, atm5);
            if (bd4 == NULL) {return;}
            if (bd4->order == 2) {doubleCount++; dBond[3] =1;} else {dBond[3] =0;}

            bond *bd5 = mol->getBond(atm5, atm6);
            if (bd5 == NULL) {return;}
            if (bd5->order == 2) {doubleCount++; dBond[4] =1;} else {dBond[4] =0;}

            bond *bd6 = mol->getBond(atm6, atm1);
            if (bd6 == NULL) {return;}
            if (bd6->order == 2) {doubleCount++; dBond[5] =1;} else {dBond[5] =0;}

            if (doubleCount == 1) {
              if (dBond[0] == 1) {
                if (atm3->aromatic && atm4->aromatic && atm5->aromatic && atm6->aromatic)
                  aro = true;
              } else
              if (dBond[1] == 1) {
                if (atm4->aromatic && atm5->aromatic && atm6->aromatic && atm1->aromatic)
                  aro = true;
              } else
              if (dBond[2] == 1) {
                if (atm5->aromatic && atm6->aromatic && atm1->aromatic && atm2->aromatic)
                  aro = true;
              } else
              if (dBond[3] == 1) {
                if (atm6->aromatic && atm1->aromatic && atm2->aromatic && atm3->aromatic)
                  aro = true;
              } else
              if (dBond[4] == 1) {
                if (atm1->aromatic && atm2->aromatic && atm3->aromatic && atm4->aromatic)
                  aro = true;
               } else
               if (dBond[5] == 1) {
                if (atm2->aromatic && atm3->aromatic && atm4->aromatic && atm5->aromatic)
                  aro = true;
               }

               if (aro == true) {
                  atm1->aromatic = true;
                  atm2->aromatic = true;
                  atm3->aromatic = true;
                  atm4->aromatic = true;
                  atm5->aromatic = true;
                  atm6->aromatic = true;
       
                  aro = false;
              }
            }
        }
    }
    
}

void AM1_BCC::BCC_ringRuleFour(molecule *mol, vector<vector< atom *> > &ringsSeven) {  
  
  for (int i = 0; i < ringsSeven.size(); i++) {
        bool aro = false;
        atom *atm1 = ringsSeven[i][0];
        atom *atm2 = ringsSeven[i][1];
        atom *atm3 = ringsSeven[i][2];
        atom *atm4 = ringsSeven[i][3];
        atom *atm5 = ringsSeven[i][4];
        atom *atm6 = ringsSeven[i][5];
        atom *atm7 = ringsSeven[i][6];
	//First lets check to see if there is a cation in the ring	
        int atomCheck;
        int atomCount = 0;
        if (xAtomCheck(atm1)) atomCount++;
        else atomCheck = 1;

        if (xAtomCheck(atm2)) atomCount++;
        else atomCheck = 2;

        if (xAtomCheck(atm3)) atomCount++;
        else atomCheck = 3;

        if (xAtomCheck(atm4)) atomCount++;
        else atomCheck = 4;

        if (xAtomCheck(atm5)) atomCount++;
        else atomCheck = 5;

        if (xAtomCheck(atm6)) atomCount++;
        else atomCheck = 6;

        if (xAtomCheck(atm7)) atomCount++;
        else atomCheck = 7;

        
        if (atomCount == 6) {
          if (atomCheck == 1 && yAtomCheck(atm1)) {aro = true;};
          if (atomCheck == 2 && yAtomCheck(atm2)) {aro = true;};
          if (atomCheck == 3 && yAtomCheck(atm3)) {aro = true;};
          if (atomCheck == 4 && yAtomCheck(atm4)) {aro = true;};
          if (atomCheck == 5 && yAtomCheck(atm5)) {aro = true;};
          if (atomCheck == 6 && yAtomCheck(atm6)) {aro = true;};
          if (atomCheck == 7 && yAtomCheck(atm7)) {aro = true;};
        }

        if (aro == true) {
          atm1->aromatic = true;
          atm2->aromatic = true;
          atm3->aromatic = true;
          atm4->aromatic = true;
          atm5->aromatic = true;
          atm6->aromatic = true;
          atm7->aromatic = true;
        }
  }
}

bool AM1_BCC::isPyrol_N(atom *atm) {
   if (atm->getAN() != 7)
      return false;
   vector< vector<atom *> > rings, ringsFive, ringsSix, ringsSeven;

   atomTyper *typer = new atomTyper;
   molecule *mol = dynamic_cast<molecule *>(atm->getParent());
   typer->findAllRings2(mol, rings, 8);

   for (int i=0; i<rings.size(); i++) {
      if (rings[i].size() == 5) {
         for (int j=0; j<rings[i].size(); j++) {
            if (rings[i][j] == atm)  {
               ringsFive.push_back(rings[i]);
            }
         }
      }
   }

   for (int i = 0; i < ringsFive.size(); i++) {
      bool aro = false;
      atom *atm1 = ringsFive[i][0];
      atom *atm2 = ringsFive[i][1];
      atom *atm3 = ringsFive[i][2];
      atom *atm4 = ringsFive[i][3];
      atom *atm5 = ringsFive[i][4];

      int aroCount = 0;
      if (atm1->aromatic && atm2->aromatic) aroCount += 2;
      if (atm2->aromatic && atm3->aromatic) aroCount += 2;
      if (atm3->aromatic && atm4->aromatic) aroCount += 2;
      if (atm4->aromatic && atm5->aromatic) aroCount += 2;
      if (atm5->aromatic && atm1->aromatic) aroCount += 2;

      int doubleCount = 0;
        vector<int> dBond(5);
        bond *bd1 = mol->getBond(atm1, atm2);
        if (bd1 == NULL) {return false;}
        if (bd1->order == 2) {
          if (!xAtomCheck(atm1) || !xAtomCheck(atm2) ) return false;
          doubleCount++;
          dBond[0] = 1;
        } else {dBond[0] = 0;}

        bond *bd2 = mol->getBond(atm2, atm3);
        if (bd2 == NULL) {return false;}
        if (bd2->order == 2) {
          if (!xAtomCheck(atm2) || !xAtomCheck(atm3) ) return false;
          doubleCount++;
          dBond[1] = 1;
        } else {dBond[1] = 0;}

        bond *bd3 = mol->getBond(atm3, atm4);
        if (bd3 == NULL) {return false;}
        if (bd3->order == 2) {
          if (!xAtomCheck(atm3) || !xAtomCheck(atm4) ) return false;
          doubleCount++;
          dBond[2] = 1;
        } else {dBond[2] = 0;}

        bond *bd4 = mol->getBond(atm4, atm5);
        if (bd4 == NULL) {return false;}
        if (bd4->order == 2) {
          if (!xAtomCheck(atm4) || !xAtomCheck(atm5) ) return false;
          doubleCount++;
          dBond[3] = 1;
        } else {dBond[3] = 0;}

        bond *bd5 = mol->getBond(atm5, atm1);
        if (bd5 == NULL) {return false;}
        if (bd5->order == 2) {
          if (!xAtomCheck(atm5) || !xAtomCheck(atm1) ) return false;
          doubleCount++;
          dBond[4] = 1;
        } else {dBond[4] = 0;}

        if (doubleCount == 2) {
           return true;
        }
        if (doubleCount == 1 && aroCount == 2)
           return true;
   }
   return false;
}

void AM1_BCC::BCC_ringRuleFive(molecule *mol, vector< vector< atom*> > &ringsFive) {
   for (int i = 0; i < ringsFive.size(); i++) {
      bool aro = false;
      atom *atm1 = ringsFive[i][0];
      atom *atm2 = ringsFive[i][1];
      atom *atm3 = ringsFive[i][2];
      atom *atm4 = ringsFive[i][3];
      atom *atm5 = ringsFive[i][4];
      ////cout <<atm1->getNum() <<"\t" <<atm1->aromatic << endl;
      ////cout <<atm2->getNum() <<"\t" <<atm2->aromatic << endl;
      ////cout <<atm3->getNum() <<"\t" <<atm3->aromatic << endl;
      ////cout <<atm4->getNum() <<"\t" <<atm4->aromatic << endl;
      ////cout <<atm5->getNum() <<"\t" <<atm5->aromatic << endl;

      int tg = 0; cin >> tg;
      //Now fused rings allowed...thus no prior assignment of aromaticity to any atoms...odd rule..see page 1627
      if (!atm1->aromatic && !atm2->aromatic && !atm3->aromatic
          && !atm4->aromatic && !atm5->aromatic) {
       // if (atm1->aromatic) return;
       // if (atm2->aromatic) return;
       // if (atm3->aromatic) return;
       // if (atm4->aromatic) return;
       // if (atm5->aromatic) return;
        //Now check for two double bonds
        int doubleCount = 0;
        vector<int> dBond(5);
        bond *bd1 = mol->getBond(atm1, atm2);
        if (bd1 == NULL) {return;}
        if (bd1->order == 2) {
          if (!xAtomCheck(atm1) || !xAtomCheck(atm2) ) return;
          doubleCount++;
          dBond[0] = 1;
        } else {dBond[0] = 0;}

        bond *bd2 = mol->getBond(atm2, atm3);
        if (bd2 == NULL) {return;}
        if (bd2->order == 2) {
          if (!xAtomCheck(atm2) || !xAtomCheck(atm3) ) return;
          doubleCount++;
          dBond[1] = 1;
        } else {dBond[1] = 0;}

        bond *bd3 = mol->getBond(atm3, atm4);
        if (bd3 == NULL) {return;}
        if (bd3->order == 2) {
          if (!xAtomCheck(atm3) || !xAtomCheck(atm4) ) return;
          doubleCount++;
          dBond[2] = 1;
        } else {dBond[2] = 0;}

        bond *bd4 = mol->getBond(atm4, atm5);
        if (bd4 == NULL) {return;}
        if (bd4->order == 2) {
          if (!xAtomCheck(atm4) || !xAtomCheck(atm5) ) return;
          doubleCount++;
          dBond[3] = 1;
        } else {dBond[3] = 0;}

        bond *bd5 = mol->getBond(atm5, atm1);
        if (bd5 == NULL) {return;}
        if (bd5->order == 2) {
          if (!xAtomCheck(atm5) || !xAtomCheck(atm1) ) return;
          doubleCount++;
          dBond[4] = 1;
        } else {dBond[4] = 0;}

        if (doubleCount == 2) {
          if (yAtomCheck(atm1) ) aro = true;
          if (yAtomCheck(atm2) ) aro = true;
          if (yAtomCheck(atm3) ) aro = true;
          if (yAtomCheck(atm4) ) aro = true;
          if (yAtomCheck(atm5) ) aro = true;

        }

        if (aro == true) {
          atm1->aromatic = true;
          atm2->aromatic = true;
          atm3->aromatic = true;
          atm4->aromatic = true;
          atm5->aromatic = true;

        }
      }

  }

}

bool AM1_BCC::xAtomCheck(atom *atm) {
  //This function just makes sure that the atom is one of the X types on page 1626 J. Comp. Chem AM1-BCC II paper
  if (atm->getAtomicNum() == 6 && atm->atoms.size() == 3) {return true;}
  else if(atm->getAtomicNum() == 7 && atm->atoms.size() == 2) {return true;}
  else if(atm->getAtomicNum() == 15 && atm->atoms.size() == 2) {return true;}
  else if(atm->getAtomicNum() == 7 && atm->atoms.size() == 3) {return true;}
  else if(atm->getAtomicNum() == 15 && atm->atoms.size() == 3) {return true;}
  else if(atm->getAtomicNum() == 8 && atm->atoms.size() == 2) {return true;}
  else if(atm->getAtomicNum() == 16 && atm->atoms.size() == 2) {return true;}
  return false;
}

bool AM1_BCC::yAtomCheck(atom *atm) {
  if (atm->getAtomicNum() == 6 && atm->atoms.size() == 2) {return true;}   //need to check formal charge as well
  else if(atm->getAtomicNum() == 7 && atm->atoms.size() == 2) {return true;} //need to check formal charge
  else if(atm->getAtomicNum() == 8 && atm->atoms.size() == 2) {return true;}
  else if(atm->getAtomicNum() == 16 && atm->atoms.size() == 2) {return true;}
  else if(atm->getAtomicNum() == 7 && atm->atoms.size() == 3) {return true;}
  else if(atm->getAtomicNum() == 15 && atm->atoms.size() == 2) {return true;}
  return false;
}

void AM1_BCC::BCC_averageIdenticalTypes(molecule *mol) {
	for (int i=0; i<mol->atoms.size(); i++) {
		atom *atm = mol->atoms[i];
		//Lets check for identical h'2 on carbon
		if (atm->getAtomicNum() == 6) {
		   float totCharge = 0;
		   float hCount = 0;
		   for (int j=0; j<atm->atoms.size(); j++) {
		      atom *tmp = atm->atoms[j];
		      if (tmp->getAtomicNum() == 1) {
		         totCharge += tmp->getCharge();
			 hCount++;
		      }
		   }
		    
		   if (hCount > 1) {
		     float avgCharge = totCharge/hCount;
		     for (int j=0; j<atm->atoms.size(); j++) {
		      atom *tmp = atm->atoms[j];
		      if (tmp->getAtomicNum() == 1) {
		         tmp->setCharge( avgCharge );
		      }
		     }
		   }
		
		}
		
		
		if (atm->getAtomicNum() == 7) {
		  int count = 0;
		  float totalCharge = 0;
		  for (int j=0; j<atm->atoms.size(); j++) {
		    atom *tmp = atm->atoms[j];
		    if (tmp->getAtomicNum() == 8) {
		       totalCharge += tmp->getCharge();
		       count++;
		    }
		  }
		  
		  if (count == 2) {
		   for (int j=0; j<atm->atoms.size(); j++) {
		    atom *tmp = atm->atoms[j];
		    if (tmp->getAtomicNum() == 8) tmp->setCharge(totalCharge/2.0); 
		   }
		  }
		}
	}
}



void AM1_BCC::BCC_BondOrderString(molecule *mol) {
  atomTyper *typer = new atomTyper;
  for (int i = 0; i<mol->bonds.size(); i++) {
    bond *bd = mol->bonds[i];
    atom *from = bd->from;
    atom *to = bd->to;
    if (bd->order == 1) {
        if (typer->isDelocalized(bd) ) bd->bcc = "09";
        else
        if ( (!from->aromatic || !to->aromatic) && (from->formalCharge >= 0 && to->formalCharge >= 0)) {
          bd->bcc = "01";
        }
        else
        if (from->aromatic && to->aromatic) {
          bd->bcc = "07";
        }
        else
        if ( (from->formalCharge == 1 && to->formalCharge == -1) || (from->formalCharge == -1 && to->formalCharge == 1) ) {
          bd->bcc = "06";
        }
        else
        if ((from->formalCharge == -1 && to->formalCharge == 0) || (from->formalCharge == 0 && to->formalCharge == -1) ) {
          bd->bcc = "09";
        }
    }
    else
    //###MISSING RUL RIGHT HERE FIX ##############
    if (bd->order == 2) {
        if (typer->isDelocalized(bd) ) bd->bcc = "09";
        else
        //You need to add in the check for deloc double bonds first I think
        if (!from->aromatic && !to->aromatic) {
          bd->bcc = "02";
        }
        else
        if (from->aromatic && to->aromatic) {
          bd->bcc = "08";
        }
    }
    else bd->bcc = "03";
  }

  delete typer;
}

void AM1_BCC::BCC_AtomTypes(molecule *mol) {
  atomTyper *typer = new atomTyper;
  mol->updateValence();
  //YOU SHOULS FIX THIS LITTLE HACK RIGHT HERE
  //ALSO REMEBER THAT YOU REMOVE THE BONDS ARRAY AT THE END
  for (int i=0; i<mol->atoms.size(); i++) {
     for (int j=i+1; j<mol->atoms.size(); j++) {
       bond *bd = mol->getBond(mol->atoms[i], mol->atoms[j]);
       if (bd) {
          mol->atoms[i]->bonds.push_back(bd);
	  mol->atoms[j]->bonds.push_back(bd);
       }
     }
  }

  for (int i=0; i<mol->atoms.size(); i++) {
    atom *atm = mol->atoms[i];
    if (atm->getAtomicNum() == 6) {
      if (atm->atoms.size() == 4) atm->bcc = "11";
      else if (atm->atoms.size() == 3) {
        if (atm->aromatic) {
          int onCheck = 0;
          for (int j=0; j<atm->atoms.size(); j++) {
            atom *tmpAtm = atm->atoms[j];
            if (tmpAtm->getAtomicNum() == 8 && tmpAtm->valence == 2 && tmpAtm->aromatic) {onCheck = 1; break;}
	    else if (tmpAtm->getAtomicNum() == 7 && tmpAtm->valence == 2 && tmpAtm->aromatic) {onCheck = 1; break;}
          }
          if (onCheck == 1) atm->bcc = "17";
          else atm->bcc = "16";
        } else {
	  for (int j=0; j<atm->atoms.size(); j++) {
	    bond *bd = mol->getBond(atm, atm->atoms[j]);
            if (bd->order == 2) {
	      if (bd->from->getAtomicNum() == 6 && bd->to->getAtomicNum() == 6) atm->bcc = "12";
              else if (bd->from->getAtomicNum() == 7 || bd->to->getAtomicNum() == 7) atm->bcc = "13";
              else if (bd->from->getAtomicNum() == 15 || bd->to->getAtomicNum() == 15) atm->bcc = "13";
              else if (bd->from->getAtomicNum() == 8 || bd->to->getAtomicNum() == 8) atm->bcc = "14";
              else if (bd->from->getAtomicNum() == 16 || bd->to->getAtomicNum() == 16) atm->bcc = "14";
              break;  
            }
          }
        }
      } else atm->bcc = "15";
    }
    else
    if (atm->getAtomicNum() == 7) {
        if (atm->valence == 4) atm->bcc = "21";
        else if (atm->valence == 3) {
             ////cout <<"atm->getNum: " << atm->getNum() << endl;
             //int test = 0; cin >> test;
            //check for aromatic highly delocalized case
            int aroCount = 0;
            for (int j=0; j<atm->atoms.size(); j++) {
              if (atm->atoms[j]->aromatic) aroCount++;
            }
            /*
            if (atm->getNum() == 8 || atm->getNum() == 9) {
               //cout <<"atm->getNum() "<<atm->getNum() <<endl;
               //cout <<"aroCount: "<< aroCount << endl;
               //cout <<"aromatic: " << atm->aromatic << endl;
               //cout <<"isNitro: " << typer->isNitro_N(atm) << endl;
            }
            */
            if (isPyrol_N(atm) || atm->aromatic == true 
            || typer->isNitro_N(atm)) 
               atm->bcc = "23";

            else//check for amine
	    if(typer->isAmide_N(atm) ) atm->bcc = "22";
            else if (typer->isAmine_N(atm)) atm->bcc = "21";
            else atm->bcc = "21";            
        }
        else if (atm->valence == 2) {
          if (atm->formalCharge < 0) {
            //Check for delocalization
            if (atm->atoms[0]->aromatic && atm->atoms[1]->aromatic) 
	       atm->bcc = "22";
            else atm->bcc = "21";
          }
          else {
            if ( (atm->bonds[0]->order == 2 && atm->bonds[1]->order == 1) 
            || (atm->bonds[1]->order == 2 && atm->bonds[0]->order == 1) ) 
            { 
                atm->bcc = "24";
            }
            else atm->bcc = "25";
          }
        } else atm->bcc = "25";
        //if (atm->getNum() == 7) atm->bcc = "23";
        //if (atm->getNum() == 8) atm->bcc = "24";
    }
    else
    if (atm->getAtomicNum() == 8) {
        if (atm->valence == 2) atm->bcc = "31";
        else {
          //CHECK FOR LACTONE OR LACTAM RIGHT HERE
          if (typer->isLactoneCarbonylOxygen(atm) || typer->isLactamCarbonylOxygen(atm)) atm->bcc = "33";
          else
          if (typer->isEster_O(atm) || typer->isCarboxyilicAcid_O(atm)) atm->bcc = "32";
          else atm->bcc = "31";
        }
    }
    else
    if (atm->getAtomicNum() == 16) {
        if (atm->valence == 4) atm->bcc = "53";
        else if (atm->valence == 3) atm->bcc = "52";
        else if (atm->valence == 2) atm->bcc = "51";
        else if (atm->valence == 1) atm->bcc = "51";
    }
    else
    if (atm->getAtomicNum() == 15) {
      if (atm->valence == 4) atm->bcc = "42";
      else if (atm->valence == 3) {
          //check to see if double bond
          int orderCheck = 0;
          for (int j=0; j<atm->bonds.size(); j++) {
            if (atm->bonds[j]->order == 2) {
              orderCheck = 1;
              break;
            }
          }
          if (orderCheck == 1) {atm->bcc = "42";}
          else {atm->bcc = "41";}
      } else {
          atm->bcc = "41";
      }
      
    }
    else if (atm->getAtomicNum() == 1) atm->bcc = "91";
    else if (atm->getAtomicNum() == 9) atm->bcc = "71";
    else if (atm->getAtomicNum() == 17) atm->bcc = "72";
    else if (atm->getAtomicNum() == 35) atm->bcc = "73";
    else if (atm->getAtomicNum() == 53) atm->bcc = "74";    
    else if (atm->getAtomicNum() == 14) atm->bcc = "61";
  }
  
  delete typer;

  //This is only here to clear the bonds array that you created before
  // you realy aren't using the atoms::bonds much any more
  for (int i=0; i<mol->atoms.size(); i++) {
    mol->atoms[i]->bonds.clear();
  }
}


bool AM1_BCC::BCC_getCorrections(molecule *mol) {

   //LINUX 3
   char *dynamol = getenv("DYNAMOL");
   QString PATH = dynamol;
   PATH += "/ForceField/bcc.txt";
  
  //WINDOWS 1
   //QString PATH = "ForceField\\bcc.txt";
  
  //////////////cout <<"PATH is " << PATH.latin1() << endl;
  ifstream inFile;
  inFile.open(PATH.latin1(), ios::in);
  if (!inFile) {
	////////////cout << "File AM1-BCC/bcc.txt was not opened, called from AM1_BCC::BCC_getCorrections " << endl; 
	return false;
 }
 
  //First stage is to read in the entire file into memory;
  vector<string> lines;
  string tmp;
  getline(inFile, tmp); //this just reads the first bs line
  
  while (!inFile.eof() ) {
    getline(inFile, tmp);
    lines.push_back(tmp);
  }
/*
  for (int i=0; i<mol->atoms.size(); i++) {
    atom *atm = mol->atoms[i];
    //cout <<atm->getNum()<<"\t"<<atm->getSym()<<"\t";
    //cout <<atm->valence<<"\t"<<atm->charge<<endl;
  }
*/

  for (int i=0; i<mol->bonds.size(); i++) {
    bond *bd = mol->bonds[i];
    atom *from = bd->from;
    atom *to = bd->to;
    int fInt, tInt; //to get integer values of bcc types

    fInt = atoi(from->bcc.c_str() );
    tInt = atoi(to->bcc.c_str() );
    string match = "";
    if (tInt < fInt) {
      match.append(to->bcc);
      match.append(bd->bcc);
      match.append(from->bcc);
    } else {
      match.append(from->bcc);
      match.append(bd->bcc);
      match.append(to->bcc);
    }

    if ((from->getNum() == 7 && to->getNum() == 8) 
    || (from->getNum() == 8 && to->getNum() == 7) ) {
       ////cout << from->getNum() << "\t" << to->getNum() << "\t"<<match << endl;
       ////cout <<"You are now lookint at bond types for atom 22"<<endl;
       //int test = 0;
       //cin >> test;

    }
    

    istringstream inString;
    string tmp;
    float chargeCorr;
    int matchCheck = 0;
    for (int j=0; j<lines.size(); j++) {
      inString.str(lines[j]);
      inString >> tmp >> tmp;
      if (tmp == match) {
        inString >> tmp >> chargeCorr;
        matchCheck = 1;
        break;
      } 
    }
    if (matchCheck == 0) {
      //cout <<"No bond charge correction"<<endl;
      //return false;
      //return true;
      //int test = 0;
      //cin >> test;
    }

     int toNum = atoi( to->bcc.c_str() );
     int fromNum = atoi( from->bcc.c_str() );
     if (toNum > fromNum ) {
      to->setCharge( to->getCharge() - chargeCorr );
      from->setCharge( from->getCharge() + chargeCorr );
     } else {
      from->setCharge( from->getCharge() - chargeCorr );
      to->setCharge(to->getCharge() + chargeCorr );
     }      
    }
    return true;
}



