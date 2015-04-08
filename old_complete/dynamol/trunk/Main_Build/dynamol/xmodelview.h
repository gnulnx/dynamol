/***************************************************************************
                          XmodelView.h  -  description
                             -------------------
    begin                : Tue Dec 30 21:35:06 EST 2004
    copyright            : (C) 2004 by John Furr
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef XmodelView_H
#define XmodelView_H

// include files for QT
#include <qsplitter.h>

// application specific includes
#include "jobmanager.h"
#include "noevent.h"

#include "enumTypes.h"

//#include <switchboard.h>

/**
 * This class provides an incomplete base for your application view.
 */
 
class dynoThread;
class molecule;
class atom;
class molView;
class molListView;
class QSEditor;
class QTabWidget;
class QSProject;
class QTextBrowser;
class QSWorkBench;
class dynaScript;
class QApplication;
class XmodelDoc;
class QSInterpreter;
class QSWorkbench;
class QTextEdit;
class QWaitCondition;
class XmodelApp;

class XmodelView : public QSplitter
{
  friend class XmodelApp;
  friend class jobManager;
  Q_OBJECT
  public:
    XmodelView(QWidget *parent=0, XmodelDoc* doc=0);
    ~XmodelView();
    void setRenderType(BONDRENDER bondType, ATOMRENDER atomType);
    void setDisplay(DISPLAY_TYPE dispType);
    void defineRibbon(RIBBON_TYPE type);

    jobManager jm;
    noEvent NOEVENT;
    QApplication *mainApp;
    QWaitCondition *update;
    void setMainApp(QApplication *app);
    void stopAllGUI();
    void startAllGUI();
    
  
  public slots:
    dynoThread *MMmin(QString jobName, QString minMethod, QString ffType, QString chargeType,  QString dielectric,  float dieValue, int maxIter, float rmsef, float maxForce, float minEDiff);
    
    void  MopacMin(QString jobName, QString method);
    
    bool  MC(QString jobName, QString method, QString outFile, int iterations, float Temp, QString fftype, QString chargeType, int outIter);
    bool  MD(QString jobName, QString method, QString outFile, int iterations, float timeStep, QString ffType, QString chargeType, int outIter);
    
    bool sysSearch(QString jobName, QString outFile, float cutoff, bool Min);
    void  charges(string method);
    dynoThread *addHydrogens(QString optimzation);
    void addHydrogens(molecule *mol, QString optimzation);
    
    void potEnergy();
    
    molListView *listView;

    /** Open an blank moltable */    
    void initTable();
    
    /** Open a molTable and read in the SDF file */
    void initTable(QString &sdfName);
    
    //THIS IS FOR FINGERPRINT BUILD ONLY
    void buildFingerPrints();
    /** This is used to convert mol fields to mol name */
    void nameMols(string field);
    void addHTest();
  protected slots:
    void slotDocumentChanged();

 public:
  molView   *viewer;
  XmodelDoc *doc;
  XmodelApp *parent;

  private:
    
    list<atom *> atomIter;
    list<molecule *> molList; //This might get deleted
    list<molecule *> *renList;

    QSplitter *horz;

    QSInterpreter *interpreter;
    QSProject *project;
    QTextEdit *edit;
    QSEditor *editor;
    
    
    QSWorkbench *workBench;
    dynaScript *ide;
    vector<QString> history;
    int histIndex;
    
    int index;
    
    QTabWidget *tabs;
    
    //This will need to be a QText edit in QT 4
    QTextBrowser *helpTab;
    
    bool eventFilter( QObject *o, QEvent *e );
    
    //energy Energy;
    //charge Charge;
};

#endif





































