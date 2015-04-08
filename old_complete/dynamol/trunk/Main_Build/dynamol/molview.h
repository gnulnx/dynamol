/***************************************************************************
                          molview.h  -  description
                             -------------------
    begin                : Tue Dec 30 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#ifndef MOLVIEW_H
#define MOLVIEW_H

#include <qpainter.h>
#include <qpixmap.h>
#include <qcursor.h>
#include <qtimer.h>
#include <qstring.h>
#include "viewerwidget.h"
#include "pickengine.h"

#include <iomanip>
#include <list>
using std::list;
using namespace std;

#include "molecule.h"
#include "protein.h"
#include "utility.h"
#include "ribbon.h"

#include "atomtyper.h"

#include <qpixmap.h>

/**
  *@author John Furr
  */

class QTimer;
  
enum sphereType {solid, wire};
struct sphere {
   float center[3];
   float radius;
   float color[3];
   sphereType type;
};

struct triangle {
  vector<float> v1, n1;
  vector<float> v2, n2;
  vector<float> v3, n3;
  float trans;
  float c1[3];
  float c2[3]; 
  float c3[3];
  vector<double> cp;
};

class molListView;
class labelDialog;
class builderDialog;
class builder;
class XmodelView;

class molView : public viewerWidget  {
  friend class pickEngine;
  friend class dynamics;
  friend class energy;

   Q_OBJECT
public: 
   molView(QWidget *parent=0, char *name=0, std::list<molecule *> *renList=NULL);
   ~molView();
   
   void setListView(molListView *listView);
   void setModelView(XmodelView *modelView);
   molListView *listView;
   XmodelView *modelView;
   molecule *mol;
   atomTyper *atmTyper;
   builder *molEdit;
   double xCenter, yCenter, zCenter;
   builderDialog *bDialog;
   QPixmap origBack;
   bool molEditMode;
   
   /** These two routines are helping me build surfaces */
   vector<sphere *> SPHERES;
   void addSphere(float x, float y, float z, float radius);
   void addSphere(float x, float y, float z, float radius, sphereType type, float r, float g, float b);
   void drawSpheres();
   
   //vector<triangle *> TRIS;
   
   /** \brief Draw A Molecular Surface
   *
   *   The surface should be defined by a surface struct in class molecule
   */
   void drawSurface(molecule *mol);
  
  /** called when the molecule should be rendered as a CPK model
  */
  void drawStick(molecule *mol);
  void drawStickBonds(vector<bond *> &Bonds, float radius);
  void drawCyl(molecule *mol, BONDRENDER bd);
  
  /** Update from dynamics */
  void energyUpdate();


  std::list<molecule *> *getRenList();
  
  /** Method comes for the QGLWidget hierarchy && is used to perform all of the
  openGL initialization stuff.
  */
  void initializeGL();

  /**  Method comes from the QGLWidget hierarchy && is called wherever the scene needs
      to be painted
  */
  void paintGL();

  /** Method comes from the QGLWidget hierarchy && is called whenever the window is resized
  */
  void resizeGL(int w, int h);

  /** This function is used to update the graphis...basically it calls updateGL() */
  void update();
  /** Sets the render type for the molecule.  This sugnal is propagated all the way from chemtest.cpp
  */
  void  setRenderType(BONDRENDER bondType, ATOMRENDER atomType);

  /** Controls weather atoms are hidden || displayed */
  void  setDisplay(DISPLAY_TYPE dispType);

  /**Performs the calulations To define the cnt points for a ribbon model */
  void  defineRibbon(RIBBON_TYPE type);
  
  /** This function will call the surface program to build a surface...***NEW*/
  void molSurface(float alpha, float res, string &colorType, 
                  float transparency, float r=1.0, float g=1.0, float b=1.0, bool dir=true);

  /** Sets the atom Labels */
  void setLabels();
    
  /** This returns the currently rendered molecules */
  void getCurrentMolList(std::list<molecule *> &molList);

  /** This function adds a new distance */
  void addNewDistance();

  /** This function deletes a distance */
  void delDistance();

  /** This cuntion deletes all Distances */
  void delAllDistances();

  /** This function adds a new angle to the render scene */
  void  addNewAngle();

