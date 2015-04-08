/***************************************************************************
                          mollistviewdialog.cpp  -  description
                             -------------------
    begin                : Sun Jan 25 2004
    copyright            : (C) 2004 by John Furr
    email                : jrflnx@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, ||     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "mollistviewdialog.h"

molListViewDialog::molListViewDialog(QWidget *parent, const char *name ) : QDialog(parent,name) {
	////////////cout <<"You did make it here: " << endl;
  renderGroup();
  displayGroup();
  commitCancel(parent);
  rs = 3;
  as = 2;
}
molListViewDialog::~molListViewDialog(){
}

void molListViewDialog::renderGroup() {
  vgroup = new QVButtonGroup("Render Type", this, "Render Type");
  rbutton = new QRadioButton("CPK", vgroup);
  rbutton = new QRadioButton("Stick", vgroup);
  rbutton = new QRadioButton("Wire", vgroup);
  rbutton = new QRadioButton("No Change", vgroup);
  vgroup->setButton(3);
  vgroup->setGeometry(5, 5, 125, 135);
  connect(vgroup, SIGNAL(clicked(int)), this, SLOT(renderState(int)));
}
void molListViewDialog::displayGroup() {
  vgroup = new QVButtonGroup("Display Choice", this, "Display Choice");
  rbutton = new QRadioButton("Display Selected", vgroup);
  rbutton = new QRadioButton("Un-display Selected", vgroup);
  rbutton = new QRadioButton("Display All", vgroup);
  vgroup->setButton(2);
  vgroup->setGeometry(135, 5, 220, 135);
  connect(vgroup, SIGNAL(clicked(int)), this, SLOT(atomState(int)));
}

void molListViewDialog::commitCancel(QWidget *parent) {
  hgroup = new QHButtonGroup("Commit", this);
  pbutton = new QPushButton("Ok", hgroup);
  connect(pbutton, SIGNAL(clicked()), this, SLOT(okPressed()));
  pbutton = new QPushButton("Cancel", hgroup);
  connect(pbutton, SIGNAL(clicked()), this, SLOT(cancelPressed()));
  hgroup->setGeometry(5, 145, 345, 60);
}

void molListViewDialog::okPressed() {
  ////////////cout <<"you are in the Done(): " <<rs<<"   "<<as<< endl;
  emit stateChanged(rs, as);
  hide();
  //this->exit(1, 1);
}

void molListViewDialog::cancelPressed() {
  ////////////cout <<"you are in the Cancel(): " << endl;
  hide();
  //this->exit(1, 1);
}

void molListViewDialog::renderState(int rs) {
  this->rs = rs;
}

void molListViewDialog::atomState(int as) {
  this->as = as;
}




































