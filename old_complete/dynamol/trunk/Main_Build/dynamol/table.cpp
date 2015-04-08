/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "table.h"
#include "molTable.h"
#include <iostream>
#include <qaction.h>
#include <qfiledialog.h>
#include <qstring.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <set>
#include <time.h>
#include "scriptmolecule.h"
#include "dynascript.h"

#include <qtable.h>
#include <qvaluelist.h>
#include <qsargument.h>
#include <qheader.h>

#include "moldb.h"

#include <qlistview.h>
#include "opendesc.h"

#include "molecule.h"
#include "trashcan.h"
#include "tableexporter.h"

#include <qmessagebox.h>

using namespace std;

Table::Table(dynaScript *ide, QObject *parent, const char *name)
 : QObject(parent, name)
{
   molTable *tb = new molTable();
   table = tb->table1;
   //connect(tb, SIGNAL(openFile()), this, SLOT(fileOpenSlot()));
   connect(tb->fileOpenAction, SIGNAL(activated()), this, SLOT(fileOpenSlot()));
   //connect(tb->fileExporttextAction, SIGNAL(activated()), this, SLOT(exportText()));
   //connect(tb->fileExportSDFAction, SIGNAL(activated()), this, SLOT(exportSDF()));
   connect(tb->viewselectedAction, SIGNAL(activated()), this, SLOT(showSelected()));
   connect(tb->viewunselectedAction, SIGNAL(activated()), this, SLOT(showUnselected()));
   connect(tb->calculateDescriptorsAction, SIGNAL(activated()), this, SLOT(descSelect()));
   connect(tb, SIGNAL(sdExportSignal(QString, int, int)), this, SLOT(sdExportSlot(QString, int, int)));
   connect(tb, SIGNAL(textExportSignal(QString, QString, int, int)), this, SLOT(textExportSlot(QString, QString, int, int)));
   connect(tb, SIGNAL(gaffFPSignal()), this, SLOT(gaffFPSlot()));
   
   connect(tb, SIGNAL(showSelectedSignal()), this, SLOT(showSelected()));
   connect(tb, SIGNAL(clearListView()), this, SLOT(clearListViewSlot()));
   tb->show();
   this->ide = ide;
}


Table::~Table()
{
   delete table;
   //////////cout <<"You are in the table destructor"<<endl;
   exit(0);
   
}

void Table::closeEvent( QCloseEvent * e ) {
//////////cout <<"closeEvent"<<endl;
}

void Table::fileOpenSlot() {
 const QString dir = "./";
 const QString type = "SDF (*.sdf)";
 const QString name = "open file dialog";
 const QString fileName = "Choose a file";
 QString s = QFileDialog::getOpenFileName(
                    dir,
                    type,
                    0,
                    name,
                    fileName);
 importSDF(s);
 
}

