/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                       
     john.furr@dynamol.com
 ***************************************************************************/
#ifndef DTAMBER_03_H
#define DTAMBER_03_H

//Standard Library Includes
#include <vector>
using std::vector;

//BOOST Includes
#include <boost/shared_ptr.hpp>

/** \brief The Dynamol Atom Type Library
*
*   Currently the dynatype library is used as way to reduce the amount of
*   code in the main Dynamol code base.  However in the ver near future
*   this library will be host to all of the atom typing routines.  Right now
*   it is primarily responsible for setting the General Amber and Amber 2003
*   atom types.  It incorporates the functionality of the Amber antechamber
*   program.
*/
namespace dt {

class molecule;
typedef boost::shared_ptr<dt::molecule> molPtr;

class atom;
typedef boost::shared_ptr<dt::atom> atomPtr;

/**
@author jfurr
*/
class AMBER_03{
public:
    //AMBER_03(molecule *mol);
    AMBER_03(molPtr mol);

    ~AMBER_03();

    /** This funciton is used to type pdb atoms with the GAFF forcefield and then
    *    convert them amber 2003 types
    */
    //void type(atom *atm);
    void type(atomPtr atm);
    
    /** This function is used to convert normal atom symbols to PDB codes */
    //void typeH(atom *atm);
    void typeH(atomPtr atm);
    
};
};
#endif






