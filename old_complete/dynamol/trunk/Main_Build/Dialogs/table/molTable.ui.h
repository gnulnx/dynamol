/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor an
** destructor.
*****************************************************************************/

#include <iostream>
#include <iomanip>
#include "moltablesdexport.h"
#include "moltabletextexport.h"
#include <qlineedit.h>
#include <qcheckbox.h>
using namespace std;

void molTable::fileNew()
{
//   cout <<"fileNew()"<<endl;
}


void molTable::fileOpen()
{
  //  cout <<"Emitting openFile()"<<endl;
   emit openFile();
}


void molTable::fileSave()
{
//   cout <<"fileSave()"<<endl;
}


void molTable::fileSaveAs()
{

}


void molTable::filePrint()
{

}


void molTable::fileExit()
{

}


void molTable::editUndo()
{

}


void molTable::editRedo()
{

}


void molTable::editCut()
{

}


void molTable::editCopy()
{

}


void molTable::editPaste()
{

}


void molTable::editFind()
{

}


void molTable::helpIndex()
{

}


void molTable::helpContents()
{

}


void molTable::helpAbout()
{

}


void molTable::molTable_toolBarPositionChanged( QToolBar * )
{

}


void molTable::fileOpenAction_2_activated()
{

}


void molTable::SDExportSlot()
{
//    cout <<"SDExportSlot()"<<endl;
    sdExport *dialog = new sdExport();
    int rowSelection = -1;
    int colSelection = -1;
    QString fileName;
    if (dialog->exec()) {
	if ( dialog->row_all->isChecked())
	    rowSelection = 0;
	if (dialog->row_sel->isChecked())
	    rowSelection = 1;
	if (dialog->row_un->isChecked())
	    rowSelection =2;
	
	if (dialog->col_all->isChecked())
	    colSelection = 0;
	if (dialog->col_sel->isChecked())
	    colSelection = 1;
	if (dialog->col_un->isChecked())	
	    colSelection = 2;
	
	fileName = dialog->fileName->text();
//	cout <<"File: " << fileName <<endl;
//	cout <<"row-col: " << rowSelection << setw(12) << colSelection << endl;
	emit sdExportSignal(fileName, rowSelection, colSelection);
    }
    
}


void molTable::textExportSlot()
{
    textExport *dialog = new textExport();
    
   int rowSelection = -1;
   int colSelection = -1;
   QString delim = ""; 
    QString fileName;
    if (dialog->exec()) {
	if ( dialog->row_all->isChecked())
	    rowSelection = 0;
	if (dialog->row_sel->isChecked())
	    rowSelection = 1;
	if (dialog->row_un->isChecked())
	    rowSelection =2;
	
	if (dialog->col_all->isChecked())
	    colSelection = 0;
	if (dialog->col_sel->isChecked())
	    colSelection = 1;
	if (dialog->col_un->isChecked())	
	    colSelection = 2;
	
	if (dialog->tab->isChecked())
	    delim = "\t";
	if (dialog->space->isChecked())
	    delim = " ";
	if (dialog->comma->isChecked())
	    delim = ",";
	if (dialog->other->isChecked())
	    delim = dialog->otherEdit->text();

	fileName = dialog->fileName->text();
//	cout <<"File: " << fileName <<endl;
//	cout <<"row-col: " << rowSelection << setw(12) << colSelection << endl;
	//emit sdExportSignal(fileName, rowSelection, colSelection);
	emit textExportSignal(fileName, delim, rowSelection, colSelection);
    }
    
}


void molTable::calculateFingerPrintsgaffFPAction_activated()
{
//   cout <<"You are in calculateFingerPrintsgaffFPAction_activated()"<<endl;
   emit gaffFPSignal();
}


void molTable::showPrevSlot()
{
    emit clearListView();
    int currRow = table1->currentRow();
    table1->clearSelection();
    if (currRow != 0) {
       table1->selectRow(currRow-1);   
       table1->setCurrentCell(currRow-1, 0);
       showSelectedSignal();
    }
}


void molTable::showNextSlot()
{
    emit clearListView();
    int currRow = table1->currentRow();
    if (currRow != table1->numRows()) {
       table1->clearSelection();
       table1->selectRow(currRow+1);
       table1->setCurrentCell(currRow+1, 0);
//       cout <<"showNextSlot()   "<< currRow << endl;
       showSelectedSignal();
    }
}
