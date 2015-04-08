#ifndef EMBEDDED_PROGRAM_H
#define EMBEDDED_PROGRAM_H

#include <string>

//In Order to make this class multithreaded I had to
//comment out Python24/include/obect.h 
//There is a line with the word slots that doesn't jive well
//With Qt.
#include <boost/python.hpp>
using namespace boost::python;
#include <qthread.h>


class DynaPy : public QThread {
public:
   DynaPy() :QThread() {}
   ~DynaPy() {}

   /** \brief Set the filename of the python script */
   void setFileName(std::string fileName)
   { this->fileName = fileName; }

   void run();
private:
   /** The name of the script */
   std::string fileName;
};

#endif
//int DynaPy(std::string);
