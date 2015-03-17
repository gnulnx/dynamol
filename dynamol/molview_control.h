/***************************************************************************
                          molview_control.h  -  description
                             -------------------
    begin                : Sun Dec 28 2007
    copyright            : (C) 2007 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#ifndef MOLVIEW_CONTROL_H
#define MOLVIEW_CONTROL_H

#include <QtOpenGL>
#include <qwidget.h>
#include <qobject.h>

#include "mousesensor.h"
#include "trackball.h"


/**
  @author John Furr

  Currently I am thinking that viewerWidget will be a generic openGl rendering widget
  which supports trackball like rotation, translation, && zooming.
*/
class molViewControl : public mouseSensor, public TrackBall {
	Q_OBJECT
public: 
	molViewControl(QWidget *parent=0, const char *name=0);
	~molViewControl() {};

protected:
	float lastQuat[4], currentQuat[4];  //Quaternions used for rotation
  
	GLdouble xTrans, yTrans, zTrans;

	float startTransX, startTransY;

	int StartScreenX;
	int StartScreenY;
	float PrevScreenX;
	float PrevScreenY;

	float zNear, zFar;
private:

protected slots:
	//Overloaded virtual openGl Functions.	
	void initializeGL() {};
	void paintGL() {};
	void resizeGL(int w, int h) {};

public slots:
	void getCoords(int &xInt, int &yInt, float &xFloat, float &yFloat);
	void rotateObj(int &xInt, int &yInt, float &xFloat, float &yFloat);
	void translateObj(int &xInt, int &yInt, float &xFloat, float &yFloat);
	void zoomObj(int &xInt, int &yInt, float &xFloat, float &yFloat);
	void wheelZoom(int &rotation);
  
  
signals:
	void testSig(int &);
};

#endif





































