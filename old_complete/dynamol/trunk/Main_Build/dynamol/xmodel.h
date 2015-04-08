/***************************************************************************
                          chemtest.h  -  description
                             -------------------
    begin                : Tue Dec 30 21:35:06 EST 2004
    copyright            : (C) 2004 by John Furr
    email                : john.furr@dynamol.com
 ***************************************************************************/


#ifndef CHEMTEST_H
#define CHEMTEST_H

// include files for QT
#include <qapp.h>
#include <qmainwindow.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qstatusbar.h>
#include <qwhatsthis.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qmsgbox.h>
#include <qfiledialog.h>
#include <qprinter.h>
#include <qpainter.h>
#include "dynothread.h"
#include <vector>

#include "surfdialog2.h"

using namespace std;

// application specific includes

/**
  * This Class is the base class for your application. It sets up the main
  * window && providing a menubar, toolbar
  * && statusbar. For the main view, an instance of class ChemTestView is
  * created which creates your view.
  */
class XmodelView;
class XmodelDoc;
class confDialog;
class Lighting;

class XmodelApp : public QMainWindow
{
  Q_OBJECT

  public:
    /** construtor */
    XmodelApp();
    /** destructor */
    ~XmodelApp();
    /** initializes all QActions of the application */
    void initActions();
    /** initMenuBar creates the menu_bar && inserts the menuitems */
    void initMenuBar();
    /** this creates the toolbars. Change the toobar look && add new toolbars in this
     * function */
    void initToolBar();
    /** setup the statusbar */
    void initStatusBar();
    /** setup the document*/
    void initDoc();
    /** setup the mainview*/
    void initView();

    /** overloaded for Message box on last window exit */
    bool queryExit();
    
    void runScript(QString fileName);

	/** This function sets the main QApplication */
	void setMainApp(QApplication *app);
    
    /** view is the main widget which represents your working area. The View
     * class should handle all events of the view widget.  It is kept empty so
     * you can create your view according to your application's needs by
     * changing the view class.
     */
    XmodelView *view;
    
    Lighting *dialog;
    
  public slots:

    /** generate a new document in the actual view */
    void slotFileNew();
    /** open a document */
    void slotFileOpen();
    /** n a document */
    void slotFileSave();
    /** save a document under a different filename*/
    void slotFileSaveAs();
    /** close the actual file */
    void slotFileClose();
    /** print the actual file */
    void slotFilePrint();
    /** exits the application */
    void slotFileQuit();
    /** put the marked text/object into the clipboard && remove
     * it from the document */
    void slotEditCut();
    /** put the marked text/object into the clipboard*/
    void slotEditCopy();
    /** paste the clipboard into the document*/
    void slotEditPaste();
    /** toggle the toolbar*/
    void slotViewToolBar(bool toggle);
    /** toggle the statusbar*/
    void slotViewStatusBar(bool toggle);
    /** This slot is activated when the build button is selected */    
    void buildMenuSlot();   

    /** shows an about dlg*/
    void slotHelpAbout();

    
    /** MY SLOTS */
    void slotViewCPK();
    void slotViewWire();
    void slotViewStick();
    void slotViewBall_Stick();

    void slotHideAll();
    void slotHideMsg();
    void slotHideHydrogen();
    void slotShowHydrogen();
    void slotShowAll();
    void slotHideSideChains();
    void slotShowSideChains();
    void slotHideBackBone();
    void slotShowBackBone();
    void slotHideSelected();

    void slotFlatRibbon();
    void slotCartoonRibbon(bool toggle);
    void slotAnalyticalSurface();
    void slotHideRibbon();
    void slotHideSurface();
    
    void slotHydTreatment(bool toggle);
    void slotFixAtoms();
    void slotFreeAtoms();
    
    /** This slot pops up the new label dialog */
    void slotLabel();
    
    void slotFFCharges();
    void slotAM1Charges();
    void slotMNDO3Charges();
    void slotPM3Charges();
    void slotAM1BCCCharges();
    void slotAM1BCCCharges_fast();

    
    void slotAddDist();
    void slotDelDist();
    void slotDelAllDist();

    void slotAddAng();
    void slotDelAng();
    void slotDelAllAng();

    void slotAddTorsion();
    void slotDelTorsion();
    void slotDelAllTorsion();
    
    void slotMinimize();
    void slotEnergy();
    void slotFlexAlign();
    
    //void slotAngleFunctions(int command);
    //void slotTorsionFunctions(int command);
    
    void slotScriptEditor();

    void slotFog(bool toogle);
    
    void slotKillJob(QString jobName);
    void slotKillJob();
    void slotNewJob(dynoThread *);
   
    /** \brief a simple test slot for python dynamol integration */
    void slotTestPy();
 
    void slotMC();
    void slotMD();
    
    void bgColorSlot();
    void atomColorSlot();
    void atomColorChangeSlot(QString, QString, QString, QString, QString, QString);
    void molColorSelectSlot();
    void molColorElementSlot();
    
    void lightSlot();
    void lightSlot2();
    
    void sysSearchSlot();
    void sysSearchStartSlot();
    
    void confSwarmSlot();
     
    void surfSlot();
    void surfDoneSlot();
    
    void tableSlot();
    
    /** A slot for the gaffFP 2D fingerprint method */
    void gaffFpSlot2();
    
  private:

    /** doc represents your actual document && is created only once. It keeps
     * information such as filename && does the serialization of your files.
     */
    XmodelDoc *doc;

