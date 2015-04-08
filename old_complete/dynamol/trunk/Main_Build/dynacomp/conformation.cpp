/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "conformation.h"
#include "linAlg.h"

#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "nonbond.h"
#include "torsion.h"

#include <queue>
#include "energy.h"
#include "forcefield.h"
#include "charge.h"

#include <stdexcept>

#include "atomtyper.h"
#include "time.h"
#include "cluster.h"

//Dynamol Base Library Includes
#include "../dynabase/utility.h"


namespace dynacomp {

/** NOW WE GET INTO THE CONFORMATION CLASS STUFF */
Conformation::Conformation()
{
   stop = false;
   errorMsg = "";
}


Conformation::~Conformation()
{
}

string Conformation::getErrorMsg()
{ return errorMsg; }

void Conformation::run() {

   //Send a display message to the user
   string text = "Running Systematic Search ";
   vector<string> lables;  lables.push_back(text);
   
   deque<confNode *> confList;
   energy eng;
   
   
   bond *bd = rotBonds[0];
   //molecule *tmpMol = dynamic_cast<molecule *>(bd->lastParent());
   molecule *tmpMol = bd->getParent();
  
   orderBonds();
   
   
   vector<float> coordHold;
   getMolCoords(tmpMol, coordHold);
   
   //Lets get the set of needed nonBonds
   vector<nbPtr> nonBonds, frozenNb;
   vector<torPtr> torsions, frozenTor;
   buildNonBondList(tmpMol, nonBonds, frozenNb);
   buildTorsionList(torsions, frozenTor);
   
   // This section calculates the static energies
   //   static energies are those that will not chage
   //   during the search
   //
   float angleE = eng.angleBendEnergy(tmpMol->angles);
   float bondE = eng.bondStretchEnergy(tmpMol->bonds);
   float nonBondE = eng.nonBondEnergy(frozenNb);
   float torsionE = eng.torsionalEnergy(frozenTor);
   
   float totFrozenE = angleE + bondE + nonBondE + torsionE;
   
   deque<confNode *> finNodes;
   for (unsigned int i=0; i<confList.size(); i++) {
      setMolCoords(tmpMol, coordHold);
      for (unsigned int j=0; j<confList[i]->angles.size(); j++) {
         bond *bd = rotBonds[j];
         float rotAngle = confList[i]->angles[j];
         rotateBond(bd, rotAngle);
      }
      if (i % 1000 == 0) {
         string num = dynabase::setNum(i);
         string num2 = dynabase::setNum(confList.size());
         text = "Generating Conformation " + num + " of " + num2;
         lables.clear();  lables.push_back(text);
      }
      
      confList[i]->energy = nonBondCheck(nonBonds, cutoff);
      if (confList[i]->energy < 100000.0) {
         finNodes.push_back(confList[i]);
         confList[i]->energy += totFrozenE;
         confList[i]->energy += eng.torsionalEnergy(torsions);
         confList[i] = NULL;
      } 
      if (stop == true) break;
   }
   
  
   for (unsigned int i=0; i<confList.size(); i++) {
      if (confList[i] != NULL) delete confList[i];
   }
   confList.resize(0);

   if (finNodes.size() == 0) {
	return;
   } 
   while (finNodes.size() > 2000) {
	int num = rand() % finNodes.size();
	finNodes.erase(finNodes.begin() + num);
   } 
   if (clusterNum > 0) {
      deque<confNode *> best;
      deque< deque< deque<confNode *> > > clusters;
      clusterByAngle(finNodes, clusterNum, best, clusters);
      finNodes.clear();
      finNodes = best;
   } 
   
   //Now we check to see if minimization is turned on
   long int confCount = 0;
   if (min && !stop) {
      string ffType = tmpMol->ffTypes;
      string chargeType = tmpMol->chargeType;
      string method = "CG";
      for (unsigned int i=0; i<finNodes.size(); i++) {
         setMolCoords(tmpMol, coordHold);
         for (unsigned int j=0; j<finNodes[i]->angles.size(); j++) {
            bond *bd = rotBonds[j];
            float rotAngle = finNodes[i]->angles[j];
            rotateBond(bd, rotAngle);
         }
         
         if (i % 10 == 0) {
            string num = dynabase::setNum(i);
            string num2 = dynabase::setNum(finNodes.size());
            text = "Minimizing " + num + " of " + num2;
            lables.clear();  lables.push_back(text);
         }
         eng.setUp(tmpMol, method, ffType, chargeType, maxIter, rmse, maxForce, minE);
         eng.setMol(tmpMol);
         eng.setUpdate(false);
         eng.CG_minimize(maxIter, rmse, maxForce, minE);
         
         //YOU NEED TO ADD SUPPORT FOR WRITING FILES
         confCount++;
         if (stop == true) break;
      }
   }
   
   if (!min && !stop) {
      string header = "Saving to " + outFile;
      lables.clear();
      lables.resize(2);
      lables[0] = header;
      string text = "Saving Conformation ";
      for (unsigned int i=0; i<finNodes.size(); i++) {
         setMolCoords(tmpMol, coordHold);
         for (unsigned int j=0; j<finNodes[i]->angles.size(); j++) {
            bond *bd = rotBonds[j];
            float rotAngle = finNodes[i]->angles[j];
            rotateBond(bd, rotAngle);
         }
         string num = dynabase::setNum(i);
         string num2 = dynabase::setNum(finNodes.size());
         string label = text + num + " of " + num2;
         lables[1] = label;

         confCount++;
         if (stop == true) break;
      }
   }
   for (unsigned int i=0; i<finNodes.size(); i++) {
      delete finNodes[i];
   }
   finNodes.resize(0);
  
   string total = dynabase::setNum(confCount);
   text = "Search Done: " + total + " conformations";
   lables.clear();  lables.push_back(text);
}


void Conformation::orderBonds() {
   atomsToRotate.resize(rotBonds.size());
   for (unsigned int i=0; i<rotBonds.size(); i++) {
      bond *bd = rotBonds[i];
      atom *from = bd->from;
      atom *to = bd->to;
      
      vector<atom *> atmsToRotateFrom, atmsToRotateTo;
      int fromNum = connectedAtoms(from, to, atmsToRotateFrom);
      int toNum = connectedAtoms(to, from, atmsToRotateTo);
      
      if (toNum > fromNum) {
        atom *tmp = bd->from;
        bd->from = bd->to;
        bd->to = tmp;
        atomsToRotate[i] = atmsToRotateFrom;
      } else {
        atomsToRotate[i] = atmsToRotateTo;
      }
   }
}

int Conformation::connectedAtoms(atom *atm, atom *other, vector<atom *> &atmsToRotate) {
   
   molecule *mol = dynamic_cast<molecule *>(atm->getParent());
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
     mol->atoms[i]->visited = false;
   }
  
