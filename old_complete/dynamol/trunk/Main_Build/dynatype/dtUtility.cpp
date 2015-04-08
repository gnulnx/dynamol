/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "dtUtility.h"
#include <sstream>
using std::stringstream;
namespace dt {
	
 bool readCommandLineArgs(int argc, char *argv[], vector<string> &args) {
 
 string dtCharge = "None";
 string path = "-1";
 string type = "None";
 
 for (int i=0; i<argc; i++) {
   if (argv[i][0] == '-') {
      if (argv[i][1] == 'c') {
        string tmpCharge = argv[i+1];
	if (tmpCharge == "AM1") dtCharge = "AM1";
	else if (tmpCharge == "am1") dtCharge = "AM1";
	else if (tmpCharge == "AM1-BCC") dtCharge = "AM1-BCC";
	else if (tmpCharge == "am1-bcc") dtCharge = "AM1-BCC";
	else if (tmpCharge == "MNDO") dtCharge = "MNDO";
	else if (tmpCharge == "mndo") dtCharge = "MNDO";
	else if (tmpCharge == "PM3") dtCharge = "PM3";
	else if (tmpCharge == "pm3") dtCharge = "PM3";
	else if (tmpCharge == "Current") dtCharge = "None";
	else {
	   return false;
	}
      } 
      
      if (argv[i][1] == 'p') {
         path = argv[i+1];
      }  
      
      if (argv[i][1] == 't') {
         type = argv[i+1];
         if (type == "gaff") type = "GAFF";
         else if (type == "GAFF") type = "GAFF";
         else if (type == "dtAmber_03") type = "AMBER_03";
         else if (type == "AMBER_03") type = "AMBER_03";
	 else if (type == "PATHS_ONLY") type = "PATHS_ONLY";
         else {
            return false;
         }
      }     
         
   }
 }

 args.push_back(dtCharge); //0
 args.push_back(path);   //1
 args.push_back(type);   //2
 return true;
 }

string setNum(double num) {
   stringstream s;
   s << num;
   string out;
   s >> out;
   return out;
}

double toNum(string str) {
   stringstream s(str);
   double num;
   s >> num;
   return num;
}

};






















