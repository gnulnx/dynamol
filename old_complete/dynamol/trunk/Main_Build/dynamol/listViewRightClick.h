/****************************************************************************
** Form interface generated from reading ui file 'listViewRightClick.ui'
**
** Created: Mon Feb 28 14:15:24 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef LISTVIEWRIGHTCLICK_H
#define LISTVIEWRIGHTCLICK_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QButtonGroup;
class QRadioButton;

class listViewRightClick : public QDialog
{
    Q_OBJECT

public:
    listViewRightClick( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~listViewRightClick();

    QPushButton* buttonCancel;
    QButtonGroup* group1;
    QRadioButton* add;
    QRadioButton* clear;
    QButtonGroup* group2;
    QRadioButton* radioButton4;
    QRadioButton* radioButton5;
    QRadioButton* radioButton6;
    QRadioButton* radioButton7;
    QPushButton* buttonOk;

protected:
    QGridLayout* listViewRightClickLayout;
    QGridLayout* layout41;
    QGridLayout* layout40;
    QGridLayout* group1Layout;
    QVBoxLayout* layout52;
    QSpacerItem* spacer21;
    QVBoxLayout* layout50;
    QHBoxLayout* layout48;
    QSpacerItem* spacer18;
    QHBoxLayout* layout49;
    QGridLayout* group2Layout;
    QVBoxLayout* layout68;
    QHBoxLayout* layout58;
    QSpacerItem* spacer22;
    QHBoxLayout* layout59;
    QSpacerItem* spacer22_2;
    QHBoxLayout* layout64;
    QSpacerItem* spacer22_3;
    QHBoxLayout* layout61;
    QSpacerItem* spacer22_4;

protected slots:
    virtual void languageChange();

};

#endif // LISTVIEWRIGHTCLICK_H



























