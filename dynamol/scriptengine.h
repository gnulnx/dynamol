/***************************************************************************
                          script_engine.h  -  description
                             -------------------
    begin                : Tue Dec 30 2007
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

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
