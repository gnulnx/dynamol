/****************************************************************************
** Form implementation generated from reading ui file 'listViewRightClick.ui'
**
** Created: Mon Feb 28 14:15:25 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "listViewRightClick.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a listViewRightClick as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
listViewRightClick::listViewRightClick( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "listViewRightClick" );
    setMinimumSize( QSize( 0, 0 ) );
    setMaximumSize( QSize( 3000, 3000 ) );
    setSizeGripEnabled( TRUE );
    listViewRightClickLayout = new QGridLayout( this, 1, 1, 11, 6, "listViewRightClickLayout"); 

    layout41 = new QGridLayout( 0, 1, 1, 0, 6, "layout41"); 

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );

    layout41->addWidget( buttonCancel, 2, 2 );

    layout40 = new QGridLayout( 0, 1, 1, 0, 6, "layout40"); 

    group1 = new QButtonGroup( this, "group1" );
    group1->setExclusive( TRUE );
    group1->setColumnLayout(0, Qt::Vertical );
    group1->layout()->setSpacing( 6 );
    group1->layout()->setMargin( 11 );
    group1Layout = new QGridLayout( group1->layout() );
    group1Layout->setAlignment( Qt::AlignTop );

    layout52 = new QVBoxLayout( 0, 0, 6, "layout52"); 

    layout50 = new QVBoxLayout( 0, 0, 6, "layout50"); 

    layout48 = new QHBoxLayout( 0, 0, 6, "layout48"); 

    add = new QRadioButton( group1, "add" );
    add->setChecked( TRUE );
    layout48->addWidget( add );
    spacer18 = new QSpacerItem( 31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout48->addItem( spacer18 );
    layout50->addLayout( layout48 );

    layout49 = new QHBoxLayout( 0, 0, 6, "layout49"); 

    clear = new QRadioButton( group1, "clear" );
    layout49->addWidget( clear );
    layout50->addLayout( layout49 );
    layout52->addLayout( layout50 );
    spacer21 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout52->addItem( spacer21 );

    group1Layout->addLayout( layout52, 0, 0 );

    layout40->addWidget( group1, 0, 1 );

    group2 = new QButtonGroup( this, "group2" );
    group2->setCheckable( FALSE );
    group2->setChecked( FALSE );
    group2->setExclusive( TRUE );
    group2->setColumnLayout(0, Qt::Vertical );
    group2->layout()->setSpacing( 6 );
    group2->layout()->setMargin( 11 );
    group2Layout = new QGridLayout( group2->layout() );
    group2Layout->setAlignment( Qt::AlignTop );

    layout68 = new QVBoxLayout( 0, 0, 6, "layout68"); 

    layout58 = new QHBoxLayout( 0, 0, 6, "layout58"); 

    radioButton4 = new QRadioButton( group2, "radioButton4" );
    radioButton4->setChecked( TRUE );
    layout58->addWidget( radioButton4 );
    spacer22 = new QSpacerItem( 31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout58->addItem( spacer22 );
    layout68->addLayout( layout58 );

    layout59 = new QHBoxLayout( 0, 0, 6, "layout59"); 

    radioButton5 = new QRadioButton( group2, "radioButton5" );
    layout59->addWidget( radioButton5 );
    spacer22_2 = new QSpacerItem( 31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout59->addItem( spacer22_2 );
    layout68->addLayout( layout59 );

    layout64 = new QHBoxLayout( 0, 0, 6, "layout64"); 

    radioButton6 = new QRadioButton( group2, "radioButton6" );
    layout64->addWidget( radioButton6 );
    spacer22_3 = new QSpacerItem( 16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout64->addItem( spacer22_3 );
    layout68->addLayout( layout64 );

    layout61 = new QHBoxLayout( 0, 0, 6, "layout61"); 

    radioButton7 = new QRadioButton( group2, "radioButton7" );
    layout61->addWidget( radioButton7 );
    spacer22_4 = new QSpacerItem( 31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout61->addItem( spacer22_4 );
    layout68->addLayout( layout61 );

    group2Layout->addLayout( layout68, 0, 0 );

    layout40->addWidget( group2, 0, 0 );

    layout41->addMultiCellLayout( layout40, 0, 0, 0, 3 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );

    layout41->addWidget( buttonOk, 2, 1 );

    listViewRightClickLayout->addLayout( layout41, 0, 0 );
    languageChange();
    resize( QSize(332, 207).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
listViewRightClick::~listViewRightClick()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void listViewRightClick::languageChange()
{
    setCaption( tr( "Render Dialog" ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    group1->setTitle( tr( "Display Method" ) );
    add->setText( tr( "Add to Mol View" ) );
    clear->setText( tr( "Clear Mol View" ) );
    group2->setTitle( tr( "Display Style" ) );
    radioButton4->setText( tr( "Wire" ) );
    radioButton5->setText( tr( "Stick" ) );
    radioButton6->setText( tr( "Ball and Stick" ) );
    radioButton7->setText( tr( "CPK" ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
}

