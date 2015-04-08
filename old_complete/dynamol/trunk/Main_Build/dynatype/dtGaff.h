/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef DTGAFF_H
#define DTGAFF_H

//Standard Library Includes
#include <map>
#include <string>
using std::map;
using std::string;

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dt {
	
class molecule;
typedef boost::shared_ptr<dt::molecule> molPtr;

class atom;
typedef boost::shared_ptr<dt::atom> atomPtr;

class bond;

/** dtGaff is responsible for atom typing using the general amber force field 
*/
class dtGaff{
public:
   dtGaff();
   //dtGaff(molecule *mol);
   dtGaff(molPtr mol);
   
   /** \brief This function builds a complex->basic type converter
   *    
   *    This function constructs a map that can be used to convert a complex
   *    GAFF type ex( cc(cd) ne(nf), etc) to its basic type equivalent.
   *    This function is used with the GAFFFinger prints.  It does not contain
   *    a c type.  It is maped like c->c2.
   *    Use the getBasicTypeMap2() function for the estate values
   */
   static void getBasicTypeMap(map<string, string> &basicMap);
   
   static void getBasicTypeMap2(map<string, string> &basicMap);
   
   
   ~dtGaff();
   //molecule *mol;
   molPtr mol;
   /** This is the first step in typeing carbon...al other steps will come from here
       These will all return true in atom type was found.  False other wise...use this for
       error checkinng
   */
   bool   typeCarbon(atomPtr atm);
   bool   sp3Carbon(atomPtr atm);
   bool   sp2Carbon(atomPtr atm);
   bool   conjugatedRingCheck(atomPtr atm);
   bool   conjugatedChainCheck(atomPtr atm);
   bool   spCarbon(atomPtr atm);
   
   bool typeNitrogen(atomPtr atm);
   bool ringNitrogen(atomPtr atm);
   bool chainNitrogen(atomPtr atm);
      
   bool typeOxygen(atomPtr atm);
   bool typeHydrogen(atomPtr atm);
   
   bool typeSulfer(atomPtr atm);
   
   bool typePhosphorus(atomPtr atm);
   bool ringPhosphorus(atomPtr atm);
   bool chainPhosphorus(atomPtr atm);
   
   /** This function returns true of the atom is an O, S 
   */
   bool isXA(atomPtr atm);
   
   /** This function returns true if the atom is an N, P
   */
   bool isXB(atomPtr atm);
   
   /** This function returns true if the atom is an F, CL, Br, I
   */
   bool isXC(atomPtr atm);
   
   /** This function returns true if the atom is S, P
   */
   bool isXD(atomPtr atm);
   
   /** this returns true if the atom is an elctron withdrawing group
   defined as:   N, O, F, Cl, Br
   */
   bool isEWD(atomPtr atm);
   
   /** This funciton is responsible for fixing the cc-ce and other ring conjugation stuff */
   void fixConjugation();
   
   /** Return true if the atom type is a Group I type */
   bool isGroupI(atomPtr atm);
   
   /** Returns true if the atom type is a Group II type */
   bool isGroupII(atomPtr atm);
   
   /** This function flips an atoms groupf from I to II or vice versa */
   void flipGroup(atomPtr atm1);
   
   //This is for debugging purposes only!
   int i;
   
private:
   /** This is map is used to convert a given GAFF type to one of the basic types 
   *   For instance it converts cc(cd)  c2
   */
   map<string, string> basicMap;
};
};
#endif

