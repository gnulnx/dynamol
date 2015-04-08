/**************************************************************************
                          molview.cpp  -  description
                             -------------------
    begin                : Tue Dec 30 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol
 ***************************************************************************/

#include "molview.h"
#include "linAlg.h"
#include "quat.h"
#include <qpalette.h>
#include <qlabel.h>
#include <qtimer.h>

#include "mollistview.h"
#include <qmessagebox.h>
#include "labeldialog.h"
#include "qcheckbox.h"
#include <qpushbutton.h>
#include "qmutex.h"
#include "qlineedit.h"

#include "builder.h"
#include "buildDialog.h"
#include "xmodelview.h"

#include "chain.h"
#include "atom.h"
#include "bond.h"

#include "buildsurface.h"

#include <fstream>
using namespace std;

#include "surfstruct.h"
//BOOST Includes
#include <boost/shared_ptr.hpp>

molView::molView(QWidget *parent, char *name, list<molecule *> *renList)
: viewerWidget(parent)
{
  render_on = true;
  surfMode = false;
 
  molEditMode = false;
  QFont times( "Times", 12, QFont::Bold);
  setFont(times);
    
  picker = new pickEngine(this);
  //Energy = new energy(this);
  atmTyper = new atomTyper();
  
  timer = new QTimer( this );
  connect( timer, SIGNAL(timeout()), this, SLOT(timerDone()));
  
  distMode = angMode = torsionMode = false;
  delDistMode = delAngMode = delTorsionMode = false;
  distSelCounter = angSelCounter = torsionSelCounter = 0;
  atm1 = atm2 = atm3 = NULL;
  allRen = 0;
  
  //Initialize the background color to black
  bgColor.resize(3);
  for (int i=0; i<bgColor.size(); i++) bgColor[i] = 0.0;
  
  //This sets the molView render list to the same spot as the molDB::renList
  /* You are thinking that molDB will hold all the listViews && then you will
  pass the appropriate lists to both molListVire && molView;
  */
  this->renList = renList;

  gluObj = gluNewQuadric();
  /** NURB CRAP **/
  pNurb = gluNewNurbsRenderer();
  gluNurbsProperty(pNurb, GLU_SAMPLING_TOLERANCE, 10.0);
  gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, GLU_FILL);
  // #### END NURB CRAP//

  connect(this, SIGNAL(leftButtonPress(int &, int &, float &, float &, button_state, button_state )),this, SLOT(selectObjects(int &, int &, float &, float &, button_state, button_state )));
  connect(this, SIGNAL(leftButtonMove(int &, int &, float &, float &, button_state)),this, SLOT(selectBox(int &, int &, float &, float &, button_state)));
  connect(this, SIGNAL(leftButtonRelease(int &, int &, float &, float &, button_state, button_state)), this, SLOT(sweepPickSelect(int &, int &, float &, float &, button_state, button_state)));
  connect(this, SIGNAL(leftButtonDoubleClick(int &, int &, float &, float &, button_state)), this, SLOT(selectFullMol(int &, int &, float &, float &, button_state)));
  connect(this, SIGNAL(midButtonRelease(int &, int &, float &, float &, button_state)), this, SLOT(selectFullMol(int &, int &, float &, float &, button_state)));
		
  boxBeginX = boxBeginY = boxEndX = boxEndY = 0;

  saveState = new QPixmap();
  
  //Setting initial ambient settings
  light_ambient.resize(4);
  light_ambient[0] = 0.25; 
  light_ambient[1] = 0.25; 
  light_ambient[2] = 0.25; 
  light_ambient[3] = 1.0;
  
  light_specular.resize(4);
  light_specular[0] = 0.78;
  light_specular[1] = 0.78;
  light_specular[2] = 0.78;
  light_specular[3] = 1.0;
  
  light_diffuse.resize(4);
  light_diffuse[0] = 0.65;
  light_diffuse[1] = 0.65;
  light_diffuse[2] = 0.65;
  light_diffuse[3] = 1.0;
  
  light_position.resize(4);
  light_position[0] = 0.0;
  light_position[1] = 100.0;
  light_position[2] = 1000.5;
  light_position[3] = 1.0;
  
  //RIB INIT SETTINGS
  light_ribbon_ambient.resize(4);
  light_ribbon_ambient[0] = 0.25; 
  light_ribbon_ambient[1] = 0.25; 
  light_ribbon_ambient[2] = 0.25; 
  light_ribbon_ambient[3] = 1.0;
  
  light_ribbon_specular.resize(4);
  light_ribbon_specular[0] = 0.99;
  light_ribbon_specular[1] = 0.99;
  light_ribbon_specular[2] = 0.99;
  light_ribbon_specular[3] = 1.0;
  
  light_ribbon_diffuse.resize(4);
  light_ribbon_diffuse[0] = 0.45;
  light_ribbon_diffuse[1] = 0.45;
  light_ribbon_diffuse[2] = 0.45;
  light_ribbon_diffuse[3] = 1.0;
  
  light_ribbon_position.resize(4);
  light_ribbon_position[0] = 10.0;
  light_ribbon_position[1] = 10.0;
  light_ribbon_position[2] = 10.0;
  light_ribbon_position[3] = 1.0;
  
  cylSlices = 7;
  cylStacks = 1;
  sphSlices = 7;
  sphStacks = 2;
  
}


molView::~molView(){
}

void molView::setListView(molListView *listView) {
   this->listView = listView;
}
void molView::setModelView(XmodelView *modelView) {
   this->modelView = modelView;
}
list<molecule *> *molView::getRenList() {return this->renList;};

void molView::initializeGL() {
  float mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  float mat_diffuse[] = {0.750, 0.750, 0.750, 1.0};
  //float light_ambient[] = {0.05, 0.05, 0.05, 1.0};
  //float light_ribbon_ambient[] = {0.15, 0.15, 0.15, 1.0};
  //float light_position[] = {0.0, 0.0, 1000.5, 0.0};
  
  float light0_position[] = {0.0, 0.0, -1000.5, 0.0};
  float light1_position[] = {0.0, 0.0, -1000.5, 0.0};
  float light2_position[] = {0.0, 0.0, 0.0, 0.0};

  mat_shininess[0] = 50;
  mat_ribbon_shininess[0] = 50;
  
  gluQuadricDrawStyle(quadObj, GLU_FILL);
  gluQuadricOrientation(quadObj, GLU_OUTSIDE);
  gluQuadricNormals(quadObj, GLU_SMOOTH);
  
  gluQuadricDrawStyle(wireObj, GLU_LINE);
  gluQuadricOrientation(wireObj, GLU_OUTSIDE);
  gluQuadricNormals(wireObj, GLU_SMOOTH);

  // Enable Vertex Array's 
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
    

  glEnable(GL_NORMALIZE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_COLOR_MATERIAL);

  glLightfv(GL_LIGHT1, GL_AMBIENT, &light_ambient[0]);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, &light_diffuse[0]);
  glLightfv(GL_LIGHT1, GL_POSITION, &light_position[0]);
  glLightfv(GL_LIGHT1, GL_SPECULAR, &light_specular[0]);
  //glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

  //NEW LIGHT SUTFF
  //glLightfv(GL_LIGHT2, GL_AMBIENT, light_ribbon_ambient);
  glLightfv(GL_LIGHT2, GL_AMBIENT, &light_ribbon_ambient[0]);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, &light_ribbon_diffuse[0]);
  glLightfv(GL_LIGHT2, GL_SPECULAR, &light_ribbon_specular[0]);
  glLightfv(GL_LIGHT2, GL_POSITION, &light_ribbon_position[0]);

  glLightfv(GL_LIGHT3, GL_AMBIENT, &light_ambient[0]);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, &light_diffuse[0]);
  glLightfv(GL_LIGHT3, GL_POSITION, light1_position);
  //END NEW LIGHT STUFF
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

  
  static int count = 0;
if (count == 0) {
  
   //START AINTIALIASING STUFF
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  //glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//  glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glLineWidth(2.5);
  //glEnable(GL_MULTISAMPLE_ARB);

  GLdouble w, h;
  xTrans = yTrans = zTrans = 0;
  //xTrans = static_cast<float>(this->width())/2.0;
  //yTrans = static_cast<float>(this->height())/2.0;
  //zTrans = 100;
  w = this->width();
  h = this->height();

 
  
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(60.0, w/h, 5.0, 100.0);
  
  //START OF FOG STUFF
  //glFogi(GL_FOG_MODE, GL_LINEAR);
  //glFogi(GL_FOG_INDEX, 1);
  //glFogf(GL_FOG_DENSITY, 0.05);
  //glFogf(GL_FOG_START, -10.0);
  //glFogf(GL_FOG_END, 100.0);
  //glHint(GL_FOG_HINT, GL_NICEST);
  //glEnable(GL_FOG);
  
  trackball(currentQuat, 0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
   renderInit();
  zTrans += 25;
  }
  count++;

 
};


void molView::renderInit() {
  mainList = glGenLists(1);

  //Setup Sphere display list for CPK model
  ballSphere = glGenLists(1);
  glNewList(ballSphere, GL_COMPILE);
  gluSphere(quadObj, 1, 12, 12);
  glEndList();

  //Setup Sphere display list for Stick model
  cpkSphere = glGenLists(1);
  glNewList(cpkSphere, GL_COMPILE);
  gluSphere(quadObj, 1, 20, 20);
  glEndList();

  //Setup singleStick displayList
  singleStick = glGenLists(1);
  glNewList(singleStick, GL_COMPILE);
    gluCylinder(gluObj, 1, 1, 1.0, 8, 8);
  glEndList();

  //Setup doubleStick
  doubleStick = glGenLists(1);
  glNewList(doubleStick, GL_COMPILE);
    glPushMatrix();
      glTranslatef(-0.33333, 0.0, 0.0);
      gluCylinder(gluObj, 0.33333, 0.33333, 1.0, 8, 8);
    glPopMatrix();
  glEndList();

  //Setup aromatic Stick

  //Setup singleWire
  singleWire = glGenLists(1);
  glNewList(singleWire, GL_COMPILE);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glEnable(GL_LIGHTING);
  glEndList();

  //Setup doubleWire
  doubleWire = glGenLists(1);
  glNewList(doubleWire, GL_COMPILE);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
      glVertex3f(0.20, 0.0, 0.0);
      glVertex3f(0.20, 0.0, 1.0);

      glVertex3f(-0.20, 0.0, 0.0);
      glVertex3f(-0.20, 0.0, 1.0);
    glEnd();
    glEnable(GL_LIGHTING);
  glEndList();

  //Setup aromaticWire
  aromaticWire = glGenLists(1);
  glNewList(aromaticWire, GL_COMPILE);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, 1.0);

      //first part of two
      glVertex3f(-0.50, 0.0, 0.0);
      glVertex3f(-0.50, 0.0, 0.25);

      //second part of two
      glVertex3f(-0.50, 0.0, 0.50);
      glVertex3f(-0.50, 0.0, 0.75);
    glEnd();
    glEnable(GL_LIGHTING);
  glEndList();

  glLineWidth(2.0);
}

void molView::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(bgColor[0], bgColor[1], bgColor[2], 0.0);
  if (mol == NULL) {
      return;
  }
  
  render(listOfMols);
  static int initialRender = 0;
  if (initialRender == 0 || hasMouse()== false ) {
    bitBlt(saveState, 0, 0, this, 0, 0, this->width(), this->height());
    initialRender = 1;
  }

}

void molView::resizeGL(int w, int h) {
  glViewport( 0, 0, (GLint)w, (GLint)h );

  saveState->resize(this->width(), this->height());
  //MEMORY LEAK MEMORY LEAK MEMORY LEAK
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  glOrtho(-this->width()/zTrans, this->width()/zTrans, -this->height()/zTrans, this->height()/zTrans, 20000.0, -20000.0);
  
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  bitBlt(saveState, 0, 0, this, 0, 0, this->width(), this->height());
  glEnable(GL_LIGHT1);
};

