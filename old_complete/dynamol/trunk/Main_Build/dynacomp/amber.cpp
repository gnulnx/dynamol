/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#include "amber.h"

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "angle.h"
#include "torsion.h"
#include "nonbond.h"

//Dynamol Base Library Includes
#include "../dynabase/utility.h"

namespace dynacomp {

amber::amber()
{
   errorMsg = "";  

   #ifdef LINUX
      Path = getenv("DYNAMOL");
      Path += "/ForceField/parm99.dat";
   #endif

   #ifdef WINDOWS
      Path = "..\\ForceField\\parm99.dat";
   #endif

   if ( !readParamFile() ) {
      cout <<Path <<" was not found"<<endl;
      //QMessageBox::critical(0, "Dynamol", "Params not read");
   }
}


amber::~amber()
{
}

string amber::getErrorMsg()
{ return errorMsg; }

bool amber::setGAFFTypes(bool onlyType, molecule *mol) {
//This function will label atoms according to the GAFF parper.
//It will label an atom type as w if it doesn't find the correct type
   //////qDebug("amber::setGAFFTypes");
   int badIndex = -1;
   if (!setBonds(mol->bonds, badIndex)) {
      return false;
   }
   if (!setAngles(mol->angles, badIndex) ) {
      return false;
   }
   if (!setNonBonds(mol, badIndex) ) {
      return false;
   }
   if (!setTorsions(mol->torsions, badIndex) ) {
      return false;
   }
  
  mol->ffTypes = "GAFF";
  return true;
}



bool amber::setBonds(vector<bond *> &Bonds, int &badIndex) {
   badIndex = -1;

   string b1, b2;
   float K, len;
   K=len=0;
   
   for (int i=0; i<Bonds.size(); i++) {
      bond *bd = Bonds[i];
      string fFFType = bd->fromAtom()->getFFType();
      string tFFType = bd->toAtom()->getFFType();
      atom *fAtm = bd->fromAtom();
      atom *tAtm = bd->toAtom();
      
      while ( true ) {
         bool tmp = getBondParam(fFFType, tFFType, bd);
         if (tmp) {
	    break;
	 }
         else {
            vector<string> front; front.push_back(fFFType);
            possTypes(fFFType, front);
            vector<string> back;  back.push_back(tFFType);
            possTypes(tFFType, back);
            bool stop = true;
            for (int i=0; i<front.size(); i++) {
               for (int j=0; j<back.size(); j++) {
                  if (getBondParam(front[i], back[j], bd) ) {
                     stop = false;
                     break;
                  }
               }
               if (!stop) break;
            }
                             
            if (stop) {
               string sFrom = dynabase::setNum(fAtm->getNum());
               string sTo = dynabase::setNum(tAtm->getNum());
               errorMsg = "Bond Type Error|dynacomp::amber::setBonds|";
               errorMsg+="(" + sFrom + "-" + fAtm->getFFType() + " -- ";
               errorMsg+= sTo + "-" + tAtm->getFFType() + ")";

               badIndex = i;
               return false;
            }
            else {
               break;
            }
        }
     }
   }
   return true;
}

bool amber::getBondParam(string &fFFType, string &tFFType, bond *bd) {
   bool bondMatch = false;
   string b1, b2;
   float K, len;
   K=len=0;
   for (int j=0; j<bdParams.size(); j++) {
      if (bdParams[j][1] == ' ') b1 = bdParams[j].substr(0,1);
      else b1 = bdParams[j].substr(0,2);
      if (bdParams[j][4] == ' ') b2 = bdParams[j].substr(3,1);
      else b2 = bdParams[j].substr(3,2);
      K = atof(bdParams[j].substr(6,6).c_str());
      len = atof(bdParams[j].substr(16, 5).c_str());
      if (fFFType == b1 && tFFType == b2) {bondMatch = true; break;}
      else if (fFFType == b2 && tFFType == b1) {bondMatch = true; break;}	
   }
	
   if (bondMatch) {
      bd->refLen = len;
      bd->K = K;
      return true;
   }
	
   if (empiricalBond(bd, bdParams)) return true;
   else return false;
}

bool amber::empiricalBond(bond *bd, vector<string> &bdParams) {
	string fFFType = bd->fromAtom()->getFFType();
	string tFFType = bd->toAtom()->getFFType();
	
	float K1, K2, len1, len2;
	string b1, b2;
	int count = 0;
	for (int j=0; j<bdParams.size(); j++) {
	if (bdParams[j][1] == ' ') b1 = bdParams[j].substr(0,1);
		else b1 = bdParams[j].substr(0,2);
		if (bdParams[j][4] == ' ') b2 = bdParams[j].substr(3,1);
		else b2 = bdParams[j].substr(3,2);
		
		string Kstr = bdParams[j].substr(6,6);
		string lenStr = bdParams[j].substr(16, 5); 
		
		float K = atof(Kstr.c_str());
		float len = atof(lenStr.c_str());
		
		if (fFFType == b1 && fFFType == b2) {
		   K1 = K;
		   len1 = len;
		   count++;
		}
		if (tFFType == b2 && tFFType == b1) {
		   K2 = K;
		   len2 = len;
		   count++;
		}
		
		if (count == 2) {
		   bd->refLen = (len1+len2)/2;
		   bd->K = (K1+K2)/2;
		   return true;
		}
	}
	return false;
}


bool amber::setAngles(vector<anglePtr> &Angles, int &badIndex) {
   badIndex = -1;

   for (int i=0; i<Angles.size(); i++) {
      //angle *ang = Angles[i];
      anglePtr ang = Angles[i];
      vector<string> angStr(3);
      //vector<string> angStr1, angStr2, angStr3;
      //angStr1.push_back(ang->front->ff_type);
      //angStr2.push_abck(ang->mid->ff_type);
      //angStr3.push_back(ang->back->ff_type);
      angStr[0] = ang->front->getFFType();
      angStr[1] = ang->mid->getFFType();
      angStr[2] = ang->back->getFFType();
        
      while ( true ) {
         bool tmp = getAngleParam(angStr[0], angStr[1], angStr[2], ang);
         if (tmp) {
	    break;
	 }
         else {
            vector<string> front; front.push_back(angStr[0]);
            possTypes(angStr[0], front);
            vector<string> mid;   mid.push_back(angStr[1]);
            possTypes(angStr[1], mid);
            vector<string> back;  back.push_back(angStr[2]);
            possTypes(angStr[2], back);
	    molecule *mol = ang->front->getParent();
            bool stop = true;
            for (int i=0; i<front.size(); i++) {
               for (int j=0; j<mid.size(); j++) {
                  for (int k=0; k<back.size(); k++) {
                     if (getAngleParam(front[i], mid[j], back[k], ang) ) {
                        stop = false;
                        break;
                     }
                  }
                  if (!stop) break;
               }
               if (!stop) break;
            }
              
               
            if (stop) {
               string sFront = dynabase::setNum(ang->front->getNum());
               string sMid = dynabase::setNum(ang->mid->getNum());
               string sBack = dynabase::setNum(ang->back->getNum());
               errorMsg = "Angle Type Error|dynacomp::amber::setAngles|";
               errorMsg +="(" + sFront + "-" + ang->front->getFFType() + " -- ";
               errorMsg += sMid + "-" + ang->mid->getFFType() + " -- ";
               errorMsg += sBack + "-" + ang->back->getFFType() + ")";
               badIndex = i;
               return false;
            }
            else {
               break;
            }
        }
     }  
   }
   return true;
}



bool amber::getAngleParam(string  &fFFType, string &mFFType, string &bFFType, anglePtr ang) {
   string a1, a2, a3;
   float K, deg;
   K=deg=0;
   for (int j=0; j<angParams.size(); j++) {
      a1 = a1Vec[j];
      a2 = a2Vec[j];
      a3 = a3Vec[j];
      K = KVec[j];
      deg = degVec[j];
	
      bool leave = false;
      if (a1 == fFFType && a2 == mFFType && a3 == bFFType) {  
         leave =  true; 
      }
      if (a3 == fFFType && a2 == mFFType && a1 == bFFType) {
         leave = true;	
      }
      if (leave) {
      	ang->K = KVec[j];
        ang->refAngle = degVec[j];
	return true;
      }
   }

   if (empricalAngle(ang, fFFType, mFFType, bFFType, angParams) ) {
   	return true;
   }
   else return false;
}


bool amber::empricalAngle(anglePtr ang, string &f, string &m, string &b, vector<string> &angParams) {

   //First lets check to see if the angle is indeed ABA && CBC angles are [resent
   string fFFType = f;
   string mFFType = m;
   string bFFType = b;
	
          
   bool angleMatch = false;
   string a1, a2, a3;
   float K1, K2, deg1, deg2;
   K1=K2=deg1=deg2=0;
   int count = 0;
   bool first = false;
   bool second = false;

   for (int j=0; j<angParams.size(); j++) {
      if (angParams[j][1] == ' ') a1 = angParams[j].substr(0,1);
      else a1 = angParams[j].substr(0,2);
      if (angParams[j][4] == ' ') a2 = angParams[j].substr(3,1);
      else a2 = angParams[j].substr(3,2);
      if (angParams[j][7] == ' ') a3 = angParams[j].substr(6,1);
      else a3 = angParams[j].substr(6,2);
		
      string Kstr = angParams[j].substr(9,8);
      string degStr = angParams[j].substr(20, 9); 
		
      float K = atof(Kstr.c_str());
      float deg = atof(degStr.c_str()); 
		          
      if (a1 == fFFType && a2 == mFFType && a3 == fFFType) {
         K1 = K;
         deg1 = deg;
         first = true;
	 count++; 
      }
      if (a1 == bFFType && a2 == mFFType && a3 == bFFType) { 
         K2 = K;
	 deg2 = deg;
         second = true;
	 count++;
      }
   }
	
   if (first && second) {
      ang->refAngle = (deg1+deg2)/2;
		
      //######### NOTE   IMPORTANT  This is not the correct way to empirically get the force constant for angle bending.
      // Howver it should work just fine for many many simple things.
      ang->K = (K1+K2)/2;
      return true;
   }
		
   return false;
}


bool amber::setTorsions(vector<torPtr> &Torsions, int &badIndex) {
   for (int i=0; i<Torsions.size(); i++) {
      torPtr tor = Torsions[i];
      string fType1 = tor->atm1->getFFType();
      string fType2 = tor->atm2->getFFType();
      string fType3 = tor->atm3->getFFType();
      string fType4 = tor->atm4->getFFType();
     
      if (!getTorsionParam(fType1, fType2, fType3, fType4, i, Torsions)) {
         string sFront = dynabase::setNum(tor->atm1->getNum());
         string sMid1 = dynabase::setNum(tor->atm2->getNum());
         string sMid2 = dynabase::setNum(tor->atm3->getNum());
         string sBack = dynabase::setNum(tor->atm4->getNum());
         errorMsg = "Torsion Type Error|dynacomp::amber::setTorsions|";
         errorMsg +="(" + sFront + "-" + tor->atm1->getFFType() + " -- ";
         errorMsg += sMid1 + "-" + tor->atm2->getFFType() + " -- ";
         errorMsg += sMid2 + "-" + tor->atm3->getFFType() + " -- ";
         errorMsg += sBack + "-" + tor->atm4->getFFType() + ")";

         return false;
      }
   }
   //int test =0;
   //cin >> test;
   return true;
}

bool amber::getTorsionParam(string &fType1, string &fType2, string &fType3, string &fType4, int pos, vector<torPtr> &Torsions) 
{
   torPtr tor = Torsions[pos];
   if (!tor->improper) {
      string torName;
      map<string, torDef>::iterator it;
      torName = fType1+'-'+fType2+'-'+fType3+'-'+fType4;
      it = TOR_DEF.find(torName);

      if (it == TOR_DEF.end()) {
         torName =fType4+'-'+fType3+'-'+fType2+'-'+fType1;
         it = TOR_DEF.find(torName);
      }
      if (it == TOR_DEF.end()) {
         torName = "X-"+fType3+'-'+fType2+"-X";
         it = TOR_DEF.find(torName);
      }
      if (it == TOR_DEF.end()) {
         torName = "X-"+fType2+'-'+fType3+"-X";
         it = TOR_DEF.find(torName);
      }
      if (it != TOR_DEF.end()) {
         tor->V = it->second.PK[0]/it->second.IDIV[0];
         tor->n = it->second.PERIOD[0];
         tor->gamma = it->second.PHASE[0];
         return true;
      } else {
        return false;
      }
   } else if (tor->improper) {
      
      string torName;
      map<string, torDef>::iterator it;
      torName = fType1+'-'+fType2+'-'+fType3+'-'+fType4;
      it = TOR_IMP.find(torName);
      if (it == TOR_IMP.end() ) {
         torName = fType2+'-'+fType1+'-'+fType3+'-'+fType4;
         it = TOR_IMP.find(torName);
      }
      if (it == TOR_IMP.end() ) {
         torName = fType1+'-'+fType4+'-'+fType3+'-'+fType2;
         it = TOR_IMP.find(torName);
      }
      if (it == TOR_IMP.end() ) {
         torName = fType2+'-'+fType4+'-'+fType3+'-'+fType1;
         it = TOR_IMP.find(torName);
      }
      if (it == TOR_IMP.end() ) {
         torName = "X-"+fType1+'-'+fType3+'-'+fType2;
         it = TOR_IMP.find(torName);
      }
      if (it == TOR_IMP.end() ) {
         torName = "X-"+fType1+'-'+fType3+'-'+fType4;
         it = TOR_IMP.find(torName);
      }
      if (it == TOR_IMP.end() ) {
         torName = "X-"+fType2+'-'+fType3+'-'+fType1;
         it = TOR_IMP.find(torName);
      }
      if (it == TOR_IMP.end() ) {
         torName = "X-"+fType2+'-'+fType3+'-'+fType4;
         it = TOR_IMP.find(torName);
      }
      if (it == TOR_IMP.end() ) {
         torName = "X-X-"+fType3+'-'+fType4;
         it = TOR_IMP.find(torName);
      }
      //torName = "X-X-"+fType3+'-'+fType4;
      //it = TOR_IMP.find(torName);
      if (it == TOR_IMP.end() ) {
         torName = "X-X-"+fType3+'-'+fType1;
         it = TOR_IMP.find(torName);
      }
      if (it == TOR_IMP.end() ) {
         torName = "X-X-"+fType3+'-'+fType2;
         it = TOR_IMP.find(torName);
      }
      if (it != TOR_IMP.end()) {
         tor->V = it->second.PK[0]/it->second.IDIV[0];
         tor->n = it->second.PERIOD[0];
         tor->gamma = it->second.PHASE[0];
         return true;
      } else {
         torName = fType1+'-'+fType2+'-'+fType3+'-'+fType4;
         Torsions.erase(Torsions.begin() + pos);
      }
   } 

   return true;
}
/*
bool amber::setTorsions(vector<torsion *> &Torsions, int &badIndex) {
  badIndex = -1;
  //int test = 0;
    
  string at1, at2;

   for (int ii=0; ii<Torsions.size(); ii++) {
      torsion *tor = Torsions[ii];
      atom *atm1 = tor->atm1;
      atom *atm2 = tor->atm2;
      atom *atm3 = tor->atm3;
      atom *atm4 = tor->atm4;
	    
      string fType1 = atm1->getFFType();
      string fType2 = atm2->getFFType();
      string fType3 = atm3->getFFType();
      string fType4 = atm4->getFFType();
      while ( true ) {
           bool tmp = getTorsionParam(fType1, fType2, fType3, fType4, tor);
           if (tmp) {
	      break;
	   }
           else {
               vector<string> front; front.push_back(fType1);
               possTypes(fType1, front);
               vector<string> mid1;   mid1.push_back(fType2);
               possTypes(fType2, mid1);
               vector<string> mid2;   mid2.push_back(fType3);
               possTypes(fType3, mid2);
               vector<string> back;  back.push_back(fType4);
               possTypes(fType4, back);
               
               bool stop = true;
               for (int i=0; i<mid1.size(); i++) {
                  for (int j=0; j<mid2.size(); j++) {
                     if (getTorsionParam(fType1, mid1[i], mid2[j], fType4, tor) ) {
                        stop = false;
                        break;
                     }
                  }
                  if (!stop) break;
               }
               if (!stop) break;
                            
               if (stop) {
                  badIndex = ii;
                  return false;
               }
               else {
                  break;
               }
           }
        }
   }
   return true;
}
*/

/*
bool amber::getTorsionParam(string &fType1, string &fType2, string &fType3, string &fType4, torsion *tor) {
   string v, phase, n;
   string divS;
   float fv, fphase, fn;
   float div = 0;
   bool torMatch = false;
   string at1, at2;
   for (int j=0; j<torParams.size(); j++) {
      if (torParams[j][4] == ' ') 
         at1 = torParams[j].substr(3,1);
      else 
         at1 = torParams[j].substr(3,2);

      if (torParams[j][7] == ' ') 
         at2 = torParams[j].substr(6,1);
      else 
         at2 = torParams[j].substr(6,2);
			
      if (fType2 == at1 && fType3 == at2) 
         {torMatch = true;}
      else if (fType3 == at1 && fType2 == at2) 
         {torMatch = true;}
		
      if (torMatch) {
         divS = torParams[j].substr(14,4);
         v = torParams[j].substr(17, 7);
         phase = torParams[j].substr(30, 8);
         n = torParams[j].substr(47, 7); //Not sure about this guy 
	   
         div = atof(divS.c_str());
         fv = atof(v.c_str());
         fphase = atof(phase.c_str());
		    
         //You should be checking for negative values here
         //You are taking the absolute value...but some torsions
         //will have more than 1 term
         fn = fabs(atof(n.c_str()));
         break;
      }
   }  
   if (torMatch) {
      tor->V = fv/div;
      tor->n = fn;
      tor->gamma = fphase;
      return true;
   } 
   return false;
}
*/

void amber::possTypes(string &type, vector<string> &others) {
   if (type == "C" || type == "CT") {
      others.push_back("CA");
      others.push_back("CB");
      others.push_back("CC");
      others.push_back("CD");
      others.push_back("CK");
      others.push_back("CM");
      others.push_back("CN");
      others.push_back("CT");
   } else
   if (type == "CA" || type == "CB" || type == "CC" || type == "CD" || type == "CE") {
      others.push_back("CA");
      others.push_back("CB");
      others.push_back("CC");
      others.push_back("CD");
      others.push_back("CK");
      others.push_back("CM");
      others.push_back("CN");
   } else
   if (type == "HC") {
      others.push_back("HP");
      others.push_back("H1");
   } else
   if (type == "O" || type == "OH" || type == "O2" || type == "OS") {
      others.push_back("O2");
      others.push_back("OH");
      others.push_back("OS");
   } else
   //This section is for the much more general types
   if (type[0] == 'H') {
      others.push_back("H");
      others.push_back("H1");
      others.push_back("H2");
      others.push_back("H3");
      others.push_back("HP");
      others.push_back("H1");
   } else
   if (type[0] == 'C') {
      others.push_back("CA");
      others.push_back("CB");
      others.push_back("CC");
      others.push_back("CD");
      others.push_back("CK");
      others.push_back("CM");
      others.push_back("CN");
      others.push_back("CT");
   } else
   
   if (type == "N2*") { 
     others.push_back("NA");
     others.push_back("NB");
     others.push_back("NC");
   }

   if (type == "N2") {
     others.push_back("N2*");
     others.push_back("NB");
     others.push_back("NC");
   }

}




bool amber::setNonBonds(molecule *mol, int &badIndex) {
    badIndex = -1;
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      bool found = false;
      for (int j=0; j<nonBondParams.size(); j++) {
         string ffType = atm->getFFType();
         if (atm->getFFType() == nonBondParams[j].substr(2,ffType.size()) ) {
	    string tmp1 = nonBondParams[j].substr(13,7);
	    float min = atof(tmp1.c_str());
	    double div = pow(2.0, 1.0/6.0);
	    float sig = min/div;
            //parm99.dat stores as 0.5*rmin
            //you store as 0.5*sigma to avoid a costly divide
            atm->setSigma(sig);
            tmp1 = nonBondParams[j].substr(22,7);
	    float eps = atof(tmp1.c_str());
            //Epsilonis stored as epslon.  you take the sqrt not to minimize
            //effort later	
            atm->setEpsilon(sqrt(eps));
            found = true;
            break;
         }
      }	
      if (!found) {
      }
   }
   
