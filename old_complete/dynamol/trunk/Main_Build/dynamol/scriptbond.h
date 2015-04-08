/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef SCRIPTBOND_H
#define SCRIPTBOND_H

#include <qobject.h>
#include "scriptobject.h"

class bond;
class scriptatom;

/**
@author jfurr
*/
class scriptbond : public scriptObject
{
Q_OBJECT
public:
    scriptbond(QObject *parent = 0, const char *name = 0);

    ~scriptbond();
    
    void setBond(bond *);
    void setAtoms(scriptatom *from, scriptatom *to); 
    bond *getBond();
  
public slots:
   /** \brief Returns the order of the bond
   *  
   *   This function returns the bond order (1, 2, or 3)
   */
   int order();  
   
   /** \brief Returns the length of the bond
   *
   *    This function returns the length of the bond in angstroms
   */
   double length();
   
   /** \brief Returns the from atom
   *
   *   This function returns the <i>from</i> atom in the bond
   *   <i> from </i>is merely a convention.  We consider the bond to have both <i>from</i> 
   *  and <i>to</i>  atoms.  The complement function getTo() returns the other atom in the bond 
   */
   scriptatom *fromAtom();
   
   /** \brief Returns the to atom
   *
   *   This function returns the <i>to </i> atom in the bond
   *   From is merely a convention.  We consider the bond to have both <i>from</i> 
   *  and <i>to</i>  atoms.  The complement function getFrom() returns the other atom in the bond 
   */
   scriptatom *toAtom();
   
private:
   bond *bd;
   scriptatom *from;
   scriptatom *to;
};

#endif





































