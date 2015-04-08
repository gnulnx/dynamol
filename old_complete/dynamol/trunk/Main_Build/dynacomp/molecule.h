/*****************************************
 *   Copyright (C) 2004 by Dynamol Inc.  *
 *   john.furr@dynamol.com               *
 *****************************************/

#ifndef DYNACOMPMOLECULE_H
#define DYNACOMPMOLECULE_H

#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;

//DELETE THESE
#include <iostream>
using namespace std;

//BOOST INCLUDES
#include <boost/shared_ptr.hpp>

namespace dynabase {
   class atom ;
}

/**
@author jfurr
*/

namespace dynacomp {

class atom;
class bond;
class angle;
class torsion;
class nonBond;

typedef boost::shared_ptr<atom> atomPtr;
typedef boost::shared_ptr<bond> bondPtr;
typedef boost::shared_ptr<angle> anglePtr;
typedef boost::shared_ptr<torsion> torPtr;
typedef boost::shared_ptr<nonBond> nbPtr;

class molecule {
public:
   molecule();

   static int molCount;
   ~molecule();

   /** \brief Add a new atom
   *
   *  Use this function to add a new atom to the molecule
   */
   atom *addAtom(int num, string xym, float x, float y, float z, int atomicNum);

   /** \brief Add a new atom from a base atom
   *
   *  Use this class when you are adapting from one class to anoter
   */
   //atom *addAtom(dynabase::atom  *atm);
   atom *addAtom( boost::shared_ptr< dynabase::atom > basePtr);

   /** \brief Add a new bond
   *
   *  Use this function to add a new bond to the molecule
   */
   bond *addBond(int num, int from, int to, int order);

   /** \brief Check to see if atom form a bond
   *
   *  This function returns a pointer to the bond if
   *  atm1 and atm2 are bonded.  It return false otherwise
   */
   bond *getBond(atom *atm1, atom *atm2);

   
   /** This function sets the formal charges on the atoms It 
   *  returns the toral formal charge
   *
   * OK I THINK THAT YOU NEED TO RENAME THIS FUNCTION TO getFormalCharge?????
   */
   int setFormalCharges();

   /** \brief Update the moleculs valence
   *
   *  This function sets formal charges for individual atoms.
   *  <pre>
   *  this function needs a new name
   *  </pre>
   */
   void updateValence();

   /** \brief Returns the molecular weight of the molecule
   *
   *   This function returns the molecular weight of the molecule 
   */
   float molWeight();

   /** \brief The atoms in the molecule 
   *
   *  These are the atoms in the molecule.  You can use random access
   *  with them since they are stored in a vector
   */
   vector<atom *> atoms;

   /** \brief Function to return the number of atoms
   *
   *  Mainly used for the C++/Python extension module
   */
   inline int numAtoms()
   { return atoms.size(); }

   /** \brief Get an atom
   *
   *   This function returns an atom pointer or null if index is out of range
   */
   atom *getAtom(int index);

   /** \brief The bonds in the molecule 
   *
   *  These are the bonds in the molecule.  You can use random access
   *  with them since they are stored in a vector
   */
   vector<bond *> bonds;
   
   /** \brief Function to return the number of bonds
   *
   *   Mainly used for the C++/Python extension module
   */
   inline int numBonds()
   { return bonds.size(); }

   /** \brief Get a Bond
   *
   *   This function returns a bond pointer or null if index is out of range
   */
   bond *getBond(int index);
   
   /** \brief These are the rings in the molecule
   *
   *  You should use the dynatype module to get
   *  the rings. 
   */
   vector< vector<int> > unsortedRings;

   /** \brief The name of the molecule
   *
   *  This variable holds the name of the molecule.
   *  You should access it with setName(string) and
   *  getName()
   */
   string name;

   /** \brief Set the name of the molecule
   *
   *  Use this function to set the name of the molecule
   */
   void setName(string molNam);

   /** \brief Return the name of the molecue
   *
   *  Use this function to return the name of the molecule
   */
   inline string getName()
   { return name; }

   //{ cout <<" You are in getName2"<< endl; return name; }
   /** \brief The charge type that is currently set for this molecule
   *
   * This holds the charge type of the molecule.  
   *
   * This should probably be a private data member.  You could then make it 
   * accessible with protected member functions.  This would make it
   * so only derived classes and friend classes can set the variable.
   *
   * */
   string chargeType;
   
   /** \brief The forcefield type for the moelcule
   *
   * This string holds the forcefield type of the molecule 
   *
   *  I think that you should treat this just like propValue 
   *  is treated above. Private with protected member functions.
   **/
   string ffTypes;

   /** \brief Stores the potential energy components
   *
   *   This is carried over from the integrated method.
   *   You may ultimately need to find some other way.
   *   of telling the viewer about updates.
   */
   vector<float> potEnergy;

   /** \brief A property map
   *
   *   This map is used to store property/value pairs about the 
   *   molecule.  For instance.  venderName -- phone number
   *   These properties are written out to an SDF file
   */
   map<string, string> propMap;

   vector<anglePtr> angles;
   vector<torPtr> torsions;
   vector<nbPtr> nonBonds;

   int setTorsions();
   int setAngles();
   int setNonBonds(float cutoff);
};
}
#endif


