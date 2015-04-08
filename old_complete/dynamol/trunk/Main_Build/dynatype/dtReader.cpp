/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "dtReader.h"
#include "molecule.h"
#include <iostream>
#include <iomanip> 
#include <fstream>
#include "bond.h"
#include "atom.h"
#include "dtUtility.h"
namespace dt {
	

dtReader::dtReader()
{
}


dtReader::~dtReader()
{
}

//bool dtReader::readSDFX(string fileName, molecule *mol) {
bool dtReader::readSDFX(string fileName, molPtr mol) {
   ifstream inFile;
   inFile.open(fileName.c_str(), ios::in);
   if (!inFile) {
      return false;
   }

   string Name, tmp, atmNumString, bdNumString, vendor, chargeType, ffType;
   inFile >> tmp;
   if (tmp != "@<MOLECULE>" && tmp != "@<CHAIN>" && tmp != "@<PROTEIN>") {
     return false;
   }
   getline(inFile, Name);
   getline(inFile, vendor);
   inFile >> tmp;
   getline(inFile, mol->ffType);
   getline(inFile, chargeType);
  
   int atmNum, bdNum;
   inFile >> atmNum >> bdNum;
   inFile >> tmp;
   if (tmp != "%ATOMS" ) {
     return false;
   }
   for (int j=0; j<atmNum; j++) {
      float x, y, z, charge;
      string type, fragName, chainName, ribType, SYM;
      int an;
      inFile >> an >> SYM >>x >> y >> z >> charge >> type >> chainName >> fragName >> ribType;
      if (!inFile) {
	      //delete mol;
	      return false;
      }

      //string sym = AN2SYM(an);
      //atom *atm = mol->addAtom(j+1, SYM, x, y, z, an);
      atomPtr atm = mol->addAtom(j+1, SYM, x, y, z, an);
      atm->charge = charge;
      atm->fragName = fragName;
      atm->chainName = chainName;
      atm->ribType = ribType;
      
    }
    inFile >> tmp;
    if (tmp != "%BONDS" ) {
      //delete mol;
      return false;
    }
   
    for (int i=0; i<bdNum; i++) {
      int num, from, to, order;
      inFile >> from >> to >>order;
      getline(inFile, tmp);
      mol->addBond(i+1, from, to, order);
    }
    //This last section will update the bond list in the atoms
   for (int i=0; i<mol->bonds.size(); i++) {
     //bond *bd = mol->bonds[i];
     bondPtr bd = mol->bonds[i];
     atomPtr from = bd->from.lock();
     atomPtr to = bd->to.lock();
     from->bonds.push_back(bd);
     to->bonds.push_back(bd); 
   }
   return true;
}


//void dtReader::readSDF(string fileName, molecule *mol, long int offset) { 
void dtReader::readSDF(string fileName, molPtr mol, long int offset) {
   fstream inFile;
   inFile.open(fileName.c_str(), ios::in | ios::binary);
   if (!inFile) {
     return;
   }

   inFile.seekg(offset, ios::cur);
   
    
   string Name, tmp, atmNumString, bdNumString;
   getline(inFile, Name);
   mol->name = Name;
   getline(inFile, tmp);
   getline(inFile, tmp);
   getline(inFile, tmp);

   if (tmp.size() == 0) {
     //delete mol;
     return;
   }
    
   atmNumString = tmp.substr(0,3);
   if (!checkFloatNum(atmNumString)) {
      //delete mol;
      return;
   }
    
   bdNumString =  tmp.substr(3,3);
   if (!checkIntNum(bdNumString)) {
      //delete mol;
      return;
   }
    
   int atmNum = atoi(atmNumString.c_str() );
   int bdNum = atoi(bdNumString.c_str() );

    
   for (int j=0; j<atmNum; j++) {
      float x, y, z;
      string sym;
	  int massDiff, charge, parity;

      inFile >> x >> y >> z >> sym >> massDiff >> charge >> parity;
      if (!inFile) {
         //delete mol;
         return;
      }  
      getline(inFile, tmp);    //There is other information that you can read from the sd 
      int atomicNum = SYM2AN(sym);
      atomPtr atm = mol->addAtom(j+1, sym, x, y, z, atomicNum);
	  atm->parity = parity;
   }
  
   for (int j=0; j<bdNum; j++) {
      int num, from, to, order;
      getline(inFile, tmp);
      string sFrom = tmp.substr(0, 3);
      string sTo = tmp.substr(3, 3);
      string sOrder = tmp.substr(6, 3);
      from = toNum(sFrom);
      to = toNum(sTo);
      order = toNum(sOrder);
      mol->addBond(j+1, from, to, order);
   }
   getline(inFile, tmp); //just to get that last little bit
   int input = 0;

   //This last section will update the bond list in the atoms
   //for (int i=0; i<mol->bonds.size(); i++) {
   //  bond *bd = mol->bonds[i];
   //  bd->from->bonds.push_back(bd);
   //  bd->to->bonds.push_back(bd);   
  // }
  return;
}

string dtReader::AN2SYM(int an) {
   if (an == 1) return "H";
   if (an == 6) return "C";
   if (an == 7) return "N";
   if (an == 8) return "O";
   if (an == 15) return "P";
   if (an == 16) return "S";
   if (an == 17) return "Cl";
   if (an == 41) return "si";
   if (an == 35) return "Br";
   if (an == 53) return "I";
   if (an == 19) return "K";
   if (an == 11) return "Na";
   if (an == 9) return "F";
   if (an == 10) return "Ca";
   if (an == 3) return "Li";
   if (an == 13) return "Al";
   else return "NONE...FIX ME JOHN!";
}

int dtReader::SYM2AN(string type) {
  int atomicNum = 0;
  if (type[0] == 'H') {
      atomicNum = 1;
    } else if (type[0] == 'C' && type[1] != 'l') {
      atomicNum = 6;
    } else if (type[0] == 'N')  {
      atomicNum = 7;
    } else if (type[0] == 'O') {
      atomicNum = 8;
    } else if (type[0] == 'S' && type[1] != 'i') {
      atomicNum = 16;
    } else if (type[0] == 'P') {
      atomicNum = 15;
    } else if (type[0] == 'F') {
      atomicNum = 9;
    } else if (type[0] == 'C' && type[1] == 'l') {
      atomicNum = 17;
    } else if (type[0] == 's' && type[1] == 'i') {
      atomicNum = 41;
    } else if (type[0] == 'B' && type[1] == 'r') {
      atomicNum = 35;
    } else if (type[0] == 'I') {
      atomicNum = 53;
    } else if (type[0] == 'N' && type[1] == 'a') {
      atomicNum = 11;
    } else if (type[0] == 'K') {
      atomicNum = 19;
    } else if (type[0] == 'C' && type[1] == 'a') {
      atomicNum = 20;
    } else if (type[0] == 'L' && type[1] == 'i') {
      atomicNum = 3;
    } else if (type[0] == 'A' && type[1] == 'l') {
      atomicNum = 13;
    } else {
      atomicNum = 0;
    }

    return atomicNum;
}

bool dtReader::checkIntNum(string &str) {
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
 
bool dtReader::checkFloatNum(string &str) {
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

//void dtReader::writeSDF(const char *file, molecule *mol, int append) { 
void dtReader::writeSDF(const char *file, molPtr mol, int append) {
   ofstream outFile;
   if (append == 1) outFile.open(file, ios::app);
   else outFile.open(file, ios::out);
   
   if (!outFile) {
     exit(0);
   }
   
   outFile << mol->name << endl;
   outFile <<"Dynamol 3D sdf file"<<endl;
   outFile <<endl;
   outFile << setw(3) << mol->atoms.size() << setw(3) << mol->bonds.size();
   for (int i=0; i<8; i++) {
     outFile << setw(3) << "0";
   }
   outFile << endl;
   
   for (int i=0; i<mol->atoms.size(); i++) {
      //atom *atm = mol->atoms[i];
      atomPtr atm = mol->atoms[i];
      outFile << setw(10) << atm->Coords[0] << setw(10) << atm->Coords[1] << setw(10) << atm->Coords[2];
      outFile << setw(3) << atm->getSymbol();
      for (int i=0; i<5; i++) outFile << setw(3) << "0";
      outFile << endl;
   
   }
   
   for (int i=0; i<mol->bonds.size(); i++) {
     //bond *bd = mol->bonds[i];
     bondPtr bd = mol->bonds[i];
     outFile << setw(3) << bd->from.lock()->getNum() << setw(3) << bd->to.lock()->getNum();
     outFile << setw(3) << bd->order;
     for (int i=0; i<3; i++) outFile << setw(3) << "0";
     outFile << endl;
   }
   outFile <<"M END"<<endl;
   
   outFile << "$$$$" << endl;
   
}



//void dtReader::writeSDFX(const char *file, molecule *mol, int append) {
void dtReader::writeSDFX(const char *file, molPtr mol, int append) {
   ofstream outFile;
   if (append == 1) outFile.open(file, ios::app);
   else outFile.open(file, ios::out);
   
   if (!outFile) {
     exit(0);
   }

   outFile <<"@<MOLECULE>\t" << mol->name << endl;
   outFile <<"Dynamol Inc."<<endl;
   outFile <<"Force_Field:"<<setw(8) << mol->ffType << endl;
   outFile <<"Charges:    "<<setw(8)<< mol->chargeType << endl;
   outFile  << mol->atoms.size() << " " << mol->bonds.size() << endl;
   outFile <<"%ATOMS"<<endl;
   for (int i=0; i<mol->atoms.size(); i++) {
      //atom *atm = mol->atoms[i];
      atomPtr atm = mol->atoms[i];
      outFile <<atm->getAN()<< setw(4)<<atm->getSymbol()<<setw(15) << atm->Coords[0] << setw(15) << atm->Coords[1] << setw(15) << atm->Coords[2];
      outFile << setw(15) << atm->charge << setw(10) <<atm->type;
      outFile << setw(10) << atm->chainName << setw(10) << atm->fragName;
      outFile << setw(10) << atm->ribType << endl;
   }
   
   outFile  <<"%BONDS"<<endl;
   for (int i=0; i<mol->bonds.size(); i++) {
     //bond *bd = mol->bonds[i];
     bondPtr bd = mol->bonds[i];
     outFile << bd->from.lock()->getNum() << setw(15) << bd->to.lock()->getNum();
     outFile << setw(15) << bd->order << endl;
   }
   
   for (int i=0; i<mol->propValue.size(); i++) {
      outFile <<"$ "<<mol->propertyNames[i]<<"\t";
      if (mol->propType.size() != 0) {
      	outFile << mol->propType[i] <<"\t";
      } else {
      	outFile <<"*\t";
      }
      outFile << mol->propValue[i] << endl;
      outFile << endl;
   }   
}

} //end namespace

























