/****************************************************************************
** Form interface generated from reading ui file 'moltablesdexport.ui'
**
** Created: Fri Aug 5 12:34:02 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SDEXPORT_H
#define SDEXPORT_H

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

class sdExport : public QDialog
{
    Q_OBJECT

public:
    sdExport( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~sdExport();

    QLabel* textLabel1;
    QLineEdit* fileName;
    QPushButton* browse;
    QButtonGroup* buttonGroup1_2;
    QCheckBox* row_sel;
    QCheckBox* row_un;
    QCheckBox* row_all;
    QButtonGroup* buttonGroup1_2_2;
    QCheckBox* col_un;
    QCheckBox* col_all;
    QCheckBox* col_sel;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

public slots:
    virtual void browseSlot();

protected:
    QGridLayout* sdExportLayout;
    QVBoxLayout* layout9;
    QVBoxLayout* layout8;
    QHBoxLayout* layout5;
    QHBoxLayout* layout7;
    QGridLayout* buttonGroup1_2Layout;
    QGridLayout* buttonGroup1_2_2Layout;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

};

#endif // SDEXPORT_H






