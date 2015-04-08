/***************************************************************************
                          dynapy.h  -  description
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

