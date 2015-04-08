/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef RINGCOUNTS_H
#define RINGCOUNTS_H

#include "counts.h"

//Standard Library Includes
#include <vector>
using std::vector;

//QT Includes
#include <qstring.h>

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dynatype {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;
}

/**
@author John Furr
*/
//class molecule;
class ringCounts : public Counts 
{
public:
   ringCounts();

   ~ringCounts();
   
   //void calcDesc(set<QString> &desc, molecule *mol);
   void calcDesc(set<QString> &desc, dt::molPtr mol);
   /** This clears the ring count vectors */
   virtual void clearCounts();
   
   /** \brief Stores the count of ring sizes in ringCounts vector
   *
   *    This function counts all of the rings in the molecule up to size
   *    12 and stores them for fast lookup
   */
   //void countRingTypes(molecule *mol);
   void countRingTypes(dt::molPtr mol);
    
   /** \brief Ring Size Counts
   *
   *    This function counts the rings of size {size}
   */
   //QString nRings(molecule *mol, int size);
   QString nRings(dt::molPtr mol, int size);
   
private:
/** Reserve rCounts[0] for the count of aromatic rings */
vector<int> rCounts;
};

#endif



