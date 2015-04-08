/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "opendesc.h"


#include "qvaluelist.h"
#include "qvariant.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include <deque>

#include "molecule.h"
#include "scriptmolecule.h"
#include "dynascript.h"
#include <qmessagebox.h>

//Trying something new
#include "scriptatomtyper.h"
#include "moladapter.h"
#include "../dynatype/dtype.h"
#include "../dynatype/molecule.h"
#include "../dynatype/atom.h"
#include "../dynatype/bond.h"
#include "../dynatype/dtGaff.h"

OpenDesc::OpenDesc(dynaScript *ide, vector<QString> &descVec)
{
   this->ide = ide;
   s.selectDesc(descSet, descVec);
   
   
   
   /*
   //LINUX 2
   QString Path = getenv("DYNAMOL");
   Path += "/OpenDescriptor/open_desc.prj";
   Path += "/OpenDescriptor/sayHi.prj";

   //WINDOWS 1
   //QString Path = "OpenDescriptor\\open_desc.prj";

   ifstream inFile(Path.latin1(), ios::in);
   if (!inFile) {
      //////////cout <<"OpenDescripter.prj not found at: " << Path << endl;
	  QMessageBox::critical( 0, "Dynamol", "Open Desc project file not opened");
   }
   inFile.clear();
   inFile.close();
   
   ide->clearProject();
   ide->openProject(Path);
   */
}


OpenDesc::~OpenDesc()
{
}

void OpenDesc::runMol( molecule *mol ) {
   //////////cout <<"Running : " << mol->getName() << endl;
   //time_t t1 = time(NULL);
   ////////////cout <<"OpenDesc::runMol"<<endl;
   static int count = 0;
   ////////////cout <<"Building sMol  "<< mol->getName() << endl; 
   //scriptmolecule *sMol = new scriptmolecule(mol);

   /*
   dt::dt::molecule *currDT =  new dt::dt::molecule;
   molAdapter::mol2dt::molecule(currDT, mol); 
   dt::dType dt;
   dt.setPathLength(10);
   ////////////cout <<"Before setGaffTypes"<<endl;
   dt.setGaffTypes(currDT);
   dt.gaffFP(currDT, 3);
   molAdapter::update(mol, currDT);
   delete currDT;
   delete sMol;
   return;
   */
   
   //dt::molecule *currDT =  new dt::molecule;
   dt::molPtr currDT( new dt::molecule );
   molAdapter::mol2molecule(currDT, mol);
   //switchBoard s;
   ////////////cout <<"Calling switchBoard.calcDesc"<<endl;
   s.calcDesc(descSet, currDT);
   void calcDesc(set<QString> &desc, dt::molecule *mol);
   ////////////cout <<"Back from calcDesc"<<endl;
   molAdapter::update(mol, currDT);
   ////////////cout <<"Back from  update"<<endl;
   //delete currDT;
   ////////////cout <<"currDT was deleted"<<endl;
   //s.descIn(descSet);
   //exit(0);

/** Don't delete this part yet...this is how you call all the descriptor
*   code from  the scripting langauge
*/
   /*
   QValueList<QVariant> args;
   set<QString>::iterator sIt = descSet.begin();
   for (sIt; sIt != descSet.end(); sIt++) {
      QString s =  *sIt;
      args.push_back(s);
   }

   QString funcName = "main";
   count++;
   ////////////cout <<"Calling ide->callFunction"<<endl;
   ide->callFunction(funcName, args, sMol);
   */
   //time_t t2 = time(NULL);
   
/** This is a bad little IDEA that you had the other day.  Basically you are
*   waiting until 5 script molecules have been created before you do any deletion
*   The reason is because scriptatomtyper has something like
*   
*   if (mol == currMol) return
*  
*   Well occasionally you were getting the exact same address two times in a row!!
*   This was causing the above statment to evaulate true even tho the scriptmolecules
*   actually contained two different molecules
*/
/*
   static deque<scriptmolecule *> trash;
   trash.push_back(sMol);
   if (trash.size() == 5) {
	while (trash.size() > 2) {
	   scriptmolecule *dMol = trash.front();
	   trash.pop_front();
	   delete dMol;
        }
   }
   */
	
   ////////////cout <<"Leaving OpenDesc::runMol"<<endl;
}


/*

void OpenDesc::buildDescList(descSel *&dialog) {
   ////////////cout <<"You are in buildDesList"<<endl;
   //LINUX 2
//   QString Path = getenv("DYNAMOL");
//   Path += "/OpenDescriptor/open_desc.prj";

   //WINDOWS 1
QString Path = "OpenDescriptor\\parm99.dat";
 
   ifstream inFile(Path.latin1(), ios::in);
   if (!inFile) {
      //////////cout <<"OpenDescripter.prj not found at: " << Path << endl;
   }
   
   string line;
   QListViewItem *parent;
   QListViewItem *child;
   
   QString className;
   QString funcName;
   QString author;
   
   QListView *list = dialog->listView;
   list->setSorting(-1);
   bool isPrivate = true;

   
   while (true) {
     getline(inFile, line);
     QString qline = line;
     
     if (qline.contains("class") && qline.contains("extends Desc")) {
        ////////////cout << qline<<endl;
	className = qline.section("{", 0);
	className = className.section(" ", 1, 1);
	isPrivate = false;
	////////////cout <<"className is: " << className << endl;
	parent = new QListViewItem(list, className);	
     } 
     else if (qline.contains("class")) {
	//////////cout <<"Bad class: " << qline << endl;
        className = "";
        isPrivate = false;
     } 
     
     if (qline.contains("private")) {
        isPrivate = true;
     }
     
     if (qline.contains("public")) {
        isPrivate = false;
     }
     
     if (!isPrivate && qline.contains("function") 
         && !qline.contains("static") && className != ""
      ) {
	////////////cout << qline << endl;
	
	bool endName = false;
	bool beginAuthor = false;
	string funcName;
	string author;
	
	QString tmp2 = qline.section("function ", 1);
	string tmp = tmp2.latin1();
	int authorCount = 0;
	for (int i=0; i<tmp.size(); i++) {
	   if (tmp[i] == '(') {
	      endName = true;
	   }
	   if (!endName) {
	      funcName.push_back(tmp[i]);
	   }
	   if (beginAuthor) {
	      author.push_back(tmp[i]);
	   }
	   if (tmp[i] == '/') {
	     authorCount++;
	     if (authorCount == 2) {
	        beginAuthor = true;
             }
	   }
	   
	}

	if (className != funcName) {
	   child = new QListViewItem(parent, funcName, author);
	   //////////cout <<"funcName: " << funcName << endl;
	   ////////////cout <<"author: " << author << endl;
	}
     }
     
     if (inFile.eof()) 
     	break;  
   }
   
   inFile.clear();
   inFile.close();
//   list->setSorting(true); 
}

*/








