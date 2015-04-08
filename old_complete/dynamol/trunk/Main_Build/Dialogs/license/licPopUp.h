/****************************************************************************
** Form interface generated from reading ui file 'licPopUp.ui'
**
** Created: Thu Mar 17 06:32:31 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef LM_H
#define LM_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QFrame;
class QPushButton;

class lm : public QDialog
{
    Q_OBJECT

public:
    lm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~lm();

    QLabel* textLabel1;
    QLineEdit* edit1;
    QFrame* line1;
    QLineEdit* edit2;
    QFrame* line1_2;
    QLineEdit* edit3;
    QFrame* line1_2_2;
    QLineEdit* edit4;
    QFrame* line1_2_2_2;
    QLineEdit* edit5;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

protected:
    QGridLayout* lmLayout;
    QVBoxLayout* layout5;
    QHBoxLayout* layout3;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

};

#endif // LM_H