void Table::importSDF(QString fileName) {
   //QMessageBox::critical( 0, "Dynamol", "importSDF");
   ifstream inFile(fileName.latin1(), ios::in | ios::binary);

   if (!inFile) {
	   QMessageBox::critical( 0, "Dynamol", "File not opened");
   }
   int count = 0;
   
   string line;
   int offSet = inFile.tellg();
   string name;
   getline(inFile, name);
   //inFile >> name;
   
   time_t t1 = time(NULL);   
   QString qName = name;
   checkName(qName);
   
   offSetMap[qName] = offSet;
   fileMap[qName] = fileName;
   
   map<QString, QString> propValMap;
   propValMap["name"] = qName;
   
   int c = 1;

   //vector< pair<QString, QString> > propValVec;
   vector< map<QString, QString> > propValVec;
   set< QString > colNames;
   //QMessageBox::critical( 0, "Dynamol", "Starting main read loop");
   while (inFile >> name) {
      if (c == 1 || (name == "$$$$" && !inFile.eof())) {
         QString qName;
         if (c != 1) {
            offSet = inFile.tellg();
            //inFile >> name;
            getline(inFile, name);
            getline(inFile, name);
            if (inFile.eof()) 
            break;
            qName = name;
            checkName(qName);         
            fileMap[qName] = fileName;
            offSetMap[qName] = offSet;
        
            /** Display the name of the compound that is being exported */ 
	    //////////cout << qName << endl;
	 
	    //move down to atm and bond nums
	    getline(inFile, name);
	    getline(inFile, name);
	    getline(inFile, name);
	    //getline(inFile, name);
	 
	    //determine numOfAtms and num of Bonds
	    string atmNumString = name.substr(0,3);
            string bdNumString =  name.substr(3,3);
            int atmNum = atoi(atmNumString.c_str() );
            int bdNum = atoi(bdNumString.c_str() );
	 
	     //seek to end of atom section
	     getline(inFile, name);

	     int size = name.size();
	     inFile.seekg(size*(atmNum-1), ios::cur);
	     inFile.seekg(bdNum*18, ios::cur);
	 
	     //map<QString, QString> propValMap;
         }
	 
         while (true) {
	    getline(inFile, name);
            ////////////cout <<"name: " << name << endl;
            if (name[0] == '>') {
               QString qName = "";
               int count = 0;
               while (name[count] != '<') {
                  count++;
               }
               count++;
               while (name[count] != '>') {
                  qName += name[count];
                  count++;
               }
               string value;
               getline(inFile, value);
   
               propValMap[qName] = value;
               colNames.insert(qName);
           }
   
	   if (name.substr(0,4) == "$$$$") {
	    	inFile.seekg(-25, ios::cur);
		break;
	   }
	    
	   
	   if (inFile.eof()) {
	      return;
	   }
	 } 
     
	 if (c != 1) {
            propValMap["name"] = qName;
         }
         
         
     propValVec.push_back(propValMap);
     propValMap.clear();
	 c++;
      }
   }
   
   table->insertRows( table->numRows(), c-1 );
   count = 0;
   map<QString, QString>::iterator mapIt = fileMap.begin();
   for (mapIt; mapIt != fileMap.end(); mapIt++) {
      QString name = mapIt->first;   
      table->setText( count, 0, name );
      rowMap[name] = count;      
      count++;
   }
   
   //return; 
   //////////cout <<"Inserting collumns  "<< propValVec.size() <<endl;
   map<QString, int> colMap;
   vector<QString> cn(colNames.begin(), colNames.end());
   //////////cout <<"total columns: " << cn.size() << endl;
   //int hold = 0;
   //cin >> hold;
   for (int i=0; i<cn.size(); i++) {
      addColumn(cn[i]); 
      colMap[cn[i]] = getColIndex(cn[i]);
   }
   //////////cout <<"Back from inserting collumns"<<endl;
   //Now for th column insertion

   map<QString,QString>::iterator mapIter; 
   map<QString, int>::iterator cm;
   for (int i=0; i<propValVec.size(); i++) {
      map<QString, QString> rowValMap = propValVec[i];
      QString name = rowValMap["name"];
      int rowIndex = rowMap[name];
      cm = colMap.begin();
      for (cm; cm!= colMap.end(); cm++) {
          QString colName = cm->first;
          int colIndex = colMap[colName];
          mapIter = rowValMap.find(colName);
          if (mapIter != rowValMap.end()) {
             table->setText(rowIndex, colIndex, rowValMap[colName]);     
          } else {
            ////////////cout <<"col not found"<<endl;
            table->setText(rowIndex, colIndex, "");
          }              
      }
//      map<QString, QString>::iterator mapIt = rowValMap.begin();
  //    QString name = propValVec[i]["name"];
      //int rowIndex = rowMap[name];
      //map<QString, QString> rowValMap = propValVec[i]; 
      /*
      //////////cout <<name <<" of: " << propValVec[i].size() << endl;
      if (rowIndex != -1) {
         map<QString, int>::iterator cm = colMap.begin();
         for (cm; cm != colMap.end(); cm++) {
            map<QString, QString> propMap = mapIt;
         //for (mapIt; mapIt != propValVec[i].end(); mapIt++) {
            QString colName = mapIt->first;
            ////////////cout << colName << endl;
            int colIndex = colMap[colName];
            //////////cout << "colIndex: " << colIndex << setw(12) << colName << endl;
            table->setText(rowIndex, colIndex, mapIt->second);

         }
         if (i == 1536) {
            break;
            //////////cout << name <<setw(12) << propValVec[i].size()<< endl;
            if (i == 1536) break;

         }
      }
      */
   }


}


