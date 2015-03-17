/***************************************************************************
                          mousesensor.cpp  -  description
                             -------------------
    begin                : Sun Dec 28 2007
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include "mousesensor.h"

mouseSensor::mouseSensor(QWidget *parent, const char *name ) : QGLWidget(parent) {
  midButton = leftButton = rightButton = shiftKey = controlKey = altKey = UP;
  scaledX = scaledY = x = y = 0;
  setFocusPolicy(Qt::ClickFocus);
  timer = new QTimer(this);
  connect( timer, SIGNAL(timeout()), this, SLOT(timerDone()) );
  clickCounter = 0;
  dblClick = false;
  currMouseEvent = NULL;
  selFullMol = false;
  wasMoved = false;
  
}
mouseSensor::~mouseSensor(){
}

void mouseSensor::mousePressEvent(QMouseEvent *event) {
	currMouseEvent = event;
	wasMoved = false;
	  
	x = event->x();
	y = event->y();	
	scaledX = event->x()*2 - this->width();
	scaledX /= this->width();
	scaledY = this->height() - 2*event->y();
	scaledY /=this->height();
	startx = scaledX;
	starty = scaledY;
	button = event->button();


	//THIS IS A PORT PROBLEM
	//key  = event->state();
	key = event->modifiers();

	shiftKey = UP;
	controlKey = UP;
	if (key & Qt::ShiftModifier) {
		shiftKey = DOWN;
	}
	if (key & Qt::ControlModifier) {
		controlKey = DOWN;
	}
	if (key & Qt::AltModifier) {
		altKey = DOWN;
	}
	if (button & Qt::LeftButton) {
		leftButton = DOWN;
	}
	if (button & Qt::RightButton) {
		rightButton = DOWN;
	}
	if (button & Qt::MidButton) {
		midButton = DOWN;
	}

	// USed to determine mouse click counter
	// The start function is connected to the
	// Timer done function.  The number of clicks
	// Are counted in the mouseReleaseEvent method
	timer->stop();
	timer->setSingleShot( true );
	timer->start( 300 );
  
	if (rightButton == DOWN && midButton == DOWN) {
		emit midAndRightPress(x, y, scaledX, scaledY);
		return;
	}

	if (rightButton == DOWN) {
		emit rightButtonPress(x, y, scaledX, scaledY);
		return;
	}

	if (shiftKey == DOWN and leftButton == DOWN) {
		cout <<"Shit-LeftMouse Press"<<endl;
		emit ShiftLeftMousePress(x, y, scaledX, scaledY);
	}

	#ifdef Dynamol
	if (leftButton == DOWN) {
		int x = event->x();
		int y = event->y();
		return;
	}
	
	if (midButton == DOWN) {
		emit midButtonPress(x, y, scaledX, scaledY);
		return;
	}
	#endif

	#ifdef PyMol
	if (midButton == DOWN) {
		int x = event->x();
		int y = event->y();
		//emit leftButtonPressTracking(x, y, scaledX, scaledY, shiftKey, controlKey);
		return;
	}

	if (leftButton == DOWN) {
		emit leftButtonPress(x, y, scaledX, scaledY);
		return;
	}
	#endif  
}

void mouseSensor::timerDone() {
	if (clickCounter == 1) 
		wasSingleClick();
	if (clickCounter == 2)
		wasDoubleClick();
		
	//cout <<"clickCounter: " << clickCounter << endl;
	clickCounter = 0;	
}
void mouseSensor::wasSingleClick() {
	//cout <<"wasSingleClick()"<<endl;
	button = currMouseEvent->button();
	int x = currMouseEvent->x();
	int y = currMouseEvent->y();
	if (lastButtonReleased & Qt::MidButton) {
		cout <<"Emiting: " << lastX <<"\t" << lastY << endl;
		emit midButtonSingleClick(lastX, lastY);
	}
	if (lastButtonReleased & Qt::MidButton) {
	}
	if (lastButtonReleased & Qt::MidButton) {
	}
	
}
void mouseSensor::wasDoubleClick() {
	cout <<"Was double Clikc"<<endl;
    if (button & Qt::RightButton) ////qDebug("RightButton");
	if (button & Qt::MidButton) ////qDebug("MidButton");
	if (button & Qt::LeftButton) ////qDebug("LeftButton");

    if (button & Qt::LeftButton) {
      emit leftButtonDoubleClick(x, y, scaledX, scaledY, shiftKey);
    }
}

void  mouseSensor::mouseDoubleClickEvent(QMouseEvent *event){
	
	scaledX = event->x()*2 - this->width();
    scaledX /= this->width();
    scaledY = this->height() - 2*event->y();
    scaledY /=this->height();

    x = event->x();
    y = event->y();

    //Qt::ButtonState button = event->button();
	Qt::MouseButtons button = event->button();

	QString num; num.setNum(button);

    if (button & Qt::LeftButton) {
      emit leftButtonDoubleClick(x, y, scaledX, scaledY, shiftKey);
    }
	
}



void mouseSensor::mouseReleaseEvent(QMouseEvent *event) {
	currMouseEvent = event;

	//This controls the single click double click
	// Counter.  There is a singleShot time set
	// In the mousePressEvent method
	if (!wasMoved) 
		clickCounter++;

	scaledX = event->x()*2 - this->width();
	scaledX /= this->width();
	scaledY = this->height() - 2*event->y();
	scaledY /=this->height();
	x = event->x();
	y = event->y();
	lastY = y;
	lastX = x;

	Qt::MouseButtons button = event->button();
	if (button & Qt::LeftButton)  {
		leftButton = UP;
		lastButtonReleased = Qt::LeftButton;
	//	return;
	}
	if (button & Qt::RightButton) {
		rightButton = UP;
		lastButtonReleased = Qt::RightButton;
	}
	if (button & Qt::MidButton){
		cout <<"MidButton released:  "<< event << endl;
		midButton  = UP;
		lastButtonReleased = Qt::MidButton;
	//	return;
	}


	if (shiftKey == DOWN and lastButtonReleased == Qt::LeftButton) {
		cout <<"Shift-LeftMouseRelease"<<endl;
		emit ShiftLeftButtonRelease(x, y, scaledX, scaledY);
	}	
	
}

void mouseSensor::mouseMoveEvent(QMouseEvent *event) {
	//clickCounter = 0; 
	currMouseEvent = event;
	wasMoved = true;
	timer->stop();
	scaledX = event->x()*2 - this->width();
	scaledX /= this->width();
	scaledY = this->height() - 2*event->y();
	scaledY /=this->height();

	x = event->x();
	y = event->y();

	
//	if (midButton == DOWN && rightButton == DOWN) {
//		emit midAndRightMove(x, y, scaledX, scaledY);
//		return;
//	}

	//############ LEFT BUTTON CONTROL SEQUENCES ##########
	if (shiftKey == DOWN and leftButton == DOWN) {
		emit ShiftLeftButtonMove(x, y, scaledX, scaledY);
	} else if (controlKey == DOWN and leftButton == DOWN) {
		//cout <<"control-Left"<<endl;
	} else if (leftButton == DOWN) {
		//cout <<"leftMouse"<<endl;
		emit  leftButtonMove(x, y, scaledX, scaledY);
	} 
	
	// ########## RIGHT BUTTON CONTROL SEQUENCES #######
	else if (shiftKey == DOWN and rightButton == DOWN) {
		//cout <<"Shift-RightMouse"<<endl;
	} else if (controlKey == DOWN and rightButton == DOWN) {
		//cout <<"Control-RightMouse"<<endl;
	} else if (rightButton == DOWN) {
		emit rightButtonMove(x, y, scaledX, scaledY);
	} 

	// ######### MID BUTTON CONTROL SEQUENCES #########
	else if (shiftKey == DOWN and midButton == DOWN) {
		//cout <<"Shift-MidMouse"<<endl;
	} else if (controlKey == DOWN and midButton == DOWN) {
		//cout <<"Control-MidMouse"<<endl;
	} else if (midButton == DOWN) {
		emit midButtonMove(x, y, scaledX, scaledY);
	} 
}

void mouseSensor::wheelEvent(QWheelEvent *event) {
	int rotation = event->delta();
	if (event->delta() > 0) {
		emit wheelForward(rotation);
	} else {
		emit wheelBackward(rotation);
	}
}

void mouseSensor::keyPressEvent( QKeyEvent *event ) {
}

void mouseSensor::keyReleaseEvent(QKeyEvent *event) {
	Qt::KeyboardModifiers key = event->modifiers();
	
	if (key & Qt::ShiftModifier) {
		shiftKey = UP;
	}
	if (key & Qt::ControlModifier) {
		controlKey = UP;
	}
	if (key & Qt::AltModifier) {
		altKey = UP;
	}   
}






