   return true;
}

int amber::getTotalBondOrder(atom *atm, molecule *mol) {
	int totBondOrder = 0;
	for (int i=0; i<atm->atoms.size(); i++) {
		bond *bd = mol->getBond(atm, atm->atoms[i]);
		if (bd != NULL) totBondOrder += bd->order;
	}
	
	return totBondOrder;
}

bool amber::amideNitrogen(atom *atm, molecule *mol) {
	if (atm->atoms.size() != 3) return false;
	int totOrder = getTotalBondOrder(atm, mol);
	if (totOrder != 3) return false;
	
	for (int i=0; i<atm->atoms.size(); i++) {
		atom *tmp = atm->atoms[i];
		for (int j=0; j<tmp->atoms.size(); j++) {
			if (tmp->atoms[j]->getAtomicNum() == 8 && tmp->atoms[j]->atoms.size() == 1) return true;
		}
	}
	return false;
}

bool amber::nitroNitrogen(atom *atm, molecule *mol) {
	if (atm->getAtomicNum() != 7) return false;
	if (atm->atoms.size() != 3) return false;
	
	int oCount = 0;
	for (int i=0; i<atm->atoms.size(); i++) {
		atom *tmp = atm->atoms[i];
		if (tmp->atoms.size() == 1 && tmp->getAtomicNum() == 8) oCount++;
	}
	if (oCount == 2) return true;
	return false;
}


