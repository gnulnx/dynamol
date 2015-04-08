/****************************************************************************
** Form interface generated from reading ui file 'gaff_fp_progress.ui'
**
** Created: Wed Aug 3 12:54:52 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GAFFPROG_H
#define GAFFPROG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QCheckBox;
class QFrame;

class gaffProg : public QDialog
{
    Q_OBJECT

public:
    gaffProg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~gaffProg();

    QLabel* textLabel1;
    QCheckBox* check1;
    QCheckBox* check2;
    QCheckBox* check3;
    QFrame* line1;

protected:
    QGridLayout* gaffProgLayout;
    QVBoxLayout* layout2;

protected slots:
    virtual void languageChange();

};

#endif // GAFFPROG_H






