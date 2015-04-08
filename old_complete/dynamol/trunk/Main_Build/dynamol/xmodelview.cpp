/***************************************************************************
                          xmodelview.cpp  -  description
                             -------------------
    begin                : Sat Feb 21 06:29:20 EST 2004
    copyright            : (C) 2004 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include "xmodelview.h"
#include "xmodel.h"

#include "xmodelview.h"
#include "addh.h"
#include "table.h"

//This are the script class includes
#include "scriptobject.h"
#include "scriptatomtyper.h"
#include "scriptselect.h"
#include "scripthide.h"
#include "scriptshow.h"
#include "scriptmolecule.h"
#include "scriptmollist.h"
#include "scriptatom.h"
#include "scriptbond.h"
#include "scriptbondlist.h"
#include "scriptfile.h"
#include "objectfactory.h"
#include "scriptlistview.h"
#include "scriptmolview.h"
#include "scriptconformation.h"
#include "scriptenergy.h"
#include "scriptmollist.h"
#include "scripttrash.h"
#include "qmessagebox.h"
#include "molchangeevent.h"
#include "conformation.h"
#include "molview.h"
#include "mollistview.h"
#include "xmodeldoc.h"
#include "charge.h"
#include "energy.h"
#include "sdreader.h"
#include "molcheck.h"

#include "qapplication.h"
#include <qseditor.h>
#include <qtabwidget.h>
#include <qsproject.h>
#include <qsinputdialogfactory.h>
#include <qsutilfactory.h>
#include <qsinterpreter.h>
#include <qtextbrowser.h>
#include <qwaitcondition.h>
#include "qsworkbench.h"

#include <qpixmap.h>
#include "dynamol.xpm"

#include <qvaluelist.h>
#include <qstylesheet.h>
#include <qlabel.h>
#include <qhgroupbox.h>
#include <qvaluelist.h>

#include "molecule.h"
#include "atom.h"
#include "dynascript.h"
#include "enumTypes.h"

//FOR FINGERPRINTS ONLY DELETE WHEN DONE 
#include <map>
#include <set>
#include "moladapter.h"
#include "../dynatype/dtype.h"
#include "../dynatype/molecule.h"
#include "trashcan.h"

#include "../dynaprint/gaffsig.h"

//Dynamol Base Library Includes
#include "../dynabase/utility.h"

//Dynamol Computational Includes
#include "../dynacomp/compute.h"
#include "../dynacomp/molecule.h"
#include "../dynacomp/atom.h"

//END FINGER PRINT SECTION

using namespace std;
static QTextEdit *debugoutput = 0;

XmodelView::XmodelView(QWidget *parent, XmodelDoc *doc) 
: QSplitter(parent)
{

   
  //QMessageBox::critical(0, "Dynamol", "XmodelView");

  this->parent = dynamic_cast<XmodelApp *>(parent);
  this->doc = doc;
  renList = new list<molecule *>;

  setOrientation(Horizontal);
  listView = new molListView(this, "molListView", doc);
  //listView->setMaximumWidth(1500);
 
  connect(&doc->db, SIGNAL(newProtein(protein *)), listView, SLOT(addProtein(protein *)));
  connect(&doc->db, SIGNAL(newMolecule(molecule *)), listView, SLOT(addMolecule(molecule *)));
  
  connect(&jm, SIGNAL(jobDone(QString)), parent, SLOT(slotKillJob(QString)));

  horz = new QSplitter(this);
  horz->setOrientation(Vertical);
  
  tabs = new QTabWidget(horz, "tabWidget");
  viewer = new molView(tabs, "molView", doc->db.getRenderList());
  viewer->setModelView(this);
  
  //Set the static viewer variable for the dynothread 
  dynoThread::setMolView(viewer);

  tabs->addTab(viewer, "Mol View");
 
  listView->setMolView(viewer);
  viewer->setListView(listView);

  connect(listView, SIGNAL(renderMol(std::list<molecule *> *)), viewer, SLOT(setMolList(std::list<molecule *> *)));
  connect(viewer, SIGNAL(selectionChanged()), listView, SLOT(selectionChangedSlot()));
  
  // This conenction handles the molView seleced delete process 
  connect(viewer, SIGNAL(deleteAtoms(vector<atom *> &)), listView,  SLOT(deleteAtomsSlot(vector<atom *> &)));

  //You will need to chage this to a qtextedit in QT versio 4
  helpTab = new QTextBrowser(tabs, "Manual");
  helpTab->hide(); 
  helpTab->mimeSourceFactory()->setExtensionType("html", "text/html;charset=iso8859-1");
  QStringList currPaths = helpTab->mimeSourceFactory()->filePath();
  for (int i=0; i<currPaths.size(); i++) {
   QMessageBox::critical(this, "Path", currPaths[i]);  
  }
  
  QValueList<int> splitWidth;
  splitWidth.push_back(150);
  splitWidth.push_back(500);
  setSizes(splitWidth);
  
  scriptObject::setParents(this); 
  
  scriptselect *selectClass = new scriptselect(this, "select");  
  scripthide *hideClass = new scripthide(this, "hide");  
  scriptshow *showClass = new scriptshow(this, "show");
  scriptfile *fileClass = new scriptfile(this, "file");  
  scriptlistview *listViewClass = new scriptlistview(this, "listView");  
  scriptmolview *molViewClass = new scriptmolview(this, "molView");
  scriptconformation *confClass = new scriptconformation(this, "Conf");
  scriptenergy *energyClass = new scriptenergy(this, "Energy");
  scripttrash  *trashClass = new scripttrash(this, "Trash");
  //scriptmolecule *molClass = new scriptmolecule(this, "Molecule");
  //scriptmollist *molList = new scriptmollist(this, "MolList");
  //scriptbondlist *bondList = new scriptbondlist(this, "BondList");
  scriptatomtyper *atomTyper = new scriptatomtyper(this, "AtomTyper");
  
  objectFactory *objFac = new objectFactory(this);
  //objFac->registerClass("mol", "scriptmolecule");
  objFac->registerClass("atom", "scriptatom");
  objFac->registerClass("charge", "scriptcharge");
  objFac->registerClass("molList", "scriptmollist");
  objFac->registerClass("conf", "scriptconformation");
  objFac->registerClass("Energy","scriptenergy");
  objFac->registerClass("Molecule","scriptmolecule");
  objFac->registerClass("MolList", "scriptmollist");
  objFac->registerClass("BondList", "scriptbondlist");
  objFac->registerClass("AtomTyper", "scriptatomtyper");
  objFac->registerClass("Trash", "scripttrash");

  
  project = new QSProject( this, "test" );
  interpreter = project->interpreter();
  interpreter->setErrorMode(QSInterpreter::Notify);
  QSInputDialogFactory *fac = new QSInputDialogFactory;
  interpreter->addObjectFactory( fac );
  interpreter->addObjectFactory( objFac );
  interpreter->addObjectFactory(new QSUtilFactory);

  project->addObject( selectClass );
  project->addObject( hideClass );
  project->addObject( showClass );
  project->addObject( fileClass );
  project->addObject( listViewClass );
  project->addObject( molViewClass );
  project->addObject( confClass );
  project->addObject( energyClass );
  project->addObject( atomTyper );
  project->addObject( trashClass );
  
  //QSplitter *vert2 = new QSplitter(horz);
  //vert2->setOrientation(Horizontal);
  QHGroupBox *hBox = new QHGroupBox ( horz, "hBox" );
  hBox->setMaximumHeight(60);
  QLabel *qsi = new QLabel( "QSI", hBox);
  editor = new QSEditor(hBox, "editor");
  
  project->addObject( editor );
  editor->setMaximumHeight(30);
  editor->setInterpreter(interpreter, interpreter);
  edit = editor->textEdit();
  QFont serif("Serif");  
  edit->setFont(serif);
  edit->setVScrollBarMode(QScrollView::AlwaysOff);
  edit->setBold(true);
  edit->installEventFilter( this );

 
  ide = new dynaScript(project, this, "Intergrated development environment");
  ide->widget()->setCaption("Dynamol Script Editor");
 
  histIndex = 0;
  QWaitCondition *update = new QWaitCondition;

  jm.setXmodelView(this);
  jm.installEventFilter(&jm);
   
  molChangeEvent::setJobManager(&jm);

  //nameMols("code");
  //buildFingerPrints();
  //addHTest();
  //exit(0);
}

void XmodelView::setMainApp(QApplication *app) {this->mainApp = app;}



bool XmodelView::eventFilter( QObject *o, QEvent *e ) {

    if (o == this && e->type() == QEvent::WindowStateChange) {
    }
    if ( o != edit && o != edit->viewport() )
	return FALSE;
    if ( e->type() == QEvent::KeyPress ) {
	QKeyEvent *ke = (QKeyEvent*)e;
	if (ke->key() == Key_Return || ke->key() == Key_Enter) {
	   
	   QString code = edit->text(); //grab the text from the editor
	   history.push_back(code);
	   //if ( code[ 0 ] == '?' )
	     //code = "debug(" + code.mid( 1 ) + ");";
	     if ( !interpreter->checkSyntax( code ) ) {
	       edit->doKeyboardAction( QTextEdit::ActionReturn );
	       //edit->clear();
	       return TRUE;
	     }
	     
	     QSArgument value = interpreter->evaluate( code );
	     edit->clear();
	     
	     //edit->setCursorPosition(0, 0);
	     //editor->gotoLine(0);
	     histIndex = history.size();
	     return TRUE;
	}
	if (ke->key() == 4115) { //The up arrow was pushed...now lets scroll through the history
	   if (histIndex >= 1 ) histIndex--;
	   
	   if (history.size() != 0) {
	      edit->setText(history[histIndex]);
	   }
	   
	   
	}
	
	if (ke->key() == 4117) { //The up arrow was pushed...now lets scroll through the history
	   if (histIndex < history.size()-1 ) histIndex++;
	   if (history.size() != 0) {
	      edit->setText(history[histIndex]);
	   }
	   
	   
	}
    }
    //int test = 0;
    //cin >> test;
    return FALSE;
    
}


XmodelView::~XmodelView()
{
}

void XmodelView::slotDocumentChanged()
{

}

void XmodelView::setRenderType(BONDRENDER bondType, ATOMRENDER atomType) {
    viewer->setRenderType(bondType, atomType);
}

void XmodelView::setDisplay(DISPLAY_TYPE dispType) {
  viewer->setDisplay(dispType);
}

void  XmodelView::defineRibbon(RIBBON_TYPE type) {
  viewer->defineRibbon(type);
}

void XmodelView::potEnergy() {
   string type;
   string chrg;
   list<molecule *> molList = *viewer->getRenList();
   if (molList.size() == 0) 
      return;

   molecule *mol = *molList.begin();
     
   dynacomp::molecule *dcMol = new dynacomp::molecule;
   molAdapter::mol2dynacomp(dcMol, mol);
   dynacomp::Compute::potEnergy(dcMol);
   /*
   for (int i=0; i<dcMol->potEnergy.size(); i++) {
      cout <<i <<"\t" << dcMol->potEnergy[i] << endl;
   }
   */
   viewer->infoText.clear();
   viewer->infoText.push_back("Potential Energy (Dielectric=1)");
   QString TE; TE.setNum(dcMol->potEnergy[0]);
   viewer->infoText.push_back("Total Energy:   " + TE);
   QString BS; BS.setNum(dcMol->potEnergy[1]);
   viewer->infoText.push_back("Bond-Stretch:   " + BS);
   QString AB; AB.setNum(dcMol->potEnergy[2]);
   viewer->infoText.push_back("Angle-Bend:     " + AB);
   QString TR; TR.setNum(dcMol->potEnergy[3]);
   viewer->infoText.push_back("Torsion:            " + TR);
   QString EL; EL.setNum(dcMol->potEnergy[4]);
   viewer->infoText.push_back("Electrostatic:    " + EL);
   QString VW; VW.setNum(dcMol->potEnergy[5]);
   viewer->infoText.push_back("van der Waals:  " + VW);
   molAdapter::dynacomp2mol(mol, dcMol);
   delete dcMol;
}

