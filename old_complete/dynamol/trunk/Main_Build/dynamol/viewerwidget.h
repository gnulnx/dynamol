/***************************************************************************
                          viewerwidget.h  -  description
                             -------------------
    begin                : Sun Dec 28 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H
//#include <Qt>
#include <QtOpenGL>
#include <qwidget.h>
#include <qobject.h>
//#include <qgl.h>
//#include "/usr/local/Trolltech/Qt-4.3.0/include/Qt/qgl.h"
#include "mousesensor.h"

#include "trackball.h"

#include <iostream>
#include <vector>

using namespace std;


/**
  @author John Furr

  Currently I am thinking that viewerWidget will be a generic openGl rendering widget
  which supports trackball like rotation, translation, && zooming.
*/
class viewerWidget : public mouseSensor, public TrackBall {
   Q_OBJECT
public: 
	viewerWidget(QWidget *parent=0, const char *name=0);
	~viewerWidget();

  void loadObj(GLuint newObj);

protected:
  float lastQuat[4], currentQuat[4];  //Quaternions used for rotation
  
  GLdouble xTrans, yTrans, zTrans;
  GLUquadricObj *quadObj, *wireObj;
  vector<GLuint> Objects;
  float startTransX, startTransY;
private:
//

protected slots:
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





