  /** This function deletes an angle from the scene */
  void delAngle();

  /** This function deletes al angles in the scene */
  void delAllAngles();

  /** This function adds a new angle to the render scene */
  void  addNewTorsion();

  /** This function deletes an angle from the scene */
  void delTorsion();

  /** This function deletes al angles in the scene */
  void delAllTorsions();
  
  /** This list contains the current view */  
  std::list<molecule *> *renList;
  
  /** Enables && disables the fog */
  void enableFog(bool toggle);
  
  /** This function is used to get all the selectedAtoms 
      if the all condition is true then the function will return all atoms (if non are selected) currently in the viewing area wether || not they are hidden.  If it is false it will return vector of size zero.
  */
  void getSelectedAtoms(vector<atom *> &ATOMS, bool all);
  
  /** This function fix's the selected atoms */
  void fixAtoms();
  
  /** This function free's the selected atoms which are fixed*/
  void freeAtoms();
 
  /** \brief Turn off rendering
  */
  void renderOff();  

  /** \breif Turn on rendering
  */
  void renderOn();
protected:
  bool render_on;
  //renderEngine *engine;

  //enum CPK_RADIUS {DEFAULT, ATOM_TYPE};
  CPK_RADIUS radType;
  std::list<atom *> atomIter;
  atom *at;
  bond *bd;
  GLUquadric *gluObj;
  GLUnurbsObj *pNurb;       
  std::list<molecule *> molList;
  int ribbonDisplay;


  float           distance(vector<double>);
  float           distance(vector<double>, vector<double>);
  float           distance(vector<float>,     vector<float>);
  vector<double>  crossProduct(vector<double> &vec1, vector<double> &vec2);
  vector<double>  normalize(vector<double> &vec1);
  void            drawDoubleBond(bond *bd, vector<float> c1, vector<float> c2);
  void            dDB(bond *bd, vector<float> c1, vector<float> c2);
  void            drawSingleBond(bond *bd, vector<float> c1, vector<float> c2);
  void            drawTripleBond(bond *bd, vector<float> c1, vector<float> c2);
 

  float           length(vector<double> &p1, vector<double> &p2);
  float           length(float *p1, float *p2);


  void            setCenter(vector<float> &center);
  void            setCenter(std::list<molecule *> *renList);

  // ################## START FLOAT CONVERSION SECTION ###############
  float           length(vector<float> &p1, vector<float> &p2);
  // #################### END SECTION ###########################
 

private:
   /** GLint names for various dispaly lists
   */
   GLint mainList;
   GLint ballSphere, cpkSphere, singleStick, doubleStick, singleWire, doubleWire, aromaticWire, aromaticStick;
   GLuint *selectBuf;

   GLint allRen;
   labelDialog *lDialog;

   GLenum renderMode;
   QPixmap *saveState;  //This is used to save the openGL state during rubberBand selection
  
   float radius;
   int boxBeginX, boxBeginY, boxEndX, boxEndY;

   /** Draws sphere, cylinder, singleBond, doubleBond, etc...
   */
   void renderInit();
   void renderAtom(float radius, atom *AT, ATOMRENDER at);

   void drawWireBond(bond *BD);
   void drawStickBond(bond *BD, float radius_1, float radius_2);

   void drawRibbon(chain *mol);
   void getRibbonCtrlPoints(molecule *mol);

   /** This function draws all of the intra && inter molecular distances */
   void drawDistances(molecule *mol);
   /** This function draw all the intra && inter molecular angles */
   void drawAngles(molecule *mol);
   /** This function draw all the intra && inter molecular torsions */
   void drawTorsions(molecule *mol);

   //void processHits(GLint hits, GLuint buffer[], button_state shiftState, button_state altState);
   //void processHits2(GLint hits, GLuint buffer[], button_state shiftState, button_state altState);
  
   //void distPicks(GLint hits, GLuint buffer[]);
   //void angPicks(GLint hits, GLuint buffer[]);

   //atom *getHit(GLint hits, GLuint buffer[]);
   //void  getHitObjectNumbers(vector<int> &nums, GLint hits, GLuint buffer[]);

   bool doubleClick;

