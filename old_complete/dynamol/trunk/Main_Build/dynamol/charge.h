/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef CHARGE_H
#define CHARGE_H

#include "dynothread.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <list>
#include "am1_bcc.h"

class chain;
class XmodelView;
class molChangeEvent;
class molecule;

struct chargeStruct {
   QString name;
   vector<string> atoms;
   vector<string> ff_type;
   vector<float>  charge;
};


using namespace std;
/**
@author jfurr
*/

//This is the charge thread wrapper class
class charge;
class chargeThread : public dynoThread
{
public:
   chargeThread(XmodelView *view = 0, const char *name = 0);
   ~chargeThread();
   void setUp(molecule *mol, string chargeType);
   virtual void setName(QString name);
   virtual QString getName();
   virtual void run();
   virtual int rtti(); //returns 2
private:
   charge *Charge;
   XmodelView *view;
   QString type;
   molecule *mol;
};

/*
class charge {
public:
   charge();
   ~charge();      
   void mopacMin(string type);
   void setUp(molecule *mol, string chargeType);

protected:
   molecule *mol;
   string type;
}
*/

//This is the real charge class
class charge
{
friend class atomTyper;
friend class chargeThread;
public:
    charge();
    void setUp(molecule *mol, string chargeType);
    bool run();

    ~charge();

    void am1_bcc_Aromaticity(molecule *mol);
    void mopacMin(string type);
    
    
    bool chargeFail();
private:
    bool failBit;
    
protected:
   string type;
   molecule *mol;

   // Returns false if the mopac charge operation fails 
   bool mopacCharges(string type);

   // Return false if the AM1_BCC Charge operation fails 
   bool AM1_BCC_Charges();

   // Returns false if the amberChargeNew fails 
   bool amberChargesNew();

   //This is a shift towards a better way of reading in the data;   
   //void chargeChain2(chain *ch, vector<chargeStruct *> &data);
   void chargeChain2(molecule *frags, vector<chargeStruct *> &data);

   void chargeAlanine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeGlycine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeSerine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeThreonine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeLeucine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeIsoleucine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeValine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeAsparagine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeGlutamine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeArginine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeHistidine(molecule *frag, vector<chargeStruct *> &data);
   void chargeHistidine_Plus2(molecule *frag, vector<chargeStruct *> &data);
   void chargeHistidine_Epsilon2(molecule *frag, vector<chargeStruct *> &data);
   void chargeHistidine_Delta2(molecule *frag, vector<chargeStruct *> &data);
   void chargeTryptophan2(molecule *frag, vector<chargeStruct *> &data);
   void chargePhenylalanine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeTyrosine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeGlutamate(molecule *frag, vector<chargeStruct *> &data);
   void chargeGlutamate_pos(molecule *frag, vector<chargeStruct *> &data);
   void chargeGlutamate_neut(molecule *frag, vector<chargeStruct *> &data);
   void chargeAspartate2(molecule *frag, vector<chargeStruct *> &data);
   void chargeLysine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeProline2(molecule *frag, vector<chargeStruct *> &data);
   void chargeCysteine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeCysteine_normal(molecule *frag, vector<chargeStruct *> &data);
   void chargeCysteine2_disulfide(molecule *frag, vector<chargeStruct *> &data);
   void chargeCysteine2_negative(molecule *frag, vector<chargeStruct *> &data);
   void chargeMethionine2(molecule *frag, vector<chargeStruct *> &data);
   void chargeWater2(molecule *frag, vector<chargeStruct *> &data);

   // The general goal here is to use gaff to determine charges for non-standard
   // residues
   void nonStandardResidue(molecule *frag);
   
   
   bool checkFragment(molecule *frag, chargeStruct *struc);
   
   // Returns 0 if not terminal.  ! if c-Terminal and 2 if n-terminal 
   //   Parameters are then read from either amber94_nt.in or amber94_ct.in
   int isTerminalFrag(molecule *frag);
  
   void avgEquivalentCharges(molecule *mol); 
protected: //declared protected because atomType assign_AM!_BCCAromaticity needs it. 

  AM1_BCC am1_bcc;
  
  bool calledFromThread;
};

#endif





































