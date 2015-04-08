/****************************************************************************
** Form implementation generated from reading ui file 'licPopUp.ui'
**
** Created: Thu Mar 17 06:32:31 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "licPopUp.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a lm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
lm::lm( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "lm" );
    setSizeGripEnabled( TRUE );
    lmLayout = new QGridLayout( this, 1, 1, 11, 6, "lmLayout"); 

    layout5 = new QVBoxLayout( 0, 0, 6, "layout5"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    layout5->addWidget( textLabel1 );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    edit1 = new QLineEdit( this, "edit1" );
    edit1->setMaxLength( 5 );
    layout3->addWidget( edit1 );

    line1 = new QFrame( this, "line1" );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );
    layout3->addWidget( line1 );

    edit2 = new QLineEdit( this, "edit2" );
    edit2->setMaxLength( 5 );
    layout3->addWidget( edit2 );

    line1_2 = new QFrame( this, "line1_2" );
    line1_2->setFrameShape( QFrame::HLine );
    line1_2->setFrameShadow( QFrame::Sunken );
    line1_2->setFrameShape( QFrame::HLine );
    layout3->addWidget( line1_2 );

    edit3 = new QLineEdit( this, "edit3" );
    edit3->setMaxLength( 5 );
    layout3->addWidget( edit3 );

    line1_2_2 = new QFrame( this, "line1_2_2" );
    line1_2_2->setFrameShape( QFrame::HLine );
    line1_2_2->setFrameShadow( QFrame::Sunken );
    line1_2_2->setFrameShape( QFrame::HLine );
    layout3->addWidget( line1_2_2 );

    edit4 = new QLineEdit( this, "edit4" );
    edit4->setMaxLength( 5 );
    layout3->addWidget( edit4 );

    line1_2_2_2 = new QFrame( this, "line1_2_2_2" );
    line1_2_2_2->setFrameShape( QFrame::HLine );
    line1_2_2_2->setFrameShadow( QFrame::Sunken );
    line1_2_2_2->setFrameShape( QFrame::HLine );
    layout3->addWidget( line1_2_2_2 );

    edit5 = new QLineEdit( this, "edit5" );
    edit5->setMaxLength( 5 );
    layout3->addWidget( edit5 );
    layout5->addLayout( layout3 );

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );
    layout5->addLayout( Layout1 );

    lmLayout->addLayout( layout5, 0, 0 );
    languageChange();
    resize( QSize(333, 146).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
lm::~lm()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void lm::languageChange()
{
    setCaption( tr( "License Manager" ) );
    textLabel1->setText( tr( "Enter Your License Key" ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
}