   atm->visited = true;
   other->visited = true;
   deque<atom *> atomQueu;
   atomQueu.push_back(atm);
   int count = 0;
   while (atomQueu.size() > 0) {
      atom *currAtm = atomQueu.front();
      atomQueu.pop_front();
      for (unsigned int i=0; i<currAtm->atoms.size(); i++) {
         atom *tmp = currAtm->atoms[i];
         if (tmp->visited == false) {
            tmp->visited = true;
            atomQueu.push_back(tmp);
            atmsToRotate.push_back(tmp);
            count++;
         }
      }
   }
   
   return count;
}

void Conformation::buildNonBondList(molecule *tmpMol, vector<nbPtr> &nonBonds, vector<nbPtr> &frozenNb) 
{
    molecule *holdMol = new molecule;
    *holdMol = *tmpMol;
    
    for (unsigned int i=0; i<rotBonds.size(); i++) {
       rotateBond(tmpMol, rotBonds[i], 5.0);
    }
   
    vector<atom *> frozenAtoms;
    for (unsigned int i=0; i<tmpMol->atoms.size(); i++) {
       float *cd1 = tmpMol->atoms[i]->fCoords;
       float *cd2 = holdMol->atoms[i]->fCoords;
       
       float dist = distance(cd1, cd2);
       if (dist < .0001) 
          frozenAtoms.push_back(tmpMol->atoms[i]);
    }
    
    for (unsigned int i=0; i<tmpMol->nonBonds.size(); i++) {
       nbPtr nb = tmpMol->nonBonds[i];
       atom *atm1 = nb->atm1;
       atom *atm2 = nb->atm2;
       
       bool oneFrozen, twoFrozen;
       oneFrozen = twoFrozen = false;
       bool frozen = false;
       
       for (unsigned int j=0; j<frozenAtoms.size(); j++) {
         if (frozenAtoms[j] == atm1) oneFrozen = true;
         if (frozenAtoms[j] == atm2) twoFrozen = true;
         
         if (oneFrozen && twoFrozen) {
            frozen = true;
            break;
         }
       }
       
       if (!frozen) nonBonds.push_back(nb);
       else frozenNb.push_back(nb);
    } 
}

