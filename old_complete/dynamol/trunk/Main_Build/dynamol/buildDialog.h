/****************************************************************************
** Form interface generated from reading ui file 'buildDialog.ui'
**
** Created: Sun Apr 3 16:18:49 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef BUILDERDIALOG_H
#define BUILDERDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QButtonGroup;
class QCheckBox;
class QLabel;
class QComboBox;
class QPushButton;

class builderDialog : public QDialog
{
    Q_OBJECT

public:
    builderDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~builderDialog();

    QFrame* frame4;
    QButtonGroup* modeGroup;
    QCheckBox* draw;
    QCheckBox* retype;
    QCheckBox* Delete;
    QFrame* frame3;
    QButtonGroup* atomGroup;
    QLabel* textLabel2;
    QComboBox* otherAtom;
    QPushButton* bromine;
    QPushButton* hydrogen;
    QPushButton* flourine;
    QPushButton* carbon;
    QPushButton* oxygen;
    QPushButton* chlorine;
    QPushButton* nitrogen;
    QPushButton* iodine;
    QPushButton* sulfer;
    QPushButton* phos;
    QFrame* frame8;
    QButtonGroup* bondGroup;
    QCheckBox* doubleBond;
    QCheckBox* tripleBond;
    QCheckBox* singleBond;
    QFrame* line3_2;
    QFrame* frame7;
    QButtonGroup* ringGroup;
    QPushButton* sp3_8;
    QPushButton* sp3_7;
    QPushButton* sp2_7;
    QPushButton* sp2_8;
    QPushButton* sp3_6;
    QPushButton* sp2_6;
    QPushButton* sp3_5;
    QPushButton* sp2_5;
    QFrame* frame5;
    QButtonGroup* strucGroup;
    QPushButton* clean;
    QPushButton* remH;
    QPushButton* addH;
    QFrame* line1;
    QFrame* line3;
    QPushButton* buttonOk_2;
    QPushButton* Done;

public slots:
    virtual void atomChangeSlot();
    virtual void ringChangeSlot();
    virtual void modeChangedSlot();
    virtual void chiralFlipSlot();
    virtual void bondChangeSlot();
    virtual void helpSlot();

protected:
    QGridLayout* builderDialogLayout;
    QVBoxLayout* layout73;
    QVBoxLayout* layout72;
    QGridLayout* frame4Layout;
    QGridLayout* modeGroupLayout;
    QHBoxLayout* layout16;
    QVBoxLayout* layout71;
    QHBoxLayout* layout70;
    QGridLayout* frame3Layout;
    QGridLayout* atomGroupLayout;
    QGridLayout* layout36;
    QGridLayout* frame8Layout;
    QGridLayout* bondGroupLayout;
    QVBoxLayout* layout68;
    QVBoxLayout* layout67;
    QHBoxLayout* layout49;
    QGridLayout* frame7Layout;
    QGridLayout* ringGroupLayout;
    QGridLayout* frame5Layout;
    QGridLayout* strucGroupLayout;
    QVBoxLayout* layout50;
    QHBoxLayout* layout21;
    QHBoxLayout* layout20;
    QSpacerItem* spacer1_2_2;
    QHBoxLayout* layout10;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;
    QPixmap image6;
    QPixmap image7;
    QPixmap image8;

};

#endif // BUILDERDIALOG_H
























