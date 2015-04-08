/****************************************************************************
** Form interface generated from reading ui file 'flexaligndialog.ui'
**
** Created: Fri Feb 24 08:05:55 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FLEXALIGNDIALOG_H
#define FLEXALIGNDIALOG_H

#include <qvariant.h>
#include <qwizard.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QWidget;
class QTextEdit;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;
class QButtonGroup;
class QComboBox;
class QSpinBox;

class FlexAlignDialog : public QWizard
{
    Q_OBJECT

public:
    FlexAlignDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~FlexAlignDialog();

    QWidget* WizardPage;
    QTextEdit* textEdit1;
    QGroupBox* groupBox3;
    QLabel* textLabel5;
    QLineEdit* tempFile;
    QPushButton* tempFileButton;
    QCheckBox* tempView;
    QCheckBox* tempFlex;
    QGroupBox* groupBox4;
    QCheckBox* toAlignView;
    QLabel* textLabel5_2;
    QLineEdit* toAlignFile;
    QPushButton* alignFileButton;
    QWidget* WizardPage_2;
    QTextEdit* textEdit1_2;
    QGroupBox* groupBox14;
    QCheckBox* singleFile;
    QLineEdit* outFile;
    QPushButton* outFileButton;
    QCheckBox* multiFile;
    QLineEdit* baseName;
    QPushButton* multiFileButton;
    QCheckBox* background;
    QLabel* textLabel1_4;
    QWidget* WizardPage_3;
    QButtonGroup* buttonGroup1;
    QLabel* textLabel1_3;
    QLineEdit* cw;
    QLabel* textLabel2;
    QLineEdit* vw;
    QLabel* textLabel3;
    QLineEdit* aw;
    QTextEdit* textEdit1_2_2;
    QWidget* WizardPage_4;
    QTextEdit* textEdit1_2_3;
    QGroupBox* groupBox1;
    QPushButton* pushButton6;
    QLabel* textLabel4_3;
    QLabel* textLabel4;
    QLabel* textLabel4_2;
    QLabel* textLabel4_2_2;
    QComboBox* chargeType;
    QLineEdit* maxMD;
    QLineEdit* MaxMin;
    QLineEdit* dielec;
    QWidget* lastPage;
    QTextEdit* textEdit1_2_4;
    QGroupBox* groupBox2;
    QLabel* textLabel1_2;
    QLineEdit* jobName;
    QLabel* poseNum_2;
    QSpinBox* Iterations;
    QLabel* poseNum;
    QSpinBox* poses;
    QLabel* textLabel1;
    QLineEdit* poseRMSE;
    QLabel* poseNum_3;
    QLineEdit* tanTerm;

    QString rmseCoords;
    QString rmse;
    QString dynIter;
    QString annealPercent;
    QString maxForce;
    QString minE;

public slots:
    virtual void fineControlSlot();
    virtual void tempFileSlot();
    virtual void alignFileSlot();
    virtual void singleFileSlot();
    virtual void multiFileSlot();
    virtual void newOutFileSlot();
    virtual void newMultiFileSlot();
    virtual void setTempFileSlot();
    virtual void setAlignFileSlot();

protected:
    QGridLayout* WizardPageLayout;
    QGridLayout* groupBox3Layout;
    QHBoxLayout* layout30;
    QGridLayout* groupBox4Layout;
    QHBoxLayout* layout31;
    QGridLayout* WizardPageLayout_2;
    QGridLayout* groupBox14Layout;
    QHBoxLayout* layout25;
    QHBoxLayout* layout21;
    QHBoxLayout* layout22;
    QHBoxLayout* layout39;
    QHBoxLayout* layout26;
    QGridLayout* WizardPageLayout_3;
    QHBoxLayout* layout81;
    QGridLayout* buttonGroup1Layout;
    QVBoxLayout* layout19;
    QHBoxLayout* layout13;
    QHBoxLayout* layout12_2;
    QHBoxLayout* layout18;
    QGridLayout* WizardPageLayout_4;
    QGridLayout* groupBox1Layout;
    QHBoxLayout* layout24;
    QVBoxLayout* layout23;
    QVBoxLayout* layout22_2;
    QGridLayout* lastPageLayout;
    QGridLayout* groupBox2Layout;
    QVBoxLayout* layout25_2;
    QHBoxLayout* layout24_2;
    QVBoxLayout* layout23_2;
    QVBoxLayout* layout22_3;
    QHBoxLayout* layout42_2_2;
    QVBoxLayout* layout21_2;
    QHBoxLayout* layout20;
    QHBoxLayout* layout19_2;
    QHBoxLayout* layout18_2;

protected slots:
    virtual void languageChange();

};

#endif // FLEXALIGNDIALOG_H
