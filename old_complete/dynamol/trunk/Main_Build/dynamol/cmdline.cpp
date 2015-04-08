/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "cmdline.h"
#include <iostream>

cmdLine::cmdLine()
{
}


cmdLine::~cmdLine()
{
}


bool cmdLine::getArgs(int argc, char *argv[], vector<QString> &args) {
   vector<string> cLine;
   for (int i=0; i<argc; i++) {
      string tmp = argv[i];
      cLine.push_back(tmp);
   }
   
   QString run = "NO";
   for (int i=0; i<cLine.size(); i++) {
      if (cLine[i] == "-script" && i < cLine.size()) {
         run = cLine[i+1];
      }
   }
   
   
   args.push_back(run); //args[0]

   return true;
}






































