#include <list>
using namespace std;

class molecule;
/****************************************************************************
** Form interface generated from reading ui file 'confdialog.ui'
**
** Created: Sun Apr 3 16:19:35 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CONFDIALOG_H
#define CONFDIALOG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QGroupBox;
class QSpinBox;
class QListView;
class QListViewItem;
class QCheckBox;

class confDialog : public QDialog
{
    Q_OBJECT

public:
    confDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~confDialog();

    QFrame* frame5;
    QLabel* textLabel1_3;
    QLineEdit* jobName;
    QLabel* textLabel1_2;
    QLineEdit* output;
    QPushButton* pushButton9;
    QFrame* line3_2;
    QGroupBox* groupBox3;
    QPushButton* Add;
    QPushButton* Delete;
    QLabel* textLabel1;
    QSpinBox* inc;
    QListView* infoBox;
    QGroupBox* groupBox2;
    QCheckBox* minCheck;
    QPushButton* eSetupButton;
    QCheckBox* cutCheck;
    QLineEdit* cutoff;
    QCheckBox* clusterCheck;
    QLineEdit* clusters;
    QFrame* line3;
    QPushButton* Help;
    QLabel* maxNum;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

    float rmse;
    int maxIter;
    float minE;
    float maxForce;

public slots:
    virtual void setMolList( list<molecule *> * ml );
    virtual void setMaxConf( unsigned long int num );
    virtual void addItem( QString ID, QString atm1, QString atm2, int angle );
    virtual void deleteSlot();
    virtual void addSelectedBonds();
    virtual void tryItemAdd( QString ID, QString ATM1, QString ATM2 );
    virtual void changeIncrement( const QString & value );
    virtual void keyPressSlot( QKeyEvent * event );
    virtual void listViewHighLight( QListViewItem * item );
    virtual void eSetupSlot();
    virtual void helpSlot();
    virtual void outFileSlot();

signals:
    void keyReleaseEvent( QKeyEvent * );
    void updateGL();

protected:
    QGridLayout* confDialogLayout;
    QGridLayout* frame5Layout;
    QVBoxLayout* layout23;
    QHBoxLayout* layout15;
    QHBoxLayout* layout7;
    QHBoxLayout* layout14;
    QSpacerItem* spacer2;
    QHBoxLayout* layout14_2;
    QGridLayout* groupBox3Layout;
    QGridLayout* groupBox2Layout;
    QHBoxLayout* layout11;
    QVBoxLayout* layout21;
    QHBoxLayout* layout52;
    QHBoxLayout* layout20;
    QVBoxLayout* layout15_2;
    QHBoxLayout* layout28;
    QSpacerItem* spacer11_2;
    QSpacerItem* spacer11;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

    void init();

};

#endif // CONFDIALOG_H
