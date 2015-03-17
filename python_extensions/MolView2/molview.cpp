// Copyright Ralf W. Grosse-Kunstleve 2002-2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "../../dynamol/molview.h"
#include "../../dynamol/script_molview.h"
#include "../../dynamol/molecule.h"
#include "../../dynamol/atom.h"
#include "../../dynamol/bond.h"

#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <iostream>
#include <fstream>
using namespace std;
#include <string>
using namespace boost::python;

#include <cstdlib>

class MolView_Wrap {
public:
	MolView_Wrap()
		{ viewer = NULL; };
	
	~MolView_Wrap(){};

	bool Connect() {
		cout <<"hostname"<<endl;
  		char *dhome = getenv("DYNAMOL_HOME");
  		if (dhome) {
			string path = dhome;
			path += "/dynamol/.molview_address.txt";
			cout <<"Path is: " << path << endl;
			ifstream inFile(path.c_str(), ios::in);
			if (!inFile) {
				cout <<"Viewer not Initialized"<<endl;
				cout <<"viewer address is: " << viewer << endl;
				//viewer = NULL;
				return false;
			} else {
				
				void *address;
				inFile >> address;
				cout <<"address: " << address << endl;
				inFile.close();
				viewer = (dynamol::molView *)address;
				string gretting = viewer->hello();
				cout <<"MolView Say's:  "<< gretting << endl;

				return true;
			}
  		} else {
	  		cout <<"You Need to set the DYNAMOL_HOME environment varialbe"<<endl;
	  		cout <<"Set this value to the default location of you install"<<endl;
  			return false;
		}
	};

	bool SetMolColor(float r, float g, float b) {
		if (!viewer) {
			cout <<"Viewer not Initialized:" << endl;
			return false;
		}

		viewer->colorMolecule(r, g, b);
	};

private:
	dynamol::molView *viewer;
};

BOOST_PYTHON_MODULE(molview)
{
	class_<MolView_Wrap>("Dynamol")
		.def("Connect", &MolView_Wrap::Connect)
		.def("SetMolColor", &MolView_Wrap::SetMolColor)
	;

	/*
	class_<script_molView>("molView")
		.def("members", &script_molView::members)
		.def("SetMolColor", &script_molView::SetMolColor)
		.def("getCurrMol", &script_molView::getCurrMol, return_internal_reference<>())
		.def("Show", &script_molView::Show)
		.def("SetFog", &script_molView::SetFog)	
	;
	*/
}

