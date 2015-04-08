/***************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   email:  john.furr@dynamol.com 
 ***************************************/
#include "atom.h"
#include "atomflyweightfactory.h"
#include "math.h"

//Debug Only
#include <iostream>
using namespace std;

namespace dynabase {

//Construct the statically typed atomFlyWeightFactory
atomFlyWeightFactory atom::factory;

atom::atom(int num, string symbol, float x, float y, float z, int AN)
{
   //is = NULL;
   factory.setIntState(this, AN, symbol);
   fCoords[0] = x;
   fCoords[1] = y;
   fCoords[2] = z;
   fCoords[3] = 1;

   this->num = num;
   charge = 0.0;
}


atom::~atom()
{
}

void atom::setSymbol(string symbol)
{ 
   factory.setIntState(
      this, 
      this->getAN(), 
      symbol, 
      this->getFFType(), 
      this->getSigma(), 
      this->getEpsilon()
   );
}

void atom::changeType(int AN, string &symbol) 
{
   factory.setIntState(
      this, 
      AN, 
      symbol, 
      this->getFFType(), 
      this->getSigma(), 
      this->getEpsilon()
   );
}


void atom::setSigma(float sigma)
{
   factory.setIntState(
      this, 
      this->getAN(), 
      this->getSymbol(),
      this->getFFType(),  
      sigma, 
      this->getEpsilon()
   );
};

void atom::setEpsilon(float epsilon)
{
   factory.setIntState(
      this, 
      this->getAN(), 
      this->getSymbol(),
      this->getFFType(),  
      this->getSigma(), 
      epsilon
   );
};

void atom::setFFType(string ff_type)
{
   factory.setIntState(
      this, 
      this->getAN(), 
      this->getSymbol(), 
      ff_type,
      this->getSigma(), 
      this->getEpsilon()
   );
};

}//END namespace

