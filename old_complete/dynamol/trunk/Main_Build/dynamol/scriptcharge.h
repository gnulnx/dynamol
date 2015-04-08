/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *    email:  john.furr@dynamol.com
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SCRIPTCHARGE_H
#define SCRIPTCHARGE_H

#include <qobject.h>
#include "scriptobject.h"
#include "charge.h"


class scriptmolecule;
/**
@author jfurr
*/
//class scriptcharge : public QObject
class scriptcharge : public scriptObject
{
Q_OBJECT
public:
    scriptcharge(QObject *parent = 0, const char *name = 0);

    ~scriptcharge();
public slots:
    void setUp(scriptmolecule *mol, QString type);
private:
    charge Charge;
};

#endif





































