/***************************************************************************
                          mousesensor.cpp  -  description
                             -------------------
    begin                : Sun Dec 28 2003
    copyright            : (C) 2003 by Dynamol Inc.
    email                : john.furr@dynamol.com
 ***************************************************************************/


#include "mousesensor.h"


mouseSensor::mouseSensor(QWidget *parent, const char *name ) : QGLWidget(parent,name) {
  midButton = leftButton = rightButton = shiftKey = controlKey = altKey = UP;
  scaledX = scaledY = x = y = 0;
  setFocusPolicy(QWidget::ClickFocus);
  timer = new QTimer(this);
  connect( timer, SIGNAL(timeout()), this, SLOT(timerDone()) );
  clickCounter = 0;
  dblClick = false;
  currEvent = NULL;
  selFullMol = false;
  wasMoved = false;
  
  //setMouseTracking(true);
}
mouseSensor::~mouseSensor(){
}

void mouseSensor::mousePressEvent(QMouseEvent *event) {
	wasMoved = false;
	//////qDebug("mouseSensor::mousePressEvent");   
     
    

    //Normalize the x && y mouse position between -1 && 1;
    //********************* NOTE **************************
    //if you move outside the boundry of the window then the
    //coords can go beyond the [-1, 1] range.  This might be a potential
    //probelm down the road.

     //This is necassary otherwise when the user first interacts with app the coords
     //are set to zero.

  //    Actually I am not sure that it is nessacary.
  
  x = event->x();
  y = event->y();	
  scaledX = event->x()*2 - this->width();
  scaledX /= this->width();
  scaledY = this->height() - 2*event->y();
  scaledY /=this->height();
  startx = scaledX;
  starty = scaledY;
  button = event->button();
  key  = event->state();
  shiftKey = UP;
  controlKey = UP;
  //leftButton = UP; //Leave these uncommented...it is right..I think
  //rightButton = UP;
  //midButton = UP;
  if (key & ShiftButton) {
      shiftKey = DOWN;
 }
  if (key & ControlButton) {
      controlKey = DOWN;
  }
  if (key & AltButton) {
      altKey = DOWN;
  }
  if (button & LeftButton) {
      leftButton = DOWN;
  }
  if (button & RightButton) {
      rightButton = DOWN;
  }
  if (button & MidButton) {
      midButton = DOWN;
  }

  timer->start( 200, TRUE );
  
  if (rightButton == DOWN && midButton == DOWN) {
    emit midAndRightPress(x, y, scaledX, scaledY);
    return;
  }

  if (rightButton == DOWN) {
    emit rightButtonPress(x, y, scaledX, scaledY);
    return;
  }

  if (leftButton == DOWN) {
    int x = event->x();
    int y = event->y();
    emit leftButtonPress(x, y, scaledX, scaledY, shiftKey, controlKey);
    emit leftButtonPressTracking(x, y, scaledX, scaledY, shiftKey, controlKey);
    //////////////cout <<"Emitting leftButtonPress()"<<endl;
    return;
  }

  if (midButton == DOWN) {
    //////////////cout <<"emitting midButtonPress"<<endl;
    emit midButtonPress(x, y, scaledX, scaledY);
    emit leftButtonPress(x, y, scaledX, scaledY, shiftKey, controlKey);
    //emit leftButtonPressTracking(x, y, scaledX, scaledY, shiftKey, controlKey);
    
    return;
  }  
}

