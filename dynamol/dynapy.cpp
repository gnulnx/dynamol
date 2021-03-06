/***************************************************************************
                          dynapy.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by John Furr
    email                : john.furr@dynamol.com


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
**************************************************************************/
#include "dynapy.h"

#include <boost/python.hpp>
#include <boost/detail/lightweight_test.hpp>
using namespace boost::python;

#include <iostream>
#include <fstream>
#include <QLineEdit>
using namespace std;

namespace python = boost::python;

namespace dynamol {

DynaPy::DynaPy()  
: QThread()
{
	Py_Initialize();

};

DynaPy::~DynaPy() {
	Py_Finalize();
};

void DynaPy::setFileName(string fileName)
{ this->script = fileName; }

void DynaPy::run() {
	cout <<"DynaPy::run"<<endl;
	//Threading works when Python isn't invovled.  You need to do more work here
	//while (true) {
	//	cout << "runnin" << endl;
	//}
	//Py_Initialize();
	QString cmd = script.c_str();
	RunCommand(cmd);
	//Py_Finalize();
	/*
	Py_Initialize();
	PyEval_InitThreads();
	PyThreadState * mainThreadState = NULL;
	mainThreadState = PyThreadState_Get();
	PyEval_ReleaseLock();
	PyEval_AcquireLock();
	PyInterpreterState * mainInterpreterState = mainThreadState->interp;
	PyThreadState * myThreadState = PyThreadState_New(mainInterpreterState);
	PyEval_ReleaseLock();

	PyEval_AcquireLock();
	PyThreadState_Swap(myThreadState);

	
	QString cmd = script.c_str();
	RunCommand(cmd);
	
	PyThreadState_Swap(NULL);
	PyEval_ReleaseLock();
	PyEval_ReleaseLock();
	PyThreadState_Swap(NULL);
	PyThreadState_Clear(myThreadState);
	PyThreadState_Delete(myThreadState);
	PyEval_ReleaseLock();
	PyEval_AcquireLock();
	Py_Finalize();
	*/
}

string DynaPy::RunCommand(QString CMD) {
	//Py_Initialize();
	string cmd = CMD.toStdString();
	string total = cmd;
	
	cout <<"Running: " << cmd << endl;
	string base_cmd = "import molecule\nfrom molview import *\nm = molView()\nm.";
	
    //string total = base_cmd + cmd;
	
	//cout <<"Running: " << cmd << endl;
	//cout <<"And that was run command"<<endl;
	PyRun_SimpleString(total.c_str());
	//int test =0;
	//cin >> test;
   	/*
	try {
        int error = PyRun_SimpleString(total.c_str());
		//exec_file(total.c_str());
		cout <<"PyRun_SimpleString was called: " << endl;
		
		if (PyErr_Occurred(	)) {
			cout <<"error: " << error << endl;
		}
		if (error == -1) {	
			PyErr_Print();
		}
		
    }
    catch (error_already_set)
    {
        cout <<"error_already_set caught from DynaPy"<<endl;
        PyErr_Print();
    }
	*/
	cout <<"Command was Run"<<endl;
	//Py_Finalize();
	//cin >> test;
	return "Must Return a String or OS X will crash...kinda like Winders";
}

void DynaPy::MolViewCommand()
{
	cout <<"DynaPy::MolViewCommand" << endl;
	string cmd = lineEdit->text().toStdString();
	string base_cmd = "from molview import *\nm = molView()\nm.";

	string total = base_cmd + cmd;
	cout << "Running" << endl;
	cout << total << endl;
	/*
	try {
		PyRun_SimpleString(total.c_str());
		//lineEdit->setText("");
	}
	catch (error_already_set)
    {
        cout <<"error_already_set caught from DynaPy"<<endl;
        PyErr_Print();
    }
	*/
}


}
