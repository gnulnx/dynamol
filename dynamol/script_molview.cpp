/***************************************************************************
                          molviewscript.cpp  -  description
                             -------------------
    begin                : Tue Dec 30 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

/*
    When dynamol is started up a script_molview object is instantiated
    and assiend the previously created molView object. 
    see: dynamol::script_molView::script_molView(dynamol::molView *viewer)

    However when a python object creates a script_molview object it doesn't have 
    any information about the molView object and thus has to get this information from
    somewhere..   This works by first writing the address of the molView pointer in
    dynamol::script_molView::script_molView(dynamol::molView *viewer)
    and then reading it in dynamol::script_molView::script_molView()
    where it is converted to a *molview pointer.
*/

#include "script_molview.h"
#include "molecule.h"
#include "molview.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

dynamol::molView *dynamol::script_molView::viewer = NULL;



dynamol::script_molView::script_molView() {
    /*
        This method reads the address of the molView object that was created when dynamol 
        started...see:  dynamol::script_molView::script_molView(dynamol::molView *viewer).
        
        It then points this->viewer at this address
    */
	ifstream inFile(".molview_address.txt", ios::in|ios::binary);
	if (!inFile) {
          cout <<"Viewer not Initialized"<<endl;
          viewer = NULL;
          return;
	}
    
    string molview_memory_str;
    inFile >> std::hex >> molview_memory_str;
    viewer = reinterpret_cast<dynamol::molView*>( \     
        (void *)strtol(molview_memory_str.c_str(), NULL, 0) \
    );
};
dynamol::script_molView::script_molView(dynamol::molView *viewer) {
	this->viewer = viewer;
	ofstream outFile(".molview_address.txt", ios::out|ios::binary);
	outFile << viewer;
	outFile.close();	
};

string dynamol::script_molView::members() {
	string funcs = "";
	funcs += "SetMolColor(float r, float g, float b)";

	return funcs;
};

bool dynamol::script_molView::SetMolColor(float r, float g, float b) {
	if (!viewer) {
		cout <<"Viewer not initialized"<<endl;
		return false;
	}

	viewer->colorMolecule(r, g, b);
	return true;
};

bool dynamol::script_molView::RunScript(string filename) {
	if (!viewer) {
		cout <<"Viewer not initialized"<<endl;
        return false;
    }

	return true;	

}

dynamol::molecule *dynamol::script_molView::getCurrMol() {
	if (!viewer) {
        cout <<"Viewer not initialized"<<endl;
        return 0;
    }

	dynamol::molecule *mol = viewer->getCurrentMol();
	return viewer->getCurrentMol();
}

bool dynamol::script_molView::Show(dynamol::molecule *mol) {
	if (!viewer) {
		cout <<"Viewer not initialized"<<endl;
		return false;
	}

	viewer->Show(mol);
	return true;
}

bool dynamol::script_molView::SetFog(float start, float end, float Trans) {
	if (!viewer) {
		cout <<"Viewer not initialized"<<endl;
		return false;
	}

	viewer->SetFog(start, end, Trans);
	return true;
}

bool dynamol::script_molView::LoadMol(string fileName) {
	if (!viewer) {
		cout <<"Viewer not initialized"<<endl;
		return false;
	}
	return true;
}
