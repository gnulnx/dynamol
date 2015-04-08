/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef DTRINGS_H
#define DTRINGS_H

//Standard Library Includes
#include <vector>
using std::vector;

//BOOST Includes
#include <boost/shared_ptr.hpp>


namespace dt {
/**
@author jfurr
*/
class molecule;
typedef boost::shared_ptr<dt::molecule> molPtr;

class atom;
typedef boost::shared_ptr<dt::atom> atomPtr;

class bond;


class Rings{
public:
   //Rings(molecule *mol);
   Rings(molPtr mol);
   Rings();

   ~Rings();
   
   /** This is responsible for setting the various ring type
     RG1-RG9
     NR
   */
   void setRingTypes();
   
   /** This sorts the ring vectors by size...smallest  ring to largest */
   void sortRingSizes();
   
   /** This vector sets the relative aromticity level 
     AR1- AR5
     AR1 is fully aromatic and AR5 is not aromatic at all
     
     ########## HOW YOU CURRENTLY DEFINE IT ################3
     to have a type of AR5 all atoms must be sp3 carbons
     To be AR1 all atoms must be either C3, N3, O2
   */
   void setAromaticity();
   
   /** This function returns true if the atom is an aliphatic atom */
   //bool isAliphatic(atom *atm);
   bool isAliphatic(atomPtr atm);
   
   /** This function returns true if the atom is planar..by definition
   Planar is only:
   C(X3), N(X2), N(X3), O(X2), S(X2), P(X2), P(X3).
   
   where X2 and X3 mean two and three bonded atoms respectively.
   ****Note this notation assums that all hydrogens have been added 
   */
   //bool isPlanar(atom *atm);
   bool isPlanar(atomPtr atm);
   
   /** This function types a dtRings atoms as aliphatic (AR5) if the ring
       was determined to be aliphatic
   */
   void typeAliphatic(vector<int> &ring);
   
   /** This function types the dtRings atoms as AR1-AR3
   */
   void typePlanar(vector<int> &ring);
   
   /** This function types the dtRings atoms as other AR4 */
   void typeOther(vector<int> &ring);
   
   /** This function return true if the atom is a pure aromatic type
     pure aromatic is C3 or N2  think benzene or pyridine
     
     You may eventually want to rethink this so that it takes into account
     the total bond order as such.
   */
   //bool isPure(atom *atm);
   bool isPure(atomPtr atm);
   
   /** This function returns true if the ring has outside double bonds.  False other wise
   */
   //bool hasOutside(atom *atm);
   bool hasOutside(atomPtr atm);
   
   /** This function is used to assign all the various bond types
   SB         Single Bond
      DB         Double Bond
      TB         Triple bond
      AB         Aromatic Bond
      DL         delocalized bond ( 9 in AM1-BCC)
      sb         single bond, including aromatic single, delocalize singbond (9 in AM1-BCC)
      db         Double Bond, including aromatic double bond
      tb         Trible bond
   
      This should probably not be in this class to bad.  It is here now!  Need to get some sleep....ah grasshopper...you need sleep!
   */
   void setBondType();
   
   /** This return true if both atoms have AR1-AR3 */
   bool isAromaticBond(bond *bd);
   
   //bool isDelocalized(atom *atm);
   
   //int piElectronCount(dt::molecule *mol, vector<int> ring);
   int piElectronCount(molPtr mol, vector<int> ring);   

   //int getTotalBondOrder(dt::molecule *mol, atom *atm); 
   //int getTotalBondOrder(dt::molecule *mol, atomPtr atm);
   int getTotalBondOrder(molPtr mol, atomPtr atm);

   //int aromaticRingCount(molecule *mol);
   int aromaticRingCount(molPtr mol);
   
   //molecule *mol;
   molPtr mol;

};

};
#endif



























