/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#include "dynascript.h"
#include <qfiledialog.h>
#include <qtextedit.h>
#include <qlineedit.h>
#include <iostream>
#include <fstream>
#include <qstringlist.h>
#include <qptrlist.h>
#include <qseditor.h>
#include <qpixmap.h>
#include "newProjectDialog.h"
#include <qmessagebox.h>
#include <qsinterpreter.h>
#include <iomanip>

/** This include statment is need for interpreter->call() 
*    I really don't have any idea why
*/
#include "scriptmolecule.h"

using namespace std;

dynaScript::dynaScript(QSProject *project, QWidget *parent, const char *name)
 : QSWorkbench(project, parent, name)
{
   widget()->setIcon( QPixmap::fromMimeSource( "qsa.png" ) );
   //this->widget()->setIconText("Who are you?");
   //parent->setIconText("What");
   this->project = project;
   //////////////cout <<"dynaScript was initialized"<<endl;
   connect( this, SIGNAL( newProjectSignal() ), this, SLOT( newProjectSlot() ) );
   connect( this, SIGNAL( openProjectSignal() ), this, SLOT( openProjectSlot() ) );
   connect( this, SIGNAL( saveProjectSignal() ), this, SLOT( saveProjectSlot() ) );
   //////////////cout <<"Leaving dynaScript::dynascript"<<endl; 
}


dynaScript::~dynaScript()
{
}

void dynaScript::newProjectSlot() {
   //////////////cout <<"dynaScript::newProjectSlot() 2"<<endl;
   newProject *dialog = new newProject(this->widget());
    
   if ( dialog->exec() == newProject::Accepted ) {
   	projName = dialog->nameEdit->text();
	Author = dialog->authoredit->text();
	date = dialog->dateEdit->text();
	description = dialog->descEdit->text();	
   }
   
   //This section clears the workbench of any previous scripts
   QStringList names = project->scriptNames();
   for (int i=0; i<names.size(); i++) {
      QSScript *script = project->script(names[i]);
      QSEditor *editor = project->editor( script );
      if ( !editor ) return;
      editor->commit();
      delete editor;
      if (script) delete script;
   }

   QSScript *script = project->createScript( "Main.qs" );
   script->setCode("//You should always include a main function\nfunction main() {\n\n}");
   showScript(script);
  
  
}

void dynaScript::clearProject() {
   QStringList names = project->scriptNames();
   for (int i=0; i<names.size(); i++) {
      QSScript *script = project->script(names[i]);
      QSEditor *editor = project->editor( script );
      if ( !editor ) return;
      editor->commit();
      delete editor;
      if (script) delete script;
   }
}

void dynaScript::openProjectSlot() {
   //////////////cout <<"dynaScript::openProjectSlot()"<<endl;
   /*
   QStringList names = project->scriptNames();
   for (int i=0; i<names.size(); i++) {
      QSScript *script = project->script(names[i]);
      QSEditor *editor = project->editor( script );
      if ( !editor ) return;
      editor->commit();
      delete editor;
      if (script) delete script;
   }
   */
   clearProject();
   //LINUX 2
   QString DYNAMOL = getenv("DYNAMOL");
   QString PATH = DYNAMOL + "/Scripts/";

   //WINDOWS 1
   //QString PATH = "Scripts";
   
   //////////cout <<"Path is: " << PATH << endl;
    QString fileName = QFileDialog::getOpenFileName(
                    PATH,
                    tr("Scripts (*.prj)"),
                    0,
                    "Open Script Dialog",
                    tr("Choose a Script") );

   //QStringList fileNames = QFileDialog::getOpenFileNames(0,PATH,this->widget());
   
   if (fileName.length() == 0) return;
  // QString name = fileNames[0];
   //////////////cout <<"Opening fileName "<< name << endl;
//   openProject(name);
   openProject(fileName);
   /*
   ifstream inFile(name.latin1(), ios::in);
   if (!inFile) {
      //////////////cout <<"file not opened: " << name << endl;
      return;
   }
   
   string tmp;
   while ( !inFile.eof() ) {
      getline(inFile, tmp);
      if (tmp == "<Project Name>") {getline(inFile, tmp); projName = tmp;}
      if (tmp == "<Author>") {getline(inFile, tmp); Author = tmp;}
      if (tmp == "<Description>") {
         //Add code to read in description section
      }
      
      if (tmp == "<Script Name>") {
         readScript(inFile);
      }
   }
   */
   
   //////////////cout <<"ProjName; " << projName << endl;
   //////////////cout <<"Author: " << Author << endl;
   
}

