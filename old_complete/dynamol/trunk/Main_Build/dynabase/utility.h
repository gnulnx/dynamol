/***************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   email:  john.furr@dynamol.com 
 ***************************************/
#ifndef DYNABASEUTILITY_H
#define DYNABASEUTILITY_H

//Standard Includes
#include <string>
using std::string;

namespace dynabase {

/** \brief Conert a string to a number
*
*  Use this function to convert a string to a number
*/
double toNum(string sNum);

/** \brief Convert a number to a string
*
*  use this function to convert a number to a string
*/
string setNum(double num);

/** \brief Search for str2 in str1
*
*   This function returns true if str2 is contained
*   in str1.  This function is intended to replace QString.contains()
*/
bool inString(string &str1, string &str2);

}; //END NAME SPACE

#endif

