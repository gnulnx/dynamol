/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef CONSTITUTIONAL_H
#define CONSTITUTIONAL_H
#include "desc.h"

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;
}
/**
@author John Furr
*/
class Constitutional : public Desc
{
public:
    Constitutional();

    ~Constitutional();
   //virtual void calcDesc(set<QString> &desc, molecule *mol);
   virtual void calcDesc(set<QString> &desc, dt::molPtr mol);
   
   //void molWeight(molecule *mol);
   void molWeight(dt::molPtr mol);
};

#endif



