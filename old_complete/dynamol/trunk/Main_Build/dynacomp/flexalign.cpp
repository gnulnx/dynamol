/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   email:  john.furr@dynamol.com
 ***************************************************************************/
#include "flexalign.h"
#include <iostream>
#include <iomanip>
#include <set>
using std::cout;
using std::endl;
using std::setw;
using std::set;

#include "molecule.h"
#include "atom.h"

//Dynamol Base Library Includes
#include "../dynabase/utility.h"

//Dynamol Type Library Includes
#include "../dynatype/molecule.h"
#include "../dynatype/dtype.h"

//Dynamol Convert Library
#include "../convert/convert.h"

//C Includes
#include <math.h>
#include <time.h>

//Dyamol Computational Library Includes
#include "forcefield.h"
#include "conformation.h"
#include "compute.h"
#include "molecule.h"
#include "energy.h"


namespace dynacomp {

//############ BEGIN flexAlign Section ###########
flexAlign::flexAlign()
{
	stop = false;
	Energy = new energy();
   
	//create the exp lookup table
	expLookup.resize(20000);
	for (double i=0; i<2000; i+=.1) {
		expLookup[i] = exp(-0.8*i);
	}
  
	chargeType = "AM1-BCC-fast";
	chgW = 1.0;
	sigW = 1.0;
	aroW = 1.0;
	maxMD = 5000;
	maxMin = 5000;
	Iter = 10;
	tempFlex = false; 
	//aso = new alignSwarmOptimizer();
	srand( time(NULL) );
}


flexAlign::~flexAlign()
{
	delete Energy;
}

void flexAlign::setInfoText(vector<string> &infoText) {
	this->infoText = &infoText;
	Energy->setInfoText(infoText);
}


void flexAlign::setTemplateMolecule(molecule *mol) {
	cout <<"flexAlign::setTemplateMolecule"<<endl;
	templ = mol;
	if (templ->chargeType != chargeType)
		prepMolecule(templ);
	
	//cout <<"HERE 1"<<endl;
	//Determine the median of mass
	set<float> xSet, ySet, zSet;
	float xAvg, yAvg, zAvg;
	xAvg = yAvg = zAvg = 0;
	for (int i=0; i<mol->atoms.size(); i++) {
		float *cd = mol->atoms[i]->fCoords;
		xSet.insert(cd[0]);
		ySet.insert(cd[1]);
		zSet.insert(cd[2]);
      
		xAvg += cd[0];
		yAvg += cd[1];
		zAvg += cd[2];
	}
   
	//cout << "HERE 2"<<endl;
	vector<float> xVec(xSet.begin(), xSet.end());
	vector<float> yVec(ySet.begin(), ySet.end());
	vector<float> zVec(zSet.begin(), zSet.end());

	int xMid = xVec.size()/2;
	int yMid = yVec.size()/2;
	int zMid = zVec.size()/2;
	cout <<"Returning"<<endl;
}

void flexAlign::setMoleculeToAlign(molecule *mol) {
	toAlign = mol;
	if (toAlign->chargeType != chargeType)
		prepMolecule(toAlign); 

}

void flexAlign::copyCurrent() {
	prevCoords.clear();
	for (int i=0; i<toAlign->atoms.size(); i++) {
		float *cd = toAlign->atoms[i]->fCoords;
		for (int j=0; j<3; j++) 
			prevCoords.push_back(cd[j]);
	}
}

void flexAlign::restoreCoords() {
	int count = 0;
	for (int i=0; i<toAlign->atoms.size(); i++) {
		float *cd = toAlign->atoms[i]->fCoords;
		for (int j=0; j<3; j++) {
			cd[j] = prevCoords[count];
			count++;
		}
	}  
}


void flexAlign::randMol(molecule *mol, molecule *mol1) {
	Conformation C;
	vector<bond *> rotBonds;
	C.setRotableBonds(mol, rotBonds);
	for (int i=0; i<rotBonds.size(); i++) {
		float num = rand() % 360;
		if (rand() % 2 > 0)
			C.rotateBond(mol, rotBonds[i], num);
	}

	//Energy->setUp(mol, "CG", "GAFF", "Current", 50, 0.0, 0.0, 0.0);
	//Energy->run()`;

	for (int i=0; i<5; i++) {
		float x = rand() % 100000;
		float y = rand() % 100000;
		float z = rand() % 100000;
		x /= 100000;
		y /= 100000;
		z /= 100000;
		float num = rand() % 360;
		C.rotMolecule(mol, x, y, z, num); 
	}
}
  
bool flexAlign::prepMolecule(molecule *mol) {
	cout <<"flexAlign::prepMolecule" << endl;
	if (infoText != NULL) {
		infoText->clear();
		infoText->push_back("Calculating Charges");
	}
	//Set the Atom Types
	//dt::molecule *dtmol = new dt::molecule;
	dt::molPtr dtmol( new dt::molecule );
	dt::convert::toDynatype(dtmol, mol);
	dt::dType d;
	d.setGaffTypes(dtmol);
	dt::convert::update(mol, dtmol);
	
	//delete dtmol;
	//Calculate Charges
	if (!Compute::charges(mol, chargeType)) {
		cout <<"Could not calculate charges"<<endl;
		return false;
	}
	
	//Set bond, angle, torsion, and nonBond terms
	forceField *ff = new forceField();
	string ffType = "GAFF";
	ff->buildLists(mol, ffType );
	delete ff;

	cout <<"Returning from flexAlign::prepMolecule"<<endl;	
	return true;
}  

void flexAlign::clearCurrentSet() {
	allAtoms.clear();
	allBonds.clear();
	allAngles.clear();
	allTors.clear();
	allNB.clear();
}

void flexAlign::addMolToSet(molecule *mol) {
	for (int i=0; i<mol->atoms.size(); i++) {
		allAtoms.push_back(mol->atoms[i]);
	}
	for (int i=0; i<mol->bonds.size(); i++) {
		allBonds.push_back(mol->bonds[i]);
	}
	for (int i=0; i<mol->angles.size(); i++) {
		allAngles.push_back(mol->angles[i]);
	}
	for (int i=0; i<mol->torsions.size(); i++) { 
		allTors.push_back(mol->torsions[i]);
	}
	for (int i=0; i<mol->nonBonds.size(); i++) {
		allNB.push_back(mol->nonBonds[i]);
	}
}

void flexAlign::setUp(map<string, string> Params) {
	this->Params = Params;
	map<string, string>::iterator mi = Params.begin();
	for (mi; mi != Params.end(); mi++) {
		if (mi->first == "aroWeight")
			aroW = dynabase::toNum(mi->second);
		if (mi->first == "chgWeight")
			chgW = dynabase::toNum(mi->second);
		if (mi->first == "volWeight")
			sigW = dynabase::toNum(mi->second);
		if (mi->first == "maxMD")
			maxMD = dynabase::toNum(mi->second);
		if (mi->first == "maxMin")
			maxMin = dynabase::toNum(mi->second);
		if (mi->first == "dielec") {
			dielec = dynabase::toNum(mi->second);
			Energy->dieSetup("Constant", dielec);
		}
		if (mi->first == "poses")		
			poseNum = dynabase::toNum(mi->second);
		if (mi->first == "poseRMSE")
			poseRMSE = dynabase::toNum(mi->second);
		if (mi->first == "rmseCoords")
			rmseCoords = dynabase::toNum(mi->second);
		if (mi->first == "tanTerm") {
			tanTerm = dynabase::toNum(mi->second);
			if (tanTerm > 1)
				tanTerm /= 100.0;
		}
		if (mi->first == "chargeType")
			chargeType = mi->second;
		if (mi->first == "Iter")
			Iter = dynabase::toNum(mi->second);
		if (mi->first == "tempFlex") 
			tempFlex = dynabase::toNum(mi->second);
		if (mi->first == "dynIter")
			dynIter = dynabase::toNum(mi->second);
		if (mi->first == "annealPercent") {
			annealPercent = dynabase::toNum(mi->second);
			annealPercent = annealPercent/100.0;
		}
		if (mi->first == "rmse")
			rmse = dynabase::toNum(mi->second);
		if (mi->first == "maxForce")
			maxForce = dynabase::toNum(mi->second);
		if (mi->first == "minE")
			minE = dynabase::toNum(mi->second);
		if (mi->first == "MinOnly")
			MinOnly = dynabase::toNum(mi->second);	
	}

	// Uncomment to print the Setup Parameters
	//PrintParams();
}

void flexAlign::PrintParams() {
	cout <<"FelxAlign SetUp Params"<<endl;
	cout <<"aroWeight: " << "\t" << aroW << endl;
	cout <<"chgWeight: " << "\t" << chgW << endl;
	cout <<"volWeight: " << "\t" << sigW << endl;
	cout <<"maxMD    : " << "\t" <<  maxMD << endl;
	cout <<"maxMin   : " << "\t" << maxMin << endl;
    cout <<"dielec   : " << "\t" << dielec << endl;  
	cout <<"Poses    : " << "\t" << poseNum <<endl;
	cout <<"poseRMSE : " << "\t" << poseRMSE << endl;
	cout <<"rmseCoords:" << "\t" << rmseCoords << endl;
	cout <<"tanTerm  : " << "\t" << tanTerm << endl;
	cout <<"chargeType:" << "\t" << chargeType << endl;
	cout <<"Iter     : " << "\t" << Iter << endl;
	cout <<"tempFlex : " << "\t" << tempFlex << endl;
	cout <<"dynIter  : " << "\t" << dynIter << endl;
	cout <<"anneal % : " << "\t" << annealPercent << endl;	
	cout <<"rmse     : " << "\t" << rmse << endl;
	cout <<"maxForce : " << "\t" << maxForce << endl;
	cout <<"minE     : " << "\t" << minE << endl;
	cout <<"MinOnly  : " << "\t" << MinOnly << endl;
	//int test =0;
	//cin >> test;
}

bool flexAlign::run(multimap<float, vector<float> > &poseMap) {
	cout <<"flexAlign::run"<<endl;
	time_t t1 = time(NULL);
	vector<float> bestCoords;
	bestTan = -1000;
	copyCurrent();
	clearCurrentSet();
	addMolToSet(toAlign); 

	//tempFlex is set to true the we will add the template molecue
	//to the set of molecules that will be flexed
	if (tempFlex)
		addMolToSet(templ);

	float aroHold = aroW;
	float sigHold = sigW;
	float chgHold = chgW;
   
	for (int i=0; i<Iter; i++) {
		aroW = aroHold;
		sigW = sigHold;
		sameW = 0.0;
		chgW = chgHold;
		if (tempFlex)
			temp = 1;
		else 
			temp = 1;

		alpha = .20;

		molecule *mol = new molecule;
		Energy->setAtoms(allAtoms);
		Energy->setBonds(allBonds);
		Energy->setAngles(allAngles);
		Energy->setTorsions(allTors);
		Energy->setNonBonds(allNB);

		//Calculate Initial tanimoto score
			
		//float tan = tanimoto(templ, toAlign);
		//savePose(poseMap, rmseCoords,tan);
		//Minimize the input molecules with alignement parametners
		minimize(toAlign, 5000, rmse, maxForce, minE);	
		//Save the minimized structure
		float tan = tanimoto(templ, toAlign);
	
		savePose(poseMap, rmseCoords,tan);
		
		if (MinOnly)
			return 1;

		alignCenters(templ, toAlign);
		Energy->CG_minimize(500, rmse, maxForce, minE);
		
		//cout <<"minE: " << minE <<endl;
		//int test3=0;
		//cin >> test3;
	
		vector<float> energies(6);
		if (!leapfrog(toAlign, maxMD)) {
			cout <<"leapfrog failed"<<endl;
			int test3=0;
			cin >> test3;
			restoreCoords();
			//cout <<"HERE 4"<<endl;
			minimize(toAlign, 100, rmse, maxForce, minE);
			i--;
		}  else {
			aroW = 1;
			sigW = 1;
			sameW = 1.0;
			chgW = 1;
			temp = 1;
			alpha = .80;

			//cout <<"HERE 5"<<endl;
			minimize(toAlign, maxMin, rmse, maxForce, minE);
			//cout <<"HERE 6"<<endl;

			float tan = tanimoto(templ, toAlign);
			cout <<"Current Tan: " << tan << endl;
			
			if (tan > bestTan) {
				bestTan = tan;
				bestCoords.clear();
				
				for (int i=0; i<toAlign->atoms.size(); i++) {
					float *cd = toAlign->atoms[i]->fCoords;
					bestCoords.push_back(cd[0]);
					bestCoords.push_back(cd[1]);
					bestCoords.push_back(cd[2]);
				}
				if (tempFlex) {
					for (int i=0; i<templ->atoms.size(); i++) {
						float *cd = templ->atoms[i]->fCoords;
						bestCoords.push_back(cd[0]);
						bestCoords.push_back(cd[1]);
						bestCoords.push_back(cd[2]);
					}

				}
				if (tanTerm > 0 && bestTan > tanTerm) {
					break;
				}
			}

			cout <<"best tan: " << bestTan << endl;
			int test2 = 0;
			cin >> test2;
			//Now check and save the pose
			//cout <<"HERE 7"<<endl;
			savePose(poseMap, rmseCoords,tan);

			double tmpE = 10000;
			while (tmpE > 2000.0) {
				for (int i=0; i<2; i++) {
					randMol(toAlign, mol);
					//randMol(templ, mol);
					vector<float> eg1;
					Energy->EandF(eg1);
					tmpE = eg1[0];
				}
			}

		copyCurrent();
		}
	} //end 10 runs
   
	int count = 0;
	for (int i=0; i<toAlign->atoms.size(); i++) {
		float *cd = toAlign->atoms[i]->fCoords;
		for (int j=0; j<3; j++) {
			cd[j] = bestCoords[count];
			count++;
		}
	}

	if (tempFlex) {
		for (int i=0; i<templ->atoms.size(); i++) {
			float *cd = templ->atoms[i]->fCoords;
			for (int j=0; j<3; j++) {
				cd[j] = bestCoords[count];
				count++;
			}
		}
	} 

	time_t t2 = time(NULL);
	return true;
}

float flexAlign::RMSE(vector<float> &p1, vector<float> &p2) {
   if (p1.size() != p2.size()) {
      return -1;
   }

   float rmse = 0.0;
   for (int i=0; i<p1.size(); i++) {
      float a = p1[i]-p2[i];
      rmse += a*a;
   }

   return sqrt(rmse/p1.size());
}

void flexAlign::savePose(multimap<float, vector<float> > &poseMap, float rmse, float tan) {
	//First build a vector of the atoimc coords
	vector<float> Coords;
	for (int i=0; i<allAtoms.size(); i++) {
		float *cd = allAtoms[i]->fCoords;
		for (int j=0; j<3; j++) 
			Coords.push_back(cd[j]);
	}
 
	if (poseMap.size() == 0) { 
		pair<float, vector<float> > newPair(-tan, Coords);
		poseMap.insert(newPair);
		return;
	} else {
		pair<float, vector<float> > newPair(-tan, Coords);
		poseMap.insert(newPair);
	}

	return; //You should delete this 
	multimap<float, vector<float> > newPoseMap;
   
	multimap<float, vector<float> >::iterator m1, m2;// closest;
	m1 = poseMap.begin();
	m1++;
 
	pair<float, vector<float> > np(m1->first, m1->second);
	newPoseMap.insert(np);   

	m2 = poseMap.begin();
	//m2 = *m1+1;
	for (m1; m1 != poseMap.end(); m1++) {
		m2 = poseMap.begin();
		float currentError;
		float closestError = 100000;
		for (m2; m2 != poseMap.end(); m2++) {
			if (m2 != m1) {
				currentError = RMSE(m1->second, m2->second);    
				if (currentError < closestError) closestError = currentError;
		
				if (currentError <= rmse) { 
					poseMap.erase(m2); 
				}
			}
		}
	}

	while (poseMap.size() > poseNum) {
		m1 = poseMap.end();
		m1--;
		poseMap.erase(m1);
	}
	m1 = poseMap.begin();
}

float flexAlign::tanimoto(molecule *tmpl, molecule *toAlign) {
	float E1 = 0;
	vector<float> eg1;
	clearForces(templ);
	Energy->setUp(templ, "CG", "GAFF", "Current", 50, 0.0, 0.0, 0.0);
	Energy->EandF(eg1);
	float alignScore = 0;
	scoreAlignment(templ, templ, alignScore);
	//cout <<"templ alignScore: " << alignScore << endl;
	E1 = -alignScore;
	E1 += eg1[0];

	float E2 = 0;
	vector<float> eg2;
	Energy->setUp(toAlign, "CG", "GAFF", "Current", 1, 0.0, 0.0, 0.0);
	Energy->EandF(eg2);
	alignScore = 0;
	scoreAlignment(toAlign, toAlign, alignScore);
	//cout <<"toAlign alignScore: " << alignScore << endl;
	E2 = -alignScore;
	E2 += eg2[0];

	alignScore = 0;
	scoreAlignment(templ, toAlign, alignScore);
	//cout <<"templ-toAlign alignScore: " << alignScore << endl;
	float ab = -alignScore;
	float AB = ab + (eg1[0] + eg2[0])*0.5;
	float tan = AB/(E1+E2-AB);
	return tan;
}

void flexAlign::perturb(molecule *mol, float n) {
   //Scatter toAlignCoords
  
   for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      float num1 = rand() % 100000;
      float num2 = rand() % 100000;
      float num3 = rand() % 100000;
      
      num1 /= (100000.0/n);
      num2 /= (100000.0/n);
      num3 /= (100000.0/n);
        
      
      atm->fCoords[0] += (n/2.0)-num1;   
      atm->fCoords[1] += (n/2.0)-num2;
      atm->fCoords[2] += (n/2.0)-num3;
      
   }
 
}

