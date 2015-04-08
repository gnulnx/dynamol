/****************************************************************************
** Form interface generated from reading ui file 'descsel.ui'
**
** Created: Wed Jun 29 06:36:08 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef DESCSEL_H
#define DESCSEL_H
#include <QtGui>
#include <QApplication>
#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QListView;
class QListViewItem;

class descSel : public QDialog
{
    Q_OBJECT

public:
	descSel( QWidget* parent = 0, const char* name = 0, bool modal = FALSE);
    //descSel( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~descSel();

    QPushButton* buttonHelp;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QListView* listView;

protected:
    QGridLayout* descSelLayout;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

};

#endif // DESCSEL_H



