/****************************************************************************
** Form implementation generated from reading ui file 'moltablesdexport.ui'
**
** Created: Fri Aug 5 12:34:02 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "moltablesdexport.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "moltablesdexport.ui.h"

/*
 *  Constructs a sdExport as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
sdExport::sdExport( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "sdExport" );
    setSizeGripEnabled( TRUE );
    sdExportLayout = new QGridLayout( this, 1, 1, 11, 6, "sdExportLayout"); 

    layout9 = new QVBoxLayout( 0, 0, 6, "layout9"); 

    layout8 = new QVBoxLayout( 0, 0, 6, "layout8"); 

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    layout5->addWidget( textLabel1 );

    fileName = new QLineEdit( this, "fileName" );
    layout5->addWidget( fileName );

    browse = new QPushButton( this, "browse" );
    browse->setMaximumSize( QSize( 30, 30 ) );
    layout5->addWidget( browse );
    layout8->addLayout( layout5 );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 

    buttonGroup1_2 = new QButtonGroup( this, "buttonGroup1_2" );
    buttonGroup1_2->setExclusive( TRUE );
    buttonGroup1_2->setColumnLayout(0, Qt::Vertical );
    buttonGroup1_2->layout()->setSpacing( 6 );
    buttonGroup1_2->layout()->setMargin( 11 );
    buttonGroup1_2Layout = new QGridLayout( buttonGroup1_2->layout() );
    buttonGroup1_2Layout->setAlignment( Qt::AlignTop );

    row_sel = new QCheckBox( buttonGroup1_2, "row_sel" );

    buttonGroup1_2Layout->addWidget( row_sel, 1, 0 );

    row_un = new QCheckBox( buttonGroup1_2, "row_un" );

    buttonGroup1_2Layout->addWidget( row_un, 2, 0 );

    row_all = new QCheckBox( buttonGroup1_2, "row_all" );
    row_all->setChecked( TRUE );

    buttonGroup1_2Layout->addWidget( row_all, 0, 0 );
    layout7->addWidget( buttonGroup1_2 );

    buttonGroup1_2_2 = new QButtonGroup( this, "buttonGroup1_2_2" );
    buttonGroup1_2_2->setExclusive( TRUE );
    buttonGroup1_2_2->setColumnLayout(0, Qt::Vertical );
    buttonGroup1_2_2->layout()->setSpacing( 6 );
    buttonGroup1_2_2->layout()->setMargin( 11 );
    buttonGroup1_2_2Layout = new QGridLayout( buttonGroup1_2_2->layout() );
    buttonGroup1_2_2Layout->setAlignment( Qt::AlignTop );

    col_un = new QCheckBox( buttonGroup1_2_2, "col_un" );

    buttonGroup1_2_2Layout->addWidget( col_un, 2, 0 );

    col_all = new QCheckBox( buttonGroup1_2_2, "col_all" );
    col_all->setChecked( TRUE );

    buttonGroup1_2_2Layout->addWidget( col_all, 0, 0 );

    col_sel = new QCheckBox( buttonGroup1_2_2, "col_sel" );

    buttonGroup1_2_2Layout->addWidget( col_sel, 1, 0 );
    layout7->addWidget( buttonGroup1_2_2 );
    layout8->addLayout( layout7 );
    layout9->addLayout( layout8 );

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );
    layout9->addLayout( Layout1 );

    sdExportLayout->addLayout( layout9, 0, 0 );
    languageChange();
    resize( QSize(276, 212).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( browse, SIGNAL( clicked() ), this, SLOT( browseSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
sdExport::~sdExport()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void sdExport::languageChange()
{
    setCaption( tr( "SD Export" ) );
    textLabel1->setText( tr( "File Name" ) );
    browse->setText( tr( "../" ) );
    buttonGroup1_2->setTitle( tr( "Rows" ) );
    row_sel->setText( tr( "Selected" ) );
    row_un->setText( tr( "Un-Selected" ) );
    row_all->setText( tr( "All" ) );
    buttonGroup1_2_2->setTitle( tr( "Columns" ) );
    col_un->setText( tr( "Un-Selected" ) );
    col_all->setText( tr( "All" ) );
    col_sel->setText( tr( "Selected" ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
}







