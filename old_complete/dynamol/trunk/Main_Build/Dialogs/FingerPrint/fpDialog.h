/****************************************************************************
** Form interface generated from reading ui file 'fpDialog.ui'
**
** Created: Wed Aug 17 12:31:40 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FPDIALOG_H
#define FPDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>
#include <map>
#include <set>
#include <vector>
#include "gaff_fp_progress.h"
#include "gafffpnet.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class QWidget;
class QLabel;
class QFrame;
class QPushButton;
class QLineEdit;
class QButtonGroup;
class QRadioButton;

class fpDialog : public QDialog
{
    Q_OBJECT

public:
    fpDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~fpDialog();

    QTabWidget* tabWidget2;
    QWidget* tab;
    QLabel* textLabel5;
    QFrame* line4;
    QPushButton* sdLoadSelect;
    QLabel* textLabel1;
    QLineEdit* sdLoadFile;
    QPushButton* fpSaveSelect;
    QLabel* textLabel1_3;
    QLineEdit* fpSaveFile;
    QFrame* line3;
    QPushButton* Build;
    QWidget* tab_2;
    QLabel* textLabel3;
    QFrame* line10;
    QLabel* textLabel1_2;
    QLineEdit* fpTrainFile1;
    QPushButton* fpLoadSelect1;
    QLabel* textLabel1_2_4;
    QLineEdit* fpTestFile1;
    QPushButton* fpLoadSelect1_3;
    QFrame* line7;
    QLabel* textLabel2;
    QLineEdit* minProbEdit;
    QLabel* textLabel2_2;
    QLineEdit* descNumEdit;
    QFrame* line9;
    QPushButton* testModel;
    QFrame* line1;
    QLabel* textLabel4;
    QLineEdit* hitRate;
    QLabel* textLabel4_3;
    QLineEdit* hitRate_3;
    QLabel* textLabel4_3_2;
    QLineEdit* hitRate_3_2;
    QWidget* TabPage;
    QFrame* line5_3;
    QLabel* textLabel4_2;
    QLabel* textLabel4_2_2;
    QLabel* textLabel4_2_4;
    QLineEdit* hitRate_2;
    QLineEdit* hitRate_2_2;
    QLineEdit* hitRate_2_3;
    QFrame* line5;
    QPushButton* testModel_2;
    QLabel* textLabel1_4;
    QLineEdit* numResults;
    QLabel* textLabel1_2_2;
    QLineEdit* fpActive;
    QPushButton* fpLoadSelect2;
    QLabel* textLabel1_2_2_2;
    QLineEdit* testFile2;
    QPushButton* fpLoadSelect2_2;
    QFrame* line5_2;
    QButtonGroup* buttonGroup1;
    QRadioButton* radioLocal;
    QRadioButton* radioZinc;
    QFrame* line12;
    QPushButton* fpLoadLocal;
    QLabel* textLabel6;
    QLineEdit* localFile;
    QPushButton* buttonHelp;
    QPushButton* buttonOk;

    virtual bool hitsToMapVec( std::vector<std::pair<QString, float> > & mapVec, std::map<QString, float> & Hits );
    virtual bool localFileSearch( QString & locFile, int numHits, std::map<QString, float> & Hits );
    virtual bool localFileSearch2( QString & locFile, int numHits, std::map<QString, float> & Hits );
    virtual void newFunction();

public slots:
    virtual void sdLoadSelectSlot();
    virtual void fpSaveSelectSlot();
    virtual void fpLoadSelectSlot();
    virtual void fpLoadSelect2Slot();
    virtual void fpLoadLocalSlot();
    virtual void fpLoadSelect2_2Slot();
    virtual void fpBuildSlot();
    virtual void testFile2Slot();
    virtual void fpSaveChangedSlot( const QString & text );
    virtual void testModelSlot();
    virtual void seachLibrarySlot();
    virtual void dbClickedSlot();
    virtual void busySlot();
    virtual void gaffFpDoneSlot();
    virtual void helpSlot();
    virtual void zincSlot( bool state );

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

    virtual bool entropyAndFeatures( QString & activeFile );
    virtual bool scoreAct_andTest( std::map<QString, float> & Hits, std::set<QString> & activeNames, std::set<QString> & act_and_test );
    virtual bool fileCheck( QString & fileName );

    QGridLayout* fpDialogLayout;
    QVBoxLayout* layout213;
    QGridLayout* tabLayout;
    QVBoxLayout* layout158;
    QVBoxLayout* layout157;
    QVBoxLayout* layout156;
    QVBoxLayout* layout155;
    QVBoxLayout* layout154;
    QHBoxLayout* layout15;
    QHBoxLayout* layout16;
    QVBoxLayout* layout152;
    QSpacerItem* spacer24;
    QVBoxLayout* layout140;
    QHBoxLayout* layout139;
    QSpacerItem* spacer22;
    QSpacerItem* spacer21;
    QGridLayout* tabLayout_2;
    QSpacerItem* spacer27;
    QVBoxLayout* layout170;
    QVBoxLayout* layout167;
    QVBoxLayout* layout166;
    QVBoxLayout* layout165;
    QVBoxLayout* layout114;
    QVBoxLayout* layout23;
    QVBoxLayout* layout18;
    QHBoxLayout* layout4_2;
    QHBoxLayout* layout4_2_3;
    QHBoxLayout* layout8;
    QHBoxLayout* layout8_2;
    QVBoxLayout* layout130;
    QHBoxLayout* layout129;
    QSpacerItem* spacer19;
    QSpacerItem* spacer18;
    QVBoxLayout* layout169;
    QVBoxLayout* layout45;
    QVBoxLayout* layout31;
    QHBoxLayout* layout29;
    QHBoxLayout* layout29_2;
    QHBoxLayout* layout29_2_2;
    QGridLayout* TabPageLayout;
    QVBoxLayout* layout204;
    QHBoxLayout* layout96;
    QVBoxLayout* layout95;
    QVBoxLayout* layout76;
    QVBoxLayout* layout201;
    QHBoxLayout* layout200;
    QSpacerItem* spacer20;
    QHBoxLayout* layout199;
    QHBoxLayout* layout196;
    QVBoxLayout* layout209;
    QVBoxLayout* layout190;
    QHBoxLayout* layout184;
    QHBoxLayout* layout183;
    QVBoxLayout* layout208;
    QVBoxLayout* layout207;
    QHBoxLayout* layout23_2;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // FPDIALOG_H
