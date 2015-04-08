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
#include <qfiledialog.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <vector>
#include <iomanip>
#include <gaffsig.h>
#include <qmessagebox.h>
#include <qcheckbox.h>
#include <qapplication.h>
#include <qeventloop.h>
#include "licensemanager.h"
#include "gafffphelp.h"
#include "gafffpnet.h"
#include "bayes.h"
#include "hits.h"
//#include "gaff_fp_progress.h"
using namespace std;

int numHits = 0;

void splitString(string in, char del, vector<string> &out) {

   out.clear();
   string curr;
   for (int i=0; i<in.size(); i++) {
       if (in[i] == del) {
          out.push_back(curr);
          curr.clear();
       } else {
          curr += in[i];
       }
   }
   out.push_back(curr);

}

bool fileCheck2(QString fileName, int &count) {
    fstream inFile(fileName.latin1(), ios::in);
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

void fpDialog::sdLoadSelectSlot()
{
QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "Molecules (*.sdf *.SDF)",
                    this,
                    "open file dialog",
                    "Choose a file" );
sdLoadFile->setText(fileName);
}


void fpDialog::fpSaveSelectSlot()
{
QString fileName = QFileDialog::getSaveFileName(
                    "./",
                    "FingerPrints (*.fp)",
                    this,
                    "open file dialog",
                    "Choose a file" );

if ( !fileName.contains("*.fp") ) {
    fileName += ".fp";
}
fpSaveFile->setText(fileName);
}


void fpDialog::fpLoadSelectSlot()
{
QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "FingerPrints (*.fp)",
                    this,
                    "open file dialog",
                    "Choose a file" );
fpTrainFile1->setText(fileName);
}


void fpDialog::fpLoadSelect2Slot()
{
QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "FingerPrints (*.fp)",
                    this,
                    "open file dialog",
                    "Choose a file" );
fpActive->setText(fileName);
}


void fpDialog::fpLoadLocalSlot()
{
    QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "FingerPrints (*.fp)",
                    this,
                    "open file dialog",
                    "Choose a file" );
localFile->setText(fileName);
}

void fpDialog::fpLoadSelect2_2Slot()
{
    QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "FingerPrints (*.fp)",
                    this,
                    "open file dialog",
                    "Choose a file" );
testFile2->setText(fileName);

}


void fpDialog::fpBuildSlot()
{
  dt::gaffSig gs;
  gs.readSubSets(-1);
  QString sdFile =  sdLoadFile->text();
  QString fpFile =  fpSaveFile->text();
  
  gs.processFile(sdFile, fpFile, 3);
}


void fpDialog::testFile2Slot()
{
    QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "FingerPrints (*.fp)",
                    this,
                    "open file dialog",
                    "Choose a file" );
fpTestFile1->setText(fileName);
}

void fpDialog::fpSaveChangedSlot( const QString &text )
{
   
}


void fpDialog::testModelSlot()
{
   testFile = fpTestFile1->text();
   QString trainFile = fpTrainFile1->text();
   QString qProb = minProbEdit->text();
   QString qDescNum = descNumEdit->text();
   minProb = qProb.toFloat();
   descNum = qDescNum.toInt();
   //features = "features.txt";
   activeFile = trainFile;

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


      //LINUX 2
   QString DYNAMOL = getenv("DYNAMOL");
   QString PATH = DYNAMOL + "/FingerPrint/";
     //Now we classify (screen the div.fp stuff  
  
   //WINDOWS 1
//   QString PATH ="FingerPrint\\";
   QString divFPPath = PATH +"div.fp";
   QString testFPPath = testFile;
   map<QString, float> Hits;
   numHits = 100;
      
   localFileSearch(divFPPath, numHits, Hits);
   /*
   if (!entropyAndFeatures(activeFile))
	   return;

  
    //Score active file Hits
       
       map<QString, float> Hits;

       if (!scoreAct_andTest(Hits, activeNames, act_and_test) )
	   return;
   
   int numHits = 100;
   
   if (!Bayes::classify(features, gaff3SEPath, divFPPath, numHits, Hits) ) {
	   return;
   }
   */ 
       vector< pair<QString, float> > mapVec (Hits.begin(), Hits.end());
       hitsToMapVec(mapVec, Hits);
      
    
       float hits = 0.0;
       float activeHits = 0.0;
       for (int i=0; i<mapVec.size(); i++) {
	   if ( i < numHits ) {
	       if (act_and_test.find(mapVec[i].first) != act_and_test.end()) {
		   hits += 1;
	       }
	       if (activeNames.find(mapVec[i].first) != activeNames.end()) {
		   activeHits += 1;
	       }
	   }
       }
       
       
       //Set Training set hit rate
       QString qHits; 
       qHits.setNum( activeHits/trainSetNum );       
       hitRate->setText(qHits);
       
       //set test set hit rate
       //int testSetNum = (act_and_test.size()-activeNames.size());
       if (testSetNum != 0) {
	   qHits.setNum( (hits-activeHits)/testSetNum);
	   hitRate_3->setText(qHits);
       }
       
       qHits.setNum( hits/(testSetNum + trainSetNum) );
       hitRate_3_2->setText(qHits);
}



