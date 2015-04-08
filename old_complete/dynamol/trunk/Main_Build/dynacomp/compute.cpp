/***************************************
 *   Copyright (C) 2004 by Dynamol Inc.*
 *   john.furr@dynamol.com             *
 ***************************************/

//Dynamol Computational Includes
#include "compute.h"
#include "molecule.h"
#include "charge.h"
#include "energy.h"
#include "forcefield.h"

//Standard Library Includes
#include <iostream>
using std::cout;
using std::endl;

//Boost Includes
#include <boost/shared_ptr.hpp>

namespace dynacomp {

string Compute::errorMsg = "";

Compute::Compute()
{
   errorMsg = "";
}


Compute::~Compute()
{
}

string Compute::getErrorMsg()
{ return errorMsg; }

bool Compute::charges(molecule *mol, string chargeType) {
   charge *chg = new charge;
   bool success = chg->run(mol, chargeType);
   delete chg;
   return success;
}

bool Compute::Minimize(dynacomp::molecule *mol, string method, string ffType,         
              string chargeType, int maxIter, float rmsef,         
              float maxForce, float minEDiff)       
{
	dynacomp::energy Energy;// = new dynacomp::energy();	
	Energy.dieSetup("Constant", this->die);
	Energy.setUp(mol, method, ffType, chargeType, maxIter, rmsef, maxForce, minEDiff);
	Energy.run();
	return true;
}

bool Compute::Charges(molecule *mol, string chargType) {
   boost::shared_ptr<charge> chg( new charge );
   bool success = chg->run(mol, chargType);
   return success;
}

bool Compute::charges(vector<molecule *> &mols, vector<string> &chargType) {
   return true;
}

int Compute::dieSetup(string method, float die) {
	if (method =="Constant") {
		this->die = die;
	}
}

bool Compute::potEnergy(molecule *mol) {
   string type = "GAFF";
   forceField ff;
   ff.setAtomTypes(mol, type);
   ff.buildLists(mol, type);
   dynacomp::energy Energy;
   Energy.dieSetup("Constant", this->die);
   Energy.molEnergy(mol);
   //delete E;

   return true;
}

}

