/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef SWITCHBOARD_H
#define SWITCHBOARD_H

//BOOST Includes
#include <boost/shared_ptr.hpp>

//QT Includes
#include <qobject.h>
#include <qstring.h>

//Standard Library Includes
#include <vector>
#include <set>
#include <map>
using std::vector;
using std::set;
using std::map;

#include "desc.h"

namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;

   class dType;
}

/**
@author John Furr
*/
;
using namespace std;

class descSel;
class QListViewItem;
class switchBoard : QObject
{
Q_OBJECT
public slots:
   void dumbSlot();
public:
    switchBoard(QObject *parent = 0, const char *name = 0);

    ~switchBoard();
    
    void selectDesc(set<QString> &descSet, vector<QString> &descVec);

    void descIn(set<QString> &desc);
    //void calcDesc(set<QString> &desc, dt::molecule  *mol);
    void calcDesc(set<QString> &desc, dt::molPtr  mol);
   
    /** This function currently reads the open descriptor dynascript
    *   project.  This will be changed in the immediate future
    */
    void buildDescList(descSel *&dialog);
    
    void buildDescList2(descSel *&dialog);
	void buildAtomEnvLists(QListViewItem *p1, QListViewItem *p2);
    
    /** Used in conjungtion with the descriptor selection part of the list view 
    */
    bool selectedParent(QListViewItem *item);
private:
    map<QString, Desc *> classMap;


};

#endif