void molView::setCenter(list<molecule *> *renList) {
  list<molecule *>::iterator iter;
  iter = renList->begin();
  //vector<float> Center;
  molecule *tmpMol;

  float xCenterTemp = 0;
  float yCenterTemp = 0;
  float zCenterTemp = 0;
  
  //These are used to keep up with the coordinates of the hidden atoms
  float xCenterHiddenTemp = 0;
  float yCenterHiddenTemp = 0;
  float zCenterHiddenTemp = 0;
  
  xCenter = yCenter = zCenter = 0.0;
  float minZTemp;
  float maxZTemp;
  
  int atmCount = 0;
  int hiddenAtomCounter = 0;
  int totalAtomCounter = 0;
  while (iter != renList->end()) {
    tmpMol = *iter;
    for (int i=0; i<tmpMol->atoms.size(); i++) {
        totalAtomCounter++;
	float *cd = tmpMol->atoms[i]->fCoords;
    	if (tmpMol->atoms[i]->display ) {
	   atmCount++;
	   
	   xCenterTemp += cd[0];
	   yCenterTemp += cd[1];
	   zCenterTemp += cd[2];
	} else {
	   hiddenAtomCounter++;
	   xCenterHiddenTemp += cd[0];
	   yCenterHiddenTemp += cd[1];
	   zCenterHiddenTemp += cd[2];
	}
    }
 
    iter++;
    for (int i=0; i<tmpMol->atoms.size(); i++) {
       atom *atm = tmpMol->atoms[i];
       if (atm->fCoords[2] > maxZ) {
         maxZTemp = atm->fCoords[2];
       } 
       if (atm->fCoords[2] < minZ) {
         minZTemp = atm->fCoords[2];
       }
    }
  }
  
  if (hiddenAtomCounter == totalAtomCounter) {
     xCenterTemp = xCenterHiddenTemp;
     yCenterTemp = yCenterHiddenTemp;
     zCenterTemp = zCenterHiddenTemp;
     atmCount = hiddenAtomCounter;
  }  
  int test = xCenterTemp + yCenterTemp + zCenterTemp;
  if (test != 0) {
    
    xCenterTemp /= atmCount;
    yCenterTemp /= atmCount;
    zCenterTemp /= atmCount;
    xCenter = xCenterTemp;
    yCenter = yCenterTemp;
    zCenter = zCenterTemp;
    minZ = minZTemp;
    maxZ = maxZTemp; 
    glFogf(GL_FOG_START, maxZ);
    glFogf(GL_FOG_END, -zCenter-maxZ);
	glFogf(GL_FOG_MODE, GL_LINEAR);
  }
}


//RENDER
void molView::render(list<molecule *> renList) {
   static int testCount = 0;
   //static int bondList;
   if (!render_on) {
      //cout <<"render_on is set to false..returning"<<endl;
      return;
   }
   fps++;
   if (renderMode == GL_SELECT) glInitNames(); //These two lines may be moved to the selection routine.
 
   //glEnable(GL_MULTISAMPLE_ARB);
 
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   static int COUNT = 0;
   if (this->renList->size() == 0)
	   return;

   if (this->renList->size() != 0) {
    //return;
      
      if (!molEditMode) 
         setCenter(this->renList);

      //You subtract 100 toget all of 1OED into viewing area                      
      glTranslatef(xTrans, yTrans, zCenter-100);
      glInitNames(); //just chekcing
      glPushMatrix();
  
      GLfloat m[4][4];
      buildRotMat(m, currentQuat);
      glMultMatrixf(&m[0][0]);

      glTranslatef(-xCenter, -yCenter, -zCenter);
  
      glGetDoublev( GL_MODELVIEW_MATRIX, mvMatrix );
      if (COUNT == 0) {
         glGetFloatv( GL_MODELVIEW_MATRIX, origMat );
         COUNT++;
      }
      //glMultMatrixf(&origMat[0]);
      glGetDoublev( GL_PROJECTION_MATRIX, projMatrix );
      glGetIntegerv( GL_VIEWPORT, vPort );
  }
  
 
  if (infoText.size() > 0) {
    glDisable(GL_LIGHTING);
    glColor3f(0.0, 1.0, 0.0);
    
    int yLoc = 15;
    for (int i=0; i<infoText.size(); i++) {
       renderText(10, yLoc, infoText[i]);
       yLoc += 16;
       
    }
    glEnable(GL_LIGHTING);
  }
  float radius = 0.15;
  
  BONDRENDER br = STICK;

  glEnable(GL_LIGHTING);
 // glDisable(GL_NORMALIZE);
    //Loop over all the molecules in the render list
    //return;
   molIterator = this->renList->begin();
   for (molIterator; molIterator != this->renList->end(); molIterator++) {
      mol=*molIterator;
     
      //Draw Bonds...However we don't draw them if we are in GL_SELECT mode
      //if (renderMode != GL_SELECT && mol->getNumOfBonds() > 0 ) {
      if (mol->getNumOfBonds() > 0) {
      
      //YOU DISABLED THIS AND THE WINDOWS FONTS BEGAN WORKING
		 
      if (glIsEnabled(GL_LIGHTING) == true) 
         glDisable(GL_LIGHTING);
     
		 
      renderText(0.0, 0.0, 0.0, "");
		 
      glShadeModel(GL_FLAT);
  
      for (unsigned int i=0; i<mol->bonds.size(); i++) {
         bd = mol->bonds[i];
         //float *mp = bd->mp;
         float mp[3];
            
         mp[0] = (bd->from->fCoords[0] + bd->to->fCoords[0])*.5;
         mp[1] = (bd->from->fCoords[1] + bd->to->fCoords[1])*.5;
         mp[2] = (bd->from->fCoords[2] + bd->to->fCoords[2])*.5;
           
         if (!distMode && !delDistMode && !angMode 
         && !delAngMode && !torsionMode || !delTorsionMode) 
         {
             glPushName(bd->objectNum);
         }
         if (bd->from->display == true && bd->to->display == true) {
            br = bd->renderType;
            if (br == WIRE) {  
               drawWireBond(bd);
               glColor3f(0.0, 0.0, 0.0);
            } 
            else if (br == STICK) {
	       bd->calcDirCosines();
          glShadeModel(GL_SMOOTH); //stick are pretty rough without this  
	       //glEnable(GL_CULL_FACE); 
  	       if (glIsEnabled(GL_LIGHTING) == false)
    	          glEnable(GL_LIGHTING);
  		 
               drawStickBond(bd, radius, radius);
            }
         }
         if (!distMode && !delDistMode && !angMode 
         && !delAngMode && !torsionMode || !delTorsionMode) 
         {
            glPopName(); 
         }
      }
       
      glShadeModel(GL_SMOOTH);
       
   }
    
   //This is were we call the vertex array for the points
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      at = mol->atoms[i];
      float *cd = at->fCoords;     
      if (at->display == true) {
         glPushName(at->objectNum);  //picking stuff
         renderAtom(radius-0.005, at, at->renderType);
         glPopName();
      }
   }
   
   //ALL OF THESE SECTIONS MUST COME AFTER THE ATOMS RENDER SECTION.
   //Because the way you do selection for distance && angles && such */
    
   // This section is were we add the labels
   
     
   glDisable(GL_LIGHTING);
   float textColor[3];
   if (bgColor[0] >= .5) textColor[0] = 0;
   else textColor[0] = 1;
   if (bgColor[1] >= .5) textColor[1] = 0;
   else textColor[1] = 1;
   if (bgColor[2] >= .5) textColor[2] = 0;
   else textColor[2] = 1;
   glColor3f(textColor[0], textColor[1], textColor[2]);
   glDisable(GL_LIGHTING);
  
   for (unsigned int i=0; i<mol->atoms.size(); i++) {
      //float *cd = labelAtoms[i]->fCoords;
      if (mol->atoms[i]->label.length() != 0) {
         float *cd = mol->atoms[i]->fCoords;	
         //QMessageBox::critical(0, "dynamol", mol->atoms[i]->label);
         renderText(cd[0]+.25, cd[1]+.15, cd[2]+.15, mol->atoms[i]->label);
      }
   }
   
   glDisable(GL_LIGHTING);
   glColor3f(0.0, 0.0, 0.0);
   //This section will draw the distances  
   //Both the intromolecular && intrmoelcular
   glLineWidth(3);
   drawDistances(mol);
   drawAngles(mol);
   drawTorsions(mol);
   glLineWidth(2);
      
   glBegin(GL_POINTS);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(5.0);
   for (int i=0; i<surfacePoints.size(); i++) { 
      //glColor3fv(&pointColors[i][0] );
      glVertex3dv(&surfacePoints[i][0]);
      i++;
   }
   glEnd();  
   glEnable(GL_LIGHTING);
    
   // This section is were ribbon drawing will take place.
   // If you are looking for the function that defines the 
   // ribbon then check defineRibbon
   // It will point you to ribbon::ribbon()

   // Currently we are using display lists to help speed up 
   // the the rendering of the
   // ribbons.  As far as I can tell it has helped....at the 
   // expense of a little code clutter
   // Yes yes I know all this damned dynamic_casting crap...
   // I hate it..I know it is bad...but
   // I wrote this program while learnig as well.
      
   //if we are not in select mode && the molecule currently in use is a chain
   if (renderMode != GL_SELECT && mol->rtti() >= 13) {
      if (mol->rtti() == 13) { //If it is a chain
         chain *ch = dynamic_cast<chain *>(mol);
         if (ch->ribList == -1 && ch->rib != NULL) {
            ch->ribList = glGenLists(1);

            glNewList(ch->ribList, GL_COMPILE);
              drawRibbon(ch);
            glEndList();

            //Now render it
            glCallList(ch->ribList);
         } else {
            glCallList(ch->ribList);
         }
          
      } else if (mol->rtti() == 14) {  //else if it is a protein
         protein *prot = dynamic_cast<protein *>(mol);
         for (int i=0; i<prot->chains.size(); i++) {
            chain *ch = prot->chains[i];
            if (ch->ribList == -1 && ch->rib != NULL)  {
               ch->ribList = glGenLists(1);
                
               glNewList(ch->ribList, GL_COMPILE);
               drawRibbon(ch);
               glEndList();

               //Now render it
               glCallList(ch->ribList);
            } else {
               glCallList(ch->ribList);
            }
         }
      }

   //Draw A surface is the molecule has one
   }
   
   drawSurface(mol);
}
  
  drawSpheres();   

   
  
  glPopMatrix();
 
  // THIS SECTION MAKES IT SO THAT YOU CAN ZOOM??? 
  // Must be a better way!
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  float tmpZ = 1/zTrans;  //only here for optimzation stuff.
  glOrtho(-width()*tmpZ, width()*tmpZ, -height()*tmpZ, 
          height()*tmpZ, -100.0, 200.0);
  // ########### END SECTION ###########    
}


void molView::drawDistances(molecule *mol) {

  //QFont font( "Times"/*"Helvetica"*/, 12, 63/*QFont::Bold*/ );
  //setFont( font );
  
  float *cd1, *cd2;
  float a, b, c, d, mp[3];
  float textColor[3];
  if (bgColor[0] >= .5) textColor[0] = 0;
  else textColor[0] = 1;
  if (bgColor[1] >= .5) textColor[1] = 0;
  else textColor[1] = 1;
  if (bgColor[2] >= .5) textColor[2] = 0;
  else textColor[2] = 1;
  glColor3f(textColor[0], textColor[1], textColor[2]);
      for (int i=0; i<mol->dist.size(); i++) {
        cd1 = mol->dist[ i ][0]->fCoords;
        cd2 = mol->dist[ i ][1]->fCoords;
        a = cd1[0] - cd2[0];
        b = cd1[1] - cd2[1];
        c = cd1[2] - cd2[2];
        d = sqrt(a*a + b*b + c*c);
        QString num;
        num.setNum(d, 'f', 3);
        mp[0] = (cd1[0] + cd2[0] )*0.5;
        mp[1] = (cd1[1] + cd2[1] )*0.5;
        mp[2] = (cd1[2] + cd2[2] )*0.5;

        glBegin(GL_LINES);
          glVertex3fv( cd1 );
          glVertex3fv( cd2 );
        glEnd();

         //glColor3f(1.0, 1.0, 1.0);
         renderText(mp[0]+0.25, mp[1]+0.25, mp[2]+0.25, num);
        //glColor3f(0.0, 1.0, 1.0);
      }

      for (int i=0; i<interMolDist.size(); i++) {
        cd1 = interMolDist[i][0]->fCoords;
        cd2 = interMolDist[i][1]->fCoords;
        a = cd1[0] - cd2[0];
        b = cd1[1] - cd2[1];
        c = cd1[2] - cd2[2];
        d = sqrt(a*a + b*b + c*c);
        QString num;
        num.setNum(d, 'f', 3);
        mp[0] = (cd1[0] + cd2[0] )*0.5;
        mp[1] = (cd1[1] + cd2[1] )*0.5;
        mp[2] = (cd1[2] + cd2[2] )*0.5;
        
        glBegin(GL_LINES);
          glVertex3fv( interMolDist[i][0]->fCoords );
          glVertex3fv( interMolDist[i][1]->fCoords );
        glEnd();

        renderText(mp[0]+0.25, mp[1]+0.25, mp[2]+0.25, num);
      }
      glColor3f(0.0, 0.0, 0.0);
}
 
