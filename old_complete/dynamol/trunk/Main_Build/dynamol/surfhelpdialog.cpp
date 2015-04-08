/****************************************************************************
** Form implementation generated from reading ui file 'surfhelpdialog.ui'
**
** Created: Mon Feb 6 13:32:34 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "surfhelpdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a surfHelpDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
surfHelpDialog::surfHelpDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "surfHelpDialog" );
    setSizeGripEnabled( TRUE );
    surfHelpDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "surfHelpDialogLayout"); 

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    Done = new QPushButton( this, "Done" );
    Done->setAutoDefault( TRUE );
    Done->setDefault( TRUE );
    Layout1->addWidget( Done );

    surfHelpDialogLayout->addLayout( Layout1, 1, 0 );

    textEdit2 = new QTextEdit( this, "textEdit2" );

    surfHelpDialogLayout->addWidget( textEdit2, 0, 0 );
    languageChange();
    resize( QSize(511, 303).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( Done, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
surfHelpDialog::~surfHelpDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void surfHelpDialog::languageChange()
{
    setCaption( tr( "Surface Help Dialog" ) );
    Done->setText( tr( "&Done" ) );
    Done->setAccel( QKeySequence( tr( "Alt+D" ) ) );
}

