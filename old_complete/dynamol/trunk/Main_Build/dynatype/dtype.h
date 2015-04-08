/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                     
 *   email:  john.furr@dynamol.com
 ***************************************************************************/
#ifndef DTYPE_H
#define DTYPE_H

//Standard Library Includes
#include <string>
#include <vector>
using std::string;
using std::vector;

//BOOST Includes
#include <boost/shared_ptr.hpp>

/** The Dynamol Atom Type Library ( dynatype )
*
*   Currenly the dynatype library is used as way to reduce the amount of
*   code in the main Dynamol code base.  However in the ver near future 
*   this library will be host to all of the atom typing routines.  Right now
*   it is primarily responsible for setting the General Amber and Amber 2003
*   atom types.  It incorporates the functionality of the Amber antechamber
*   program.
*/
namespace dt {
	
class molecule;
typedef boost::shared_ptr<dt::molecule> molPtr;

/** /brief A wrapper for many basic library functions.
*
*  class dType provides easy access to some of the dynatype classes.
*/
class dType {
public:
    dType();

    ~dType();

    /** This function is used to read an sdfx file.  It returns a *molecule 
     */
    //static molecule *readSDFX(string fileName);
    static molPtr readSDFX(string fileName);
    
    /** This function is used to write an sdfx file from a *molecule */
    //void writeSDFX(string fileName, molecule *mol, int append);
    void writeSDFX(string fileName, molPtr mol, int append);
    
    /** Call this function to set all the atom types according to the gaff force feild */    
    //void setGaffTypes(molecule *mol);
    void setGaffTypes(molPtr mol);

    /** \brief Return the matrix of equivalent atoms
    *
    *    This function is used to set a matrix of equivalent atoms
    */
    //void getEquivalents(molecule *mol, vector< vector< int > > &equivs, int pathLength=-1);
    void getEquivalents(molPtr mol, vector< vector< int > > &equivs, int pathLength=-1);

    /** Call this function to set the atom types to the Amber 2003 force field */
    //static void setAmber03Types(molecule *mol);
    static void setAmber03Types(molPtr mol);
 
    /** Call this function to set the maximum depth
    *   when enumerating all possible paths.  The default value is -1 
    *   which means there is no limit
    */
    void setPathLength(int pLength);
    
    /** This function will return the number of aromatic rings in
    *   the molecule
    */
    //int aromaticRingCount(molecule *mol);
    int aromaticRingCount(molPtr mol);

private: 
   int pathLength;

};
};
#endif