int Table::getRowIndex(QString text, QString colName) {
   int index = -1;
   
   //First we need to determine which column has the correct header
   QHeader *h = table->horizontalHeader();
   int hIndex = -1;
   for (int i=0; i<h->count(); i++) {
      if ( h->label(i) == colName) {
          hIndex = i;
          break;
      }
   }
   if (hIndex == -1)
      return index;
      
   //Now lets seach the rows for the text in column hIndex   
   for (int i=0; i<table->numRows(); i++) {
      QString rowText = table->text(i, hIndex);
//      //////////cout <<"Searching: " <<rowText << setw(12) << i << setw(12) << text << endl;
      if (rowText == text)
         return i;
   }
   return index;
}

void Table::checkName(QString &name) {
   long int count = 1;
   QString nameHold = name;
   while ( fileMap.find(name) != fileMap.end()) {
      QString num;
      num.setNum(count);
      
      name = nameHold + "_" + num;
      count++;
   }
}


/** This function is used to view the selected molecules */
void Table::showSelected() {
   /** You should put something here to force the use of the correct column incase
   *   It gets moved
   */
   for (int i=0; i<table->numRows(); i++) {
      if (table->isRowSelected(i) ) {
         QString name = table->text(i, 0);
         QString fileName = fileMap[name];
         int offSet = offSetMap[name];
         emit viewMol(fileName, offSet);
      }
   }
}
   
   /** This function is used to view the unselected molecules */
void Table::showUnselected() {
   //////////cout <<"showUnselected.... is not finished"<<endl;
   emit viewMol("TestFile", 10);
}

void Table::descSelect() {
   vector<QString> descVec;
   OpenDesc OD(ide, descVec);
   addColumns(descVec);
   //return;
   molDB db;
   time_t t1 = time(NULL);
   for (int i=0; i<table->numRows(); i++) {
      if (!table->isRowSelected(i) ) {
        QString molName = table->text(i, 0);
        QString fileName = fileMap[ molName ];
        int offSet = this->offSetMap[ molName ];
        //time_t t2 = time(NULL);
        ////////////cout <<"map time: " << t2-t1 << endl;   
   
      
        molecule *mol = db.readSD(fileName, offSet);
       
        mol->propMap.clear();
        //////////cout <<mol->getName() << setw(12) << i << " of "<< table->numRows() << endl;
        mol->setName(molName);
      
        //time_t t3 = time(NULL);
        ////////////cout <<"readMol time: " << t3-t2 << endl;
        //run molecule and update table
        ////////////cout <<"Running mol...table"<<endl;
        OD.runMol(mol);
        //time_t t4 = time(NULL);
        ////////////cout <<"runMol time: "<< endl;
        ////////////cout <<"updating table"<<endl;
        updateTable(mol);
        
        ////////////cout <<"After update table"<<endl;
        //time_t t5 = time(NULL);
        ////////////cout <<"update time: "<< endl;
      
        //delete molecule
        ////////////cout <<"deleting molecule"<<endl;
        vector<Object *> molVec;
        molVec.push_back(mol);
        TrashCan t(molVec);
        t.empty();
        ////////////cout <<"Molecule was deleted"<<endl;
        //time_t t6 = time(NULL);
        ////////////cout <<"del time: " << endl;
        ////////////cout <<"total time: " << t6 - t1 << endl;    
      } 
   }
   time_t t2 = time(NULL);
   //////////cout <<"total time: " << t2-t1 <<   endl;
   //exit(0);
}

