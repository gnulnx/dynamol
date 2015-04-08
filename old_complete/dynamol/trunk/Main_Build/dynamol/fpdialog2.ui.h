/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#include <iostream>
#include <qfiledialog.h>
#include <string>
#include <qstring.h>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <math.h>
#include <vector>
#include <list>
#include <iterator>
#include <iomanip>
#include "moldb.h"
#include "molecule.h"

//Fingerprint includes
#include "../dynaprint/gaffsig.h"

#include <qmessagebox.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qapplication.h>
#include <qeventloop.h>
#include "licensemanager.h"
#include "gafffphelp.h"
#include "gafffpnet.h"
#include "bayes.h"
#include "hits.h"

using namespace std;

int numHits2 = 0;



void fpDialog2::fpBuilderEnableSlot( int but)
{
    if (but == 0) {
 groupBox1->setEnabled(true);
    } else {
 groupBox1->setEnabled(false);
    }
}


void fpDialog2::enableTestSetSlot( bool toggle )
{
    testSetFile->setEnabled(toggle);
    testSetButton->setEnabled(toggle);
}


void fpDialog2::hitNumEnableSlot( QString &text )
{

}


void fpDialog2::hitNumEnableSlot( const QString &text )
{
    if (text == "Local Database") {
 hitNumBox->setEnabled(true);
 localFP->setEnabled(true);
 dbButton->setEnabled(true);
    } else {
 hitNumBox->setEnabled(false);
 localFP->setEnabled(false);
 dbButton->setEnabled(false);
    }
}


void fpDialog2::sdBuildSlot()
{
    QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "Molecules (*.sdf *.SDF)",
                    this,
                    "open file dialog",
                    "Choose a file" );
    sdLoadFile->setText(fileName);
}




void fpDialog2::saveFpSlot()
{
QString fType = fpType->currentText();
QString select = "";
if (fType.contains("gafffp") ) {
      select = "gafffp Fingerprint (*.fp)";
  } else {
      select = "gafffp Fingerprint (*.fp)";
  }
QString fileName = QFileDialog::getSaveFileName(
                    "./",
                    select,
                    this,
                    "open file dialog",
                    "Choose a file" );


if (fType.contains("gafffp") &&  !fileName.contains("*.fp") ) {
    fileName += ".fp";
}

fpSaveFile->setText(fileName);

}


void fpDialog2::QueryLoadSlot()
{
 QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "Molecules (*.sdf *.SDF)",
                    this,
                    "open file dialog",
                    "Choose a file" );
    queryFile->setText(fileName);
}


void fpDialog2::testSetLoadSlot()
{
    
 QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "Molecules (*.sdf *.SDF)",
                    this,
                    "open file dialog",
                    "Choose a file" );
    testSetFile->setText(fileName);
}


void fpDialog2::fpBuildSlot()
{
    
    QString sdFile =  sdLoadFile->text();
    QString fpFile =  fpSaveFile->text();
    if (sdFile != "" && fpFile != "") {
       fp::gaffSig gs;
       gs.readSubSets(-1);
       gs.processFile(sdFile, fpFile, 3);
    }
  
}