void dynaScript::openProject(const QString &fileName) {
   //////////cout <<"openProject"<<endl;
   ifstream inFile(fileName.latin1(), ios::in);
   if (!inFile) {
      //////////////cout <<"file not opened: " << name << endl;
      return;
   }
   
   string tmp;
   while ( !inFile.eof() ) {
      getline(inFile, tmp);
      if (tmp == "<Project Name>") {getline(inFile, tmp); projName = tmp;}
      if (tmp == "<Author>") {getline(inFile, tmp); Author = tmp;}
      if (tmp == "<Description>") {
         //Add code to read in description section
      }
      
      if (tmp == "<Script Name>") {
         readScript(inFile);
      }
   }
}

void dynaScript::readScript(ifstream &inFile) {
   if ( inFile.eof() ) return;
   string scriptName, tmp;
   getline(inFile, scriptName);
   //////////////cout <<"Script Name: " << scriptName << endl;
   getline(inFile, tmp);
   if (tmp != "<Script Code>") {
      ////////////cout <<"Problems: in dynaScript::readScript " << tmp << endl;
      return;
   }
   
   QString scriptCode;
   int count = 0;
   while (!inFile.eof() ) {
      getline(inFile, tmp);
      if (tmp == "<Script Name>" || inFile.eof()) {
         //////////////cout <<"Creating script "<< scriptName << endl;
         //////////////cout << scriptCode << endl;
         QSScript *script = project->createScript( scriptName );
         
         script->setCode(scriptCode);
         currProj.push_back(scriptCode);
         scriptNames.push_back(scriptName);
         showScript(script);  
            
         count = 0;   
         readScript(inFile);
      } else {
         if (count != 0) {
            scriptCode += "\n";
         }
         count++;
         scriptCode += tmp;
      }
   }
   
   //////////////cout <<"adding problem script: " << scriptName << endl;
   //QSScript *script = project->createScript( scriptName );
   //script->setCode(scriptCode);
   //showScript(script);  
               
   
}

void dynaScript::reLoadCurrProj() {

  clearProject();
  for (int i=0; i<currProj.size(); i++) {
      QSScript *script = project->createScript( scriptNames[i] );  
      script->setCode(currProj[i]);
      showScript(script);  
  }       
}

void dynaScript::saveProjectSlot() {
   project->commitEditorContents();
   //////////////cout <<"dynaScript::saveProjectSlot()"<<endl;

  QString name;  
  bool cont = true;
  
  while (cont) {
  name = QFileDialog::getSaveFileName(
                    tr("./"),
                    tr("molTypes (*.prj)"),
                    0,
                    tr("save file dialog"),
                    tr("Choose a filename to save under") );
    if (name == "")  
       return;
    
       
    cont = QFile::exists( name ) &&
       QMessageBox::question(0, tr("Overwrite File? -- Application Name"),
       tr("A file called %1 already exists." "Do you want to overwrite it?").arg( name ),
       tr("&Yes"), tr("&No"), QString::null, 0, 1 ); 
  }
  
   if ( !name.contains(".prj") )
      name += ".prj";
   //////////////cout <<"Saving as: " << name << endl;
   ofstream outFile(name.latin1(), ios::out);
   if (!outFile) {
      ////////////cout <<"Problem openeing the file fpor writing"<<endl;
      return;
   }
   outFile <<"<Project Name>\n" << projName << endl;
   outFile <<"<Author>\n" << Author << endl;
   outFile <<"<Description>"<<endl;
   outFile <<"No Description"<<endl;
      
   QStringList names = project->scriptNames();
   //////////////cout <<"Total Scripts to save is: " << names.size() << endl;
   for (int i=0; i<names.size(); i++) {
      outFile <<"<Script Name>\n" << names[i] << endl;
      outFile <<"<Script Code>"<<endl;
      QSScript *script = project->script(names[i]);
      QString code = script->code();
      if (code.length() != 0) {
         //////////////cout << code << endl;
         outFile << code << endl;
      }
   }
   
}

bool dynaScript::callFunction(const QString &funcName, const QValueList<QVariant> &args, scriptmolecule *sMol) {
   //////////cout <<"dynaScript::callFunction(const QString &funcName, const QValueList<QVariant> &args, scriptmolecule *sMol)"<<endl;
   QSInterpreter *inter = project->interpreter();
   
   QValueList<QVariant> list;
   QSArgumentList ARGS;
   
   ARGS.push_back(sMol);
   for (int i=0; i<args.size(); i++) {
      QVariant a(args[i]);
      ARGS.push_back(a);
   }
   
   for (int i=0; i<list.size(); i++) {
   	ARGS.push_back(list[i]);
   }
   
   //It is really slow if you don't clear the interpreter
   inter->clear();
   inter->call(funcName, ARGS);
   return true;
}

bool dynaScript::callFunction(const QString &funcName,  const QSArgumentList &ARGS) {
   //////////cout <<"dynaScript::callFunction(const QString &funcName,  const QSArgumentList &ARGS)"<<endl;
   QSInterpreter *inter = project->interpreter();
   inter->call(funcName, ARGS); 
   return true;
}










 
























