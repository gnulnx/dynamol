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
#include <qcolordialog.h>
using std::cout;
using std::endl;



void colorDialog::cs_1_Slot()
{
   emit colorChange("#ffaa00", "#fe7fbe", "#0055ff",  "#ffffff", "#aa0000", "#55ff7f");
}


void colorDialog::cs_2_Slot()
{
   emit colorChange("#10da3c", "#e60000", "#3ba3f8", "#ffffff","#ffaa7f", "#ffff7f");
}


void colorDialog::cs_3_Slot()
{
   emit colorChange( "#ffff7f", "#e60000", "#3ba3f8", "#ffffff","#ffaa7f","#10da3c");
}


void colorDialog::cs_4_Slot()
{
   emit colorChange("#f373ff","#e60000","#3ba3f8", "#ffffff","#aa0000","#55ff7f");
}


void colorDialog::cs_5_Slot()
{
    emit colorChange("#aa55ff", "#e60000","#3ba3f8", "#ffffff","#aa0000","#55ff7f");
}


void colorDialog::cs_6_Slot()
{
   emit colorChange("#ffaa00", "#e60000", "#0055ff",  "#ffffff", "#ffff7f", "#55ff7f");
}



void colorDialog::cs_7_Slot()
{
      emit colorChange("#2ecece", "#e60000", "#0055ff",  "#ffffff", "#ffff7f", "#55ff7f");
}


void colorDialog::cs_8_Slot()
{

   emit colorChange("#bbcceb", "#e60000", "#0055ff",  "#ffffff", "#ffff7f", "#55ff7f");
}


void colorDialog::cs_9_Slot()
{
   emit colorChange("#97aca2", "#e60000", "#0055ff",  "#ffffff", "#ffff7f", "#55ff7f");
}


void colorDialog::us_1_Slot()
{
    cout <<"us_1_Slot"<<endl;
    QColor newColor = QColorDialog::getColor();
    QString colorName = "<font color=\"" + newColor.name() + "\">C</font>";
    this->Label10->setText(colorName);
    
    QString tmp = Label10->text();
    QString color10 = tmp.section( "\"", 1, 1 );
    
     tmp = Label11->text();
    QString color11 = tmp.section( "\"", 1, 1 );
    
     tmp = Label12->text();
    QString color12 = tmp.section( "\"", 1, 1 );
    
     tmp = Label13->text();
    QString color13 = tmp.section( "\"", 1, 1 );
    
     tmp = Label14->text();
    QString color14 = tmp.section( "\"", 1, 1 );
    
     tmp = Label15->text();
    QString color15 = tmp.section( "\"", 1, 1 );
    
     tmp = Label16->text();
    QString color16 = tmp.section( "\"", 1, 1 );

    emit colorChange(color10, color11, color12, color13, color14, color14);
}


void colorDialog::us_2_Slot()
{
    cout <<"us_2_Slot"<<endl;
    QColor newColor = QColorDialog::getColor();
    QString colorName = "<font color=\"" + newColor.name() + "\">O</font>";
    this->Label11->setText(colorName);
    
    QString tmp = Label10->text();
    QString color10 = tmp.section( "\"", 1, 1 );
    
     tmp = Label11->text();
    QString color11 = tmp.section( "\"", 1, 1 );
    
     tmp = Label12->text();
    QString color12 = tmp.section( "\"", 1, 1 );
    
     tmp = Label13->text();
    QString color13 = tmp.section( "\"", 1, 1 );
    
     tmp = Label14->text();
    QString color14 = tmp.section( "\"", 1, 1 );
    
     tmp = Label15->text();
    QString color15 = tmp.section( "\"", 1, 1 );
    
     tmp = Label16->text();
    QString color16 = tmp.section( "\"", 1, 1 );

    emit colorChange(color10, color11, color12, color13, color14, color14);
}


void colorDialog::us_3_Slot()
{
    cout <<"us_3_Slot"<<endl;
    QColor newColor = QColorDialog::getColor();
    QString colorName = "<font color=\"" + newColor.name() + "\">N</font>";
    this->Label12->setText(colorName);
    
    QString tmp = Label10->text();
    QString color10 = tmp.section( "\"", 1, 1 );
    
     tmp = Label11->text();
    QString color11 = tmp.section( "\"", 1, 1 );
    
     tmp = Label12->text();
    QString color12 = tmp.section( "\"", 1, 1 );
    
     tmp = Label13->text();
    QString color13 = tmp.section( "\"", 1, 1 );
    
     tmp = Label14->text();
    QString color14 = tmp.section( "\"", 1, 1 );
    
     tmp = Label15->text();
    QString color15 = tmp.section( "\"", 1, 1 );
    
     tmp = Label16->text();
    QString color16 = tmp.section( "\"", 1, 1 );

    emit colorChange(color10, color11, color12, color13, color14, color14);
}


