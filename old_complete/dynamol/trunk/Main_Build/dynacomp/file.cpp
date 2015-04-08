/***************************************
 *   Copyright (C) 2004 by Dynamol Inc.*
 *   john.furr@dynamol.com             *
 ***************************************/
#include "file.h"

//Dynamol Computational Libary includes
#include "molecule.h"
#include "atom.h"
#include "bond.h"

//Dynamol Base Library Includes
#include "../dynabase/utility.h"

//Standard Library Includes
#include <iostream>
#include <iomanip>
#include <fstream>
using std::cout;
using std::endl;
using std::setw;
using std::ofstream;

#include <boost/weak_ptr.hpp>

namespace dynacomp {

file::file()
{
}


file::~file()
{
}

bool file::writeSDF(const char *file, molecule *mol, int append) {
   ////////////cout <<"n::writeSDF"<<endl;
  //THis first section renumbers the atoms && bonds to make sure that everything writes correctly 
  for (int i=0; i < mol->atoms.size(); i++) {
    mol->atoms[i]->setNum(i+1);
  }
  
  for (int i=0; i<mol->atoms.size(); i++) {
     atom *atm = mol->atoms[i];
     atm->atoms.clear();
     atm->angles.clear();
     atm->bonds.clear();
  }
  
  for (int i=0; i<mol->bonds.size(); i++) {
     bond *bd = mol->bonds[i];
     bd->fromAtom()->addAtom(bd->toAtom());
     bd->toAtom()->addAtom(bd->fromAtom());
  }
  
  //this->AN2SYM(1);
  for (int i=0; i<mol->atoms.size(); i++) {
     atom *atm = mol->atoms[i];
     string sym = AN2SYM(atm->getAN());
     atm->setSymbol( sym );
  }
  //Now lets make sure that all the atom->syms match the atomicNumbers
  
   ofstream outFile;
   if (append == 1) outFile.open(file, ios::app);
   else outFile.open(file, ios::out);
   
   if (!outFile) {
     cout <<"Could not open " << file <<" for writing"<<endl;
     return false;
   }
   
   outFile << mol->getName() << endl;
   outFile <<"Dynamol 3D sdf file"<<endl;
   outFile <<endl;
   outFile << setw(3) << mol->atoms.size() << setw(3) << mol->bonds.size();
   outFile <<"  0  0  1  0  0  0  0  0999 V2000"<<endl;
   //outFile <<" 0 0  1  0  0  0  0  0999 V2000" << endl;
   //for (int i=0; i<8; i++) {
   //  outFile << setw(3) << "0";
   //}
   //outFile << endl;
   
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      float *cd = atm->fCoords;

      string scd0 = dynabase::setNum(cd[0]);
      string scd1 = dynabase::setNum(cd[1]);
      string scd2 = dynabase::setNum(cd[2]);
	
      string tmp = "";
	  	
	  for (int i=0; i<scd0.size(); i++) {
         if (i < 7) 
	     	tmp = tmp + scd0[i];
      }
	  scd0 = tmp;
		
	  tmp = "";
      for (int i=0; i<scd1.size(); i++) {
		 if (i < 7) 
             tmp = tmp + scd1[i];
      }
      scd1 = tmp;
	  
      tmp = "";
      for (int i=0; i<scd2.size(); i++) {
         if (i < 7)
             tmp = tmp + scd2[i];
      }
      scd2 = tmp;
	

      //outFile << setiosflags(ios::fixed) << setprecision(2) << setw(10) << scd0 << setw(10) << scd1 << setw(10) << scd2;
	  outFile << setiosflags(ios::fixed) << setprecision(4) <<setw(10)<< cd[0] << setw(10) << cd[1] << setw(10) << cd[2];
      outFile <<" "<< left << setw(2) << atm->getSymbol().c_str()<<"  0  0  " << atm->parity << right;
      for (int i=0; i<9; i++) outFile << setw(3) << "0";
      outFile << endl;
   
   }
   
   for (int i=0; i<mol->bonds.size(); i++) {
     bond *bd = mol->bonds[i];
     outFile << setw(3) << bd->fromAtom()->getNum() << setw(3) << bd->toAtom()->getNum();
     outFile << setw(3) << bd->order;
     for (int i=0; i<4; i++) outFile << setw(3) << "0";
     outFile << endl;
   }
   outFile <<"M  END"<<endl;
   
   map<string, string>::iterator propIt = mol->propMap.begin();
   for (propIt; propIt != mol->propMap.end(); propIt++) {
   //for (int i=0; i<mol->propertyData.size(); i++) {
      string name = propIt->first;
      string value = propIt->second;  
      outFile << ">  <" << name << ">" << endl;
      outFile << value << endl;
      outFile << endl;
   }
   
