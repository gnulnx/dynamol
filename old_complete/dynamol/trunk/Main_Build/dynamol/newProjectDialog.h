/****************************************************************************
** Form interface generated from reading ui file 'newProjectDialog.ui'
**
** Created: Thu Nov 18 12:10:22 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTextEdit;
class QLineEdit;
class QLabel;

class newProject : public QDialog
{
    Q_OBJECT

public:
    newProject( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~newProject();

    QPushButton* buttonHelp;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QTextEdit* descEdit;
    QLineEdit* nameEdit;
    QLabel* Name;
    QLabel* author;
    QLabel* date;
    QLineEdit* dateEdit;
    QLabel* description;
    QLineEdit* authoredit;

protected:
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;
    QVBoxLayout* layout8;

protected slots:
    virtual void languageChange();

};

#endif // NEWPROJECT_H





