void molView::drawAngles(molecule *mol) {

  if (mol->ang.size() == 0 && interMolAng.size()==0) return;
  glDisable(GL_LIGHTING);
  float angle = 0;
  float mag1, mag3, dotProd, mp[3], trMid[3];
  
  float cd1[4], cd3[4], *cPtr1, *cPtr2, *cPtr3;
  cd1[3] = cd3[3] = 1; //because of matrix mutliply stuff
  float textColor[3];
  if (bgColor[0] >= .5) textColor[0] = 0;
  else textColor[0] = 1;
  if (bgColor[1] >= .5) textColor[1] = 0;
  else textColor[1] = 1;
  if (bgColor[2] >= .5) textColor[2] = 0;
  else textColor[2] = 1;
  glColor3f(textColor[0], textColor[1], textColor[2]);
  //glColor3f(0.7, 1.0, 0.0);
  for (int i=0; i<mol->ang.size(); i++) {
    atom *atm1 = mol->ang[ i ][0];
    atom *atm2 = mol->ang[ i ][1];
    atom *atm3 = mol->ang[ i ][2];
    cPtr1 = atm1->fCoords;
    cPtr2 = atm2->fCoords;
    cPtr3 = atm3->fCoords;
    mag1 = mag3 = dotProd = 0;
    for (int j=0; j<3; j++) { 
        cd1[ j ] = cPtr1[ j ] - cPtr2[ j ];   //translateing the two outer points to the origin
        cd3[ j ] = cPtr3[ j ] - cPtr2[ j ];

        dotProd += cd1[ j ] * cd3[ j ];     //the dot product

        mag1 += cd1[ j ] * cd1[ j ];   //The two seperate maginitudes..translatesd to the origin
        mag3 += cd3[ j ] * cd3[ j ];
        
        mp[ j ] = (cPtr1[ j ] + cPtr3[ j ])*0.5;      //The mid point of the angle line
        trMid[ j ] = (cd1[ j ] + cd3[ j ])*0.5;
    }
    mag1 = sqrt(mag1);
    mag3 = sqrt(mag3);
    angle = ARCFIX*acos( dotProd/(mag1*mag3) );  //this gives us the angle between the two points

    QString num;
    num.setNum(angle, 'f', 3);

  //This draws the outline of the triangle being evauluated
  if (!atm2->isBondedTo(atm1)  || !atm2->isBondedTo(atm3) ) {
    glBegin(GL_LINES);
      glVertex3fv(cPtr1);
      glVertex3fv(cPtr2);
      
      glVertex3fv(cPtr2);
      glVertex3fv(cPtr3);
    glEnd();
   } 

   renderText(mp[0]+0.05, mp[1]+0.05, mp[2]+0.05, num);

   float cross[3], rotAxis[3], cross2[3], axis[3], rotMat[16], rotMat3[16], newPoint[4], rotMat4[16];
      
   //Get crossProduct of origin centered points.
   vCross(cd1, cd3, cross);

   axis[0] = 0;  axis[1] = 0; axis[2] = 1;
   vCross(axis, cross, rotAxis);

   float len1 = vLength(cross);
   float ang2 = -acos(cross[2]/len1);

   QUAT q1(ang2, rotAxis);
   q1.buildMatrix(rotMat);

    //Now we nee to rotate one of our angle points  so that we can correctly determine the angle
   QUAT q2(-ang2, rotAxis);
   q2.buildMatrix(rotMat3);
 
   mulit_4X16(newPoint, cd3, rotMat3);
    
   axis[0] = 0; axis[1] = 1; axis[2] = 0; 
   vCross(newPoint, axis, cross2);
    //vCross(newPoint, axis, cd3);
    
   float len2 = vLength(newPoint);
   float dotProd2 = vDot(newPoint, axis);
   float ang3 = 0;
   if (cross2[2] > 0) ang3 = acos(dotProd2/len2);
   else ang3 = -acos(dotProd2/len2);

   axis[0] = 0; axis[1] = 0; axis[2] = 1;
   QUAT q3(ang3, axis);
   q3.buildMatrix(rotMat4);

   glPushMatrix();
     glTranslatef(cPtr2[0], cPtr2[1], cPtr2[2]);
     glMultMatrixf(rotMat);
     glMultMatrixf(rotMat4);
     gluQuadricDrawStyle(quadObj, GLU_SILHOUETTE);
     gluPartialDisk(quadObj, 0.0, 0.75, 20, 14, 0.0, angle);
   glPopMatrix();  
  }

  //Now we will draw the intermoleuclar angles
  for (int i=0; i<interMolAng.size(); i++) {
    atom *atm1 = interMolAng[ i ][0];
    atom *atm2 = interMolAng[ i ][1];
    atom *atm3 = interMolAng[ i ][2];
    cPtr1 = atm1->fCoords;
    cPtr2 = atm2->fCoords;
    cPtr3 = atm3->fCoords;
    mag1 = mag3 = dotProd = 0;
    for (int j=0; j<3; j++) {
        cd1[ j ] = cPtr1[ j ] - cPtr2[ j ];   //translateing the two outer points to the origin
        cd3[ j ] = cPtr3[ j ] - cPtr2[ j ];

        dotProd += cd1[ j ] * cd3[ j ];     //the dot product

        mag1 += cd1[ j ] * cd1[ j ];   //The two seperate maginitudes..translatesd to the origin
        mag3 += cd3[ j ] * cd3[ j ];

        mp[ j ] = (cPtr1[ j ] + cPtr3[ j ])*0.5;      //The mid point of the angle line
        trMid[ j ] = (cd1[ j ] + cd3[ j ])*0.5;
    }
    mag1 = sqrt(mag1);
    mag3 = sqrt(mag3);
    angle = ARCFIX*acos( dotProd/(mag1*mag3) );  //this gives us the angle between the two points

    QString num;
    num.setNum(angle, 'f', 3);

  //This draw the outline of the triangle being evauluated
  if (!atm2->isBondedTo(atm1)  || !atm2->isBondedTo(atm3) ) {
    glBegin(GL_LINES);
      glVertex3fv(cPtr1);
      glVertex3fv(cPtr2);

      glVertex3fv(cPtr2);
      glVertex3fv(cPtr3);
    glEnd();
   }
    renderText(mp[0]+0.25, mp[1]+0.25, mp[2]+0.25, num);

    float cross[3], rotAxis[3], cross2[3], axis[3], rotMat[16], rotMat3[16], newPoint[4], rotMat4[16];

    //Get crossProduct of origin centered points.
    vCross(cd1, cd3, cross);

    axis[0] = 0;  axis[1] = 0; axis[2] = 1;
    vCross(axis, cross, rotAxis);

    float len1 = vLength(cross);
    float ang2 = -acos(cross[2]/len1);

    QUAT q1(ang2, rotAxis);
    q1.buildMatrix(rotMat);

    //GLfloat rotMat2[4][4];

    //Now we nee to rotate one of our angle points  so that we can correctly determine the angle
    QUAT q2(-ang2, rotAxis);
    q2.buildMatrix(rotMat3);
    mulit_4X16(newPoint, cd3, rotMat3);

    axis[0] = 0; axis[1] = 1; axis[2] = 0;
    vCross(newPoint, axis, cross2);

    float len2 = vLength(newPoint);
    float dotProd2 = vDot(newPoint, axis);
    float ang3 = 0;
    if (cross2[2] > 0) ang3 = acos(dotProd2/len2);
    else ang3 = -acos(dotProd2/len2);

    axis[0] = 0; axis[1] = 0; axis[2] = 1;
    QUAT q3(ang3, axis);
    q3.buildMatrix(rotMat4);

    glPushMatrix();
      glTranslatef(cPtr2[0], cPtr2[1], cPtr2[2]);

      glMultMatrixf(rotMat);
      glMultMatrixf(rotMat4);

      gluQuadricDrawStyle(quadObj, GLU_SILHOUETTE);
      gluPartialDisk(quadObj, 0.0, 0.75, 20, 14, 0.0, angle);
    glPopMatrix();
  }
  glColor3f(0.0, 0.0, 0.0);
  glEnable(GL_LIGHTING);
}


void  molView::drawTorsions(molecule *mol) {
  if (mol->tor.size() == 0 && interMolTor.size()==0) return;

  glDisable(GL_LIGHTING);
  float angle = 0;
  float mag1, mag3, dotProd, mp[3], trMid[3];

  float mid1[3], mid2[3], textMid[3], *cPtr1, *cPtr2, *cPtr3, *cPtr4;
  float cd1[3], cd2[3];
  float textColor[3];
  if (bgColor[0] >= .5) textColor[0] = 0;
  else textColor[0] = 1;
  if (bgColor[1] >= .5) textColor[1] = 0;
  else textColor[1] = 1;
  if (bgColor[2] >= .5) textColor[2] = 0;
  else textColor[2] = 1;
  glColor3f(textColor[0], textColor[1], textColor[2]);
  //glColor3f(0.7, 1.0, 0.0);
  for (int i=0; i<mol->tor.size(); i++) {
    cPtr1 = mol->tor[i][0]->fCoords;
    cPtr2 = mol->tor[i][1]->fCoords;
    cPtr3 = mol->tor[i][2]->fCoords;
    cPtr4 = mol->tor[i][3]->fCoords;

    for (int i=0; i<3; i++) {
      mid1[i] = (cPtr1[i]+ cPtr2[i])*0.50;
      mid2[i] = (cPtr3[i] +cPtr4[i])*0.50;

      textMid[i] = (mid1[i] + mid2[i])*0.50;
    }

    //This section is were we calculate the torsion angle
   float cross1[3], cross2[3];
   vSub( cPtr1, cPtr2, cd1 );
   vSub( cPtr3, cPtr2, cd2 );
   vCross( cd1, cd2, cross1 );

   vSub( cPtr4, cPtr3, cd1 );
   vSub( cPtr2, cPtr3, cd2 );
   vCross( cd2, cd1, cross2 );

    float dp = vDot(cross1, cross2);
    float l1 = vLength(cross1);
    float l2 = vLength(cross2);

    float angle = ARCFIX*acos( dp/(l1*l2) );

    QString num;
    num.setNum(angle, 'f', 3);

    //Draw the torsion outline
    //glPointSize(5);
    glBegin(GL_LINE_STRIP);
      glVertex3fv(cPtr1);
      glVertex3fv(cPtr2);
      glVertex3fv(cPtr3);
      glVertex3fv(cPtr4);      
    glEnd();

    //Now draw the torsion cross bar  && text
    renderText(textMid[0]+0.15, textMid[1]+0.15, textMid[2]+0.15, num);
    glBegin(GL_LINES);
      glVertex3fv(mid1);
      glVertex3fv(mid2);
    glEnd();
  }

  //Now lets take care of the inter-molecular torsions
  for (int i=0; i<interMolTor.size(); i++) {
    cPtr1 = interMolTor[i][0]->fCoords;
    cPtr2 = interMolTor[i][1]->fCoords;
    cPtr3 = interMolTor[i][2]->fCoords;
    cPtr4 = interMolTor[i][3]->fCoords;

    for (int i=0; i<3; i++) {
      mid1[i] = (cPtr1[i]+ cPtr2[i])*0.50;
      mid2[i] = (cPtr3[i] +cPtr4[i])*0.50;

      textMid[i] = (mid1[i] + mid2[i])*0.50;
    }

    //This section is were we calculate the torsion angle
   float cross1[3], cross2[3];
   vSub( cPtr1, cPtr2, cd1 );
   vSub( cPtr3, cPtr2, cd2 );
   vCross( cd1, cd2, cross1 );

   vSub( cPtr4, cPtr3, cd1 );
   vSub( cPtr2, cPtr3, cd2 );
   vCross( cd2, cd1, cross2 );

    float dp = vDot(cross1, cross2);
    float l1 = vLength(cross1);
    float l2 = vLength(cross2);

    float angle = ARCFIX*acos( dp/(l1*l2) );

    QString num;
    num.setNum(angle, 'f', 3);

    //Draw the torsion outline
    //glPointSize(5);
    glBegin(GL_LINE_STRIP);
      glVertex3fv(cPtr1);
      glVertex3fv(cPtr2);
      glVertex3fv(cPtr3);
      glVertex3fv(cPtr4);
    glEnd();

    //Now draw the torsion cross bar  && text
    renderText(textMid[0]+0.05, textMid[1]+0.05, textMid[2]+0.05, num);
    glBegin(GL_LINES);
      glVertex3fv(mid1);
      glVertex3fv(mid2);
    glEnd();
  }
  

}

