/****************************************************************************
** Form interface generated from reading ui file 'fpdialog2.ui'
**
** Created: Mon Oct 17 13:19:31 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FPDIALOG2_H
#define FPDIALOG2_H

#include <qvariant.h>
#include <qwizard.h>
#include <map>
#include <set>
#include <vector>
#include "gaff_fp_progress.h"
#include "gafffpnet.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QWidget;
class QButtonGroup;
class QCheckBox;
class QGroupBox;
class QLabel;
class QComboBox;
class QPushButton;
class QLineEdit;
class QFrame;
class QSpinBox;
class molView;

class fpDialog2 : public QWizard
{
    Q_OBJECT

public:
    fpDialog2( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~fpDialog2();

    QWidget* WizardPage;
    QButtonGroup* buttonGroup1;
    QCheckBox* checkBox1_2;
    QCheckBox* checkBox1;
    QGroupBox* groupBox1;
    QLabel* textLabel3;
    QComboBox* fpType;
    QPushButton* Build;
    QLabel* textLabel2;
    QLabel* textLabel2_2;
    QLineEdit* sdLoadFile;
    QLineEdit* fpSaveFile;
    QPushButton* pushButton2;
    QPushButton* pushButton2_2;
    QWidget* WizardPage_2;
    QButtonGroup* buttonGroup2;
    QCheckBox* molViewQuery;
    QCheckBox* sdQuery;
    QLineEdit* queryFile;
    QPushButton* queryButton;
    QGroupBox* groupBox3;
    QCheckBox* checkBox5;
    QLineEdit* testSetFile;
    QPushButton* testSetButton;
    QWidget* WizardPage_3;
    QGroupBox* groupBox2;
    QComboBox* dbCombo;
    QLabel* textLabel4;
    QLineEdit* localFP;
    QPushButton* dbButton;
    QFrame* line1;
    QLabel* textLabel6;
    QSpinBox* hitNumBox;
    QGroupBox* groupBox5;
    QPushButton* pushButton7;
    QLabel* textLabel5_2_2;
    QLabel* textLabel5_2;
    QLineEdit* hitRate_2_3;
    QLineEdit* hitRate_2_2;
    QLineEdit* hitRate_2;
    QLabel* textLabel5;

    virtual void hitsToMapVec( std::vector<std::pair<QString, float> > & mapVec, std::map<QString, float> & Hits );
    virtual bool fileCheck( QString & fileName );
    virtual bool fileCheck2( QString fileName, int & count );
    virtual bool entropyAndFeatures( QString & activeFile );
    virtual bool scoreAct_andTest( std::map<QString, float> & Hits, std::set<QString> & activeNames, std::set<QString> & act_and_test );
    virtual void newFunction();
    virtual void setMolViewSlot( molView * viewer );

public slots:
    virtual void fpBuilderEnableSlot( int but );
    virtual void enableTestSetSlot( bool toggle );
    virtual void hitNumEnableSlot( QString & text );
    virtual void hitNumEnableSlot( const QString & text );
    virtual void sdBuildSlot();
    virtual void saveFpSlot();
    virtual void QueryLoadSlot();
    virtual void testSetLoadSlot();
    virtual void fpBuildSlot();
    virtual void searchLibrarySlot();
    virtual void busySlot();
    virtual void gaffFpDoneSlot();
    virtual void localDBSlot();
    virtual void helpSlotSlot();

signals:
    void runDone(QString &);

protected:
    std::set<QString> act_and_test;
    std::set<QString> activeNames;
    gaffProg *prog;
    QString gaff3SEPath;
    QString features;
    float minProb;
    int descNum;
    float hr;
    QString activeFile;
    QString testFile;
    gaffFpNet *gNet;
    molView *viewer;

    QGridLayout* WizardPageLayout;
    QGridLayout* buttonGroup1Layout;
    QGridLayout* groupBox1Layout;
    QVBoxLayout* layout8;
    QVBoxLayout* layout17;
    QVBoxLayout* layout16;
    QVBoxLayout* layout22;
    QGridLayout* WizardPageLayout_2;
    QGridLayout* buttonGroup2Layout;
    QVBoxLayout* layout17_2;
    QHBoxLayout* layout16_2;
    QGridLayout* groupBox3Layout;
    QGridLayout* WizardPageLayout_3;
    QGridLayout* groupBox2Layout;
    QVBoxLayout* layout15;
    QVBoxLayout* layout14;
    QHBoxLayout* layout13;
    QVBoxLayout* layout27;
    QVBoxLayout* layout26;
    QGridLayout* groupBox5Layout;

protected slots:
    virtual void languageChange();

};

#endif // FPDIALOG2_H

