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

#include <qmessagebox.h>
#include "qcheckbox.h"
#include <qpushbutton.h>
#include "qmutex.h"
//#include "qlineedit.h"

#include "molecule.h"
#include "atom.h"
#include "bond.h"
#include "dynapy.h"
#include <fstream>

#include <time.h>
using namespace std;



//BOOST Includes
#include <boost/shared_ptr.hpp>

namespace dynamol {

string molView::hello() {
	cout <<"Hello" << endl;
	return "molView::hello";
	/*
	return this->currMol;
	if (currMol) {
		cout <<"You are right here..address is: "<< this << endl;
		cout <<"currMol: " << this->currMol << endl;
		cout <<"currMol->name: " << this->currMol->name << endl;
	} else {
		cout <<"currMol is NULL"<<endl;
	}
	*/
};

molView::~molView() {
	// ### NOT A PORTABLE WAY TO REMOVE THIS FILE
	// ### USE THE QT LIBRARIED TO DO THIS:
	system("rm .molview_address.txt");
	cout <<"molView::~molView was called"<<endl;
}

molView::molView(QWidget *parent, char *name)
: molViewControl(parent)
{
	// ####### FIRST THING WE DO IS WRITE THE ADDRESS OF THE VIEWER TO A FILE ###
	ofstream outFile(".molview_address.txt", ios::out);
	outFile << this << endl;
	// ############## THIS FILE IS DELETED ONCE THE MOLVIEW IS CLOSED..

	quadObj = gluNewQuadric();
    wireObj = gluNewQuadric();

	SelectMode = false;	
	currMol = NULL;
	InitSetup();
	//initializeGL();
	xCenter = yCenter = zCenter = 0.0;
	centerX = centerY = centerZ = 0.0;

	fps = 0.0;

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(FPS_Slot()));

	connect(this, SIGNAL(midButtonSingleClick(int &, int &)), \
			this, SLOT(ReCenter(int &, int &)));


	// These Connections Are involved in Sweep Pick Selection 
	connect(this, SIGNAL(ShiftLeftButtonRelease(int, int, float, float)), \
			this, SLOT(SweepPickSelect(int, int, float, float)));

	connect(this, SIGNAL(ShiftLeftButtonMove(int, int, float, float)), \
			this, SLOT(selectBox(int, int, float, float)));

	connect(this, SIGNAL(ShiftLeftMousePress(int, int, float, float)), \
			this, SLOT(selectObjects(int, int, float, float)));


}

void  molView::selectObjects(int xInt, int yInt, float xFloat, float yFloat) {
	cout <<"molViewSelectObject"<<endl;
	//Very important line.  This is responsible for saving the screen image.
	//updateGL();
//	bitBlt(saveState, 0, 0, this, 0, 0, this->width(), this->height());
//	updateGL();
	saveState2 = renderPixmap();
	
	boxBeginX = xInt;
	boxBeginY = yInt;
	boxEndX = boxBeginX;
	boxEndY = boxBeginY;
	
}


void  molView::selectBox(int newX, int newY, float newXFloat, float newYFloat) {//, button_state shiftState) {
	cout <<"molView::selectBox:"<<endl;
  
  boxEndX = newX; boxEndY=newY;
  QPainter p( this );

  p.setPen( Qt::blue );
  int width = boxEndX-boxBeginX;
  int height = boxEndY-boxBeginY;
  if (width > 7 || height > 7 || width < 7 || height < 7) {
    //bitBlt(this, 0, 0, saveState, 0, 0, this->width(), this->height(),  CopyROP);
	//QWidget *aa = parent();
	//setPixmap(saveState2);
	//renderArea->setPixmap(saveState2);
	//render(&saveState2);
	saveState2.save("Image.png");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	p.drawPixmap( 0, 0, saveState2 );
    p.drawRect(boxBeginX, boxBeginY, width, height);
  }

  glInitNames();
  
}


void molView::SweepPickSelect(int x, int y, float scaledX, float scaledY) {
	cout <<"SweepPickSelect"<<endl;
	saveState2 = renderPixmap();
    saveState2.save("Image.png");

}
//This function is called when the middle 
//Mouse button is singleClicked
void molView::ReCenter(int &x, int &y) {
	startPicking(x, y);
	Render(currMol);
	stopPicking();

	currMol->BuildVertexArrays(WIRE, center);

	updateGL();
}

void molView::FPS_Slot() {
	//cout <<"fps: " << fps << endl;
	fps = 0;
}