dynoThread *XmodelView::MMmin(QString jobName, QString minMethod, QString ffType, QString chargeType, QString dielectric, float dieValue,  int maxIter, float rmsef, float maxForce, float minEDiff) {
  static int a = 0;
  if (viewer->getRenList()->size() == 0 ) {
    return NULL;
  }
  a++;
  static energyThread *et;
  et = new energyThread(this, jobName); 
  jm.registerJob(et);
  
  if (ffType == "ff2003") ffType = "AMBER_03";
  if (chargeType=="Force Field" && ffType == "GAFF") chargeType = "AM1-BCC";
  if (chargeType=="Force Field" && ffType == "AMBER_03") chargeType = "AMBER";
  
  bool sizeToBig = false;
  list<molecule *> molList = *viewer->getRenList();
  list<molecule *>::iterator itr = molList.begin();
  for (itr; itr != molList.end(); itr++) {
     molecule *mol = *itr;
     if (mol->atoms.size() <= 198 && ffType == "Default") {
        ffType = "GAFF";
        if (chargeType=="Force Field") chargeType = "AM1-BCC-fast";
     } else if (mol->atoms.size() > 198 && ffType == "Default") {
        ffType = "AMBER_03";
        if (chargeType=="Force Field") chargeType = "AMBER";
     }
     
     if (mol->atoms.size() >= 199 && chargeType == "AM1-BCC") {
        QMessageBox::critical( 0, "Dynamol",
    	"This molecule has to many atoms for the AM1-BCC charges.\nAM1-BCC is the default charge type when using the GAFF forcefield.\n You will need to either change the force field type or the set the charges to current");
        //sizeToBig = true;
        return false;
        ffType = "AMBER_03";
     } 
     if (chargeType == "Current") chargeType = mol->chargeType;
  }
  
  et->setUp(viewer->getRenList(), minMethod, ffType, chargeType, maxIter, 
	    rmsef, maxForce, minEDiff, dielectric, dieValue);
  
  viewer->startAutoUpdate(-1);
   
  QSemaphore *wait_sem = new QSemaphore(1);
  (*wait_sem)++;
  et->setSemaphore(wait_sem);
  
  parent->slotNewJob(et);
  et->start();
  //return true;
  return et;
}

