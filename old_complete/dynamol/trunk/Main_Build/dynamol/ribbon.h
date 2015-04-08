/***************************************************************************
                          ribbon.h  -  description
                             -------------------
    begin                : Tue Nov 18 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef RIBBON_H
#define RIBBON_H

#include <iostream>

using namespace std;

#include "object.h"
#include "enumTypes.h"
//#include "utility.h"

/**
  *@author 
  */

class chain;

struct GuidePoints {
  //vector<float> P1, P2, P3, P4;
  float P1[3], P2[3], P3[3], P4[3];
};


/** I think that for this class you will eventually want to have the ribbon::ribbon() function call
    the correct function for example ribbon::cartoon || ribbon::flat.  Also why not make
    it so that ribbon::ribbon tkaes molecule * as a parameter so that you can free up the dynamic_cast<>
    clutter in the molView.cpp file????
*/

class ribbon : public Object  {
public: 
	ribbon(chain *ch);
  ribbon(chain *mol, RIBBON_TYPE type);
	~ribbon();

  //personnally thing that you should get rid of this at some point;
  vector<GuidePoints *> allGuidePoints;

  vector<float> colors;
  int numOfSegs;
  //float *seg;
  vector<float> seg;
  vector<float> uKnots;
  vector<float> vKnots;

  int vOrder, uOrder;

  private:
    void flat(chain *ch);
    void cartoon(chain *ch);

    vector< float * > CAatoms;
    vector< float * > Oatoms;
    vector<FRAG_TYPE> type; 
};

#endif





































