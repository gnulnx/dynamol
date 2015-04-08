/****************************************************************************
** Form implementation generated from reading ui file 'eSetup.ui'
**
** Created: Sun Apr 3 16:19:35 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "eSetup.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a eSetup as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
eSetup::eSetup( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "eSetup" );
    setSizeGripEnabled( TRUE );
    eSetupLayout = new QGridLayout( this, 1, 1, 11, 6, "eSetupLayout"); 

    layout10 = new QVBoxLayout( 0, 0, 6, "layout10"); 

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 

    layout7 = new QVBoxLayout( 0, 0, 6, "layout7"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    layout7->addWidget( textLabel1 );

    textLabel2 = new QLabel( this, "textLabel2" );
    layout7->addWidget( textLabel2 );

    textLabel3 = new QLabel( this, "textLabel3" );
    layout7->addWidget( textLabel3 );

    textLabel4 = new QLabel( this, "textLabel4" );
    layout7->addWidget( textLabel4 );
    layout8->addLayout( layout7 );

    layout6 = new QVBoxLayout( 0, 0, 6, "layout6"); 

    rmse = new QLineEdit( this, "rmse" );
    layout6->addWidget( rmse );

    maxRMS = new QLineEdit( this, "maxRMS" );
    layout6->addWidget( maxRMS );

    minE = new QLineEdit( this, "minE" );
    layout6->addWidget( minE );

    maxIter = new QLineEdit( this, "maxIter" );
    layout6->addWidget( maxIter );
    layout8->addLayout( layout6 );
    layout10->addLayout( layout8 );

    layout9 = new QHBoxLayout( 0, 0, 6, "layout9"); 
    Horizontal_Spacing2 = new QSpacerItem( 150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout9->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    layout9->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    layout9->addWidget( buttonCancel );
    layout10->addLayout( layout9 );

    eSetupLayout->addLayout( layout10, 0, 0 );
    languageChange();
    resize( QSize(362, 188).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
eSetup::~eSetup()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void eSetup::languageChange()
{
    setCaption( tr( "Convergence Criteria" ) );
    textLabel1->setText( tr( "Minimum RMSE of Atomic Forces" ) );
    textLabel2->setText( tr( "Maximum Atomic Force" ) );
    textLabel3->setText( tr( "Minimum Energy Change" ) );
    textLabel4->setText( tr( "Maximum Iterations" ) );
    rmse->setText( tr( "0.05" ) );
    maxRMS->setText( tr( "0.01" ) );
    minE->setText( tr( "0.001" ) );
    maxIter->setText( tr( "5000" ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
}

























