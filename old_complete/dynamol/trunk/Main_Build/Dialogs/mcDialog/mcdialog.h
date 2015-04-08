/****************************************************************************
** Form interface generated from reading ui file 'mcdialog.ui'
**
** Created: Sun Apr 17 14:18:10 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MCDIALOG_H
#define MCDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;
class QButtonGroup;
class QRadioButton;
class QComboBox;
class QSpinBox;

class mcDialog : public QDialog
{
    Q_OBJECT

public:
    mcDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~mcDialog();

    QLabel* textLabel1;
    QLineEdit* jobName;
    QLabel* textLabel2;
    QLineEdit* outFile;
    QPushButton* browse;
    QButtonGroup* buttonGroup1;
    QRadioButton* force;
    QRadioButton* regular;
    QRadioButton* torsional;
    QLabel* textLabel4;
    QLineEdit* temp;
    QLabel* textLabel5;
    QComboBox* dieMethod;
    QLabel* textLabel6;
    QLineEdit* dieValue;
    QLabel* textLabel4_2;
    QLineEdit* steps;
    QLabel* textLabel4_3;
    QSpinBox* output;
    QPushButton* buttonHelp;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

public slots:
    virtual void dieSlot( const QString & method );
    virtual void outFileSlot();
    virtual void helpSlot();

protected:
    QVBoxLayout* mcDialogLayout;
    QVBoxLayout* layout24;
    QVBoxLayout* layout21;
    QHBoxLayout* layout19;
    QSpacerItem* spacer7;
    QHBoxLayout* layout20;
    QSpacerItem* spacer6;
    QVBoxLayout* layout23;
    QHBoxLayout* layout17;
    QGridLayout* buttonGroup1Layout;
    QVBoxLayout* layout14;
    QHBoxLayout* layout10;
    QSpacerItem* spacer5;
    QHBoxLayout* layout7;
    QHBoxLayout* layout11;
    QSpacerItem* spacer4;
    QHBoxLayout* layout12;
    QSpacerItem* spacer3;
    QHBoxLayout* layout13;
    QSpacerItem* spacer2;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // MCDIALOG_H