bool  XmodelView::MD(QString jobName, QString method, QString outFile, int iterations, float timeStep, QString ffType, QString chargeType, int outIter) {
  bool sizeToBig = false;
  list<molecule *> molList = *viewer->getRenList();
  if (molList.size() == 0) 
  	return false;
  list<molecule *>::iterator itr = molList.begin();
  molecule *tmpMol;
  for (itr; itr != molList.end(); itr++) {
     molecule *mol = *itr;
     tmpMol = mol;
     if (mol->atoms.size() > 200) {
        sizeToBig = true;
        ffType = "AMBER_03";
        chargeType = "AMBER";
     } else {
        ffType = "GAFF";
     }
  }

  if (!sizeToBig) chargeType = "AM1-BCC-fast";
  if (sizeToBig) chargeType = "AMBER";
  if (viewer->getRenList()->size() == 0 ) {
    return false;
  }
  
  energyThread *et;
  et = new energyThread(this, jobName);  
  et->mdSetup(viewer->getRenList(), method, iterations, timeStep, ffType, chargeType, outFile, outIter);
  jm.registerJob(et);
  viewer->startAutoUpdate(-1);
  
  QSemaphore *wait_sem = new QSemaphore(1);
  (*wait_sem)++;
  et->setSemaphore(wait_sem);
  
 
  parent->slotNewJob(et);
  et->start();    
  return true;
}


