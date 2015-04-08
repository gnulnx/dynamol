/***************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   email:  john.furr@dynamol.com 
 ***************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>

#include <boost/shared_ptr.hpp>
using namespace std;

int main(int argc, char *argv[])
{

  #ifdef WINDOWS
     cout <<"Dynabase WINDOWS build"<<endl;
  #else
     cout <<"Dynamol LINUX build"<<endl;
     cout <<"To build for Windows pass:  define=WINDOWS"<<endl;
     cout <<"on bjam command line"<<endl;
  #endif
 
  boost::shared_ptr<int> a; 
  return EXIT_SUCCESS;
}
