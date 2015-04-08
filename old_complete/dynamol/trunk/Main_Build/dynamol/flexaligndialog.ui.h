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

#include "fcdialog.h"

//QT Includes
#include "qfiledialog.h"

void FlexAlignDialog::fineControlSlot()
{
   fcDialog *dialog = new fcDialog();
   if (dialog->exec()) {
       this->dynIter = dialog->dynIter->text();
       this->annealPercent = dialog->annealPercent->text();        
       this->rmse = dialog->rmse->text();
       this->maxForce = dialog->maxForce->text();
       this->minE = dialog->minEChange->text();
       this->rmseCoords = dialog->rmseCoords->text();
   }
   delete dialog;
}


void FlexAlignDialog::tempFileSlot()
{
   if (tempView->isChecked())
       tempFile->setEnabled(false);
    else
	tempFile->setEnabled(true);
}


void FlexAlignDialog::alignFileSlot()
{
    if (toAlignView->isChecked())
	toAlignFile->setEnabled(false);
    else
	toAlignFile->setEnabled(true);
}


void FlexAlignDialog::singleFileSlot()
{
   if (singleFile->isChecked())
       outFile->setEnabled(true);
   else 
       outFile->setEnabled(false);
}


void FlexAlignDialog::multiFileSlot()
{
   if (multiFile->isChecked())
       baseName->setEnabled(true);
   else
       outFile->setEnabled(false);
}


void FlexAlignDialog::newOutFileSlot()
{

   QString fileName = QFileDialog::getSaveFileName(
                    "./",
                    "Molecule (*.sdf)",
                    this,
                    "open file dialog",
                    "Choose a file" );

   outFile->setText(fileName);
}


void FlexAlignDialog::newMultiFileSlot()
{
   QString fileName = QFileDialog::getSaveFileName(
                    "./",
                    "Molecule (*.sdf)",
                    this,
                    "open file dialog",
                    "Choose a file" );
   baseName->setText(fileName);
}


void FlexAlignDialog::setTempFileSlot()
{
   QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "Molecules (*.sdf)",
                    this,
                    "open file dialog",
                    "Choose a file" );
   
   tempFile->setText(fileName);
}


void FlexAlignDialog::setAlignFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(
                    "./",
                    "Molecules (*.sdf)",
                    this,
                    "open file dialog",
                    "Choose a file" );
    toAlignFile->setText(fileName);
}