void  XmodelView::MopacMin(QString jobName, QString method) {
   list<molecule *> molList = *viewer->getRenList();
   
   if (molList.size() == 0) 
   	return;
   
   list<molecule *>::iterator itr = molList.begin();
   for (itr; itr != molList.end(); itr++) {
     molecule *mol = *itr;
     chargeThread *ct = new chargeThread(this, "Charges");
     QSemaphore *wait_sem = new QSemaphore(1);
     (*wait_sem)++;
     if ((method == "AM1" || method == "PM3" || method == "MNDO") && mol->atoms.size() > 200) {
        QMessageBox::critical( 0, "Dynamol",
    	"This molecule has to many atoms for MOPAC's semi-empirical routines.\nCurrent limit is 200 heavy atoms");
        return;
     }
     charge chrg;
     chrg.setUp(mol, method);
     viewer->clearInfoText();
        vector<QString> text;
        text.push_back("Minimizing with MOPAC");
     viewer->setInfoText(text);
     viewer->updateInfoText();
     chrg.mopacMin(method);
     viewer->clearInfoText();
     viewer->updateInfoText();
   } 
}

bool  XmodelView::MC(QString jobName, QString method, QString outFile, int iterations, float Temp, QString ffType, QString chargeType, int outIter) {
  
  static energyThread *et;
  et = new energyThread(this, jobName); 
  jm.registerJob(et);
  
  if (viewer->renList->size() == 0) {
  	return false;
  }
  
  et->mcSetup(viewer->getRenList(), method, iterations, Temp, ffType, chargeType, outFile, outIter);
  viewer->startAutoUpdate(-1);
  
  QSemaphore *wait_sem = new QSemaphore(1);
  (*wait_sem)++;
  et->setSemaphore(wait_sem);
  
  parent->slotNewJob(et);
  et->start();    
  return true;
}


