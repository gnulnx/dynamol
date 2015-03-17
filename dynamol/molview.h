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
#include <qlabel.h>
#include "molview_control.h"

#include <iomanip>
#include <iostream>
#include <list>
using std::list;
using namespace std;

class QLineEdit;

namespace dynamol {

class bond;
class molecule;
class DynaPy;
#include <qpixmap.h>

/**
  *@author John Furr
  */

class molView : public molViewControl  {
	Q_OBJECT
public:
	molView(QWidget *parent=0, char *name=0);
	void SetScripter(DynaPy *dynapy);
	~molView();
   

	string hello(); 

protected slots: 
	/** Method comes for the QGLWidget hierarchy && is used to perform all of the
	openGL initialization stuff.
	*/
	void initializeGL();

	/** Perform Setup operations that sould not be updated on 
	//  recall to initializeGL */
	void InitSetup();

	/**  Method comes from the QGLWidget hierarchy && is called wherever the scene needs
      to be painted
	*/
	void paintGL();

	/** Method comes from the QGLWidget hierarchy && is called whenever the window is resized
	*/
	void resizeGL(int w, int h);
	/** This slot is used to update the molview window */

	void ReCenter(int &x, int &y);

	/** Slots involved in Sweep Picks Selection */
	void selectObjects(int x, int y, float xFloat, float yFloat);
	void selectBox(int newX, int newY, float newXFloat, float newYFloat);
	void SweepPickSelect(int x, int y, float xScale, float yScale);

protected:
	/** Start Picking Mode. */
	void startPicking(int cursorX, int cursorY);

	/** Stop Picking Mode */
	void stopPicking();

	/** Process Hit records */
	void processHits(GLint hits, GLuint buffer[]);

	/** The selectionBuffer */
	vector<GLuint> selectBuf;

	/** The center of the model */
	vector<float> center;

	/* Variables for Sweep Pick Selection */
	int boxBeginX, boxBeginY, boxEndX, boxEndY;

public:
	/** This function is used to update the graphis...basically it calls updateGL() */
	void update();

	/** Draws sphere, cylinder, singleBond, doubleBond, etc...
   */
	void renderInit();


	void solidCylinder(double tx, double ty, double tz, double radius,double height, int n_subdivision_steps);

	/** Draw Wire Frame Bonds */
	void drawWireBond(bond *BD);

	/** Script Test Function...Nothing More and Nothing Less */
	void colorMolecule(float r, float g, float b);

	/** Use this to position gluLookAt */
	void LookAt(float eyeX, float eyeY, float eyeZ, \
                float centerX, float centerY, float centerZ, \
				float upX, float upY, float upZ);

	
	void Show(molecule *mol);

	void SetFog(float start, float end, float trans);

	void DrawCenterAxis();

	molecule *getCurrentMol();
	/** This function takes a list of molecules to render as an argument  S
    */
    void Render(molecule *mol);

public slots:



	/** FPS_SLOT */
	void FPS_Slot();
private:
	GLUquadricObj *quadObj, *wireObj;
	/** gluLookAt variables */
	float centerX, centerY, centerZ;

	float fogStart, fogEnd, fogTrans;

	float fps;

	float currMat[16];
	float origMat[16]; 
	GLdouble mvMatrix[16];
	GLint vPort[4];
	GLdouble projMatrix[16];
	float mat_shininess[1];
	float mat_ribbon_shininess[2];
	GLint mainList;
	GLint ballSphere, cpkSphere, singleStick, doubleStick, singleWire, doubleWire, aromaticWire, aromaticStick;
	GLUquadric *gluObj;
	QPixmap *saveState;  //This is used to save the openGL state during rubberBand selection
	QPixmap saveState2;
	double xCenter, yCenter, zCenter;

	DynaPy *dynapy;
	bool SelectMode;
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


	// CURRENT STUFF
	molecule *currMol;
	vector<molecule *> Mols;
};
};
#endif




