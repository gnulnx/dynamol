/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef SCRIPTMOLLIST_H
#define SCRIPTMOLLIST_H

#include <qobject.h>
#include "scriptobject.h"
#include <deque>
#include "scriptmolecule.h"

using namespace std;

class XmodelView;
/** DETAIL
@author Dynamol Inc.

The molList class provides a convient container for storing molecules.  For the 
computer science savay users you will find it to much more like a deque than
a list.  It contains operations for front and back insertion and deletion as well
random acces.
*/
class scriptmollist : public scriptObject
{
Q_OBJECT
public:
    scriptmollist(QObject *parent = 0, const char *name = 0);

    ~scriptmollist();

public slots:
    /** \brief Returns the size of the molList
     *
     *   Typical usage:
     *   <pre>
     *   var molList = molView.getCurrent();
     *   for (var i=0; i < molList.size(); i++) {
     *      var mol = molList.getMol();
     *   }
     *   </pre>
     */
    int size() {return molList.size();}
    
    /** \brief Returns the molecule specified by index <i> i </i>
     *
     *   Typical usage:
     *   <pre>
     *   var molList = molView.getCurrent();
     *   for (var i=0; i < molList.size(); i++) {
     *      var mol = molList.getMol();
     *   }
     *   </pre>
     */
    scriptmolecule *getMol(int index);
    
    /** \brief Pushes a new molecule onto the back of the molList
     *
     *      Add a molecule to the back of the molList
     */
    void push_back(scriptmolecule *mol);
    
    /** \brief Pushes a new molecule onto the front of the molList
     *
     *      Add a molecule to the front of the molList
     */
    void push_front(scriptmolecule *mol);
    
    
    /** \brief Return and removes the last molecule from the molList
     *
     *   Removes and returns the last atom in the molList
     */
    scriptmolecule *pop_back();
    
    /** \brief Return and removes the first molecule from the molList
     *
     *   Returns and removes the first atom in the molList
     */
    scriptmolecule *pop_front();
    
    /** \brief Returns the first molecule in the molList
     *
     *   Returns the first atom in the molList
     */
    scriptmolecule *front();
    
    /** \brief Returns the last molecule in the molList
     *
     *   Returns the last atom in the molList  
     */
    scriptmolecule *back();
    
private:
    deque<scriptmolecule *> molList;    
};

#endif





































