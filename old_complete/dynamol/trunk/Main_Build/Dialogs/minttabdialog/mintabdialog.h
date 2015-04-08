/****************************************************************************
** Form interface generated from reading ui file 'mintabdialog.ui'
**
** Created: Wed Nov 9 08:01:50 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MINTABDIALOG_H
#define MINTABDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class QWidget;
class QLabel;
class QLineEdit;
class QComboBox;
class QFrame;
class QGroupBox;
class QPushButton;

class minTabDialog : public QDialog
{
    Q_OBJECT

public:
    minTabDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~minTabDialog();

    QTabWidget* MinTab;
    QWidget* Widget8;
    QLabel* textLabel1_3;
    QLineEdit* jobName;
    QLabel* methodLabel;
    QComboBox* methodCombo;
    QFrame* line1;
    QGroupBox* mmGroup;
    QLabel* textLabel2;
    QLabel* chargeLabel;
    QLabel* descentLabel;
    QLabel* dieLabel;
    QLabel* textLabel1_2;
    QComboBox* ffCombo;
    QComboBox* chargeCombo;
    QComboBox* descentCombo;
    QComboBox* dieCombo;
    QLineEdit* dieValue;
    QGroupBox* semiGroup;
    QComboBox* theoryCombo;
    QLabel* theoryLabel;
    QWidget* Widget9;
    QLabel* textLabel1;
    QLineEdit* rmsefEdit;
    QLineEdit* maxForceEdit;
    QLineEdit* eDiffEdit;
    QLineEdit* maxIterEdit;
    QLabel* textLabel2_2;
    QLabel* textLabel3;
    QLabel* textLabel4;
    QLabel* textLabel5;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QPushButton* buttonHelp;

public slots:
    virtual void MinTab_destroyed( QObject * );
    virtual void methodChangedSlot( const QString & method );
    virtual void dieChanged( const QString & value );
    virtual void helpSlot();

protected:
    QGridLayout* minTabDialogLayout;
    QVBoxLayout* layout92;
    QGridLayout* Widget8Layout;
    QVBoxLayout* layout74;
    QHBoxLayout* layout73;
    QSpacerItem* spacer7;
    QVBoxLayout* layout72;
    QHBoxLayout* layout60;
    QHBoxLayout* layout59;
    QHBoxLayout* layout50;
    QGridLayout* mmGroupLayout;
    QHBoxLayout* layout49;
    QVBoxLayout* layout20;
    QVBoxLayout* layout48;
    QHBoxLayout* layout47;
    QSpacerItem* spacer4;
    QVBoxLayout* semiGroupLayout;
    QGridLayout* layout28;
    QGridLayout* Widget9Layout;
    QVBoxLayout* layout86;
    QSpacerItem* spacer11;
    QHBoxLayout* layout82;
    QSpacerItem* spacer9;
    QHBoxLayout* layout85;
    QSpacerItem* spacer12;
    QVBoxLayout* layout77;
    QVBoxLayout* layout79;
    QHBoxLayout* layout91;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

    void init();

};

#endif // MINTABDIALOG_H
