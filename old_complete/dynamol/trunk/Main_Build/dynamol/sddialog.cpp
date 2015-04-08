/***************************************************************************
                          sddialog.cpp  -  description
                             -------------------
    begin                : Thu Dec 4 2003
    copyright            : (C) 2003 by John Furr
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, ||     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "sddialog.h"
#include "moldb.h"

sdDialog::sdDialog(QWidget *parent, const char *name, bool modal, int records )
: QDialog(parent,name, modal)
{
  setMinimumSize(255, 170);
  setMaximumSize(255, 170);
  this->records = records;
  QString tmp;
  tmp.setNum(records);
  QString header = "Total Number of Records: ";
  header += tmp;
  headerLabel = new QLabel(header, this); 
  headerLabel->setGeometry(10, 5, 200, 20);
  
  group1 = new QButtonGroup("Import", this);
  group1->setGeometry(10, 30, 100, 80);
  group1->setRadioButtonExclusive(true);
  
  All = new QRadioButton("All", group1);
  All->setGeometry(5, 20, 60, 20);
  All->setChecked(true);
  Range = new QRadioButton("Range", group1);
  Range->setGeometry(3, 50, 60, 20);
  
  fromLabel = new QLabel("From", this);
  fromLabel->setGeometry(120, 60, 60, 20);
  
  toLabel = new QLabel("To", this);
  toLabel->setGeometry(185, 60, 60, 20);
  
  fromEdit = new QLineEdit("0", this);
  fromEdit->setGeometry(120, 90, 60, 20);
  fromEdit->setDisabled(true);
  
  toEdit = new QLineEdit(tmp, this);
  toEdit->setGeometry(185, 90, 60, 20);
  toEdit->setDisabled(true);
  
  Ok = new QPushButton("Ok", this);
  Ok->setGeometry(10, 120, 80, 40);
  
  Cancel = new QPushButton("Cancel", this);
  Cancel->setGeometry(105, 120, 80, 40);
  
  connect(group1, SIGNAL(pressed(int)), this, SLOT(enableEdit(int)));
  connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
  connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
}


sdDialog::~sdDialog(){
  delete headerLabel;
  delete All;
  delete Range;
  delete group1;
  delete toEdit;
  delete fromEdit;
  delete Ok;
  delete Cancel;
  delete fromLabel;
  delete toLabel;
}

void sdDialog::enableEdit(int num) {
   ////////////cout << "you are in sdDialog::enableEdit" << num << endl;
   
   if (num == 0) {
     fromEdit->setDisabled(true);
     fromEdit->setText("0");
     toEdit->setDisabled(true);
     QString tmp;
     tmp.setNum(records);
     toEdit->setText(tmp);
   } else if (num == 1) {
     fromEdit->setDisabled(false);
     toEdit->setDisabled(false);
   }
     
}







































