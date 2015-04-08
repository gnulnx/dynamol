/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                           
 *   email:  john.furr@dynamol.com
 ***************************************************************************/
#ifndef FPGAFFSIG_H
#define FPGAFFSIG_H

//Standard Includes
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <string>
using std::vector;
using std::deque;
using std::string;
using std::set;
using std::map;

//BOOST Includes
#include <boost/shared_ptr.hpp>

class QApplication;

namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;

   class atom;
   typedef boost::shared_ptr<dt::atom> atomPtr; 
}
//typedef boost::shared_ptr<dt::atom> 
namespace fp {
/**
@author jfurr
*/

class gaffSig{
public:
    gaffSig();

    ~gaffSig();

    /** \brief Calculates the gaffFP's for an SDFile
    *
    *   Use this funcion for batch procession of gaffFP calculation
    *   The default height is set to 3
    */
    void processFile(string sdFile, string outFile, int height = 3);
   
    /** \brief Fills the bitMap2, and bitMap3 with atom environments 
    *
    *   This function reads data in gaffsig2 and gaffsig3.  It is used 
    *   by the fingerpint module (which is not really a modules yet.
    *   fpdialog.ui.h.
    *   It is also used by the descriptor library where it reads in the
    *   top 100 highest entropies for both height 2 and heigh 3 
    *   environments.  If gaffsig3.txt is not found it throws error code -1
    *   if gaffsig2.txt is not found it throws error code -2.
    */
    void readSubSets(int size);
 
    /** This function is called to run a new molecule */
    //string runMol(dt::molecule *mol, int height, bool single);
    string runMol(dt::molPtr mol, int height, bool single);

    /** \brief used by the Atom Environment Fingerprints
    * 
    *   It maps the fingerpint to an integer.
    *   It throws error code -1 if gaffsig.txt is not found
    */
    void createMap();

    /** This function is called with the height parameter to 
    *   contruct the fingerprints which are stored in the fp 
    *   vectors
    */
    string buildFingerPrint(int height, bool single);
    /** This is the fingerprint vector */
   vector< vector<int> > fp; 
private:
   /** This is the fingerprint to integer map */
   map<string, int> bitMap3, bitMap2;
   
   /** This maps the atom environments fingerprint to it's probability */
   map<int, float> probMap;

   /** This maps the atom environments fingerprint to it's shannon entropy */
   map<int, float> seMap;

   /** This varialbe holds a pointer to the molecule being searched over
   */
   //dt::molecule *mol;
   dt::molPtr mol;

   /** This variable holds a pointer to the previous atom in the tree
   */
   //dt::atom *prev;
   dt::atomPtr prev;

   /** This varialbe holds a pointer to the current atom being used
   *   to build a fingerprint
   */
   //dt::atom *start;
   dt::atomPtr start;

   /** The deque is used to perform the search.  It used instead of a stack */
   //deque<dt::atom *>  atomStack;
   deque<dt::atomPtr> atomStack;

   /** The set hold the current atoms in the atom print */
   //set<dt::atom *> atomSet;
   set<dt::atomPtr> atomSet;

   /** This varialbe holds the max search depth */
   unsigned int maxDepth;

   /** this variable holds the curr depth of the search */
   int currDepth;

   /** This is the recursive function that is called during the fingerprint 
   *   construction
   */
   //void next( dt::atom *atm );
   void next( dt::atomPtr atm );

   /** This function constructs/reinitializes the countMap
   *   It should be called for each new atom print
   */
   void countMapSetup();

   /** This function sets up the basicMap.
   *   The basic map is used in conjunction with the countMap
   *   <pre>
   *   string type = basicMap[type];
   *   countMap[type]++;
   *   </pre>
   */ 
   void basicMapSetup();   

   /** \brief  Make sure the molecule contains valid GAFF types
   *   
   *   This function simply ensures that the molecule only contains valid
   *   gaff types. 
   */
   bool  checkFFTypes();

   /** This map is used to count the number of times a type shows up.
    *  Usage is like  countMap["ca"]++;
   */
   map<string, int> countMap;

   /** This is map is used to convert a given GAFF type to one of the basic types 
   *   For instance it converts cc(cd)  c2
   */
   map<string, string> basicMap; 
};

};
#endif