void flexAlign::clearForces(molecule *mol) {
//   for (int i=0; i<mol->atoms.size(); i++) {
   for (int i=0; i<allAtoms.size(); i++) {
//      atom *atm = mol->atoms[i];
      atom *atm = allAtoms[i];
      atm->forces[0] = 0.0;
      atm->forces[1] = 0.0;
      atm->forces[2] = 0.0;
   }
}

void flexAlign::alignCenters(molecule *mol1, molecule *mol2) {
   vector<float> c1(3);
   for (int i=0; i<3; i++)
      c1[i] = 0.0;
   for (int i=0; i<mol1->atoms.size(); i++) {
      float *cd = mol1->atoms[i]->fCoords;
      c1[0] += cd[0];
      c1[1] += cd[1];
      c1[2] += cd[2];
   }
   for (int i=0; i<3; i++)
      c1[i] /= mol1->atoms.size();
      
   vector<float> c2(3); 
   for (int i=0; i<3; i++)
      c2[i] = 0.0;
      
   for (int i=0; i<mol2->atoms.size(); i++) {
      float *cd = mol2->atoms[i]->fCoords;
      c2[0] += cd[0];
      c2[1] += cd[1];
      c2[2] += cd[2];
   }
   for (int i=0; i<3; i++)
      c2[i] /= mol2->atoms.size();
      
   
   
   for (int i=0; i<mol2->atoms.size(); i++) {
      float *cd = mol2->atoms[i]->fCoords;
      cd[0] -= c2[0]-c1[0];
      cd[1] -= c2[1]-c1[1];
      cd[2] -= c2[2]-c1[2];  
   }
}

