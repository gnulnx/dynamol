/***************************************************************************
                          moldb.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef MOLDB_H
#define MOLDB_H

#include <qwidget.h>
#include <qapplication.h>
#include <qsqldatabase.h>


//#include "mollistview.h"

//STL include files
#include <list>
#include <string>
#include <vector>

//C include files
#include <stdlib.h>


//QT includes
#include <qstring.h>

using namespace std;

class molecule;
class protein;
class fragment;
class fragFactory;
/**
  *@author John Furr
  */

/** Currently this class is used as a means to read PDB && mol2 files.  Eventually it will be
  used to store the molecules in an SQL database were they can be quickly accessed.  Ideally
  The program will allow the user to connect to an arbitrary database.  Maybe there
  will be some sort of graphical interface that allows the user to specify which collumn in which
  table the mol data is located.  Also you will want to be able to access other data such as molecular properties.
  It is hoped that the program will be able to pull all this information into a spread sheet so that
  a QSAR like analysis can be performed on it.  I also like the idea of having everything stored inside
  of a database so that the users home directory doesn't get all cluttered up.  You still need to iron
  out some realistic ideas regarding this subject.


*/

class sdDialog;
  

class molDB : public QObject {
  Q_OBJECT
public:
   string sdFile;
   molDB();
   ~molDB();

  QSqlDatabase *defaultDB;// = QSqlDatabase::addDatabase( DB_SALES_DRIVER );

  void read_mol2(string file, vector<molecule *> *currMol = 0);

  /** Function will be used to read in sdf files
      This function should be felxible enough to read an sd file of arbitrary size
      While the sdf file format is constrained by format, programs like bable
      will write the files regardless of the number of atoms || bonds.
      The goal of this function is tob e smart enough to read them in anyway.

      Note the software shoule probably only write sdf files in the normal fashion
  */
  int read_sd(string file, bool prompt);
  
  /** This function is used to read an SDFile into the a vector
  *   Not signal is emitted to update the list view.
  *   You created this function when you needed to read in the frags for
  *   The builder Module.
  *   WARNING** This function reads the entire SDF File...it doesn't prompt you
  */
  static void readSDToMolVec(QString fileName, vector<molecule *> &mols);

  /** This function is used to write a mol2 file
      If append = 1 then the molecule will be appended to the file
  */
  static void writeMol2(const char *file, molecule *mol, int append);

  /** \brief write a .ddb file
  *
  *   The .ddb file is your attempt at a small compact dynamol file format
  *   The dynamol database  format
  */
  static void writeDDB(const char *file, molecule *mol, int append);

  /** \brief Read a ddb file
  *
  *   Expiremental function to read the .ddb format 
  */
  void readDDB(const char *file);
  
  /** This function is used to write an sdf file
      If append = 1 then the molecule will be appended to the file
  */
  static void writeSDF(const char *file, molecule *mol, int append);
  
  /** This function is used to read an MAE file */
  bool readMAE(QString fileName);
  
  /** This is the extended sdf format....it contains the molecule charge 
  */
  static void writeSDFX(const char *file, molecule *mol, int append);
  /** this function is used soley to determine special amber types....ASP neutraul, etc... */
  static void typeFrag(fragment *frag);
  
  /** writePDB.  If append == 1 then add new */
  static void writePDB(char *file, molecule *mol, int append);

  /** As the name suggests this operation reads in a pdb file
  */
  void  read_pdb(string file);


  /** Symbol to atomic number
  */
  static int   SYM2AN(string sym);
  
  static string AN2SYM(int an);

  //Operators for working with the molecule list
  void setMolToBegin();
  int nextMol();
  int prevMol();
  molecule *getMol();

  //Operators for working with the renList
  void setRenListToBegin();
  int   nextRen();
  int   prevRen();
  molecule  *getCurrentRen();

  //Operatros for working with the protein list
  void      setProtToBegin();
  int       nextProt();
  int       prevProt();
  protein   *getCurrentProt();

  //Operators for the fragment list
  void      setFragToBegin();
  int       nextFrag();
  int       prevFrag();
  fragment  *getCurrentFrag();

  /** Return the size of the mols list
  */
  int   numOfMols();

  /**
  */
  int   renSize();

  /** Returns a list of all the molecules
  */
  list<molecule *>  getAllMols();

  /** Return a list of all the molecules
  */
  list<protein *>   getALLProts();
  int               numOfProts();

  /** returns the render list
  */
  list<molecule *> *getRenderList();
    
private:
  list<molecule *>::iterator  currentMol;
  list<molecule *>::iterator  currentRen;
  list<protein *>::iterator   currentProt;
  list<fragment *>::iterator  currentFrag;
  list<molecule *>  mols;
  list<protein  *>  prots;
  list<fragment *>  frags;
  list<molecule *>  *renList;

  fragFactory *fragGen;

 // molListView *listView;

   /** This is used ot block the listView update after molecule has bee read */
   bool signalBlock;
   sdDialog *dialog;
 
 /* This function returns false if the string contains any characters other
  than numbers || +/- sings*/
 static bool checkIntNum(string &str);
 /** this function return false if any characters other than numbers, decimal point && +/- are encountered */
 static bool checkFloatNum(string &str);

 
 signals:
  void  newProtein(protein *prot);
  void  newMolecule(molecule *mol);

  public slots:
    void getSdRange(int start, int end, vector<molecule *> &molVec);                

    /** This function is used to read a single molecule from fileName
    *   It currently only used with the molTable
    */
    molecule *readSD(QString fileName, int offset, bool show=true);

public:
    /** \brief Returns the number records in the file 
    *   
    *   Scans the sd file and stores the offset in the sdFileMap
    *   typical usage:
    *   <pre>
    *   int numRecords = molDB::scanSDFile(fileName);
    *   for (int i=0; i< numRecords; i++) {
    *      molecule * mol = molDB::getMolNum();
    *   }   
    */
    static int scanSDFile(string fileName);

    /*   \brief Return the molecule  
    *
    */
    static molecule *getMolNum(int);

private:
   static map<int, int> sdFileMap;
};

#endif





