void mouseSensor::timerDone() {
   //////qDebug("Timer Done");
   /*
	if (clickCounter == 2) {
	   //////qDebug("Double Click");
	   wasDoubleClick();
	   emit leftButtonRelease(x, y, scaledX, scaledY, shiftKey, controlKey);
   } else {
	   //////qDebug("Single Click");
	   wasSingleClick();
	   //emit leftButtonRelease(x, y, scaledX, scaledY, shiftKey, controlKey);
   }
   clickCounter = 0;
   */
}
void mouseSensor::wasSingleClick() {
	////qDebug("singleClick");   
    //Normalize the x && y mouse position between -1 && 1;
    //********************* NOTE **************************
    //if you move outside the boundry of the window then the
    //coords can go beyond the [-1, 1] range.  This might be a potential
    //probelm down the road.

     //This is necassary otherwise when the user first interacts with app the coords
     //are set to zero.

  //    Actually I am not sure that it is nessacary.
 

  //if (button & RightButton) ////qDebug("Single Click RightButton");
  //if (button & MidButton) ////qDebug("Single Click MidButton"); 
  //if (button & LeftButton) ////qDebug("Single Click LeftButton");
  
  if (rightButton == DOWN && midButton == DOWN) {
    emit midAndRightPress(x, y, scaledX, scaledY);
    return;
  }

  if (rightButton == DOWN) {
    emit rightButtonPress(x, y, scaledX, scaledY);
    return;
  }

  if (leftButton == DOWN) {
    emit leftButtonPress(x, y, scaledX, scaledY, shiftKey, controlKey);
    emit leftButtonPressTracking(x, y, scaledX, scaledY, shiftKey, controlKey);
    //////////////cout <<"Emitting leftButtonPress()"<<endl;
    return;
  }

  if (midButton == DOWN) {
    //////////////cout <<"emitting midButtonPress"<<endl;
    
	//emit leftButtonPress(x, y, scaledX, scaledY, shiftKey, controlKey);
    emit midButtonPress(x, y, scaledX, scaledY);
    return;
  }
}
void mouseSensor::wasDoubleClick() {
    if (button & RightButton) ////qDebug("RightButton");
	if (button & MidButton) ////qDebug("MidButton");
	if (button & LeftButton) ////qDebug("LeftButton");

    if (button & LeftButton) {
	////qDebug("emitting leftButtonDoubleClick");
      emit leftButtonDoubleClick(x, y, scaledX, scaledY, shiftKey);
    }
}

void  mouseSensor::mouseDoubleClickEvent(QMouseEvent *event){
	
	////qDebug("mouseSensor::mouseDoubleClickEvent");
	scaledX = event->x()*2 - this->width();
    scaledX /= this->width();
    scaledY = this->height() - 2*event->y();
    scaledY /=this->height();

    x = event->x();
    y = event->y();

    ButtonState button = event->button();

	QString num; num.setNum(button);
	////qDebug(num);

    if (button & LeftButton) {
	////qDebug("emitting leftButtonDoubleClick");
      emit leftButtonDoubleClick(x, y, scaledX, scaledY, shiftKey);
    }
	
}



void mouseSensor::mouseReleaseEvent(QMouseEvent *event) {
  clickCounter++;
	int tst = 10;
	//////qDebug("mouseSensor::mouseReleaseEvent %x", tst);
  scaledX = event->x()*2 - this->width();
  scaledX /= this->width();
  scaledY = this->height() - 2*event->y();
  scaledY /=this->height();
  x = event->x();
  y = event->y();
   ButtonState button = event->button();
  if (button & LeftButton)  {
    leftButton = UP;
    emit leftButtonRelease(x, y, scaledX, scaledY, shiftKey, controlKey);
	return;
  }
  if (button & RightButton) {
     rightButton = UP;
     emit rightButtonRelease(x, y, scaledX, scaledY, shiftKey, controlKey);
  }
  if (button & MidButton){
    midButton  = UP;
	if (!wasMoved) {
	  selFullMol = true;
	  emit leftButtonRelease(x, y, scaledX, scaledY, shiftKey, controlKey);
	}
	//emit midButtonRelease(x, y, scaledX, scaledY, shiftKey);
	return;
  }
  
}

void mouseSensor::mouseMoveEvent(QMouseEvent *event) { 
  wasMoved = true;
  timer->stop();
  //////qDebug("Mouse Move Event");
  scaledX = event->x()*2 - this->width();
  scaledX /= this->width();
  scaledY = this->height() - 2*event->y();
  scaledY /=this->height();

  x = event->x();
  y = event->y();

  //////////////cout <<"Emmiting leftButton Press"<<endl;
  if (hasMouseTracking() && midButton != DOWN) {
      double xPos, yPos, zPos;
      emit trackMouse(xPos, yPos, zPos, x, y, scaledX, scaledY, shiftKey, controlKey);
  }
  
  if (midButton == DOWN && rightButton == DOWN) {
    emit midAndRightMove(x, y, scaledX, scaledY);
    return;
  }
  if (leftButton == DOWN) {
    emit  leftButtonMove(x, y, scaledX, scaledY, shiftKey );
  } else if (rightButton == DOWN) {
    emit rightButtonMove(x, y, scaledX, scaledY);
  } else if (midButton == DOWN) {
    emit midButtonMove(x, y, scaledX, scaledY);
  }

}

void mouseSensor::wheelEvent(QWheelEvent *event) {
  //////////////cout <<"Yes you are in mouseWheelEvent()
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
	ButtonState key = event->state();
   //////////////cout <<"YOU ARE IN THE keyReleaseEvent(): " << endl;
 	if (key & ShiftButton) {
		shiftKey = UP;
  	}
  	if (key & ControlButton) {
		controlKey = UP;
  	}
  	if (key & AltButton) {
		altKey = UP;
  	}   
}






































