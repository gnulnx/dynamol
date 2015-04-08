/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 John Furr
    email                : john.furr@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

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
    //TODO This needs to be offloaded to python code.   
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
		inFile >> num >> symbol >> x >> y >> z >>mol2_type;
		getline(inFile, tmp);
		mol->addAtom(num, symbol, x, y, z);		
	}
	getline(inFile, tmp);
	int bdNum, fromNum, toNum, order;
	string sorder;
	for (int i=0; i<numBd; i++) {
		inFile >> bdNum >> fromNum >> toNum >> sorder;
		if (sorder == "1")
			order = 1;	
		if (sorder == "ar")
			order = 2;
		if (sorder == "2")
			order = 2;
		if (sorder == "3")
			order = 3;
		
		bond *bd = mol->addBond(i+1, fromNum, toNum, order);
		
	}

	return mol;

};

int main(int argc, char *argv[]) {
    //NOTE: Rename this to molfile or something since you 
    //      will determine the type in python code and then load the molecule
	string sdFile = argv[1];
	QApplication a(argc, argv);

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
    
	molecule *mol;
	if (sdFile[ sdFile.size()-1 ] == '2'){
    	mol = readMol2(sdFile);
		v2->Show(mol);
	} else {
		SE->LoadMol(sdFile);
	}

	widget->show();
	return a.exec();
}
