/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef DESC_H
#define DESC_H

//Standard Library Includes
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
//using namespace dt;

/**
@author John Furr
*/
class Desc{
public:
    Desc();

    virtual ~Desc();
    //virtual void calcDesc(set<QString> &desc, dt::molecule *mol) = 0;
    virtual void calcDesc(set<QString> &desc, dt::molPtr mol) = 0;
    
protected:
   map<QString, set<QString> > descMap;
   set<QString> funcSet;
   map<QString, Desc *> classMap;
};

#endif