void Conformation::buildTorsionList(vector<torPtr> &torsions, vector<torPtr> &frozenTors) 
{
   /** The first section generates a list of all torsions and all molecules
   */
   vector<torPtr> allTors;
   vector<molecule *> allMols;
   for (unsigned int i=0; i<rotBonds.size(); i++) {
      //molecule *mol = dynamic_cast<molecule *>(rotBonds[i]->lastParent());
      molecule *mol = rotBonds[i]->getParent();
      bool isIn = false;
      for (unsigned int j=0; j<allMols.size(); j++) {
         if (mol == allMols[j]) {
           isIn = true;
           break;
         }
      }
      if (!isIn) allMols.push_back(mol);
   }
   
   for(unsigned int i=0; i<allMols.size(); i++) {
      molecule *mol = allMols[i];
      for (unsigned int j=0; j<mol->torsions.size(); j++) {
         allTors.push_back(mol->torsions[j]);
      }
   }
   
   /** This section makes a list of all torsions associated with a rotable
   *  bond.  These torsions are save in the torsions vector
   */
   for (unsigned int i=0; i<rotBonds.size(); i++) {
      bond *bd = rotBonds[i];
      atom *atm1 = bd->from;
      atom *atm2 = bd->to;
      //molecule *mol = dynamic_cast<molecule *>(bd->lastParent());
      for (unsigned int j=0; j<allTors.size(); j++) {
         torPtr t = allTors[j];
         int count = 0;
         if (t->atm2 == atm1 || t->atm2 == atm2) count++;
         if (t->atm3 == atm1 || t->atm3 == atm2) count++;
         if (count == 2) {
            torsions.push_back(t);
         } 
      }
   }
   
   /** This section makes a list of all the torsions that are not part of
   *   a rotable bond.  These are stored int he frozenTors vector
   */
   for (unsigned int i=0; i<allTors.size(); i++) {
      torPtr t = allTors[i];
      
      bool wasIn = false;
      for (unsigned int j=0; j<torsions.size(); j++) {
         if (torsions[j] == t) {
           wasIn = true;
           break;
         }
      }
      
      if (!wasIn) frozenTors.push_back(t);
   }
}

