/***************************************************************************
Copyright 2005 Dynamol Inc.
Created by John Furr
john.furr@dynamol.inc
*****************************************************************************/


#include <iostream>
#include <iomanip>
#include "minhelpdialog.h"

using namespace std;

void minTabDialog::init() {
    semiGroup->setEnabled(false);   
}
void minTabDialog::MinTab_destroyed( QObject * )
{
}

void minTabDialog::methodChangedSlot(const QString &method) {   if (method == "Molecular Mechanics") {
       semiGroup->setEnabled(false);
       mmGroup->setEnabled(true);
       MinTab->setTabEnabled(Widget9, true);
   }  else {
       semiGroup->setEnabled(true);
       mmGroup->setEnabled(false);
       MinTab->setTabEnabled(Widget9, false);
   }
}

void minTabDialog::dieChanged(const QString &value) {
    if (value == "Distant Dependant") {
       dieValue->setEnabled(false);
    } else {
       dieValue->setEnabled(true);
    }
 }




void minTabDialog::helpSlot()
{
   minHelpDialog *help = new minHelpDialog(this, "help", this);
   help->show();
}






























