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
#include <fstream>
#include <qfiledialog.h>
#include <qstring.h>

using namespace std;



void textExport::browseSlot()
{
    const QString dir = "./";
    const QString type = "*";
    const QString name = "Export SD FIle";
    const QString fileName = "Choose a file";
    QString s = QFileDialog::getSaveFileName(
                    dir,
                    type,
                    0,
                    name,
                    fileName);
    
//    cout <<"fileName is: " << fileName << endl;
    this->fileName->setText(s);
    
}


void textExport::otherClickedSlot( bool clicked)
{
      otherEdit->setEnabled(clicked);
}