void molView::drawStickBonds(vector<bond *> &Bonds, float radius) {
float radius_1 = radius;
float radius_2 = radius;
glShadeModel(GL_SMOOTH); //stick are pretty rough without this  

//glEnable(GL_CULL_FACE); 
if (glIsEnabled(GL_LIGHTING) == false)
   glEnable(GL_LIGHTING);

for (int i=0; i<Bonds.size(); i++) {
  bond *BD = Bonds[i];
    
  float *Coords1 = BD->from->fCoords;
  float *Coords2 = BD->to->fCoords;
  atom *from, *to;
  from = BD->from;
  to = BD->to;
  //float *midPoint = BD->mp;
  float midPoint[3];
  float len = BD->len;
  float halfLen = len*0.5; 

  float Cross1[3], Cross2[3], tmp[3], tmp1[3];
 
  //float *fColor = from->COLOR;
  //float *tColor = to->COLOR;
  
  float fColor[4]; 
  float tColor[4]; 
  if (BD->selected) {
      fColor[0] = tColor[0] = 0.85;
      fColor[1] = tColor[1] = 0.20;
      fColor[2] = tColor[2] = 0.0;
      fColor[3] = tColor[3] = 1.0;
  } else {
     for (int i=0; i<3; i++) {
        fColor[i] = from->COLOR[i];
        tColor[i] = to->COLOR[i];
     }
     fColor[3] = tColor[3] = 1.0;
  }
  


  if (BD->order == 1) {
     
    //Lets first do a little check to see if atoms are the same color.  If so we can just
    //render one cylinder instead of two.  YIPPY!
    if (fColor[0] == tColor[0] && fColor[1] == tColor[1] && fColor[2] == tColor[2]) {
      
      glPushMatrix();
        glTranslatef(Coords1[0], Coords1[1], Coords1[2]);
        glRotatef(BD->zRot1, BD->xAxis, BD->yAxis, 0.0);
        glColor4fv(fColor);
        //glPushMatrix();
        gluCylinder(gluObj, radius, radius, len, cylSlices, cylStacks);
	gluSphere(quadObj, radius_1, sphSlices, sphStacks);
        glTranslatef(0.0, 0.0, len);
	gluSphere(quadObj, radius_1, sphSlices, sphStacks);
	//glPopMatrix();

        //glScalef(radius_1, radius_2, len);
	//gluCylinder(gluObj, radius, radius, len, cylSlices, cylStacks);
      glPopMatrix();

    } else {  
    
      glPushMatrix();
        
        glTranslatef(Coords1[0], Coords1[1], Coords1[2]);
	glRotatef(BD->zRot1, BD->xAxis, BD->yAxis, 0.0);
        glColor4fv(fColor);
	gluSphere(quadObj, radius_1, sphSlices, sphStacks);
	gluCylinder(gluObj, radius, radius, halfLen, cylSlices, cylStacks);

    	glTranslatef(0.0, 0.0, halfLen);

        glColor4fv(tColor);
        gluCylinder(gluObj, radius, radius, halfLen, cylSlices, cylStacks);
        glTranslatef(0.0, 0.0, halfLen);
        gluSphere(quadObj, radius_1, sphSlices, sphStacks);  

      glPopMatrix();
      
    }
  }   
  
  //glScalef(radius_1, radius_2, halfLen);

}

}

void molView::drawStickBond(bond *BD, float radius_1, float radius_2 ) {
      
  
  float *Coords1 = BD->from->fCoords;
  float *Coords2 = BD->to->fCoords;
  atom *from, *to;
  from = BD->from;
  to = BD->to;
  //float *midPoint = BD->mp;
  float midPoint[3];
  float len = BD->len;
  float halfLen = len*0.5; 

  float Cross1[3], Cross2[3], tmp[3], tmp1[3];
 
  //float *fColor = from->COLOR;
  //float *tColor = to->COLOR;
  
  float fColor[4]; 
  float tColor[4]; 
  if (BD->selected) {
      fColor[0] = tColor[0] = 0.85;
      fColor[1] = tColor[1] = 0.20;
      fColor[2] = tColor[2] = 0.0;
      fColor[3] = tColor[3] = 1.0;
  } else {
     for (int i=0; i<3; i++) {
        fColor[i] = from->COLOR[i];
        tColor[i] = to->COLOR[i];
     }
     fColor[3] = tColor[3] = 1.0;
  }
 
  if (BD->order == 1) {
     
    //Lets first do a little check to see if atoms are the same color.  If so we can just
    //render one cylinder instead of two.  YIPPY!
    if (fColor[0] == tColor[0] && fColor[1] == tColor[1] && fColor[2] == tColor[2]) {
      
      glPushMatrix();
        glTranslatef(Coords1[0], Coords1[1], Coords1[2]);
        glRotatef(BD->zRot1, BD->xAxis, BD->yAxis, 0.0);
        glColor4fv(fColor);
        //glPushMatrix();
        gluCylinder(gluObj, radius_1, radius_2, len, cylSlices, cylStacks);
	gluSphere(quadObj, radius_1, sphSlices, sphStacks);
        glTranslatef(0.0, 0.0, len);
	gluSphere(quadObj, radius_1, sphSlices, sphStacks);
	//glPopMatrix();

        //glScalef(radius_1, radius_2, len);
      glPopMatrix();

    } else {  
      glPushMatrix();
        
        glTranslatef(Coords1[0], Coords1[1], Coords1[2]);
	glRotatef(BD->zRot1, BD->xAxis, BD->yAxis, 0.0);
        glColor4fv(fColor);
	gluSphere(quadObj, radius_1, sphSlices, sphStacks);
        //glPushMatrix();
	   //glScalef(radius_1, radius_2, halfLen); 
	   //glColor4fv(fColor); 
	   gluCylinder(gluObj, radius_1, radius_2, halfLen, cylSlices, cylStacks);
    	   glTranslatef(0.0, 0.0, halfLen);
           glColor4fv(tColor);
           gluCylinder(gluObj, radius_1, radius_2, halfLen, cylSlices, cylStacks);
	//glPopMatrix();
        glTranslatef(0.0, 0.0, halfLen);
        gluSphere(quadObj, radius_1, sphSlices, sphStacks);  
      glPopMatrix();
    }
  } else if(BD->order > 1) {
    //THIS is stuff to orient the double bond in the Z axis correctly
       atom *af = BD->from;
       atom *at = BD->to;
       atom *dbTemp = NULL;;
       float zRot = 0;
       if (af->atoms.size() != 0) {
         for (unsigned int i=0; i<af->atoms.size(); i++) {
           if (af->atoms[i] != BD->to) {
             dbTemp = af->atoms[i];
             break;
           }
         }
       }
       if (dbTemp == NULL) {
          if (at->atoms.size() != 0) {
            for (unsigned int i=0; i<at->atoms.size(); i++) {
              if (at->atoms[i] != af) {
                dbTemp = at->atoms[i];
                break;
              }
            }
          }
       }

      if (/*order == 2 && */dbTemp != NULL) {

            float *Coords3 = dbTemp->get_fCoords();

            tmp[0] =  Coords3[0] - Coords1[0];
            tmp[1] =  Coords3[1] - Coords1[1];
            tmp[2] =  Coords3[2] - Coords1[2];

            tmp1[0] =  Coords2[0] - Coords1[0];
            tmp1[1] =  Coords2[1] - Coords1[1];
            tmp1[2] =  Coords2[2] - Coords1[2];

            midPoint[0] = tmp1[0]*0.5;
            midPoint[1] = tmp1[1]*0.5;
            midPoint[2] = tmp1[2]*0.5;

            Cross1[0] = (tmp[1]*tmp1[2])-(tmp[2]*tmp1[1]);// - Coords1[0];
            Cross1[1] = (tmp[2]*tmp1[0])-(tmp[0]*tmp1[2]);// - Coords1[1];
            Cross1[2] = (tmp[0]*tmp1[1])-(tmp[1]*tmp1[0]);// - Coords1[2];

            Cross2[0] = (Cross1[1]*tmp1[2])-(Cross1[2]*tmp1[1]);// - Coords1[0];
            Cross2[1] = (Cross1[2]*tmp1[0])-(Cross1[0]*tmp1[2]);// - Coords1[1];
            Cross2[2] = (Cross1[0]*tmp1[1])-(Cross1[1]*tmp1[0]);// - Coords1[2];
	    
            float Cross2Mag = sqrt(Cross2[0]*Cross2[0] + Cross2[1]*Cross2[1] + Cross2[2]*Cross2[2]);
            //Cross2Mag = 1/(Cross2Mag*10);
            Cross2Mag = 0.1/Cross2Mag;
            Cross2[0] *= (Cross2Mag);
            Cross2[1] *= (Cross2Mag);
            Cross2[2] *= (Cross2Mag);

	    float radFactor = 1.00;
	    if (BD->order == 3) {
 		Cross2[0] *= 1.50;
		Cross2[1] *= 1.50;
		Cross2[2] *= 1.50;
	        glPushMatrix();
                glTranslatef(Coords1[0], Coords1[1], Coords1[2]);
                glRotatef(BD->zRot1, BD->xAxis, BD->yAxis, 0.0);

                //Draw first part of single Bond
                glColor4fv(fColor);
                glPushMatrix();
                
		gluSphere(quadObj, radius_1, sphSlices, sphStacks);
                
		glPopMatrix();
		glPushMatrix();
                  glScalef(radius_1*radFactor, radius_2*radFactor, halfLen);
		  gluCylinder(gluObj, 1, 1, 1.0, cylSlices, cylStacks);
                glPopMatrix();

                //Translate to beggining of second part of bond
                glTranslatef(0.0, 0.0, halfLen);

                //Draw second part of bond
                glColor4fv(tColor);
                glPushMatrix();
                  glScalef(radius_1*radFactor, radius_2*radFactor, halfLen);
		  gluCylinder(gluObj, 1, 1, 1.0, cylSlices, cylStacks);
                glPopMatrix();
		
		glTranslatef(0.0, 0.0, len*0.5);
		gluSphere(quadObj, radius_1, sphSlices, sphStacks);
                glPopMatrix();
	    }
            //DRAW FIRST SIDE OF BOND>>>BOTH TOOP AND BOTTOM
        glPushMatrix();
            glTranslatef(Cross2[0]+Coords1[0], Cross2[1]+Coords1[1], Cross2[2]+Coords1[2]);
            glRotatef(BD->zRot1, BD->xAxis, BD->yAxis, 0.0);

            //Draw first part of single Bond
            glColor4fv(fColor);
            gluSphere(quadObj, radius_1, sphSlices, sphStacks);
	    glPushMatrix();
                glScalef(radius_1*radFactor, radius_2*radFactor, halfLen);
		gluCylinder(gluObj, 1, 1, 1.0, cylSlices, cylStacks);
            glPopMatrix();

            //Translate to beggining of second part of bond
            glTranslatef(0.0, 0.0, halfLen);

            //Draw second part of bond
            glColor4fv(tColor);
            glPushMatrix();
              glScalef(radius_1*radFactor, radius_2*radFactor, halfLen);
	      gluCylinder(gluObj, 1, 1, 1.0, cylSlices, cylStacks);
            glPopMatrix();
	    
	    glTranslatef(0.0, 0.0, halfLen);
	    gluSphere(quadObj, radius_1, sphSlices, sphStacks);
			    
        glPopMatrix();
            
        //DRAW SECOND PART OF BOND >>>> BOTH TOP AND BOTTOM
        glPushMatrix();
          glTranslatef(-Cross2[0]+Coords1[0], -Cross2[1]+Coords1[1], -Cross2[2]+Coords1[2]);
          glRotatef(BD->zRot1, BD->xAxis, BD->yAxis, 0.0);

          //Draw first part of single Bond
          glColor4fv(fColor);
	  gluSphere(quadObj, radius_1, sphSlices, sphStacks);
          glPushMatrix();
              glScalef(radius_1*radFactor, radius_2*radFactor, halfLen);
	      gluCylinder(gluObj, 1, 1, 1.0, cylSlices, cylStacks);
          glPopMatrix();

          //Translate to beggining of second part of bond
          glTranslatef(0.0, 0.0, halfLen);

          //Draw second part of bond
          glColor4fv(tColor);
          glPushMatrix();
              glScalef(radius_1*radFactor, radius_2*radFactor, halfLen);
//	      glCallList(singleStick);
              gluCylinder(gluObj, 1, 1, 1.0, cylSlices, cylStacks);
          glPopMatrix();

          glTranslatef(0.0, 0.0, halfLen);
          gluSphere(quadObj, radius_1, sphSlices, sphStacks);
          glPopMatrix();
      }
  }
}