bool flexAlign::scoreAlignment(molecule *mol1, molecule *mol2, float &score) {
   score = 0;
   //clearForces(mol1);
   //clearForces(mol2);
   //static corr1 = 20.0/ 
   
   for (int i=0; i<mol1->atoms.size(); i++) {
      atom *atm1 = mol1->atoms[i];
      if (atm1->getAtomicNum() != 1) {
      float *cd1 = atm1->fCoords;
      double sig1 = atm1->getSigma();
      double chg1 = atm1->getCharge();
      double aro1=0;  
      if (atm1->getFFType() == "ca" || atm1->getFFType() == "nb") 
         aro1 = 1;
      
      for (int j=0; j<mol2->atoms.size(); j++) {
         
         atom *atm2 = mol2->atoms[j];
         if (atm2->getAtomicNum() != 1) {
            float *cd2 = atm2->fCoords;
            double sig2 = atm2->getSigma();
            double chg2 = atm2->getCharge();
            double aro2=0;  
            if (atm2->getFFType() == "ca" || atm2->getFFType() == "nb") 
               aro2 = 1;

            double same=0;  
            if (atm2->getFFType() == atm1->getFFType()) 
               same = 1;
         
            double a = cd1[0] - cd2[0];
            double b = cd1[1] - cd2[1];
            double c = cd1[2] - cd2[2];
         
            double d2 = a*a + b*b +c*c;
         
            double expPart = exp(-alpha*(d2));
            if (expPart != expPart) {
               cout <<"NaN was generated"<<endl;
               return false;
            }
            double aPart = temp*(aroW*aro1 + sigW*sig1*sig2 
                              + sameW*same + chgW*chg1*chg2);

            double tmpScore = aPart*expPart;
            score += aPart*expPart;
            atm2->forces[0] -= -2.0*alpha*(a)*aPart*expPart;
            atm2->forces[1] -= -2.0*alpha*(b)*aPart*expPart;
            atm2->forces[2] -= -2.0*alpha*(c)*aPart*expPart;
      
            atm1->forces[0] += -2.0*alpha*(a)*aPart*expPart;
            atm1->forces[1] += -2.0*alpha*(b)*aPart*expPart;
            atm1->forces[2] += -2.0*alpha*(c)*aPart*expPart;   
         //}
         } 
      }
      }//AN == 1
   }
   return true;
}

