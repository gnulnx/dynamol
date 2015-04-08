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
#include <iomanip>
#include <qfiledialog.h>
#include "mchelpdialog.h"
using namespace std;



void mcDialog::dieSlot(const QString &method)
{
   if (method == "Distant Dependant") {
          dieValue->setEnabled(false);
   } else {
          dieValue->setEnabled(true); 
   }     
   
}


void mcDialog::outFileSlot()
{
 QFileDialog* fd = new QFileDialog(this, "file dialog" );
  fd->setMode( QFileDialog::AnyFile );
  if (fd->exec()) {
      string fileName = fd->selectedFile();   
      outFile->setText(fileName);
  }
}


void mcDialog::helpSlot()
{
   mcHelpDialog *dialog = new mcHelpDialog(this, "help dialog", true);
   if (dialog->exec()) {};
}

















