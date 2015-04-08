/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                        
 *   john.furr@dynamol.com                                                 
 ***************************************************************************/
#ifndef DTTOPOLOGICAL_H
#define DTTOPOLOGICAL_H

//Standard Library Includes
#include <vector>
#include <deque>
#include <set>
#include <map>
using std::vector;
using std::deque;
using std::set;
using std::map;


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
/** \brief A base class for topological descriptors
*   
*   This class should be used as a base class for various topological descriptors
*   Such as electrotopological, Walks, Paths, etc...
*/
class Topological{
public:
    Topological();
    //virtual void setMol(molecule *mol);
    virtual void setMol(molPtr mol);
    //molecule *getMol();
    molPtr getMol();
    ~Topological();
    
       
   /** \brief Connectivity Indices
   *
   *   This function takes a path length h as an argument and it calculated the connectivity index
   *   for the current molecule
   */   
   float conV( int depth );

   /** \brief Valence Connectivity Indices
   *
   *   This function takes a path length h as an argument and calculates the valence connectivity index
   *   for the current molecule
   */
   float conVV( int depth );

protected:
    /** \brief This function sets the vertex degree of each atom 
    *
    *   Functions sets up the vDegre vector for each atom in the molecule
    *   Hydrogen atoms are assigned a vDegree of -1.
    */
    void setVDegree();
    
    /** \brief This function sets the valence vertex degree of each atom 
    *
    *    Sets up the vvDegree vector for each atom in the molecule.
    *    Hydrogens are assigned a vvDegree of -1
    */
    void setVVDegree();
    
    /** \brief Returns the number of valence electrons
    *
    *    This function returns the number of valence electrons on the atom
    */
    //int valenceCount(atom *atm);
    int valenceCount(atomPtr atm);
   
    /** \brief Returns the number of bonded hydrogen atoms
    * 
    *    Simply returns a count of the bonded hydrogen atoms
    */
    //int hydrogenCount(atom *atm);
    int hydrogenCount(atomPtr atm);
    
    /** \brief Returns the principle quantum number of the atom
   *
   *   This function simply returns the principle quantum number of the atom
   */
   //int pQN(atom *atm);
   int pQN(atomPtr atm);
   
      
   /**  \brief Vertex Degree of each atom in mol 
   *    This holds the vertex degree of the atom.  The vertex
   *    degree is defined as number of sigma electrons minus the 
   *    number of hydrogens in the atom.  Basically it is a count of
   *    the number of heavy atoms bonded to the the atom.  Hydrogen atoms
   *    will return a vertex degree of 0
   */
   vector<int> vDegree;
   
   /** \brief Valence Vertex Degree of the atom in mol
   *
   *    This holds the Valence Vertex degree of the atom.
   *    The Valence Vertex Degree is defined as
   *    <pre>
   *    vvd = (Zv - H) / (Z - Zv - 1)
   *     
   *     Z  = Atomic Number
   *     Zv = Number of valence electrons
   *     H  = Number of hydrogens
   *     </pre>
   */
   vector<float> vvDegree;

   /** This varialbe holds the current molecule */
   //molecule *mol;
   molPtr mol;
private:
 
   /** \brief used for graph searching during a depth first like search
   *
   */
   //void pathVisit( atom *atm ); 
   void pathVisit( atomPtr atm );

   /** \brief used to check atoms in graph searching
   *
   */
   //bool checkAtom( atom *atm);
   bool checkAtom( atomPtr atm);
 
   /** \brief Data structure that is used to hold all of the Paths
   * 
   *   Paths are built from a depth first search.  You should
   *   set stackMode=true
   */
   //set< set<atom *> > Paths;
   set< set<atomPtr> > Paths;

   /** \brief Data structure to hold all of the clusters
   *
   *   Clusters are built from a breadth first seatch You should
   *   set stackMode=false;
   */
   //set< set<atom *> > Clusters;
   set< set<atomPtr> > Clusters;
public:
   /** \brief This function builds the atomPaths variable
   * 
   *    This function enumerates all the atoms Paths in the molecule of
   *    Length h
   */
   void buildPaths(int depth);
private:
   /** \brief holds the current atom in the topological search */
   //atom *currAtom;
   atomPtr currAtom;

   /** \brief the previously visited atom */
   //atom *prevAtom;
   atomPtr prevAtom;

   /** \brief deque for depth first and breadth first
   *
   *    This data structure is used for both depth first and breadth first
   *    When using depth first you push_front() and pop_front()
   *    When using breadth first you push_back() and pop_front()
   *    Also set stackMode=true for depth first and stackMode=false
   *    for breadth first
   */
   //deque<atom *> DEQUE;
   deque<atomPtr> DEQUE;

   /** \brief the max search depth
   */
   int maxDepth;

   /** \brief Used to specify stack mode
   *  
   *    When stackMode is set to true a depth first search is performed
   *    When it is set to false a bredth first search is assumed 
   */
   bool stackMode;
 
   /** \brief Use the H depleted graph 
   *
   *    When set to true all searches will ignore H atoms
   */
   bool hSupressMode;
};

}; //end namespace dt
#endif






