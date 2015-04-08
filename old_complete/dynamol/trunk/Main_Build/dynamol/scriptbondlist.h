/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef SCRIPTBONDLIST_H
#define SCRIPTBONDLIST_H

#include "scriptobject.h"
#include <deque>

class scriptbond;

using namespace std;
/**
@author jfurr
*/
class scriptbondlist : public scriptObject
{
Q_OBJECT
public:
    scriptbondlist(QObject *parent = 0, const char *name = 0);

    ~scriptbondlist();
public slots:
    /** This function returns the size of the bond list 
    *   Typical usage includes:
    *   for (var i=0; $i < bondList.size(); $i++) {
    *        bond *bd = bondList.getBond($i);
    *        someUserDefinedBondOperation( bd );
    *   }
    */
    int size();
    
    /** \brief Returns the first bond in the list 
    *
    *   This function returns the first bond in the list 
    */
    scriptbond *front();
    
    /** \brief Returns the last bond in the list 
    *
    *   This function returns the last bond in the list 
    */
    scriptbond *back();
    
    /** \brief Add a bond to the end of the list
    *
    *    This funciton adds a bond to the end of the bondList
    */
    void push_back(scriptbond *);
    
    /** \brief Add a bond to the front of the list
    *
    *    This funciton adds a bond to the front of the bondList
    */
    void push_front( scriptbond * );
    
    /** \brief This function returns and removes the last bond in bondList
    *
    *   Removes and Return the last bond form the list
    */
    scriptbond *pop_back();
    
    /** \brief This function returns and removes the first bond in bondList
    *
    *   Removes and Return the first bond form the list
    */
    scriptbond *pop_front();
    
    /** \brief Returns the bond at the specified index
    *
    *    Return bond at index <i> index> </i>
    */
    scriptbond *getBond(int index);
private:
   deque<scriptbond *> bondList;
};

#endif
