/** This function uses a distant dependant dielectric...avoids a sqrt() call */
float Conformation::nonBondCheck(vector<nbPtr> &nonbondVec, float cutoff) {
   float vdwE = 0;
   float chargeE = 0;	
   float tChargeE = 0;
   float tVanE = 0;
   float totalE = 0;
   for (unsigned int i=0; i<nonbondVec.size(); i++) {
      nbPtr nb = nonbondVec[i];
      atom *atm1 = nb->atm1;
      atom *atm2 = nb->atm2;
      	
      float *cd1 = atm1->fCoords;
      float *cd2 = atm2->fCoords;		
	
      float a = cd1[0] - cd2[0];
      float b = cd1[1] - cd2[1];
      float c = cd1[2] - cd2[2];
		
      float dist2 = a*a + b*b + c*c;
		
      if (dist2 < 2.25) {
         cout <<"Because of distace"<<endl;
         return 100000.0;
      }
      dist2 = 1.0/dist2;
		
      float dist4 = dist2*dist2;
      float dist6 = dist4*dist2;
      float dist12 = dist6*dist6;
	
      float sig = (atm1->getSigma() + atm2->getSigma());
      float sig2 = sig*sig;
      float sig3 = sig2*sig;

      float sigma6 = sig3*sig3;	
      float sigma12 = sigma6*sigma6;
	
      float epsilon = atm1->getEpsilon() *atm2->getEpsilon();
      float chrg = atm1->getCharge() * atm2->getCharge();

      /** Distant dependant...avoids a sqrt() call */
      chargeE = chrg * dist2;
        	
      if (sigma6 == 0 || sigma12 == 0) vdwE = 0;
      else vdwE = epsilon * (sigma12*dist12 - sigma6*dist6);
		
      totalE = 	4.0*vdwE*nb->scaleFactor;
      if (totalE > cutoff) {
         return 100000.0;
      }
      tChargeE += chargeE*nb->scaleFactor;
      tVanE += totalE;

    }
    tChargeE *= 332.5;
    
    return tChargeE + tVanE;
}

confNode *Conformation::buildConfList(deque<confNode *> &confList) {
   confNode *start = new confNode;
   confList.resize(0);
   confList.push_back(start);
   
   deque<confNode *> nodesToDelete;
   int count  = 0;
   while (confList.size() > 0) {
      confNode *currNode = confList.front();
      confList.pop_front();
      nodesToDelete.push_back(currNode);
      if (currNode->angles.size() < rotBonds.size()) {
         bond *bd = rotBonds[currNode->angles.size()]; 
         for (float i=0.0; i<360.0; i += bd->defInc) {
            confNode *newNode = new confNode;
            newNode->angles = currNode->angles;//
            newNode->angles.push_back(i);
            count++;
            currNode->neigh.push_back(newNode);
            confList.push_back(newNode);
         }
      } else {
        for (unsigned int i=0; i<nodesToDelete.size(); i++) {
           delete nodesToDelete[i];
        }
        nodesToDelete.clear();
        return start;
      }
   }  
   return start;
}


void Conformation::setMolCoords(molecule *mol, const vector<float> &coords) {
   int count = 0;
   if (coords.size() != 3*mol->atoms.size()) {
   }
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      float *cd = mol->atoms[i]->fCoords;
      for (int j=0; j<3; j++) {
         cd[j] = coords[count]; 
         count++;
      }
   }
}

void Conformation::getMolCoords(const molecule *mol, vector<float> &coords) {
   coords.clear();
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      float *cd = mol->atoms[i]->fCoords;
      for (int j=0; j<3; j++) 
         coords.push_back(cd[j]);
   }
}

void Conformation::setNewBonds(vector<bond *> &newBonds, vector<bond *> &currBonds, molecule *oldMol, molecule *newMol) {
   for (unsigned int i=0; i<currBonds.size(); i++) {
            
      int tFromNum = currBonds[i]->fromAtom()->getNum();
      int tToNum = currBonds[i]->toAtom()->getNum();
           
      for (unsigned int j=0; j< oldMol->bonds.size(); j++) {
         int fromNum = oldMol->bonds[j]->fromAtom()->getNum();
         int toNum = oldMol->bonds[j]->toAtom()->getNum();
           
         if (fromNum == tFromNum && toNum == tToNum) {
            newBonds.push_back( newMol->bonds[j] );
            newMol->bonds[j]->defInc = currBonds[i]->defInc;
            break;
         }
      }
   }
}
bool Conformation::setUp(list<molecule *> *molList, vector<bond *> &rotBonds, string outFile) {
  this->molList = new list<molecule *>;
  list<molecule *>::iterator mIter;
  vector<bond *> newBonds;
  for (mIter = molList->begin(); mIter != molList->end(); mIter++) {
     molecule *mol = *mIter;
     molecule *tmpMol = new molecule;
     *tmpMol = *mol;
     this->molList->push_back(tmpMol);
     setNewBonds(newBonds, rotBonds, mol, tmpMol);
  }
  this->rotBonds = newBonds;
  this->outFile = outFile;
  
  return prepMolList(*this->molList);
}

