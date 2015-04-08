/***************************************************************************
                          molview_control.cpp  -  description
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

#include "molview_control.h"

molViewControl::molViewControl(QWidget *parent, const char *name )
: mouseSensor(parent,name),
  TrackBall()
{
	startTransX = startTransY = 0;
  
	//Initialize lastQuat && cuttentQuat
	for (int i=0; i< 4; i++) {
		lastQuat[i] = 0;
		currentQuat[i] = 0;
	}

	#ifdef Dynamol
	connect(this, SIGNAL(midButtonMove(int &, int &, float &, float &)),
			this, SLOT(rotateObj(int &, int &, float &, float &)));

	connect(this, SIGNAL(midButtonPress(int &, int &, float &, float &)),
		this, SLOT(getCoords(int &, int &, float &, float &)));

	connect(this, SIGNAL(rightButtonPress(int &, int &, float &, float &)),
		this, SLOT(getCoords(int &, int &, float &, float &)));

	connect(this, SIGNAL(rightButtonMove(int &, int &, float &, float &)),
		this, SLOT(translateObj(int &, int &, float &, float &)));

	connect(this, SIGNAL(midAndRightMove(int &, int &, float &, float &)),
            this, SLOT(zoomObj(int &, int &, float &, float &)));
	#endif

	#ifdef PyMol
	connect(this, SIGNAL(leftButtonMove(int &, int &, float &, float &)),
            this, SLOT(rotateObj(int &, int &, float &, float &)));

    connect(this, SIGNAL(leftButtonPress(int &, int &, float &, float &)),
        this, SLOT(getCoords(int &, int &, float &, float &)));
	
  
  	connect(this, SIGNAL(midButtonPress(int &, int &, float &, float &)),
			this, SLOT(getCoords(int &, int &, float &, float &)));
  
	connect(this, SIGNAL(midButtonMove(int &, int &, float &, float &)),
			this, SLOT(translateObj(int &, int &, float &, float &)));

	connect(this, SIGNAL(rightButtonMove(int &, int &, float &, float &)),
            this, SLOT(zoomObj(int &, int &, float &, float &)));

	#endif

	connect(this, SIGNAL(wheelForward(int &)), 
			this, SLOT(wheelZoom(int &)));

	connect(this, SIGNAL(wheelBackward(int &)), 
			this, SLOT(wheelZoom(int &)));

	show();
}
                                            

void molViewControl::rotateObj(int &xInt, int &yInt, float &xFloat, float &yFloat) {
	//These two lines of code effectively flip the coordinate system.
	//The reason is to make the object follow the mouse instead of tracking opposite.
	xFloat = 0-xFloat;
	yFloat = 0-yFloat;

	trackball(lastQuat, startx, starty, xFloat, yFloat);
	addQuats(lastQuat, currentQuat, currentQuat);

	startx = xFloat;
	starty = yFloat;

	updateGL();
}

void molViewControl::translateObj(int &xInt, int &yInt, float &xFloat, float &yFloat) {
  //cout <<"translateObj: " << xInt <<"\t" << yInt<<"\t"<<xFloat<<"\t"<<yFloat<<endl;
  //I am pretty sure there are sexier ways to do this, but it does work like I want it to.
  if (shiftKey == DOWN) zoomObj(xInt, yInt, xFloat, yFloat);
  else if (this->controlKey == DOWN) {
     rotateObj(xInt, yInt, xFloat, yFloat);
  }
  else {
     if (xFloat > startx) {
       xTrans -= this->width()*sqrt((xFloat-startx)*(xFloat-startx))*zTrans;
     } else if (xFloat < startx) {
       xTrans += this->width()*sqrt((xFloat-startx)*(xFloat-startx))*zTrans;
     }

     if (yFloat > starty) {
       yTrans -= this->height()*sqrt((yFloat-starty)*(yFloat-starty))*zTrans;
     } else if (yFloat < starty) {
       yTrans += this->height()*sqrt((yFloat-starty)*(yFloat-starty))*zTrans;
     }

     startx = xFloat;
     starty = yFloat;
     updateGL();
  }
};

void molViewControl::zoomObj(int &xInt, int &yInt, float &xFloat, float &yFloat) {
	
	float factor = 1.0;
	if (yFloat < starty)
		factor = -1.0;

	if (zTrans > 0.1)
		zTrans += factor*0.085*zTrans;
	else if (zTrans <0.1 and zTrans > 0.05)
		zTrans += factor*0.075*zTrans;
	else if (zTrans <0.05 and zTrans > 0.01)
		zTrans += factor*0.050*zTrans;
	else
		zTrans += factor*0.025*zTrans;

	startx = xFloat;
	starty = yFloat;

	updateGL();
}

void molViewControl::wheelZoom(int &rotation) {

	//#### SLAB MODE ######
	if (rotation > 0) {
		zNear -= 5;
	} else if (rotation < 0){
		zNear +=5;
	}
	//## END SLAB MODE ####
	
	updateGL();
}

void molViewControl::getCoords(int &xInt, int &yInt, float &xFloat, float &yFloat) {
	#ifdef Dynamol
	if (midButton == DOWN) {// or leftButton == DOWN) {
		this->startx = 0-xFloat;
		this->starty = 0-yFloat;
	} else if (this->controlKey == DOWN && this->rightButton == DOWN) {
		this->startx = 0-xFloat;
		this->starty = 0-yFloat;
	}
	#endif

	#ifdef PyMol
	if (leftButton == DOWN) {// or leftButton == DOWN) {
		this->startx = 0-xFloat;
		this->starty = 0-yFloat;
	} else if (this->controlKey == DOWN && this->rightButton == DOWN) {
		this->startx = 0-xFloat;
		this->starty = 0-yFloat;
	}
	#endif

	StartScreenX = xInt;
	StartScreenY = yInt;
	PrevScreenX = xInt;
	PrevScreenY = yInt;
}

