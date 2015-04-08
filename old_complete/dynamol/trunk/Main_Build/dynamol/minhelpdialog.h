/****************************************************************************
** Form interface generated from reading ui file 'minhelpdialog.ui'
**
** Created: Wed Nov 9 08:01:50 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MINHELPDIALOG_H
#define MINHELPDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTextEdit;

class minHelpDialog : public QDialog
{
    Q_OBJECT

public:
    minHelpDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~minHelpDialog();

    QPushButton* buttonOk;
    QTextEdit* textEdit1;

protected:
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // MINHELPDIALOG_H

