/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   emai:  john.furr@dynamol.com
 ***************************************************************************/
#ifndef SDREADER_H
#define SDREADER_H

#include <map>
#include <string>
#include <vector>
#include <qstring.h>

using namespace std;

/**
@author jfurr

This class provides functionality that enables you to read idividual records from an
SD file based on either position or name.  To that end it allows you to check for
records of a certain name in the SD file.  This will probably replace the molDB
sd readers in the future
*/

class molecule;

class sdReader{
public:
    sdReader();

    ~sdReader();
    /** \brief Returns the number records in the file 
    *   
    *   Scans the sd file and stores the offset in the sdFileMap
    *   typical usage:
    *   <pre>
    *   int numRecords = sdReader::scanSDFile(fileName);
    *   for (int i=0; i< numRecords; i++) {
    *      molecule * mol = sdReader::getMolNum();
    *   }   
    *   </pre>
    */
    int scanSDFile(string fileName);

    /**   \brief Return the molecule 
    *
    *    Return the molecule at position.  This file is used in conjunction with
    *    scanSDFile
    */
    molecule *getMolPos(int pos);

   /** \brief Used to store recNum, offset maps
   *
   *    This map is cleared and recreated every time scanSDFile is called
   */
   map<int, long long int> posMap;
private:
   
   /** \brief Used to store the location of records by name
   *
   *    This map stores the offset location to each record by name
   */
   multimap<QString, long long int> nameMap;
   
   /** \brief The currFileName
   *
   *    This is the current fileName that sd records are read from
   */
   string currFileName;
   
   /** \brief Return the molecule from the file
   *
   *    This function reads the molecule at {offset}
   *    from the file {fileName} and returns it;
   */
   molecule *readSD(QString fileName, int offset); 
  
   /** \brief Check to see if str is a Number (Float)
   *
   *    This function is used to insure that the str is a number
   *    It is called by readSD to make sure that the atomNum and bdNum
   *    Make sense
   */
   bool checkFloatNum(string &str); 


   /** \brief Check to see if str is an Integer
   *
   *   This function is used to insure that the str is a number
   *    It is called by readSD to make sure that the atomNum and bdNum
   *    Make sense
   */
   bool checkIntNum(string &str);
};

#endif


