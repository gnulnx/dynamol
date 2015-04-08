/***************************************************************************
                          viewerwidget.cpp  -  description
                             -------------------
    begin                : Sun Dec 28 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/

#include "viewerwidget.h"

viewerWidget::viewerWidget(QWidget *parent, const char *name )
: mouseSensor(parent,name),
  TrackBall()
{
  quadObj = gluNewQuadric();
  wireObj = gluNewQuadric();
  //Initialize the starting x && y coords
  //startx = starty = 0;
  startTransX = startTransY = 0;
  
  //Initialize lastQuat && cuttentQuat
  for (int i=0; i< 4; i++) {
    lastQuat[i] = 0;
    currentQuat[i] = 0;
  }

  connect(this, SIGNAL(midButtonMove(int &, int &, float &, float &)),this, SLOT(rotateObj(int &, int &, float &, float &)));
  //connect(this, SIGNAL(leftButtonMove(int &, int &, float &, float &)),this, SLOT(translateObj(int &, int &, float &, float &)));
  //connect(this, SIGNAL(rightButtonMove(int &, int &, float &, float &)),this, SLOT(zoomObj(int &, int &, float &, float &)));
  connect(this, SIGNAL(midButtonPress(int &, int &, float &, float &)),this, SLOT(getCoords(int &, int &, float &, float &)));
  
  connect(this, SIGNAL(rightButtonPress(int &, int &, float &, float &)),this, SLOT(getCoords(int &, int &, float &, float &)));
  
  connect(this, SIGNAL(rightButtonMove(int &, int &, float &, float &)),this, SLOT(translateObj(int &, int &, float &, float &)));
  connect(this, SIGNAL(midAndRightMove(int &, int &, float &, float &)),this, SLOT(zoomObj(int &, int &, float &, float &)));

  connect(this, SIGNAL(wheelForward(int &)), this, SLOT(wheelZoom(int &)));
  connect(this, SIGNAL(wheelBackward(int &)), this, SLOT(wheelZoom(int &)));
}
viewerWidget::~viewerWidget(){
}

//These are virtual functions
void viewerWidget::initializeGL()           {}
void viewerWidget::paintGL()                {}
void viewerWidget::resizeGL(int w, int h)   {}
                                            

void viewerWidget::loadObj(GLuint newObj) {
  Objects.clear();
  Objects.push_back(newObj);
}


void viewerWidget::rotateObj(int &xInt, int &yInt, float &xFloat, float &yFloat) {
  //These two lines of code effectively flip the coordinate system.
  //The reason id to make the object follow the mouse instead of tracking opposite.
  xFloat = 0-xFloat;
  yFloat = 0-yFloat;

  trackball(lastQuat, startx, starty, xFloat, yFloat);
  addQuats(lastQuat, currentQuat, currentQuat);

  startx = xFloat;
  starty = yFloat;

  updateGL();
}


void viewerWidget::translateObj(int &xInt, int &yInt, float &xFloat, float &yFloat) {
  //I am pretty sure there are sexier ways to do this, but it does work like I want it to.
  if (shiftKey == DOWN) zoomObj(xInt, yInt, xFloat, yFloat);
  else if (this->controlKey == DOWN) {
     //getCoords(xInt, yInt, xFloat, yFloat); 
     rotateObj(xInt, yInt, xFloat, yFloat);
  }
  else {
     if (xFloat > startx) {
       xTrans += this->width()*sqrt((xFloat-startx)*(xFloat-startx))/zTrans;
     } else if (xFloat < startx) {
       xTrans -= this->width()*sqrt((xFloat-startx)*(xFloat-startx))/zTrans;
     }
  
     if (yFloat > starty) {
       yTrans += this->height()*sqrt((yFloat-starty)*(yFloat-starty))/zTrans;
     } else if (yFloat < starty) {
       yTrans -= this->height()*sqrt((yFloat-starty)*(yFloat-starty))/zTrans;
     }

     startx = xFloat;
     starty = yFloat;
     updateGL();
  }
};

void viewerWidget::zoomObj(int &xInt, int &yInt, float &xFloat, float &yFloat) {
  /** What you have done is to make the function a decreasing exponential...however you have
   bond the alpha value to a linear equation were it is 0 when zTrans is 250 && l03 when Trans
   is 25
   */

  static float alpha = 0.03;
  float IA = 0;
  
  float slope = -0.03/225;
  alpha = slope*zTrans + 0.033;
  IA = exp(alpha*zTrans)-1;

  if (yFloat > starty) {
      if (zTrans > 225) 
	zTrans -= 5.0;
      else
        zTrans -= IA*3;
  } else if (yFloat <starty) {
      if (zTrans < 5)
	zTrans += 2.0;
      else 
         zTrans += IA*3;
  }
 
  startx = xFloat;
  starty = yFloat;

  
  updateGL();
}

void viewerWidget::wheelZoom(int &rotation) {
  static float alpha = 0.03;
  float IA = 0;
  float slope = -0.03/225;

  alpha = slope*zTrans + 0.033;
  IA = exp(alpha*zTrans)-1;

  if (rotation > 0) {
    zTrans -= IA*3;       
  } else if (rotation < 0){
    zTrans += IA*3;              
  }  
  updateGL();
}

void viewerWidget::getCoords(int &xInt, int &yInt, float &xFloat, float &yFloat) {
  //////////////cout <<"getCoords: " << endl;
  if (midButton == DOWN) {
   this->startx = 0-xFloat;
   this->starty = 0-yFloat;
  } else if (this->controlKey == DOWN && this->rightButton == DOWN) {
   this->startx = 0-xFloat;
   this->starty = 0-yFloat;
  }
}

