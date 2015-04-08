/***************************************************************************
                          molview_control.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by John Furr
    email                : john.furr@gmail.com


    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/


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





