   std::list<molecule *>::iterator molIterator;
   std::list<molecule *> listOfMols; //Will want to delete this one once you get the rest of it all figured out.
  

   //Both of these next two data types should probably be removed at some point in time
   vector<guidePoints *> allGuidePoints;
   vector<ctrlPoint> cp;

   vector<ribbon *> Ribbons;
    
public slots:

  /** This function takes a list of molecules to render as an argument  S
  */
  void render(std::list<molecule *> renList);
  void  selectObjects(int &, int &, float &, float &, button_state, button_state);
  void  selectBox(int &, int &, float &, float &, button_state);
  void  sweepPickSelect(int &, int &, float &, float &, button_state, button_state);
  void  selectFullMol(int &x, int &y, float &xFloat, float &yFloat, button_state state);
  void setMolList(std::list<molecule *> *renList);
  
   /** You are hoping to get thread safe access here */
   void renderMols(vector<molecule *> &molList);

  void  keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent *event);
  
  void  buildModeSelect(int &, int &, float &, float &, button_state, button_state);
  
  int  maxTimerIteration;
  void timerDone();
  void startAutoUpdate(int maxCycle);
  void stopAutoUpdate();
  void endAutoUpdate(dynoThread *);

  void slotLabelDone();
  void slotApplyLables();

  void buildMenu(double &xPos, double &yPos, double &zPos, int &, int &, float &, float &, button_state, button_state);

  void initBuildMode();
  void buildDone();
  
  /** This is used to set the current infoeText display */
  void setInfoText(vector<QString> &data);
  void setInfoText(vector<string > &data);
  /** This function simply calls updateGL() */
  void updateInfoText();
  /** This is used to clear the current infoText...calls updateInfotext */
  void clearInfoText();

   float currMat[16];
   float origMat[16]; 
   GLdouble mvMatrix[16];
   GLint vPort[4];
   GLdouble projMatrix[16];
signals:
  void  selectionChanged();
  void  clearSelection();
  void  atomAdded(vector<atom *> &newAtoms, molecule *parent);
  void  deleteAtoms(vector<atom *> &Atoms);
  void  sendWorldCoords(double x, double y, double z);
  //void renderList(list<molecule *> &);

private:
  bool autoTime;
  float mat_shininess[1];
  float mat_ribbon_shininess[2];

  float fps;

  vector<QString> Labels;
  //Use to get information about the coordinates
  vector<atom *>   labelAtoms;
  //This list will hold the currently selected atoms
  vector<atom *> currentSelection;

   /** Various selection modes.  You will need to disable sweep pick select during these times */
   bool distMode, angMode, torsionMode;
   bool delDistMode, delAngMode, delTorsionMode;
   int distSelCounter, angSelCounter, torsionSelCounter;

  vector< vector<atom *> > interMolDist;
  vector< vector<atom *> > interMolAng;
  vector< vector<atom *> > interMolTor;
  void delInterMolDist(atom *atm1, atom *atm2);
  void delInterMolAng(atom *atm1, atom *atm2, atom *atm3);
  void delInterMolTorsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4);
  /** These two atoms are used when measuring bonds */
  atom *atm1, *atm2, *atm3, *atm4;

  /** This controls all of the picking && pick related function for the class */
  pickEngine *picker;

   
   QTimer *timer;
   
   
   
   float minZ, maxZ;
   
public:
   vector<float> bgColor;
   
   /** This is used to set the display text in the molView window */
   vector<string>  infoText;
   vector<float> light_ambient;
   vector<float> light_specular;
   vector<float> light_diffuse;
   vector<float> light_position;
   
   vector<float> light_ribbon_ambient;
   vector<float> light_ribbon_specular;
   vector<float> light_ribbon_diffuse;
   vector<float> light_ribbon_position;
   
   
   float cylSlices, cylStacks, sphSlices, sphStacks;
   //QPainter *pTest;//( this );
  //pTest.setPen( Qt::blue );
  vector< vector<double> > surfacePoints;
  vector< vector<float> > pointColors;

  vector<float> surfVertex;
  vector<float> surfColor;
  vector<float> surfNormal;
  bool surfMode;
};

#endif





































