#ifndef DYNAPY_H
#define DYNAPY_H

#include <string>
//In Order to make this class multithreaded I had to
//comment out Python24/include/obect.h
//There is a line with the word slots that doesn't jive well
//With Qt.
//#include <qobject.h>
//#include <boost/python.hpp>
#include <qthread.h>
//#include <qwidget.h>
//#include <qobject.h>

//using namespace boost::python;
using namespace std;

class QLineEdit;

namespace dynamol {

class DynaPy :  public QThread {
//Q_OBJECT
public:
	DynaPy();
	~DynaPy();

	void setFileName(string fileName);

	string RunCommand(QString cmd);
	void MolViewCommand();
	
	void run();

	QLineEdit *lineEdit;
private:
   /** The name of the script */
   string script;
	
};

};
#endif

