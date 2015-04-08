/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SCRIPTTRASH_H
#define SCRIPTTRASH_H

#include "scriptobject.h"

/**
@author jfurr
*/
class scripttrash : public scriptObject
{
Q_OBJECT
public:
    scripttrash(QObject *parent = 0, const char *name = 0);

    ~scripttrash();

public slots:
    void free(scriptObject *obj);
};

#endif


