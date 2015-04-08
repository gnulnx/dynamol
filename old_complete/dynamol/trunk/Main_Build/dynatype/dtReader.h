/***************************************************************************
 *   Copyright (C) 2004 by Dynamol                                         *
 *   john.furr@dynamol.com                                                **
 ***************************************************************************/
#ifndef DTREADER_H
#define DTREADER_H

//Standard Library Includes
#include <vector>
#include <string>
using std::vector;
using std::string;

//BOOST Includes
#include <boost/shared_ptr.hpp>


namespace dt {
/**
@author jfurr
*/
class molecule;
typedef boost::shared_ptr<dt::molecule> molPtr;

class bond;
class atom;

/** The dtReader class provides functions for reading and writing molecules
*/
class dtReader{
public:
    dtReader();

    ~dtReader();
   
   /** readSDF reads an sdf (mol.sdf) file\n
   *   
   *   This function reads an sdf file. \n
   *   fileName is passed as a std::string\n
   */
   //void readSDF(string fileName, molecule *mol, long int offset=0);
   void readSDF(string fileName, molPtr mol, long int offset=0);
   
   /** readSDFX reads an SDFX (mol.sdfx) file.\n
   *   
   *   The fileName is passed as a std::string\n
   *   It returns true if succeful or false otherwise.\n      
   */
   //static bool readSDFX(string fileName, molecule *mol);
   static bool readSDFX(string fileName, molPtr mol);
   
   /** writeSDF  writes an sdf (mol.sdf) file\n
   *   
   *   This function is used to write an sdf file.\n
   *   if append = 1 the the molecule is appended to fileName\n
   *   if append = 0 then fileName is over written\n
   */
   //void writeSDF(const char *fileName, molecule *mol, int append);
   void writeSDF(const char *fileName, molPtr mol, int append);

   /** writeSDFX writes an sdfx (mol.sdfx) file.\n
   *   
   *   if append = 1 the the molecule is appended to fileName\n
   *   if append = 0 then fileName is over written\n
   */
   //static void writeSDFX(const char *file, molecule *mol, int append);
   static void writeSDFX(const char *file, molPtr mol, int append);

private:
   int SYM2AN(string type);
   string AN2SYM(int an);
   bool checkIntNum(string &str);
   bool checkFloatNum(string &str);
};

};
#endif



























