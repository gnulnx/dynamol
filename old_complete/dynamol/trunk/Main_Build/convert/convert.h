/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                       
     john.furr@dynamol.com
 ***************************************************************************/
#ifndef DTCONVERT_H
#define DTCONVERT_H

//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dynacomp {
   class molecule;
}

//class molecule;
namespace dt {

class molecule;
typedef boost::shared_ptr<dt::molecule> molPtr;

class atom;
/**
The convert class is used to convert between various molecule types in the Dynamol package

@author jfurr
*/
class convert{
public:
	convert();

	//static void toDynatype(dt::molecule *dtMol, dynacomp::molecule *dcMol);
	static void toDynatype(dt::molPtr dtMol, dynacomp::molecule *dcMol);
   	
	static void toDynacomp(dynacomp::molecule *dcMol, dt::molPtr dtMol);
 
	//static bool update(dynacomp::molecule *dcMol, dt::molecule *dtMol);
	static bool update(dynacomp::molecule *dcMol, dt::molPtr dtMol);
     
      
    ~convert();

};

};

#endif

