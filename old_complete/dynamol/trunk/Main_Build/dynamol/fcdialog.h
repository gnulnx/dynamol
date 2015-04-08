/****************************************************************************
** Form interface generated from reading ui file 'fcdialog.ui'
**
** Created: Fri Feb 24 08:05:56 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FCDIALOG_H
#define FCDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTextEdit;
class QGroupBox;
class QLabel;
class QSpinBox;
class QLineEdit;

class fcDialog : public QDialog
{
    Q_OBJECT

public:
    fcDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~fcDialog();

    QPushButton* buttonHelp;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QTextEdit* textEdit7;
    QGroupBox* groupBox8;
    QLabel* textLabel2;
    QSpinBox* dynIter;
    QLabel* textLabel1_3;
    QSpinBox* annealPercent;
    QLabel* textLabel2_2;
    QLineEdit* rmseCoords;
    QGroupBox* groupBox7;
    QLabel* textLabel1;
    QLabel* textLabel1_2;
    QLabel* textLabel1_2_2;
    QLineEdit* rmse;
    QLineEdit* maxForce;
    QLineEdit* minEChange;

protected:
    QGridLayout* fcDialogLayout;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;
    QGridLayout* groupBox8Layout;
    QVBoxLayout* layout32;
    QHBoxLayout* layout31;
    QVBoxLayout* layout30;
    QHBoxLayout* layout28;
    QHBoxLayout* layout29;
    QGridLayout* groupBox7Layout;
    QHBoxLayout* layout26;
    QVBoxLayout* layout25;
    QVBoxLayout* layout24;

protected slots:
    virtual void languageChange();

};

#endif // FCDIALOG_H
