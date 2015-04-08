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
#include <sstream>
#include <stdlib.h>
using namespace std;

dynamol::molView *dynamol::script_molView::viewer = NULL;



dynamol::script_molView::script_molView() {
    cout <<"* dynamol::script_molView::script_molView(): "<< this->viewer << endl;
	ifstream inFile(".molview_address.txt", ios::in|ios::binary);
	if (!inFile) {
          cout <<"Viewer not Initialized"<<endl;
          viewer = NULL;
          return;
	}
    inFile.seekg (0, inFile.beg);
    string s;
    inFile >> std::hex >> s;
    const char *address = s.c_str();
    cout <<"address: " << address << endl;
    void *vnum = (void *)strtol(address, NULL, 0);
    cout <<"vnum: " << vnum << endl;
    viewer = reinterpret_cast<dynamol::molView*>(vnum);
    //string address;
    //inFile >> address;
    //cout <<"address: " << address << endl;
    //cout << static_cast<void*>(&address) << endl;
    //cout <<"address: " << address << endl;
    //viewer = static_cast<dynamol::molView*>(address);
    //void *c = reinterpret_cast<void *>(saddress);
    
    //const char *c = saddress.c_str();
    //cout <<"c: " << c << endl;
    //viewer = (dynamol::molView *)address;
    // Now convert string to void * pointer
    
    //const void *address = reinterpret_cast<void *>( const_cast<char*>(c));
    //cout <<"address: " << address << endl;

    //reinterpret the cast to a molView pointer
    //viewer = reinterpret_cast<dynamol::molView*>(address);
    //viewer = (dynamol::molView *)saddress;
	cout <<"viewer from script_molView: " << this->viewer << endl;
    
};
dynamol::script_molView::script_molView(dynamol::molView *viewer) {
    cout <<"dynamol::script_molView::script_molView(dynamol::molView *viewer): " << viewer << endl;
	this->viewer = viewer;
	ofstream outFile(".molview_address.txt", ios::out|ios::binary);
	outFile << viewer;
	outFile.close();	
    cout <<"sizeof(viewer): "<<sizeof(viewer) << "  " << viewer << endl;
};

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
        return 0;
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
