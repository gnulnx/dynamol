/****************************************************************************
** Form interface generated from reading ui file 'lighting.ui'
**
** Created: Sun Feb 20 18:09:22 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.2   edited Nov 24 13:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef LIGHTING_H
#define LIGHTING_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>
#include <vector>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class QWidget;
class QPushButton;
class QFrame;
class QLabel;
class QSpinBox;

class Lighting : public QDialog
{
    Q_OBJECT

public:
    Lighting( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~Lighting();

    QTabWidget* ribbons;
    QWidget* Widget8;
    QPushButton* buttonApply;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QPushButton* genLighSpecHelp_2;
    QFrame* frame3;
    QLabel* genLightPosLabel;
    QSpinBox* genLightPosZ;
    QSpinBox* genLightPosY;
    QLabel* textLabel1_2_2;
    QLabel* textLabel1;
    QSpinBox* genLightPosX;
    QLabel* textLabel1_2;
    QFrame* frame4;
    QLabel* genLightAmbLabel;
    QSpinBox* genLightAmbR;
    QSpinBox* genLightAmbG;
    QSpinBox* genLightAmbB;
    QLabel* genLightDifLabel;
    QSpinBox* genLightDifR;
    QSpinBox* genLightDifG;
    QSpinBox* genLightDifB;
    QLabel* genLightSpecLabel;
    QSpinBox* genLightSpecR;
    QSpinBox* genLightSpecG;
    QSpinBox* genLightSpecB;
    QWidget* Widget9;
    QPushButton* buttonApply_3;
    QPushButton* buttonOk_3;
    QPushButton* buttonCancel_3;
    QPushButton* genLighSpecHelp_2_3;
    QFrame* frame3_3;
    QLabel* genLightPosLabel_3;
    QSpinBox* genLightPosZ_3;
    QSpinBox* genLightPosY_3;
    QLabel* textLabel1_2_4;
    QLabel* textLabel1_2_2_3;
    QLabel* textLabel1_4;
    QSpinBox* genLightPosX_3;
    QFrame* frame4_3;
    QLabel* genLightAmbLabel_3;
    QSpinBox* genLightAmbR_3;
    QSpinBox* genLightAmbG_3;
    QSpinBox* genLightAmbB_3;
    QLabel* genLightDifLabel_3;
    QSpinBox* genLightDifR_3;
    QSpinBox* genLightDifG_3;
    QSpinBox* genLightDifB_3;
    QLabel* genLightSpecLabel_3;
    QSpinBox* genLightSpecR_3;
    QSpinBox* genLightSpecG_3;
    QSpinBox* genLightSpecB_3;

public slots:
    virtual void setGenLightProp( vector<float> & pos, vector<float> & amb, vector<float> & spec, vector<float> & dif );
    virtual void helpSlot();
    virtual void setRibLightProp( vector<float> & pos, vector<float> & amb, vector<float> & spec, vector<float> & dif );
    virtual void applySlot();

signals:
    void apply();

protected:
    QHBoxLayout* layout7;
    QSpacerItem* Horizontal_Spacing2;
    QGridLayout* layout47;
    QVBoxLayout* layout9;
    QHBoxLayout* layout23;
    QSpacerItem* spacer3;
    QHBoxLayout* layout24;
    QSpacerItem* spacer4;
    QHBoxLayout* layout25;
    QSpacerItem* spacer5;
    QHBoxLayout* layout7_3;
    QSpacerItem* Horizontal_Spacing2_3;
    QGridLayout* layout46;
    QVBoxLayout* layout9_3;
    QHBoxLayout* layout23_3;
    QSpacerItem* spacer3_3;
    QHBoxLayout* layout24_3;
    QSpacerItem* spacer4_3;
    QHBoxLayout* layout25_3;
    QSpacerItem* spacer5_3;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // LIGHTING_H
