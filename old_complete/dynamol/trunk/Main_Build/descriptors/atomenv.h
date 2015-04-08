/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef ATOMENV_H
#define ATOMENV_H

#include "desc.h"
#include <set>
#include <qstring.h>

//Dynatype Forward Declarations
namespace dt {
   class molecule;
}

#include "../dynaprint/gaffsig.h"


/**
@author John Furr
*/
class atomEnv : public Desc
{
public:
   atomEnv();

   ~atomEnv();
   void calcDesc(set<QString> &desc, dt::molecule *mol);

protected:
   fp::gaffSig gs;
};

#endif



