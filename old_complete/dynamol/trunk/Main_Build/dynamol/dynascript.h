/***************************************************************************
 *   Copyright (C) 2004 by Dynamol Inc.
 *   john.furr@dynamol.com
 ***************************************************************************/
#ifndef DYNASCRIPT_H
#define DYNASCRIPT_H

#include <qsworkbench.h>
#include <qstring.h>
#include <fstream>
#include <vector>
#include <qvaluelist.h>
#include <qsargument.h>

using namespace std;
/**
@author jfurr
*/

class scriptmolecule;

class dynaScript : public QSWorkbench
{
Q_OBJECT
public:
    dynaScript(QSProject *project, QWidget *parent = 0, const char *name = 0);

    ~dynaScript();
    
    /** This function will open a new project */
    void openProject(const QString &fileName); 
    
    /** This function will clear the current project space */
    void clearProject();
    
    /** This tells the interpreter to run the specified function
    *   If the function is not found or the operation fails it 
    *   return false
    */
    bool callFunction(const QString &funcName,  const QValueList<QVariant> &args, scriptmolecule *mol = 0);
    
    /** You wrote this function because of IO issues with re-reading the
    *   project for the OpenDecriptor project each and every time
    */
    void reLoadCurrProj();
    
    /** This is a better function for calling the interpreter.  */
    bool callFunction(const QString &funcName,  const QSArgumentList &args);
public slots:
   void newProjectSlot();
   void openProjectSlot();
   void saveProjectSlot();
      
   
   
   QSProject *project;
   
   QString projName, Author, date, description;
   
private:
   /** This function simply reads the script from the project file */
   void readScript(ifstream &inFile);
   vector<QString> currProj;
   vector<QString> scriptNames;
};

#endif





































