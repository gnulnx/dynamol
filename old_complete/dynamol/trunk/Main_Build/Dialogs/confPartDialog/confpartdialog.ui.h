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
#include <qfiledialog.h>
#include <string>
#include <qstring.h>

using namespace std;

void confPartDialog::getSaveAsSlot()
{
QString fileName = QFileDialog::getSaveFileName(
                    "./",
                    "Molecules (*.sdf *.SDF)",
                    this,
                    "open file dialog",
                    "Choose a file" );
    saveAs->setText(fileName);

}
