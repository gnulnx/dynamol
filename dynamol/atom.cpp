/***************************************************************************
                          atom.cpp  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;
#include "atom.h"
#include "bond.h"

namespace dynamol {

atom::~atom() {

}

molecule *atom::getParent() 
{ 
    cout <<"atom::getParent: "<< this->parent<<endl;
    return this->parent; 
}

atom::atom(const atom &atm) 
: DyObject() // You might want t keep the original object number???
{
	num = atm.num;
	symbol = atm.symbol;

	for (int i=0; i<3; i++)
		fCoords[i] = atm.fCoords[i];

	for (int i=0; i<4; i++) 
		COLOR[i] = atm.COLOR[i];

	AN = atm.AN;

	//Note 1) molecule *parent must be set in molecule copy constructor
	//Note 2) vector<atom *> atoms must be copied in the molecule copy constuctor
}

atom::atom(int num, string symbol, float x, float y, float z, int atomicNum) 
: DyObject()
{
	this->num = num;
	this->symbol = symbol;
	fCoords[0] = x;
	fCoords[1] = y;
	fCoords[2] = z;

	if (atomicNum == -1)
		AN = SYM2AN(symbol);
	else
		AN = atomicNum;

	defaultColor();
}

//I don't think that you are using this function right now
bool  atom::addAtom(atom *at) {
	for (unsigned int i=0; i<atoms.size(); i++) {
		if (atoms[i] == at)
			return false;
	}

	atoms.push_back(at);
	return true;
}

void atom::defaultColor() {
	if (AN == 6) {
		COLOR[0] = 0.15; COLOR[1] = 0.80; COLOR[2] = 0.15;
	} else if (AN == 7) {
		COLOR[0] = 0.0; COLOR[1] = 0.0; COLOR[2] = 1.0;
	} else if (AN == 8) {
		COLOR[0] = 1.0; COLOR[1] = 0.00; COLOR[2] = 0.0;
	} else if (AN == 9) { //Flourine
		COLOR[0] = 0.0; COLOR[1] = 1.0; COLOR[2] = 0.0;
	}  else if (AN == 1) {
		COLOR[0] = 1.0; COLOR[1] = 1.0; COLOR[2] = 1.0;
	} else if (AN == 15) {
		COLOR[0] = 0.65; COLOR[1] = 0.05; COLOR[2] = 1.0;
	} else if (AN == 16) {
		COLOR[0] = 0.8; COLOR[1] = 0.8; COLOR[2] = 0.0;
	} else if (AN == 17) { //Chlorine
		COLOR[0] = 0.0; COLOR[1] = 0.50; COLOR[2] = 0.0;
	} else if (AN == 35) { //Bromine
		COLOR[0] = 0.8; COLOR[1] = 0.10; COLOR[2] = 0.0;
	} else if (AN == -1) {
		COLOR[0] =  0.0; COLOR[1] = 0.85; COLOR[2] = 0.0;  //Select color is now GREEN
	} else if (AN == -2) {
		COLOR[0] =  1.0; COLOR[1] = 1.0; COLOR[2] = 0.5; //yellow for highlighted objects...bond order guessing?
	} else if (symbol == "X" || symbol == "x") {
		COLOR[0] = 1.0; COLOR[1] = 0.5; COLOR[2] = 0.34;
	} else {
		COLOR[0] = 0.5; COLOR[1] = 0.5; COLOR[2] = 0.5;
	}

	COLOR[3] = 1.0;  //default alpha value of 1.  This makes it so that the atom is blended correctly
}

int atom::SYM2AN(string type) {
   int atomicNum = 0;
   if (type[0] == 'H' && type.size() == 1) {
      atomicNum = 1;
   } else if (type[0] == 'H' && type[1] == 'e') {
      atomicNum = 2;
   } else if (type[0] == 'l' && type[1] == 'i') {
      atomicNum = 3;
   } else if (type[0] == 'B' && type[1] == 'e') {
      atomicNum = 4;
   } else if (type[0] == 'B' && type.size() == 1) {
      atomicNum = 5;
   } else if (type[0] == 'C' && type.size() == 1) {
      atomicNum = 6;
   } else if (type[0] == 'N' && type.size() == 1) {
      atomicNum = 7;
   } else if (type[0] == 'O' && type.size() == 1) {
      atomicNum = 8;
   } else if (type[0] == 'F') {
      atomicNum = 9;
   } else if (type[0] == 'N' && type[1] == 'e') {
      atomicNum = 10;
   } else if (type[0] == 'N' && type[1] == 'a') {
      atomicNum = 11;
   } else if (type[0] == 'M' && type[1] == 'g') {
      atomicNum = 12;
   } else if (type[0] == 'A' && type[1] == 'l') {
      atomicNum = 13;
   } else if (type[0] == 'S' && type[1] == 'i') {
      atomicNum = 14;
   } else if (type[0] == 'P' && type.size() == 1) {
      atomicNum = 15;
   } else if (type[0] == 'S' && type.size() == 1) {
      atomicNum = 16;
   } else if (type[0] == 'C' && type[1] == 'l') {
      atomicNum = 17;
   } else if (type[0] == 'A' && type[1] == 'r') {
      atomicNum = 18;
   } else if (type[0] == 'K') {
      atomicNum = 19;
   } else if (type[0] == 'C' && type[1] == 'a') {
      atomicNum = 20;
   } else if (type[0] == 'S' && type[1] == 'c') {
      atomicNum = 21;
   } else if (type[0] == 'T' && type[1] == 'i') {
      atomicNum = 22;
   } else if (type[0] == 'V') {
      atomicNum = 23;
   } else if (type[0] == 'C' && type[1] == 'r') {
      atomicNum = 24;
   } else if (type[0] == 'M' && type[1] == 'n') {
      atomicNum = 25;
   } else if (type[0] == 'F' && type[1] == 'e') {
      atomicNum = 26;
   } else if (type[0] == 'C' && type[1] == 'o') {
      atomicNum = 27;
   } else if (type[0] == 'N' && type[1] == 'i') {
      atomicNum = 28;
   } else if (type[0] == 'C' && type[1] == 'u') {
      atomicNum = 29;
   } else if (type[0] == 'Z' && (type[1] == 'n' || type[1] == 'N' )) {
      atomicNum = 30;
   } else if (type[0] == 'G' && type[1] == 'a') {
      atomicNum = 31;
   } else if (type[0] == 'G' && type[1] == 'e') {
      atomicNum = 32;
   } else if (type[0] == 'A' && type[1] == 's') {
      atomicNum = 33;
   } else if (type[0] == 'S' && type[1] == 'e') {
      atomicNum = 34;
   } else if (type[0] == 'B' && type[1] == 'r') {
      atomicNum = 35;
   } else if (type[0] == 'K' && type[1] == 'r') {
      atomicNum = 36;
   } else if (type[0] == 'R' && type[1] == 'b') {
      atomicNum = 37;
   } else if (type[0] == 'S' && type[1] == 'r') {
      atomicNum = 38;
   } else if (type[0] == 'Y') {
      atomicNum = 39;
   } else if (type[0] == 'Z' && type[1] == 'r') {
      atomicNum = 40;
   } else if (type[0] == 'M' && type[1] == 'o') {
      atomicNum = 42;
   } else if (type[0] == 'T' && type[1] == 'c') {
      atomicNum = 43;
   } else if (type[0] == 'R' && type[1] == 'u') {
      atomicNum = 44;
   } else if (type[0] == 'R' && type[1] == 'h') {
      atomicNum = 45;
   } else if (type[0] == 'P' && type[1] == 'd') {
      atomicNum = 46;
   } else if (type[0] == 'A' && type[1] == 'g') {
      atomicNum = 47;
   } else if (type[0] == 'C' && type[1] == 'd') {
      atomicNum = 48;
   } else if (type[0] == 'I' && type[1] == 'n') {
      atomicNum = 49;
   } else if (type[0] == 'S' && type[1] == 'n') {
      atomicNum = 50;
   } else if (type[0] == 'S' && type[1] == 'b') {
      atomicNum = 51;
   } else if (type[0] == 'T' && type[1] == 'e') {
      atomicNum = 52;
   } else if (type[0] == 'I') {
      atomicNum = 53;
   } else if (type[0] == 'X' && type[1] == 'e') {
      atomicNum = 54;
   } else if (type[0] == 'C' && type[1] == 's') {
      atomicNum = 55;
   } else if (type[0] == 'B' && type[1] == 'a') {
      atomicNum = 56;
   } else if (type[0] == 'L' && type[1] == 'a') {
      atomicNum = 57;
   } else if (type[0] == 'H' && type[1] == 'f') {
      atomicNum = 58;
   } else if (type[0] == 'P' && type[1] == 'r') {
      atomicNum = 59;
   } else if (type[0] == 'N' && type[1] == 'd') {
      atomicNum = 60;
   } else if (type[0] == 'P' && type[1] == 'm') {
      atomicNum = 61;
   } else if (type[0] == 'S' && type[1] == 'm') {
      atomicNum = 62;
   } else if (type[0] == 'E' && type[1] == 'u') {
      atomicNum = 63;
   } else if (type[0] == 'G' && type[1] == 'd') {
      atomicNum = 64;
   } else if (type[0] == 'T' && type[1] == 'b') {
      atomicNum = 65;
   } else if (type[0] == 'D' && type[1] == 'y') {
      atomicNum = 66;
   } else if (type[0] == 'H' && type[1] == 'o') {
      atomicNum = 67;
   } else if (type[0] == 'E' && type[1] == 'r') {
      atomicNum = 68;
   } else if (type[0] == 'T' && type[1] == 'm') {
      atomicNum = 69;
   } else if (type[0] == 'Y' && type[1] == 'b') {
      atomicNum = 70;
   } else if (type[0] == 'L' && type[1] == 'u') {
      atomicNum = 71;
   } else if (type[0] == 'H' && type[1] == 'f') {
      atomicNum = 72;
   } else if (type[0] == 'T' && type[1] == 'a') {
      atomicNum = 73;
   } else if (type[0] == 'W') {
      atomicNum = 74;
   } else if (type[0] == 'R' && type[1] == 'e') {
      atomicNum = 75;
   } else if (type[0] == 'O' && type[1] == 's') {
      atomicNum = 76;
   } else if (type[0] == 'I' && type[1] == 'r') {
      atomicNum = 77;
   } else if (type[0] == 'P' && type[1] == 't') {
      atomicNum = 78;
   } else if (type[0] == 'A' && type[1] == 'u') {
      atomicNum = 79;
   } else if (type[0] == 'H' && type[1] == 'g') {
      atomicNum = 80;
   } else if (type[0] == 'T' && type[1] == 'i') {
      atomicNum = 81;
   } else if (type[0] == 'P' && type[1] == 'b') {
      atomicNum = 82;
   } else if (type[0] == 'B' && type[1] == 'i') {
      atomicNum = 83;
   } else if (type[0] == 'P' && type[1] == 'o') {
      atomicNum = 84;
   } else if (type[0] == 'A' && type[1] == 't') {
      atomicNum = 85;
   } else if (type[0] == 'R' && type[1] == 'n') {
      atomicNum = 86;
   } else if (type[0] == 'F' && type[1] == 'r') {
      atomicNum = 87;
   } else if (type[0] == 'R' && type[1] == 'a') {
      atomicNum = 88;
   } else if (type[0] == 'A' && type[1] == 'c') {
      atomicNum = 89;
   } else if (type[0] == 'T' && type[1] == 'h') {
      atomicNum = 90;
   } else if (type[0] == 'P' && type[1] == 'a') {
      atomicNum = 91;
   } else if (type[0] == 'U') {
      atomicNum = 92;
   } else if (type[0] == 'N' && type[1] == 'p') {
      atomicNum = 93;
   } else if (type[0] == 'P' && type[1] == 'u') {
      atomicNum = 94;
   } else if (type[0] == 'A' && type[1] == 'm') {
      atomicNum = 95;
   } else if (type[0] == 'C' && type[1] == 'm') {
      atomicNum = 96;
   } else if (type[0] == 'B' && type[1] == 'k') {
      atomicNum = 97;
   } else if (type[0] == 'C' && type[1] == 'f') {
      atomicNum = 98;
   } else if (type[0] == 'E' && type[1] == 's') {
      atomicNum = 99;
   } else if (type[0] == 'F' && type[1] == 'm') {
      atomicNum = 100;
   } else if (type[0] == 'M' && type[1] == 'd') {
      atomicNum = 101;
   } else if (type[0] == 'N' && type[1] == 'o') {
      atomicNum = 102;
   } else if (type[0] == 'L' && type[1] == 'r') {
      atomicNum = 103;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'q') {
      atomicNum = 104;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'p') {
      atomicNum = 105;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'h') {
      atomicNum = 106;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 's') {
      atomicNum = 107;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'o') {
      atomicNum = 108;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'e') {
      atomicNum = 109;
   } else if (type[0] == 'U' && type[1] == 'n' && type[2] == 'n') {
      atomicNum = 110;
   }

   if (atomicNum == 0) {

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
  } else if (type[0] == 'A' && type[1] == 'u') {
      atomicNum = 79;
  } else {
      atomicNum = 0;
  }
  }
    return atomicNum;
}

}
                                        
