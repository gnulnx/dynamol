/****************************************************************************
** Form interface generated from reading ui file 'confpartdialog.ui'
**
** Created: Fri Sep 23 07:06:44 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CONFPARTDIALOG_H
#define CONFPARTDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QLineEdit;
class QGroupBox;
class QSpinBox;

class confPartDialog : public QDialog
{
    Q_OBJECT

public:
    confPartDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~confPartDialog();

    QPushButton* buttonHelp;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QLabel* textLabel1;
    QLineEdit* saveAs;
    QPushButton* pushButton4;
    QGroupBox* groupBox1;
    QLineEdit* id;
    QLineEdit* c1;
    QLineEdit* c2;
    QSpinBox* popSize;
    QSpinBox* gen;
    QLabel* textLabel2;
    QLabel* textLabel2_2;
    QLabel* textLabel2_2_2;
    QLabel* textLabel3;
    QLabel* textLabel3_2;

public slots:
    virtual void getSaveAsSlot();

protected:
    QGridLayout* confPartDialogLayout;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;
    QHBoxLayout* layout2;
    QGridLayout* groupBox1Layout;
    QHBoxLayout* layout9;
    QVBoxLayout* layout7;
    QVBoxLayout* layout8;

protected slots:
    virtual void languageChange();

};

#endif // CONFPARTDIALOG_H
