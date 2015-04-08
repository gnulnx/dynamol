/***************************************
 *   Copyright (C) 2004 by Dynamol Inc.*
 *   john.furr@dynamol.com             *
 ***************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>

#include "../dynatype/dtReader.h"
#include "../dynatype/molecule.h"
#include "../dynatype/atom.h"
#include "../dynatype/dtUtility.h"
#include "../convert/convert.h"
#include "flexalign.h"
#include "atom.h"
#include "molecule.h"
#include "compute.h"
#include "file.h"

using namespace std;

int main(int argc, char *argv[])
{

	// FlexAlign Section
	dynacomp::flexAlign *align = new dynacomp::flexAlign();

	cout <<"You need an input fileName and an Output fileName" << endl;
	string TemplateName = argv[1];
	string ToAlignName = argv[2];
	
	cout <<"Running dynacomp!!!"<<endl;
	dt::molPtr dtMol( new dt::molecule );
	dt::dtReader *reader = new dt::dtReader();

	cout <<"HERE 1"<<endl;	
	reader->readSDF(TemplateName, dtMol);
	dt::convert *conv = new dt::convert();
	dynacomp::molecule *dcMol = new dynacomp::molecule();
	conv->toDynacomp(dcMol, dtMol);

	align->setTemplateMolecule(dcMol);
	
	cout <<"HERE 2"<<endl;
	
	dt::molPtr dtMol2( new dt::molecule );
	reader->readSDF(ToAlignName, dtMol2);
	dynacomp::molecule *dcMol2 = new dynacomp::molecule();
	conv->toDynacomp(dcMol2, dtMol2);
	align->setMoleculeToAlign(dcMol2);

	cout <<"Before multimp"<<endl;
	multimap<float, vector<float> > poseMap;
	map<string, string> Params;
	Params["dynIter"] = "1000";
	Params["dielec"] = "80";
	Params["poses"] = "1";
	Params["poseRMSE"] = "1.0";
	Params["annealPercent"] = "5";
	Params["chgWeight"] = "3";
	Params["volWeight"] = "2";
	Params["aroWeight"] = "1";
	Params["maxMD"] = "10000";
	Params["maxMin"] = "2500";
	Params["rmse"] = "1.0";
	Params["maxForce"] = "0.000001";
	Params["minE"] = "0.000001";
	Params["rmseCoords"] = "1.0";
	Params["tanTerm"] = "90";
	Params["MinOnly"] = "1";	
	align->setUp(Params);
	cout <<"Calling run" << endl;
	align->run(poseMap);
	cout <<"poseMap.size(): " << poseMap.size() << endl;
	map<float, vector<float> >::iterator iter = poseMap.begin();
	string NameHold = dtMol2->name;
	while (iter != poseMap.end()) {
		float num = iter->first;
		string sNum = dt::setNum( double(num) );
		
		vector<float> coords = iter->second;
		//cout <<"num: " << num <<"\t" << coords.size() << endl;
		//cout <<"numAtom " << dcMol2->atoms.size() << endl;	
		//int blah2 = 0;
		//cin >> blah2;
		int count = 0;
		for (int i=0; i<dcMol2->atoms.size(); i++) {
			dynacomp::atom *atm = dcMol2->atoms[i];
			atm->fCoords[0] = coords[count];
			atm->fCoords[1] = coords[count+1];
			atm->fCoords[2] = coords[count+2];
			count = count + 3;
			//atm->fCoords[0]
		}
		
		conv->toDynatype(dtMol2, dcMol2);
		string Name = NameHold +"-" + sNum;
		cout <<"Name: " << Name << endl;
		dtMol2->setName(Name);
		reader->writeSDF("Aligned.sdf", dtMol2, 1);	

		iter++;
	}	
	cout << "After setTemplateMolecule"<<endl;
	
//	 bool Minimize(dynacomp::molecule *mol, //Minimize a Molecule
//             string method,         //SD=Steepest Descent CG=Conjugate Gradients
//              string ffType,         //GAFF or AMBER03
//              string chargeType,     //Current, AM1, AM1-BCC, MNDO, PM3, ForceField
//              int maxIter=5000,         //The maximum Iterations for minimiation
//              float rmsef=0.005,           //The minimum RMSE of the atomic forces before termination
//              float maxForce=0.01,        //The maximum allowable atomic force
//              float minEDiff=0.01);       //The min chage in energy before termination
//

	return EXIT_SUCCESS;

}