void fpDialog2::searchLibrarySlot()
{
    fp::gaffSig gs;
    gs.readSubSets(-1);
    if (sdQuery->isChecked()) {
       QString fpFile = "train.fp";
       gs.processFile(queryFile->text(), fpFile, 3);
       activeFile = fpFile;
   } else if (molViewQuery->isChecked()) {
       ofstream outFile("train.sdf", ios::out);
       outFile.close(); outFile.clear();
       if (viewer->renList->size() == 0) 
           QMessageBox::critical(0, "Mol Error", "There is no molecule in the molView Windows");
       
       list<molecule *>::iterator it= viewer->renList->begin();
       
       for (it; it != viewer->renList->end(); it++) {
                 molecule *mol = *it;
                 molDB::writeSDF("train.sdf", mol, 1);
       }
       gs.processFile("train.sdf", "train.fp", 3);
       activeFile = "train.fp";
     
       
   }
    if (activeFile == "") {
        QMessageBox::critical(0, "Error", "You must provide an active file to train with");
         return;
    }
    if (checkBox5->isChecked() ) {
       gs.processFile(testSetFile->text(), "test.fp", 3);  
       testFile = "test.fp";
   }
    features  = "features.txt";
    minProb = 0.0;//qProb.toFloat();
    descNum = 100;//qDescNum.toInt();
    numHits2 = hitNumBox->text().toInt();
    int testSetNum = 0;
    int trainSetNum = 0;
    if ( !fileCheck2(activeFile, trainSetNum) ) {
       QMessageBox::critical(0, "Error", "Active (fp) file could not be opend");
       return;
    }
    if ( testFile != "" && !fileCheck2(testFile, testSetNum) ) {
       QMessageBox::critical(0, "Error", "Test (fp) file could not be opend");
       return;
    }
    //Check for local or network based search
   if (dbCombo->currentText() == "Local Database") { 
       QString locFile = localFP->text();
       if ( locFile != "" && !fileCheck(locFile) ) {
           QMessageBox::critical(0, "Error", "Local (fp) file could not be opend");
            return;
       }
    
 
       /** If no commercial license is found then only allow screening of files with 100,000
  compounds
        */
       /* 
       if( !licenseManager::simpleCheck()) {
            ifstream inFile(locFile.latin1(), ios::in);
            if (!inFile) {
                QMessageBox::critical(0, "File error", "File not found");
                return;
            }
   
            int count = 0;
            string line;
            while (true) {
               getline(inFile, line);
               if (inFile.eof()) {
                  break;
               }
               if (count == 100001) {
                 QString error = "You must purchase a commercial license to screen against\nmore then 100,000 compounds at a time";
                 QMessageBox::critical(0, "FingerPrint Error", error);
                 return;
               }
               count++;      
           }
        }
        */ 
  
       // END LICENSE CHECK SECTION 
       prog = new gaffProg(0, "Progress", true);
       prog->show();

       QEventLoop *el = QApplication::eventLoop();
       el->processEvents(QEventLoop::ExcludeUserInput);
       
       //Calculate the entropy and the features
       if (!entropyAndFeatures(activeFile))
          return;
                    
       prog->check1->setChecked(true);
       el->processEvents(QEventLoop::ExcludeUserInput);
       float hitRate = -1.0;
       
       //Score active file Hits
       set<QString> activeNames;
       set<QString> act_and_test;
       map<QString, float> Hits;

       if (!scoreAct_andTest(Hits, activeNames, act_and_test) )
          return;
       //Score local db hits
       prog->check2->setChecked(true);
       el->processEvents(QEventLoop::ExcludeUserInput);
       if (!Bayes::classify(features, gaff3SEPath, locFile, numHits2, Hits) ) {
          return;
       } 
       
       prog->check3->setChecked(true);
       el->processEvents(QEventLoop::ExcludeUserInput);
       vector< pair<QString, float> > mapVec (Hits.begin(), Hits.end());
       hitsToMapVec(mapVec, Hits);
    
       float hits = 0.0;
       float activeHits = 0.0;
       for (int i=0; i<mapVec.size(); i++) {
       if ( i < numHits2 ) {
        if (act_and_test.find(mapVec[i].first) != act_and_test.end()) {
           hits += 1;
        }
        if (activeNames.find(mapVec[i].first) != activeNames.end()) {
           activeHits += 1;
        }
       }
       }
       
       QString qHits; 
       qHits.setNum( 100 *(activeHits/trainSetNum) );       
       hitRate_2->setText(qHits);
       if (testSetNum != 0) {
          qHits.setNum( 100 * ((hits-activeHits)/testSetNum));
          hitRate_2_2->setText(qHits);
       }
       
       qHits.setNum( 100* (hits/(trainSetNum + testSetNum)) );
       hitRate_2_3->setText(qHits);
       hitsDialog  *HITS = new hitsDialog(this, false);
       HITS->buildTable(mapVec, activeNames, act_and_test, numHits2);
       HITS->show();
        
       setFinishEnabled(WizardPage_3, true);
   } 
   
   // START OF THE NETWORK BASED SEARCH.  yOU MUST MAKE SURE THAT ONLY THE FEATURE
   // AND SE FILE'S ARE SENT ACROSS THE NETWORK
   else  {
       QString database = dbCombo->currentText();
       cout <<"Right before license check!"<<endl;
       
       if( !licenseManager::simpleCheck()) {
          //QString Error = "A commercial license is required to screen against the ZINC database";  
          //QString Error = "Add support for license check here\n";
          //QMessageBox::critical(0, "License Error", Error);
           //return;
          cout <<"License did not check out...but that should b ok"<<endl;
       }
       prog = new gaffProg(0, "Progress", true);
       prog->show();
       QEventLoop *el = QApplication::eventLoop();
       el->processEvents(QEventLoop::ExcludeUserInput);
       
       if (!entropyAndFeatures(activeFile))
           return;

       prog->check1->setChecked(true);
       
       //Now lets read the features.txt file and send it to Dynamol
       QString features = "features.txt";
       ifstream inFile("features.text");
       string line;
      
       QString host = "24.97.144.147";
      
       gaffFpNet *gNet = new gaffFpNet(host, 80);
       gNet->setFileNames(features);
       gNet->setLogFile("gafffp.log");
       gNet->runGaffFpBg(0);
       prog->check2->setChecked(true);
       el->processEvents(QEventLoop::ExcludeUserInput);
       pushButton7->setEnabled(false);
       connect(gNet, SIGNAL( gaffFpDone()), this, SLOT(gaffFpDoneSlot()));
       connect(gNet, SIGNAL( connClosed()), this, SLOT(busySlot()));
       
   }
   
}