bool Conformation::prepMolList(list<molecule *> &molList) {
   list<molecule *>::iterator mIter;
   
   bool success = true;
   for (mIter = molList.begin(); mIter != molList.end(); mIter++) {
      molecule *mol = *mIter;
      //Lets set up the atomtype stuff one time right here
      forceField ff;
      string type = "GAFF";
      string chrg = "AM1-BCC-fast";
     
      ff.setAtomTypes(mol, type);
      ff.buildLists(mol, type);
      charge chg;
      success = chg.run(mol, chrg);
   }
   
   //Should  you return success here? 
   return true;
}

void Conformation::eSetup(bool min, float cutoff,  int clusterNum, float rmse, float minE, float maxForce, int maxIter) {
   this->min = min;
   this->cutoff = cutoff;
   this->clusterNum = clusterNum;
   this->rmse = rmse;
   this->minE = minE;
   this->maxForce = maxForce;
   this->maxIter = maxIter;
}

void Conformation::setRotableBonds(molecule *mol, vector<bond *> &BONDS) {
   atomTyper typer;
   vector< vector<atom *> > rings;
   typer.findAllRings2(mol, rings, 19);
   for (unsigned int i=0; i<mol->bonds.size(); i++) {
     bond *bd = mol->bonds[i];
     bool rot = true;
     atom *from = bd->fromAtom();
     atom *to = bd->toAtom();
     if (bd->from->inRing && bd->to->inRing) {
        //Now we must check to see if they are in different rings
        for (unsigned int j=0; j<rings.size(); j++) {
           bool fromMatch, toMatch;
           fromMatch = toMatch = false;
           for (unsigned int k=0; k<rings[j].size(); k++) {
              if (rings[j][k] == from) fromMatch = true;
              if (rings[j][k] == to) toMatch = true;
              if (fromMatch && toMatch) break;
           }
           if (fromMatch && toMatch) {
             rot = false;
             break;
           }
        }
     }
     if (from->getAtomicNum() == 1 || to->getAtomicNum() == 1) rot = false;
     //We now set the bond as rotable..even tho we will omit it from the initial select.
     //This will allow th resarcher to add certain bonds to the list
     if (rot) bd->rotable = true;
     if ( typer.heavyAtoms(from) == 1 || typer.heavyAtoms(to) == 1) rot = false;
     
     if (rot) BONDS.push_back(bd);
   }
}

//void  Conformation::rotateBond(molecule *mol, bond *bd, vector<float> &rotZ) {
void  Conformation::rotateBond(molecule *mol, bond *bd, float degree) {
   
  for (unsigned int i=0; i<mol->atoms.size(); i++) {
     mol->atoms[i]->visited = false;
  }
  vector<float> rotZ(16);
  setRotZ(rotZ, degree);
  /** The first section involves aligning the bond with the z Axis */
  float *tmpfCoords1 = bd->fromAtom()->fCoords;
  float *tmpfCoords2 = bd->toAtom()->fCoords;
  vector<float> trans(16), rotX(16), rotY(16), inverse(16);
  vector<float> mat(16), M(16);
  vector<float> iM(16);
  vector<float> fM(16);

  //determine the direction cosines
  vector<double> cosines(3);
  dirCosines(cosines, tmpfCoords1, tmpfCoords2);

  float d = sqrt(cosines[1]*cosines[1] + cosines[2]*cosines[2]);

  //Set the transformation matrices for all rotations
  setTransMat(trans, tmpfCoords2[0], tmpfCoords2[1], tmpfCoords2[2]);
  setRotX(rotX, cosines[2]/d, cosines[1]/d);
  setRotY(rotY, d, cosines[0]);
  //######## REPLACE NEXT TWO COMMENTED LINES

  multTransMatrix_16(mat, trans, rotX);
  multTransMatrix_16(M, mat, rotY);

  /*determine the inverse matrix of the TXY combination.  result is stored in inverse
    This step is done before z Multiplication so that we can quickly undue this step
  */
  invertMatrix(M, inverse);

  //Multiply the Z matrix rotation by M
  multTransMatrix_16(iM, M, rotZ);
 
  /*Now multiply by the inverse iM to get the full Matrix fM
    It is with this matrix that you will multiply each atomic coordinate
    That is on the rotating side of the bond... should always be the smaller of the fragments
  */

  multTransMatrix_16(fM, iM, inverse);
  //Apply the rotation to each of the effected atoms...this actually isn't right
  applyRot(mol, bd, fM);

}


