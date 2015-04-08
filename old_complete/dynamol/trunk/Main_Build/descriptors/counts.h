/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef COUNTS_H
#define COUNTS_H

//QT Includes
#include <qobject.h>
#include <qstring.h>

//Standard Library Includes
#include <vector>
#include <set>
using std::vector;
using std::set;

#include "constitutional.h"

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;
}
/**
@author John Furr
*/

using namespace std;


/**
@author John Furr
*/
class Counts : public Constitutional 
{
public:
    Counts();

    ~Counts();
    
    //void calcDesc(set<QString> &desc, dt::molecule *mol);
    void calcDesc(set<QString> &desc, dt::molPtr mol);
    
    /** This function clears the count vectors */
    virtual void clearCounts();
    
    /** This funciton counts the various bonds and stores them in the vector<int>(2) BC;
    */
    //void countBondTypes(dt::molecule *mol);
    void countBondTypes(dt::molPtr mol);
    /** This function counts the various atom types and stores them in the several vectors
    *   vector<int> ANC; --atomicNumber counts
    *   vector<QString> gaffC -- gaff atom type counts
    */
    //void countAtomTypes(dt::molecule *mol);
    void countAtomTypes(dt::molPtr mol);

    //void inputParser(set<QString> &input);

    /** \brief Bond Order Counts
    *
    *   This function counts the the bonds of order "order" in the molecule "
    */
    //QString nBond(dt::molecule *mol, int order);
    QString nBond(dt::molPtr mol, int order);
    
    /** \brief Atom Counts
    *
    *    This function counts the atoms with atomic number "an"
    */
    //QString nAtom(dt::molecule *mol, int an);
    QString nAtom(dt::molPtr mol, int an);
    
private:
    vector<int> BC;
    vector<int> ANC;
    vector<QString> gaffC;
    
    float totalAtomCount;
    float hAtomCount;
    
};

#endif



