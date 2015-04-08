/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "tableexporter.h"
#include "qtable.h"
#include "table.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "moldb.h"
#include <qheader.h>
#include "molecule.h"
#include <map>
using namespace std;

tableExport::tableExport(Table *table, QObject *parent, const char *name)
 : QObject(parent, name)
{
   this->table = table;
   this->molTable = table->table;
}

tableExport::tableExport(QTable *table, QObject *parent, const char *name)
 : QObject(parent, name)
{
   //this->table = table;
   this->molTable = table;
}


tableExport::~tableExport()
{
}

bool tableExport::exportSD(QString fileName, int row, int col) {
   //////////cout <<"tableSDExport::exportSD"<<endl;
   //////////cout <<"fileName: " << fileName << endl;
   //////////cout <<"row: " << row << endl;
   //////////cout <<"col: " << col << endl;
   
   /**row and col ints
   *  0   ----   all
   *  1   ----   selected
   *  2   ----   unselected
   */
   /** You should put something here to force the use of the correct column incase
   *   It gets moved
   */

/*
   for (int i=0; i<table->numRows(); i++) {
      if (table->isRowSelected(i) ) {
         QString name = table->text(i, 0);
         QString fileName = fileMap[name];
         int offSet = offSetMap[name];
         emit viewMol(fileName, offSet);
      }
   }
*/
//   if (row == 0 && col == 0)
	exportAll(fileName, row, col);
	return true;
}

bool tableExport::exportAll(QString fileName, int row, int col) {
    QHeader *h = molTable->horizontalHeader();

   int hIndex = -1;
   for (int i=0; i<h->count(); i++) {
      if ( h->label(i) == "Molecule") {
          hIndex = i;
          break;
      }
   }


   molDB db;
   for (int i=0; i<molTable->numRows(); i++) {
      if (row == 0 || (molTable->isRowSelected(i, true) && row == 1) ||
	 (!molTable->isRowSelected(i, true) && row == 2) ) 
      {
         molecule *mol;
         QString molName = molTable->text(i, hIndex);
         QString fileMapName = table->fileMap[molName];
         int offSet = table->offSetMap[molName];

         mol = db.readSD(fileMapName, offSet, false);
         mol->clearPropMap(); 
         for (int j=0; j<molTable->numCols(); j++) {
            if (col == 0 || (molTable->isColumnSelected(j, true) && col == 1) ||
               (!molTable->isColumnSelected(j, true) && col == 2) )
            {
               QString propName = h->label(j);
	       if (propName != "Molecule") {
                  QString propValue = molTable->text(i, j);
                  mol->addPropValuePair(propName, propValue);  
               }
            }
         }//end col loop
	 db.writeSDF(fileName, mol, 1);
      }//end row loop
   }
   return true;
}


bool tableExport::exportText(QString fileName, QString delim, int row, int col) {
   ofstream outFile(fileName.latin1(), ios::out);
   if (!outFile) {
	//////////cout <<"File not opened for writing"<<endl;
   }
   
   //First section writes out the header
   QHeader *h = molTable->horizontalHeader();
   for (int j=0; j<molTable->numCols(); j++) {
         if (col == 0 || (molTable->isColumnSelected(j, true) && col == 1) ||
	    (!molTable->isColumnSelected(j, true) && col == 2) )
	 {
            QString header = h->label(j);
            outFile << header << delim;
         
         }
   }
   outFile << endl;
   
   
   for (int i=0; i<molTable->numRows(); i++) {
      if (row == 0 || (molTable->isRowSelected(i, true) && row == 1) ||
	   (!molTable->isRowSelected(i, true) && row == 2) ) 
      {
      QString line = "";
      for (int j=0; j<molTable->numCols(); j++) {
         if (col == 0 || (molTable->isColumnSelected(j, true) && col == 1) ||
	    (!molTable->isColumnSelected(j, true) && col == 2) )
	 {
	     QString text = molTable->text(i, j);
             line += text;
             line += delim;
         }
      }
      outFile << line << endl;
      }  
   }
   return true;
}









