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

    //Initialize the molView
	molView *v2 = dynamic_cast<molView *>(ui.widget);

    //Initialize the ScriptEngine
	ScriptEngine *SE = dynamic_cast<ScriptEngine *>(ui.lineEdit);

	DynaPy *scripter = new DynaPy();
	SE->SetDynaPy(scripter);
	SE->viewer = v2;

	scripter->lineEdit = ui.lineEdit;
	v2->SetScripter(scripter);
	script_molView *mvscript = new script_molView(v2);
    
    cout <<"script_molView: " << mvscript << endl; 
    //int test = 0;
    //cin >> test;

	
	molecule *mol;
	if (sdFile[ sdFile.size()-1 ] == '2'){
    	mol = readMol2(sdFile);
		v2->Show(mol);
	} else {
        cout <<"main calling SE->LoadMol"<<endl;
		SE->LoadMol(sdFile);
	}

	widget->show();
	return a.exec();
}