//########## AM1_BCC Charges are still done the old way see xmodelapp
void  XmodelView::charges(string method) {
   list<molecule *> molList = *viewer->getRenList();
   list<molecule *>::iterator itr = molList.begin();
   for (itr; itr != molList.end(); itr++) {
     molecule *mol = *itr;
     chargeThread *ct = new chargeThread(this, "Charges");
     jm.registerJob(ct);
     QSemaphore *wait_sem = new QSemaphore(1);
     (*wait_sem)++;
     if ((method == "AM1" || method == "AM1-BCC" || method == "AM1-BCC-fast" 
     ||method == "MNDO" || method == "PM3") && mol->atoms.size() >200) {
        QMessageBox::critical( 0, "Dynamol",
    	"This molecule has to many atoms for this charge type.\nCurrent limit is 200 heavy atoms");
        return;  
     }
     if (method=="FF" && mol->atoms.size() < 200) 
         method = "AM1-BCC-fast";
     if (method=="FF" && mol->atoms.size() > 200) 
         method = "AMBER";
     ct->setUp(mol, method);
     parent->slotNewJob(ct);
     ct->setSemaphore(wait_sem);
     ct->start();
   }
   viewer->startAutoUpdate(-1);
}

void XmodelView::addHydrogens(molecule *mol, QString optimzation) {
  list<molecule *> molList;
  molList.push_back(mol);
  addH *h = new addH; 
  
  update = new QWaitCondition; //update->wakeAll() called in jobManager
  
  //h->setUp(listView, optimzation, molList);
  
  QSemaphore *wait_sem = new QSemaphore(1);
  (*wait_sem)++;
  h->setUp(wait_sem, this, optimzation, molList);
  
  //viewer->startAutoUpdate(-1);
  parent->slotNewJob(h);
  stopAllGUI();
  h->start();
}
dynoThread *XmodelView::addHydrogens(QString optimzation) {
  list<molecule *> molList = *viewer->getRenList();
  addH *h = new addH; 
  
  update = new QWaitCondition; //update->wakeALL() called in jobManager
  jm.installEventFilter(&jm);
  
  QSemaphore *wait_sem = new QSemaphore(1);
  (*wait_sem)++;
  h->setUp(wait_sem, this, optimzation, molList);
  viewer->startAutoUpdate(-1);
  parent->slotNewJob(h);
  stopAllGUI();
  h->start();  
  return h;
}

