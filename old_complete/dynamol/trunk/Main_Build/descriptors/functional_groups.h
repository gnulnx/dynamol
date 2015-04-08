/***************************************************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef FUNCTIONAL_GROUPS_H
#define FUNCTIONAL_GROUPS_H

#include "desc.h"

//QT Includes
#include <qstring.h>

//Standard Library Includes
#include <string>
using std::string;

//BOOST Includes
#include <boost/shared_ptr.hpp>



//Dynatype forward declarations
namespace dt {
   class molecule;
   typedef boost::shared_ptr<dt::molecule> molPtr;
}
/**
@author John Furr
*/

class Functional_Groups : public Desc
{
public:
   Functional_Groups();

   ~Functional_Groups();
   //virtual void calcDesc(set<QString> &desc, dt::molecule *mol);
   virtual void calcDesc(set<QString> &desc, dt::molPtr mol);
   
   //QString countType(string type, dt::molecule *mol);
   QString countType(string type, dt::molPtr mol);
};

#endif



