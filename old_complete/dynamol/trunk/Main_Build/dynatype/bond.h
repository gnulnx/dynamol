/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   jjohn.furr@dynamol.com                                                *
 *                                                                         * 
 ***************************************************************************/
#ifndef DTBOND_H
#define DTBOND_H

//BOOST Includes
#include <boost/weak_ptr.hpp>

using namespace std;

namespace dt {

class atom;
typedef boost::weak_ptr<dt::atom> atomWPtr;

class molecule;

class bond;
typedef boost::shared_ptr<dt::bond> bondPtr;
typedef boost::weak_ptr<dt::bond> bondWPtr;	

class bond   {	
friend class molecule;
friend class atom;
public:
    bond();
    bond(int num, atomWPtr from, atomWPtr to, int order);

    ~bond();
   atomWPtr from;
   atomWPtr to;
   int num;
   int order;

};

}
#endif



























