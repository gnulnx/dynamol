/****************************************************************************
** Form implementation generated from reading ui file 'gaff_fp_progress.ui'
**
** Created: Wed Aug 3 12:54:52 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "gaff_fp_progress.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a gaffProg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
gaffProg::gaffProg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "gaffProg" );
    setModal( TRUE );
    gaffProgLayout = new QGridLayout( this, 1, 1, 11, 6, "gaffProgLayout"); 

    textLabel1 = new QLabel( this, "textLabel1" );

    gaffProgLayout->addWidget( textLabel1, 0, 0 );

    layout2 = new QVBoxLayout( 0, 0, 6, "layout2"); 

    check1 = new QCheckBox( this, "check1" );
    layout2->addWidget( check1 );

    check2 = new QCheckBox( this, "check2" );
    layout2->addWidget( check2 );

    check3 = new QCheckBox( this, "check3" );
    layout2->addWidget( check3 );

    gaffProgLayout->addLayout( layout2, 2, 0 );

    line1 = new QFrame( this, "line1" );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );

    gaffProgLayout->addWidget( line1, 1, 0 );
    languageChange();
    resize( QSize(202, 201).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
gaffProg::~gaffProg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void gaffProg::languageChange()
{
    setCaption( tr( "Search Progress" ) );
    textLabel1->setText( tr( "Search may take<br>\n"
"a few minutes" ) );
    check1->setText( tr( "Calculating Features" ) );
    check2->setText( tr( "Running Search" ) );
    check3->setText( tr( "Compiling Results" ) );
}

