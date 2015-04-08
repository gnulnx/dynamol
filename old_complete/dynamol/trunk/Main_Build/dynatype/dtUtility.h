/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef DTUTILITY_H
#define DTUTILITY_H
 /** This function is respible for reading and processing new command line arguments.
     If it encounters a function that it does not know it will return false.
     Thus all new arguments must be added to this function 
*/

//Standard Library Includes
#include <vector>
#include <string>
using std::vector;
using std::string;

namespace dt {
	
   bool readCommandLineArgs(int argc, char *argv[], vector<string> &str);

   /** \brief Num to string conversion
   *
   *    This function converts a number to a string
   */
   string setNum(double num);

   /** \brief String to num conversio
   *
   *    This function converts a string to a number
   */
   double toNum(string str);
}

#endif























