/***************************************************************************
                          fragfactory.h  -  description
                             -------------------
    begin                : Thu Feb 5 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef FRAGFACTORY_H
#define FRAGFACTORY_H

#include <string>
#include <vector>
using namespace std;

/**
  *@author John Furr
  */

  
class fragment;
class bond;
  
class fragFactory {
public: 
	fragFactory();
	~fragFactory();

  fragment *getNewFrag(string type, vector<string> *fragInfo);

private:
  void checkFrag_2(fragment *frag, vector< string > &fr);

  void buildFrag(fragment *frag, vector<string> &fragInfo);
  //int  getAtomicNum(string name);

  /** This function takes a bond && returns the expected order */
  int detBondOrder(bond *bd);

  /** This is were you will add new error checks 
   * Currently you check for ASN mis assigned as ASP
  */
  void checkResidue(fragment *frag, string &atomType); 
};

#endif





































