/****************************************************************************
** Form implementation generated from reading ui file 'fpdialog2.ui'
**
** Created: Mon Oct 17 13:19:31 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "fpdialog2.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "molview.h"
#include "fpdialog2.ui.h"

/*
 *  Constructs a fpDialog2 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The wizard will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal wizard.
 */
fpDialog2::fpDialog2( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QWizard( parent, name, modal, fl )
{
    if ( !name )
	setName( "fpDialog2" );
    setModal( FALSE );

    WizardPage = new QWidget( this, "WizardPage" );
    WizardPageLayout = new QGridLayout( WizardPage, 1, 1, 11, 6, "WizardPageLayout"); 

    buttonGroup1 = new QButtonGroup( WizardPage, "buttonGroup1" );
    buttonGroup1->setAlignment( int( QButtonGroup::AlignAuto ) );
    buttonGroup1->setExclusive( TRUE );
    buttonGroup1->setColumnLayout(0, Qt::Vertical );
    buttonGroup1->layout()->setSpacing( 6 );
    buttonGroup1->layout()->setMargin( 11 );
    buttonGroup1Layout = new QGridLayout( buttonGroup1->layout() );
    buttonGroup1Layout->setAlignment( Qt::AlignTop );

    checkBox1_2 = new QCheckBox( buttonGroup1, "checkBox1_2" );

    buttonGroup1Layout->addWidget( checkBox1_2, 1, 0 );

    checkBox1 = new QCheckBox( buttonGroup1, "checkBox1" );
    checkBox1->setChecked( TRUE );

    buttonGroup1Layout->addWidget( checkBox1, 0, 0 );

    WizardPageLayout->addWidget( buttonGroup1, 0, 0 );

    groupBox1 = new QGroupBox( WizardPage, "groupBox1" );
    groupBox1->setEnabled( FALSE );
    groupBox1->setAlignment( int( QGroupBox::AlignHCenter ) );
    groupBox1->setColumnLayout(0, Qt::Vertical );
    groupBox1->layout()->setSpacing( 6 );
    groupBox1->layout()->setMargin( 11 );
    groupBox1Layout = new QGridLayout( groupBox1->layout() );
    groupBox1Layout->setAlignment( Qt::AlignTop );

    layout8 = new QVBoxLayout( 0, 0, 6, "layout8"); 

    textLabel3 = new QLabel( groupBox1, "textLabel3" );
    layout8->addWidget( textLabel3 );

    fpType = new QComboBox( FALSE, groupBox1, "fpType" );
    layout8->addWidget( fpType );

    groupBox1Layout->addMultiCellLayout( layout8, 0, 0, 0, 2 );

    Build = new QPushButton( groupBox1, "Build" );

    groupBox1Layout->addMultiCellWidget( Build, 2, 2, 0, 2 );

    layout17 = new QVBoxLayout( 0, 0, 6, "layout17"); 

    textLabel2 = new QLabel( groupBox1, "textLabel2" );
    layout17->addWidget( textLabel2 );

    textLabel2_2 = new QLabel( groupBox1, "textLabel2_2" );
    layout17->addWidget( textLabel2_2 );

    groupBox1Layout->addLayout( layout17, 1, 0 );

    layout16 = new QVBoxLayout( 0, 0, 6, "layout16"); 

    sdLoadFile = new QLineEdit( groupBox1, "sdLoadFile" );
    layout16->addWidget( sdLoadFile );

    fpSaveFile = new QLineEdit( groupBox1, "fpSaveFile" );
    layout16->addWidget( fpSaveFile );

    groupBox1Layout->addLayout( layout16, 1, 1 );

    layout22 = new QVBoxLayout( 0, 0, 6, "layout22"); 

    pushButton2 = new QPushButton( groupBox1, "pushButton2" );
    pushButton2->setMaximumSize( QSize( 45, 25 ) );
    layout22->addWidget( pushButton2 );

    pushButton2_2 = new QPushButton( groupBox1, "pushButton2_2" );
    pushButton2_2->setMaximumSize( QSize( 45, 25 ) );
    layout22->addWidget( pushButton2_2 );

    groupBox1Layout->addLayout( layout22, 1, 2 );

    WizardPageLayout->addWidget( groupBox1, 0, 1 );
    addPage( WizardPage, QString("") );

    WizardPage_2 = new QWidget( this, "WizardPage_2" );
    WizardPageLayout_2 = new QGridLayout( WizardPage_2, 1, 1, 11, 6, "WizardPageLayout_2"); 

    buttonGroup2 = new QButtonGroup( WizardPage_2, "buttonGroup2" );
    buttonGroup2->setExclusive( TRUE );
    buttonGroup2->setColumnLayout(0, Qt::Vertical );
    buttonGroup2->layout()->setSpacing( 6 );
    buttonGroup2->layout()->setMargin( 11 );
    buttonGroup2Layout = new QGridLayout( buttonGroup2->layout() );
    buttonGroup2Layout->setAlignment( Qt::AlignTop );

    molViewQuery = new QCheckBox( buttonGroup2, "molViewQuery" );

    buttonGroup2Layout->addWidget( molViewQuery, 0, 0 );

    layout17_2 = new QVBoxLayout( 0, 0, 6, "layout17_2"); 

    sdQuery = new QCheckBox( buttonGroup2, "sdQuery" );
    sdQuery->setChecked( TRUE );
    layout17_2->addWidget( sdQuery );

    layout16_2 = new QHBoxLayout( 0, 0, 6, "layout16_2"); 

    queryFile = new QLineEdit( buttonGroup2, "queryFile" );
    layout16_2->addWidget( queryFile );

    queryButton = new QPushButton( buttonGroup2, "queryButton" );
    queryButton->setMaximumSize( QSize( 45, 32767 ) );
    layout16_2->addWidget( queryButton );
    layout17_2->addLayout( layout16_2 );

    buttonGroup2Layout->addLayout( layout17_2, 1, 0 );

    WizardPageLayout_2->addWidget( buttonGroup2, 0, 0 );

    groupBox3 = new QGroupBox( WizardPage_2, "groupBox3" );
    groupBox3->setAlignment( int( QGroupBox::AlignHCenter ) );
    groupBox3->setColumnLayout(0, Qt::Vertical );
    groupBox3->layout()->setSpacing( 6 );
    groupBox3->layout()->setMargin( 11 );
    groupBox3Layout = new QGridLayout( groupBox3->layout() );
    groupBox3Layout->setAlignment( Qt::AlignTop );

    checkBox5 = new QCheckBox( groupBox3, "checkBox5" );

    groupBox3Layout->addWidget( checkBox5, 0, 0 );

    testSetFile = new QLineEdit( groupBox3, "testSetFile" );
    testSetFile->setEnabled( FALSE );

    groupBox3Layout->addWidget( testSetFile, 1, 0 );

    testSetButton = new QPushButton( groupBox3, "testSetButton" );
    testSetButton->setEnabled( FALSE );
    testSetButton->setMaximumSize( QSize( 45, 32767 ) );

    groupBox3Layout->addWidget( testSetButton, 1, 1 );

    WizardPageLayout_2->addWidget( groupBox3, 0, 1 );
    addPage( WizardPage_2, QString("") );

    WizardPage_3 = new QWidget( this, "WizardPage_3" );
    WizardPageLayout_3 = new QGridLayout( WizardPage_3, 1, 1, 11, 6, "WizardPageLayout_3"); 

    groupBox2 = new QGroupBox( WizardPage_3, "groupBox2" );
    groupBox2->setColumnLayout(0, Qt::Vertical );
    groupBox2->layout()->setSpacing( 6 );
    groupBox2->layout()->setMargin( 11 );
    groupBox2Layout = new QGridLayout( groupBox2->layout() );
    groupBox2Layout->setAlignment( Qt::AlignTop );

    layout15 = new QVBoxLayout( 0, 0, 6, "layout15"); 

    dbCombo = new QComboBox( FALSE, groupBox2, "dbCombo" );
    layout15->addWidget( dbCombo );

    layout14 = new QVBoxLayout( 0, 0, 6, "layout14"); 

    textLabel4 = new QLabel( groupBox2, "textLabel4" );
    layout14->addWidget( textLabel4 );

    layout13 = new QHBoxLayout( 0, 0, 6, "layout13"); 

    localFP = new QLineEdit( groupBox2, "localFP" );
    layout13->addWidget( localFP );

    dbButton = new QPushButton( groupBox2, "dbButton" );
    dbButton->setMaximumSize( QSize( 45, 32767 ) );
    layout13->addWidget( dbButton );
    layout14->addLayout( layout13 );
    layout15->addLayout( layout14 );

    groupBox2Layout->addLayout( layout15, 0, 0 );

    layout27 = new QVBoxLayout( 0, 0, 6, "layout27"); 

    line1 = new QFrame( groupBox2, "line1" );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );
    layout27->addWidget( line1 );

    layout26 = new QVBoxLayout( 0, 0, 6, "layout26"); 

    textLabel6 = new QLabel( groupBox2, "textLabel6" );
    layout26->addWidget( textLabel6 );

    hitNumBox = new QSpinBox( groupBox2, "hitNumBox" );
    hitNumBox->setMaxValue( 10000 );
    hitNumBox->setValue( 100 );
    layout26->addWidget( hitNumBox );
    layout27->addLayout( layout26 );

    groupBox2Layout->addLayout( layout27, 1, 0 );

    WizardPageLayout_3->addWidget( groupBox2, 0, 0 );

    groupBox5 = new QGroupBox( WizardPage_3, "groupBox5" );
    groupBox5->setAlignment( int( QGroupBox::AlignHCenter ) );
    groupBox5->setColumnLayout(0, Qt::Vertical );
    groupBox5->layout()->setSpacing( 6 );
    groupBox5->layout()->setMargin( 11 );
    groupBox5Layout = new QGridLayout( groupBox5->layout() );
    groupBox5Layout->setAlignment( Qt::AlignTop );

    pushButton7 = new QPushButton( groupBox5, "pushButton7" );

    groupBox5Layout->addMultiCellWidget( pushButton7, 0, 0, 0, 1 );

    textLabel5_2_2 = new QLabel( groupBox5, "textLabel5_2_2" );

    groupBox5Layout->addWidget( textLabel5_2_2, 3, 0 );

    textLabel5_2 = new QLabel( groupBox5, "textLabel5_2" );

    groupBox5Layout->addWidget( textLabel5_2, 2, 0 );

    hitRate_2_3 = new QLineEdit( groupBox5, "hitRate_2_3" );
    hitRate_2_3->setMaximumSize( QSize( 100, 32767 ) );

    groupBox5Layout->addWidget( hitRate_2_3, 3, 1 );

    hitRate_2_2 = new QLineEdit( groupBox5, "hitRate_2_2" );
    hitRate_2_2->setMaximumSize( QSize( 100, 32767 ) );

    groupBox5Layout->addWidget( hitRate_2_2, 2, 1 );

    hitRate_2 = new QLineEdit( groupBox5, "hitRate_2" );
    hitRate_2->setMaximumSize( QSize( 100, 32767 ) );

    groupBox5Layout->addWidget( hitRate_2, 1, 1 );

    textLabel5 = new QLabel( groupBox5, "textLabel5" );
    textLabel5->setMinimumSize( QSize( 150, 0 ) );

    groupBox5Layout->addWidget( textLabel5, 1, 0 );

    WizardPageLayout_3->addWidget( groupBox5, 0, 1 );
    addPage( WizardPage_3, QString("") );
    languageChange();
    resize( QSize(575, 302).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonGroup1, SIGNAL( clicked(int) ), this, SLOT( fpBuilderEnableSlot(int) ) );
    connect( checkBox5, SIGNAL( toggled(bool) ), this, SLOT( enableTestSetSlot(bool) ) );
    connect( dbCombo, SIGNAL( textChanged(const QString&) ), this, SLOT( hitNumEnableSlot(const QString&) ) );
    connect( dbCombo, SIGNAL( activated(const QString&) ), this, SLOT( hitNumEnableSlot(const QString&) ) );
    connect( dbCombo, SIGNAL( highlighted(const QString&) ), this, SLOT( hitNumEnableSlot(const QString&) ) );
    connect( pushButton2, SIGNAL( clicked() ), this, SLOT( sdBuildSlot() ) );
    connect( pushButton2_2, SIGNAL( clicked() ), this, SLOT( saveFpSlot() ) );
    connect( queryButton, SIGNAL( clicked() ), this, SLOT( QueryLoadSlot() ) );
    connect( testSetButton, SIGNAL( clicked() ), this, SLOT( testSetLoadSlot() ) );
    connect( Build, SIGNAL( clicked() ), this, SLOT( fpBuildSlot() ) );
    connect( pushButton7, SIGNAL( clicked() ), this, SLOT( searchLibrarySlot() ) );
    connect( dbButton, SIGNAL( clicked() ), this, SLOT( localDBSlot() ) );
    connect( this, SIGNAL( helpClicked() ), this, SLOT( helpSlotSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
fpDialog2::~fpDialog2()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void fpDialog2::languageChange()
{
    setCaption( tr( "Lead Finder" ) );
    buttonGroup1->setTitle( tr( "Action" ) );
    checkBox1_2->setText( tr( "Build Database Fingerprint File." ) );
    checkBox1->setText( tr( "Search a Database" ) );
    groupBox1->setTitle( tr( "FP Builder" ) );
    textLabel3->setText( tr( "Select Fingerprint Type" ) );
    fpType->clear();
    fpType->insertItem( tr( "gafffp (Atom Environment)" ) );
    Build->setText( tr( "Build" ) );
    textLabel2->setText( tr( "Input SD File" ) );
    textLabel2_2->setText( tr( "Save as" ) );
    pushButton2->setText( tr( "../" ) );
    pushButton2_2->setText( tr( "../" ) );
    setTitle( WizardPage, tr( "Search or Build" ) );
    buttonGroup2->setTitle( tr( "Query Molecules" ) );
    molViewQuery->setText( tr( "Use Structures in MolView" ) );
    sdQuery->setText( tr( "Enter Query Molecules (SD File)" ) );
    queryButton->setText( tr( "../" ) );
    groupBox3->setTitle( tr( "Test Set" ) );
    checkBox5->setText( tr( "Use a Test Set (*.sdf)" ) );
    testSetButton->setText( tr( "../" ) );
    setTitle( WizardPage_2, tr( "Training (Query) / Test Set" ) );
    groupBox2->setTitle( tr( "Database" ) );
    dbCombo->clear();
    dbCombo->insertItem( tr( "Local Database" ) );
    dbCombo->insertItem( tr( "ZINC " ) );
    textLabel4->setText( tr( "Enter Local Database File (*.fp)" ) );
    dbButton->setText( tr( "../" ) );
    textLabel6->setText( tr( "Number of Hits to Return" ) );
    groupBox5->setTitle( tr( "Search" ) );
    pushButton7->setText( tr( "Find Hits" ) );
    textLabel5_2_2->setText( tr( "Percent <font color=\"#aa0000\">Total</font> Found" ) );
    textLabel5_2->setText( tr( "Percent <font color=\"#aa0000\">Test</font> Found" ) );
    textLabel5->setText( tr( "Percent <font color=\"#aa0000\">Query</font> Found" ) );
    setTitle( WizardPage_3, tr( "Search" ) );
}


