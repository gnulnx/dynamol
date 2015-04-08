/****************************************************************************
** Form interface generated from reading ui file 'mchelpdialog.ui'
**
** Created: Sun Apr 17 14:18:10 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MCHELPDIALOG_H
#define MCHELPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTextEdit;
class QPushButton;

class mcHelpDialog : public QDialog
{
    Q_OBJECT

public:
    mcHelpDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~mcHelpDialog();

    QTextEdit* textEdit1;
    QPushButton* buttonOk;

protected:
    QGridLayout* mcHelpDialogLayout;
    QVBoxLayout* layout16;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

};

#endif // MCHELPDIALOG_H
