/****************************************************************************
** Form interface generated from reading ui file 'sysHelpDialog.ui'
**
** Created: Sun Apr 3 16:19:35 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SYSHELPDIALOG_H
#define SYSHELPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTextEdit;
class QPushButton;

class sysHelpDialog : public QDialog
{
    Q_OBJECT

public:
    sysHelpDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~sysHelpDialog();

    QTextEdit* textEdit1;
    QPushButton* buttonOk;

protected:
    QVBoxLayout* layout40;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

};

#endif // SYSHELPDIALOG_H
























