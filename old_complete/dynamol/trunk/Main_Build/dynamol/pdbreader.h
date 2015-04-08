/***************************************************************************
                          pdbreader.h  -  description
                             -------------------
    begin                : Fri May 2 2003
    copyright            : (C) 2003 by John Furr
    email                : john.furr@dynamol.com
 ***************************************************************************/


#ifndef PDBREADER_H
#define PDBREADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>


using namespace std;

class protein;
class chain;
class pdbReadChain;
class pdbReadFrag;
class fragment;

/**
  *@author John Furr
  */

class pdbReader {
public: 
	pdbReader(string fileName);
  pdbReader();

  void readPDB(string fileName, list<protein *> &protList);
  protein *readProtein(ifstream &inFile, string &line);
  chain   *readChain(ifstream &inFile, string &line);
  fragment      *readFrag(ifstream &inFile, string &line);
	~pdbReader();

	void printStats();

public:
	vector< pdbReadChain * >  chains;
	vector< pdbReadFrag *>    Fragment;
	vector<string>            conectVec;
};

#endif





