   outFile << "$$$$" << endl;
   
   return true;
}

string file::AN2SYM(int an) {
   if (an == 1) return "H";
   else if (an == 2) return "He";
   else if (an == 3) return "li";
   else if (an == 4) return "Be";
   else if (an == 5) return "B";
   else if (an == 6) return "C";
   else if (an == 7) return "N";
   else if (an == 8) return "O";
   else if (an == 9) return "F";
   else if (an == 10) return "Ne";
   else if (an == 11) return "Na";
   else if (an == 12) return "Mg";
   else if (an == 13) return "Al";
   else if (an == 14) return "Si";
   else if (an == 15) return "P";
   else if (an == 16) return "S";
   else if (an == 17) return "Cl";
   else if (an == 18) return "Ar";
   else if (an == 19) return "K";
   else if (an == 20) return "Ca";
   else if (an == 21) return "Sc";
   else if (an == 22) return "Ti";
   else if (an == 23) return "V";
   else if (an == 24) return "Cr";
   else if (an == 25) return "Mn";
   else if (an == 26) return "Fe";
   else if (an == 27) return "Co";
   else if (an == 28) return "Ni";
   else if (an == 29) return "Cu";
   else if (an == 30) return "Zn";
   else if (an == 31) return "Ga";
   else if (an == 32) return "Ge";
   else if (an == 33) return "As";
   else if (an == 34) return "Se";
   else if (an == 35) return "Br";
   else if (an == 36) return "Kr";
   else if (an == 37) return "Rb";
   else if (an == 38) return "Sr";
   else if (an == 39) return "Y";
   else if (an == 40) return "Zr";
   else if (an == 42) return "Mo";
   else if (an == 43) return "Tc";
   else if (an == 44) return "Ru";
   else if (an == 45) return "Rh";
   else if (an == 46) return "Pd";
   else if (an == 47) return "Ag";
   else if (an == 48) return "Cd";
   else if (an == 49) return "In";
   else if (an == 50) return "Sn";
   else if (an == 51) return "Sb";
   else if (an == 52) return "Te";
   else if (an == 53) return "I";
   else if (an == 54) return "Xe";
   else if (an == 55) return "Cs";
   else if (an == 56) return "Ba";
   else if (an == 57) return "La";
   else if (an == 58) return "Hf";
   else if (an == 59) return "Pr";
   else if (an == 60) return "Nd";
   else if (an == 61) return "Pm";
   else if (an == 62) return "Sm";
   else if (an == 63) return "Eu";
   else if (an == 64) return "Gd";
   else if (an == 65) return "Tb";
   else if (an == 66) return "Dy";
   else if (an == 67) return "Ho";
   else if (an == 68) return "Er";
   else if (an == 69) return "Tm";
   else if (an == 70) return "Yb";
   else if (an == 71) return "Lu";
   else if (an == 72) return "Hf";
   else if (an == 73) return "Ta";
   else if (an == 74) return "W";
   else if (an == 75) return "Re";
   else if (an == 76) return "Os";
   else if (an == 77) return "Ir";
   else if (an == 78) return "Pt";
   else if (an == 79) return "Au";
   else if (an == 80) return "Hg";
   else if (an == 81) return "Ti";
   else if (an == 82) return "Pb";
   else if (an == 83) return "Bi";
   else if (an == 84) return "Po";
   else if (an == 85) return "At";
   else if (an == 86) return "Rn";
   else if (an == 87) return "Fr";
   else if (an == 88) return "Ra";
   else if (an == 89) return "Ac";
   else if (an == 90) return "Th";
   else if (an == 91) return "Pa";
   else if (an == 92) return "U";
   else if (an == 93) return "Np";
   else if (an == 94) return "Pu";
   else if (an == 95) return "Am";
   else if (an == 96) return "Cm";
   else if (an == 97) return "Bk";
   else if (an == 98) return "Cf";
   else if (an == 99) return "Es";
   else if (an == 100) return "Fm";
   else if (an == 101) return "Md";
   else if (an == 102) return "No";
   else if (an == 103) return "Lr";
   else if (an == 104) return "Unq";
   else if (an == 105) return "Unp";
   else if (an == 106) return "Unh";
   else if (an == 107) return "Uns";
   else if (an == 108) return "Uno";
   else if (an == 109) return "Une";
   else if (an == 110) return "Unn";
   else {
   	//////////cout <<"Could not convert atomic number: " << an << " to symbol...please fix me!"<<endl;
   }
}

}