void fpDialog2::hitsToMapVec( std::vector<std::pair<QString, float> > & mapVec, std::map<QString, float> & Hits )
{
    pair<QString, float> tmpPair;
    for (int i=0; i<mapVec.size(); i++) {
       for (int j=i+1; j<mapVec.size(); j++) {
          if (mapVec[j].second > mapVec[i].second) {
             tmpPair = mapVec[j];
             mapVec[j] = mapVec[i];
             mapVec[i] = tmpPair;
         }
       }
    }
}




bool fpDialog2::fileCheck( QString & fileName )
{
    ifstream inFile(fileName.latin1(), ios::in);
    if (inFile) {
        return true;
    }
    return false;
}




bool fpDialog2::fileCheck2( QString fileName, int &count )
{
    ifstream inFile(fileName.latin1(), ios::in);
    if (inFile) {
        count = -1; //first line is a header  
        string line;
        while (true) {
           getline(inFile, line);
           if (inFile.eof()) 
              break;
           
           count++;
        }
        return true;
    }
    return false;
}


bool fpDialog2::entropyAndFeatures( QString & activeFile )
{
    if (!Bayes::buildEntropyFile(activeFile))
         return false;
     //Now we select the features
     QString PATH = "";
     #ifdef LINUX
        QString DYNAMOL = getenv("DYNAMOL");
        PATH = DYNAMOL + "/FingerPrint/";
     #endif
 
     #ifdef WINDOWS
        PATH ="../FingerPrint/";
     #endif

     QString fgSEPath = "fp.se";
       
     gaff3SEPath = PATH + "gaff3SE.se";
       
    
     if (!Bayes::selectFeatures(fgSEPath, gaff3SEPath, descNum, minProb ))
        return false; 
     features = "features.txt";
     return true;
}



