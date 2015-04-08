/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SCRIPTSHOW_H
#define SCRIPTSHOW_H

#include <qobject.h>
#include "scriptobject.h"

using namespace std;

class molView;

/**DETAIL
@author jfurr

Function for displaying atoms in the molView.
*/
class scriptshow : public scriptObject
{
Q_OBJECT
public:
    scriptshow(QObject *parent = 0, const char *name = 0);

    ~scriptshow();
    
public slots:
    /** \brief Display all atoms in the molView
    *
    *  Typical usage:
    *  <pre>
    *  show.all();
    *  </pre>
    */
    void all();  

private:

};

#endif





































