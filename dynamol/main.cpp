//#include <boost/python.hpp>
//#include <boost/detail/lightweight_test.hpp>


#include <Qt>
#include <QApplication>

#include <boost/python.hpp>
#include <boost/detail/lightweight_test.hpp>

#include <iostream>
#include <fstream>
using namespace std;

#include "molview_layout.h"
#include "molview_control.h"
#include "molview.h"
#include "script_molview.h"
#include "scriptengine.h"


#include "molecule.h"
#include "atom.h"
#include "bond.h"

#include "dynapy.h"


using dynamol::molecule;
using dynamol::bond;
using dynamol::molView;
using dynamol::DynaPy;
using dynamol::script_molView;
using dynamol::ScriptEngine;

molecule *readMol2(string fileName) {
	string name = "None";
	molecule *mol = new molecule(name);
	ifstream inFile(fileName.c_str(), ios::in);
	string tmp;
	getline(inFile, tmp);
	getline(inFile, tmp);
	int numAtm, numBd;
	inFile >> numAtm >> numBd;
	getline(inFile, tmp);
	cout <<"Reading mol: " <<numAtm <<"\t" << numBd << endl;
	while (true) {
		getline(inFile, tmp);
		if (tmp == "@<TRIPOS>ATOM")
			break;
	}
	int num;
	string symbol, mol2_type;
	float x, y, z;
	for (int i=0; i<numAtm; i++) {
		//cout << i << endl;
		inFile >> num >> symbol >> x >> y >> z >>mol2_type;
		getline(inFile, tmp);
		mol->addAtom(num, symbol, x, y, z);		
	}
	//cout <<"Now Reading Bonds"<<endl;
	getline(inFile, tmp);
	int bdNum, fromNum, toNum, order;
	string sorder;
	for (int i=0; i<numBd; i++) {
		inFile >> bdNum >> fromNum >> toNum >> sorder;
		//getline(inFile, tmp);
		//cout << bdNum <<"\t" << fromNum << endl;
		//cout <<"bond tmp: " << tmp << endl;
		//cin >> test;
		if (sorder == "1")
			order = 1;	
		if (sorder == "ar")
			order = 2;
		if (sorder == "2")
			order = 2;
		if (sorder == "3")
			order = 3;
		
		//order = 1;
		//cout << bdNum <<"\t"<<fromNum<<"\t"<<toNum<<"\t"<<sorder<<endl;
		bond *bd = mol->addBond(i+1, fromNum, toNum, order);
		
	}

	return mol;

};

int main(int argc, char *argv[]) {


	string sdFile = argv[1];
	QApplication a(argc, argv);
	DynaPy *scripter = new DynaPy();
	//molecule *mol = readSD("SDF/Trans.sdf");
	//molecule *mol = readMol2("SDF/120939.mol2");
	//molecule *mol = readMol2("SDF/1GW7.mol2");
    /*
	molecule *mol;
	if (sdFile[ sdFile.size()-1 ] == 'f') {
		mol = readSD(sdFile);
    }
	if (sdFile[ sdFile.size()-1 ] == '2') {
		mol = readMol2(sdFile);
    }
    */
	//molecule *mol = readMol2("SDF/Really_Big_Structure.mol2");
	//cout <<mol->atoms.size() <<"\t" << mol->bonds.size() << endl;
	//Initialize the molecule viewer
	Ui::Form ui;
	QWidget *widget = new QWidget;
	ui.setupUi(widget);
	molView *v2 = dynamic_cast<molView *>(ui.widget);
	cout <<"Viewer from main: " << v2 << endl;
	ScriptEngine *SE = dynamic_cast<ScriptEngine *>(ui.lineEdit);
	SE->SetDynaPy(scripter);
	SE->viewer = v2;

	scripter->lineEdit = ui.lineEdit;
	//v2->Show(mol);
	//v2->Show(mol);
	//v2->currMol = mol;
	v2->SetScripter(scripter);
	script_molView *mvscript = new script_molView(v2);
	//LoadMol(string fileName)
	//widget->show();

	
	molecule *mol;
    /*
    if (sdFile[ sdFile.size()-1 ] == 'f') {
		SE->CheckText();
		SE->LoadMol2(sdFile);
		string fileName = "../dynamol/" + sdFile;
		
		SE->LoadMol(fileName);
		SE->LoadMol(sdFile);
		cout <<"After SE->LoadMol: " << endl;
		SE->LoadMol(sdFile);
	}
    */ 
	if (sdFile[ sdFile.size()-1 ] == '2'){
    	mol = readMol2(sdFile);
		v2->Show(mol);
	} else {
        cout <<"YOU ARE RIGHT HERE JOHNNY"<<endl;
		SE->LoadMol(sdFile);
	}

	widget->show();
	//Initialize the molviewr script class before callign any python
	//script_molView *mvscript = new script_molView(v2);

	// THIS IS A TEST ONLY SECTION
	//scripter->setFileName("../../Scripts/test.py");
	//scripter->start();
	//scripter->setFileName("../../Scripts/test.py");
    //scripter->start();

	//And Finally we start out main GUI loop
	//a.setActiveWindow(mviewer);
	return a.exec();
}
