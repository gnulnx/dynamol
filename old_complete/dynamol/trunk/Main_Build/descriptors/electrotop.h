/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef ELECTROTOP_H
#define ELECTROTOP_H

//#include <desc.h>
#include "topo.h"
#include <set>
#include <map>
using std::set;
using std::map;

//QT Includes
#include <qstring.h>

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;
}

/**
@author John Furr
*/

class ElectroTop : public Topo
{
public:
    ElectroTop();

    ~ElectroTop();

    //void calcDesc(set<QString> &desc, dt::molecule *mol);
    void calcDesc(set<QString> &desc, dt::molPtr mol);
    
    /** This function is used to prep th eeState stuff */
    //void setGaffEStateSum(dt::molecule *mol);
    void setGaffEStateSum(dt::molPtr mol);
    
    /** \brief Returns the EState values for the basic GAFF types
    *
    *   This function returns the electrotopolocigal values for the
    *   basic GAFF atom types.
    */
    QString getGaffEStateSum(QString type);
    
    /** \brief Return a count of the EState types 
    *
    *    This function returns a count of the individual GAFF EState types
    */
    QString getGaffEStateCount(QString type);
    
private:
 /** This map is used in conjunction with setGaffEStateSum() and getGaffEStateSum()
   */
   map<QString, float> gaffEStateMap;
   map<QString, int> gaffEStateCountMap;
};

#endif



