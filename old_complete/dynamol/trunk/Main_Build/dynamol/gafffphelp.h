/****************************************************************************
** Form interface generated from reading ui file 'gafffphelp.ui'
**
** Created: Mon Oct 17 13:19:31 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GAFFFPHELP_H
#define GAFFFPHELP_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTextEdit;

class gafffpHelp : public QDialog
{
    Q_OBJECT

public:
    gafffpHelp( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~gafffpHelp();

    QPushButton* buttonOk;
    QTextEdit* textEdit1;

protected:
    QGridLayout* gafffpHelpLayout;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

};

#endif // GAFFFPHELP_H

