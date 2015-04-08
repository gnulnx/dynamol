/***************************************************************************
                          chemtest.cpp  -  description
                             -------------------
    begin                : Tue Dec 30 21:35:06 EST 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "atom.h"
#include <qaccel.h>
#include "xmodel.h"
#include "filesave.xpm"
#include "fileopen.xpm"
#include "filenew.xpm"
#include "script.xpm"
#include "help.xpm"
#include "surfIcon.xpm"
#include "ribIcon.xpm"
#include "lock.xpm"
#include "unlock.xpm"
#include "builder.xpm"
#include "cpk.xpm"
#include "labels.xpm"
#include "light.xpm"

#include "mintabdialog.h"
#include "mcdialog.h"
#include "mddialog.h"

#include <qcolordialog.h>
#include <qstringlist.h>
#include "lighting.h"
#include "confdialog.h"
#include "conformation.h"
#include <qcombobox.h>
#include <qcheckbox.h>
#include "labeldialog.h"
#include "qdir.h"
#include <qmessagebox.h>
#include <qtextbrowser.h>

#include <qslider.h>

#include <qsscript.h>
#include <qsinterpreter.h>
//#include <qsworkbench.h>
#include "dynascript.h"

#include <qtabwidget.h>

#include "xmodelview.h"
#include "xmodeldoc.h"
#include "molview.h"
#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "enumTypes.h"
#include "fpdialog2.h"

#include "flexaligndialog.h"
#include "flexalign.h"
#include "confpartdialog.h"
#include "confswarmoptimizer.h"
#include <map>

#include "surfstruct.h"
#include "colordialog.h"

//EMBEDDING STUFF
#include "embedded_program.h"
#include "molview_script.h"

#include <boost/shared_ptr.hpp>

//#include "../dynacomp/molecule.h"

XmodelApp::XmodelApp()
{
//   DynaPy("setup.py");
  
  //QMessageBox::critical(0, "Dynamol", "XmodelApp");
  //Set up the label vector
  Labels.resize(7);
  for (int i=0; i<Labels.size(); i++) {
    Labels[i] = 0;
  }

  //initialize charge type to zero
  chargeType = 0;
  
//  setCaption(tr("Xmodel " VERSION));

  ///////////////////////////////////////////////////////////////////
  // call inits to invoke all other construction parts
  initActions();
  initMenuBar();
  initToolBar();
  initStatusBar();

  initDoc();
  initView();

  viewToolBar->setOn(true);
  viewStatusBar->setOn(true);
  //viewCPK->setOn(false);
  //viewWire->setOn(true);
  //viewStick->setOn(false);
}

XmodelApp::~XmodelApp()
{
}

void XmodelApp::setMainApp(QApplication *app) {
   view->setMainApp(app);
}

/** initializes all QActions of the application */
void XmodelApp::initActions(){

  QPixmap openIcon, saveIcon, newIcon, scriptIcon, helpIcon, surfIcon, ribIcon;
  QPixmap lockIcon, unlockIcon, buildIcon, labelIcon, lightIcon;
  newIcon = QPixmap(filenew);
  openIcon = QPixmap(fileopen_xpm);
  saveIcon = QPixmap(filesave_xpm);
  scriptIcon = QPixmap(script_xpm);
  helpIcon = QPixmap(help_xpm);
  surfIcon = QPixmap(surfIcon_xpm);
  ribIcon = QPixmap(ribIcon_xpm);
  lockIcon = QPixmap(lock_xpm);
  unlockIcon = QPixmap(unlock_xpm);
  buildIcon = QPixmap(builder_xpm);
  cpkIcon = QPixmap(cpk_xpm);
  labelIcon = QPixmap(labels_xpm);
  lightIcon = QPixmap(light_xpm);
  //saveIcon = QPixmap("../src/script.png");


  scriptMenu = new QAction(tr("Script Editor"), scriptIcon, tr("&Script Editor"), 0 , this);
  //scriptMenu->setStatusTip(tr("Open the script editor"));
  //scriptMenu->setWhatsThis(tr("New File\n\nCreates a new document"));
  connect(scriptMenu, SIGNAL(activated()), this, SLOT(slotScriptEditor()));
  
  fileNew = new QAction(tr("New File"), newIcon, tr("&New"), QAccel::stringToKey(tr("Ctrl+N")), this);
  fileNew->setStatusTip(tr("Creates a new document"));
  fileNew->setWhatsThis(tr("New File\n\nCreates a new document"));
  connect(fileNew, SIGNAL(activated()), this, SLOT(slotFileNew()));

  fileOpen = new QAction(tr("Open File"), openIcon, tr("&Open..."), 0, this);
  fileOpen->setStatusTip(tr("Opens an existing document"));
  fileOpen->setWhatsThis(tr("Open File\n\nOpens an existing document"));
  connect(fileOpen, SIGNAL(activated()), this, SLOT(slotFileOpen()));

  fileSave = new QAction(tr("Save File"), saveIcon, tr("&Save"), QAccel::stringToKey(tr("Ctrl+S")), this);
  fileSave->setStatusTip(tr("Saves the actual document"));
  fileSave->setWhatsThis(tr("Save File.\n\nSaves the actual document"));
  connect(fileSave, SIGNAL(activated()), this, SLOT(slotFileSave()));

  fileSaveAs = new QAction(tr("Save File As"), saveIcon, tr("Save &as..."), 0, this);
  fileSaveAs->setStatusTip(tr("Saves the actual document under a new filename"));
  fileSaveAs->setWhatsThis(tr("Save As\n\nSaves the actual document under a new filename"));
  connect(fileSaveAs, SIGNAL(activated()), this, SLOT(slotFileSaveAs()));

  /*
  fileClose = new QAction(tr("Close File"), tr("&Close"), QAccel::stringToKey(tr("Ctrl+W")), this);
  fileClose->setStatusTip(tr("Closes the actual document"));
  fileClose->setWhatsThis(tr("Close File\n\nCloses the actual document"));
  connect(fileClose, SIGNAL(activated()), this, SLOT(slotFileClose()));

  filePrint = new QAction(tr("Print File"), tr("&Print"), QAccel::stringToKey(tr("Ctrl+P")), this);
  filePrint->setStatusTip(tr("Prints out the actual document"));
  filePrint->setWhatsThis(tr("Print File\n\nPrints out the actual document"));
  connect(filePrint, SIGNAL(activated()), this, SLOT(slotFilePrint()));
*/
  fileQuit = new QAction(tr("Exit"), tr("E&xit"), QAccel::stringToKey(tr("Ctrl+Q")), this);
  fileQuit->setStatusTip(tr("Quits the application"));
  fileQuit->setWhatsThis(tr("Exit\n\nQuits the application"));
  connect(fileQuit, SIGNAL(activated()), this, SLOT(slotFileQuit()));

  editCut = new QAction(tr("Cut"), tr("Cu&t"), QAccel::stringToKey(tr("Ctrl+X")), this);
  editCut->setStatusTip(tr("Cuts the selected section && puts it to the clipboard"));
  editCut->setWhatsThis(tr("Cut\n\nCuts the selected section && puts it to the clipboard"));
  connect(editCut, SIGNAL(activated()), this, SLOT(slotEditCut()));

  editCopy = new QAction(tr("Copy"), tr("&Copy"), QAccel::stringToKey(tr("Ctrl+C")), this);
  editCopy->setStatusTip(tr("Copies the selected section to the clipboard"));
  editCopy->setWhatsThis(tr("Copy\n\nCopies the selected section to the clipboard"));
  connect(editCopy, SIGNAL(activated()), this, SLOT(slotEditCopy()));

  editPaste = new QAction(tr("Paste"), tr("&Paste"), QAccel::stringToKey(tr("Ctrl+V")), this);
  editPaste->setStatusTip(tr("Pastes the clipboard contents to actual position"));
  editPaste->setWhatsThis(tr("Paste\n\nPastes the clipboard contents to actual position"));
  connect(editPaste, SIGNAL(activated()), this, SLOT(slotEditPaste()));

  viewToolBar = new QAction(tr("Toolbar"), tr("Tool&bar"), 0, this, 0, true);
  viewToolBar->setStatusTip(tr("Enables/disables the toolbar"));
  viewToolBar->setWhatsThis(tr("Toolbar\n\nEnables/disables the toolbar"));
  connect(viewToolBar, SIGNAL(toggled(bool)), this, SLOT(slotViewToolBar(bool)));

  viewStatusBar = new QAction(tr("Statusbar"), tr("&Statusbar"), 0, this, 0, true);
  viewStatusBar->setStatusTip(tr("Enables/disables the statusbar"));
  viewStatusBar->setWhatsThis(tr("Statusbar\n\nEnables/disables the statusbar"));
  connect(viewStatusBar, SIGNAL(toggled(bool)), this, SLOT(slotViewStatusBar(bool)));

  //viewRender =
  //You added in RIGHT HERE
  viewCPK = new QAction(tr("CPK MODEL"), tr("&CPK"), 0, this, 0, true);
  //viewCPK = new QAction(tr("&CPK"), cpkIcon, tr("CPK Modle"), this, 0);
  viewCPK->setStatusTip(tr("Renders all atoms as CPK model"));
  viewCPK->setWhatsThis(tr("CPK view\nRenders atoms in as a space fill model"));
  viewCPK->setToggleAction(false);
  connect(viewCPK, SIGNAL(activated()), this, SLOT(slotViewCPK()));
  //Need to connect to something

  viewWire = new QAction(tr("Wire MODEL"), tr("&WIRE"), 0, this, 0, true);
  viewWire->setStatusTip(tr("Renders all atoms as a wire frame model"));
  viewWire->setWhatsThis(tr("Wire Frame view\nRenders atoms in as a wire frame model"));
  viewWire->setToggleAction(false);
  connect(viewWire, SIGNAL(activated()), this, SLOT(slotViewWire()));

  viewStick = new QAction(tr("Stick MODEL"), tr("&STICK"), 0, this, 0, true);
  viewStick->setStatusTip(tr("Renders all atoms as a stick model"));
  viewStick->setWhatsThis(tr("Wire Frame view\nRenders atoms in as a stick model"));
  viewStick->setToggleAction(false);
  connect(viewStick, SIGNAL(activated()), this, SLOT(slotViewStick()));

  viewBall_Stick = new QAction(tr("Ball && Stick MODEL"), tr("&Ball && STICK"), 0, this, 0, true);
  viewBall_Stick->setStatusTip(tr("Renders all molecules as ball && stick"));
  viewBall_Stick->setWhatsThis(tr("renders atoms as ball && stick"));
  viewBall_Stick->setToggleAction(false);
  connect(viewBall_Stick , SIGNAL(activated()), this, SLOT(slotViewBall_Stick()));

  // #####################

  //LABELS = new QAction(tr("Label Dialog Box"), tr("&Labels"), labelIcon, this, 0, true);
  LABELS = new QAction(tr("Lables"), labelIcon, tr("Lable Molecule  "), 0, this);
  LABELS->setStatusTip(tr("Open the Label Dialog Box"));
  LABELS->setWhatsThis(tr("Open the Label Dialog Box"));
  LABELS->setToggleAction(false);
  connect(LABELS, SIGNAL(activated()), this, SLOT(slotLabel()));
  
  
  //hydAdd
  //hydTreatment
  hydAdd = new QAction(tr("Add hydrogens"), tr("&Add"), 0, this, 0, true);
  hydAdd->setStatusTip(tr("Add/delete Hydrogens"));
  hydAdd->setWhatsThis(tr("rAdds/Deletes Hydrogens"));
  //hydAdd->setToggleAction(false);
  connect(hydAdd , SIGNAL(toggled(bool)), this, SLOT(slotHydTreatment(bool)));
  
  fixAtoms = new QAction(tr("Lock Atoms"), lockIcon, tr("&Lock Atom Positions"), 0, this, 0, true);
  fixAtoms->setStatusTip(tr("Freeze Atom Positions"));
  fixAtoms->setWhatsThis(tr("Freezes the Atoms Positions"));
  //hydAdd->setToggleAction(false);
  connect(fixAtoms , SIGNAL(activated()), this, SLOT(slotFixAtoms()));
  
  freeAtoms = new QAction(tr("Free Atoms"), unlockIcon, tr("&UnLock Atom Positions"), 0, this, 0, true);
  freeAtoms->setStatusTip(tr("Lock Atom Positions"));
  freeAtoms->setWhatsThis(tr("Lock the Atoms Positions"));
  //hydAdd->setToggleAction(false);
  connect(freeAtoms , SIGNAL(activated()), this, SLOT(slotFreeAtoms()));

  hideAll = new QAction(tr("Hide all Atoms"), tr("&All Atoms"), 0, this, 0, true);
  hideAll->setStatusTip(tr("Hides all atoms...Useful for viewing ribbons || surfaces"));
  hideAll->setWhatsThis(tr("Will hide all atoms in the model"));
  hideAll->setToggleAction(false);
  connect(hideAll , SIGNAL(activated()), this, SLOT(slotHideAll()));

  hideMsg = new QAction(tr("Hide Messages"), tr("&Messages"), 0, this, 0, true);
  hideMsg->setStatusTip(tr("Hides Messages"));
  hideMsg->setWhatsThis(tr("Hides the Messages"));
  hideMsg->setToggleAction(false);
  connect(hideMsg , SIGNAL(activated()), this, SLOT(slotHideMsg()));

  hideSideChains = new QAction(tr("Hide Protein side chain atoms"), tr("&Side Chains"), 0, this, 0, true);
  hideSideChains->setStatusTip(tr("Hides the protein side chains."));
  hideSideChains->setWhatsThis(tr("Will hide the protein side chains"));
  hideSideChains->setToggleAction(false);
  connect(hideSideChains , SIGNAL(activated()), this, SLOT(slotHideSideChains()));

  showSideChains = new QAction(tr("Show side chains"), tr("&Side Chains"), 0, this, 0, true);
  showSideChains->setStatusTip(tr("Shows protein side chains"));
  showSideChains->setWhatsThis(tr("Will show all protein side chains"));
  showSideChains->setToggleAction(false);
  connect(showSideChains , SIGNAL(activated()), this, SLOT(slotShowSideChains()));

  hideBackbone = new QAction(tr("Hide protein backbone atoms"), tr("&Backbone"), 0, this, 0, true);
  hideBackbone->setStatusTip(tr("Hides the protein backbone atoms."));
  hideBackbone->setWhatsThis(tr("Will hide the protein backbone atoms"));
  hideBackbone->setToggleAction(false);
  connect(hideBackbone , SIGNAL(activated()), this, SLOT(slotHideBackBone()));

  hideRibbon = new QAction(tr("Hide the ribbon"), tr("&Ribbon"), 0, this, 0, true);
  hideRibbon->setStatusTip(tr("Hides the ribbon."));
  hideRibbon->setWhatsThis(tr("Will hide the ribbon"));
  hideRibbon->setToggleAction(false);
  connect(hideRibbon , SIGNAL(activated()), this, SLOT(slotHideRibbon()));

  hideSurface = new QAction(tr("Hide the surface"), tr("&Surface"), 0, this, 0, true);
  hideSurface->setStatusTip(tr("Hides the molecular surface."));
  hideSurface->setWhatsThis(tr("Will hide the surface"));
  hideSurface->setToggleAction(false);
  connect(hideSurface , SIGNAL(activated()), this, SLOT(slotHideSurface()));

  showBackbone = new QAction(tr("Show protein backbone atoms"), tr("&Backbone"), 0, this, 0, true);
  showBackbone->setStatusTip(tr("Show's the protein backbone atoms."));
  showBackbone->setWhatsThis(tr("Will show the protein backbone atoms"));
  showBackbone->setToggleAction(false);
  connect(showBackbone , SIGNAL(activated()), this, SLOT(slotShowBackBone()));

  hideHydrogens = new QAction(tr("Hide all hydrogens"), tr("&Hydrogens"), 0, this, 0, true);
  hideHydrogens->setStatusTip(tr("Hides all hydrogen atoms"));
  hideHydrogens->setWhatsThis(tr("Will hide all hydrogen atoms in the model"));
  hideHydrogens->setToggleAction(false);
  connect(hideHydrogens , SIGNAL(activated()), this, SLOT(slotHideHydrogen()));

  hideSelected = new QAction(tr("Hide all selected atoms"), tr("&Selected"), 0, this, 0, true);
  hideSelected->setStatusTip(tr("Hides all selected atoms"));
  hideSelected->setWhatsThis(tr("Will hide all selected atoms in the model"));
  hideSelected->setToggleAction(false);
  connect(hideSelected , SIGNAL(activated()), this, SLOT(slotHideSelected()));


  showAll = new QAction(tr("Show all atoms"), tr("&All"), 0, this, 0, true);
  showAll->setStatusTip(tr("Show all atoms"));
  showAll->setWhatsThis(tr("Will show all atoms in the model"));
  showAll->setToggleAction(false);
  connect(showAll , SIGNAL(activated()), this, SLOT(slotShowAll()));

  showHydrogens = new QAction(tr("Show hydrogens"), tr("&Hydrogens"), 0, this, 0, true);
  showHydrogens->setStatusTip(tr("Show all hydrogens"));
  showHydrogens->setWhatsThis(tr("Will show all hydrogens in the model"));
  showHydrogens->setToggleAction(false);
  connect(showHydrogens , SIGNAL(activated()), this, SLOT(slotShowHydrogen()));

  flatRibbon = new QAction(tr("Render a flat ribbon model of the protein backbone"), ribIcon, tr("&Ribbon  "), 0, this, 0, true);
  flatRibbon->setStatusTip(tr("Renders a flat ribbon model of the protein side chains"));
  flatRibbon->setWhatsThis(tr("Will render a flat ribbon model of the protien side chain"));
  flatRibbon->setToggleAction(false);
  connect(flatRibbon , SIGNAL(activated()), this, SLOT(slotFlatRibbon()));

  cartoonRibbon = new QAction(tr("Render a cartoon ribbon model of the protein backbone"), tr("&Cartoon Ribbon"), 0, this, 0, true);
  cartoonRibbon->setStatusTip(tr("Renders a cartoon ribbon model of the protein side chains"));
  cartoonRibbon->setWhatsThis(tr("Will render a cartoon ribbon model of the protien side chain"));
  connect(cartoonRibbon , SIGNAL(toggled(bool)), this, SLOT(slotCartoonRibbon(bool)));

  analyticalSurface = new QAction(tr("Render an analytical surface of the molecule"), tr("&Analytical"), 0, this, 0, true);
  analyticalSurface->setStatusTip(tr("Render an analytical surface of the molecule"));
  analyticalSurface->setWhatsThis(tr("Render an analytical surface of the molecule"));
  analyticalSurface->setToggleAction(false);
  connect(analyticalSurface , SIGNAL(activated()), this, SLOT(slotAnalyticalSurface()));

  gausSurf = new QAction(tr("Render an gaussian surface of the molecule"), surfIcon, tr("&Surface"), 0, this, 0, true);
  gausSurf->setStatusTip(tr("Render an gaussian surface of the molecule"));
  gausSurf->setWhatsThis(tr("Render an gaussian surface of the molecule"));
  gausSurf->setToggleAction(false);
  connect(gausSurf , SIGNAL(activated()), this, SLOT(slotAnalyticalSurface()));
 
  //CHARGE SECTION
  FF = new QAction(tr("Calculate FF Charges"), tr("&Force Field"), 0, this, 0, true);
  FF->setStatusTip(tr("Calculates charges based on Forcefield.  For proteins this is amber 2000 && for small molecules it is AM1-BCC"));
  FF->setWhatsThis(tr("Will calculate AM1 charges"));
  connect(FF , SIGNAL(activated()), this, SLOT(slotFFCharges()));
  
  AM1 = new QAction(tr("Calculate AM1 Charges"), tr("&AM1"), 0, this, 0, true);
  AM1->setStatusTip(tr("Uses the mopac program to calculate AM1 charges"));
  AM1->setWhatsThis(tr("Will calculate AM1 charges"));
  AM1->setToggleAction(false);
  connect(AM1 , SIGNAL(activated()), this, SLOT(slotAM1Charges()));


  AM1BCC = new QAction(tr("Calculate AM1-BCC Charges with MOPAC Optimization"), tr("&Optmize"), 0, this, 0, true);
  AM1BCC->setStatusTip(tr("Uses MOPAC Optimization to calculate AM1-BCC charges"));
  AM1BCC->setWhatsThis(tr("Will calculate AM1-BCC charges with MOPAC Optimization"));
  AM1BCC->setToggleAction(false);
  connect(AM1BCC, SIGNAL(activated()), this, SLOT(slotAM1BCCCharges()));

   AM1BCC_fast = new QAction(tr("Calculate AM1-BCC Charges without MOPAC Optimization"), tr("&Fast"), 0, this,
 0, true);
  AM1BCC_fast->setStatusTip(tr("Calculate AM1-BCC charges without MOPAC Optimization"));
  AM1BCC_fast->setWhatsThis(tr("Will calculate AM1-BCC charges"));
  AM1BCC_fast->setToggleAction(false);
  connect(AM1BCC_fast, SIGNAL(activated()), this, SLOT(slotAM1BCCCharges_fast()));


  MNDO3 = new QAction(tr("Calculate MNDO3 Charges"), tr("&MNDO3"), 0, this, 0, true);
  MNDO3->setStatusTip(tr("Uses the mopac program to calculate MNDO3 charges"));
  MNDO3->setWhatsThis(tr("Will calculate MNDO/3 charges"));
  MNDO3->setToggleAction(false);
  connect(MNDO3 , SIGNAL(activated()), this, SLOT(slotMNDO3Charges()));
  
  PM3 = new QAction(tr("Calculate PM3 Charges"), tr("&PM3"), 0, this, 0, true);
  PM3->setStatusTip(tr("Uses the mopac program to calculate PM3 charges"));
  PM3->setWhatsThis(tr("Will calculate PM3 charges"));
  PM3->setToggleAction(false);
  connect(PM3 , SIGNAL(activated()), this, SLOT(slotPM3Charges()));
 // QActionGroup *chargteOptions;
  //  QAction *AM1, *MNDO3;

  distAddNew = new QAction(tr("Add a new distance"), tr("&New Distance"), QAccel::stringToKey(tr("Ctrl+D")), this);
  //distAddNew = new QAction(tr("Add a new distance"), tr("&New Distance"), 0, this, 0, true);
  distAddNew->setStatusTip(tr("Select atoms for distance"));
  distAddNew->setWhatsThis(tr("This will calculate two distances"));
  distAddNew->setToggleAction(false);
  connect(distAddNew, SIGNAL(activated()), this, SLOT(slotAddDist()));  

  distDel = new QAction(tr("Delete a distance"), tr("&Delete Distance"), QAccel::stringToKey(tr("Alt+D")), this);
  //distDel = new QAction(tr("Delete a distance"), tr("&Delete Distance"), 0, this, 0, true);
  distDel->setStatusTip(tr("Select atoms in distance to delete"));
  distDel->setWhatsThis(tr("This will delete a distances"));
  distDel->setToggleAction(false);
  connect(distDel , SIGNAL(activated()), this, SLOT(slotDelDist()));

  distDelAll = new QAction(tr("Delete all Distance's"), tr("&Delete all Distance's"), QAccel::stringToKey(tr("Shift+D")), this);
  //distDelAll = new QAction(tr("Delete all Distance's"), tr("&Delete all Distance's"), 0, this, 0, true);
  distDelAll->setStatusTip(tr("Delete's all distances"));
  distDelAll->setWhatsThis(tr("This will delete all distance's"));
  distDelAll->setToggleAction(false);
  connect(distDelAll , SIGNAL(activated()), this, SLOT(slotDelAllDist()));

  angAddNew = new QAction(tr("Add a new angle"), tr("&New angle"), QAccel::stringToKey(tr("Ctrl+A")), this);
  angAddNew->setStatusTip(tr("Select atoms for angle"));
  angAddNew->setWhatsThis(tr("This will calculate the angle between three atoms"));
  angAddNew->setToggleAction(false);
  connect(angAddNew , SIGNAL(activated()), this, SLOT(slotAddAng()));


  angDel = new QAction(tr("Delete a angle"), tr("&Delete angle"), QAccel::stringToKey(tr("Alt+A")), this);
  angDel->setStatusTip(tr("Select atoms in angle to delete"));
  angDel->setWhatsThis(tr("This will delete an angle"));
  angDel->setToggleAction(false);
  connect(angDel , SIGNAL(activated()), this, SLOT(slotDelAng()));

  angDelAll = new QAction(tr("Delete all angle's"), tr("&Delete all angle's"), QAccel::stringToKey(tr("Shift+A")), this);
  angDelAll->setStatusTip(tr("Delete's all angle"));
  angDelAll->setWhatsThis(tr("This will delete all angle's"));
  angDelAll->setToggleAction(false);
  connect(angDelAll , SIGNAL(activated()), this, SLOT(slotDelAllAng()));

  torsionAddNew = new QAction(tr("Add a new torsion"), tr("&New torsion"), QAccel::stringToKey(tr("Ctrl+T")), this);
  torsionAddNew->setStatusTip(tr("Select atoms for torsion"));
  torsionAddNew->setWhatsThis(tr("This will calculate the torsion between four atoms"));
  torsionAddNew->setToggleAction(false);
  connect(torsionAddNew , SIGNAL(activated()), this, SLOT(slotAddTorsion()));

  torsionDel = new QAction(tr("Delete a torsion"), tr("&Delete torsion"), QAccel::stringToKey(tr("Alt+T")), this);
  torsionDel->setStatusTip(tr("Select atoms in torsion to delete"));
  torsionDel->setWhatsThis(tr("This will delete a torsion"));
  torsionDel->setToggleAction(false);
  connect(torsionDel , SIGNAL(activated()), this, SLOT(slotDelTorsion()));

  torsionDelAll = new QAction(tr("Delete all torsion's  "), tr("&Delete all torsion's  "), QAccel::stringToKey(tr("Shift+T")), this);
  torsionDelAll->setStatusTip(tr("Delete's all torsion  "));
  torsionDelAll->setWhatsThis(tr("This will delete all torsion's  "));
  torsionDelAll->setToggleAction(false);
  connect(torsionDelAll , SIGNAL(activated()), this, SLOT(slotDelAllTorsion()));
 
  minimize = new QAction(tr("Minimize  "), tr("&Minimize  "), 0, this);
  minimize->setStatusTip(tr("Minimize the system  "));
  minimize->setWhatsThis(tr("Minimize the system  "));
  connect(minimize, SIGNAL(activated()), this, SLOT(slotMinimize()));
  
  potEnergy = new QAction(tr("Potential Energy  "), tr("&Potential Energy  "), 0, this);
  potEnergy->setStatusTip(tr("Display the current Energy of the system  "));
  potEnergy->setWhatsThis(tr("Display the current Energy of the system  "));
  connect(potEnergy, SIGNAL(activated()), this, SLOT(slotEnergy()));
  
  fog = new QAction(tr("Fog  "), tr("&Fog  "), 0, this);
  fog->setStatusTip(tr("Toggle Fog  "));
  fog->setWhatsThis(tr("Toggle Fog  "));
  connect(fog , SIGNAL(toggled(bool)), this, SLOT(slotFog(bool)));
  
  // END MY SECTION

  helpAboutApp = new QAction(tr("Manual  "), helpIcon, tr("&Manual  "), QAccel::stringToKey(tr("Ctrl+H")), this);
  //helpAboutApp = new QAction(tr("Manual"), helpIcon, tr("&Manual"), 0, this);
  helpAboutApp->setStatusTip(tr("Manual covering dynamol usage  "));
  helpAboutApp->setWhatsThis(tr("About\n\nAbout the application  "));
  connect(helpAboutApp, SIGNAL(activated()), this, SLOT(slotHelpAbout()));

  background = new QAction(tr("Background  "), tr("&Background  "), 0, this);
  background->setStatusTip(tr("Set Background Color  "));
  background->setWhatsThis(tr("Set Background Color  "));
  connect(background , SIGNAL(activated()), this, SLOT(bgColorSlot()));

  atomColor  = new QAction(tr("Atom Colors  "), tr("&Atom Colors  "), 0, this);
  atomColor->setStatusTip(tr("Set Atom Colors  "));
  atomColor->setWhatsThis(tr("Set Atom Colors  "));
  connect(atomColor , SIGNAL(activated()), this, SLOT(atomColorSlot()));

  select = new QAction(tr("Select  "), tr("&Select  "), 0, this);
  select->setStatusTip(tr("Select Molecule Color  "));
  select->setWhatsThis(tr("Select Molecule Color  "));
  connect(select , SIGNAL(activated()), this, SLOT(molColorSelectSlot()));
  
  element = new QAction(tr("Element  "), tr("&Element  "), 0, this);
  element->setStatusTip(tr("Set Molecule Color to Element Type  "));
  element->setWhatsThis(tr("Set Molecule Color to element Type  "));
  connect(element , SIGNAL(activated()), this, SLOT(molColorElementSlot()));
  
  
  lighting = new QAction(tr("Lighting  "), lightIcon, tr("&Lighting  "), 0, this);
  lighting->setStatusTip(tr("Adjust the light properties  "));
  lighting->setWhatsThis(tr("Adjust the light properties  "));
  connect(lighting , SIGNAL(activated()), this, SLOT(lightSlot()));
  /*
  fileNew = new QAction(tr("New File"), newIcon, tr("&New"), QAccel::stringToKey(tr("Ctrl+N")), this);
  fileNew->setStatusTip(tr("Creates a new document"));
  fileNew->setWhatsThis(tr("New File\n\nCreates a new document"));
  connect(fileNew, SIGNAL(activated()), this, SLOT(slotFileNew()));
  */
  
  monteCarlo = new QAction(tr("Monte Carlo  "), tr("&Monte Carlo  "), 0, this);
  monteCarlo->setStatusTip(tr("Monte Carlo Simulation  "));
  monteCarlo->setWhatsThis(tr("Monte Carlo Simulation  "));
  connect(monteCarlo , SIGNAL(activated()), this, SLOT(slotMC()));  
  
  md = new QAction(tr("Molecular Dynamics  "), tr("&Molecular Dynamics  "), 0, this);
  md->setStatusTip(tr("Molecular Dynamics Simulation  "));
  md->setWhatsThis(tr("Molecular Dynamics Simulation  "));
  connect(md , SIGNAL(activated()), this, SLOT(slotMD())); 
  
  FlexAlignAction = new QAction(tr("Flexible Alignment  "), tr("&Flex Align  "), 0, this);
  FlexAlignAction->setStatusTip(tr("Flexibl Alignment  "));
  FlexAlignAction->setWhatsThis(tr("Flexibl Alignment  "));
  connect(FlexAlignAction , SIGNAL(activated()), this, SLOT(slotFlexAlign()));
 
  runScriptAction = new QAction(tr("Run Test Script  "), tr("&Run test.py  "), 0, this);
  runScriptAction->setStatusTip(tr("Run Test Script  "));
  runScriptAction->setWhatsThis(tr("Run Test Script  "));
  connect(runScriptAction , SIGNAL(activated()), this, SLOT(slotTestPy()));
 
  sysSearch = new QAction(tr("Systematic Search  "), tr("&Systematic Search  "), 0, this);
  sysSearch->setStatusTip(tr("Systematic Conformational Search  "));
  sysSearch->setWhatsThis(tr("Systematic Conformational Search  "));
  connect(sysSearch , SIGNAL(activated()), this, SLOT(sysSearchSlot()));  
  
  confSwarm = new QAction(tr("PSO Search  "), tr("&PSO Search  "), 0, this);
  confSwarm->setStatusTip(tr("PSO Search  "));
  confSwarm->setWhatsThis(tr("PSO Search  "));
  connect(confSwarm , SIGNAL(activated()), this, SLOT(confSwarmSlot()));  
  
    
  buildMenu = new QAction(tr("Molecular Editor  "), buildIcon, tr("&Molecular Editor  "), 0, this);
  buildMenu->setStatusTip(tr("Molecular Editor  "));
  buildMenu->setWhatsThis(tr("Molecular Editor  "));
  connect(buildMenu , SIGNAL(activated()), this, SLOT(buildMenuSlot()));
 
  //fileNew = new QAction(tr("New File"), newIcon, tr("&New"), QAccel::stringToKey(tr("Ctrl+N")), this); 
  table = new QAction(tr("&New Mol Table  "), newIcon, tr("&New Mol Table  "), 0, this);
  table->setStatusTip(tr("&New Mol Table  "));
  table->setWhatsThis(tr("&New Mol Table  "));
  connect(table , SIGNAL(activated()), this, SLOT(tableSlot()));
 
  gafffp2 = new QAction(tr("Search Databases  "), tr("Search Databases  "), 0, this);
  gafffp2->setStatusTip(tr("Search Databases  "));
  gafffp2->setWhatsThis(tr("Search Databases  "));
  connect(gafffp2 , SIGNAL(activated()), this, SLOT(gaffFpSlot2()));
  
}

