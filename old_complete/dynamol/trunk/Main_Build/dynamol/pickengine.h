/***************************************************************************
                          pickengine.h  -  description
                             -------------------
    begin                : Mon Mar 8 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamo.com
 ***************************************************************************/


#ifndef PICKENGINE_H
#define PICKENGINE_H

#include <vector>
using namespace std;

#include "mousesensor.h"


/**
  *@author John Furr
  */

class molView;
class molecule;
class atom;
class molView;
  
class pickEngine {
public: 
	pickEngine(molView *viewer);
	~pickEngine();

  //enum button_state {DOWN, UP};
  void  getHitObjectNumbers(vector<int> &nums, GLint hits, GLuint buffer[]);
  atom *getHit(GLint hits, GLuint buffer[]);
  //void processHits(GLint hits, GLuint buffer[], mouseSensor::button_state shiftState, mouseSensor::button_state cntrlState);
  void processHits(GLint hits, GLuint buffer[], int shiftState, int cntrlState);
  
  void distPicks(GLint hits, GLuint buffer[]);
  void angPicks(GLint hits, GLuint buffer[]);
  void torsionPicks(GLint hits, GLuint buffer[]);
  
  molView *viewer;
  atom *atm1, *atm2, *atm3, *atm4;
};

#endif





































