/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef AM1_BCC_H
#define AM1_BCC_H

#include <vector>

using namespace std;

class molecule;
class atom;
class bond;
/**
@author jfurr
*/
class AM1_BCC{
friend class charge;
public:
    AM1_BCC();

    ~AM1_BCC();
    
    void am1_bcc_Aromaticity(molecule *mol);
protected: //declared protected because atomType assign_AM!_BCCAromaticity needs it.  
  void BCC_ringRuleOne(molecule *mol, vector< vector<atom *> > &ringsSix);
  void BCC_ringRuleTwo(molecule *mol, vector< vector<atom *> > &ringSix);
  void BCC_ringRuleTwoPointFive(molecule *mol, vector< vector<atom *> > &ringsSix);
  void BCC_ringRuleThree(molecule *mol, vector< vector< atom *> > &ringSix);
  void BCC_ringRuleFour(molecule *mol, vector<vector< atom *> > &ringsSeven);
  void BCC_ringRuleFive(molecule *mol, vector< vector< atom*> > &ringsFive);
  void BCC_BondOrderString(molecule *mol);
  void BCC_AtomTypes(molecule *mol);
  bool BCC_getCorrections(molecule *mol);
  void BCC_averageIdenticalTypes(molecule *mol);
  bool xAtomCheck(atom *atm);
  bool yAtomCheck(atom *atm);

  bool isPyrol_N(atom *atm);
};

#endif





