void flexAlign::mmEnergy(molecule *mol, vector<float> &energies) {
     
   Energy->setAtoms(mol->atoms);
   if (stop == true) return;
   Energy->setBonds(mol->bonds);
   if (stop == true) return;
   Energy->setAngles(mol->angles);
   if (stop == true) return;
   Energy->setTorsions(mol->torsions);
   if (stop == true) return;
   Energy->setNonBonds(mol->nonBonds);
   if (stop == true) return;
   
   Energy->EandF(energies);
}


float flexAlign::minimize(molecule *mol, int maxIter, float rmsef, 
                          float maxForce, float minEDiff) 
{

   time_t t1 = time(NULL);
   static int minCount = 0;
   
   float stepSize = .01;
   double currE = 0;
   vector< vector<double> > prevForces(allAtoms.size());
   vector< vector<double> > prevDir(allAtoms.size());
   vector< vector<double> > currDir(allAtoms.size());

   for (int i=0; i<prevForces.size(); i++) {
      for (int j=0; j<3; j++) {
         prevForces[i].push_back(0);
	 prevDir[i].push_back(0);
	 currDir[i].push_back(0);
      }		
   }

   double initEnergy = 1000000;//totalEnergy(mol, 0);
   double prevRMS = 5000000;
   currE = initEnergy;
   int count = 0;
   int iteration = 0;
   vector<float> energies(6);
   double rms = 0.0;
   for (iteration=0; iteration<maxIter; iteration++) {  
      if (stop == true) break;	
      
      clearForces(toAlign);
      clearForces(templ);
      Energy->EandF(energies);

      float alignScore;
      if (!scoreAlignment(templ, toAlign, alignScore))
         return false;

      currE = -alignScore;
      currE += energies[0];
	
      mol->potEnergy[0] = energies[0];
      mol->potEnergy[1] = energies[1];
      mol->potEnergy[2] = energies[2];
      mol->potEnergy[3] = energies[3];
      mol->potEnergy[4] = energies[4] + energies[5];
	
      rms = 0;
               
      //Determine the gamma && rms parametes
      double top, bottom, top2;
      top = bottom = 0;
      float largestForce = -100;
      for (int j=0; j<allAtoms.size(); j++) {
         atom *atm = allAtoms[j];
         for (int k=0; k<3; k++) {
	    top  += atm->forces[k]*atm->forces[k];
	    top2 += (atm->forces[k] - prevForces[j][k])*atm->forces[k];
	    bottom += prevForces[j][k] * prevForces[j][k];
            float tmp = fabs(atm->forces[k]);
            if (tmp > maxForce) largestForce = tmp;
         }
      }
		
      double gamma = 0;
		
      if (bottom == 0) gamma = 0.0;  //gradient was zero
      else gamma = top/bottom;
      if (gamma > 1) gamma = 1;
		
      for (int j=0; j<currDir.size(); j++) {
         atom *atm = allAtoms[j];
	 for (int k=0; k<3; k++) {
            currDir[j][k] = atm->forces[k] + gamma*prevDir[j][k];
            prevForces[j][k] = atm->forces[k];
	    atm->forces[k] = currDir[j][k]; 
	    prevDir[j][k] = currDir[j][k];
         }    
      }

      rms = sqrt(top/(3.0*allAtoms.size()));		                
		
      if (rms < rmsef && largestForce < maxForce) {
	 break;
      }
		
      float eDiff = fabs(currE-initEnergy);
      if (eDiff < minEDiff && rms < 0.5 ) {
         break;
      }
		
      moveAtomsSD(toAlign, stepSize, rms);
      if ( currE < initEnergy) {
         stepSize *= 1.2;
	 if (stepSize > 1.5 ) stepSize = 1.5;
      } else {
	 stepSize *= 0.5;
         if (stepSize < .000001) stepSize = .000001;	
      }		
   
      prevRMS = rms;
      initEnergy = currE;
   }
    
   time_t t2 = time(NULL);
   return currE;
}

