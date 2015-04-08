/****************************************************************************
** Form implementation generated from reading ui file 'hits.ui'
**
** Created: Wed Aug 17 12:31:40 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "hits.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "hits.ui.h"

/*
 *  Constructs a hitsDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
hitsDialog::hitsDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "hitsDialog" );
    setSizeGripEnabled( TRUE );
    hitsDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "hitsDialogLayout"); 

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    save = new QPushButton( this, "save" );
    save->setAutoDefault( TRUE );
    save->setDefault( TRUE );
    Layout1->addWidget( save );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    hitsDialogLayout->addLayout( Layout1, 1, 0 );

    table1 = new QTable( this, "table1" );
    table1->setNumCols( table1->numCols() + 1 );
    table1->horizontalHeader()->setLabel( table1->numCols() - 1, tr( "Name" ) );
    table1->setNumCols( table1->numCols() + 1 );
    table1->horizontalHeader()->setLabel( table1->numCols() - 1, tr( "Score" ) );
    table1->setNumRows( 0 );
    table1->setNumCols( 2 );
    table1->setFocusStyle( QTable::SpreadSheet );

    hitsDialogLayout->addWidget( table1, 0, 0 );
    languageChange();
    resize( QSize(306, 350).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( save, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( save, SIGNAL( clicked() ), this, SLOT( saveSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
hitsDialog::~hitsDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void hitsDialog::languageChange()
{
    setCaption( tr( "Hits" ) );
    save->setText( tr( "Save" ) );
    save->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    table1->horizontalHeader()->setLabel( 0, tr( "Name" ) );
    table1->horizontalHeader()->setLabel( 1, tr( "Score" ) );
}