void molView::drawWireBond(bond *BD) {
  if (glIsEnabled(GL_LIGHTING) == true) {
      glDisable(GL_LIGHTING);
  }
  glShadeModel(GL_FLAT);
  
  atom *from = BD->from;
  atom *to = BD->to;
  
  float *Coords1 = from->fCoords;
  float *Coords2 = to->fCoords;

  float fColor[3]; 
  float tColor[3]; 
  if (BD->selected) {
      fColor[0] = tColor[0] = 0.85;
      fColor[1] = tColor[1] = 0.20;
      fColor[2] = tColor[2] = 0.0;
  } else {
     for (int i=0; i<3; i++) {
        fColor[i] = from->COLOR[i];
        tColor[i] = to->COLOR[i];
     }
  }
  
  
  float Cross1[3], Cross2[3];
  //float *midPoint = BD->mp;
  float midPoint[3];
  float *c1 = BD->from->fCoords;
  float *c2 = BD->to->fCoords;
  midPoint[0] = (c1[0] + c2[0])*0.5;
  midPoint[1] = (c1[1] + c2[1])*0.5;
  midPoint[2] = (c1[2] + c2[2])*0.5; 
       
  
  float tmp[3], tmp1[3];
  int order = BD->order;

  if (order == 1 ) {
      //This is render text stuff
      if (fColor[0] == tColor[0] && fColor[1] == tColor[1] && fColor[2] == tColor[2]) {
        glColor3fv( fColor );
        glBegin(GL_LINES);
          glVertex3fv( Coords1 );
          glVertex3fv( Coords2 );
        glEnd();
      } else {  
        glBegin(GL_LINE_STRIP);
        
          //Draw first half of single bond
          glColor3fv( fColor );
          glVertex3fv( Coords1 );
          glVertex3fv( midPoint );

          //Draw second half of single bond
          glColor3fv( tColor );
          glVertex3fv( Coords2 );

        glEnd();
      }

    }
    else if( order == 2 || order ==3 || order == 4) {
       //THIS is stuff to orient the double bond in the Z axis correctly    
       //atom *af = BD->from;
       //atom *at = BD->to;
       atom *dbTemp = NULL;;
       float zRot = 0;
       if (from->atoms.size() != 0) {
         for (unsigned int i=0; i<from->atoms.size(); i++) {
           if (from->atoms[i] != to) {
             dbTemp = from->atoms[i];
             break;
           }
         }
       }
       if (dbTemp == NULL) {
          if (to->atoms.size() != 0) {
            for (unsigned int i=0; i<to->atoms.size(); i++) {
              if (to->atoms[i] != from) {
                dbTemp = to->atoms[i];
                break;
              }
            }
          }
       }
       if (/*order == 2 && */dbTemp != NULL) {
        //float *Coords3 = dbTemp->get_fCoords();
        float *Coords3 = dbTemp->fCoords;
        
        tmp[0] =  Coords3[0] - Coords1[0];
        tmp[1] =  Coords3[1] - Coords1[1];
        tmp[2] =  Coords3[2] - Coords1[2];

        tmp1[0] =  Coords2[0] - Coords1[0];
        tmp1[1] =  Coords2[1] - Coords1[1];
        tmp1[2] =  Coords2[2] - Coords1[2];

        midPoint[0] =tmp1[0]*0.5;
        midPoint[1] =tmp1[1]*0.5;
        midPoint[2] =tmp1[2]*0.5;

        Cross1[0] = (tmp[1]*tmp1[2])-(tmp[2]*tmp1[1]);
        Cross1[1] = (tmp[2]*tmp1[0])-(tmp[0]*tmp1[2]);
        Cross1[2] = (tmp[0]*tmp1[1])-(tmp[1]*tmp1[0]);

        Cross2[0] = (Cross1[1]*tmp1[2])-(Cross1[2]*tmp1[1]);
        Cross2[1] = (Cross1[2]*tmp1[0])-(Cross1[0]*tmp1[2]);
        Cross2[2] = (Cross1[0]*tmp1[1])-(Cross1[1]*tmp1[0]);

        float Cross2Mag = sqrt(Cross2[0]*Cross2[0] + Cross2[1]*Cross2[1] + Cross2[2]*Cross2[2]);
        //Cross2Mag = 1.0/(Cross2Mag*20);
        Cross2Mag = .05/Cross2Mag;
        Cross2[0] *= (Cross2Mag);
        Cross2[1] *= (Cross2Mag);
        Cross2[2] *= (Cross2Mag);

       } else {
       }
       
       
        float len = BD->len;

       //Check to see if both atoms are colored the same.  If they are then just render one line instead of two.
       //This should ultimately speed up the calcultions a pretty good bit 
       if (fColor[0] == tColor[0] && fColor[1] == tColor[1] && fColor[2] == tColor[2]) {
          if (order == 3) {
	      glPushMatrix();
              glTranslatef(Coords1[0], Coords1[1], Coords1[2]);
	      glColor3fv( fColor );
              glBegin(GL_LINES);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3fv(tmp1);
              glEnd();	
	      glPopMatrix();
	  }
          glPushMatrix();
          glTranslatef(Cross2[0]+Coords1[0], Cross2[1]+Coords1[1], Cross2[2]+Coords1[2]);
          glColor3fv( fColor );
          glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3fv(tmp1);
          glEnd();
          glPopMatrix();
	  
          glPushMatrix();
          glTranslatef(-Cross2[0]+Coords1[0], -Cross2[1]+Coords1[1], -Cross2[2]+Coords1[2]);
          glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3fv(tmp1);
          glEnd();
          glPopMatrix();
       } else {
           //Oh well the atoms were different colors now lets spend the time it takes to render them
           // as two seperate lines
	   if (order == 3) {
	     glPushMatrix();
             glTranslatef(Coords1[0], Coords1[1], Coords1[2]);
             glBegin(GL_LINE_STRIP);
               glColor3fv( fColor );
               glVertex3f(0.0, 0.0, 0.0);
               glVertex3fv( midPoint );
               glColor3fv( tColor );
               glVertex3fv( tmp1 );
             glEnd();
             glPopMatrix();
	   }
	   
            glPushMatrix();
            glTranslatef(Cross2[0]+Coords1[0], Cross2[1]+Coords1[1], Cross2[2]+Coords1[2]);

            glBegin(GL_LINE_STRIP);
              glColor3fv( fColor );
              glVertex3f(0.0, 0.0, 0.0);
              glVertex3fv( midPoint );
              glColor3fv( tColor );
              glVertex3fv( tmp1 );
            glEnd();
        glPopMatrix();

        glPushMatrix();
         glTranslatef(-Cross2[0]+Coords1[0], -Cross2[1]+Coords1[1], -Cross2[2]+Coords1[2]);

        glBegin(GL_LINE_STRIP);
              glColor3fv( fColor );
              glVertex3f(0.0, 0.0, 0.0);
              glVertex3fv( midPoint );
              glColor3fv( tColor );
              glVertex3fv( tmp1 );
            glEnd();
        glPopMatrix();
      }
    }
    //glEnable(GL_LIGHTING);
   
}



void molView::renderAtom(float radius, atom *AT, ATOMRENDER at) {
  float *Coords = AT->fCoords;

  if(at == PNT) {
    //glColor3f(1.0, 1.0, 1.0);
    glColor3fv(&AT->COLOR[0]);
    glBegin(GL_POINTS);
      glVertex3fv(Coords);
    glEnd();
    
    //Funky litte code snippet that makes the selected atoms show
    //as wire from spheres
    /*
    if (AT->isSelected() == true) {
      gluQuadricDrawStyle(quadObj, GLU_LINE);
      glPushMatrix();
         glEnable(GL_LIGHTING);
         glTranslatef(AT->fCoords[0], AT->fCoords[1], AT->fCoords[2]);
         gluSphere(quadObj, 0.25, 4, 4);
      glPopMatrix();
      gluQuadricDrawStyle(quadObj, GLU_FILL);
    }
    */
    
  }
  else if (at == BALL) {
      if (glIsEnabled(GL_LIGHTING) == false) {
        glEnable(GL_LIGHTING);
      }
     glColor3fv(&AT->COLOR[0]);
    glPushMatrix();
      glTranslatef(Coords[0], Coords[1], Coords[2]);
      glScalef(radius, radius, radius);
      glCallList(ballSphere);
    glPopMatrix();
  }
  else if(at == CPK) {
    if (glIsEnabled(GL_LIGHTING) == false) {
        glEnable(GL_LIGHTING);
    }
    glPushMatrix();
    glColor3fv(&AT->COLOR[0]);
    radius = AT->getRadii();
      glTranslatef(Coords[0], Coords[1], Coords[2]);
      glScalef(radius, radius, radius);
      glCallList(cpkSphere);
      //gluSphere(wireObj, 1.0, sphSlices, sphStacks);
      //glDisable(GL_BLEND);
    glPopMatrix();
  }
  glColor3f(0.0, 0.0, 0.0);
}

void molView::setCenter(vector<float> &center) {
  xCenter = center[0];
  yCenter = center[1];
  zCenter = center[2];
}

float molView::distance(vector<double> vec1) {
  float distance = 0;
  for (unsigned int i=0; i<vec1.size(); i++) {
    distance += vec1[i]*vec1[i];
  }

  return sqrt(distance);
}

//This method is going to be obsolete
float molView::distance(vector<double> vec1, vector<double> vec2) {
  float distance = 0;
  for (unsigned int i=0; i<vec1.size(); i++) {
    distance += (vec1[i]-vec2[i])*(vec1[i]-vec2[i]);
  }

  return sqrt(distance);
}

float molView::distance(vector<float> vec1, vector<float> vec2) {
  float distance = 0;
  for (unsigned int i=0; i<vec1.size(); i++) {
    distance += (vec1[i]-vec2[i])*(vec1[i]-vec2[i]);
  }

  return sqrt(distance);
}

vector<double> molView::crossProduct(vector<double> &vec1, vector<double> &vec2) {
  //Safety code.  Shouldn't hurt performance enought o need removal
  if (vec1.size() != 3 || vec2.size() != 3) {
    exit(0);
  }

  vector<double> returnVec;
  returnVec.resize(3);

  returnVec[0] = vec1[1]*vec2[2] - vec1[2]*vec2[1];
  returnVec[1] = -(vec1[0]*vec2[2] - vec1[2]*vec2[0]);
  returnVec[2] = vec1[0]*vec2[1] - vec1[1]*vec2[0];
  return returnVec;
}

vector<double> molView::normalize(vector<double> &vec1) {
  vector<double> norm;
  norm.resize(vec1.size());
  double len = 0;

  for (unsigned int i=0; i<vec1.size(); i++) {
    len += vec1[i]*vec1[i];
  }
  len = sqrt(len);
  for (unsigned int i=0; i<vec1.size(); i++) {
    norm[i] = vec1[i]/len;
  }

  return norm;
}


float molView::length(vector<double> &p1, vector<double> &p2) {
  float a = p2[0]-p1[0];
  float b = p2[1]-p1[1];
  float c = p2[2]-p1[2];
  return sqrt( (a*a) + (b*b) + (c*c));
}

float molView::length(float *p1, float *p2) {
  
  float a = p2[0]-p1[0];
  float b = p2[1]-p1[1];
  float c = p2[2]-p1[2];

  return sqrt( (a*a) + (b*b) + (c*c));
  
  //return sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]) + (p2[2]-p1[2])*(p2[2]-p1[2]));
}


float molView::length(vector<float> &p1, vector<float> &p2) {
   return sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]) + (p2[2]-p1[2])*(p2[2]-p1[2]));
}

void molView::keyPressEvent( QKeyEvent  *e ) {

    if (e->state() == ControlButton && e->key() == Key_A) {
      if (renList->size() != 0) {
        molIterator = renList->begin();
        while (molIterator != renList->end()) {
          molecule *mol = *molIterator;
          mol->setSelected(true, true);
          mol->getItem()->setSelected(true);
          molIterator++;
        }
      }
      updateGL(); //update the molView contentd
      emit selectionChanged();  //update the molListView Contents
      return;
  }
  
}

void molView::update() {updateGL();}


void  molView::selectObjects(int &xInt, int &yInt, float &xFloat, float &yFloat, button_state shiftState, button_state ctrlState) {
	//////qDebug("molView::selectObjects");   
  if (shiftState == DOWN) {
  }
  if (ctrlState == DOWN) {
  }

  //Very important line.  This is responsible for saving the screen image.
  //updateGL();
  bitBlt(saveState, 0, 0, this, 0, 0, this->width(), this->height());
  updateGL();
  
  boxBeginX = xInt;
  boxBeginY = yInt;
  boxEndX = boxBeginX;
  boxEndY = boxBeginY;
 
}

void  molView::selectFullMol(int &x, int &y, float &xFloat, float &yFloat, button_state state) {
 doubleClick = true;
 selFullMol = true;
 //////qDebug("Mouse was double clicked");

}

void  molView::selectBox(int &newX, int &newY, float &newXFloat, float &newYFloat, button_state shiftState) {
  boxEndX = newX; boxEndY=newY;
  QPainter p( this );

  p.setPen( Qt::blue );
  int width = boxEndX-boxBeginX;
  int height = boxEndY-boxBeginY;
  if (width > 7 || height > 7 || width < 7 || height < 7) {
    bitBlt(this, 0, 0, saveState, 0, 0, this->width(), this->height(),  CopyROP);
    p.drawRect(boxBeginX, boxBeginY, width, height);
  }

  glInitNames();
}

