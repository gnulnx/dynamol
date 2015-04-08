/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   emai:  john.furr@dynamol.com
 ***************************************************************************/
#include "sdreader.h"
#include "molecule.h"
#include "qstring.h"
#include "atom.h"
#include "bond.h"
#include <fstream>
#include <iostream>
#include <qmessagebox.h>
#include "moldb.h"

sdReader::sdReader()
{
   posMap.clear();
   nameMap.clear();
   currFileName = "";
}


sdReader::~sdReader()
{
   posMap.clear();
   nameMap.clear();
}

int sdReader::scanSDFile(string fileName) {
   posMap.clear();
   nameMap.clear();
   currFileName = fileName;
   ifstream inFile(fileName.c_str(), ios::binary);
   if (!inFile) {
      QString error = fileName + " not found";
      QMessageBox::critical(0, "Error", error);
   }
   
   // Read the initial header
   string name, tmp, atomLine;
   long int pos = inFile.tellg();
   getline(inFile, name);
      
   posMap[0] = pos;
   pair<QString, long long int> namePair(name, pos);
   nameMap.insert(namePair);
   
   int molCount = 1;
   while (true) {
      getline(inFile, tmp);
      if ( inFile.eof() )
          break;
          
      if (tmp.substr(0,4) == "$$$$") {
         pos = inFile.tellg();
         getline(inFile, name);
         if ( inFile.eof() ) 
	     break;
         posMap[molCount] = pos;
         pair<QString, long long int> namePair(name, pos);
         nameMap.insert(namePair);
         molCount++;
      }
   }
       
   return posMap.size(); 
}

molecule *sdReader::getMolPos(int pos) {
   if (pos >= posMap.size()) {
      QMessageBox::critical(0, "Error", "Index out of range in sdReader::getMolNum");
   }
   
   molDB db;
   return readSD(currFileName, posMap[pos]);
}

 
molecule *sdReader::readSD(QString fileName, int offset) {
   ifstream inFile(fileName.latin1(), ios::in);
   
   if (!inFile) {
      QMessageBox::critical(0, "Error", fileName + " No opened.  sdReader::readSD");
      return NULL;
   }
   
   inFile.seekg(offset);
   
   molecule *mol = new molecule;
   
   string Name, tmp, atmNumString, bdNumString;
      
    getline(inFile, Name);
    mol->setName(Name);
    getline(inFile, tmp);
    getline(inFile, tmp);
    getline(inFile, tmp);

    if (tmp.size() == 0) {
      QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"This error is likely due to an extra line in the SD header");
      delete mol;
      
      return NULL;
    }
    
    atmNumString = tmp.substr(0,3);
    if (!checkFloatNum(atmNumString)) {
    	QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"Did not find an integer value for number of atoms");
	delete mol;
	//////////////cout <<"atmNumString is: " << atmNumString << endl;
	return NULL;
    }
    
    bdNumString =  tmp.substr(3,3);
    if (!checkIntNum(bdNumString)) {
    	QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"Did not find an integer value for number of bonds");
	delete mol;
	return NULL;
    }
    
    int atmNum = atoi(atmNumString.c_str() );
    int bdNum = atoi(bdNumString.c_str() );

    
    for (int j=0; j<atmNum; j++) {
      float x, y, z;
      string sym;
      
      inFile >> x >> y >> z >> sym;
      if (!inFile) {
      	QMessageBox::critical( 0, "Dynamol",
    	"An error was encountered in the sd file.  Molecule read has been aborted\n"
    	"Line read failed!");
	delete mol;
	return NULL;
      }
     
      getline(inFile, tmp);    //There is other information that you can read from the sd 
      int atomicNum = molDB::SYM2AN(sym);
      mol->addAtom(j+1, sym, x, y, z, atomicNum);
    }

    string line;
    for (int j=0; j<bdNum; j++) {
      int num, from, to, order;
      getline(inFile, line);
      QString qFrom = line.substr(0,3);
      QString qTo = line.substr(3,3);
      QString qOrder = line.substr(8,1);
      from =  qFrom.toInt();
      to = qTo.toInt();
      order = qOrder.toInt();

      mol->addBond(j+1, from, to, order);
    }
  
    while (inFile >> tmp) {
      if (tmp == ">") {
        inFile >> tmp;
      	string name = tmp.substr(1,tmp.size()-2);
	getline(inFile, tmp);
	string data;
	getline(inFile, data);
        mol->addPropValuePair(name, data);;
      }
      if (tmp.substr(0,4) == "$$$$") {
         break;
      }
    }
    
    
    return mol;
}
 
bool sdReader::checkFloatNum(string &str) {
   bool bad = true;
   for (int i=0; i<str.size(); i++) {
      bool bad = true;
      if (str[i] == '0') bad = false;
      else if (str[i] == '1') bad = false;
      else if (str[i] == '2') bad = false;
      else if (str[i] == '3') bad = false;
      else if (str[i] == '4') bad = false;
      else if (str[i] == '5') bad = false;
      else if (str[i] == '6') bad = false;
      else if (str[i] == '7') bad = false;
      else if (str[i] == '8') bad = false;
      else if (str[i] == '9') bad = false;
      else if (str[i] == '+') bad = false;
      else if (str[i] == '-') bad = false;
      else if (str[i] == '.') bad = false;
      else if (str[i] == ' ') bad = false;
     
      if (bad) return false;
   }
   return true;
}

bool sdReader::checkIntNum(string &str) {
   bool bad = true;
   for (int i=0; i<str.size(); i++) {
      bool bad = true;
      if (str[i] == '0') bad = false;
      else if(str[i] == '1') bad = false;
      else if (str[i] == '2') bad = false;
      else if (str[i] == '3') bad = false;
      else if (str[i] == '4') bad = false;
      else if (str[i] == '5') bad = false;
      else if (str[i] == '6') bad = false;
      else if (str[i] == '7') bad = false;
      else if (str[i] == '8') bad = false;
      else if (str[i] == '9') bad = false;
      else if (str[i] == '+') bad = false;
      else if (str[i] == '-') bad = false;
      else if (str[i] == ' ') bad = false;
     
      if (bad) return false;
   }
   return true;
}


