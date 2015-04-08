/***************************************************************************
                          pdbreadfrag.h  -  description
                             -------------------
    begin                : Fri May 2 2003
    copyright            : (C) 2003 by John Furr
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef PDBREADFRAG_H
#define PDBREADFRAG_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

/**
  *@author John Furr
  */

class pdbReadFrag {
public: 
	pdbReadFrag();
	~pdbReadFrag();

	void printStats();
	void readFrag(ifstream inFile);

  /** I don't like the name of this function...but any way this is the vector that holds the fragment data (from PDB)
      You then pass the entire pdbReadFrag object to the fragment Factory to have a fragment returned to you.
  */
	vector< string > frag;

  void  setData( vector< string > data);

  string  getName();
  int     getNum();
  void    setName(string name);
  void    setNum(string setNum);
private:
  string  name;
  int  num;
};

#endif





































