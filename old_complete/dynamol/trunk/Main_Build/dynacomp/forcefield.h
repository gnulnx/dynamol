/***************************************************************************
                          forcefield.h  -  description
                             -------------------
    begin                : Sun Feb 22 2004
    copyright            : (C) 2004 by John Furr
    email                : john.furr@dynamol.com 
 ***************************************************************************/

#ifndef DYNACOMPFORCEFIELD_H
#define DYNACOMPFORCEFIELD_H

#include <vector>
#include <string>
using std::vector;
using std::string;

namespace dt {
   class molecule;
}

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

class gaff;
class amber;

class forceField {
public: 
  forceField();
  ~forceField(); 
  
  
  /** This function is used to type the atoms  It returns false if the 
  *    atom type procedure fails and true otherwise
  */
  bool setAtomTypes(molecule *mol, string &type);
  
  /** This function is used to add charges to the atoms.
  *   It returns true if charges were set and false otherwise
  */
  bool setCharges(molecule *mol, string &type);
  
  /** This function is responsible for ensuring that the angles, torsions, && 
     nonBond lists are constructured && typed */
  bool buildLists(molecule *mol, string &method);
  
  /** These are generic routines....each one will call the appropriate class...GAFF || amber */  
  bool setBonds(vector<bond *> &Bonds, string &method, int &badIndex);
  bool setAngles(vector<anglePtr> &Angles, string &method, int &badIndex);
  bool setNonBonds(molecule *mol, string &method, int &badIndex);
  bool setTorsions(vector<torPtr> &Torsions, string &method, int &badIndex);
 
   /** \brief Return the error message */
   string getErrorMsg(); 
  private:
   string errorMsg;

  gaff *gaffTyper;
  amber *amberTyper;
     
};
};//End Namespace
#endif





