/***************************************************************************
                          molviewscript.cpp  -  description
                             -------------------
    begin                : Tue Dec 30 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include "script_molview.h"
#include "molecule.h"
#include "molview.h"
#include <iostream>
#include <fstream>
using namespace std;

dynamol::molView *dynamol::script_molView::viewer = NULL;

dynamol::script_molView::script_molView() {
	ifstream inFile(".molview_address.txt", ios::in);
	if (!inFile) {
          cout <<"Viewer not Initialized"<<endl;
          viewer = NULL;
          return;
	}
	void *address;
	inFile >> address;
	cout <<"address: " << address << endl;
	inFile.close();
	viewer = (dynamol::molView *)address;
	cout <<"viewer from script_molView: " << viewer << endl;
	//int test = 0;
	//cin >> test;	
};
dynamol::script_molView::script_molView(dynamol::molView *viewer) {
	this->viewer = viewer;
	ofstream outFile(".molview_address.txt", ios::out);
	outFile << viewer;
	outFile.close();	
};

/*
script_molView::~script_molView() {
	cout <<"----------------------------script_molView::~script_molView()------------------------"<<endl;
};
*/
string dynamol::script_molView::members() {
	string funcs = "";
	funcs += "SetMolColor(float r, float g, float b)";

	return funcs;
};

bool dynamol::script_molView::SetMolColor(float r, float g, float b) {
	cout <<"You are here"<<endl;
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
        return false;
    }

	dynamol::molecule *mol = viewer->getCurrentMol();
	cout <<"script_molView::getCurrMol: " << mol->name << endl;
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
