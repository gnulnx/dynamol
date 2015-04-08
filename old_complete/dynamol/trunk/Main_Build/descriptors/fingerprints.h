/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef FINGERPRINTS_H
#define FINGERPRINTS_H

#include "desc.h"
#include "../dynaprint/gaffsig.h"

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;
}
/**
@author John Furr
*/
class FingerPrints : public Desc
{
public:
   FingerPrints();

   ~FingerPrints();
   //virtual void calcDesc(set<QString> &desc, dt::molecule *mol);
   virtual void calcDesc(set<QString> &desc, dt::molPtr mol);

private:
   fp::gaffSig gs;
};

#endif