void XmodelView::stopAllGUI() {
   this->listView->installEventFilter(&NOEVENT);
   this->viewer->installEventFilter(&NOEVENT);
   this->installEventFilter(&NOEVENT);
   
}
void XmodelView::startAllGUI() {
this->viewer->removeEventFilter(&NOEVENT);
   this->listView->removeEventFilter(&NOEVENT);
   this->removeEventFilter(&NOEVENT);
}

bool XmodelView::sysSearch(QString jobName, QString outFile, float cutoff, bool Min) {
   confThread *ct = new confThread(this, jobName);
   jm.registerJob(ct);
   return true;
}

void XmodelView::initTable(QString &sdfName) {
   Table *t = new Table(ide);
   connect(t, SIGNAL(viewMol(QString, int)), &doc->db, SLOT(readSD(QString, int)));
   connect(t, SIGNAL(deleteListView()), listView, SLOT(deleteAll()));
   t->importSDF(sdfName);
}

void XmodelView::initTable() {
   Table *t = new Table(ide);
   connect(t, SIGNAL(viewMol(QString, int)), &doc->db, SLOT(readSD(QString, int)));
   connect(t, SIGNAL(deleteListView()), listView, SLOT(deleteAll()));   
}

void XmodelView::addHTest() {
    addH *h = new addH; 

    sdReader reader;
    int numRecs = reader.scanSDFile("renamed.sdf");
    vector<atom *> newAtoms;
    molCheck checkMol;
    for (int i=0; i < numRecs; i++) {
       molecule *mol = reader.getMolPos(i);
       checkMol.singleAtomCheck(mol);
       newAtoms.clear();
       h->addHydrogens(mol, newAtoms);
    }
}

void XmodelView::nameMols(string field) {
  sdReader r;
  string fileName = "Screening_Collection_3D.sdf";
  int numMols = r.scanSDFile(fileName);
 
   for (int i=0; i<numMols; i++) {
      molecule *mol = r.getMolPos(i);
      string name = mol->getPropValue(field).latin1();
      string tmpName = "";
      for (int i=0; i<name.size(); i++) {
         if (name[i] != ' ') {
             tmpName += name[i];
         } else {
             tmpName += "_";
         }
      }
      mol->setName(tmpName);
      mol->clearPropMap();
      mol->addPropValuePair("Fax", "+44 1840 770111");
      mol->addPropValuePair("phone", "+44 1840 770467");
      mol->addPropValuePair("email", "orders@maybridge.com");
      mol->addPropValuePair("Website", "www.maybridge.com");
      mol->addPropValuePair("Supplier_Code", mol->getName());
      mol->addPropValuePair("Vender_Name", "Maybridge");

  
      molDB::writeSDF("renamed.sdf",mol, 1);
      vector<Object *> molToDel;
      molToDel.push_back(mol);
      TrashCan t(molToDel);
      t.empty();
   } 

}