void fpDialog::seachLibrarySlot()
{
    activeFile = fpActive->text();
    if (activeFile == "") {
	QMessageBox::critical(0, "Error", "You must provide an active file to train with");
	return;
    }
    testFile = testFile2->text();
    features  = "features.txt";
    QString qProb = minProbEdit->text();
    QString qDescNum = descNumEdit->text();
    minProb = qProb.toFloat();
    descNum = qDescNum.toInt();
    numHits = numResults->text().toInt();
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
   if (radioLocal->isChecked()) { 
       QString locFile = localFile->text();
       if ( locFile != "" && !fileCheck(locFile) ) {
	QMessageBox::critical(0, "Error", "Local (fp) file could not be opend");
	return;
       }
    
	
       /** If no commercial license is found then only allow screening of files with 100,000
	 compounds
        */
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
       /** END LICENSE CHECK SECTION */
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
       if (!Bayes::classify(features, gaff3SEPath, locFile, numHits, Hits) ) {
	   return;
       } 
       prog->check3->setChecked(true);
       el->processEvents(QEventLoop::ExcludeUserInput);
       vector< pair<QString, float> > mapVec (Hits.begin(), Hits.end());
       hitsToMapVec(mapVec, Hits);
      
    
       float hits = 0.0;
       float activeHits = 0.0;
       for (int i=0; i<mapVec.size(); i++) {
	   if ( i < numHits ) {
	       if (act_and_test.find(mapVec[i].first) != act_and_test.end()) {
		   hits += 1;
	       }
	       if (activeNames.find(mapVec[i].first) != activeNames.end()) {
		   activeHits += 1;
	       }
	   }
       }
       
       QString qHits; 
       qHits.setNum( activeHits/trainSetNum );       
       hitRate_2->setText(qHits);
       if (testSetNum != 0) {
	   qHits.setNum( (hits-activeHits)/testSetNum);
	   hitRate_2_2->setText(qHits);
       }
       
       qHits.setNum( hits/(trainSetNum + testSetNum) );
       hitRate_2_3->setText(qHits);
       hitsDialog  *HITS = new hitsDialog(this);
       HITS->buildTable(mapVec, activeNames, act_and_test, numHits);
       HITS->show();

   } 
   
   // START OF THE NETWORK BASED SEARCH.  yOU MUST MAKE SURE THAT ONLY THE FEATURE
   // AND SE FILE'S ARE SENT ACROSS THE NETWORK
   else if (radioZinc->isChecked()) {
       //cout <<"Network search"<<endl;
       if( !licenseManager::simpleCheck()) {
	   QString Error = "A commercial license is required to screen against the ZINC database";	 
	   ////cout <<Error<<endl;
	   QMessageBox::critical(0, "License Error", Error);
	   return;
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
       //cout <<"HERE 3"<<endl;
       //QString host = "10.11.10.121";
       QString host = "24.97.144.147";
       //QDialog *d = new QDialog(this);
       //QLabel *l = new QLabel("Hi There\n", d);
       // d->show();
       gaffFpNet *gNet = new gaffFpNet(host, 80);
       //gNet = new gaffFpNet(host, 80);
       gNet->setFileNames(features);
       gNet->setLogFile("gafffp.log");
       //l->setText("Now Running");
       //cout <<"HERE 4"<<endl;
       gNet->runGaffFpBg(0);
       //cout <<"HERE 5"<<endl;
       prog->check2->setChecked(true);
       el->processEvents(QEventLoop::ExcludeUserInput);
       testModel_2->setEnabled(false);
       connect(gNet, SIGNAL( gaffFpDone()), this, SLOT(gaffFpDoneSlot()));
      
 //      connect(gNet, SIGNAL( conFail()), this, SLOT(gaffFpDoneSlot()));
  
   //    connect(gNet, SIGNAL( conFail()), this, SLOT(busySlot()));
       connect(gNet, SIGNAL( connClosed()), this, SLOT(busySlot()));
       
   }
   
}


bool fpDialog::entropyAndFeatures( QString &activeFile )
{
   if (!Bayes::buildEntropyFile(activeFile))
         return false;
       //Now we select the features
       //LINUX 2
       QString DYNAMOL = getenv("DYNAMOL");
       QString PATH = DYNAMOL + "/FingerPrint/";
   
       //WINDOWS 1
//QString PATH ="FingerPrint\\";

       QString fgSEPath = "fp.se";
       
       gaff3SEPath = PATH + "gaff3SE.se";
       
	   
       if (!Bayes::selectFeatures(fgSEPath, gaff3SEPath, descNum, minProb ))
	   return false;	
       features = "features.txt";
       return true;
}


bool fpDialog::scoreAct_andTest( std::map<QString, float> &Hits, std::set<QString> &activeNames, std::set<QString> &act_and_test )
{ 
   //int numHits = numResults->text().toInt();
   //cout <<"Scoring activeFie: " << activeFile << endl;
   if (!Bayes::classify(features, gaff3SEPath, activeFile, numHits, Hits) ) {
	   QMessageBox::critical(0, "error", "Bayes::classify failed");
	   return false;
   }
   //QMessageBox::critical(0, "error", "After Bayes::classify");
   //cout <<"HERE 1"<<endl;
   map<QString, float>::iterator mi = Hits.begin();
   for (mi; mi != Hits.end(); mi++) {
      activeNames.insert(mi->first);   
   }
   //cout << "HERE 2"<<endl;
       
       //Score test File
   if (testFile != "") {
      //cout <<"Scoring testFile "<< testFile << endl;
      if (!Bayes::classify(features, gaff3SEPath, testFile, numHits, Hits) ) {
         return false;
      } 
   }
   //cout <<"HERE 3"<<endl;

   //Make a set of the active and test (active) compound names
   mi = Hits.begin();
   for (mi; mi != Hits.end(); mi++) {
      act_and_test.insert(mi->first);   
   }
   //cout <<"Leaving scoreAct_andTest"<<endl;
}

/** This function builds a sorted vector based on score */
bool fpDialog::hitsToMapVec(std::vector< std::pair<QString, float> > &mapVec, std::map<QString, float> &Hits)
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
/*
       double max = -100000;
       double min = +1000000000;
       for (int i=0; i<mapVec.size(); i++) {
          if (mapVec[i].second < min) 
             min = mapVec[i].second;
          if (mapVec[i].second > max) 
             max = mapVec[i].second;
       }
       double m = (1.0-.5) / (max-min);
       double b = 1.0 -(m*max);
       double c = 0 - (m*min);
       cout <<"m is: " << m << endl;
       cout <<"b is; " << b << endl;
       cout <<"c is: " << c << endl;
       cout <<"max: "<< max << endl;
       cout <<"min: " << min << endl;
       for (int i=0; i<mapVec.size(); i++) {
          cout <<"before: " << mapVec[i].second << endl;
          mapVec[i].second = m*mapVec[i].second /(mapVec.size()-1);
          cout <<"after: " << mapVec[i].second << "\n"<<endl;
       }
     */ 
/*       
       float total =0.0;
       for (int i=0; i<mapVec.size(); i++) {
	   total += mapVec[i].second;
       }
       
       for (int i=0; i<mapVec.size(); i++) {
	   mapVec[i].second /= total;
       }
*/
	   return true;
}


