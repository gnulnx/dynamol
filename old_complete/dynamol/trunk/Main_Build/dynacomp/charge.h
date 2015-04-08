/********************************************
 *   Copyright (C) 2004 by Dynamol          *
 *   jjohn.furr@dynamol.com                 *
 ********************************************/
#ifndef DYNACOMPCHARGE_H
#define DYNACOMPCHARGE_H

//Standard Library Includes
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace dynacomp {

struct chargeStruct {
   string name;
   vector<string> atoms;
   vector<string> ff_type;
   vector<float>  charge;
};

class molecule;
/**
@author john furr
*/
class charge{
public:
   charge();
   ~charge();
   /** \brief Setup up the charge class
   *
   *  You need to pass the setup funtion a valid dynacomp::molecule
   *  as well as a valid charge type:  AM1, AM1-BCC, MNDO, PM3
   */
   void setUp(molecule *mol, string type);
   
   /** \brief Calculate the charges
   *
   *  Call this function to calculate the charges
   */
   bool run();
   bool run(molecule *mol, string type);

   bool chargeChain2(vector<molecule *> &frags);
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

   /** The general goal here is to use gaff to determine charges for non-standard
   residues
   */
   void nonStandardResidue(molecule *frag);


   bool checkFragment(molecule *frag, chargeStruct *struc);

   /** Returns 0 if not terminal.  ! if c-Terminal and 2 if n-terminal
   *   Parameters are then read from either amber94_nt.in or amber94_ct.in
   */
   int isTerminalFrag(molecule *frag);

   /** \brief Return any error messages
   */
   string getErrorMsg();
private:
   /** \brief Hold any error messages */
   string errorMsg;

   molecule *mol;
   
   /** \brief The Charge Type
   *
   *  This variable holds the charge type
   *  ex.  AM1, AM1-BCC, MNDO, PM3
   */
   string type;

   /** \brief Calculate the MOPAC Charges
   * 
   *  Type options are AM1, MNDO, PM3
   */
   bool mopacCharges(string type, bool optimize);

   /** \brief Calculate the AM1-BCC Charges
   *
   *  This function first calls mopacCharges
   */
   bool AM1_BCC_Charges(bool optimize);

   /** \brief Calculate the amber 2003
   *
   *  charges for proteins
   */
   bool amberChargesNew();

   /** \brief Average the equivalent atom charges
   *
   *   Called after all charge routines to average the 
   *   partial atomic charges on equivalent atoms
   */
   void avgEquivalentCharges(molecule *mol);
};

}

#endif

