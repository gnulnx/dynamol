#include "embedded_program.h"

#include <boost/python.hpp>
using namespace boost::python;

#include <iostream>
using namespace std;


//int DynaPy(std::string fileName) {
void DynaPy::run() {
	cout <<"Hello from DynaPy::run()  "<< this->fileName.size()  << endl;
	if (fileName.size() == 0) 
		return;
	cout <<"Hi from DynaPy...You have uncommented Python stuff"<<endl;
	if ( !Py_IsInitialized() )
		Py_Initialize();

	object main_module((
	handle<>(borrowed(PyImport_AddModule("__main__")))));

	object main_namespace = main_module.attr("__dict__");

	try {
		FILE *fp      = fopen (fileName.c_str(),   "r+");

		handle<> ignored((PyRun_SimpleFile(fp, fileName.c_str()), 
							main_namespace.ptr(), 
							main_namespace.ptr()));

	}
	catch (error_already_set)
	{
		cout <<"error_already_set caught from DynaPy"<<endl;
		PyErr_Print();
	}

	Py_Finalize();
};



