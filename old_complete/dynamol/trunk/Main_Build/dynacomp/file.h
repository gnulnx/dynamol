/****************************************
 *   Copyright (C) 2004 by Dynamol Inc. *
 *   john.furr@dynamol.com              *
 ****************************************/
#ifndef DYNACOMPFILE_H
#define DYNACOMPFILE_H

//Standard Library Includes
#include <string>
using std::string;

namespace dynacomp {

class molecule;
/**
@author john furr
*/
class file{
public:
   file();

   ~file();

   /** \brief Save the molecule to an SD File
   *   
   *   If append is set to 1 then the molecule 
   *   is appended to the file.  If it is set to
   *   0 then the file is truncated.
   *   The function returns true on success and
   *   false on fail 
   */
   static bool writeSDF(const char *file, molecule *mol, int append);

   static string AN2SYM(int an);
};

}

#endif