void XmodelView::buildFingerPrints() {
   fp::gaffSig gs;
   gs.readSubSets(1000000);
   //FIRST WE NEED TO GET A LISTING OF ALL THE FILES IN THE CURRENT DIRECTORY
   system("ls *.sdf > Files.txt");
   ifstream tmpFile("Files.txt", ios::in);
   string line;
   vector<string> Files;
   while (tmpFile >> line) {
      Files.push_back(line);
   }

   
   molDB db;
   for (int i=0; i<Files.size(); i++) {
      string name = Files[i];
      string fileName = Files[i];
      //RECOMPRESS FILE
      string fpName = fileName.substr(0, fileName.size()-4);
      fpName +=".fp";
      
      ifstream inFile(name.c_str(), ios::in | ios::binary);
      if (!inFile) {
	 exit(0);
      } 
      
      int c = 1;
      int offSet = inFile.tellg();
      map<string, int> offSetMap;
      while (inFile >> name) {
      if (c == 1 || (name == "$$$$" && !inFile.eof())) {
         QString qName;
         if (c != 1) {
            offSet = inFile.tellg();
            inFile >> name;
            if (inFile.eof()) 
            break;
            qName = name;
           
            offSetMap[qName] = offSet;
        
            // Display the name of the compound that is being exported  
	 
	    //move down to atm and bond nums
	    getline(inFile, name);
	    getline(inFile, name);
	    getline(inFile, name);
	    getline(inFile, name);
	 
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
            if (name.substr(0,4) == "$$$$") {
	    	inFile.seekg(-25, ios::cur);
		break;
	    }
	    
	   
	    if (inFile.eof()) {
	       return;
	    }
	 } 
     
	 c++;
      }
      
      
   }
      ofstream outFile(fpName.c_str(), ios::out);
      ofstream out2("fp-charge.txt", ios::out);
      map<string, int>::iterator mi = offSetMap.begin();
      int count = 0;

      for (mi; mi!= offSetMap.end(); mi++) {
	 count++;
	 
         molecule *mol = db.readSD(fileName, mi->second, false);
	 if (mol != NULL) { 
	    //scriptmolecule *sMol = new scriptmolecule(mol);

	 
   	    //dt::molecule *currDT =  new dt::molecule;
          dt::molPtr currDT( new dt::molecule );
   	    molAdapter::mol2molecule(currDT, mol);
   	    dt::dType dt;
   	    dt.setPathLength(10);
   	    dt.setGaffTypes(currDT);
   	 
            
          currDT->propMap["ae3"] = gs.runMol(currDT, 3, false);
          currDT->propMap["ae2"] = gs.runMol(currDT, 2, false);
	    
   	    molAdapter::update(mol, currDT);
	       //delete currDT;
	
            dynacomp::molecule *dcMol = new dynacomp::molecule;
            molAdapter::mol2dynacomp(dcMol, mol);
            dynacomp::Compute::charges(dcMol, "AM1-BCC-fast");
            molAdapter::dynacomp2mol(mol, dcMol);
            string CHRG = "";
            for (int i=0; i<mol->atoms.size(); i++) {
               atom *atm = mol->atoms[i];
               string chgS = dynabase::setNum( atm->getCharge() );
               if (i == mol->atoms.size()-1) 
                  CHRG += chgS;
               else
                  CHRG += chgS + " ";
            }
            mol->propMap["AM1-BCC"] = CHRG;
             
	    string fp3 = mol->getPropValue("ae3");
            string fp2 = mol->getPropValue("ae2");
           

            out2 << mol->getName() << endl; 
            out2 << fp2 << endl;
            out2 << fp3 << endl;
            out2 << CHRG <<"\n"<< endl;

            molDB::writeSDF("GoodFile.sdf", mol, 1);
	    outFile <<mol->getName()<<"\t" << fp3 << endl;
   	 
	    //delete mol;
	 
	    vector<Object *> molToDel;
	    molToDel.push_back(mol);
	    TrashCan t(molToDel);
	    t.empty();
         }
	 //delete mol;
      }
      outFile.close();
      outFile.clear();
      //RECOMPRESS FILE
    
      inFile.close();
      inFile.clear();
   }
}































