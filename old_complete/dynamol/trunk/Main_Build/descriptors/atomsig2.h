/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef ATOMSIG2_H
#define ATOMSIG2_H

#include "atomenv.h"

//Standard Library Includes
#include <set>
using std::set;

//QT Includes
#include <qstring.h>

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;
}

/**
@author John Furr
*/
class atomSig2 : public atomEnv
{
public:
    atomSig2();

    ~atomSig2();

    virtual void calcDesc(set<QString> &desc, dt::molPtr mol);
};

#endif