void colorDialog::us_4_Slot()
{
    cout <<"us_4_Slot"<<endl;
    QColor newColor = QColorDialog::getColor();
    QString colorName = "<font color=\"" + newColor.name() + "\">H</font>";
    this->Label13->setText(colorName);
    
    QString tmp = Label10->text();
    QString color10 = tmp.section( "\"", 1, 1 );
    
     tmp = Label11->text();
    QString color11 = tmp.section( "\"", 1, 1 );
    
     tmp = Label12->text();
    QString color12 = tmp.section( "\"", 1, 1 );
    
     tmp = Label13->text();
    QString color13 = tmp.section( "\"", 1, 1 );
    
     tmp = Label14->text();
    QString color14 = tmp.section( "\"", 1, 1 );
    
     tmp = Label15->text();
    QString color15 = tmp.section( "\"", 1, 1 );
    
     tmp = Label16->text();
    QString color16 = tmp.section( "\"", 1, 1 );

    emit colorChange(color10, color11, color12, color13, color14, color14);
}


void colorDialog::us_5_Slot()
{
    cout <<"us_5_Slot"<<endl;
    QColor newColor = QColorDialog::getColor();
    QString colorName = "<font color=\"" + newColor.name() + "\">S</font>";
    this->Label14->setText(colorName);
    
    QString tmp = Label10->text();
    QString color10 = tmp.section( "\"", 1, 1 );
    
     tmp = Label11->text();
    QString color11 = tmp.section( "\"", 1, 1 );
    
     tmp = Label12->text();
    QString color12 = tmp.section( "\"", 1, 1 );
    
     tmp = Label13->text();
    QString color13 = tmp.section( "\"", 1, 1 );
    
     tmp = Label14->text();
    QString color14 = tmp.section( "\"", 1, 1 );
    
     tmp = Label15->text();
    QString color15 = tmp.section( "\"", 1, 1 );
    
     tmp = Label16->text();
    QString color16 = tmp.section( "\"", 1, 1 );

    emit colorChange(color10, color11, color12, color13, color14, color14);
}


void colorDialog::us_6_Slot()
{
    cout <<"us_6_Slot"<<endl;
    QColor newColor = QColorDialog::getColor();
    QString colorName = "<font color=\"" + newColor.name() + "\">P</font>";
    this->Label15->setText(colorName);
    
    QString tmp = Label10->text();
    QString color10 = tmp.section( "\"", 1, 1 );
    
     tmp = Label11->text();
    QString color11 = tmp.section( "\"", 1, 1 );
    
     tmp = Label12->text();
    QString color12 = tmp.section( "\"", 1, 1 );
    
     tmp = Label13->text();
    QString color13 = tmp.section( "\"", 1, 1 );
    
     tmp = Label14->text();
    QString color14 = tmp.section( "\"", 1, 1 );
    
     tmp = Label15->text();
    QString color15 = tmp.section( "\"", 1, 1 );
    
     tmp = Label16->text();
    QString color16 = tmp.section( "\"", 1, 1 );

    emit colorChange(color10, color11, color12, color13, color14, color14);
}


void colorDialog::us_7_Slot()
{
    cout <<"us_7_Slot"<<endl;
    QColor newColor = QColorDialog::getColor();
    QString colorName = "<font color=\"" + newColor.name() + "\">X</font>";
    this->Label16->setText(colorName);
    
    QString tmp = Label10->text();
    QString color10 = tmp.section( "\"", 1, 1 );
    
     tmp = Label11->text();
    QString color11 = tmp.section( "\"", 1, 1 );
    
     tmp = Label12->text();
    QString color12 = tmp.section( "\"", 1, 1 );
    
     tmp = Label13->text();
    QString color13 = tmp.section( "\"", 1, 1 );
    
     tmp = Label14->text();
    QString color14 = tmp.section( "\"", 1, 1 );
    
     tmp = Label15->text();
    QString color15 = tmp.section( "\"", 1, 1 );
    
     tmp = Label16->text();
    QString color16 = tmp.section( "\"", 1, 1 );

    emit colorChange(color10, color11, color12, color13, color14, color14);
    
}


void colorDialog::us_8_Slot()
{ //SLOT IS OPEN
    cout <<"us_8_Slot"<<endl;
    QColor newColor = QColorDialog::getColor();
    QString colorName = "<font color=\"" + newColor.name() + "\">C</font>";
    //this->Label17->setText(colorName);
}


void colorDialog::us_9_Slot()
{ //SLOT IS OPEN
    cout <<"us_9_Slot"<<endl;
    QColor newColor = QColorDialog::getColor();
    QString colorName = "<font color=\"" + newColor.name() + "\">C</font>";
    //this->Label18->setText(colorName);
}




void colorDialog::saveColorSlot()
{
QString tmp = Label10->text();
    QString color10 = tmp.section( "\"", 1, 1 );
    
     tmp = Label11->text();
    QString color11 = tmp.section( "\"", 1, 1 );
    
     tmp = Label12->text();
    QString color12 = tmp.section( "\"", 1, 1 );
    
     tmp = Label13->text();
    QString color13 = tmp.section( "\"", 1, 1 );
    
     tmp = Label14->text();
    QString color14 = tmp.section( "\"", 1, 1 );
    
     tmp = Label15->text();
    QString color15 = tmp.section( "\"", 1, 1 );
    
     tmp = Label16->text();
    QString color16 = tmp.section( "\"", 1, 1 );
    
    //You need to add code here to save the default color
}
