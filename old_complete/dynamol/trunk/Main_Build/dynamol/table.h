/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef TABLE_H
#define TABLE_H

#include <qobject.h>
#include <qstring.h>
#include <map>
#include <fstream>
#include <vector>
using namespace std;
/**
@author jfurr
*/


//File offset pair
struct foPair {
   QString fileName;
   long int offset;
};


class QTable;
class dynaScript;
class descSel;
class molecule;
class tableExport;
class Table : public QObject
{
friend class tableExport;
Q_OBJECT
public:
    Table(dynaScript *ide, QObject *parent = 0, const char *name = 0);

    ~Table();

public slots:

   /** \brief This slot connects to the molTable when the user clicks the gaffFP action
    *
  */
   void gaffFPSlot();

   /** Clears the list view slot */	
   void clearListViewSlot();
   
   
   /** \brief This slot catches the sdexport signal from the sdExport class
   *
   *   This slot catches a signal which is then passed on to the tableSDExport class
   *   were the correct records are exportd
   */
   void sdExportSlot(QString fileName, int row, int col);
   
   /** Export the table in text format */
   void textExportSlot(QString fileName, QString delim, int row, int col);
   
   /** as the name implies this function opens a file */
   void fileOpenSlot();
   
   /** This function is used to scan the sdf.  It creates a map between molecule
   *   name and file location
   */
   void importSDF(QString fileName);
   
   /** This function is used to view the selected molecules */
   void showSelected();
   
   /** This function is used to view the unselected molecules */
   void showUnselected();
   
   /** This function will call the OpenDesc constructor which will
   *   pop a listView containing descriptors for the user to select from
   *
   *   This function is also responsible for running calling and running the descriptor functions
   */
   void descSelect();

   /** This function adds new columns to the table.
   *   the columsn will be named according to the QString name
   */
   void addColumns(vector<QString> &descVec);
   
   /** This function works like the addCollumns function but it takes a single
   *   QString as input.  It returns the index were the collumn was inserted
   */
   int addColumn(QString name);

   /** This function returns the index of column "name"
   *   If no column is found it returns -1
   */
   int getColIndex(QString name);  
 
   /** This function return the row containing the text "text" in the column
   *   identified by the header colName.  If no row is found -1 is returned
   */
   int getRowIndex(QString text, QString colName);
protected:
   virtual void closeEvent( QCloseEvent * e );
signals:
   void viewMol(QString fileName, int offSet);
   void deleteListView();
private:
   
   
   /** This function checks to make sure that the molecule "name" doesn't already exist */
   void checkName(QString &name);
   
   /** This function updates the table with prop/value pairs in the molecule
   *   It performs a check to make sure that the propName matches the column name
   */
   void updateTable(molecule *mol);
         
   map<QString, int> offSetMap;
   
   /** This maps the moelcule name to the row number */
   map<QString, int> rowMap; //this maps the molecule row number
      
   map<QString, QString> fileMap;
   
   /** This variable maps a column name with column index for fast lookup */
   map<QString, int> collMap;
   
   dynaScript *ide;
protected:
   QTable *table;
};

#endif