void molView::Show(molecule *mol) {
	Mols.clear();
	if (mol->PyObject) {
		molecule *NewMol = new molecule(*mol);
		currMol = NewMol;
		Mols.clear();
	} else {
		currMol = mol;
		
	}
	
	Mols.push_back(currMol);

	float minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = 10000000;
	maxX = maxY = maxZ = -10000000;

	float totX, totY, totZ;
	totX = totY = totZ = 0.0;

	center = currMol->getCenter();
	//mol->CenterMol();

	for (int i=0; i<currMol->atoms.size(); i++) {
		atom *atm = currMol->atoms[i];
		float cd[3];		
		for (int j=0; j<3; j++) 
			cd[j] = atm->fCoords[j]-center[j];

		if (cd[0] < minX)
			minX = cd[0];
		if (cd[0] > maxX)
			maxX = cd[0];

		if (cd[1] < minY)
			minY = cd[1];
		if (cd[1] > maxY)
			maxY = cd[1];

		if (cd[2] < minZ)
			minZ = cd[2];
		if (cd[2] > maxZ)
			maxZ = cd[2];

	}

	
	//This Value can be used to manipulate the clipping plane like pymol
	zNear = +minZ-100;
	//This value Needs to be at least the size of the molecule
	//Right Now you assume the molecule is centered....Not sure this
	//is the best way 
	zFar = maxZ*4;
	//cout <<"zFar: " << zFar << endl;

	fogStart = 0.0;
	if (minZ < minX and minZ < minY) {
		fogEnd = minZ*3;
		zFar = maxZ*3;
	}
	else if (minY < minX and minY < minZ) {
		fogEnd = minY*3;
		zFar = maxY*3;
	}
	else if (minX < minY and minX < minZ) {
		fogEnd = minX*3;
		zFar = maxX*3;
	}
	zTrans = 0.035;
	fogTrans = minZ;
	float fogColor[4] = {0.0, 0.0, 0.0, 1.0f};
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_START, fogStart);
    glFogf(GL_FOG_END, fogEnd);
	glFogf(GL_FOG_DENSITY, 0.035f);
	glEnable(GL_FOG);

	//vector<float> center(3);
	//for (int j=0; j<3; j++)
	//	center[j] = 0.0;
	currMol->BuildVertexArrays(WIRE, center);
	Render(currMol);
	updateGL();
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glColorPointer(3, GL_FLOAT, 0, Colors)
	//glVertexPointer(3, GL_FLOAT, 0, &currMol->VertexArray[0]);
}

void molView::SetScripter(DynaPy *dynapy) {
	
	this->dynapy = dynapy;
	if (this->dynapy != 0) {
        //connect(dynapy->lineEdit, SIGNAL(returnPressed()), this, SLOT(RunScript()));
    }
	
}


void molView::InitSetup() {
	
	trackball(currentQuat, 0.0, 0.0, 0.0, 0.0);
    xTrans = yTrans = 0;
	zTrans = 0.035;
    xCenter = yCenter = zCenter = 0.0;
}

void molView::initializeGL() {
	//int test = 0;
	//cin >> test;
	//Setting initial ambient settings
	light_ambient.resize(4);
	light_ambient[0] = 0.75;
	light_ambient[1] = 0.75;
	light_ambient[2] = 0.75;
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
	light_position[1] = 1000;
	light_position[2] = 1000.0;
	light_position[3] = 1.0;

	//Initialize the background color to black
	bgColor.resize(3);
	for (int i=0; i<bgColor.size(); i++)
		bgColor[i] = 0.0;


	float mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	float mat_diffuse[] = {0.750, 0.750, 0.750, 1.0};

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
	//glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	//cout <<"INIT 2"<<endl;
	glLightfv(GL_LIGHT1, GL_AMBIENT, &light_ambient[0]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, &light_diffuse[0]);
	glLightfv(GL_LIGHT1, GL_POSITION, &light_position[0]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, &light_specular[0]);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glLightfv(GL_LIGHT3, GL_AMBIENT, &light_ambient[0]);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, &light_diffuse[0]);
	glLightfv(GL_LIGHT3, GL_POSITION, light1_position);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);


	//START AINTIALIASING STUFF
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//  glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1.5);
	//glEnable(GL_MULTISAMPLE_ARB);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT1);

}

/**	Method comes from the QGLWidget hierarchy && is called wherever the scene needs
	to be painted
*/ 
void molView::paintGL() {
	// THIS IS THE ORIGINAL DYNAMOL WAY
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(bgColor[0], bgColor[1], bgColor[2], 0.0);
	Render(currMol);
}

