/****************************************************************************
** Form implementation generated from reading ui file 'flexaligndialog.ui'
**
** Created: Fri Feb 24 08:05:55 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "flexaligndialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qtextedit.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qbuttongroup.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "flexaligndialog.ui.h"

/*
 *  Constructs a FlexAlignDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The wizard will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal wizard.
 */
FlexAlignDialog::FlexAlignDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QWizard( parent, name, modal, fl )
{
    if ( !name )
	setName( "FlexAlignDialog" );

    WizardPage = new QWidget( this, "WizardPage" );
    WizardPageLayout = new QGridLayout( WizardPage, 1, 1, 11, 6, "WizardPageLayout"); 

    textEdit1 = new QTextEdit( WizardPage, "textEdit1" );
    textEdit1->setTextFormat( QTextEdit::RichText );
    textEdit1->setWordWrap( QTextEdit::WidgetWidth );
    textEdit1->setReadOnly( TRUE );
    textEdit1->setAutoFormatting( int( QTextEdit::AutoAll ) );

    WizardPageLayout->addMultiCellWidget( textEdit1, 0, 1, 1, 1 );

    groupBox3 = new QGroupBox( WizardPage, "groupBox3" );
    groupBox3->setColumnLayout(0, Qt::Vertical );
    groupBox3->layout()->setSpacing( 6 );
    groupBox3->layout()->setMargin( 11 );
    groupBox3Layout = new QGridLayout( groupBox3->layout() );
    groupBox3Layout->setAlignment( Qt::AlignTop );

    layout30 = new QHBoxLayout( 0, 0, 6, "layout30"); 

    textLabel5 = new QLabel( groupBox3, "textLabel5" );
    layout30->addWidget( textLabel5 );

    tempFile = new QLineEdit( groupBox3, "tempFile" );
    tempFile->setEnabled( FALSE );
    tempFile->setMinimumSize( QSize( 100, 0 ) );
    layout30->addWidget( tempFile );

    tempFileButton = new QPushButton( groupBox3, "tempFileButton" );
    tempFileButton->setMaximumSize( QSize( 45, 32767 ) );
    layout30->addWidget( tempFileButton );

    groupBox3Layout->addMultiCellLayout( layout30, 1, 1, 0, 1 );

    tempView = new QCheckBox( groupBox3, "tempView" );
    tempView->setChecked( TRUE );

    groupBox3Layout->addWidget( tempView, 0, 0 );

    tempFlex = new QCheckBox( groupBox3, "tempFlex" );

    groupBox3Layout->addWidget( tempFlex, 0, 1 );

    WizardPageLayout->addWidget( groupBox3, 0, 0 );

    groupBox4 = new QGroupBox( WizardPage, "groupBox4" );
    groupBox4->setColumnLayout(0, Qt::Vertical );
    groupBox4->layout()->setSpacing( 6 );
    groupBox4->layout()->setMargin( 11 );
    groupBox4Layout = new QGridLayout( groupBox4->layout() );
    groupBox4Layout->setAlignment( Qt::AlignTop );

    toAlignView = new QCheckBox( groupBox4, "toAlignView" );
    toAlignView->setChecked( TRUE );

    groupBox4Layout->addWidget( toAlignView, 0, 0 );

    layout31 = new QHBoxLayout( 0, 0, 6, "layout31"); 

    textLabel5_2 = new QLabel( groupBox4, "textLabel5_2" );
    layout31->addWidget( textLabel5_2 );

    toAlignFile = new QLineEdit( groupBox4, "toAlignFile" );
    toAlignFile->setEnabled( FALSE );
    layout31->addWidget( toAlignFile );

    alignFileButton = new QPushButton( groupBox4, "alignFileButton" );
    alignFileButton->setMaximumSize( QSize( 45, 32767 ) );
    layout31->addWidget( alignFileButton );

    groupBox4Layout->addLayout( layout31, 1, 0 );

    WizardPageLayout->addWidget( groupBox4, 1, 0 );
    addPage( WizardPage, QString("") );

    WizardPage_2 = new QWidget( this, "WizardPage_2" );
    WizardPageLayout_2 = new QGridLayout( WizardPage_2, 1, 1, 11, 6, "WizardPageLayout_2"); 

    textEdit1_2 = new QTextEdit( WizardPage_2, "textEdit1_2" );
    textEdit1_2->setTextFormat( QTextEdit::RichText );
    textEdit1_2->setWordWrap( QTextEdit::WidgetWidth );
    textEdit1_2->setReadOnly( TRUE );
    textEdit1_2->setAutoFormatting( int( QTextEdit::AutoAll ) );

    WizardPageLayout_2->addWidget( textEdit1_2, 1, 0 );

    groupBox14 = new QGroupBox( WizardPage_2, "groupBox14" );
    groupBox14->setColumnLayout(0, Qt::Vertical );
    groupBox14->layout()->setSpacing( 6 );
    groupBox14->layout()->setMargin( 11 );
    groupBox14Layout = new QGridLayout( groupBox14->layout() );
    groupBox14Layout->setAlignment( Qt::AlignTop );

    layout25 = new QHBoxLayout( 0, 0, 6, "layout25"); 

    layout21 = new QHBoxLayout( 0, 0, 6, "layout21"); 

    singleFile = new QCheckBox( groupBox14, "singleFile" );
    layout21->addWidget( singleFile );

    outFile = new QLineEdit( groupBox14, "outFile" );
    outFile->setEnabled( FALSE );
    outFile->setMinimumSize( QSize( 100, 0 ) );
    layout21->addWidget( outFile );
    layout25->addLayout( layout21 );

    outFileButton = new QPushButton( groupBox14, "outFileButton" );
    outFileButton->setMaximumSize( QSize( 45, 32767 ) );
    layout25->addWidget( outFileButton );

    groupBox14Layout->addLayout( layout25, 0, 0 );

    layout22 = new QHBoxLayout( 0, 0, 6, "layout22"); 

    multiFile = new QCheckBox( groupBox14, "multiFile" );
    layout22->addWidget( multiFile );

    layout39 = new QHBoxLayout( 0, 0, 6, "layout39"); 

    baseName = new QLineEdit( groupBox14, "baseName" );
    baseName->setEnabled( FALSE );
    baseName->setMinimumSize( QSize( 100, 0 ) );
    layout39->addWidget( baseName );

    multiFileButton = new QPushButton( groupBox14, "multiFileButton" );
    multiFileButton->setMaximumSize( QSize( 45, 32767 ) );
    layout39->addWidget( multiFileButton );
    layout22->addLayout( layout39 );

    groupBox14Layout->addLayout( layout22, 1, 0 );

    layout26 = new QHBoxLayout( 0, 0, 6, "layout26"); 

    background = new QCheckBox( groupBox14, "background" );
    layout26->addWidget( background );

    textLabel1_4 = new QLabel( groupBox14, "textLabel1_4" );
    layout26->addWidget( textLabel1_4 );

    groupBox14Layout->addLayout( layout26, 2, 0 );

    WizardPageLayout_2->addWidget( groupBox14, 0, 0 );
    addPage( WizardPage_2, QString("") );

    WizardPage_3 = new QWidget( this, "WizardPage_3" );
    WizardPageLayout_3 = new QGridLayout( WizardPage_3, 1, 1, 11, 6, "WizardPageLayout_3"); 

    layout81 = new QHBoxLayout( 0, 0, 6, "layout81"); 

    buttonGroup1 = new QButtonGroup( WizardPage_3, "buttonGroup1" );
    buttonGroup1->setExclusive( FALSE );
    buttonGroup1->setRadioButtonExclusive( FALSE );
    buttonGroup1->setColumnLayout(0, Qt::Vertical );
    buttonGroup1->layout()->setSpacing( 6 );
    buttonGroup1->layout()->setMargin( 11 );
    buttonGroup1Layout = new QGridLayout( buttonGroup1->layout() );
    buttonGroup1Layout->setAlignment( Qt::AlignTop );

    layout19 = new QVBoxLayout( 0, 0, 6, "layout19"); 

    layout13 = new QHBoxLayout( 0, 0, 6, "layout13"); 

    textLabel1_3 = new QLabel( buttonGroup1, "textLabel1_3" );
    layout13->addWidget( textLabel1_3 );

    cw = new QLineEdit( buttonGroup1, "cw" );
    cw->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, cw->sizePolicy().hasHeightForWidth() ) );
    cw->setMaximumSize( QSize( 50, 32767 ) );
    layout13->addWidget( cw );
    layout19->addLayout( layout13 );

    layout12_2 = new QHBoxLayout( 0, 0, 6, "layout12_2"); 

    textLabel2 = new QLabel( buttonGroup1, "textLabel2" );
    layout12_2->addWidget( textLabel2 );

    vw = new QLineEdit( buttonGroup1, "vw" );
    vw->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vw->sizePolicy().hasHeightForWidth() ) );
    vw->setMaximumSize( QSize( 50, 32767 ) );
    layout12_2->addWidget( vw );
    layout19->addLayout( layout12_2 );

    layout18 = new QHBoxLayout( 0, 0, 6, "layout18"); 

    textLabel3 = new QLabel( buttonGroup1, "textLabel3" );
    layout18->addWidget( textLabel3 );

    aw = new QLineEdit( buttonGroup1, "aw" );
    aw->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, aw->sizePolicy().hasHeightForWidth() ) );
    aw->setMaximumSize( QSize( 50, 32767 ) );
    layout18->addWidget( aw );
    layout19->addLayout( layout18 );

    buttonGroup1Layout->addLayout( layout19, 0, 0 );
    layout81->addWidget( buttonGroup1 );

    textEdit1_2_2 = new QTextEdit( WizardPage_3, "textEdit1_2_2" );
    textEdit1_2_2->setTextFormat( QTextEdit::RichText );
    textEdit1_2_2->setWordWrap( QTextEdit::WidgetWidth );
    textEdit1_2_2->setReadOnly( TRUE );
    textEdit1_2_2->setAutoFormatting( int( QTextEdit::AutoAll ) );
    layout81->addWidget( textEdit1_2_2 );

    WizardPageLayout_3->addLayout( layout81, 0, 0 );
    addPage( WizardPage_3, QString("") );

    WizardPage_4 = new QWidget( this, "WizardPage_4" );
    WizardPageLayout_4 = new QGridLayout( WizardPage_4, 1, 1, 11, 6, "WizardPageLayout_4"); 

    textEdit1_2_3 = new QTextEdit( WizardPage_4, "textEdit1_2_3" );
    textEdit1_2_3->setTextFormat( QTextEdit::RichText );
    textEdit1_2_3->setWordWrap( QTextEdit::WidgetWidth );
    textEdit1_2_3->setReadOnly( TRUE );
    textEdit1_2_3->setAutoFormatting( int( QTextEdit::AutoAll ) );

    WizardPageLayout_4->addWidget( textEdit1_2_3, 0, 1 );

    groupBox1 = new QGroupBox( WizardPage_4, "groupBox1" );
    groupBox1->setColumnLayout(0, Qt::Vertical );
    groupBox1->layout()->setSpacing( 6 );
    groupBox1->layout()->setMargin( 11 );
    groupBox1Layout = new QGridLayout( groupBox1->layout() );
    groupBox1Layout->setAlignment( Qt::AlignTop );

    pushButton6 = new QPushButton( groupBox1, "pushButton6" );

    groupBox1Layout->addWidget( pushButton6, 1, 0 );

    layout24 = new QHBoxLayout( 0, 0, 6, "layout24"); 

    layout23 = new QVBoxLayout( 0, 0, 6, "layout23"); 

    textLabel4_3 = new QLabel( groupBox1, "textLabel4_3" );
    layout23->addWidget( textLabel4_3 );

    textLabel4 = new QLabel( groupBox1, "textLabel4" );
    layout23->addWidget( textLabel4 );

    textLabel4_2 = new QLabel( groupBox1, "textLabel4_2" );
    layout23->addWidget( textLabel4_2 );

    textLabel4_2_2 = new QLabel( groupBox1, "textLabel4_2_2" );
    layout23->addWidget( textLabel4_2_2 );
    layout24->addLayout( layout23 );

    layout22_2 = new QVBoxLayout( 0, 0, 6, "layout22_2"); 

    chargeType = new QComboBox( FALSE, groupBox1, "chargeType" );
    layout22_2->addWidget( chargeType );

    maxMD = new QLineEdit( groupBox1, "maxMD" );
    layout22_2->addWidget( maxMD );

    MaxMin = new QLineEdit( groupBox1, "MaxMin" );
    layout22_2->addWidget( MaxMin );

    dielec = new QLineEdit( groupBox1, "dielec" );
    layout22_2->addWidget( dielec );
    layout24->addLayout( layout22_2 );

    groupBox1Layout->addMultiCellLayout( layout24, 0, 0, 0, 1 );

    WizardPageLayout_4->addWidget( groupBox1, 0, 0 );
    addPage( WizardPage_4, QString("") );

    lastPage = new QWidget( this, "lastPage" );
    lastPageLayout = new QGridLayout( lastPage, 1, 1, 11, 6, "lastPageLayout"); 

    textEdit1_2_4 = new QTextEdit( lastPage, "textEdit1_2_4" );
    textEdit1_2_4->setTextFormat( QTextEdit::RichText );
    textEdit1_2_4->setWordWrap( QTextEdit::WidgetWidth );
    textEdit1_2_4->setReadOnly( TRUE );
    textEdit1_2_4->setAutoFormatting( int( QTextEdit::AutoAll ) );

    lastPageLayout->addWidget( textEdit1_2_4, 0, 1 );

    groupBox2 = new QGroupBox( lastPage, "groupBox2" );
    groupBox2->setColumnLayout(0, Qt::Vertical );
    groupBox2->layout()->setSpacing( 6 );
    groupBox2->layout()->setMargin( 11 );
    groupBox2Layout = new QGridLayout( groupBox2->layout() );
    groupBox2Layout->setAlignment( Qt::AlignTop );

    layout25_2 = new QVBoxLayout( 0, 0, 6, "layout25_2"); 

    layout24_2 = new QHBoxLayout( 0, 0, 6, "layout24_2"); 

    textLabel1_2 = new QLabel( groupBox2, "textLabel1_2" );
    layout24_2->addWidget( textLabel1_2 );

    jobName = new QLineEdit( groupBox2, "jobName" );
    layout24_2->addWidget( jobName );
    layout25_2->addLayout( layout24_2 );

    layout23_2 = new QVBoxLayout( 0, 0, 6, "layout23_2"); 

    layout22_3 = new QVBoxLayout( 0, 0, 6, "layout22_3"); 

    layout42_2_2 = new QHBoxLayout( 0, 0, 6, "layout42_2_2"); 

    poseNum_2 = new QLabel( groupBox2, "poseNum_2" );
    layout42_2_2->addWidget( poseNum_2 );

    Iterations = new QSpinBox( groupBox2, "Iterations" );
    Iterations->setMaxValue( 10000 );
    Iterations->setMinValue( 1 );
    Iterations->setValue( 10 );
    layout42_2_2->addWidget( Iterations );
    layout22_3->addLayout( layout42_2_2 );

    layout21_2 = new QVBoxLayout( 0, 0, 6, "layout21_2"); 

    layout20 = new QHBoxLayout( 0, 0, 6, "layout20"); 

    poseNum = new QLabel( groupBox2, "poseNum" );
    layout20->addWidget( poseNum );

    poses = new QSpinBox( groupBox2, "poses" );
    poses->setMaxValue( 10000 );
    poses->setMinValue( 1 );
    layout20->addWidget( poses );
    layout21_2->addLayout( layout20 );

    layout19_2 = new QHBoxLayout( 0, 0, 6, "layout19_2"); 

    textLabel1 = new QLabel( groupBox2, "textLabel1" );
    layout19_2->addWidget( textLabel1 );

    poseRMSE = new QLineEdit( groupBox2, "poseRMSE" );
    layout19_2->addWidget( poseRMSE );
    layout21_2->addLayout( layout19_2 );
    layout22_3->addLayout( layout21_2 );
    layout23_2->addLayout( layout22_3 );

    layout18_2 = new QHBoxLayout( 0, 0, 6, "layout18_2"); 

    poseNum_3 = new QLabel( groupBox2, "poseNum_3" );
    layout18_2->addWidget( poseNum_3 );

    tanTerm = new QLineEdit( groupBox2, "tanTerm" );
    layout18_2->addWidget( tanTerm );
    layout23_2->addLayout( layout18_2 );
    layout25_2->addLayout( layout23_2 );

    groupBox2Layout->addLayout( layout25_2, 1, 0 );

    lastPageLayout->addWidget( groupBox2, 0, 0 );
    addPage( lastPage, QString("") );
    languageChange();
    resize( QSize(602, 409).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( pushButton6, SIGNAL( clicked() ), this, SLOT( fineControlSlot() ) );
    connect( tempView, SIGNAL( clicked() ), this, SLOT( tempFileSlot() ) );
    connect( toAlignView, SIGNAL( clicked() ), this, SLOT( alignFileSlot() ) );
    connect( singleFile, SIGNAL( clicked() ), this, SLOT( singleFileSlot() ) );
    connect( multiFile, SIGNAL( clicked() ), this, SLOT( multiFileSlot() ) );
    connect( outFileButton, SIGNAL( clicked() ), this, SLOT( newOutFileSlot() ) );
    connect( multiFileButton, SIGNAL( clicked() ), this, SLOT( newMultiFileSlot() ) );
    connect( tempFileButton, SIGNAL( clicked() ), this, SLOT( setTempFileSlot() ) );
    connect( alignFileButton, SIGNAL( clicked() ), this, SLOT( setAlignFileSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
FlexAlignDialog::~FlexAlignDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FlexAlignDialog::languageChange()
{
    setCaption( tr( "Flexible Alignment" ) );
    textEdit1->setText( tr( "<b>File Based Alignment</b><br>\n"
"<b>All </b>molecules in the flexible file will be aligned to <b>all </b>molecule in the template file\n"
"\n"
"<br><br>\n"
"<b>MolView Based Alignment</b><br>\n"
"The first molecule placed into the MolView is used as the template.  " ) );
    groupBox3->setTitle( tr( "Template Molecule" ) );
    textLabel5->setText( tr( "File (.sdf)" ) );
    tempFile->setText( tr( "template.sdf" ) );
    tempFileButton->setText( tr( "../" ) );
    tempView->setText( tr( "MolView" ) );
    tempFlex->setText( tr( "Flexible" ) );
    groupBox4->setTitle( tr( "Flexible Molecule" ) );
    toAlignView->setText( tr( "In MolView" ) );
    textLabel5_2->setText( tr( "File (.sdf)" ) );
    toAlignFile->setText( tr( "to_align.sdf" ) );
    alignFileButton->setText( tr( "../" ) );
    setTitle( WizardPage, tr( "Molecule Output" ) );
    textEdit1_2->setText( tr( "<b>Single File Outut</b>\n"
"  <br>\n"
"\n"
"In single file mode all poses for each flexible molecule are written to a single file.  \n"
"<br><br>\n"
"<b>Mutliple File Output</b>\n"
"<br>\n"
"Multiple file output will write a seperate file for each of the flexible ligands.  Each entry in the SD (*.sdf) file will be named according to the resulting alignment score.\n"
"<br><br>\n"
"<b>Background</b><br>\n"
"If this option is checked then the job will be run in the background.  This is the recommended mode for large jobs.  If not checked then each molecule will be added to both the listView and the molView." ) );
    groupBox14->setTitle( tr( "Output Method" ) );
    singleFile->setText( tr( "Single File" ) );
    outFile->setText( tr( "overlay.sdf" ) );
    outFileButton->setText( tr( "../" ) );
    multiFile->setText( tr( "Multiple Files" ) );
    baseName->setText( tr( "baseName_" ) );
    multiFileButton->setText( tr( "../" ) );
    background->setText( tr( "Background" ) );
    background->setAccel( QKeySequence( QString::null ) );
    textLabel1_4->setText( tr( "Run large jobs in the background" ) );
    setTitle( WizardPage_2, tr( "Molecule Output" ) );
    buttonGroup1->setTitle( tr( "Gaussian Weights" ) );
    textLabel1_3->setText( tr( "Charge" ) );
    cw->setText( tr( "3" ) );
    textLabel2->setText( tr( "Volume" ) );
    vw->setText( tr( "2" ) );
    textLabel3->setText( tr( "Aromaticity" ) );
    aw->setText( tr( "1" ) );
    textEdit1_2_2->setText( tr( "<b>Gaussion Weights</b>\n"
"<br><br>\n"
"The DynAlign module uses a Gaussian overlay function composed of 3 separate components.  You may change the relative weight of each of these functions by setting the value in the input boxes to the left.  " ) );
    setTitle( WizardPage_3, tr( "Overlay Setup" ) );
    textEdit1_2_3->setText( tr( "DynAlign is a three stage process.<br>\n"
"<br>\n"
"<b>Stage 1</b><br>\n"
" The first stage makes a random perturbation to the conformational and orientations space of the flexible molecule.\n"
"<br><br>\n"
"<b>Stage 2</b><br>\n"
"The second stage is a Molecular Mechanics/Gaussian dynamics simulation.  The simulation performs a velocity scaling every <i>n</i> steps to achieve a simulated annealing effect.  You can set the maximum number of steps for this stage to the left.  Finer control can be acessed with the <b>Fine Control</b> button.\n"
"<br><br>\n"
"<b>Stage 3</b><br>\n"
"The Third stage is a Molecule Mechanics/Gaussian minimization.  You can set the maximum number of steps for this stage to the left.\n"
"\n"
"<br><br>\n"
"<b>Fine Control</b><br>\n"
"Use the Fine Control button if you wish to have more control over minimization and dynamics termination criteria.  " ) );
    groupBox1->setTitle( tr( "Force Field Parameters" ) );
    pushButton6->setText( tr( "Fine Control" ) );
    textLabel4_3->setText( tr( "Charges" ) );
    textLabel4->setText( tr( "Max MD Steps" ) );
    textLabel4_2->setText( tr( "Max Min Steps" ) );
    textLabel4_2_2->setText( tr( "Dielectric" ) );
    chargeType->clear();
    chargeType->insertItem( tr( "AM1-BCC-fast" ) );
    chargeType->insertItem( tr( "AM1-BCC" ) );
    chargeType->insertItem( tr( "AM1" ) );
    chargeType->insertItem( tr( "MNDO" ) );
    chargeType->insertItem( tr( "PM3" ) );
    chargeType->insertItem( tr( "Current" ) );
    maxMD->setText( tr( "10000" ) );
    MaxMin->setText( tr( "2500" ) );
    dielec->setText( tr( "80" ) );
    setTitle( WizardPage_4, tr( "Molecular Mechanics/Dynamics Setup" ) );
    textEdit1_2_4->setText( tr( "<b>Job Name</b><br>\n"
"Set the Job name.  This is the name that can be used to terminate the job with the jobs menubar.\n"
"\n"
"<br><br>\n"
"<b>Iterations Per Molecule</b><br>\n"
"The number of random starts for each molecule.\n"
"\n"
"<br><br>\n"
"<b>Max Poses</b><br>\n"
"The maximum number of poses to keep for each molecule.\n"
"\n"
"<br><br>\n"
"<b>RMSE for new Poses<b><br>\n"
"The minimum root mean square error needed to consider a pose unique.\n"
"\n"
"<br><br>\n"
"<b>Stop Similariy</b><br>\n"
"If the search finds a pose with a similarity greater than the cuttoff point the simulation will stop the search process for that molecule." ) );
    groupBox2->setTitle( tr( "Run Parameters" ) );
    textLabel1_2->setText( tr( "Job Name" ) );
    jobName->setText( tr( "DynAlign" ) );
    poseNum_2->setText( tr( "Iterations Per Molecule" ) );
    poseNum->setText( tr( "Max Number of Poses" ) );
    textLabel1->setText( tr( "RMSE for new Pose" ) );
    QToolTip::add( textLabel1, tr( "This is the minimum root mean square error needed before a pose can be considered distinct enough to keep" ) );
    poseRMSE->setText( tr( "1.0" ) );
    QToolTip::add( poseRMSE, tr( "This is the minimum root mean square error needed before a pose can be considered distinct enough to keep" ) );
    poseNum_3->setText( tr( "Stop at Similarity % >" ) );
    tanTerm->setText( tr( "90" ) );
    setTitle( lastPage, tr( "Simulation Setup" ) );
}

