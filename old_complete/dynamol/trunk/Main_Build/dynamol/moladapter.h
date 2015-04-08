/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef MOLADAPTER_H
#define MOLADAPTER_H


//BOOST Includes
#include <boost/shared_ptr.hpp>

#include <vector>
#include <list>
/**
@author jfurr
*/

class molecule;

//forward declare the name space and the molecule class
namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;
}

//Forward declaration of the dynacomp namespace
namespace dynacomp {
   class molecule;
}


//Now define our molAdapter class
class molAdapter{
public:
    molAdapter();

    ~molAdapter();

   /** \brief  Converts a list<molecule *> to a vector<dynacomp::molecule *>
   */
   static void molList2dynacompList(std::vector<dynacomp::molecule *> &dcList, std::list<molecule *> &molList);

   static void mol2dynacomp(dynacomp::molecule *dcMol, molecule *mol);

   /** This is a simple function that converts a molecule to a molecule */
   //static void mol2molecule(dt::molecule *dmol, molecule *mol);
   static void mol2molecule(dt::molPtr dmol, molecule *mol);
    
   /** This function converts a molecule to a mol */
   //static molecule *molecule2mol(dt::molecule *mol);
   static molecule *molecule2mol(dt::molPtr mol);

   /** This function updates mol with dtmol's properties */
   //static bool update(molecule *&mol, dt::molecule *dtmol);
   static bool update(molecule *&mol, dt::molPtr dtmol);

   static void dynacomp2mol(molecule *mol, dynacomp::molecule *dcMol);
   static void dynacomp2molecule(molecule *mol, dynacomp::molecule *dcMol);

private:
    /** This function is used to convert the special case fragments so that 
    *   you can match the amber force field types...it is just like
    *   the function by the same name in molDB
    */
    static void typeFrag(molecule *frag);
};

#endif












