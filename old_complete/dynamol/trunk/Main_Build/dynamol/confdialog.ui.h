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
#include <vector>
#include <list>
#include <iterator>
#include <qfiledialog.h>
#include "conformation.h"
#include "molecule.h"
#include "eSetup.h"
#include "sysHelpDialog.h"
#include "bond.h"
#include "atom.h"
using namespace std;

list<molecule *> *molList;
list<molecule *>::iterator molIterator;
vector<bond *> rotBonds;

void confDialog::init() {
   rmse = 0.05;
   maxIter = 5000;
   maxForce = 0.01;
   minE = 0.001;
}
void confDialog::setMolList(list<molecule *> *ml) {
    molList = ml;
    Conformation conf;
    
    unsigned long int totNum = 1;
    molIterator = molList->begin();
   for (molIterator; molIterator != molList->end(); molIterator++) {
      molecule *mol=*molIterator; 
      rotBonds.clear();
      conf.setRotableBonds(mol, rotBonds);
      for (int i=0; i<rotBonds.size(); i++) {
         bond *bd = rotBonds[i];
         if (bd->order == 1) {
           QString ATM1 = bd->fromAtom()->getSym();
           QString num1; num1.setNum( bd->fromAtom()->getNum());
           ATM1 += ":" + num1;  
           QString ATM2 = bd->toAtom()->getSym();
           QString num2; num2.setNum( bd->toAtom()->getNum());    
           ATM2 += ":" + num2; 
           unsigned long int tmpNum = 360/bd->defInc;
           totNum *= tmpNum;
           addItem(mol->getName(), ATM1, ATM2, bd->defInc);
         }
       }         
   }
   setMaxConf(totNum);
}
void confDialog::setMaxConf(unsigned long int num) {
    ////////cout <<"Changing maxConf  "<< num << endl;
    QString sNum; sNum.setNum(num);
    QString words = "Possible Conformations: " + sNum;
    maxNum->setText(words);
}

void confDialog::addItem(QString ID, QString atm1, QString atm2, int angle) {
    //QString sNum; sNum.setNum(num);
    QString sInc; sInc.setNum(angle);
    new QListViewItem(infoBox, ID, atm1, atm2, sInc);
}


void confDialog::deleteSlot()
{
   QListViewItemIterator it(infoBox);
   vector<QListViewItem *> Items;
  while ( it.current() ) {
      QListViewItem *item = it.current();
      if (it.current()->isSelected()) 
   Items.push_back(item);
      it++;
  }
  
  for (int i=0; i<Items.size(); i++) {
      delete Items[i];
  }
  
  QListViewItemIterator it2(infoBox);
  unsigned long int totNum = 1;
  while ( it2.current() ) {
      QListViewItem *item = it2.current();
      QString text =  it2.current()->text(3);
      
      if (text.length() > 0) {
          unsigned long int num = text.toInt();
          unsigned long int max = 360;
          if ( num != 0) totNum *= max/num;
      }
      it2++;
  }
  this->setMaxConf(totNum);
}


void confDialog::addSelectedBonds()
{
   molIterator = molList->begin();
   for (molIterator; molIterator != molList->end(); molIterator++) {
      molecule *mol=*molIterator; 
      for (int i=0; i<mol->bonds.size(); i++) {
        bond *bd = mol->bonds[i]; 
        if (bd->selected && bd->rotable) {
           QString ATM1 = bd->fromAtom()->getSym();
           QString num1; num1.setNum( bd->fromAtom()->getNum());
           ATM1 += ":" + num1;  
           QString ATM2 = bd->toAtom()->getSym();
           QString num2; num2.setNum( bd->toAtom()->getNum());    
           ATM2 += ":" + num2; 
           tryItemAdd(mol->getName(), ATM1, ATM2);
           
         }
      }
  }
   
   //This will update the display of the possible conformations
   QListViewItemIterator it2(infoBox);
  unsigned long int totNum = 1;
  while ( it2.current() ) {
      QListViewItem *item = it2.current();
      QString text =  it2.current()->text(3);
      
      if (text.length() > 0) {
          unsigned long int num = text.toInt();
          unsigned long int max = 360;
          if ( num != 0) totNum *= max/num;
      }
      it2++;
  }
  this->setMaxConf(totNum);
}

void confDialog::tryItemAdd(QString ID, QString ATM1, QString ATM2) {
 ////////cout <<"tryItemAdd"<<endl;   
 QListViewItemIterator it(infoBox);
 bool add = true;
  while ( it.current() ) {
      QListViewItem *item = it.current();
      QString from = it.current()->text ( 1 );
      QString to = it.current()->text ( 2 );
      if (from == ATM1 && to == ATM2) {
        add = false;
         break;
      }
      it++;
  }
  if (add) addItem(ID, ATM1, ATM2, 5);
}

void confDialog::changeIncrement( const QString &value )
{
    QString sValue= inc->text();
    ////////cout <<"changeIncrement"<<endl;
    QListViewItemIterator it(infoBox);
   vector<QListViewItem *> Items;
   unsigned long int totNum = 1;
  while ( it.current() ) {
      QListViewItem *item = it.current();
      if (it.current()->isSelected()) 
           it.current()->setText ( 3, sValue );
      
      QString text =  it.current()->text(3);
      
      if (text.length() > 0) {
          unsigned long int num = text.toInt();
          unsigned long int max = 360;
          if ( num != 0) totNum *= max/num;
      }
      it++;
  }
  
   ////////cout <<"Heading into setMaxConf"<<endl;
  this->setMaxConf(totNum);
    //# virtual void setText ( int column, const QString & text )
//# virtual QString text ( int column ) const
}


void confDialog::keyPressSlot( QKeyEvent *event )
{
    QString INC = inc->text();
    changeIncrement(INC);
}


void confDialog::listViewHighLight(QListViewItem *item)
{
   ////////cout <<"listViewHighLight"<<endl; 
   if (item != NULL) {   
      QString text = item->text(3);
      inc->setValue(text.toInt());
   }
}


void confDialog::eSetupSlot()
{
   ////////cout <<"You are in eSetup"<<endl;
   eSetup *eDialog = new eSetup(this, "eDialog", true);
  
   if (eDialog->exec() ) {
      rmse = eDialog->rmse->text().toFloat();
      maxIter = eDialog->maxIter->text().toInt();
      minE = eDialog->minE->text().toFloat();
      maxForce = eDialog->maxRMS->text().toFloat();
      ////////cout <<"Now a word from our sponsor"<<endl;   
   }
  
}


void confDialog::helpSlot()
{
   sysHelpDialog *hDialog = new sysHelpDialog(this, "help", true);
   if (hDialog->exec()) {}
}


void confDialog::outFileSlot()
{
   QFileDialog* fd = new QFileDialog(this, "file dialog" );
  fd->setMode( QFileDialog::AnyFile );
  if (fd->exec()) {
      string fileName = fd->selectedFile();   
      output->setText(fileName);
  }
}
























