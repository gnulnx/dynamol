/***************************************************************************
                          sddialog.h  -  description
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

#ifndef SDDIALOG_H
#define SDDIALOG_H

#include <qwidget.h>
#include <qdialog.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qbuttongroup.h>
#include <qlineedit.h>
//#include <qtextlabel.h>
#include <qlabel.h>
#include <qstring.h>

#include <iostream>

using namespace std;

/**
  *@author John Furr
  */

class molDB;

class sdDialog : public QDialog  {
   Q_OBJECT
public: 
	sdDialog(QWidget *parent=0, const char *name=0, bool modal = true, int records = 0);
  void  setNumOfRecords(int records, molDB *db);
	~sdDialog();
  
  QPushButton *Ok, *Cancel;
  QRadioButton *All, *Range;
  QButtonGroup *group1;
  QLabel *headerLabel, *fromLabel, *toLabel;
  QLineEdit  *fromEdit, *toEdit;
  
  molDB *db;
private:
  int records;

  
public slots:
   void enableEdit(int);
};

#endif





































