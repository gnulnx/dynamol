/***************************************************************************
                          script_engine.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by John Furr
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
**************************************************************************/

#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QLineEdit>
#include <string>
#include <stack>
using namespace std;
class QKeyEvent;

namespace dynamol {

class molView;
class DynaPy;
class ScriptEngine : public QLineEdit {
Q_OBJECT
public:
	ScriptEngine(QWidget *parent=0, char *name=0);
	~ScriptEngine();

	void SetDynaPy(DynaPy *dynapy);
	
	void LoadMol(string &fileName);
	
	DynaPy *dynapy;
	molView *viewer;

	bool SpecialCmd(string cmd);
	void RunFile(string fileName);
public slots:
	void keyPressEvent( QKeyEvent *event );
	void CheckText();
	//void LoadMol(string fileName);
private:
	/** This function was being used for debuggin..Utility only
    */
    void PrintStack( stack<QString> s );
	stack<QString> History;
	stack<QString> PopStack;
};

};
#endif