void Conformation::applyRot(molecule *mol, bond *bd, vector<float> &fM) {
  //Apply the rotation to each of the effected atoms...this actually isn't right
  atom *baseAtm = bd->fromAtom();
  queue<atom *> rotQueue;

  unsigned int atomSize = mol->atoms.size();
  for (unsigned int i=0; i<atomSize; i++) {
    mol->atoms[i]->visited = 0;
  }

  rotQueue.push(bd->toAtom());
  atom *tmpAtm, *tba;
  vector<float> vec1(4);
  vec1[3] = 1;

  while (!rotQueue.empty()) {
    tmpAtm = rotQueue.front();
    rotQueue.pop();
    for (unsigned int i=0; i<tmpAtm->atoms.size(); i++) {
      tba = tmpAtm->atoms[i];
      if (tba->visited == false && tba != baseAtm) {
        rotQueue.push(tba);
        tba->visited = 1;
        float *cd = tba->fCoords;

        multTransMatrix_4(vec1, cd, fM);
        
        cd[0] = vec1[0];
        cd[1] = vec1[1];
        cd[2] = vec1[2];
      }
    }
  }
}

void Conformation::rotateBond(bond *bd, float degree) {
   vector<float> rotZ(16);
  setRotZ(rotZ, degree);
  /** The first section involves aligning the bond with the z Axis */
  float *tmpfCoords1 = bd->fromAtom()->fCoords;
  float *tmpfCoords2 = bd->toAtom()->fCoords;
  vector<float> trans(16), rotX(16), rotY(16), inverse(16);
  vector<float> mat(16), M(16);
  vector<float> iM(16);
  vector<float> fM(16);

  //determine the direction cosines
  vector<double> cosines(3);
  dirCosines(cosines, tmpfCoords1, tmpfCoords2);

  float d = sqrt(cosines[1]*cosines[1] + cosines[2]*cosines[2]);

  //Set the transformation matrices for all rotations
  setTransMat(trans, tmpfCoords2[0], tmpfCoords2[1], tmpfCoords2[2]);
  setRotX(rotX, cosines[2]/d, cosines[1]/d);
  setRotY(rotY, d, cosines[0]);
  //######## REPLACE NEXT TWO COMMENTED LINES

  multTransMatrix_16(mat, trans, rotX);
  multTransMatrix_16(M, mat, rotY);

  /*determine the inverse matrix of the TXY combination.  result is stored in inverse
    This step is done before z Multiplication so that we can quickly undue this step
  */
  invertMatrix(M, inverse);

  //Multiply the Z matrix rotation by M
  multTransMatrix_16(iM, M, rotZ);
 
  /*Now multiply by the inverse iM to get the full Matrix fM
    It is with this matrix that you will multiply each atomic coordinate
    That is on the rotating side of the bond... should always be the smaller of the fragments
  */

  multTransMatrix_16(fM, iM, inverse);
  //Apply the rotation to each of the effected atoms...this actually isn't right
  applyRot(bd, fM);
}

