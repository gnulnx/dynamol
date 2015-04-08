/***************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   email:  john.furr@dynamol.com 
 ***************************************/
#include "utility.h"

//Standard Includes
#include <string>
#include <sstream>
using std::stringstream;
using std::string;

namespace dynabase {

double toNum(string sNum) {
   stringstream s(sNum);
   double num;
   s >> num;
   return num;
};


string setNum(double num) {
   stringstream s;
   s << num;

   string sNum;
   s >> sNum;
   return sNum;
};

bool inString(string &str1, string &str2) {
   if (strstr (str1.c_str(), str2.c_str()))
	return true;
   return false;
}
};//END NAMESPACE

