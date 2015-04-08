/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef DYNACOMPAM1_BCC_H
#define DYNACOMPAM1_BCC_H

#include <vector>
#include <string>
using std::vector;
using std::string;


namespace dynacomp {

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

  //void BCC_ringRuleFive(molecule *mol, vector< vector< atom*> > &ringsFive);
  void BCC_ringRuleFive(molecule *mol, vector< vector< atom*> > &ringsFive, 
                        vector< vector<atom *> > &allRings);
  void BCC_BondOrderString(molecule *mol);
  void BCC_AtomTypes(molecule *mol);
  bool BCC_getCorrections(molecule *mol);
  void BCC_averageIdenticalTypes(molecule *mol);
  bool xAtomCheck(atom *atm);
  bool yAtomCheck(atom *atm);

  //New Stuff
  bool isPyrol_N(atom *atm);
  bool isHighlyDelocalized(atom *atm);

  /** return the number of non hydrogen atoms */
  int heavyAtoms(atom *atm);
  int methylCount(atom *atm);
  /** \brief Arranges bond atoms such that hte forward at is bond->toAtom()
  */
  bool setForward(bond *bd);

   string getErrorMsg();
   string errorMsg;
};

};//END namespace dynacomp
#endif





































