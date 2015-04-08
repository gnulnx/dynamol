/***************************************************************************
                          mollistviewdialog.h  -  description
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

#ifndef MOLLISTVIEWDIALOG_H
#define MOLLISTVIEWDIALOG_H

#include <qwidget.h>
#include <qdialog.h>
#include <qvbuttongroup.h>
#include <qhbuttongroup.h>
#include <qradiobutton.h>
#include <qpushbutton.h>

#include <iostream>

using namespace std;

/**
  *@author John Furr
  */

class molListViewDialog : public QDialog  {
   Q_OBJECT
public: 
	molListViewDialog(QWidget *parent=0, const char *name=0);
	~molListViewDialog();

private:
  void renderGroup();
  void displayGroup();
  void commitCancel(QWidget *parent);

  QVButtonGroup *vgroup;
  QHButtonGroup *hgroup;
  QRadioButton *rbutton;
  QPushButton *pbutton;

  //rs = renderState, as = atomState
  int rs, as;

public slots:
  void okPressed();
  void cancelPressed();
  void renderState(int);
  void atomState(int);
signals:
  void stateChanged(int render, int atoms);
};

#endif





































