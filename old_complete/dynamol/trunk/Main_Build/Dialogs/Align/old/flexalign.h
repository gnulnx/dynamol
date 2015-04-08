/****************************************************************************
** Form interface generated from reading ui file 'flexalign.ui'
**
** Created: Sat Aug 20 11:10:32 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FLEXALIGN_H
#define FLEXALIGN_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QButtonGroup;
class QRadioButton;
class QLineEdit;
class QPushButton;
class QLabel;

class FlexAlign : public QDialog
{
    Q_OBJECT

public:
    FlexAlign( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~FlexAlign();

    QButtonGroup* buttonGroup1;
    QRadioButton* chargeButton;
    QLineEdit* chargeWeight;
    QRadioButton* volumeButton;
    QLineEdit* volumeWeight;
    QRadioButton* aromaButton;
    QLineEdit* aromaWeight;
    QPushButton* buttonHelp;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QLabel* textLabel1;
    QLineEdit* lineEdit1;
    QLabel* textLabel1_2;
    QLineEdit* lineEdit2;
    QPushButton* template_load;
    QPushButton* to_align_load;

public slots:
    virtual void tempLoadSlot();
    virtual void toAlignLoadSlot();

protected:
    QGridLayout* FlexAlignLayout;
    QGridLayout* buttonGroup1Layout;
    QVBoxLayout* layout11;
    QHBoxLayout* layout8;
    QHBoxLayout* layout8_2;
    QHBoxLayout* layout8_3;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;
    QHBoxLayout* layout18;
    QVBoxLayout* layout14;
    QHBoxLayout* layout2;
    QHBoxLayout* layout3;
    QVBoxLayout* layout17;

protected slots:
    virtual void languageChange();

};

#endif // FLEXALIGN_H
