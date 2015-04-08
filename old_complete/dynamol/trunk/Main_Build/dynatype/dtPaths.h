/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef DTPATHS_H
#define DTPATHS_H

#include <vector>
using std::vector;

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dt {

class molecule;
typedef boost::shared_ptr<dt::molecule> molPtr;

class atom;
typedef boost::shared_ptr<dt::atom> atomPtr;

class bond;
/**
*  class Path is used to enumerate all possible dtPaths from a given atom\n
*  to each of the terminal atoms which are defined in the "term" vector. \n
*  This class finds all dtRings as well as dtPaths of all lengths.  The various\n
*  dtPaths are used in the amber atom typing procedure...as are the dtRings\n
*/
class Paths {
public:
    /** If pathLength == -1 then all dtPaths will be searched. \n 
    *  If however another integer is used then all dtPaths of \n
    *  that length will be found 
    */
    //Paths(molecule *mol, int pathLength);
    Paths(molPtr mol, int pathLength);
    ~Paths();
private: 
    /** This function finds all the terminal atoms in molecule "mol"\n
    *    and stores them in the internel "term" vector 
    */
    void findTerms();
    
    /** This function checks to see if the atom "currAtom" is a terminal atom.
        It return true if it is...and false if it is not */
    //bool isTerminal(atom *currAtom);
    bool isTerminal(atomPtr currAtom);
    
    /** This function checks to see if the atom "currAtom" is already in the "path" vector.  If it is the function returns true.  Otherwise it returns false */
    //bool isPathRing(atom *currAtom);
    bool isPathRing(atomPtr currAtom);
    
    /** This function scores the path as outlined int he antechamber paper */
    float scorePath();
   
    /** This is a recursive function which enumerates all possible dtPaths for current base atom */
    //void findPaths(atom *currAtom);
    void findPaths(atomPtr currAtom);
  
    /** This is the molecule for which the search is performed over */
    //molecule *mol;
    molPtr mol;
    
    /** This will be the base at the start of each new search.... path[0] */
    //atom *baseAtom;
    atomPtr baseAtom;
    
    /** This will be the stack used in the depth first search for all dtPaths.
        I used a vector becuase it has push_back(), pop_front() and array like index functions....all make my life easier
    */
    //vector<atom *> path;
    vector<atomPtr> path;
    
    /** This vector holds the terminal atoms in the molecule */
    //vector<atom *> term; 
    vector<atomPtr> term;
    
    /** This holds the max length/depth of the path search.  -1 means search full deep
    */
    int maxPath;

};
};
#endif



