/**	Method comes from the QGLWidget hierarchy && is called whenever the window is resized
*/
void molView::resizeGL(int w, int h) {
	glViewport( 0, 0, (GLint)w, (GLint)h );
	//saveState2 = renderPixmap();
	//saveState2.save("Image.png");	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho(-width()*zTrans, width()*zTrans, -height()*zTrans,  height()*zTrans, zNear, zFar);
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

/** This function is used to update the graphis...basically it calls updateGL() */
void molView::update() {
	updateGL();
	Render(currMol);
}


/** This function takes a list of molecules to render as an argument  S
*/
void molView::Render(molecule *mol) {
	if (!mol) {
		cout <<"No Molecule to render"<<endl;
		return;
	}
	//saveState2 = renderPixmap();
    //saveState2.save("Image.png");
	fps++;
	if (!mol)
		return;

	float fogColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_START, fogStart);
	glFogf(GL_FOG_END, -fogEnd);
	glFogf(GL_FOG_DENSITY, 0.0035f);
	glEnable(GL_FOG);


	//static int COUNT = 0;
	//cout <<"xTrans-ytrans: " << xTrans <<"\t" << yTrans << endl;
	//glTranslatef(xTrans, yTrans, -5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glColor3f(0, 1, 0);
	//gluSphere(wireObj, 1, 10, 10);
	//gluLookAt(10, 0, 0, 0, 0, 0, 0, 1, 0);
	glTranslatef(-xTrans, -yTrans, fogTrans);

	glInitNames(); //just chekcing

	glPushMatrix();
	//glLoadIdentity();	

	GLfloat m[4][4];
	buildRotMat(m, currentQuat);
	glMultMatrixf(&m[0][0]);	

	//solidCylinder(double tx, double ty, double tz, double radius, double height, int n_subdivision_steps)
	//solidCylinder(1.2, -5.0, 2.3, 1.0, 10.0, 10);
	// ###### DRAW X,Y,Z Axis
	glPushName(9000);
	DrawCenterAxis();
	glPopName();
	// ####### END AXIS RENDER

	glGetDoublev( GL_MODELVIEW_MATRIX, mvMatrix );
	glGetDoublev( GL_PROJECTION_MATRIX, projMatrix );
	glGetIntegerv( GL_VIEWPORT, vPort );
	
	
	glEnable(GL_LIGHTING);
	glShadeModel(GL_FLAT);

	//Interesting Cyclinder Routine
	//solidCylinder(1.2, -5.0, 2.3, 1.0, 10.0, 10);



	if (glIsEnabled(GL_LIGHTING) == true) {
		glDisable(GL_LIGHTING);
	}
	

	if (!SelectMode) {
		glVertexPointer(3, GL_FLOAT, 0, &currMol->BondVertexArray[0]);
		glColorPointer(3, GL_FLOAT, 0, &currMol->BondColorArray[0]);
		glDrawArrays(GL_LINES, 0, currMol->BondArraySize);

		//glVertexPointer(3, GL_FLOAT, 0, &currMol->StickTriangleArray[0]);
		//glNormalPointer(GL_FLOAT, 0, &currMol->StickNormalArray[0]);
		//glColorPointer(3, GL_FLOAT, 0, &currMol->StickColorArray[0]);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, currMol->TriangleArraySize);
	}

	//if (SelectMode) {
	if (!SelectMode) { //Change Later
		glPushName(currMol->ObjectNum);
		glVertexPointer(3, GL_FLOAT, 0, &currMol->AtomVertexArray[0]);
		glColorPointer(3, GL_FLOAT, 0, &currMol->AtomColorArray[0]);
    	for (int i=0; i<currMol->AtomArraySize; i++) {
			glPushName(currMol->atoms[i]->ObjectNum);
			glBegin(GL_POINTS);
    	    glArrayElement(i);
			glEnd();
			glPopName();
    	}
		glPopName(); //Pop currMol->ObjectNum
	}	


	// THIS SECTION MAKES IT SO THAT YOU CAN ZOOM???
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(-width()*zTrans, width()*zTrans, -height()*zTrans,  height()*zTrans, zNear, zFar);
	//int test2 = 0;
	//cin >> test2;
}

void molView::DrawCenterAxis() {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-10, 0.0, 0.0);
	glVertex3f(10, 0.0, 1.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 10, 0.0);
	glVertex3f(0.0, -10, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 10.0);
	glVertex3f(0.0, 0.0, -10.0);
	glEnd();
 
}

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
		if (dbTemp != NULL) {
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
			
			glBegin(GL_LINES);
			glColor3fv(fColor);
			glVertex3f(Cross2[0]+Coords1[0], Cross2[1]+Coords1[1], Cross2[2]+Coords1[2]);
			glVertex3f(Cross2[0]+Coords2[0], Cross2[1]+Coords2[1],Cross2[2]+Coords2[2]);
			glVertex3f(-Cross2[0]+Coords1[0], -Cross2[1]+Coords1[1], -Cross2[2]+Coords1[2]);
			glVertex3f(-Cross2[0]+Coords2[0], -Cross2[1]+Coords2[1], -Cross2[2]+Coords2[2]);
			glEnd();
			/*		
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
			*/
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
	
	/*
	Coords1[0] = Coords1[0] - centerX;
	Coords1[1] = Coords1[1] - centerY;
	Coords1[2] = Coords1[2] - centerZ;

	Coords2[0] = Coords2[0] - centerX;
	Coords2[1] = Coords2[1] - centerY;
	Coords2[2] = Coords2[2] - centerZ;
	*/
	//glEnable(GL_LIGHTING);
}

