/****************************************************************************
** Form implementation generated from reading ui file 'confpartdialog.ui'
**
** Created: Fri Sep 23 07:06:44 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "confpartdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qgroupbox.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "confpartdialog.ui.h"

/*
 *  Constructs a confPartDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
confPartDialog::confPartDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "confPartDialog" );
    setSizeGripEnabled( TRUE );
    confPartDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "confPartDialogLayout"); 

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonHelp = new QPushButton( this, "buttonHelp" );
    buttonHelp->setAutoDefault( TRUE );
    Layout1->addWidget( buttonHelp );
    Horizontal_Spacing2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    confPartDialogLayout->addLayout( Layout1, 2, 0 );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setMinimumSize( QSize( 90, 0 ) );
    layout2->addWidget( textLabel1 );

    saveAs = new QLineEdit( this, "saveAs" );
    layout2->addWidget( saveAs );

    pushButton4 = new QPushButton( this, "pushButton4" );
    pushButton4->setMaximumSize( QSize( 40, 32767 ) );
    layout2->addWidget( pushButton4 );

    confPartDialogLayout->addLayout( layout2, 0, 0 );

    groupBox1 = new QGroupBox( this, "groupBox1" );
    groupBox1->setColumnLayout(0, Qt::Vertical );
    groupBox1->layout()->setSpacing( 6 );
    groupBox1->layout()->setMargin( 11 );
    groupBox1Layout = new QGridLayout( groupBox1->layout() );
    groupBox1Layout->setAlignment( Qt::AlignTop );

    layout9 = new QHBoxLayout( 0, 0, 6, "layout9"); 

    layout7 = new QVBoxLayout( 0, 0, 6, "layout7"); 

    id = new QLineEdit( groupBox1, "id" );
    layout7->addWidget( id );

    c1 = new QLineEdit( groupBox1, "c1" );
    layout7->addWidget( c1 );

    c2 = new QLineEdit( groupBox1, "c2" );
    layout7->addWidget( c2 );

    popSize = new QSpinBox( groupBox1, "popSize" );
    popSize->setMaxValue( 1000000 );
    popSize->setValue( 100 );
    layout7->addWidget( popSize );

    gen = new QSpinBox( groupBox1, "gen" );
    gen->setMaxValue( 100000 );
    gen->setValue( 100 );
    layout7->addWidget( gen );
    layout9->addLayout( layout7 );

    layout8 = new QVBoxLayout( 0, 0, 6, "layout8"); 

    textLabel2 = new QLabel( groupBox1, "textLabel2" );
    layout8->addWidget( textLabel2 );

    textLabel2_2 = new QLabel( groupBox1, "textLabel2_2" );
    layout8->addWidget( textLabel2_2 );

    textLabel2_2_2 = new QLabel( groupBox1, "textLabel2_2_2" );
    layout8->addWidget( textLabel2_2_2 );

    textLabel3 = new QLabel( groupBox1, "textLabel3" );
    layout8->addWidget( textLabel3 );

    textLabel3_2 = new QLabel( groupBox1, "textLabel3_2" );
    layout8->addWidget( textLabel3_2 );
    layout9->addLayout( layout8 );

    groupBox1Layout->addLayout( layout9, 0, 0 );

    confPartDialogLayout->addWidget( groupBox1, 1, 0 );
    languageChange();
    resize( QSize(283, 264).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( pushButton4, SIGNAL( clicked() ), this, SLOT( getSaveAsSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
confPartDialog::~confPartDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void confPartDialog::languageChange()
{
    setCaption( tr( "Particle Swarm Conformational Analysis" ) );
    buttonHelp->setText( tr( "&Help" ) );
    buttonHelp->setAccel( QKeySequence( tr( "F1" ) ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    textLabel1->setText( tr( "Save As <font color=\"#005500\">(*.sdf)</font>" ) );
    saveAs->setText( tr( "conf.sdf" ) );
    pushButton4->setText( tr( "./" ) );
    groupBox1->setTitle( tr( "Variables" ) );
    id->setText( tr( ".5" ) );
    c1->setText( tr( ".65" ) );
    c2->setText( tr( ".45" ) );
    textLabel2->setText( tr( "Inertial Dampener [0-1]" ) );
    textLabel2_2->setText( tr( "Global Pull [0-1]" ) );
    textLabel2_2_2->setText( tr( "Local Pull [0-1]" ) );
    textLabel3->setText( tr( "Population Size" ) );
    textLabel3_2->setText( tr( "Max Generations" ) );
}


