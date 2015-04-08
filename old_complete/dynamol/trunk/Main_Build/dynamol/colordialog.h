/****************************************************************************
** Form interface generated from reading ui file 'colordialog.ui'
**
** Created: Wed Feb 22 22:52:28 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <qstring.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QButtonGroup;
class QLabel;
class QPushButton;
class QGroupBox;

class colorDialog : public QDialog
{
    Q_OBJECT

public:
    colorDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~colorDialog();

    QButtonGroup* buttonGroup1;
    QLabel* Label1;
    QPushButton* pushButton1;
    QLabel* Label2;
    QPushButton* pushButton2;
    QLabel* Label3;
    QPushButton* pushButton3;
    QLabel* Label4;
    QPushButton* pushButton4;
    QLabel* Label5;
    QPushButton* pushButton5;
    QLabel* Label6;
    QPushButton* pushButton6;
    QLabel* Label7;
    QPushButton* pushButton7;
    QLabel* Label8;
    QPushButton* pushButton8;
    QLabel* Label9;
    QPushButton* pushButton9;
    QGroupBox* groupBox1;
    QLabel* Label10;
    QLabel* Label11;
    QLabel* Label12;
    QLabel* Label13;
    QLabel* Label14;
    QLabel* Label15;
    QLabel* Label16;
    QPushButton* pushButton10;
    QPushButton* pushButton11;
    QPushButton* pushButton12;
    QPushButton* pushButton13;
    QPushButton* pushButton14;
    QPushButton* pushButton15;
    QPushButton* pushButton16;
    QPushButton* pushButton17;

public slots:
    virtual void cs_1_Slot();
    virtual void cs_2_Slot();
    virtual void cs_3_Slot();
    virtual void cs_4_Slot();
    virtual void cs_5_Slot();
    virtual void cs_6_Slot();
    virtual void cs_7_Slot();
    virtual void cs_8_Slot();
    virtual void cs_9_Slot();
    virtual void us_1_Slot();
    virtual void us_2_Slot();
    virtual void us_3_Slot();
    virtual void us_4_Slot();
    virtual void us_5_Slot();
    virtual void us_6_Slot();
    virtual void us_7_Slot();
    virtual void us_8_Slot();
    virtual void us_9_Slot();
    virtual void saveColorSlot();

signals:
    void colorChange(QString C, QString O, QString N, QString H, QString S, QString P);

protected:
    QGridLayout* colorDialogLayout;
    QGridLayout* buttonGroup1Layout;
    QVBoxLayout* layout28;
    QHBoxLayout* layout19;
    QHBoxLayout* layout19_2;
    QHBoxLayout* layout19_2_2;
    QHBoxLayout* layout19_2_2_2;
    QHBoxLayout* layout19_2_2_2_2;
    QHBoxLayout* layout19_2_2_2_2_2;
    QHBoxLayout* layout19_2_2_2_2_2_2;
    QHBoxLayout* layout19_2_2_2_2_2_2_2;
    QHBoxLayout* layout19_2_2_2_2_2_2_2_2;
    QGridLayout* groupBox1Layout;
    QHBoxLayout* layout16;
    QVBoxLayout* layout15;
    QVBoxLayout* layout14;

protected slots:
    virtual void languageChange();

};

#endif // COLORDIALOG_H
