/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         
 *   john.furr@dynamol.com                                                
 ***************************************************************************/
#ifndef DTELECTROTOPOLOGICAL_H
#define DTELECTROTOPOLOGICAL_H

#include "topological.h"
#include <deque>
#include <set>
#include <map>
using namespace std;

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
class electroTopological : public Topological
{
public:
    /** \brief calculate the EStates for each atom.
    *   The eStates vector will be copied to ES which can then
    *   Be used for further processing...such as summing the SEtates
    *   for given atom types. The ES vector will be order by atoms
    *   in the molecule.  ES[0] = mol->atoms[0];
    */
    electroTopological();

    ~electroTopological();
    
    /** Used to set the mol */
    //void setMol(molecule *mol, vector<float> &ES);
    void setMol(molPtr mol, vector<float> &ES);
protected:
   /** \brief Sets the intrinsic state of each atom in mol
   *
   *   This function fills the I vector with the correct I states
   */
   void setIState();
   
   /** \brief calculates the E-State values for each atom
   *
   *   This function calculated the full E-State value for each 
   *   atom in the molecule
   */
   void setEState();
    
private:
    /** \brief calculates the EState between the currAtom and atm
    */
    //void calcEState(atom *atm);
    void calcEState(atomPtr atm);

    /** \brief  This function is used perform the breadth first search
    *
    *   Called until the searchQueu is emppty
    */
    //void visit(atom *atm);
    void visit(atomPtr atm);
   
    /** \brief This function checks for search termination criteria
    *
    *   This function is called from within visit before new atoms
    *   are added to the end of the queu.  
    */
    //bool checkAtom(atom *atm);
    bool checkAtom(atomPtr atm);
 
    /** \brief Holds the intrinsic state for each atom
    *
    *  The intrinsic state is defined as:
    *   <pre>
    *   I = ( (2/L)^2 * vvD +1) / (d + 1 )^k
    *   </pre>
    */
   //map<atom *, float> iMap;
   map<atomPtr, float> iMap;
   
   /** \brief Holds the E-State values for each atom
   *
   *   You can then determine the most suitable way to sum these
   *   For instance using the GAFF types
   */
   vector<float> eStates;

   /** \brief a queu for depth first searching
   *
   *    This variable provides a search Queu for depth first 
   *    searching
   */
   //deque<atom *> searchQueu;
   deque<atomPtr> searchQueu;

   /** \brief A map to hold the search depth for each atom
   *
   *   This variable maps an atom to a search depth.
   *   It should be cleared and reset after each search
   */
   //map<atom *, int> searchDepth;
   map<atomPtr, int> searchDepth;

   /** \brief The set of visited atoms
   *
   *   I use a set to hold the atoms visited in the current 
   *   search.
   */
   //set<atom *> visitedAtoms;
   set<atomPtr> visitedAtoms;

   /** \brief The current atom which is being search over
   */
//   atom *currAtom;
   atomPtr currAtom;
 
   /** \brief The current EState value
   *
   *   This holds the current EState value for the currAtom
   */
   float currEState;
   
};

}; //end namespace dt
#endif






