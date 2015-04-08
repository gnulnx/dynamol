/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.                                    *
 *   john.furr@dynamol.com                                                 *
 ***************************************************************************/
#ifndef SCRIPTFILE_H
#define SCRIPTFILE_H

#include <qobject.h>
#include "scriptobject.h"
#include <qstring.h>
#include <vector>
#include "moldb.h"
#include <qptrvector.h>
#include "sdreader.h"
using namespace std;

class molecule;
class scriptmolecule;
class XmodelView;
class scriptmollist;

/**DETAIL
@author Dynamol Inc.

The file class provides operations for reading and writing mol2 and SDF files.
This class should not be confused with the File (with a capital) class which is used 
to read and write any file type.
*/
class scriptfile : public scriptObject
{
Q_OBJECT
public:
    scriptfile(QObject *parent = 0, const char *name = 0);

    ~scriptfile();
        
public slots:
   /** \brief This function reads a molecule file and returns a molList
   *
   *   Reads a molecule data file and returns a molList containing 
   *   an entry for each molecule in the file.  Warning very large files 
   *   will consume all of your computers memory.  This function does not display 
   *   the molecules.  Use openMol() if you want to display the molecule in the
   *   molView
   *
   *   Typical usage:
   *   <pre>
   *   var molList = file.readMol("tmp.sdf");
   *   for (var i=0; i < molList.size(); i++) {
   *       var mol = molList.getMol(i);
   *       print ( mol.getName() );
   *       ..other cool molecule functions
   *   }
   *   </pre>
   */
    scriptmollist *readMol(QString fileName);
    
    /** \brief Read a section of a molecule data file
    *
    *   This function reads a molecule file and returns the results as a molList.
    *   You can specify the start and end record.
    *
    *   Typical usage:
    *   <pre>
    *   var numOfRecords = file.numOfRecords("tmp.sdf");  //assume it returns 100
    *   var molList = file.readMol("tmp.sdf", 45, 50); //return 5 molecule
    *   </pre>
    */
    scriptmollist *readMol(QString fileName, int start, int end);
    
    /** \brief Read a molecule data file and display in the molView Window
     *
     *   This function reads a molecule data file and displays the molecules in the 
     *   molView and molListView windows
     *
     *   Typical usage:
     *   <pre>
     *   file.openMol("tmp.sdf");
     *   </pre>
     */
    void openMol(QString fileName);

    /** \brief scan the SD file and report number of molecules
    * 
    *    This function returns the number of records in the
    *    sd file.  It returns -1 if no records are found
    *
    *    ypical usage:
    *   <pre>
    *   var numOfRecords = scanSDFile( fileName );
    *   for( var i=0; i<numOfRecords; i++) {
    *      var mol = getMol( i );
    *      ...do something with the molecule
    *   }
    *   </pre>
    */
    int scanSDFile(QString fileName);

    /** \brief  Return molecule at specific position
    *
    *   This function returns the molecule at position.  
    *   You must always call scanSDFile(fileName) before
    *   Using this function.  
    *
    *   Typical usage:
    *   <pre>
    *   var numOfRecords = scanSDFile( fileName );
    *   for( var i=0; i<numOfRecords; i++) {
    *      var mol = getMol( i );
    *      ...do something with the molecule
    *   }
    *   </pre>
    */
    scriptmolecule *getMol(int position);   

    
 
    /** \brief Scan the molecule data file and return the number of records
     *
     *   This function returns the number of records in the SDF (*.sdf) file.
     *   It currently only works with SDF file types.
     *
     *   Typical usage
     *   print( file.numOfRecords("tmp.sdf") );
     */
    int numOfRecords(QString fileName);
    
    /** \brief Save the molecule
    *
    *   This function saves the molecule.  Two file types are supported (.mol2 and .sdf)
    *   To save in either format use the proper extension.
    *
    *    Typical usage:
    *    <pre>
    *       file.write(mol, "tmp.sdf", false);  //write sdf file.  no append
    *       file.write(mol, "tmp.sdf", true);  //write sdf file.  append
    *
    *       file.write(mol, "tmp.mol2", false);  //write mol2 file.  no append
    *       file.write(mol, "tmp.sdf", true);  write mol2 file.  append.
    *    </pre>
    */
    bool writeMol(scriptmolecule *mol, QString fileName, bool append);
    
private:
   static sdReader sdRead;
};

#endif





































