/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   email:  john.furr@dynamol.com
 ***************************************************************************/
#include "flexalign.h"

//Standard Library Includes
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::multimap;
using std::map;

//C includes
#include <math.h>
#include <time.h>

//Dynamol Specific Includes
#include "molchangeevent.h"
#include "xmodelview.h"
#include "xmodeldoc.h"
#include "molview.h"
#include "mollistview.h"
#include "molecule.h"
#include "atom.h"
#include "moladapter.h"
#include "sdreader.h"
#include "moldb.h"

//QT Includes
#include "qmessagebox.h"
#include "qapplication.h"
#include "qstring.h"
#include "qmutex.h"

//Dynamol Type Library Includes
#include "../dynatype/molecule.h"
#include "../dynatype/dtype.h"

//Dynamol Base Library Includes
#include "../dynabase/utility.h"

//Dyamol Computational Library Includes
#include "../dynacomp/compute.h"
#include "../dynacomp/flexalign.h"
#include "../dynacomp/molecule.h"

flexAlignThread::flexAlignThread(XmodelView *view, string name) 
: dynoThread(NULL) 
{
   
   dcFlexAlign = new dynacomp::flexAlign();
   setName(name);
   this->view = view;

   templ = toAlign = NULL;  
   stop = false;
}

flexAlignThread::~flexAlignThread() {
   delete dcFlexAlign;
   if (templ) delete templ;
   if (toAlign) delete toAlign;
}
int flexAlignThread::rtti() {return 4;}
void flexAlignThread::stopThread() 
{
   stop = true;
   dcFlexAlign->stop = true;
}
void flexAlignThread::setName(string name) {this->name = name;}
QString flexAlignThread::getName() {return this->name;};

void flexAlignThread::setUp(map<string, string> Params) {
   this->Params = Params;
   dcFlexAlign->setUp(Params);
}

void flexAlignThread::run() 
{
try {	
   cout <<"flexAlignThread::run(): " << Params["tempView"] <<" "<<Params["toAlignView"]<< endl;
									
   dcFlexAlign->setInfoText(view->viewer->infoText);
   if (Params["tempView"] == "1" && Params["toAlignView"] == "1") {
	   cout <<"Yep you are here"<<endl;
      if (!molViewAlign() )
		  cout <<"Job not run"<<endl;
   }
   else if (Params["tempView"] == "1" && Params["toAlignView"] == "0") {
      tempViewAlignFile(); 
   }
   else if (Params["tempView"] == "0" && Params["toAlignView"] == "1") {
      tempFileAlignView();
   }
   else if (Params["tempView"] == "0" && Params["toAlignView"] == "0") {
      tempFileAlignFile();
   }
}
catch (const char *msg) {
	cout << msg << endl;
	view->viewer->infoText.clear();
	view->viewer->infoText.push_back(msg);
}
   emit threadDone();
   molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1002));
   e->name = name;
   QApplication::postEvent(&view->jm, e);
}

bool flexAlignThread::tempViewAlignFile() {
	if (view->viewer->renList->size() == 0)
		return false;
   time_t t1 = time(NULL);
   list<molecule *>::iterator mi = view->viewer->renList->begin();
   molecule *realTemp = *mi;
   templ  = new dynacomp::molecule;
   molAdapter::mol2dynacomp(templ, realTemp);
   dcFlexAlign->setTemplateMolecule(templ);

   molDB db;
   sdReader *reader = new sdReader;
   int recs = reader->scanSDFile(Params["toAlignFile"]);
   for (int i=0; i<recs; i++) {
      if (stop) return true;
      toAlign = new dynacomp::molecule;
      molecule *mol = reader->getMolPos(i);

      if (Params["background"] != "1") {
         molChangeEvent *e = new molChangeEvent(static_cast<QEvent::Type>(1011));
         e->mol = mol;
         e->molVec.clear();
         e->molVec.push_back(realTemp);
         e->molVec.push_back(mol);
         QApplication::postEvent(&view->jm, e);
      }

      molAdapter::mol2dynacomp(toAlign, mol);
      dcFlexAlign->setMoleculeToAlign(toAlign);
     
      // This is the pose map.  
      // It is the score mapped to the coordinates
      multimap<float, vector<float > > poseMap;

      dcFlexAlign->run(poseMap);
    
      if (i == 0) {
         string tempName = realTemp->getName();
         tempName += "-template";
         realTemp->setName(tempName);
         if (Params["singleFile"] == "1")
            molDB::writeSDF(Params["outFile"].c_str(), realTemp, 0);
      }
      savePoseMap(poseMap, realTemp, mol);
      delete toAlign;
   } 
    time_t t2 = time(NULL);
    return true;
}

