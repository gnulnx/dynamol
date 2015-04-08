/****************************************************************************
** Form interface generated from reading ui file 'labeldialog.ui'
**
** Created: Thu Mar 17 09:20:36 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef LABELDIALOG_H
#define LABELDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QCheckBox;
class QLineEdit;
class QPushButton;

class labelDialog : public QDialog
{
    Q_OBJECT

public:
    labelDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~labelDialog();

    QFrame* frame3;
    QCheckBox* symbol;
    QCheckBox* type;
    QCheckBox* charge;
    QFrame* frame4;
    QCheckBox* atomNum;
    QCheckBox* resName;
    QCheckBox* resNum;
    QFrame* frame5;
    QCheckBox* custom;
    QLineEdit* customEdit;
    QPushButton* clear;
    QPushButton* apply;
    QPushButton* buttonOk;

public slots:
    virtual void customSlot( bool toggle );
    virtual void clearSlot();

protected:
    QGridLayout* labelDialogLayout;
    QVBoxLayout* layout20;
    QVBoxLayout* layout19;
    QHBoxLayout* layout8;
    QGridLayout* frame3Layout;
    QVBoxLayout* layout3;
    QGridLayout* frame4Layout;
    QVBoxLayout* layout2;
    QGridLayout* frame5Layout;
    QHBoxLayout* layout4;
    QHBoxLayout* layout18;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

};

#endif // LABELDIALOG_H