void flexAlign::moveAtomsSD(molecule *mol, const double &stepSize, double rms) {
   rms = 1.0/rms;
   for (int i=0; i<allAtoms.size(); i++) {
      float *cd = allAtoms[i]->fCoords;
      double *forces = allAtoms[i]->forces;
   //for (int i=0; i<mol->atoms.size(); i++) {
      //atom *atm = mol->atoms[i];
      //float *cd = mol->atoms[i]->fCoords;
      //double *forces = mol->atoms[i]->forces;
      //if (!atm->frozen) {
         cd[0] += stepSize*forces[0]*rms;
         cd[1] += stepSize*forces[1]*rms;
         cd[2] += stepSize*forces[2]*rms;
         //atm->fCoords[0] += stepSize*atm->forces[0]*rms;
         //atm->fCoords[1] += stepSize*atm->forces[1]*rms;
         //atm->fCoords[2] += stepSize*atm->forces[2]*rms;
      //}
    }
}

bool flexAlign::leapfrog(molecule *mol, int maxIter) {
	//cout <<"flexAlign::leapfrog"<<endl;
	vector<float> energies(6);
	vector<double> vel(allAtoms.size()*3);
	vector<double> acc(allAtoms.size()*3);

	vector<float> currRMSECoords;  
  
	avgRMSECoords.resize(0);   
	for (int i=0; i<allAtoms.size(); i++) {
		float *cd = allAtoms[i]->fCoords;
		for (int j=0; j<3; j++) {
			currRMSECoords.push_back(cd[j]);
			avgRMSECoords.push_back(cd[j]);
		}
	}

	float E = 0;
	float ID = 2.0;
	float bestE = 10000;
	float prevAvgE = 100000;
	float currAvgE = 10000;
	vector< float > bestCoords(allAtoms.size()*3);

	// Kinteic Energy
	double KE = 0; 

	//boltz in kcal/mol
	const double boltz = 0.00198561151;

	//Initialize velocities
	Energy->initVelocity(vel, 2.0);
  
	double timeStep = 0.02;
	double avgTemp = 0.0;
	double avgKE = 0.0;
	double avgPE = 0.0;
	double time = 0.0;
	//cout <<"Maxiter: " << maxIter   << endl;
	for (int i=0; i<maxIter; i++) {
		if (i % dynIter == 0) {
			currAvgE /= dynIter;
			if (!tempFlex && currAvgE > prevAvgE) {
				//break;
			}
			prevAvgE = currAvgE;
			currAvgE = 0.0;
			if (i == 1000) {
				aroW /= 4;
				sigW /= 4;
				//sameW /= 2;
				chgW /= 4;
			}
			if (i > 1000) {
				for (int i=0; i<vel.size(); i++) {
					vel[i] *= annealPercent;
				}
			} else {
				for (int i=0; i<vel.size(); i++) {
					vel[i] *= 1.1;
				}
			}
			//Determine the avg Root MEAS Square error of coord movement 
			float rmse = 0;
			for (int j=0; j<avgRMSECoords.size(); j++) { 
				avgRMSECoords[j] /= dynIter;
				float tmp = avgRMSECoords[j] - currRMSECoords[j];
				rmse += tmp*tmp;
			}
			rmse = sqrt(rmse/avgRMSECoords.size());
			//cout << "rmse: " << rmse << endl;	
			//infoText->clear(); 
			string bString = "BestScore: " + dynabase::setNum(bestTan);
			//infoText->push_back(bString);
			string sRMSE = "RMSE: " + dynabase::setNum(rmse);
			//infoText->push_back(sRMSE); 
			if (rmse < rmseCoords)
				break;
			//Rezero the avgRMSE Coord Vec;
			currRMSECoords = avgRMSECoords;
			for (int j=0; j<avgRMSECoords.size(); j++) 
				avgRMSECoords[j]  = 0.0;
          
		}
 		//cout <<"D"<<endl;
		if (!Energy->EandF(energies)) {
			cout <<"Failed on Energy->EandF"<<endl;
			return false;
		}

		E = energies[0];
		float alignScore = 0;

		if (!scoreAlignment(templ, toAlign, alignScore)) {
			cout <<"Not scoreAlignemnt"<<endl;
			int test2=0;
			cin >> test2;
			return false;
		}

		E += -alignScore;
		currAvgE += E;
		if ( E < bestE ) {
			bestE = E;
			int count = 0;
			for (int i=0; i<allAtoms.size(); i++) {
				float *cd = allAtoms[i]->fCoords;
				for (int j=0; j<3; j++) {
					bestCoords[count] = cd[j];
					count++;
				}
			}
		}
 
		int count = 0;
		KE = 0;
		double vSum = 0; 
		for (int j=0; j<allAtoms.size(); j++) {
			//Move forward
			atom *atm = allAtoms[j];
			float *cd = atm->fCoords;
			double *force = atm->forces;
			double mass = atm->getMass();
			double vv = 0;
			for (int k=0; k<3; k++) {
				acc[count] = force[k]/mass;
				vel[count] = vel[count] + timeStep*acc[count]; 
				vv += vel[count]*vel[count];
				cd[k] += timeStep*vel[count];
				count++;
			}
			vSum += vv;
		}

		KE = 0.5 * vSum/allAtoms.size();
		avgKE += KE;

		avgPE += energies[0];

		double Temp = KE*2.0/(boltz*3.0);
		avgTemp += Temp;

		time += timeStep*2161.0/1000.0;

		int coordCount = 0;
		for (int i=0; i<allAtoms.size(); i++) {
			float *cd = allAtoms[i]->fCoords;
			for (int j=0; j<3; j++) {
				avgRMSECoords[coordCount] += cd[j];
				coordCount++;
			}
		}

		if (i % 500 == 0) {	
			avgTemp = avgTemp/500.0;    
			avgKE = avgKE/500.0;
			avgPE = avgPE/500.0;
			avgTemp = 0.0;
		}

		if (stop == true) break;
	}

	int count = 0;
	for (int i=0; i<allAtoms.size(); i++) {	
		float *cd = allAtoms[i]->fCoords;       
		for (int j=0; j<3; j++) {
			cd[j] = bestCoords[count];
			count++;
		}
	}

	cout <<"Leaving flexAlign::leapfrog"<<endl;
	return true;

}

};//END NAMESPACE

