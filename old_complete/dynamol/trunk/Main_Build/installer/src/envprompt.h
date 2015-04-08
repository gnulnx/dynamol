/****************************************************************************
** Form interface generated from reading ui file 'envprompt.ui'
**
** Created: Mon Feb 21 15:47:30 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef ENVPROMPT_H
#define ENVPROMPT_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTextEdit;
class QCheckBox;
class QPushButton;

class envprompt : public QDialog
{
    Q_OBJECT

public:
    envprompt( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~envprompt();

    QTextEdit* textEdit1;
    QCheckBox* checkBox;
    QPushButton* buttonOk;

protected:
    QVBoxLayout* layout5;
    QHBoxLayout* layout3;
    QSpacerItem* spacer2;
    QHBoxLayout* layout4;
    QSpacerItem* spacer3;

protected slots:
    virtual void languageChange();

};

#endif // ENVPROMPT_H