void fpDialog::dbClickedSlot()
{
   int num = numResults->text().toInt();
   if (num > 200) {
       numResults->setText(tr("200"));
   }
   
   numResults->setText("100");
}


void fpDialog::busySlot()
{
    //cout <<"busySlot"<<endl;
    testModel_2->setEnabled(true);
    //delete prog;
    //cout <<"testModel_2 was reenabled"<<endl;
}

void fpDialog::gaffFpDoneSlot()
{
    QEventLoop *el = QApplication::eventLoop();
    testModel_2->setEnabled(true);
    ifstream files("gafffp.log", ios::in);
	if (!files) {
		QMessageBox::critical(0, "error", "gafffp.log file not found. fpDialog::gaffFpDoneSlot ");
	}
    //QString nameFile, sdFile;
    string nameFile, sdFile;
    files >> nameFile >> sdFile;
    //cout << nameFile << endl;
    //cout << sdFile << endl;
    
    //ifstream inFile(fileName, ios::in);
   
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
       qHits.setNum( activeHits/activeNames.size() );       
       hitRate_2->setText(qHits);
       
       //set test set hit rate
       int testSetNum = (act_and_test.size()-activeNames.size());
       if (testSetNum != 0) {
	   qHits.setNum( (hits-activeHits)/testSetNum);
	   hitRate_2_2->setText(qHits);
       }
       
       qHits.setNum( hits/act_and_test.size() );
       hitRate_2_3->setText(qHits);
       hitsDialog  *HITS = new hitsDialog(this);
       HITS->buildTable(mapVec, activeNames, act_and_test, numHits);
       HITS->show();
       
       delete prog;
       QString qsdFile = sdFile;
       emit runDone(qsdFile);
}