void XmodelApp::initMenuBar()
{
  ///////////////////////////////////////////////////////////////////
  // MENUBAR

  ///////////////////////////////////////////////////////////////////
  // menuBar entry fileMenu
  fileMenu=new QPopupMenu();
  //fileNew->addTo(fileMenu);
  table->addTo(fileMenu);
  fileOpen->addTo(fileMenu);
 // fileClose->addTo(fileMenu);
  fileMenu->insertSeparator();
  fileSaveAs->addTo(fileMenu);
  //fileSave->addTo(fileMenu);
  fileMenu->insertSeparator();
  //filePrint->addTo(fileMenu);
  fileMenu->insertSeparator();
  fileQuit->addTo(fileMenu);
  
  
  
  jobMenu=new QPopupMenu();

  
  ///////////////////////////////////////////////////////////////////
  // menuBar entry editMenu
  editMenu=new QPopupMenu();
     fixAtoms->addTo(editMenu);
     fixAtoms->setToggleAction(false);
     freeAtoms->addTo(editMenu);
     freeAtoms->setToggleAction(false);
     buildMenu->addTo(editMenu);
  
  hydTreatment = new QPopupMenu();
  hydAdd->addTo(hydTreatment);
  hydTreatment->setCheckable(false);
  
  ///////////////////////////////////////////////////////////////////
  // menuBar entry viewMenu
  viewMenu=new QPopupMenu();
  viewToolBar->addTo(viewMenu);
  viewMenu->insertSeparator();

  fog->addTo(viewMenu);
   fog->setToggleAction(true);
  
  lighting->addTo(viewMenu);
  //You added HERE

  colorMenu = new QPopupMenu();
  colorMenu->setCheckable(false);
      background->addTo(colorMenu);
      atomColor->addTo(colorMenu);
      molColor = new QPopupMenu();
  colorMenu->insertItem("&Molecule  ", molColor);
     select->addTo(molColor);
     element->addTo(molColor);
  
  viewRender = new QPopupMenu();
  viewRender->setCheckable(false);
      renderStyle = new QActionGroup( viewRender );
      renderStyle->addTo(viewRender);
          renderStyle->add(viewCPK);
          renderStyle->add(viewWire);
          renderStyle->add(viewStick);
          renderStyle->add(viewBall_Stick);

      viewCPK->addTo(viewRender);
      viewWire->addTo(viewRender);
      viewStick->addTo(viewRender);
      viewBall_Stick->addTo(viewRender);

      //QAction *labelAtomType, *labelCharge, *labelSym, *labelFrag;
    
  viewHide = new QPopupMenu();
  viewHide->setCheckable(false);
      hideOptions = new QActionGroup( viewHide );
      hideOptions->setExclusive(true);
          hideOptions->add(hideAll);
          hideOptions->add(hideHydrogens);
          hideOptions->add(hideSideChains);
          hideOptions->add(hideSelected);
          hideOptions->add(showAll);
          hideOptions->add(showHydrogens);
          hideOptions->add(showSideChains);
          hideOptions->add(hideBackbone);
          hideOptions->add(showBackbone);
          hideOptions->add(hideRibbon);
          hideOptions->add(hideSurface);
	 
	  //hideOptions->setCheckable(false);
	 

      hideMsg->addTo(viewHide);
      viewHide->insertSeparator(); 
      hideAll->addTo(viewHide);
      hideHydrogens->addTo(viewHide);
      hideSideChains->addTo(viewHide);
      hideBackbone->addTo(viewHide);
      hideSelected->addTo(viewHide);
      viewHide->insertSeparator();  
      hideRibbon->addTo(viewHide);
      hideSurface->addTo(viewHide);

  viewShow = new QPopupMenu();
  viewShow->setCheckable(false);
    showAll->addTo(viewShow);
    //showAll->setToggleAction(false);
    showHydrogens->addTo(viewShow);
    //showHydrogens->setToggleAction(false);
    showSideChains->addTo(viewShow);
    //showSideChains->setToggleAction(false);
    showBackbone->addTo(viewShow);
    
    //showBackbone->setToggleAction(false);

  viewRibbon = new QPopupMenu();
  viewRibbon->setCheckable(false);
      ribbonOptions = new QActionGroup(viewRibbon);
      ribbonOptions->setExclusive(true);
      ribbonOptions->add(flatRibbon);
      flatRibbon->addTo(viewRibbon);
      
  viewSurface = new QPopupMenu();
  viewSurface->setCheckable(false);
      surfaceOptions = new QActionGroup(viewSurface);
      surfaceOptions->setExclusive(true);
      //surfaceOptions->add(analyticalSurface);
      surfaceOptions->add(gausSurf);
      //analyticalSurface->addTo(viewSurface);
      gausSurf->addTo(viewSurface);
  

  
  //  QAction *AM1, *MNDO3;

  measureMenu = new QPopupMenu();
    distance = new QPopupMenu();
    distance->setCheckable(false);
      distAddNew->addTo(distance);
      distDel->addTo(distance);
      distDelAll->addTo(distance);

    angle = new QPopupMenu();
    angle->setCheckable(false);
      angAddNew->addTo(angle);
      angDel->addTo(angle);
      angDelAll->addTo(angle);
          
    torsion= new QPopupMenu();
    torsion->setCheckable(false);
      torsionAddNew->addTo(torsion);
      torsionDel->addTo(torsion);
      torsionDelAll->addTo(torsion);
      
    computational = new QPopupMenu();
    computational->setCheckable(false);
    	chargeMenu = new QPopupMenu();
  	chargeMenu->setCheckable(false);
        am1bccMenu = new QPopupMenu();
     	chargeOptions = new QActionGroup(chargeMenu);
        chargeOptions->setExclusive(true);
        chargeOptions->add(FF);
	chargeOptions->add(AM1);
        chargeOptions->add(AM1BCC);
        chargeOptions->add(MNDO3);
	chargeOptions->add(PM3);
	FF->addTo(chargeMenu);
        chargeMenu->insertItem(tr("&AM1-BCC  "), am1bccMenu);
	AM1BCC->addTo(am1bccMenu);
        AM1BCC_fast->addTo(am1bccMenu);
     	AM1->addTo(chargeMenu);
	PM3->addTo(chargeMenu);
     	MNDO3->addTo(chargeMenu);
	//chargeMenu->addTo(computational);
        potEnergy->addTo(computational);
        computational->insertSeparator();
        computational->insertItem(tr("&Charges  "), chargeMenu);
        computational->insertSeparator();
        minimize->addTo(computational);
        FlexAlignAction->addTo(computational);
        runScriptAction->addTo(computational);
        monteCarlo->addTo(computational);
        //md->addTo(computational);
        
     conformation = new QPopupMenu();
     conformation->setCheckable(false);
        sysSearch->addTo(conformation);
        //confSwarm->addTo(conformation);
        //md->addTo(computational);
	
    	
   informatics = new QPopupMenu();
      fingerprint = new QPopupMenu();
      //informatics->insertItem("Search Database  ", fingerprint);
      gafffp2->addTo(informatics);
      //QPopupMenu *fingerprint;     


  //simulation = new QPopupMenu();
     //monteCarlo->addTo(simulation);
     //md->addTo(simulation);
  ///////////////////////////////////////////////////////////////////
  // EDIT YOUR APPLICATION SPECIFIC MENUENTRIES HERE

  ///////////////////////////////////////////////////////////////////
  // menuBar entry helpMenu
  helpMenu=new QPopupMenu();
  helpAboutApp->addTo(helpMenu);

  ///////////////////////////////////////////////////////////////////
  // MENUBAR CONFIGURATION
  menuBar()->insertItem(tr("&File"), fileMenu);
  menuBar()->insertItem(tr("&Edit"), editMenu);
     editMenu->insertItem(tr("&Hydrogens  "), hydTreatment); 
  menuBar()->insertItem(tr("&View"), viewMenu);
    viewMenu->insertItem(tr("&Color  "), colorMenu);   
    viewMenu->insertSeparator(); 
    viewMenu->insertItem(cpkIcon, tr("Dislplay Style  "), viewRender); //You added this line 
    //viewMenu->insertItem(tr("&Ribbons  "), viewRibbon);
    //viewMenu->insertItem(tr("&Surface  "), viewSurface);
    //viewMenu->insertItem(tr("&Surface  "), gausSurf);
    gausSurf->addTo(viewMenu);
    flatRibbon->addTo(viewMenu);
    LABELS->addTo(viewMenu);
    //viewMenu->insertItem(tr("&Label"), viewLabel);
    viewMenu->insertItem(tr("&Hide  "), viewHide);
    viewMenu->insertItem(tr("&Show  "), viewShow);
   
  //menuBar()->insertItem(tr("&Hydrogens"), hydTreatment);
  //menuBar()->insertItem(tr("&Charges"), chargeMenu);
  menuBar()->insertItem("&Computational", computational);
     computational->insertItem(tr("&Conformation"), conformation);
  menuBar()->insertItem("Informatics", informatics);
  
//  menuBar()->insertItem("&Simulations", simulation);
  
  menuBar()->insertItem("&Jobs", jobMenu);
  
    
  menuBar()->insertItem("&Measure", measureMenu);
    measureMenu->insertItem("&Distance  ", distance);
    measureMenu->insertItem("&Angle  ", angle);
    measureMenu->insertItem("&Torsion  ", torsion);
  menuBar()->insertSeparator();
 
  
     
  menuBar()->insertSeparator(5);
  menuBar()->insertItem("&Help", helpMenu);
  
  
  
}