void Conformation::applyRot(bond *bd, vector<float> &fM) {
   vector<float> vec1(4);
   vec1[3] = 1;

   int index = 0;
   for (unsigned int i=0; i<rotBonds.size(); i++) {
     if (rotBonds[i] == bd) index = i;
   }
   
   for (unsigned int i=0; i<atomsToRotate[index].size(); i++) {
      float *cd = atomsToRotate[index][i]->fCoords;
      multTransMatrix_4(vec1, cd, fM);  
      cd[0] = vec1[0];
      cd[1] = vec1[1];
      cd[2] = vec1[2];
   }
}

void Conformation::systematicSearch(molecule *mol, vector<bond *> &rotBonds, string outFile) {
}

void Conformation::clusterByAngle(deque<confNode *> &nodeList, int numOfClusters, deque<confNode *> &best, deque< deque< deque<confNode *> > > &clusters ) {
   string label = "Clustering Conformations";
   vector<string> lables;
   lables.push_back(label);

   //molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1010));
   //e->setDisplayText(lables);
   //e->sendEvent();

   /** The first section reorganizes the data into a vector< vector<float> > structure
   *   as this is what the cluster::hierarchal() function requires.
   */
   vector< vector<float> > datMat;
   vector<float> props;
   for (unsigned int i=0; i<nodeList.size(); i++) {
      vector<float> row = nodeList[i]->angles;
      props.push_back(nodeList[i]->energy);
      datMat.push_back(row);
   }
   /** newClusters[i][j][k]
   *   i represents the cluster number
   *   j represents a particular conformation
   *   k represents the actual angle rotation values for each rotable bond
   */
   vector< vector< vector<float> > > newClusters;
   //////////cout <<"Before heir "<< numOfClusters << endl; 
   cluster c;
   c.hierarchal(datMat, props, newClusters, numOfClusters);
   best.resize(newClusters.size());
   for (unsigned int i=0; i<newClusters.size(); i++) {
      best[i] = new confNode;
      best[i]->angles = newClusters[i][0];
   }
}

void Conformation::rotMolecule(molecule *mol, float x, float y, float z, float angle) {
   vector<float> axis(3);
   axis[0] = x; axis[1] = y; axis[2] = z;
   vector<float> quat(4), rotMat(16);//, torque(3);
   angle = angle*3.14159265*.005555555;
   axis_to_quat(axis, angle, quat);
   quatToMatrix(rotMat, quat);
   rotMolecule(mol, rotMat);

}

void Conformation::rotMolecule(molecule *mol, vector<float> &fM) {
   //First thing we do is get molecule center
   float center[3];
   center[0] = center[1] = center[2] = 0;
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      float *cd = mol->atoms[i]->fCoords;

      center[0] += cd[0];//*mass;
      center[1] += cd[1];//*mass;
      center[2] += cd[2];//*mass;
   }

   int numOfAtoms =  mol->atoms.size();
   center[0] /= numOfAtoms;
   center[1] /= numOfAtoms;
   center[2] /= numOfAtoms;

   //Next thing we do is translate the molecule to the center

    float tmpcoords3[3];
    for (unsigned int i = 0; i<mol->atoms.size(); i++)  {
      atom *tba = mol->atoms[i];
      //Translate the atom
      float *cd = tba->fCoords;

      //Perform rotation by multiplying atomic coords with rotation matrix.
      //This section can certainly be improved performance wise
      tmpcoords3[0] = cd[0]-center[0];
      tmpcoords3[1] = cd[1]-center[1];
      tmpcoords3[2] = cd[2]-center[2];

      cd[0] = (tmpcoords3[0]*fM[0] + tmpcoords3[1]*fM[4] + tmpcoords3[2]*fM[8] + fM[12]) + center[0];
      cd[1] = (tmpcoords3[0]*fM[1] + tmpcoords3[1]*fM[5] + tmpcoords3[2]*fM[9] + fM[13]) + center[1];
      cd[2] = (tmpcoords3[0]*fM[2] + tmpcoords3[1]*fM[6] + tmpcoords3[2]*fM[10] + fM[14]) + center[2];

     }
}

};//END NAMESPACE




