bool flexAlignThread::savePoseMap(
    multimap<float, vector<float> > &poseMap,
    molecule *templ, molecule *mol 
) {
   vector<float> backup_templ, backup_mol;
   for (int i=0; i<templ->atoms.size(); i++) {
      float *cd = templ->atoms[i]->fCoords;
      for (int j=0; j<3; j++)
         backup_templ.push_back(cd[j]);
   }

   for (int i=0; i<mol->atoms.size(); i++) {
      float *cd = mol->atoms[i]->fCoords;
      for (int j=0; j<3; j++)
         backup_mol.push_back(cd[j]);
   }

//   string tempName = templ->getName();
//   tempName += "-template";
//   templ->setName(tempName);
//   if (Params["singleFile"] == "1")
//      molDB::writeSDF(Params["outFile"].c_str(), templ, 0);

   //Save Mol section
   multimap<float, vector<float> >::iterator mi = poseMap.begin();

   for (mi; mi != poseMap.end(); mi++) {
      vector<float> coords = mi->second;
      string score = dynabase::setNum(-mi->first);//-score is correct
      int coordCount = 0;
      for (int j=0; j<mol->atoms.size(); j++) {
         float *cd = mol->atoms[j]->fCoords;
         for (int k=0; k<3; k++) {
            cd[k] = coords[coordCount];
            coordCount++;
         }
      }
      string nameHold = mol->getName();
     
      string newName = nameHold + " [" + score + "]";
      mol->setName(newName);
      mol->propMap["DynaAlignScore"] = score;

      if (Params["singleFile"] == "1")
         molDB::writeSDF(Params["outFile"].c_str(), mol, 1);
      if (Params["multiFile"] == "1") { 
         string name = Params["baseName"] + mol->getName() + ".sdf";
         molDB::writeSDF(name.c_str(), mol, 1);
      }
      mol->setName(nameHold);

      if (Params["tempFlex"] == "1") {
         for (int j=0; j<templ->atoms.size(); j++) {
            float *cd = templ->atoms[j]->fCoords;
            for (int k=0; k<3; k++) {
               cd[k] = coords[coordCount];
               coordCount++;
            }
         }
         templ->propMap["DynaAlignScore"] = score;
         if (Params["singleFile"] == "1")
            molDB::writeSDF(Params["outFile"].c_str(), mol, 1);
         if (Params["multiFile"] == "1") {
            string name = Params["baseName"] + mol->getName() + ".sdf";
            molDB::writeSDF(name.c_str(), mol, 1);
         }
      }
   }


   if (Params["multiFile"] == "1") {
      
   }
      
   int count = 0;
   for (int i=0; i<templ->atoms.size(); i++) {
      float *cd = templ->atoms[i]->fCoords;
      for (int j=0; j<3; j++) {
         cd[j] = backup_templ[count];
         count++;
      }
   }

   count = 0;
   for (int i=0; i<mol->atoms.size(); i++) {
      float *cd = mol->atoms[i]->fCoords;
      for (int j=0; j<3; j++) {
         cd[j] = backup_mol[count];
         count++;
      }
   }
   return true;

}

bool flexAlignThread::tempFileAlignView() {
return true;
}

bool flexAlignThread::tempFileAlignFile() {
   sdReader *tempFile = new sdReader;
   int temps = tempFile->scanSDFile(Params["tempFile"]);
   time_t t1 = time(NULL);
   for (int j=0; j<temps; j++) {
      if (stop) return true;
      templ = new dynacomp::molecule; 
      molecule *realTemp = tempFile->getMolPos(j);

      molChangeEvent *e = new molChangeEvent(
                static_cast<QEvent::Type>(1011)
      );
      e->mol = realTemp;
      e->molVec.clear();
      e->molVec.push_back(realTemp);
      QApplication::postEvent(&view->jm, e);

      molAdapter::mol2dynacomp(templ, realTemp);
      dcFlexAlign->setTemplateMolecule(templ);
 
      molDB db;
      sdReader *alignFile = new sdReader;
      int recs = alignFile->scanSDFile(Params["toAlignFile"]);
      //for (int i=0; i<0; i++) {
      for (int i=0; i<recs; i++) {
         if (stop) return true;
         toAlign = new dynacomp::molecule;
         molecule *mol = alignFile->getMolPos(i);
         if (Params["background"] != "1") {
            molChangeEvent *e = new molChangeEvent(
                static_cast<QEvent::Type>(1011)
            );
            e->mol = mol;
            e->molVec.clear();
            e->molVec.push_back(realTemp);
            e->molVec.push_back(mol);
            QApplication::postEvent(&view->jm, e);
         }

         molAdapter::mol2dynacomp(toAlign, mol);
         dcFlexAlign->setMoleculeToAlign(toAlign);
     
         // This is the pose map.  
         // It is the score mapped to the coordinates
         multimap<float, vector<float > > poseMap;

         dcFlexAlign->run(poseMap);
      
         savePoseMap(poseMap, realTemp, mol);
         delete toAlign;
      } 
   }
   time_t t2 = time(NULL);
   return true;
}

bool flexAlignThread::molViewAlign() {
	cout <<"flexAlignThread::molViewAlign: " << view->viewer->renList->size() << endl;
   if (view->viewer->renList->size() < 2) {
      QString error = "You need at least two molecule to run DynaAlign";
	  throw "You need at least two molecule to run DynaAlign";
      //QMessageBox::critical(0, "Error", error);
//      return false;
   }
   list<molecule *>::iterator mi = view->viewer->renList->begin();
   molecule *realTemp = *mi;
   templ  = new dynacomp::molecule;
   molAdapter::mol2dynacomp(templ, realTemp);
   dcFlexAlign->setTemplateMolecule(templ);
   mi++;
   toAlign  = new dynacomp::molecule;
   for (mi; mi!= view->viewer->renList->end(); mi++) {
      if (stop) return true;
      molecule *mol = *mi;
      //toAlign  = new dynacomp::molecule;
      molAdapter::mol2dynacomp(toAlign, mol);
      dcFlexAlign->setMoleculeToAlign(toAlign);

      multimap<float, vector<float> > poseMap;
      dcFlexAlign->run(poseMap);
      savePoseMap(poseMap, realTemp, mol);
   }
   return true;
}