void XmodelApp::initToolBar()
{
  ///////////////////////////////////////////////////////////////////
  // TOOLBAR
  fileToolbar = new QToolBar(this, "file operations");
  //fileNew->addTo(fileToolbar);
  fileOpen->addTo(fileToolbar);
  //fileSave->addTo(fileToolbar);
  fileSaveAs->addTo(fileToolbar);
  fileToolbar->addSeparator();
  //buildMenu->addTo(fileToolbar);
  scriptMenu->addTo(fileToolbar);
  buildMenu->addTo(fileToolbar);
  //LABELS->addTo(fileToolbar);
  fileToolbar->addSeparator();
  LABELS->addTo(fileToolbar);
  lighting->addTo(fileToolbar);
  gausSurf->addTo(fileToolbar);
  flatRibbon->addTo(fileToolbar); 
  fileToolbar->addSeparator();
  helpAboutApp->addTo(fileToolbar);
  //QWhatsThis::whatsThisButton(fileToolbar);

}

void XmodelApp::initStatusBar()
{
  ///////////////////////////////////////////////////////////////////
  //STATUSBAR
  statusBar()->message(tr("Ready."), 2000);
}

void XmodelApp::initDoc()
{
   //QMessageBox::critical(0, "Dynamol", "initDoc");
   doc=new XmodelDoc();
}

