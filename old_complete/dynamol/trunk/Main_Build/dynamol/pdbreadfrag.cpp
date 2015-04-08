/***************************************************************************
                          pdbreadfrag.cpp  -  description
                             -------------------
    begin                : Fri May 2 2003
    copyright            : (C) 2003 by John Furr
    email                : john.furr@albmolecular.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, ||     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "pdbreadfrag.h"

pdbReadFrag::pdbReadFrag(){
  this->num = 10;
}
pdbReadFrag::~pdbReadFrag(){
}

string  pdbReadFrag::getName()                        {return name;};
int     pdbReadFrag::getNum()                         {return this->num;};
void    pdbReadFrag::setName(string name)             {this->name = name;};
void    pdbReadFrag::setData( vector< string > data)  {this->frag = data;};

void    pdbReadFrag::setNum(string setNum)     {
  this->num = atoi(setNum.c_str());
  int a = this->num;
};

void pdbReadFrag::readFrag(ifstream inFile) {

}

void pdbReadFrag::printStats() {
	for (unsigned int i=0; i<frag.size(); i++) {
		////////////cout <<frag[i]<<endl;
	}
}





































