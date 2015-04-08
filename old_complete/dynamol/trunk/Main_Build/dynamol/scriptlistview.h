/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef SCRIPTLISTVIEW_H
#define SCRIPTLISTVIEW_H

#include <qobject.h>
#include "scriptobject.h"
#include <qvariant.h>

class scriptmolecule;
/**DETAIL
@author Dynamol Inc.

This class provides a set of functions for interacting with the listView
*/
class scriptlistview : public scriptObject
{
Q_OBJECT
public:
    scriptlistview(QObject *parent = 0, const char *name = 0);

    ~scriptlistview();

public slots:
   /** \brief Add a molecule to the listView and dispaly in the molView
   *
   *    Typical usage;
   *   <pre>
   *   var molList = file.readMol("tmp.sdf");
   *   for (var i=0; i< molList.size(); i++) {
   *      var mol = molList.getMol();
   *      molList.addMol( mol );
   *   }
   *   </pre>
   */
   void addMol(scriptmolecule *mol);
   
   /** \brief Show specified molecule from listView in molView
    *
    *  This function searches for molecule <i> name </i> and display's it in the
    *  the 3D molView window.  If <i> clear </i> is set to true then the molView
    *  Window is cleared first.  Otherwise the new molecule is added to the window.
    */
   
   void displayMol(QString name, bool clear);
   
   /** \brief Show specified molecule from listView in molView  
  *
    *  This function searches for molecule <i> name </i> and display's it in the
    *  the 3D molView window.  The molView window is cleared when the molecule is 
    *  added.  This is works just like the above funtion when <i> clear </i> is set to true
    */
   void displayMol(QString name);

   /** \brief Return an array of names from the listView
    *
    *   This function returns an array of molecule names from the listView.
    */
   QVariant/*Array*/ getListNames();
public:
};

#endif





































