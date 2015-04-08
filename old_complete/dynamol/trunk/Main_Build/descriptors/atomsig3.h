/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef ATOMSIG3_H
#define ATOMSIG3_H

#include "atomenv.h"
#include <set>
#include <qstring.h>

//BOOST Includes
#include <boost/shared_ptr.hpp>

//Dynatype Forward Declarations
namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;
}

/**
@author John Furr
*/
class atomSig3 : public atomEnv
{
public:
    atomSig3();

    ~atomSig3();

   //virtual void calcDesc(set<QString> &desc, dt::molecule *mol);
   virtual void calcDesc(set<QString> &desc, dt::molPtr mol);
};

#endif



