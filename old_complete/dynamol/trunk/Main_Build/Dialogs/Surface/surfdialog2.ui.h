/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#include <iostream>
using namespace std;

//QT INCLUDES
#include <qcolordialog.h>

//Dynamol Includes
#include "surfhelpdialog.h"

void surfDialog2::helpSlot()
{
   cout <<"You are in the helpSlot"<<endl;
   surfHelpDialog *dialog = new surfHelpDialog();
   dialog->setModal(false);
   if ( dialog->exec() ==  surfHelpDialog::Accepted) 
      delete dialog;
}


void surfDialog2::applySlot()
{

}



void surfDialog2::qualitySlot( int value )
{
   if (value == 0)
       fineQuality->setValue(70);
   if (value == 1)
       fineQuality->setValue(55);
   if (value == 2)
       fineQuality->setValue(30);
}


void surfDialog2::tightSlot( int value )
{
    if (value == 0)
	fineTight->setValue(20);
    if (value == 1)
	fineTight->setValue(30);
    if (value == 2)
	fineTight->setValue(35);
}


void surfDialog2::transSlot( bool value )
{
    if (value)	
	slider3->setValue(65);
    else
	slider3->setValue(100);
}


void surfDialog2::colorSlot()
{
   int r, g, b;
   
   if (Red >=0 && Red <= 1.0)
      r = Red*255;
   if (Green >= 0 && Green <= 1.0)
      g = Green*255;
   if (Blue >= 0 && Blue <= 1.0)
      b = Blue*255;
   
   QColor cl(r, g, b);
   QColor newColor = QColorDialog::getColor(cl);

   float fr, fg, fb;
   Red = newColor.red();
   Green = newColor.green();
   Blue = newColor.blue();

   Red /= 255;
   Green /= 255;
   Blue /= 255;
}


void surfDialog2::newSlot()
{

}
