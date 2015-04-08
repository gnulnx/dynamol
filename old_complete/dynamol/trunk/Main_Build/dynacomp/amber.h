/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                          *
 ***************************************************************************/
#ifndef DYNACOMPAMBER_H
#define DYNACOMPAMBER_H

#include <vector>
#include <map>
#include <string>
using std::map;
using std::vector;
using std::string;

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dynacomp {
class molecule;
class atom;
class bond;
class angle;
class torsion;
class nonBond;

typedef boost::shared_ptr<molecule> molPtr;
typedef boost::shared_ptr<atom> atomPtr;
typedef boost::shared_ptr<bond> bondPtr;
typedef boost::shared_ptr<angle> anglePtr;
typedef boost::shared_ptr<torsion> torPtr;
typedef boost::shared_ptr<nonBond> nbPtr;


struct torDef {
   vector<float> IDIV;
   vector<float> PK;
   vector<float> PHASE;
   vector<float> PERIOD;

   bool improper;
};

/**
@author jfurr
*/
class amber{
public:
    amber();
    
    ~amber();
    
/** This sets the general amber forcefield types...if onlyType is true then it only does basic atom types
     && it doesn't set bonds && angles && all the jive 
  */
  bool setGAFFTypes(bool onlyType, molecule *mol);
  
  
  int getTotalBondOrder(atom *atm, molecule *mol);
  bool amideNitrogen(atom *atm, molecule *mol);
  bool nitroNitrogen(atom *atm, molecule *mol);
  
  bool setBonds(vector<bond *> &Bonds, int &badIndex);
  bool setAngles(vector<anglePtr> &Angles, int &badIndex);
  bool setNonBonds(molecule *mol, int &badIndex);
  bool setTorsions(vector<torPtr> &Torsions, int &badIndex);
  
  bool empricalAngle(anglePtr ang, string &f, string &m, string &b, vector<string> &angParams);
  bool empiricalBond(bond *bd, vector<string> &bondParams);

    // ERROR MESSAGE
   string getErrorMsg();
private:
   string errorMsg;
  /** This function is called by setBonds to get the correct bond params */
  bool getBondParam(string &f1, string &f2, bond *bd);
  
  /** This function is called by setAngles to get the correct angle parameter */
  bool getAngleParam(string  &fFFType, string &mFFType, string &bFFType, anglePtr ang);
  
  /** This function is called by setTorsions to get the correct torsional parameter */
  bool getTorsionParam(string &f, string &m1, string &m2, string &b, int pos, vector<torPtr> &Torsions);
  /** This function populates the vector with the next best atom types for the given type */
  void possTypes(string &type, vector<string> &others);
  
  /**This function reads the gaff.dat parameter file and stores the results */
  bool readParamFile();
  string Path;
  
  /** These are all used in the determination of an angle type */
  vector<string> bdParams, angParams, torParams, nonBondParams;
  vector<string> a1Vec, a2Vec, a3Vec;
  vector<float> KVec, degVec;


  /** \brief knew torsion stuff */
   map<string, torDef> TOR_DEF;
   map<string, torDef> TOR_IMP;

};

};//End Namespace
#endif