void Table::updateTable(molecule *mol) {
   time_t t1 = time(NULL);
   ////////////cout <<"mol->propMap.size(): " << mol->propMap.size() << endl;
   map<QString, QString>::iterator propIt = mol->propMap.begin();
   map<QString, int>::iterator collIt;
   QHeader *h = table->horizontalHeader();
   
   int row = rowMap[mol->getName()];
   for (propIt; propIt != mol->propMap.end(); propIt++) {
      QString prop = propIt->first;
      QString value = propIt->second;
      ////////////cout <<"Adding header: " << prop << endl;
      //h->addLabel(prop);
      
      int hIndex = -1;
      for (int i=0; i<h->count(); i++) {
         if ( h->label(i) == prop) {
             hIndex = i;
             break;
         }
      }
      
      int colIndex = -1;
      if (hIndex == -1) {
         //colIndex = h->addLabel(prop);
         int index = table->numCols();
         table->insertColumns(index, 1);
         h->setLabel(index, prop);
         ////////////cout <<"inserted new header" << endl;
         //table->insertColumns(colIndex, 1);
         table->setText(row, index, value);
      } else {
      
         table->setText(row, hIndex, value);
      
      } 
      
    time_t t2 = time(NULL);
    ////////////cout <<"UPDATE TIME is: " << t2-t1 << endl;
    //int test = 0;
    //cin >> test;
      
      //check for the column
      //QString QHeader::label ( int section ) const
      //Returns the text for section section. If the section does not exist, a QString::null is returned.

       //Example: helpsystem/tooltip.cpp. 

      
   }
}

int Table::getColIndex(QString name) {
   QHeader *h = table->horizontalHeader();
   for (int i=0; i<h->count(); i++) {
      if ( h->label(i) == name) {
          return i;
      }
   }
   return -1;
}

int Table::addColumn(QString name) {
   QHeader *h = table->horizontalHeader();
   int hIndex = -1;
   for (int i=0; i<h->count(); i++) {
      if ( h->label(i) == name) {
          hIndex = i;
          break;
      }
   }
   int index = hIndex;
   int colIndex = -1;
   if (hIndex == -1) {
      index = table->numCols();
      table->insertColumns(index, 1);
      h->setLabel(index, name);
   } 
   
   return index;
}

void Table::addColumns(vector<QString> &descVec) {

   QHeader *h = table->horizontalHeader();

   for (int i =0; i < descVec.size(); i++) {
      QString name = descVec[i];

      int hIndex = -1;
      for (int i=0; i<h->count(); i++) {
         if ( h->label(i) == name) {
             hIndex = i;
             break;
         }
      }

      int colIndex = -1;
      if (hIndex == -1) {
         //colIndex = h->addLabel(prop);
         int index = table->numCols();
         table->insertColumns(index, 1);
         h->setLabel(index, name);
      } else {
      }
    time_t t2 = time(NULL);

   }
}


void Table::sdExportSlot(QString fileName, int row, int col) {
   tableExport *exporter = new tableExport(this);
   exporter->exportSD(fileName, row, col);
   delete exporter;
}

void Table::textExportSlot(QString fileName, QString delim, int row, int col) {
   tableExport *exporter = new tableExport(this);
   exporter->exportText(fileName, delim, row, col);
   delete exporter;
}

void Table::gaffFPSlot() {
   //////////cout <<"Welcome to the gaffFPSlot() "<<endl;
   //fpDialog *dialog = new fpDialog(0, 0, true);
   //dialog->show();
}

void Table::clearListViewSlot() {
   //////////cout <<"table::clearListViewSlot()" << endl;
   //////////cout <<"Emitting deleteListView"<<endl;
   emit deleteListView();
}













