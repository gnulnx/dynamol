/****************************************************************************
** Form interface generated from reading ui file 'eSetup.ui'
**
** Created: Sun Apr 3 16:19:35 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef ESETUP_H
#define ESETUP_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;

class eSetup : public QDialog
{
    Q_OBJECT

public:
    eSetup( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~eSetup();

    QLabel* textLabel1;
    QLabel* textLabel2;
    QLabel* textLabel3;
    QLabel* textLabel4;
    QLineEdit* rmse;
    QLineEdit* maxRMS;
    QLineEdit* minE;
    QLineEdit* maxIter;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

protected:
    QGridLayout* eSetupLayout;
    QVBoxLayout* layout10;
    QHBoxLayout* layout8;
    QVBoxLayout* layout7;
    QVBoxLayout* layout6;
    QHBoxLayout* layout9;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

};

#endif // ESETUP_H