void molView::buildMenu(double &posX, double &posY, double &posZ, int &xInt, int &yInt, float &xFloat, float &yFloat, button_state shiftState, button_state ctrlState) {
   sweepPickSelect(xInt, yInt, xFloat, yFloat, shiftState, ctrlState);
   float  pickCenterX, pickCenterY, pickWidth, pickHeight;

  int width = this->width();
  int height = this->height();

  if (boxEndY == boxBeginY && boxEndX == boxBeginX) {
     pickCenterX = xInt;
     pickCenterY = yInt;
     pickWidth = 15.0;    //was 9
     pickHeight = 15.0;  // was 9
  }  else {
     if (boxEndX > boxBeginX ) {
        pickWidth = boxEndX-boxBeginX;
     }  else {
        pickWidth = boxBeginX-boxEndX;
     }

     if (boxEndY > boxBeginY) {
        pickHeight =boxEndY-boxBeginY;
     }  else {
        pickHeight = boxBeginY-boxEndY;
     }


    //This code keeps it ffrom selecting the whole molecule on accident.
    if (pickWidth < 2 || pickHeight <2) {
      return;
    }

    if (boxBeginX < boxEndX ) {
       pickCenterX = boxBeginX+(pickWidth)/2;
    } else {
       pickCenterX = boxEndX+(pickWidth)/2;
    }

    if (boxBeginY < boxEndY) {
       pickCenterY = boxBeginY+(pickHeight)/2;
    }  else {
       pickCenterY = boxEndY+(pickHeight)/2;
    }

  }


   GLdouble winX, winY, winZ;


   winX = (float)pickCenterX;
   winY = (float)vPort[3] - (float)pickCenterY;
   glReadPixels( pickCenterX, pickCenterY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
   gluUnProject( winX, winY, 0.0, mvMatrix, projMatrix, vPort, &posX, &posY, &posZ);

   float DIST = 100000;
   GLdouble newWinX, newWinY, newWinZ;
   for (molIterator = this->renList->begin(); molIterator != this->renList->end(); molIterator++) {
     molecule *mol=*molIterator;
     int selCount = 0;
     atom *atm = NULL;
     for (int i=0; i<mol->atoms.size(); i++) {
        float *cd = mol->atoms[i]->fCoords;  
        if (mol->atoms[i]->isSelected()) {
         selCount++;
         atm = mol->atoms[i];
        }
        vector<float> vec1(4);
   
        float a = cd[0] - posX;
        float b = cd[1] - posY;
        
        float dist = sqrt(a*a + b*b);
        if (dist < DIST) {
          DIST = dist;
          posZ = cd[2];
          gluProject(cd[0], cd[1], cd[2], mvMatrix, projMatrix, vPort, &newWinX, &newWinY, &newWinZ);
        }
     }
     
     if (selCount == 1) {
      float *cd = atm->fCoords;
      gluProject(cd[0], cd[1], cd[2], mvMatrix, projMatrix, vPort, &winX, &winY, &newWinZ);
     }

   }
   gluUnProject( winX, winY, newWinZ, mvMatrix, projMatrix, vPort, &posX, &posY, &posZ);
}

void molView::sweepPickSelect(int &xInt, int &yInt, float &xFloat, float &yFloat, button_state shiftState, button_state ctrlState) {
   #ifdef LINUX
      grabMouse(); 
   #endif

   float  pickCenterX, pickCenterY, pickWidth, pickHeight;

   int width = this->width();
   int height = this->height();
  
   if (boxEndY == boxBeginY && boxEndX == boxBeginX) {
      pickCenterX = xInt;
      pickCenterY = yInt;
      pickWidth = 15.0;    //was 9
      pickHeight = 15.0;  // was 9
   }  else {
      if (boxEndX > boxBeginX ) {
         pickWidth = boxEndX-boxBeginX;
      }  else {
         pickWidth = boxBeginX-boxEndX;
      }

      if (boxEndY > boxBeginY) {
         pickHeight =boxEndY-boxBeginY;
      }  else {
         pickHeight = boxBeginY-boxEndY;
      }


      //This code keeps it ffrom selecting the whole molecule on accident.
      if (pickWidth < 2 || pickHeight <2) {
         return;
      }

      if (boxBeginX < boxEndX ) {
         pickCenterX = boxBeginX+(pickWidth)/2;
      } else {
        pickCenterX = boxEndX+(pickWidth)/2;
      }

      if (boxBeginY < boxEndY) {
         pickCenterY = boxBeginY+(pickHeight)/2;
      }  else {
         pickCenterY = boxEndY+(pickHeight)/2;
      }

   }

   ribbonDisplay = 0;   //This controls weather || not the ribbon model is displayed
  
   int test =0;
   const int bufferSize = 50000;
   GLuint selectBuf[bufferSize];
   GLint hits, viewport[4];
   glGetIntegerv(GL_VIEWPORT, viewport);
   glSelectBuffer(bufferSize, selectBuf);
   glRenderMode(GL_SELECT);
   renderMode = GL_SELECT; //set the molView draw mode to GL_SELECT...This is so that we render the atoms different...with names && such
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
      glLoadIdentity();
      gluPickMatrix((GLdouble)(pickCenterX), (GLdouble)(viewport[3]-pickCenterY), pickWidth, pickHeight, viewport);
      glOrtho(-width/zTrans, width/zTrans, -height/zTrans, height/zTrans, -100.0, 200.0);
      render(listOfMols);
      glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   renderMode = GL_RENDER;
   hits = glRenderMode(GL_RENDER);
   ribbonDisplay = 1; //This controls weather || not the ribbon model is displayed
   if (distMode || delDistMode) {
      picker->distPicks(hits, selectBuf);
   }
   else
   if (angMode || delAngMode) picker->angPicks(hits, selectBuf);
   else
   if (torsionMode || delTorsionMode) picker->torsionPicks(hits, selectBuf);
   else {
      picker->processHits(hits, selectBuf, shiftState, ctrlState); 
   }
   updateGL();
   bitBlt(saveState, 0, 0, this, 0, 0, width, height);
   listView->selQueue.clear();
   QListViewItemIterator it( listView );
   while ( it.current() ) {
      molListViewItem *item = dynamic_cast<molListViewItem *>(it.current());
      if (item->isSelected()) listView->selQueue.push_back(item);
      it++;
   }
   emit selectionChanged();
    
   glInitNames();
   
   #ifdef LINUX
      releaseMouse(); 
   #endif
}


void molView::delInterMolDist(atom *atm1, atom *atm2) {
  vector< vector<atom*> >::iterator itRem = interMolDist.begin();
  //for (itRem = dist.begin(); itRem != dist.end(); itRem++) {
  for (int i=0; i<interMolDist.size(); i++) {
      if (interMolDist[i][0] == atm1 && interMolDist[i][1] == atm2) {interMolDist.erase(itRem+i); return;}
      if (interMolDist[i][1] == atm1 && interMolDist[i][0]== atm2) {interMolDist.erase(itRem+i); return;}
  }
}

void molView::delInterMolAng(atom *atm1, atom *atm2, atom *atm3) {
  vector< vector<atom*> >::iterator itRem = interMolAng.begin();
  //for (itRem = dist.begin(); itRem != dist.end(); itRem++) {
  for (int i=0; i<interMolAng.size(); i++) {
      if (interMolAng[i][0] == atm1 && interMolAng[i][1] == atm2 && interMolAng[i][2] == atm3) {interMolAng.erase(itRem+i); return;}
      if (interMolAng[i][0] == atm1 && interMolAng[i][2] == atm2 && interMolAng[i][1] == atm3) {interMolAng.erase(itRem+i); return;}
      if (interMolAng[i][1] == atm1 && interMolAng[i][2] == atm2 && interMolAng[i][0] == atm3) {interMolAng.erase(itRem+i); return;}
      if (interMolAng[i][1] == atm1 && interMolAng[i][0] == atm2 && interMolAng[i][2] == atm3) {interMolAng.erase(itRem+i); return;}
      if (interMolAng[i][2] == atm1 && interMolAng[i][0] == atm2 && interMolAng[i][1] == atm3) {interMolAng.erase(itRem+i); return;}
      if (interMolAng[i][2] == atm1 && interMolAng[i][1] == atm2 && interMolAng[i][0] == atm3) {interMolAng.erase(itRem+i); return;}
  }
}

//Need to finish this method
void molView::delInterMolTorsion(atom *atm1, atom *atm2, atom *atm3, atom *atm4) {
  vector< vector<atom*> >::iterator itRem = interMolTor.begin();

  for (int i=0; i<interMolTor.size(); i++) {
    int match = 0;
    for (int j=0; j<4; j++) {
      if (interMolTor[i][j] == atm1) match++;
      else if (interMolTor[i][j] == atm2) match++;
      else if (interMolTor[i][j] == atm3) match++;
      else if (interMolTor[i][j] == atm4) match++;
    }
    if (match == 4) {interMolTor.erase(itRem+i); return;}
  }
}

void molView::renderMols(vector<molecule *> &molList) {
   ///QMutex mutex;
   //mutex.lock();
   renList->clear();
   for (int i=0; i<molList.size(); i++) {
      renList->push_back(molList[i]);
   }
   //mutex.unlock();
}

void molView::setMolList(list<molecule *> *renList) {
  QMutex mutex;
  mutex.lock();
  if (renList->size() == 0) {
    updateGL();
    return; 
  }
  //Clear distances, angles && torsions measures
  interMolDist.clear();
  interMolTor.clear();
  interMolAng.clear();
  
  this->renList = renList;
  list<molecule *>::iterator it;
  it = renList->begin();
  molecule *tmpMol;
  setCenter(this->renList);
  //Clear the lable vectors
  Labels.clear();
  labelAtoms.clear();
  
  /** This section will clear the infoText stuff */
  infoText.clear();
  render(listOfMols);
  updateGL();
  mutex.unlock();
}

void  molView::setRenderType(BONDRENDER bondType, ATOMRENDER atomType) {
  //First thing we do is check to see if any atoms are selected
    //If their are atoms selected then we only apply the transformation to those atoms
    list<molecule *>::iterator molIterator;
    int selectCount = 0;
    for (molIterator = renList->begin(); molIterator != renList->end(); molIterator++) {
      molecule *tmp = *molIterator;
      for (int i=0; i<tmp->bonds.size(); i++) {
        bond *bd = tmp->bonds[i];
        int tmpCount = 0;
        if (bd->from->isSelected() == true) {
          tmpCount++;
          selectCount++;
          bd->from->renderType = atomType;
        }
        if (bd->to->isSelected() == true) {
          tmpCount++;
          bd->to->renderType = atomType;
        }
        if (tmpCount == 2) {
          bd->renderType = bondType;
        }
      }
      for (int i=0; i<tmp->atoms.size(); i++) {
          atom *atm = tmp->atoms[i];
          if (atm->isSelected() == true) {
              atm->renderType = atomType;
              selectCount++;
          }
      }
    }

    if (selectCount == 0) {
      for (molIterator = renList->begin(); molIterator != renList->end(); molIterator++) {
          molecule *tmp = *molIterator;
          for (int i=0; i<tmp->bonds.size(); i++) {
              bond *bd = tmp->bonds[i];
              bd->renderType = bondType;
              bd->to->renderType = atomType;
              bd->from->renderType = atomType;
          }
          
          for (int i=0; i<tmp->atoms.size(); i++) {
              atom *atm = tmp->atoms[i];
              atm->renderType = atomType;
          }
      }
    } else {
      return;
    }

    render(*renList);
    updateGL();
}
void  molView::setDisplay(DISPLAY_TYPE dispType) {
  int all_disp = 3;
  int hyd_disp = 3;
  int sc_disp = 3;
  int bb_disp = 3;
  int selected_disp = 3;
  int ribbonHide = 0;

  if (dispType == HIDE_ALL) {
    all_disp = 0;
  } else if (dispType == SHOW_ALL) {      //show all the atoms
    all_disp = 1;
  } else if (dispType == HIDE_HYDROGEN) {  //Hide the hydrogens
    hyd_disp = 0;
  } else if (dispType == SHOW_HYDROGEN) {  //show the hydrogens
    hyd_disp = 1;
  } else if (dispType == HIDE_SIDE_CHAIN) { //hide the side chains
    sc_disp = 0;
  } else if (dispType == SHOW_SIDE_CHAIN) { //show the side chains
    sc_disp = 1;
  } else if (dispType == HIDE_BACKBONE) {  //hide the backbone
    bb_disp = 0;
  } else if (dispType == SHOW_BACKBONE) {  //show the backbone
    bb_disp = 1;
  } else if (dispType == HIDE_SELECTED) { //hide the selected atoms
    selected_disp = 0;
  }  else if (dispType == HIDE_RIBBON) {
     ribbonHide = 1;
  }

  list<molecule *>::iterator molIterator;
  if (all_disp != 3) {
    for (molIterator = renList->begin(); molIterator != renList->end(); molIterator++) {
        molecule *tmp = *molIterator;
        for (int i=0; i<tmp->atoms.size(); i++) {
            atom *atm = tmp->atoms[i];
            atm->display = all_disp;
       }
    }
  } else if (hyd_disp != 3) {
    for (molIterator = renList->begin(); molIterator != renList->end(); molIterator++) {
        molecule *tmp = *molIterator;
        for (int i=0; i<tmp->atoms.size(); i++) {
            atom *atm = tmp->atoms[i];
            
            if (atm->getAtomicNum() == 1) {
              atm->display = hyd_disp;
            }
       }
    }
  } else if (sc_disp != 3) {
     //THIS IS WERE THE SIDE CHAIN STUFF WILL GO.
     for (molIterator = renList->begin(); molIterator != renList->end(); molIterator++) {
        molecule *tmp = *molIterator;
        for (int i=0; i<tmp->atoms.size(); i++) {
            atom *atm = tmp->atoms[i];
            if (atm->protType == SIDE_CHAIN) {
              atm->display = sc_disp;
            }
        }
     }
  } else if (bb_disp != 3) {
     for (molIterator = renList->begin(); molIterator != renList->end(); molIterator++) {
        molecule *tmp = *molIterator;
        for (int i=0; i<tmp->atoms.size(); i++) {
            atom *atm = tmp->atoms[i];
            if (atm->protType == BACKBONE) {
              atm->display = bb_disp;
            }
        }
     }
  } else if (selected_disp != 3) {
     for (molIterator = renList->begin(); molIterator != renList->end(); molIterator++) {
        molecule *tmp = *molIterator;
        for (int i=0; i<tmp->atoms.size(); i++) {
            atom *atm = tmp->atoms[i];
            if (atm->isSelected() == true) {
              atm->display = selected_disp;
            }
        }
     }
  } else if (ribbonHide == 1) {
    for (molIterator = renList->begin(); molIterator != renList->end(); molIterator++) {
        molecule *tmp = *molIterator;
        if (mol->rtti() == 13) {
          chain *ch = dynamic_cast<chain *>(mol);
          if (ch->rib != NULL) {
            delete ch->rib;
            ch->rib = NULL;
            glDeleteLists(ch->ribList, 1);
            ch->ribList  = -1;
          }  
        } else if (mol->rtti() == 14) {
          protein *prot = dynamic_cast<protein *>(mol);
          for (int i=0; i<prot->chains.size(); i++) {
            chain *ch = prot->chains[i];
            if (ch->rib != NULL) {
              delete ch->rib;
              ch->rib = NULL;
              glDeleteLists(ch->ribList, 1);
              ch->ribList  = -1;
            }  
          }
        } else {
          return;
        }
        
     }
    }  

  updateGL();
}

void  molView::defineRibbon(RIBBON_TYPE type) {
  chain *ch;
  protein *prot;

  //I think that eventualy you will want to make the ribbon::ribbon() function
  //actually be responsible for sending the appropriate request to the correct funtion.
  //for example ribbon::cartoon()  || ribbon::flat()
  list<molecule *>::iterator molIter;
  for (molIter = renList->begin(); molIter != renList->end(); molIter++) {
    molecule *mol = *molIter;
    if (mol->rtti() == 13) {
      ch = dynamic_cast<chain *>(mol);

      //Check for old ribbon object && delete it if it exsists.
      if (ch->rib != NULL) { 
         delete ch->rib;
	 ch->rib = NULL;
      }
      
      //Now Delete the display list object as well
      if ( glIsList(ch->ribList) ) {
        glDeleteLists(ch->ribList, 1);
      }
      ch->ribList = -1;
      new ribbon(ch, type);
      
    } else if (mol->rtti() == 14) {     //REPEAT ALL OF THE ABOVE BUT FOR PROTEINS...WELL EACH CHAIN IN THE PROTEIN
      prot = dynamic_cast<protein *>(mol);
      for (int i=0; i<prot->chains.size(); i++) {
        ch = prot->chains[i];
	if (ch->rib != NULL) {
          delete ch->rib;
	  ch->rib = NULL;
	}
        if ( glIsList(ch->ribList) ) {
          glDeleteLists(ch->ribList, 1);
        }
        ch->ribList = -1;
        //new ribbon(ch);
        new ribbon(ch, type);
      }
    }    
  }
}

void molView::drawRibbon(chain *ch) {
 if (glIsEnabled(GL_LIGHTING) == false) {
      glEnable(GL_LIGHTING);
 }

  glPushMatrix();
    glEnable(GL_AUTO_NORMAL);

    glDisable(GL_LIGHT1);   //disable the normal lighting
    glEnable(GL_LIGHT2);    //turn on the ribbon lighting
    glDisable(GL_CULL_FACE);
    //glShadeModel(GL_FLAT);

    //GLfloat mat_shininess[] = {5};
    //float mat_ribbon_shininess[] = {5.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_ribbon_shininess);

  
    //int gridSize = 12;
    //int order = 4;
    int vOrder = ch->rib->vOrder;
    int uOrder = ch->rib->uOrder;
    ribbon *rib = ch->rib;
    //int knotSize = ch->rib->allGuidePoints.size()+order;
    int uKnotSize = rib->uKnots.size();
    int vKnotSize = rib->vKnots.size();
   //glColor3f(0.0, 1.0, 0.0);
    gluBeginSurface(pNurb);
       gluNurbsSurface(pNurb, uKnotSize, &rib->uKnots[0], vKnotSize, &rib->vKnots[0], 
                       vOrder*4, 4, &rib->colors[0], uOrder, vOrder, GL_MAP2_COLOR_4);

       gluNurbsSurface(pNurb, uKnotSize, &rib->uKnots[0], vKnotSize, &rib->vKnots[0], 
                       vOrder*3, 3, &rib->seg[0], uOrder, vOrder, GL_MAP2_VERTEX_3);
    gluEndSurface(pNurb);

    glDisable(GL_LIGHT2); //This light is only used for the ribbon models
    glEnable(GL_LIGHT1); //turn normal lighting back on
    glDisable(GL_AUTO_NORMAL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess); //reset the material properties
  glPopMatrix();
}

void molView::slotLabelDone() {
   //QMessageBox::critical(0, "dynamol", "slotLabelDone");
   slotApplyLables();
   delete lDialog;
}
void molView::slotApplyLables() {
   //QMessageBox::critical(0, "dynamol", "slotApplyLables");
   Labels.clear();
   labelAtoms.clear();
   for (molIterator = this->renList->begin(); molIterator != this->renList->end(); molIterator++) {
      mol=*molIterator;
      for (int i=0; i<mol->atoms.size(); i++) {
         atom *tmpAtm = mol->atoms[i];
         if (tmpAtm->isSelected()) {
            bool comma = false;
            //Res name section
            QString lab;
            if (lDialog->resName->isChecked()) {
               molecule *mol = dynamic_cast<molecule *>(tmpAtm->getParent());
               QString tmp = mol->getName();
               lab.append(tmp);
               comma = true;
            }
            //Residue num  section
            if (lDialog->resNum->isChecked()) {
               QString tmp;
	       molecule *mol = dynamic_cast<molecule *>(tmpAtm->getParent());
               tmp.setNum(mol->getNum());
               if (comma) {
                  lab.append(", ");
                  lab.append(tmp);
               } else {
                  lab.append(tmp);
               }
               comma = true;
            }
		
            //Atom Symbol
            if (lDialog->symbol->isChecked()) {
               QString tmp = tmpAtm->getSym();
               if (comma) {
                  lab.append(", ");
		   lab.append(tmp);
               } else {
                  lab.append(tmp);
               }
               comma = true;		
            }
		
            //Atom Num
            if (lDialog->atomNum->isChecked()) {
               QString tmp;
               tmp.setNum(tmpAtm->getNum());
               if (comma) {
                  lab.append(", ");
                  lab.append(tmp);
               } else {
                  lab.append(tmp);
               }		
               comma = true;
            }
		
            //Atom Charge
            if (lDialog->charge->isChecked()) {
               QString tmp;
               tmp.setNum( tmpAtm->getCharge() );
               if (tmp[0] == '-') tmp.truncate(5);
               else tmp.truncate(4);
		   
               if (comma) {
                  lab.append(", ");
                  lab.append(tmp);
               } else {
                  lab.append(tmp);
               }		
               comma = true;
            }
		
            //Atom FF type
            if (lDialog->type->isChecked()) {
               QString tmp = tmpAtm->getFFType();
               if (comma) {
                  lab.append(", ");
                  lab.append(tmp);
               } else {
                  lab.append(tmp);
               }		
               comma = true;
            }
            
            if (lDialog->custom->isChecked()) {
               QString tmp = lDialog->customEdit->text();
               if (comma) {
                  lab.append(", ");
                  lab.append(tmp);
               } else {
                  lab.append(tmp);
               }		
               comma = true;
            }
            tmpAtm->label = lab;
            Labels.push_back(lab);
            labelAtoms.push_back(tmpAtm);
         }
      }
       
      
   }
   
   QString ls; ls.setNum(Labels.size());
   //QMessageBox::critical(0, "dynamol", ls);
   QString ls1; ls1.setNum(labelAtoms.size());
   //QMessageBox::critical(0, "dynamol", ls1);
   updateGL();
}

void molView::setLabels() {
  lDialog = new labelDialog(0, "Label_Dialog", true, 0);
  connect(lDialog->apply, SIGNAL(clicked()), this, SLOT(slotApplyLables()));
  connect(lDialog->buttonOk, SIGNAL(clicked()), this, SLOT(slotLabelDone()));
  connect(lDialog->clear, SIGNAL(clicked()), this, SLOT(slotApplyLables()));
  lDialog->show();
}



void molView::getCurrentMolList(list<molecule *> &molList) {
   for (molIterator = this->renList->begin(); molIterator != this->renList->end(); molIterator++) {
       mol=*molIterator;
       molList.push_back(mol);
   }  
}

void molView::addNewDistance() {
  distSelCounter = 0;
  setCursor(QCursor(Qt::CrossCursor));
  distMode = true; 
  delDistMode = false;
  angMode = false;
  delAngMode = false;
  torsionMode = false;
  delTorsionMode = false;
  glInitNames();
}


void molView::delDistance() {
  distSelCounter = 0;
  setCursor(QCursor(Qt::CrossCursor));
  distMode = false;
  delDistMode = true;
  angMode = false;
  delAngMode = false;
  torsionMode = false;
  delTorsionMode = false;
  glInitNames();
}

void molView::delAllDistances() {
  for (molIterator = this->renList->begin(); molIterator != this->renList->end(); molIterator++) {
       mol=*molIterator;
       mol->dist.clear();
   }

   //clear the interMolDist as well
   setCursor(QCursor(Qt::CrossCursor));
   distSelCounter = 0;
   setCursor(QCursor(Qt::ArrowCursor) );
   interMolDist.clear();
   updateGL();
}

void  molView::addNewAngle() {
  angSelCounter = 0;
  setCursor(QCursor(Qt::CrossCursor));
  angMode = true;
  delAngMode = false;
  distMode = false;
  delDistMode = false;
  torsionMode = false;
  delTorsionMode = false;
  glInitNames();
}


void molView::delAngle() {
  angSelCounter = 0;
  setCursor(QCursor(Qt::CrossCursor));
  angMode = false;
  delAngMode = true;
  distMode = false;
  delDistMode = false;
  torsionMode = false;
  delTorsionMode = false;
  glInitNames();
}


void molView::delAllAngles() {
  for (molIterator = this->renList->begin(); molIterator != this->renList->end(); molIterator++) {
       mol=*molIterator;
       mol->ang.clear();
   }

   //clear the interMolDist as well
   setCursor(QCursor(Qt::CrossCursor));
   angSelCounter = 0;
   setCursor(QCursor(Qt::ArrowCursor) );
   interMolAng.clear();
   updateGL();
}

void molView::addNewTorsion() {
  torsionSelCounter = 0;

  setCursor(QCursor(Qt::CrossCursor));
  angMode = false;
  delAngMode = false;
  distMode = false;
  delDistMode = false;
  torsionMode = true;
  delTorsionMode = false;
  glInitNames();
}

void molView::delTorsion() {
  torsionSelCounter = 0;
 
  setCursor(QCursor(Qt::CrossCursor));
  angMode = false;
  delAngMode = false;
  distMode = false;
  delDistMode = false;
  torsionMode = false;
  delTorsionMode = true;
  glInitNames(); 
}

void molView::delAllTorsions() {
  //First clear the intra-molecular torsions
  for (molIterator = this->renList->begin(); molIterator != this->renList->end(); molIterator++) {
       mol=*molIterator;
       mol->tor.clear();
   }

  //now clear the interMolTorsion as well    
   setCursor(QCursor(Qt::CrossCursor));
   torsionSelCounter = 0;
   setCursor(QCursor(Qt::ArrowCursor) );
   interMolTor.clear();
   updateGL();
}


void molView::energyUpdate() {
	updateGL();
}

void molView::stopAutoUpdate() {
   autoTime = false;
   timer->stop();
}

void molView::startAutoUpdate(int maxCycle) {
   autoTime = true;
   maxTimerIteration = maxCycle;
   timer->start( 150, TRUE );
} 

void molView::endAutoUpdate(dynoThread *) {
  autoTime = false;
}

void molView::timerDone() {
   static int count = 0;
   if (count  == 10000) {  
      count = 0;
   }
   count++;

   bitBlt(saveState, 0, 0, this, 0, 0, this->width(), this->height());
   updateGL();

   if (autoTime) timer->start(50, TRUE);
}

void molView::setInfoText(vector<string > &data) {
  if (infoText.size() != data.size()) {
      infoText.clear();
      infoText.resize(data.size());
   }

   for (int i=0; i<data.size(); i++) {
      infoText[i] = data[i];
   }

}

void molView::setInfoText(vector<QString> &data) {  
   if (infoText.size() != data.size()) {
      infoText.clear();
      infoText.resize(data.size());
   }
   for (int i=0; i<data.size(); i++) {
      infoText[i] = data[i].latin1();
   }
}

void molView::clearInfoText() {
   infoText.clear();
   updateInfoText();
}

void molView::updateInfoText() {
   updateGL();
}


void molView::enableFog(bool toggle) {
  if (toggle) glEnable(GL_FOG);
  else glDisable(GL_FOG);
}

void molView::getSelectedAtoms(vector<atom *> &ATOMS, bool all) {
list<molecule *>::iterator molIterator;
  molIterator = this->renList->begin();
  for (molIterator; molIterator != this->renList->end(); molIterator++) {
    molecule *mol = *molIterator;
    for (int i=0; i<mol->atoms.size(); i++) {
      atom *atm = mol->atoms[i];
      if (atm->isSelected()) ATOMS.push_back(atm);
    }
  }
  
  if (ATOMS.size() == 0 && all == true) { //Lets add all the atoms
     molIterator = this->renList->begin();
     for (molIterator; molIterator != this->renList->end(); molIterator++) {
       molecule *mol = *molIterator;
       for (int i=0; i<mol->atoms.size(); i++) {
         atom *atm = mol->atoms[i];
         ATOMS.push_back(atm);
       }
     }
  }
}


void molView::fixAtoms() {
   vector<atom *> atomsToFreeze;
   getSelectedAtoms(atomsToFreeze, true);
   for (int i=0; i<atomsToFreeze.size(); i++) {
      atomsToFreeze[i]->frozen = true;
   }
}

void molView::freeAtoms() {
   vector<atom *> atomsToFreeze;
   getSelectedAtoms(atomsToFreeze, true);
   for (int i=0; i<atomsToFreeze.size(); i++) {
      atomsToFreeze[i]->frozen = false;
   }
}

void molView::keyReleaseEvent(QKeyEvent *event) {
  
  int key = event->key();
  
  if (key == Key_Delete) {
    vector<atom *> selectedAtoms;
    getSelectedAtoms(selectedAtoms, true);
    currentSelection.clear();
    emit deleteAtoms(selectedAtoms);
  }

  Object::updateRegistry();
}

void 
molView::molSurface(float alpha, float res, string &colorType, 
                    float trans, float r, float g, float b, bool dir) 
{

   vector<atom *> ATOMS;
   getSelectedAtoms(ATOMS, true);
   if (ATOMS.size() == 0 ) 
      return; 
   
//   molecule *molToSurface = dynamic_cast<molecule *>(ATOMS[0]->getParent()); 
   list<molecule *>::iterator ri = renList->begin();
   molecule *molToSurface = *ri;
   //molToSurface->hideSurface(true);
 
   //Mol struct should be delete by the buildSurface module
   boost::shared_ptr<molStruct> ms( new molStruct );

   //molStruct *ms = new molStruct;
   int cdIndex, rIndex, clIndex;
   cdIndex = rIndex = clIndex = 0;
   for (int i=0; i<ATOMS.size(); i++) {
      atom *atm = ATOMS[i];
      float *cd = atm->fCoords;
      for (int j=0; j<3; j++) {
         ms->coords.push_back(cd[j]);
         cdIndex++;
      }
      for (int j=0; j<4; j++) {
         ms->color.push_back(atm->COLOR[j]);
         clIndex++;
      }
      ms->radii.push_back(atm->getRadii());
      ms->charge.push_back( atm->getCharge() );
      rIndex++;
   }

//   molecule *mol = renList

   surfacePoints.clear();

   buildSurface *s = new buildSurface(this);

   molToSurface->surf.reset( new surface );
   s->molSurfSetup(ms, molToSurface->surf, res, alpha, trans, colorType);

   s->setColor(r, g, b);
   s->start();
   
   //s->run();
   startAutoUpdate(-1);
}



void molView::addSphere(float x, float y, float z, float radius) {
   sphere *s = new sphere;
   s->center[0] = x;
   s->center[1] = y;
   s->center[2] = z;
   s->color[0] = 0.0;
   s->color[1] = 1.0;
   s->color[2] = 1.0;
   s->radius = radius;
   s->type = solid;
   SPHERES.push_back(s);
}

void molView::addSphere(float x, float y, float z, float radius, sphereType type, float r, float g, float b) {
   sphere *s = new sphere;
   s->center[0] = x;
   s->center[1] = y;
   s->center[2] = z;
   s->color[0] = r;
   s->color[1] = g;
   s->color[2] = b;
   s->radius = radius;
   s->type = type;
   SPHERES.push_back(s);
}

void molView::drawSpheres() {
   //cout <<"drawSpheres: " << endl;
   for (int i=0; i<SPHERES.size(); i++) {
      sphere *s = SPHERES[i];
      glColor3f(s->color[0], s->color[1], s->color[2]);
      //glColor3f(1.0, 0.0, 1.0);
      glPushMatrix();
         glTranslatef(s->center[0], s->center[1], s->center[2]);
         glScalef(s->radius, s->radius, s->radius);
         gluSphere(wireObj, 1, 10, 10);
         if (s->type == solid)
            glCallList(cpkSphere);
         if (s->type == wire)
            gluSphere(wireObj, 1, 10, 10);
      glPopMatrix();
   
   }
}

void molView::drawSurface(molecule *mol) {
   if (!mol->showSurface()) 
      return;

   //DELETE THIS SECTION
   /*
   glDisable(GL_LIGHTING);
   glPointSize(3);
    glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
		for (int i=0; i<mol->surf->verts.size(); i+=3) {
			glVertex3fv(&mol->surf->verts[i]);
		}
	glEnd();
	glEnable(GL_LIGHTING);
   return; 
   */
   //END DELETE SECTION

   // This First part checks to see if the surface is translucent
   // If it is a quick sort on the z Axis (after rotation by the mvMatrix)
   // is performed.  Right now  you are simple using the red-black tree
   // from the standard template library aka multimap.  To map depthe
   // with index.  You then update the surface vertex array's and you are off and running
   //
   // Couple of quick notes.  
   // 1)  Use a radix sort.  To lazy to program it now.
   // 2)  You should be able to use an index array to dramatically reduce the number
   //     of vertices.  Need to think about this.  It has the side benefit of  
   //     reducing the sort time as well as the render time.  Should probably work
   //     this out before the moving to a radix sort.

   
   if (mol->surf->color[3] != 1.0) {
      int vertSize = mol->surf->verts.size();
      vector<float> newVerts(vertSize);
      vector<float> newNorms(vertSize);
      vector<float> newColor(mol->surf->color.size());   

      multimap<float, int> vertMap;
      for (int i=0; i < vertSize; i+=9) {
         float *cd = &mol->surf->verts[i];
         float z = cd[0]*mvMatrix[2] + cd[1]*mvMatrix[6] + cd[2]*mvMatrix[10] + mvMatrix[14];
         pair<float, int> p(-z, i);
         vertMap.insert(p);
      }

      multimap<float, int>::iterator mi = vertMap.begin();
      int vertIndex = 0;
      int colorIndex = 0;
      for (mi; mi != vertMap.end(); mi++) {
         int index = mi->second;
         int cIndex = index + index/3;//colorCount;

         float *cd = &mol->surf->verts[index];
         float *ns = &mol->surf->norms[index];
         float *clr = &mol->surf->color[cIndex];

         for (int i=0; i<9; i++) {
            newVerts[vertIndex]   = cd[i];
            newNorms[vertIndex++] = ns[i];
         }
         for (int i=0; i<12; i++) {
            newColor[colorIndex++] = clr[i];
         }
      }
      mol->surf->verts = newVerts;
      mol->surf->norms = newNorms;
      mol->surf->color = newColor; 
   }
   

   glVertexPointer(3, GL_FLOAT, 0, &mol->surf->verts[0]);
   if (!mol->surf->singleColor) {
      glColorPointer(4, GL_FLOAT, 0, &mol->surf->color[0]);
   }
   glNormalPointer(GL_FLOAT, 0, &mol->surf->norms[0]);

   glColor4fv(&mol->surf->color[0]);

/*
   glBegin(GL_TRIANGLE_STRIP);
   for (int i=0; i<mol->surf->strips.size(); i++) {
      int size = mol->surf->strips[i].size();
      int *index = &mol->surf->strips[i][0];
      for (int j=0; j<size; j++) {
          glArrayElement(index[j]);
          cout <<index[j] <<" ";
      }
      cout << endl;
   }
   glEnd();
*/   
   glBegin(GL_TRIANGLES);
      int size = mol->surf->verts.size()/3;
      for (int i=0; i<size; i++) {
         glArrayElement(i);
      }
      
//      int size = mol->surf->indices.size();
//     int *index = &mol->surf->indices[0];
//      for (int i=0; i<size; i++) {
//         glArrayElement(index[i]);
//      }
   glEnd();


}

void  molView::buildModeSelect(int &xInt, int &yInt, float &xFloat, float &yFloat, button_state shiftState, button_state ctrlState) {
  double x, y, z;
  buildMenu(x, y, z, xInt, yInt, xFloat, yFloat, shiftState, ctrlState);
   molEdit->processRequest(x, y, z);
}

void molView::initBuildMode() {
   //Reset to initial view for building
   cout <<"Resetting the initial Matrix"<<endl;
/*   
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glMultMatrixf(&origMat[0]);
   int count = 0;
   for (int i=0; i<4; i++) {
      for (int j=0; j<4; j++) {
         cout << origMat[count] << "\t";
         count++;
      }
      cout << endl;
   }
  
//   xTrans = yTrans = zTrans = 0.0;
    startTransX = startTransY = 0;
   for (int i=0; i< 4; i++) {
      lastQuat[i] = 0;
      currentQuat[i] = 0;
   }

   initializeGL();
   updateGL();
*/

   float xx = 0.0;
   float yy = 0.0;
   int xi = 10000000;
   int yi = 10000000;
   selectObjects(xi, yi, xx, yy, UP, UP);
   //sweepPickSelect(xi, yi, xx, yy, UP, UP);
   setMouseTracking(true);
   bDialog = new builderDialog(this, "builder", true, 0);
   molEdit = new builder(this, "Editor");
   molEdit->setMolView(this);
   molEdit->setDialog(bDialog);
   
   connect(bDialog->Done, SIGNAL(clicked()), this, SLOT(buildDone()));
   //connect(dialog->buttonOk, SIGNAL(clicked()), this, SLOT(buildDone()));
   bDialog->show();
   //disconnect( SLOT(sweepPickSelect(int &, int &, float &, float &, button_state, button_state)), 0,this ));
   disconnect(this, SIGNAL(leftButtonRelease(int &, int &, float &, float &, button_state, button_state)), this, SLOT(sweepPickSelect(int &, int &, float &, float &, button_state, button_state)));
   disconnect(this, SIGNAL(leftButtonMove(int &, int &, float &, float &, button_state)),this, SLOT(selectBox(int &, int &, float &, float &, button_state)));
   disconnect(this, SIGNAL(leftButtonPress(int &, int &, float &, float &, button_state, button_state )),this, SLOT(selectObjects(int &, int &, float &, float &, button_state, button_state )));
   
   connect(this, SIGNAL(sendWorldCoords(double, double, double)),molEdit, SLOT(processRequest(double, double, double)));
   connect(this, SIGNAL(trackMouse(double &, double &, double &, int &, int &, float &, float &, button_state, button_state)), this, SLOT(buildMenu(double &, double &, double &, int &, int &, float &, float &, button_state, button_state)));
   connect(this, SIGNAL(leftButtonPressTracking(int &, int &, float &, float &, button_state, button_state)), this, SLOT(buildModeSelect(int &, int &, float &, float &, button_state, button_state)));
   
   molEditMode = true;
}

void molView::buildDone() {
  setMouseTracking(false);
  connect(this, SIGNAL(leftButtonRelease(int &, int &, float &, float &, button_state, button_state)), this, SLOT(sweepPickSelect(int &, int &, float &, float &, button_state, button_state)));
  connect(this, SIGNAL(leftButtonMove(int &, int &, float &, float &, button_state)),this, SLOT(selectBox(int &, int &, float &, float &, button_state)));
  connect(this, SIGNAL(leftButtonPress(int &, int &, float &, float &, button_state, button_state )),this, SLOT(selectObjects(int &, int &, float &, float &, button_state, button_state )));
  
  disconnect(this, SIGNAL(sendWorldCoords(double, double, double)),molEdit, SLOT(processRequest(double, double, double)));
  disconnect(this, SIGNAL(trackMouse(double &, double &, double &, int &, int &, float &, float &, button_state, button_state)), this, SLOT(buildMenu(double &, double &, double &, int &, int &, float &, float &, button_state, button_state)));
  disconnect(this, SIGNAL(leftButtonPressTracking(int &, int &, float &, float &, button_state, button_state)), this, SLOT(buildModeSelect(int &, int &, float &, float &, button_state, button_state)));
  
  delete bDialog;
  delete molEdit;
  
  molEditMode = false;
}

void molView::renderOff() 
{ render_on = false; }

void molView::renderOn()
{ render_on = true; }


































