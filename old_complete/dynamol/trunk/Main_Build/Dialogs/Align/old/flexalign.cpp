/****************************************************************************
** Form implementation generated from reading ui file 'flexalign.ui'
**
** Created: Sat Aug 20 11:10:32 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "flexalign.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "flexalign.ui.h"

/*
 *  Constructs a FlexAlign as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FlexAlign::FlexAlign( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "FlexAlign" );
    setSizeGripEnabled( TRUE );
    FlexAlignLayout = new QGridLayout( this, 1, 1, 11, 6, "FlexAlignLayout"); 

    buttonGroup1 = new QButtonGroup( this, "buttonGroup1" );
    buttonGroup1->setExclusive( FALSE );
    buttonGroup1->setRadioButtonExclusive( FALSE );
    buttonGroup1->setColumnLayout(0, Qt::Vertical );
    buttonGroup1->layout()->setSpacing( 6 );
    buttonGroup1->layout()->setMargin( 11 );
    buttonGroup1Layout = new QGridLayout( buttonGroup1->layout() );
    buttonGroup1Layout->setAlignment( Qt::AlignTop );

    layout11 = new QVBoxLayout( 0, 0, 6, "layout11"); 

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 

    chargeButton = new QRadioButton( buttonGroup1, "chargeButton" );
    chargeButton->setChecked( TRUE );
    layout8->addWidget( chargeButton );

    chargeWeight = new QLineEdit( buttonGroup1, "chargeWeight" );
    chargeWeight->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, chargeWeight->sizePolicy().hasHeightForWidth() ) );
    chargeWeight->setMaximumSize( QSize( 50, 32767 ) );
    layout8->addWidget( chargeWeight );
    layout11->addLayout( layout8 );

    layout8_2 = new QHBoxLayout( 0, 0, 6, "layout8_2"); 

    volumeButton = new QRadioButton( buttonGroup1, "volumeButton" );
    volumeButton->setChecked( TRUE );
    layout8_2->addWidget( volumeButton );

    volumeWeight = new QLineEdit( buttonGroup1, "volumeWeight" );
    volumeWeight->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, volumeWeight->sizePolicy().hasHeightForWidth() ) );
    volumeWeight->setMaximumSize( QSize( 50, 32767 ) );
    layout8_2->addWidget( volumeWeight );
    layout11->addLayout( layout8_2 );

    layout8_3 = new QHBoxLayout( 0, 0, 6, "layout8_3"); 

    aromaButton = new QRadioButton( buttonGroup1, "aromaButton" );
    aromaButton->setChecked( TRUE );
    layout8_3->addWidget( aromaButton );

    aromaWeight = new QLineEdit( buttonGroup1, "aromaWeight" );
    aromaWeight->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, aromaWeight->sizePolicy().hasHeightForWidth() ) );
    aromaWeight->setMaximumSize( QSize( 50, 32767 ) );
    layout8_3->addWidget( aromaWeight );
    layout11->addLayout( layout8_3 );

    buttonGroup1Layout->addLayout( layout11, 0, 0 );

    FlexAlignLayout->addWidget( buttonGroup1, 1, 0 );

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

    FlexAlignLayout->addLayout( Layout1, 2, 0 );

    layout18 = new QHBoxLayout( 0, 0, 6, "layout18"); 

    layout14 = new QVBoxLayout( 0, 0, 6, "layout14"); 

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    layout2->addWidget( textLabel1 );

    lineEdit1 = new QLineEdit( this, "lineEdit1" );
    lineEdit1->setMinimumSize( QSize( 100, 0 ) );
    layout2->addWidget( lineEdit1 );
    layout14->addLayout( layout2 );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    textLabel1_2 = new QLabel( this, "textLabel1_2" );
    layout3->addWidget( textLabel1_2 );

    lineEdit2 = new QLineEdit( this, "lineEdit2" );
    layout3->addWidget( lineEdit2 );
    layout14->addLayout( layout3 );
    layout18->addLayout( layout14 );

    layout17 = new QVBoxLayout( 0, 0, 6, "layout17"); 

    template_load = new QPushButton( this, "template_load" );
    template_load->setMaximumSize( QSize( 45, 32767 ) );
    layout17->addWidget( template_load );

    to_align_load = new QPushButton( this, "to_align_load" );
    to_align_load->setMaximumSize( QSize( 45, 32767 ) );
    layout17->addWidget( to_align_load );
    layout18->addLayout( layout17 );

    FlexAlignLayout->addLayout( layout18, 0, 0 );
    languageChange();
    resize( QSize(337, 252).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( template_load, SIGNAL( clicked() ), this, SLOT( tempLoadSlot() ) );
    connect( to_align_load, SIGNAL( clicked() ), this, SLOT( toAlignLoadSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
FlexAlign::~FlexAlign()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FlexAlign::languageChange()
{
    setCaption( tr( "Flexible Alignment" ) );
    buttonGroup1->setTitle( tr( "Parameters/Weights" ) );
    chargeButton->setText( tr( "Partial Charge" ) );
    chargeWeight->setText( tr( "1" ) );
    volumeButton->setText( tr( "Volume" ) );
    volumeWeight->setText( tr( "1" ) );
    aromaButton->setText( tr( "Aromaticity" ) );
    aromaWeight->setText( tr( "1" ) );
    buttonHelp->setText( tr( "&Help" ) );
    buttonHelp->setAccel( QKeySequence( tr( "F1" ) ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    textLabel1->setText( tr( "Template Molecule (*.sdf)" ) );
    lineEdit1->setText( tr( "template.sdf" ) );
    textLabel1_2->setText( tr( "Molecules to Align (*.sdf)" ) );
    lineEdit2->setText( tr( "to_align.sdf" ) );
    template_load->setText( tr( "../" ) );
    to_align_load->setText( tr( "../" ) );
}

