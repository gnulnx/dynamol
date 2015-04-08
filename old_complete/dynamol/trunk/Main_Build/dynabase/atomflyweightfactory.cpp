/***************************************
 *   Copyright (C) 2005 by Dynamol Inc.
 *   email:  john.furr@dynamol.com 
 ***************************************/
#include "atomflyweightfactory.h"

#include "atomintstate.h"
#include "atom.h"

//Debugging only REMOVE
#include <iostream>
using namespace std;

namespace dynabase {

atomFlyWeightFactory::atomFlyWeightFactory()
{
   //Clear the bits
   preDefinedStates.clear();
}


atomFlyWeightFactory::~atomFlyWeightFactory()
{
   
   //cout <<"atomFlyWeightFactory::~atomFlyWeightFactory(): " << endl;
}

void atomFlyWeightFactory::setIntState(atom *atm,
int AN, string symbol, string ff_type, float sigma, float epsilon) 
{
   atomIntStatePtr atmIs = atm->is;

   atomIntStatePtr is(new atomIntState());
   is->AN = AN;

   //These are your dynamic intrinsic state variables
   is->symbol = symbol;
   is->ff_type = ff_type;
   is->sigma = sigma;
   is->epsilon = epsilon;
 
   for (unsigned int i=0; i<preDefinedStates.size(); i++) {
      if (*is == *preDefinedStates[i]) {
         atm->is = preDefinedStates[i];
         return;
      }
   }

   is->Name = getName( AN );
   is->mass = getAtomicMass( AN );
   is->radii = getvdwRadii( AN );
   atm->is = is;
   preDefinedStates.push_back(is);
}

float atomFlyWeightFactory::getAtomicMass(int atomicNum) {
   if (atomicNum == 1)
        return  1.008;
   else if (atomicNum == 2)
        return  4.003;
   else if (atomicNum == 3)
        return  6.941;
   else if (atomicNum == 4)
        return  9.012;
   else if (atomicNum == 5)
        return  10.81;
   else if (atomicNum == 6)
        return  12.01;
   else if (atomicNum == 7)
        return  14.01;
   else if (atomicNum == 8)
        return  16.00;
   else if (atomicNum == 9)
        return  19.00;
   else if (atomicNum == 10)
        return  20.18;
   else if (atomicNum == 11)
        return  22.99;
   else if (atomicNum == 12)
        return  24.31;
   else if (atomicNum == 13)
        return  26.98;
   else if (atomicNum == 14)
        return  28.09;
   else if (atomicNum == 15)
        return  30.97;
   else if (atomicNum == 16)
        return  32.07;
   else if (atomicNum == 17)
        return  35.45;
   else if (atomicNum == 18)
        return  39.95;
   else if (atomicNum == 19)
	return 39.10;
   else if (atomicNum == 20)
 	return 40.08;
   else if (atomicNum == 21)
	return 44.96;
   else if (atomicNum == 22)
	return 47.88;
   else if (atomicNum == 23)
	return 50.94;
   else if (atomicNum == 24)
	return 52.00;
   else if (atomicNum == 25)
	return 54.94;
   else if (atomicNum == 26)
	return 55.85;
   else if (atomicNum == 27)
  	return 58.93;
   else if (atomicNum == 28)
	return 58.69;
   else if (atomicNum == 29)
	return 63.55;
   else if (atomicNum == 30)
	return 65.39;
   else if (atomicNum == 31)
	return 66.72;
   else if (atomicNum == 32)
	return 72.59;
   else if (atomicNum == 33)
	return 74.92;
   else if (atomicNum == 34)
	return 78.96;
   else if (atomicNum == 35)
   	return 79.90;
   else if (atomicNum == 36)
	return 83.80;
   else if (atomicNum == 37)
	return 85.47;
   else if (atomicNum == 38)
	return 87.62;
   else if (atomicNum == 39)
	return 88.91;
   else if (atomicNum == 40)
	return 91.22;
   else if (atomicNum == 41)
	return 92.91;
   else if (atomicNum == 42)
 	return 95.94;
   else if (atomicNum == 43)
	return 98.0;
   else if (atomicNum == 44)
	return 101.1;
   else if (atomicNum == 45)
	return 102.9;
   else if (atomicNum == 46)
	return 106.4;
   else if (atomicNum == 47)
	return 107.9;
   else if (atomicNum == 48)
	return 112.4;
   else if (atomicNum == 49)
	return 114.8;
   else if (atomicNum == 50)
	return 118.7;
   else if (atomicNum == 51)
	return 121.8;
   else if (atomicNum == 52)
	return 127.6;
   else if (atomicNum == 53)
	return 126.9;
   else if (atomicNum == 54)
	return 131.3;
   else if (atomicNum == 55)
	return 132.9;
   else if (atomicNum == 56)
	return 137.3;
   else if (atomicNum == 57)
	return 138.9;
   else if (atomicNum == 58)
	return 140.1;
   else if (atomicNum == 59)
	return 140.9;
   else if (atomicNum == 60)
	return 144.2;
   else if (atomicNum == 61)
	return 147;
   else if (atomicNum == 62)
	return 150.4;
   else if (atomicNum == 63)
	return  152.0;
   else if (atomicNum == 64)
	return 157.3;
   else if (atomicNum == 65)
	return 158.9;
   else if (atomicNum == 66)
	return 162.5;
   else if (atomicNum == 67)
	return 164.9;
   else if (atomicNum == 68)
	return 167.3;
   else if (atomicNum == 69)
	return 168.9;
   else if (atomicNum == 70)
	return 173.0;
   else if (atomicNum == 71)
	return 175.0;
   else if (atomicNum == 72)
	return 178.5;
   else if (atomicNum == 73)
	return 180.9;
   else if (atomicNum == 74)
	return 183.9;
   else if (atomicNum == 75)
	return 186.2;
   else if (atomicNum == 76)
	return 190.2;
   else if (atomicNum == 77)
	return 190.2;
   else if (atomicNum == 78)
	return 195.1;
   else if (atomicNum == 79)
 	return 197.0;
   else if (atomicNum == 80)
	return 200.5;
   else if (atomicNum == 81)
	return 204.4;
   else if (atomicNum == 82)
	return 207.2;
   else if (atomicNum == 83)
	return 209.0;
   else if (atomicNum == 84)
	return 210;
   else if (atomicNum == 85)
	return 210;
   else if (atomicNum == 86)
	return 222;
   else if (atomicNum == 87)
	return 223;
   else if (atomicNum == 88)
	return 226;
   else if (atomicNum == 89)
	return 227;	
   else if (atomicNum == 90)
	return 232.0;
   else if (atomicNum == 91)
	return 231;
   else if (atomicNum == 92)
	return 238;
   else if (atomicNum == 93)
	return 237;
   else if (atomicNum == 94)
	return 242;
   else if (atomicNum == 95)
	return 243;
   else if (atomicNum == 96)
	return 247;
   else if (atomicNum == 97)
	return 247;
   else if (atomicNum == 98)
	return 249;
   else if (atomicNum == 99)
	return 254;
   else if (atomicNum == 100)
	return 253;
   else if (atomicNum == 101)
	return 256;
   else if (atomicNum == 102)
	return 254;
   else if (atomicNum == 103)
	return 257;
   else if (atomicNum == 104)
	return 257;
   else if (atomicNum == 105)
	return 260;
   else if (atomicNum == 106)
	return 263;
   else if (atomicNum == 107)
	return 262;
   else if (atomicNum == 108)
	return 265;
   else if (atomicNum == 109)
	return 266;
   else if (atomicNum == 110)
	return 271;
   else if (atomicNum == 111)
	return 272;
   else if (atomicNum == 112)
	 return  277;

   //Return -1 on bad atomic number
   return -1;
}

float atomFlyWeightFactory::getvdwRadii(int atomicNum) {
  if (atomicNum == 1) {
    return 1.20;
  } else if (atomicNum == 6) {
    return 1.70;
  } else if (atomicNum == 7) {
    return 1.55;
  } else if (atomicNum == 8) {
    return 1.52;
  } else if (atomicNum == 16) { //Sulfer
    return 1.80;
  } else if (atomicNum == 15) { //Phos
    return 1.80;
  } else if (atomicNum == 9) { //Flourine
    return 1.47;
  } else if (atomicNum == 17) { //Chlorine
    return 1.75;
  } else if (atomicNum == 35) { //Bromine
    return 1.85;
  } else if (atomicNum == 53) { //Iodine
    return 1.98;
  } else if (atomicNum == 47) { //(Au)
    return 1.72;
  } else if (atomicNum == 18) { //(Ar)
    return 1.88;
  } else if (atomicNum == 33) { //(As)
    return 1.85;
  } else if (atomicNum == 79) { //A (Au)
    return 1.66;
  } else if (atomicNum == 48) { //(Ar)
    return 1.58;
  } else if (atomicNum == 29) { //(Ar)
    return 1.40;
  } else if (atomicNum == 31) { //(Ga)
    return 1.87;
  } else if (atomicNum == 2) { // (He)
    return 1.40;
  } else if (atomicNum == 80) { // (He)
    return 1.55;
  } else if (atomicNum == 49) { // (In)
    return 1.93;
  } else if (atomicNum == 19) { // (K)
    return 2.75;
  } else if (atomicNum == 36) { // (Kr)
    return 2.02;
  } else if (atomicNum == 3) { // (Li)
    return 1.82;
  } else if (atomicNum == 12) { // (Mg)
    return 1.73;
  } else if (atomicNum == 11) { // (Na)
    return 2.27;
  } else if (atomicNum == 10) { // (Ne)
    return 1.54;
  } else if (atomicNum == 28) { // (Ni)
    return 1.63;
  } else if (atomicNum == 82) { // (Pb)
    return 2.02;
  } else if (atomicNum == 46) { // (Pd)
    return 1.63;
  } else if (atomicNum == 78) { // (Pt)
    return 1.72;
  } else if (atomicNum == 34) { // (Se)
    return 1.90;
  } else if (atomicNum == 14) { // (Si)
    return 2.10;
  } else if (atomicNum == 50) { // (Sn)
    return 2.17;
  } else if (atomicNum == 52) { // (Te)
    return 2.06;
  } else if (atomicNum == 22) { // (Ti)
    return 1.96;
  } else if (atomicNum == 92) { // (U)
    return 1.86;
  } else if (atomicNum == 54) { // (Xe)
    return 2.16;
  } else if (atomicNum == 30) { // (Zn)
    return 1.39;
  } else {
    return 1.2; //default size is the same as hydrogen
  }
}

string atomFlyWeightFactory::getName(int atomicNum) {
   if (atomicNum == 1 )
	return "Hydrogen";
   if (atomicNum == 6)
	return "Carbon";
   if (atomicNum == 7)
	return "Nitrogen";
   if (atomicNum == 8)
	return "Oxygen";

   //default return type
   return "None";

}

}