bool fpDialog2::scoreAct_andTest( std::map<QString, float> & Hits, std::set<QString> & activeNames, std::set<QString> & act_and_test )
{
  
   if (!Bayes::classify(features, gaff3SEPath, activeFile, numHits2, Hits) ) {
    QMessageBox::critical(0, "error", "Bayes::classify failed");
    return false;
   }
  
   map<QString, float>::iterator mi = Hits.begin();
   for (mi; mi != Hits.end(); mi++) {
      activeNames.insert(mi->first);   
   }

       
       //Score test File
   if (testFile != "") {
      if (!Bayes::classify(features, gaff3SEPath, testFile, numHits2, Hits) ) {
         return false;
      } 
   }


   //Make a set of the active and test (active) compound names
   mi = Hits.begin();
   for (mi; mi != Hits.end(); mi++) {
      act_and_test.insert(mi->first);   
   }
}


void fpDialog2::busySlot()
{

}


void fpDialog2::gaffFpDoneSlot()
{
    setFinishEnabled(WizardPage_3, true);
QEventLoop *el = QApplication::eventLoop();
    pushButton7->setEnabled(true);
    ifstream files("gafffp.log", ios::in);
 if (!files) {
  QMessageBox::critical(0, "error", "gafffp.log file not found. fpDialog::gaffFpDoneSlot ");
 }
    //QString nameFile, sdFile;
    string nameFile, sdFile;
    files >> nameFile >> sdFile;
   
    set<QString> activeNames;
    set<QString> act_and_test;
    map<QString, float> Hits;
       
    //prog->check2->setChecked(true);
  
  if (!scoreAct_andTest(Hits, activeNames, act_and_test) ) {
   QMessageBox::critical(0, "error", "scoreAct_andTest Failed");
      return;
  }
     //QMessageBox::critical(0, "error", "After scoreAct_andTest");
     ifstream inFile(nameFile.c_str(), ios::in);
     string name;
     float score;
     while (inFile >> name >> score) {
  Hits[name] = score;
     }
     /** You should read in the hits_names.txt and add them to the Hits map before this section */
     vector< pair<QString, float> > mapVec (Hits.begin(), Hits.end());
     hitsToMapVec(mapVec, Hits);
     prog->check3->setChecked(true);
     el->processEvents(QEventLoop::ExcludeUserInput);
     float hits = 0.0;
     float activeHits = 0.0;
     for (int i=0; i<mapVec.size(); i++) {
         if (i < 100) {
             if (act_and_test.find(mapVec[i].first) != act_and_test.end()) {
               hits += 1;
             }
             if (activeNames.find(mapVec[i].first) != activeNames.end()) {
                activeHits += 1;
             }
        }
    }
      
       QString qHits; 
       //cout <<"activeHits: " << activeHits << endl;
       //cout <<"activeNames: " << activeNames.size() << endl;
       qHits.setNum( 100 *(activeHits/activeNames.size()) );       
       hitRate_2->setText(qHits);
       
       //set test set hit rate
       int testSetNum = (act_and_test.size()-activeNames.size());
       if (testSetNum != 0) {
            qHits.setNum( 100*((hits-activeHits)/testSetNum));
             hitRate_2_2->setText(qHits);
       }
       
       qHits.setNum( 100*(hits/act_and_test.size() ));
       hitRate_2_3->setText(qHits);
       hitsDialog  *HITS = new hitsDialog(this);
       HITS->buildTable(mapVec, activeNames, act_and_test, numHits2);
       HITS->show();
       
       delete prog;
       QString qsdFile = sdFile;
       emit runDone(qsdFile);
}


void fpDialog2::newFunction()
{

}


void fpDialog2::localDBSlot()
{
QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "Molecules (*.fp)",
                    this,
                    "open file dialog",
                    "Choose a file" );
    localFP->setText(fileName);
}


void fpDialog2::setMolViewSlot( molView *viewer )
{
    this->viewer = viewer;
}


void fpDialog2::helpSlotSlot()
{
    gafffpHelp *dialog = new gafffpHelp(0, "Help");
    while(dialog->exec()) {

    }
}

