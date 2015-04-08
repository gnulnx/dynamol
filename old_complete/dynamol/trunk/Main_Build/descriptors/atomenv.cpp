/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "atomenv.h"

atomEnv::atomEnv()
 : Desc()
{
   gs.readSubSets(110);
}


atomEnv::~atomEnv()
{
}


void atomEnv::calcDesc(set<QString> &desc, dt::molecule *mol) {
}




