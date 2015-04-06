/**************************************************************************
                          scriptengine.cpp  -  description
                             -------------------
    begin                : Tue Dec 30 2007
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol
 ***************************************************************************/
#include "scriptengine.h"
#include "dynapy.h"
#include "molview.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <qevent.h>
#include <QString>

namespace dynamol {

ScriptEngine::ScriptEngine(QWidget *parent, char *name) 
: QLineEdit(parent)
{
	name = name; //Make warning go away...nothing more
}

ScriptEngine::~ScriptEngine() {}

void ScriptEngine::SetDynaPy(DynaPy *dynapy) {
	this->dynapy = dynapy;
	if (this->dynapy != 0) {
		//QObject::connect(dynapy->lineEdit, SIGNAL(returnPressed()), this, SLOT(RunScript()));
	}
	
}

// This function is mostly used for debuggin purposes
void ScriptEngine::PrintStack( stack<QString> s ) {
	while (s.size() > 0) {
		string txt = s.top().toStdString();
		s.pop();
		cout << txt << endl;
	}
}

void ScriptEngine::keyPressEvent( QKeyEvent *event ) {
	// ## LEFT ARROW
	if ( event->key() == Qt::Key_Left ) 
		cursorBackward(false, 1);
	// ## RIGHT ARROW
	else if ( event->key() == Qt::Key_Right )
		cursorForward(false, 1);
	// ## BACKSPACE
	else if (event->key() == Qt::Key_Backspace) {
		cursorBackward(true, 1);
		del();
	}
	// ## RETURN/ENTER 
	else if (event->key() == Qt::Key_Return) {
		while (PopStack.size() >0) {
			History.push(PopStack.top());
			PopStack.pop();
		}
	
		if ( !text().isEmpty() ) {
			History.push( text() );
			CheckText();
			setText("");
		}
	}
	// ## UP ARROW
	else if (event->key() == Qt::Key_Up) {
		if (History.size() > 0) {
			QString txt = History.top();
			PopStack.push(txt);
			History.pop();
			setText(txt);
		} else if (PopStack.size() != 0)  {
			QString txt = PopStack.top();
			History.push(txt);
			PopStack.pop();
		}	
	}
	// ## DOWN ARROW
	else if (event->key() == Qt::Key_Down) {
		if (PopStack.size() > 0) {
			QString txt = PopStack.top();
			PopStack.pop();
			History.push(txt);
			setText(txt);
		} else {
			setText("");
		} 
	}
	// ## TAB
	else if (event->key() == Qt::Key_Tab) {
		if (History.size() > 0)
			History.pop();
	}
	else { // DEFAULT CASE.  BASICALLY ADDED THE CHARACTER TO THE TEXT
		string text = event->text().toStdString();
		insert(event->text());
	}
}

void ScriptEngine::CheckText() {
	//QString txt = text();
	string txt = text().toStdString();

	if (!SpecialCmd(txt)) {
		string cmd = 
			"\nfrom molview import * \n"
			"import molecule\n"
			"import sys\n"
			"v = molView()\n"
			"v."
		;
		cmd += txt;
		cmd += "\n";
		//cmd += "del(LoadMol)\n";
		//cmd +=  "keys = sys.modules.keys()\n"
		//		"keys.sort()\n"
		//		"for k in keys:\n"
		//		"	print str(k) +'\t' + str(sys.modules[k])\n"
		//		//"del(LoadMol)\n"
		//;

		QString base_cmd(cmd.c_str());
		dynapy->RunCommand(base_cmd);
		cout <<"cmd: " << cmd << endl;
		cout <<"CheckText: " << txt << endl;
		return;
	} else {
		return;
	}

}

bool ScriptEngine::SpecialCmd(string cmd) {
	if (cmd.substr(0,4) == "run(" ) {
		string fileName = cmd.substr(5, cmd.size()-7);
		cout <<"You are trying to run file"<<endl;
		cout <<"run file: " << fileName << endl;
		RunFile(fileName);
		return true;
	}
	if (cmd.substr(0,5) == "load(" ) {
		string fileName = cmd.substr(6, cmd.size()-8);
        cout <<"You are trying to LOAD file"<<endl;
        cout <<"Load file: " << fileName << endl;
		LoadMol(fileName);
		return true;
	}

	return false; //No Special commands yet
}

void ScriptEngine::RunFile(string fileName) {
	ifstream inFile(fileName.c_str(), ios::in);
	string cmd = "";
	string tmp;
	while (!inFile.eof()) {
		getline(inFile, tmp);
		cmd += tmp +"\n";
	}
	QString base_cmd(cmd.c_str());
	//dynapy->RunCommand(base_cmd);
	//cout <<"RunFile cmd:  " << cmd << endl;
	dynapy->setFileName(cmd);
	dynapy->run();
	//dynapy->start();
}

void ScriptEngine::LoadMol(string &fileName) {
	
	string cmd = "from molecule import *\nfrom molview import *\nfrom LoadMol import *\n";
	cmd += "mol = LoadMol('";
	cmd += fileName;
	cmd += "')\n";
	//cmd += "print '------------------------YOU ARE HERE---------------------'\n";
	cmd += "del(sys.modules['LoadMol'])";

	QString base_cmd(cmd.c_str());	
    cout <<"base_cmd:" << cmd.c_str() << endl;
	dynapy->RunCommand(base_cmd);
	
}
}
