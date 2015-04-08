/***************************************************************************
                          forcefield.h  -  description
                             -------------------
    begin                : Sun Feb 22 2004
    copyright            : (C) 2004 by John Furr
    email                : john.furr@dynamol.com 
 ***************************************************************************/

#ifndef FORCEFIELD_H
#define FORCEFIELD_H

#include <vector>
#include <string>

using namespace std;

class molecule;
class nonBond;
class angle;
class torsion;
class bond;
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
  bool setAngles(vector<angle *> &Angles, string &method, int &badIndex);
  bool setNonBonds(molecule *mol, string &method, int &badIndex);
  bool setTorsions(vector<torsion *> &Torsions, string &method, int &badIndex);
  
  private:
  gaff *gaffTyper;
  amber *amberTyper;
     
};

#endif





