void XmodelApp::initView()
{
  ////////////////////////////////////////////////////////////////////
  // set the main widget here
  //QMessageBox::critical(0, "Dynamol", "initView");
  view=new XmodelView(this, doc);
  //QMessageBox::critical(0, "Dynamol", "after XmodelView creation");
  setCentralWidget(view);
}

bool XmodelApp::queryExit()
{
  int exit=QMessageBox::information(this, tr("Quit..."),
                                    tr("Do your really want to quit?"),
                                    QMessageBox::Ok, QMessageBox::Cancel);

  if (exit==1)
  {

  }
  else
  {

  };

  return (exit==1);
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////


void XmodelApp::slotFileNew()
{
  statusBar()->message(tr("Creating new file..."));
  doc->newDoc();
  statusBar()->message(tr("Ready."));
}

void XmodelApp::slotFileOpen()
{
  statusBar()->message(tr("Opening file..."));

  //QString fileName = QFileDialog::getOpenFileName(0,0,this);
  QStringList fileNames = QFileDialog::getOpenFileNames("mols(*.list *.mol2 *.ent *.pdb *.sdf *.mol *.SDF *.mae)",0,this);
  
  
  if (!fileNames.isEmpty())
  {
    for ( QStringList::Iterator fileIt = fileNames.begin(); fileIt != fileNames.end(); ++fileIt ) {
    	doc->load(*fileIt);
	setCaption(*fileIt);
	QString message=tr("Loaded document: ")+(*fileIt);
	statusBar()->message(message, 2000);
    }    
  }
  else
  {
    statusBar()->message(tr("Opening aborted"), 2000);
  }
  
}


void XmodelApp::slotFileSave()
{
 
  statusBar()->message(tr("Saving file..."));
  doc->save();
  statusBar()->message(tr("Ready."));
}

void XmodelApp::slotFileSaveAs()
{
  
  statusBar()->message(tr("Saving file under new filename..."));
  //QString fn = QFileDialog::getSaveFileName(0, 0, this);
  bool cont = true;
  QString fn;  
  while (cont) {
  fn = QFileDialog::getSaveFileName(
                    "./",
                    "molTypes (*.sdf *.mol2)",
                    this,
                    "save file dialog",
                    "Choose a filename to save under" );
    if (fn == "")  
       return;
    
    cont = QFile::exists( fn ) &&
       QMessageBox::question(this, tr("Overwrite File? -- Application Name"),
       tr("A file called %1 already exists." "Do you want to overwrite it?").arg( fn ),
       tr("&Yes"), tr("&No"), QString::null, 0, 1 ); 
  }

  if (!fn.isEmpty())
  {
    doc->saveAs(fn, *view->viewer->renList);
  }
  else
  {
    statusBar()->message(tr("Saving aborted"), 2000);
  }

  statusBar()->message(tr("Ready."));
}

void XmodelApp::slotFileClose()
{
  statusBar()->message(tr("Closing file..."));

  statusBar()->message(tr("Ready."));
}

void XmodelApp::slotFilePrint()
{
  statusBar()->message(tr("Printing..."));
  QPrinter printer;
  if (printer.setup(this))
  {
    QPainter painter;
    painter.begin(&printer);

    ///////////////////////////////////////////////////////////////////
    // TODO: Define printing by using the QPainter methods here

    painter.end();
  };

  statusBar()->message(tr("Ready."));
}

void XmodelApp::slotFileQuit()
{
  statusBar()->message(tr("Exiting application..."));
  ///////////////////////////////////////////////////////////////////
  // exits the Application
  if(doc->isModified())
  {
    if(queryExit())
    {
      qApp->quit();
    }
    else
    {

    };
  }
  else
  {
    qApp->quit();
  };

  statusBar()->message(tr("Ready."));
}

void XmodelApp::slotEditCut()
{
  statusBar()->message(tr("Cutting selection..."));

  statusBar()->message(tr("Ready."));
}

void XmodelApp::slotEditCopy()
{
  statusBar()->message(tr("Copying selection to clipboard..."));

  statusBar()->message(tr("Ready."));
}

void XmodelApp::slotEditPaste()
{
  statusBar()->message(tr("Inserting clipboard contents..."));

  statusBar()->message(tr("Ready."));
}


void XmodelApp::slotViewToolBar(bool toggle)
{
  statusBar()->message(tr("Toggle toolbar..."));
  ///////////////////////////////////////////////////////////////////
  // turn Toolbar on || off

  if (toggle== false)
  {
    fileToolbar->hide();
  }
  else
  {
    fileToolbar->show();
    //fileToolbar->hide();
  };

  statusBar()->message(tr("Ready."));
}

void XmodelApp::slotViewStatusBar(bool toggle)
{
  statusBar()->message(tr("Toggle statusbar..."));
  ///////////////////////////////////////////////////////////////////
  //turn Statusbar on || off

  if (toggle == false)
  {
    statusBar()->hide();
  }
  else
  {
    statusBar()->show();
  }

  statusBar()->message(tr("Ready."));
}

void XmodelApp::slotHelpAbout()
{ 
  static bool toggle = false;
  if (toggle == false) {
     view->helpTab = new QTextBrowser(view->tabs, "Manual");
     view->helpTab->mimeSourceFactory()->setExtensionType("html", "text/html;charset=iso8859-1");
     view->tabs->addTab(view->helpTab, "Manual");     
     //##################################### PORT SECTION #################
  
      QString Path = "";
      #ifdef WINDOWS
         Path = QDir::currentDirPath();
         Path += "\\..\\Documentation\\index.html";
      #endif
  
      #ifdef LINUX
         Path = getenv("DYNAMOL");
         Path += "/Documentation/index.html";
      #endif
      
      //######################################## END PORT SECTION ############
	
      view->helpTab->setSource(Path.latin1());           
      toggle = true;      
  } else {
      toggle = false;
      delete view->helpTab;
//      view->helpTab->hide();
  }
}


void XmodelApp::slotViewCPK() {
  //if (toggle == true)
    view->setRenderType(NOBOND, CPK);
}

void XmodelApp::slotViewWire() {
  //if (toggle == true)
    view->setRenderType(WIRE, PNT);
}
void XmodelApp::slotViewStick() {
  //if (toggle == true)
    //view->setRenderType(STICK, BALL);
    view->setRenderType(STICK, PNT);
}

void XmodelApp::slotViewBall_Stick() {
   view->setRenderType(WIRE, BALL);
}

void  XmodelApp::slotHideAll() {
   view->setDisplay(HIDE_ALL);
}
void  XmodelApp::slotShowAll() {
   view->setDisplay(SHOW_ALL);
}

void XmodelApp::slotHideHydrogen() {
   view->setDisplay(HIDE_HYDROGEN);
}

void XmodelApp::slotShowHydrogen() {
   view->setDisplay(SHOW_HYDROGEN);
}

void XmodelApp::slotHideRibbon() {
   view->setDisplay(HIDE_RIBBON);
}

void XmodelApp::slotHideSurface() {
   std::list<molecule *>::iterator it = view->viewer->renList->begin();
   for (it; it != view->viewer->renList->end(); it++) {
      molecule *mol = *it;
      mol->surf->show = false;
   }
}

void XmodelApp::slotFlatRibbon() {
   view->defineRibbon(FLAT);
}

void XmodelApp::surfSlot() {
   string colorType = surf_dialog->color->currentText().latin1();
   float res = 1.0-float(surf_dialog->fineQuality->value())/100;
   float alpha = 1.0/(float(surf_dialog->fineTight->value())/100);
   float trans = float(surf_dialog->slider3->value())/100;
   view->viewer->molSurface(alpha, res, colorType, trans, 
                            surf_dialog->Red, surf_dialog->Green, 
                            surf_dialog->Blue, true);
}

void XmodelApp::surfDoneSlot() 
{ delete surf_dialog; }

void XmodelApp::slotAnalyticalSurface() {
   surf_dialog = new surfDialog2(this, "Surfaces", false);
   surf_dialog->setModal(false);
   surf_dialog->Red = 1.0;
   surf_dialog->Green = 1.0;
   surf_dialog->Blue = 1.0;

   connect(surf_dialog->Apply, SIGNAL(clicked()), this, SLOT(surfSlot()));
   connect(surf_dialog->Done, SIGNAL(clicked()), this, SLOT(surfDoneSlot()));

   surf_dialog->show();
}

void XmodelApp::slotCartoonRibbon(bool toggle) {
  if (toggle == true)
    view->defineRibbon(CARTOON);
}

void XmodelApp::slotHideMsg() {
   view->viewer->infoText.clear();
}

void XmodelApp::slotHideSideChains() {
  //if (toggle == true)
    view->setDisplay(HIDE_SIDE_CHAIN);
    //this->hideSideChains->setOn(false);
}
void XmodelApp::slotShowSideChains() {
  //if (toggle == true)
    view->setDisplay(SHOW_SIDE_CHAIN);
    //this->showSideChains->setOn(false);
}
void XmodelApp::slotHideBackBone() {
  //if (toggle == true)
    view->setDisplay(HIDE_BACKBONE);
    //this->hideBackbone->setOn(false);
}
void XmodelApp::slotShowBackBone() {
  //if (toggle == true)
    view->setDisplay(SHOW_BACKBONE);
    //showBackbone->setOn(false);
}

void XmodelApp::slotHydTreatment(bool toggle) {
  if (toggle == true) {
    view->addHydrogens("PARTIAL");
    this->hydAdd->setOn(false);
    
  }
}

void XmodelApp::slotHideSelected() {
  //if (toggle == true)
    view->setDisplay(HIDE_SELECTED);
    //this->hideSelected->setOn(false);
}


void XmodelApp::slotFFCharges() {
  view->charges("FF");
}

void XmodelApp::slotAM1Charges() {
  view->charges("AM1");
}

void XmodelApp::slotAM1BCCCharges() {
  view->charges("AM1-BCC");
}

void XmodelApp::slotAM1BCCCharges_fast() {
   view->charges("AM1-BCC-fast");
}

void XmodelApp::slotMNDO3Charges() {
  view->charges("MNDO3");
}

void XmodelApp::slotPM3Charges() {
  view->charges("PM3");
}


void XmodelApp::slotAddDist() {
  view->viewer->addNewDistance();
}

void XmodelApp::slotDelDist() {
  view->viewer->delDistance();
}

void XmodelApp::slotDelAllDist() {
  view->viewer->delAllDistances();
}

void XmodelApp::slotAddAng() {
  view->viewer->addNewAngle();
}

void XmodelApp::slotDelAng() {
  view->viewer->delAngle();
}

void XmodelApp::slotDelAllAng() {
  view->viewer->delAllAngles();
}

void XmodelApp::slotAddTorsion() {
  view->viewer->addNewTorsion();
}

void XmodelApp::slotDelTorsion() {
  view->viewer->delTorsion();
}

void XmodelApp::slotDelAllTorsion() {
  view->viewer->delAllTorsions();
}


void XmodelApp::slotFog(bool toggle) {
   if (toggle) view->viewer->enableFog(toggle);
   else emit view->viewer->enableFog(toggle);
}


void XmodelApp::slotMinimize() {
	
   minTabDialog *dialog = new minTabDialog(0, "Minimizer Dialog", true);
   dialog->show();
	
   //dialog->show(); //You didn't need show because of the exec()???
   QString minType;
   if ( dialog->exec() == minTabDialog::Accepted ) {
      if( dialog->mmGroup->isEnabled()) {
	       
         //This section gets the convergence criteria for the minimizer
         float rmsf = dialog->rmsefEdit->text().toFloat();
         float maxForce = dialog->maxForceEdit->text().toFloat();
         float eDiff = dialog->eDiffEdit->text().toFloat();
         int   maxIter = dialog->maxIterEdit->text().toInt();
	 
         QString chargeType = dialog->chargeCombo->currentText();     
         QString jobName = dialog->jobName->text();
         QString die = dialog->dieCombo->currentText();
         if (dialog->descentCombo->currentText() == "Steepest Descent") {
            minType = "SD";
         } else
         if (dialog->descentCombo->currentText() == "Conjugate Gradient") {
            minType = "CG";
         }
         
         float dieValue = -1; ///no dielectric
         if (die == "Constant") {
            dieValue = dialog->dieValue->text().toFloat();
         }
		 
         QString ffType = dialog->ffCombo->currentText();
         view->MMmin(jobName, minType, ffType, chargeType, die, dieValue, maxIter, rmsf, maxForce, eDiff);
         dialog->close();
      } else 
      if ( dialog->semiGroup->isEnabled() ) {
         QString minType = dialog->theoryCombo->currentText();
         QString jobName = dialog->jobName->text();
         view->MopacMin(jobName, minType);	       
               /*
	       
	       */
        
	/*
        if (minType == "SD" || minType == "CG") {
        
        } else {
           view->MopacMin("Mopac", minType);
       
        dialog->close();
        */
      }
   }
}

void XmodelApp::slotEnergy() {
   view->potEnergy();
}

void XmodelApp::slotScriptEditor() {
  view->ide->open();
}

//This is were the thread manager is updates
void XmodelApp::slotNewJob(dynoThread *job) {
   if (job) {
   QString name = job->getName();
   
   QAction *newJob = new QAction(name, name, 0, jobMenu, 0, jobMenu);
   
   newJob->setToggleAction(false);
   
   newJob->addTo(jobMenu);
   
   newJob->setName( job->getName() );
   
   connect(newJob, SIGNAL(activated()), this, SLOT(slotKillJob()));
   
   Jobs.push_back(job);
   jobId.push_back(job->getNum());
   jobActions.push_back(newJob);
   } else {
   }
}

void XmodelApp::slotKillJob(QString jobName) {
   view->jm.removeJob(jobName);
   std::vector<QAction *>::iterator it = jobActions.begin();
   for (it; it != jobActions.end(); it++) {
      QAction *ac = *it;
      if ( ac->text() == jobName ) {
         ac->removeFrom(jobMenu);
         jobActions.erase(it);
         break;
      }
   }   
}

void XmodelApp::slotKillJob() {
   const QObject *obj = sender();
   if (obj == NULL) return;
   
   slotKillJob(obj->name());
   
   
}

void XmodelApp::slotMC() {
   
   mcDialog *dialog = new mcDialog(0, "Monte Carlo Dialog", false);

   if ( dialog->exec() == mcDialog::Accepted ) {
      
      QString jobName = dialog->jobName->text();
      QString outFile = dialog->outFile->text();
      const int buttonId = dialog->buttonGroup1->selectedId();
      int maxIter = dialog->steps->text().toInt();
      float Temp = dialog->temp->text().toFloat();
      int outIter = dialog->output->text().toInt();
      
      float dieValue = -1;
      if (dialog->dieMethod->currentText() == "Constant") { 
         dieValue = dialog->dieValue->text().toFloat();
      }
      
      QString method;
      
      if (buttonId == 0) method = "MCFB";
      else if (buttonId == 1) method = "MC";    
      else if (buttonId == 2) method = "MCTR";
      
      view->MC(jobName, method, outFile, maxIter, Temp, "GAFF", "AM1-BCC-fast", outIter);
      
   }
}

void XmodelApp::slotMD() {
   
   mdDialog *dialog = new mdDialog(0, "Molecular Dynamics Dialog", true);
   view->MD("Molecular Dynamics", "MD", "outFile", 1000000, 0.005, "GAFF", "AM1-BCC", 10);
   /*
   if ( dialog->exec() == mdDialog::Accepted ) {
      view->MD("Molecular Dynamics", "MD", "outFile", 1000000, 0.005, "GAFF", "AM1-BCC");
   }
   */
}

void XmodelApp::atomColorSlot() {
   //cout <<"Yeah you are in atomColorSlot: " << endl;
   colorDialog *dialog = new colorDialog(this, "Color", false);
   dialog->show();
   connect(dialog, SIGNAL(colorChange(QString, QString, QString, QString, QString, QString)), 
           this, SLOT(atomColorChangeSlot(QString, QString, QString, QString, QString, QString))); 
}


void XmodelApp::atomColorChangeSlot(QString C, QString O, QString N, QString H, QString S, QString P) {
//   cout <<"XmodelApp:atomColorChangeSlot()" << endl;
   vector<int> AN;
   AN.push_back(6);
   AN.push_back(8);
   AN.push_back(7);
   AN.push_back(1);
   AN.push_back(16);
   AN.push_back(15);
   
   for (int j=0; j<AN.size(); j++) {
   QColor Color; 
   if (AN[j] == 6)
      Color.setNamedColor(C);
   if (AN[j] == 8)
      Color.setNamedColor(O);
   if (AN[j] == 7)
      Color.setNamedColor(N);
   if (AN[j] == 1)
      Color.setNamedColor(H);
   if (AN[j] == 16)
      Color.setNamedColor(S);
   if (AN[j] == 15)
      Color.setNamedColor(P);
   float color[3];
   color[0] = Color.red();
   color[1] = Color.green();
   color[2] = Color.blue();
 
   for (int i=0; i<3; i++)
      color[i] /= 255.0;
  
   std::list<molecule *>::iterator it = view->viewer->renList->begin();
   for (;it != view->viewer->renList->end(); it++) {
      molecule *mol = *it;
      for (int i=0; i<mol->atoms.size(); i++) {
         atom *atm = mol->atoms[i];
         if (atm->getAN() == AN[j]) {
            for (int i=0; i<3; i++) {
               atm->COLOR[i] = color[i];
               atm->tmpColor[i] = color[i];
            }
         } 
      }
   }
   }

   view->viewer->updateGL();
}

void XmodelApp::bgColorSlot() {
   int r = view->viewer->bgColor[0]*256;
   int g = view->viewer->bgColor[1]*256;
   int b = view->viewer->bgColor[2]*256;
   QColor cl(r, g, b);
   QColor newColor = QColorDialog::getColor(cl);
  
   view->viewer->bgColor[0] = newColor.red();
   view->viewer->bgColor[1] = newColor.green();
   view->viewer->bgColor[2] = newColor.blue();
   
   for (int i=0; i<3; i++) {
     view->viewer->bgColor[i] /= 256.0;
   }
   
}

void XmodelApp::molColorSelectSlot() {
   int r = 0;
   int g = 0;
   int b = 0;
   QColor cl(r, g, b);
   QColor newColor = QColorDialog::getColor(cl);
  
   //view->viewer->bgColor[0] = newColor.red();
   //view->viewer->bgColor[1] = newColor.green();
   //view->viewer->bgColor[2] = newColor.blue();
   
   std::list<molecule *>::iterator molIterator = view->viewer->renList->begin();
   int selCount = 0;
   for (molIterator; molIterator != view->viewer->renList->end(); molIterator++) {
       molecule *mol=*molIterator;
      for (int i=0; i<mol->atoms.size(); i++) {
         atom *tmp = mol->atoms[i];
         if (tmp->isSelected()) {
            selCount++;
            tmp->setSelected(false);
            tmp->COLOR[0] = newColor.red(); tmp->COLOR[0] /= 256.0;
            tmp->COLOR[1] = newColor.green(); tmp->COLOR[1] /= 256.0;
            tmp->COLOR[2] = newColor.blue(); tmp->COLOR[2] /= 256.0;
            for (int j=0; j<3; j++) tmp->tmpColor[j] = tmp->COLOR[j];
            //tmp->setSelected(true);
         }
      }
   }
   if(selCount == 0) {
      molIterator = view->viewer->renList->begin();
      for (molIterator; molIterator != view->viewer->renList->end(); molIterator++) {
       molecule *mol=*molIterator;
      for (int i=0; i<mol->atoms.size(); i++) {
         atom *tmp = mol->atoms[i];
         tmp->setSelected(false);
         tmp->COLOR[0] = newColor.red(); tmp->COLOR[0] /= 256.0;
         tmp->COLOR[1] = newColor.green(); tmp->COLOR[1] /= 256.0;
         tmp->COLOR[2] = newColor.blue(); tmp->COLOR[2] /= 256.0;
         for (int j=0; j<3; j++) tmp->tmpColor[j] = tmp->COLOR[j];
      }
   }
   
   }
  //for (int i=0; i<3; i++) {
     
  //   view->viewer->bgColor[i] /= 256.0;
  // }
}

void XmodelApp::molColorElementSlot() {
   std::list<molecule *>::iterator molIterator = view->viewer->renList->begin();
   for (molIterator; molIterator != view->viewer->renList->end(); molIterator++) {
       molecule *mol=*molIterator; 
       for (int i=0; i<mol->atoms.size(); i++) {
          atom *tmp = mol->atoms[i];
          tmp->defaultColor();
       }         
   }
}

void XmodelApp::lightSlot() {
   dialog = new Lighting(this, "Lighting");
   dialog->setModal(false);
   dialog->show();
   
   dialog->setGenLightProp(
   	view->viewer->light_position,
	view->viewer->light_ambient,
	view->viewer->light_specular,
	view->viewer->light_diffuse
   );
   dialog->setRibLightProp(
   	view->viewer->light_ribbon_position,
	view->viewer->light_ribbon_ambient,
	view->viewer->light_ribbon_specular,
	view->viewer->light_ribbon_diffuse
   );
   connect(dialog, SIGNAL(apply()), this, SLOT(lightSlot2()));
   if ( dialog->exec() == Lighting::Accepted ) {
   }
}

void XmodelApp::lightSlot2() {
   //GENERAL
   float ambR = dialog->genLightAmbR->text().toFloat();
   float ambG = dialog->genLightAmbG->text().toFloat();
   float ambB = dialog->genLightAmbB->text().toFloat();
   
   float posX = dialog->genLightPosX->text().toFloat();
   float posY = dialog->genLightPosY->text().toFloat();
   float posZ = dialog->genLightPosZ->text().toFloat();
   
   float specR = dialog->genLightSpecR->text().toFloat();
   float specG = dialog->genLightSpecG->text().toFloat();
   float specB = dialog->genLightSpecB->text().toFloat();
   
   float DifR = dialog->genLightDifR->text().toFloat();
   float DifG = dialog->genLightDifG->text().toFloat();
   float DifB = dialog->genLightDifB->text().toFloat();
   
   //RIBBON
   float ambR_rib = dialog->genLightAmbR_3->text().toFloat();
   float ambG_rib = dialog->genLightAmbG_3->text().toFloat();
   float ambB_rib = dialog->genLightAmbB_3->text().toFloat();
   
   float posX_rib = dialog->genLightPosX_3->text().toFloat();
   float posY_rib = dialog->genLightPosY_3->text().toFloat();
   float posZ_rib = dialog->genLightPosZ_3->text().toFloat();
   
   float specR_rib = dialog->genLightSpecR_3->text().toFloat();
   float specG_rib = dialog->genLightSpecG_3->text().toFloat();
   float specB_rib = dialog->genLightSpecB_3->text().toFloat();
   
   float DifR_rib = dialog->genLightDifR_3->text().toFloat();
   float DifG_rib = dialog->genLightDifG_3->text().toFloat();
   float DifB_rib = dialog->genLightDifB_3->text().toFloat();
   
   view->viewer->light_position[0] = posX;
   view->viewer->light_position[1] = posY;
   view->viewer->light_position[2] = posZ;
   
   view->viewer->light_ambient[0] = (1.0+ambR)/100.0;
   view->viewer->light_ambient[1] = (1.0+ambG)/100.0;
   view->viewer->light_ambient[2] = (1.0+ambB)/100.0;
   
   view->viewer->light_specular[0] = (1.0+specR)/100.0;
   view->viewer->light_specular[1] = (1.0+specG)/100.0;
   view->viewer->light_specular[2] = (1.0+specB)/100.0;
   
   view->viewer->light_diffuse[0] = (1.0+DifR)/100.0;
   view->viewer->light_diffuse[1] = (1.0+DifG)/100.0;
   view->viewer->light_diffuse[2] = (1.0+DifB)/100.0;
   
   
   //RIBBON STUFF
   view->viewer->light_ribbon_position[0] = posX_rib;
   view->viewer->light_ribbon_position[1] = posY_rib;
   view->viewer->light_ribbon_position[2] = posZ_rib;
   
   view->viewer->light_ribbon_ambient[0] = (1.0+ambR_rib)/100.0;
   view->viewer->light_ribbon_ambient[1] = (1.0+ambG_rib)/100.0;
   view->viewer->light_ribbon_ambient[2] = (1.0+ambB_rib)/100.0;
   
   view->viewer->light_ribbon_specular[0] = (1.0+specR_rib)/100.0;
   view->viewer->light_ribbon_specular[1] = (1.0+specG_rib)/100.0;
   view->viewer->light_ribbon_specular[2] = (1.0+specB_rib)/100.0;
   
   view->viewer->light_ribbon_diffuse[0] = (1.0+DifR_rib)/100.0;
   view->viewer->light_ribbon_diffuse[1] = (1.0+DifG_rib)/100.0;
   view->viewer->light_ribbon_diffuse[2] = (1.0+DifB_rib)/100.0;
   
   
   view->viewer->initializeGL();
   
   //You call it twice so that it definetly updates all the way.
   view->viewer->updateGL();
   view->viewer->updateGL();
}


void XmodelApp::runScript(QString fileName) {
   if (this->view->project != NULL ) {
      QSScript *scr = view->project->createScript ( "Script1", fileName );
      QStringList functions = view->project->interpreter()->functions();
   }
}

void XmodelApp::slotFreeAtoms() {
   view->viewer->freeAtoms();
}

void XmodelApp::slotFixAtoms() {
   view->viewer->fixAtoms();
}


void XmodelApp::sysSearchSlot() {
   cfDialog = new confDialog(0, "name", true, 0);
   int count = 1;
   cfDialog->setMolList(view->viewer->renList);
   connect(cfDialog->buttonOk, SIGNAL(clicked()), this, SLOT(sysSearchStartSlot()));
   cfDialog->show();
}
void XmodelApp::confSwarmSlot() {
   confPartDialog *dialog = new confPartDialog(0, "name", true, 0);
  
   //dialog->setMolList(view->viewer->renList);
   float id, c1, c2;
   int popSize, gen;
   if ( dialog->exec() == Lighting::Accepted ) {
      QString fileName = dialog->saveAs->text();   
      id = dialog->id->text().toFloat();
      c1 = dialog->c1->text().toFloat();
      c2 = dialog->c2->text().toFloat();
      popSize = dialog->popSize->text().toInt();
      gen = dialog->gen->text().toInt();
   }
   
   if (view->viewer->renList->size() != 1) {
      QMessageBox::critical(0, "Error", "You must have exactly one molecule in the viewer to run psoSearch");
      return;
   }
   
   csoThread *ct = new csoThread(view, "psoSearch");
   std::list<molecule *>::iterator it = view->viewer->renList->begin();
   ct->setMolecule(*it);
   ct->init(id, c1, c2, popSize, gen);
   ct->start();
   
   
   //connect(cfDialog->buttonOk, SIGNAL(clicked()), this, SLOT(sysSearchStartSlot()));
   //dialog->show();
}


void XmodelApp::sysSearchStartSlot() {
   QString jobName = cfDialog->jobName->text();
   QString outFile = cfDialog->output->text();
   float cutoff = -1;
   int clusters = -1;
   float minE = cfDialog->minE;
   float rmse = cfDialog->rmse;
   float maxForce = cfDialog->maxForce;
   int maxIter = cfDialog->maxIter;
   if (cfDialog->cutCheck->isChecked() ) cutoff = cfDialog->cutoff->text().toFloat();
   if (cfDialog->clusterCheck->isChecked() ) clusters = cfDialog->clusters->text().toInt();
   
   bool Min = false;
   if (cfDialog->minCheck->isChecked() ) Min = true;
   vector<bond *> rotBonds;
   QListViewItemIterator it(cfDialog->infoBox);
   vector<QListViewItem *> Items;
   while ( it.current() ) {
      QListViewItem *item = it.current();
      QString molName = item->text(0);
      int fromNum = item->text(1).section( ':', -1 ).toInt();
      int toNum = item->text(2).section( ':', -1 ).toInt();
      int inc = item->text(3).toInt();
      
      std::list<molecule *>::iterator mIter = view->viewer->renList->begin();
      for (mIter; mIter != view->viewer->renList->end(); mIter++) {
         molecule *mol = *mIter;
         bool found = false;
         if (mol->getName() == molName) {
            for (int i=0; i<mol->bonds.size(); i++) {
               int fInt = mol->bonds[i]->fromAtom()->getNum();
               int tInt = mol->bonds[i]->toAtom()->getNum();
               if (fInt == fromNum && tInt == toNum) {
                  rotBonds.push_back(mol->bonds[i]);
                  mol->bonds[i]->defInc = inc;
                  found = true;
                  break;
               }
               //MUST REMOVE THIS LINE
            }
            if (found) break;
         }
      }
      it++;
   }
   
   if (view->viewer->renList->size() == 0)
   	return;

   confThread *ct = new confThread(view, jobName);
   view->jm.registerJob(ct);
   view->parent->slotNewJob(ct);
   view->viewer->startAutoUpdate(-1);
   ct->setUp(view->viewer->renList, rotBonds, outFile);
   ct->eSetup(Min, cutoff, clusters, rmse, minE, maxForce, maxIter);
   ct->start();
}

void XmodelApp::slotLabel() {
  view->viewer->setLabels();
}




void XmodelApp::buildMenuSlot() {
   view->viewer->initBuildMode();
}

void XmodelApp::tableSlot() {
   view->initTable();
}

void XmodelApp::gaffFpSlot2() {
   fpDialog2 *dialog = new fpDialog2(0, 0, true);
   dialog->setMolViewSlot(view->viewer);
   dialog->show();
   connect(dialog, SIGNAL(runDone(QString &)), view, SLOT(initTable(QString &)));
}


void XmodelApp::slotFlexAlign() {
   FlexAlignDialog *dialog = new FlexAlignDialog(0, 0, false);
   dialog->minE = "0.01";
   dialog->maxForce = "0.001";
   dialog->rmse = "0.05";
   dialog->annealPercent = "5";
   dialog->dynIter = "500";
   dialog->rmseCoords = "1.0";
   dialog->show();  
   dialog->setFinishEnabled(dialog->lastPage, true); 
   if ( dialog->exec() ) {
      flexAlignThread *fat = new flexAlignThread(view, "DynAlign");
      fat->setName(dialog->jobName->text().latin1());
      //list<molecule *>::iterator rl = view->viewer->renList->begin();
      map<string, string> Params;
      Params["outFile"] = dialog->outFile->text().latin1();
      Params["baseName"] = dialog->baseName->text().latin1();
      Params["tempFile"] = dialog->tempFile->text().latin1();
      Params["toAlignFile"] = dialog->toAlignFile->text().latin1();

      Params["tempView"] = "0";
      if (dialog->tempView->isChecked())
         Params["tempView"] = "1";

      Params["toAlignView"] = "0";
      if (dialog->toAlignView->isChecked())
         Params["toAlignView"] = "1";

      Params["singleFile"] = "0";
      if (dialog->singleFile->isChecked())
         Params["singleFile"] = "1";

      Params["multiFile"] = "0";
      if (dialog->multiFile->isChecked())
         Params["multiFile"] = "1";

      //Params["listView"] = "0";
      //if (dialog->listView->isChecked())
      //   Params["listView"] = "1";

      Params["tempFlex"] = "0";
      if (dialog->tempFlex->isChecked())
         Params["tempFlex"] = "1";
      
      Params["chgWeight"] = dialog->cw->text().latin1();
      Params["volWeight"] = dialog->vw->text().latin1();
      Params["aroWeight"] = dialog->aw->text().latin1(); 
      Params["chargeType"] = dialog->chargeType->currentText().latin1();
      Params["maxMD"] = dialog->maxMD->text().latin1();
      Params["maxMin"] = dialog->MaxMin->text().latin1(); 
      Params["dielec"] = dialog->dielec->text().latin1();
      
      Params["background"] = "0";
      if (dialog->background->isChecked())
         Params["background"] = "1";
      Params["poses"] = dialog->poses->text().latin1();
      Params["Iter"] = dialog->Iterations->text().latin1();
      Params["tanTerm"] = dialog->tanTerm->text().latin1();
      Params["poseRMSE"] = dialog->poseRMSE->text().latin1(); 
      Params["dynIter"] = dialog->dynIter.latin1();
      Params["annealPercent"] = dialog->annealPercent.latin1();
      Params["rmse"] = dialog->rmse.latin1();
      Params["maxForce"] = dialog->maxForce.latin1();
      Params["minE"] = dialog->minE.latin1();
      
      Params["rmseCoords"] = dialog->rmseCoords.latin1();   
   
      fat->setUp(Params);
      //Template is always first molecule    
      //rl++;
      //You should probably convert this to a list or something
      view->jm.registerJob(fat);
     
      view->parent->slotNewJob(fat);
      view->viewer->startAutoUpdate(-1);
      fat->start();
   }
}

void XmodelApp::slotTestPy() {
   cout <<"You are in slotTextPy"<<endl;
   static int count = 0;
   if (count == 1) {
      cout <<"Creating new molViewScript from Dynamol" << endl;
      cout <<"Now it was deleted"<<endl;
      molViewScript::VIEWER = view->viewer;
   }
   count=1;
   molViewScript::VIEWER = view->viewer;
//   boost::shared_ptr< Dynapy > runpy;;
   DynaPy *runpy = new DynaPy;
   runpy->setFileName("test.py");
   //runpy->run();
   runpy->start();
   //delete runpy; 
//   DynaPy("test.py");

}

