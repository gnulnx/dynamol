/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com
 ***************************************************************************/

#ifndef DTMOLECULE_H
#define DTMOLECULE_H

#include <vector>
#include <string>
#include <map>
using std::vector;
using std::string;
using std::map;

//Dynatype Includes
//#include "atom.h"

//Dynamol Base Library Includes
#include "../dynabase/atom.h"
//namespace dynabase {
//   class atom;
//}

//BOOST Includes
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

/**
@author jfurr
*/

namespace dt {

class atom;
typedef boost::shared_ptr<dt::atom> atomPtr;
typedef boost::weak_ptr<dt::atom> atomWPtr;

class bond;
typedef boost::shared_ptr<dt::bond> bondPtr;
typedef boost::weak_ptr<dt::bond> bondWPtr;

class molecule;
typedef boost::shared_ptr<dt::molecule> molPtr;

class molecule {
public:
   molecule();

   ~molecule();

   //vector<atom *> atoms;
   vector<atomPtr> atoms;

   //vector<bond *> bonds;
   vector<bondPtr> bonds;

   atomPtr addAtom(int num, string xym, double x, double y, double z, int atomicNum);
   atomPtr addAtom(dynabase::atomPtr atm);
   //bond *addBond(int num, int from, int to, int order);
   bondPtr addBond(int num, int from, int to, int order);
   //bond *getBond(atom *atm1, atom *atm2);
   //bond *getBond(atomPtr atm1, atomPtr atom2);
   bondPtr getBond(atomPtr atm1, atomPtr atom2);
   

   /** This function adds a new ring to the molecule.  It makes sure that the ring has not been added
   *  ...you should send it a sorted list....  It returns true if the ring was new and added or false otherwise.
   * ********************************************************************************
   *  Actually I now think that you should probably use a set<int>  Makes much more sense
   ***********************************************************************************
   */
   bool addRing(vector<int> &R);
   
   vector< vector<int> > sortedRings;
   vector< vector<int> > unsortedRings;

   void setName(string name);
   string name;
   
   /** \brief A map of property value pairs 
    *   
    *   This map holds property value pairs.  Usage is like:
    *   <pre>
    *   propMap[name] = value
    *   <\pre>
    *
    *   Both arguments should be strings.  You can determine what the type is by using
    *   propTypeMap
    */
    map<string, string> propMap;

    /** \brief Stores the value type for propMap
     *
     * This map stores i/f/d/s for integer, float, double, or string
     */
    map<string, string> propTypeMap;
   
   /** This will hold property names from sd and sdfx files 
    * 
    * DEPRICATED
   */
   vector<string> propertyNames;
   /** This wil hold the property type [i/f/s] from sdfx files
    *
    * DEPRICATED
   */
   vector<string> propType;
   
   /** This holds the property value.  Currently it just holds it as a strin because 
    * for the purpose of atom typeing you only need to carry the property straight though
    *
    *  DEPRICATED
    */
   vector<string> propValue; 
   
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
    *  I think that you should treat this just like propValue is treated above.  
    *  Private with protected member functions.
    **/
   string ffType;
   
   /** \brief Returns the molecular weight of the molecule
   *
   *   This function returns the molecular weight of the molecule 
   */
   float molWeight();
};
}
#endif


