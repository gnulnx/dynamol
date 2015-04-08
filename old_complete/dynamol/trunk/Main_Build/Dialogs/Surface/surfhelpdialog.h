/****************************************************************************
** Form interface generated from reading ui file 'surfhelpdialog.ui'
**
** Created: Mon Feb 6 13:32:34 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SURFHELPDIALOG_H
#define SURFHELPDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTextEdit;

class surfHelpDialog : public QDialog
{
    Q_OBJECT

public:
    surfHelpDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~surfHelpDialog();

    QPushButton* Done;
    QTextEdit* textEdit2;

protected:
    QGridLayout* surfHelpDialogLayout;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

};

#endif // SURFHELPDIALOG_H
