/****************************************************************************
** Form interface generated from reading ui file 'buildHelpDialog.ui'
**
** Created: Sun Apr 3 16:18:49 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef BUILDHELPDIALOG_H
#define BUILDHELPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTextEdit;

class buildHelpDialog : public QDialog
{
    Q_OBJECT

public:
    buildHelpDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~buildHelpDialog();

    QPushButton* buttonOk;
    QTextEdit* textEdit1;

protected:
    QGridLayout* buildHelpDialogLayout;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

};

#endif // BUILDHELPDIALOG_H
























