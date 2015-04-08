/***************************************************************************
                          mousesensor.h  -  description
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

#ifndef MOUSESENSOR_H
#define MOUSESENSOR_H

#include <qwidget.h>
#include <Qt>
#include <QtOpenGL>
#include <qevent.h>
#include <qtimer.h>

#include "enumTypes.h"

#include <iostream>

using namespace std;

/**
  @author John Furr

  Class mouseSensor is a simple widget which tracks the x && y coordinates of the mouse
  relative to the mouseSensor widget.  The widget emits signals  which report two types of x && y
  coordinates.  The first type are normal widget coordinats were (0,0) is locate in the upper left
  had corner && (max, max) is located in the lower right hand corner of the widget.
  The other coordinates are scaled between [-1, 1] for both the x && y axis.  The origin (0,0) is then
  located in the center of the widget.

  One way to use the mouseSensor widget/class is to inhereit from it like:
  <pre>
  class someClass : public mouseSensor
  {
    slot trackCoords(float &, float &, float &, float &);
  }
  </pre>

  Then in the class implementation connect your slot with the mouse sensor signal you wish to use like:

  <pre>
  someClass::somClass(QWidget *parent const char *name)
    : mouseSensor(parent, name)
  {
    connect(this, SIGNAL(leftButtonMove(float &, float &, float &, float &)),
            this, SLOT(trackCoords(float &, float &, float & float &)));

*/
class mouseSensor : public QGLWidget  {
	friend class pickEngine;
	Q_OBJECT
public: 
	mouseSensor(QWidget *parent=0, const char *name=0);
	~mouseSensor();

	bool selFullMol;
	bool wasMoved;
protected:
	float startx, starty;

	enum button_state {DOWN, UP};  //Makes for easier to read c

	/**
	Variables of type button_state which are used to determine wether the buton in question is
	being pressed (DOWN) are has been released (UP).  The default position is UP.
	*/
	button_state  leftButton, rightButton, midButton, shiftKey, controlKey, altKey;


	float   scaledX, scaledY;
	int     x, y;
private:
	QTimer *timer;
	int clickCounter; //This is used to count the nubmer of mouse clickes
	bool dblClick;
	void wasDoubleClick();

	void wasSingleClick();

	QMouseEvent *currMouseEvent;
	
	Qt::MouseButtons button;
	Qt::KeyboardModifiers key;
  
	Qt::MouseButton lastButtonReleased;
	int lastX, lastY;
private slots:
  /** called whenever a mouse button is pressed
  */
  void mousePressEvent(QMouseEvent *);

  /** This event is used to time the double click events */
  void timerDone();

  /** Called whenever a mouse double click event is recorded
  */
  void mouseDoubleClickEvent(QMouseEvent *event);
  /** Called whenever the mouse is moved.  Default state requires a button to be in the DOWN
      Position....i.e...being pressed
  */
  void mouseMoveEvent(QMouseEvent *);

  /** Called whenever the mouse button has been released
  */
  void mouseReleaseEvent(QMouseEvent *);

  /** Called whenever the mouse wheel has been moved
  */
  void wheelEvent(QWheelEvent *);

  void keyPressEvent( QKeyEvent* );
  void keyReleaseEvent(QKeyEvent *);
  //void keyReleaseEvent ( QKeyEvent*e )

signals:
	//void leftButtonPressTracking(int &x, int &y, float &scaledX, float &scaledY, button_state shiftState, button_state ctrlState);
	void rightButtonPress();
  
	//void trackMouse(double &xPos, double &yPos, double &zPos, int &x, int &y, float &scaledX, float &scaledY, button_state shiftState, button_state ctrlState);
	void leftButtonMove(int &x, int &y, float &scaledX, float &scaledY, button_state shiftState);
	void leftButtonMove(int &x, int &y, float &scaledX, float &scaledY);
	void leftButtonPress(int &x, int &y, float &scaledX, float &scaledY, button_state shiftState, button_state ctrlState);


	// ########## NEW FUNCTION
	// THESE ARE INVOLVED IN SWEEP PICK SELECTIN
	void ShiftLeftMousePress(int x, int y, float scaledX, float scaledY);
	void ShiftLeftButtonMove(int x, int y, float scaledX, float scaledY);
	void ShiftLeftButtonRelease(int x, int y, float scaledX, float scaledY);


	void leftButtonDoubleClick(int &x, int &y, float &scaledX, float &scaledY, button_state shiftState);


	void rightButtonMove(int &x, int &y, float &scaledX, float &scaledY);
	void rightButtonPress(int &x, int &y, float &scaledX, float &scaledY);

	void midButtonMove(int &x, int &y, float &scaledX, float &scaledY);
	void midButtonPress(int &x, int &y, float &scaledX, float &scaledY);
	void leftButtonPress(int &x, int &y, float &scaledX, float &scaledY);

	void midAndRightMove(int &x, int &y, float &scaledX, float &scaledY);
	void midAndRightPress(int &x, int &y, float &scaledX, float &scaledY);

	//void leftButtonRelease(int &x, int &y, float &scaledX, float &scaledY, button_state shiftState, button_state ctrlState);
	//void rightButtonRelease(int &x, int &y, float &scaledX, float &scaledY, button_state shiftState, button_state ctrlState);
	void midButtonRelease(int &x, int &y, float &scaledX, float &scaledY, button_state shiftState);
 
	void wheelForward(int &rotation);
	void wheelBackward(int &rotation);

	void midButtonSingleClick(int &x, int &y);  
};

#endif





































