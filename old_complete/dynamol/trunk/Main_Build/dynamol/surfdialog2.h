/****************************************************************************
** Form interface generated from reading ui file 'surfdialog2.ui'
**
** Created: Mon Feb 6 13:32:34 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SURFDIALOG2_H
#define SURFDIALOG2_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTabWidget;
class QWidget;
class QButtonGroup;
class QCheckBox;
class QGroupBox;
class QComboBox;
class QLabel;
class QSlider;

class surfDialog2 : public QDialog
{
    Q_OBJECT

public:
    surfDialog2( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~surfDialog2();

    QPushButton* buttonHelp;
    QPushButton* Done;
    QPushButton* Apply;
    QTabWidget* surfDialog;
    QWidget* Widget8;
    QButtonGroup* quality;
    QCheckBox* checkBox8;
    QCheckBox* checkBox9;
    QCheckBox* checkBox10;
    QGroupBox* groupBox1;
    QComboBox* color;
    QPushButton* Color;
    QLabel* textLabel1;
    QCheckBox* trans;
    QButtonGroup* tightness;
    QCheckBox* checkBox11;
    QCheckBox* checkBox12;
    QCheckBox* checkBox13;
    QWidget* Widget9;
    QGroupBox* groupBox5;
    QSlider* fineQuality;
    QLabel* textLabel2;
    QLabel* textLabel3;
    QGroupBox* groupBox6;
    QLabel* textLabel4;
    QLabel* textLabel5;
    QSlider* fineTight;
    QGroupBox* groupBox4;
    QSlider* slider3;
    QLabel* textLabel1_2;
    QLabel* textLabel2_2;

    float Blue;
    float Green;
    float Red;

public slots:
    virtual void helpSlot();
    virtual void applySlot();
    virtual void qualitySlot( int value );
    virtual void tightSlot( int value );
    virtual void transSlot( bool value );
    virtual void colorSlot();
    virtual void newSlot();

protected:
    QGridLayout* surfDialog2Layout;
    QGridLayout* layout5;
    QSpacerItem* Horizontal_Spacing2;
    QGridLayout* Widget8Layout;
    QGridLayout* qualityLayout;
    QVBoxLayout* groupBox1Layout;
    QGridLayout* layout1;
    QGridLayout* tightnessLayout;
    QGridLayout* Widget9Layout;
    QGridLayout* groupBox5Layout;
    QSpacerItem* spacer2;
    QGridLayout* groupBox6Layout;
    QGridLayout* groupBox4Layout;
    QSpacerItem* spacer3;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // SURFDIALOG2_H
