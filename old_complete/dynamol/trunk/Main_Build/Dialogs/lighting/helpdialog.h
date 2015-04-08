/****************************************************************************
** Form interface generated from reading ui file 'helpdialog.ui'
**
** Created: Sat Nov 20 11:30:31 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.2   edited Nov 24 13:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTextEdit;

class helpDialog : public QDialog
{
    Q_OBJECT
    

public:
    helpDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~helpDialog();

    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QTextEdit* textEdit1;

protected:
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

};

#endif // HELPDIALOG_H