    /** file_menu contains all items of the menubar entry "File" */
    QPopupMenu *fileMenu;
    
    /** edit_menu contains all items of the menubar entry "Edit" */
    QPopupMenu *editMenu;
    /** view_menu contains all items of the menubar entry "View" */
    QPopupMenu *viewMenu;
    /** veiwRender contains all of the items about molecule rendering.  CPK, STICK, Wire, Ribbon, Surface */
    QPopupMenu *viewRender;
    /** viewRibbon will let the user select the ribbon display type */
    QPopupMenu *viewRibbon;
    
    /** This pops up a dialog to change the various colors */
    QPopupMenu *colorMenu;  
 
    /** viewSurface will let the user select the surface display type */    
    QPopupMenu *viewSurface;

    /** viewHide contains all the various options for hiding/showing an atom */
    QPopupMenu *viewHide, *viewShow;
       
    /**hydAdd contains all the information necassary to add hydrogens */
    QPopupMenu *hydTreatment;
    
    /**This menu will allow the user to add charges */
    QPopupMenu *chargeMenu;
    /**This menu is to perform measurements...distance, angle && torsion */
    QPopupMenu *measureMenu;
    /** This is for measure menu related stuff....each of these will have three actions associated with it */
    QPopupMenu *distance, *angle, *torsion;
    /** view_menu contains all items of the menubar entry "Help" */

    /** this is the help menu stuff */
    QPopupMenu *helpMenu;
    
    /** This is the jobMenu stuff */
    QPopupMenu *jobMenu;
        
    /** dynamic menu will contain all the minimization && dynamics routines */
    QPopupMenu *computational;
    	QAction *FlexAlignAction;
      QAction *runScriptAction;   
 
    QPopupMenu *simulation;
      QAction *monteCarlo;
      QAction *md;
    
    /** This is the informatics tab */
    QPopupMenu *informatics;
      QPopupMenu *fingerprint;
         QAction *gafffp2;
      QPopupMenu *diversity;
         QAction *random;
      
    /** the main toolbar */
    QToolBar *fileToolbar;
    /** actions for the application initialized in initActions() && used to en/disable them
      * according to your needs during the program */
    QAction *fileNew;
    QAction *fileOpen;
    QAction *fileSave;
    QAction *fileSaveAs;
    QAction *fileClose;
    QAction *filePrint;
    QAction *fileQuit;

    
        
    /** This will provide functions to interact with the QSWorkbench */
    QAction *scriptMenu;
    
    QAction *editCut;
    QAction *editCopy;
    QAction *editPaste;

    //View menu
    QAction *viewToolBar;
    QAction *viewStatusBar;

    //Render options
    QActionGroup *renderStyle;
    QAction *viewCPK, *viewWire, *viewStick, *viewBall_Stick;
    QAction *hydAdd;
    QAction *fixAtoms;
    QAction *freeAtoms;
    //QAction *hydTreatment;

    //Label option
    QAction *LABELS;
    QActionGroup  *whichLabel;
    QAction *labelAtomType, *labelCharge, *labelSym, *labelFrag, *labelFragNum, *labelNum, *clearLabel;

    //Hide options
    QActionGroup *hideOptions;   //This goup includes the show options below as well
    QAction *hideAll, *hideHydrogens, *hideSideChains, *hideSelected, *hideBackbone, *hideRibbon;
    QAction *hideSurface;
    QAction *hideMsg;

    //Show options
    QAction *showAll, *showHydrogens, *showSideChains, *showBackbone;
    
    //Background Color options
    QAction *background;
    QAction *atomColor;

    
    QAction *buildMenu;
    
    //MolColor
    QPopupMenu *molColor;
    QAction *select;
    QAction *element;
    
    QAction *lighting;

    //Ribbon options
    QActionGroup *ribbonOptions;
    QAction *flatRibbon, *cartoonRibbon;
    
    QActionGroup *surfaceOptions;
    QAction *analyticalSurface, *gausSurf;
    
    //dynamics options
    QAction *minimize;
    QAction *potEnergy;
    
    //Conformation options
    QPopupMenu *conformation;
    QAction *sysSearch;
    QAction *confSwarm;

    QActionGroup *chargeOptions;
    QPopupMenu *am1bccMenu;
    QAction *FF, *AM1, *MNDO3, *AM1BCC, *PM3, *AM1BCC_fast;

    QAction *distAddNew, *distDel, *distDelAll;
    QAction *angAddNew, *angDel, *angDelAll;
    QAction *torsionAddNew, *torsionDel, *torsionDelAll;
    
    QAction *helpAboutApp;
    
    QAction *fog;

    QAction *table;
    
     /** this pops up the conformation dialog widget...I dont' like it here */
    confDialog *cfDialog;

    /** \brief The surface dialog
    *
    */
    surfDialog2 *surf_dialog;
        
    /**  Label types are all binary  1 is on && 0 is off
    
    
    */
    vector<int> Labels;

    /** ChargeType:
        0 = AM1
        1 = MNDO/3
        2 = AM1-BCC
        Define more as you add them
     */
    int chargeType;
    
    //vector<dynoThread *> threads;
    vector<dynoThread *> Jobs;
    //vector<int>		 threadId;
    vector<int>		jobId;
    vector<QAction *> jobActions;
    

    QPixmap cpkIcon;   
};
#endif

