/***************************************************************************
                          atomtyper.h  -  description
                             -------------------
    begin                : Wed Dec 3 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ************************************************************/



#ifndef ATOMTYPER_H
#define ATOMTYPER_H

 #include <iostream>
 #include <vector>
 #include <stack>
 #include <bitset>
 #include "energy.h"
 #include "forcefield.h"
 #include "string"

using namespace std;

class molecule;
class atom;
class bond;
class energy;

const int maxRingBits = 5000;
/**
  *@author John Furr
  */

class atomTyper {
public:
  atomTyper();
  ~atomTyper();

  void assignAromaticity_AM1_BCC(molecule *mol, vector< vector<atom *> > &rings);
  void findAllRings2(molecule *mol, vector< vector<atom *> > &rings, int maxRingSize);  
  bool aParent(atom *tmp, atom *top);
  
  /** this is used to set aromaticity based on huckels rules */
  void setAromatic(molecule *mol, vector< vector<atom *> > &rings);
  /** this function is responsible for setting the formal charges */
  void setFormalCharges(molecule *mol);
  

  bool isAmine_N(atom *atm);
  bool isAmide_N(atom *atm);
  bool isNitro_N(atom *atm);
  bool isNitro_O(atom *atm);
  bool isEster_O(atom *atm);
  bool isCarboxyilicAcid_C(atom *atm);
  bool isCarboxyilicAcid_O(atom *atm);
  bool isLactoneCarbonylOxygen(atom *atm);
  bool isLactamCarbonylOxygen(atom *atm);
  
  /** This return the number of heavy atoms connected to the atom */
  int  heavyAtoms(atom *atm);

  bool isDelocalized(bond *bd);

  string atomicNumToString(int num);

  void type_mol2(molecule *mol);
  int getTotalBondOrder(atom *atm, molecule *mol);
   
  /** This function converts from gaff types to mol2 types */
  void gaff2Mol2(molecule *mol);
  
  forceField *ff;
  
  /** This function returns the chirality of the selected atom
  *   R/S/N  N is for None
  */
  string chirality(atom *atm);
  /** this function us called by chirality...it sums up the atomic
  *   nubers of the atoms attached to "atm"
  */
  int assignPriority(atom *atm);
  
  void checkPriority(vector<int> &priority, vector<int> &sameIndex);
private:
  int piElectronCount(molecule *mol, vector<atom *> ring);
  int getTotalBondOrder(molecule *mol, atom *atm);
};

#endif





