bool amber::readParamFile() {
   ifstream inFile(Path.c_str(), ios::in);
   if (!inFile) {
      cout <<Path<< " not opened " << endl; 
      return false;
   }
   //READ IN THE BOND STUFF
   string line;
   while (true) {
      getline(inFile, line);
      if (line == "#BOND") {
         getline(inFile, line);
         break;
      }
   }

   bdParams.clear();
  
   while (true) {
      getline(inFile, line);
      if (line == "#ANGLE") break;
      bdParams.push_back(line);
   }
   
   
   //NOW READ IN THE ANGLE SECTION
  angParams.clear();
  a1Vec.clear();
  a2Vec.clear();
  a3Vec.clear();
  KVec.clear();
  degVec.clear();
  string a1, a2, a3;
  float K, deg;
  K=deg=0;
  while (true) {
  	getline(inFile, line);
	if (line == "#TORSION") break;
	angParams.push_back(line);
	if (line[1] == ' ') a1 = line.substr(0,1);
	else a1 = line.substr(0,2);
	if (line[4] == ' ') a2 = line.substr(3,1);
	else a2 = line.substr(3,2);
	if (line[7] == ' ') a3 = line.substr(6,1);
	else a3 = line.substr(6,2);
	
	string Kstr = line.substr(9,8);
	string degStr = line.substr(20, 9); 
	
	K = atof(Kstr.c_str());
	deg = atof(degStr.c_str()); 
	
	a1Vec.push_back(a1);
	a2Vec.push_back(a2);
	a3Vec.push_back(a3);
	KVec.push_back(K);
	degVec.push_back(deg);
  }

   //NOW READ IN THR TORSION PARAMETERS
   torParams.clear();
   bool improper = false;
   while (true) {
      getline(inFile, line);
      if (line == "#IMPROPER") break;
      torParams.push_back(line); //OLDER STUFF

      string tmp = line.substr(0,11);
      stringstream s(line.substr(12, line.size()-1));
      string name = "";
      for (int i=0; i<tmp.size(); i++) 
         if (tmp[i] != ' ')
            name += tmp[i];

      float idiv = 1.0;
      float pk, phase, period;
      s >> idiv >> pk >> phase >> period;

      if (period  > 0) {
      map<string, torDef>::iterator it = TOR_DEF.find(name);
      if (it != TOR_DEF.end() ) {
         it->second.IDIV.push_back(idiv);
         it->second.PK.push_back(pk);
         it->second.PHASE.push_back(phase);
         it->second.PERIOD.push_back(period);
      } else {
         torDef def;
         def.IDIV.push_back(idiv);
         def.PK.push_back(pk);
         def.PHASE.push_back(phase);
         def.PERIOD.push_back( fabs(period) );
         def.improper = improper;
         TOR_DEF[name] = def;
      }
      }
   }

   //IMPROPER TORSION READ
   while (true) {
      getline(inFile, line);
      if (line == "#NONBOND") break;
      torParams.push_back(line); //OLDER STUFF

      string tmp = line.substr(0,11);
      stringstream s(line.substr(12, line.size()-1));
      string name = "";
      for (int i=0; i<tmp.size(); i++) 
         if (tmp[i] != ' ')
            name += tmp[i];

      float idiv = 1.0;
      float pk, phase, period;
      s >> pk >> phase >> period;

      if (period  > 0) {
      map<string, torDef>::iterator it = TOR_IMP.find(name);
      if (it != TOR_IMP.end() ) {
         it->second.IDIV.push_back(idiv);
         it->second.PK.push_back(pk);
         it->second.PHASE.push_back(phase);
         it->second.PERIOD.push_back(period);
      } else {
         torDef def;
         def.IDIV.push_back(idiv);
         def.PK.push_back(pk);
         def.PHASE.push_back(phase);
         def.PERIOD.push_back( fabs(period) );
         def.improper = improper;
         TOR_IMP[name] = def;
      }
      }
   }

   
  //NOW READ IN THE NON BOND STUFF
  nonBondParams.clear();
    while (true) {
    	getline(inFile, line);
	if (line == "#END") break;
	nonBondParams.push_back(line);
    }
 
   inFile.clear();
   inFile.close();
   return true;
}

};//End Namespace





