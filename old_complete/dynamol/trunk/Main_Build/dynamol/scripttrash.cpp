/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "scripttrash.h"
#include <iostream>
using namespace std;
scripttrash::scripttrash(QObject *parent, const char *name)
 : scriptObject(parent, name)
{
}


scripttrash::~scripttrash()
{
}

void scripttrash::free(scriptObject *obj) {
   delete obj;
}