void molView::colorMolecule(float r, float g, float b) {
	for (int i=0; i<currMol->atoms.size(); i++) {
		atom *atm = currMol->atoms[i];
		atm->COLOR[0] = r;
		atm->COLOR[1] = g;
		atm->COLOR[2] = b;
	}

	Show(currMol);
	updateGL();
}

void molView::SetFog(float start, float end, float trans) {
	fogStart = start;
	fogEnd = end;
	fogTrans = trans;
}
molecule *molView::getCurrentMol() 
{ return currMol; }

void molView::solidCylinder(double tx, double ty, double tz, double radius, 
		   double height, int n_subdivision_steps)
{
  int i,n;
  double theta, d_theta;
  double z_bottom,z_top;
  int MAX_NUM_SUBDIVISION = 1000;
  double px[MAX_NUM_SUBDIVISION],py[MAX_NUM_SUBDIVISION];
  double nx[MAX_NUM_SUBDIVISION],ny[MAX_NUM_SUBDIVISION];

  n = (n_subdivision_steps > MAX_NUM_SUBDIVISION) ? MAX_NUM_SUBDIVISION : n_subdivision_steps;
  
  /* approximation of the circle with polyline */
  d_theta = 2*PI/n;
  for(theta=0,i=0;i<n;++i, theta+=d_theta)
    {
      nx[i] = radius*cos(theta);
      ny[i] = radius*sin(theta);
      px[i] = nx[i]+tx;
      py[i] = ny[i]+ty;
    }

  /* cylinder is centered at 0,0,0 and is aligned along Z */
  z_top = tz+height;
  z_bottom = tz; 
  
  /* create the quad strip for cylinder sides*/
  glBegin(GL_TRIANGLE_STRIP);

  for(i=0;i<n;++i)
    {
      glNormal3d(nx[i],ny[i],0);
      glVertex3d(px[i],py[i],z_bottom);
      glNormal3d(nx[i],ny[i],0);
      glVertex3d(px[i],py[i],z_top);
    }
  
  glNormal3d(nx[0],ny[0],0);
  glVertex3d(px[0],py[0],z_bottom);
  glNormal3d(nx[0],ny[0],0);
  glVertex3d(px[0],py[0],z_top);
  
  glEnd();

  glBegin(GL_POLYGON);

  for(i=0;i<n;++i)
    {
      glNormal3d(0,0,1);
      glVertex3d(px[i],py[i],z_top);
    }

  glEnd();
  
  glBegin(GL_POLYGON);

  for(i=0; i < n;++i)
    {
      glNormal3d(0,0,-1);
      glVertex3d(px[i],py[i],z_bottom);
    }

  glEnd();

}

void molView::startPicking(int cursorX, int cursorY) {
	SelectMode = true;
	GLint viewport[4];
	selectBuf.resize(50000000);

	glSelectBuffer(selectBuf.size(), &selectBuf[0]);
	glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT,viewport);
	gluPickMatrix(cursorX,viewport[3]-cursorY,15,15,viewport);
	glOrtho(-width()*zTrans, width()*zTrans, -height()*zTrans,  height()*zTrans, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glInitNames();
}

void molView::stopPicking() {

	int hits;
	
	// restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	
	// returning to normal rendering mode
	hits = glRenderMode(GL_RENDER);
	
	// if there are hits process them
	if (hits != 0)
		processHits(hits,&selectBuf[0]);

	SelectMode = false;
}

void molView::processHits(GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

	printf ("hits = %d\n", hits);
	ptr = (GLuint *) buffer;
	minZ = 0xffffffff;
	//minZ = 0;
	for (i = 0; i < hits; i++) {	
		names = *ptr;
		ptr++;
		if (*ptr < minZ) {
			numberOfNames = names;
			minZ = *ptr;
			ptrNames = ptr+2;
		}
	  
		ptr += names+2;
	}
	
	vector<atom *> SelectedAtoms;
	if (numberOfNames == 2) {
		atom *atm = currMol->atoms[ptrNames[1]-1];
		SelectedAtoms.push_back(atm);
		atm->COLOR[0] = 1.0;
		atm->COLOR[1] = 1.0;
		atm->COLOR[2] = 1.0;
	}
	printf ("The closest hit names are ");
	ptr = ptrNames;
	for (j = 0; j < numberOfNames; j++,ptr++) {
		printf ("%d ", *ptr);
	}
	printf ("\n");
  
	//Show(currMol); 
}

}