void fpDialog::helpSlot()
{
    gafffpHelp *dialog = new gafffpHelp(0, "Help");
    while(dialog->exec()) {
	
    }
}


void fpDialog::zincSlot( bool state)
{
    if (state) {
	
	localFile->setEnabled(false);
	textLabel6->setEnabled(false);
	fpLoadLocal->setEnabled(false);
    } else {
	localFile->setEnabled(true);
	textLabel6->setEnabled(true);
	fpLoadLocal->setEnabled(true);
    }
    
     
}




bool fpDialog::fileCheck( QString &fileName )
{
    ifstream inFile(fileName.latin1(), ios::in);
    if (inFile) {
	return true;
    }
    return false;
}




bool fpDialog::localFileSearch( QString &locFile, int numHits, std::map<QString, float> &Hits )
{
   //cout <<"HERE 1"<<endl;
   prog = new gaffProg(0, "Progress", true);
   prog->show();
   QEventLoop *el = QApplication::eventLoop();
   el->processEvents(QEventLoop::ExcludeUserInput);
       
   //cout <<"prog->show() called"<<endl;
   //Calculate the entropy and the features
   if (!entropyAndFeatures(activeFile))
       return false;
                    
   prog->check1->setChecked(true);
   el->processEvents(QEventLoop::ExcludeUserInput);
   float hitRate = -1.0;
       
   //Score active file Hits
   //set<QString> activeNames;
   //set<QString> act_and_test;
   

   if (!scoreAct_andTest(Hits, activeNames, act_and_test) )
      return false;
   //Score local db hits
   prog->check2->setChecked(true);
   el->processEvents(QEventLoop::ExcludeUserInput);
   if (!Bayes::classify(features, gaff3SEPath, locFile, numHits, Hits) ) {
      return false;
   } 
   prog->check3->setChecked(true);
   el->processEvents(QEventLoop::ExcludeUserInput);
   
}



bool fpDialog::localFileSearch2( QString &locFile, int numHits, std::map<QString, float> &Hits )
{

    return true;
}


void fpDialog::newFunction()
{

}


