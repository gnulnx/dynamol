/****************************************************************************
** Form interface generated from reading ui file 'moltabletextexport.ui'
**
** Created: Fri Aug 5 12:34:02 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef TEXTEXPORT_H
#define TEXTEXPORT_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;
class QButtonGroup;
class QCheckBox;

class textExport : public QDialog
{
    Q_OBJECT

public:
    textExport( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~textExport();

    QLabel* textLabel1;
    QLineEdit* fileName;
    QPushButton* browse;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QButtonGroup* buttonGroup1_2;
    QCheckBox* row_all;
    QCheckBox* row_sel;
    QCheckBox* row_un;
    QButtonGroup* buttonGroup1_2_2;
    QCheckBox* col_sel;
    QCheckBox* col_un;
    QCheckBox* col_all;
    QButtonGroup* buttonGroup3;
    QCheckBox* space;
    QCheckBox* comma;
    QCheckBox* other;
    QLineEdit* otherEdit;
    QCheckBox* tab;

public slots:
    virtual void browseSlot();
    virtual void otherClickedSlot( bool clicked );

protected:
    QGridLayout* textExportLayout;
    QHBoxLayout* layout5;
    QHBoxLayout* layout8;
    QHBoxLayout* layout9;
    QGridLayout* buttonGroup1_2Layout;
    QGridLayout* buttonGroup1_2_2Layout;
    QGridLayout* buttonGroup3Layout;
    QHBoxLayout* layout7;

protected slots:
    virtual void languageChange();

};

#endif // TEXTEXPORT_H
