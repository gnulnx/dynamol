/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef SCRIPTMOLVIEW_H
#define SCRIPTMOLVIEW_H

#include <qobject.h>
#include "scriptobject.h"
#include <qvaluevector.h>

class scriptmolecule;
class scriptmollist;
class molView;
class XmodelView;
/**DETAIL
@author Dynamol Inc.

The molView class class provides a functions for interacting with the 3D molView window.
*/
class scriptmolview : public scriptObject
{
Q_OBJECT
public:
   scriptmolview(QObject *parent = 0, const char *name = 0);
   //void setXmodelView(XmodelView *view);
   
   ~scriptmolview();
public slots:
   /** \brief Depreicated.  Use getMols() instead.
   *
   *   This function returns a molList containing a entry for each
   *   molecule currently in the molView window.  
   *
   *   Typical Usage would be:
   *   <pre>
   *   var molList = molView.getCurrent();
   *   for (var i=0; i < molList.size(); i++) {
   *      var mol = molList.getCurrent(i); 
   *      print( mol.getName() );
   *      ...other interesting molecule operations
   *   } 
   *  </pre>
   */
   scriptmollist *getCurrent();
   
   /** \brief Return a list of molecules currently in the molView window 
   *
   *   This function returns a molList containing a entry for each
   *   molecule currently in the molView window.  
   *
   *   Typical Usage would be:
   *   <pre>
   *   var molList = molView.getMols();
   *   for (var i=0; i < molList.size(); i++) {
   *      var mol = molList.getMol(i); 
   *      print( mol.getName() );
   *      ...other interesting molecule operations
   *   } 
   *  </pre>
   */
   scriptmollist *getMols();
   
  // void getMolList(scriptmollist *molList);
      
   /** \brief Draw a sphere at the specified location
   *
   *  This function draws a sphere of size <i> radius </i>
   *  at the location specified by <i> x, y, z </i>
   *
   *  Typical Usage:
   *  <pre>
   *  molView.addSphere(10.0, 10.0, 10.0, 1.0);
   *  <\pre>
   */
   void addSphere(float x, float y, float z, float radius);
   
   /** \brief Clear the spheres in the molView window
    *
    *  Function clears the spheres drawn in the molView window
    */
   void clearSpheres();

public:
   //molView *viewer;
   //XmodelView *view;
};

#endif





































