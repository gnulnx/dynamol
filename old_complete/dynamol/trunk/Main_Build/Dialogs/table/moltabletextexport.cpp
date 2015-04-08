/****************************************************************************
** Form implementation generated from reading ui file 'moltabletextexport.ui'
**
** Created: Fri Aug 5 12:34:02 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "moltabletextexport.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "moltabletextexport.ui.h"

/*
 *  Constructs a textExport as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
textExport::textExport( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "textExport" );
    setSizeGripEnabled( TRUE );
    textExportLayout = new QGridLayout( this, 1, 1, 11, 6, "textExportLayout"); 

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    layout5->addWidget( textLabel1 );

    fileName = new QLineEdit( this, "fileName" );
    layout5->addWidget( fileName );

    browse = new QPushButton( this, "browse" );
    browse->setMaximumSize( QSize( 30, 30 ) );
    layout5->addWidget( browse );

    textExportLayout->addLayout( layout5, 0, 0 );

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    layout8->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    layout8->addWidget( buttonCancel );

    textExportLayout->addLayout( layout8, 2, 0 );

    layout9 = new QHBoxLayout( 0, 0, 6, "layout9"); 

    buttonGroup1_2 = new QButtonGroup( this, "buttonGroup1_2" );
    buttonGroup1_2->setExclusive( TRUE );
    buttonGroup1_2->setColumnLayout(0, Qt::Vertical );
    buttonGroup1_2->layout()->setSpacing( 6 );
    buttonGroup1_2->layout()->setMargin( 11 );
    buttonGroup1_2Layout = new QGridLayout( buttonGroup1_2->layout() );
    buttonGroup1_2Layout->setAlignment( Qt::AlignTop );

    row_all = new QCheckBox( buttonGroup1_2, "row_all" );
    row_all->setChecked( TRUE );

    buttonGroup1_2Layout->addWidget( row_all, 0, 0 );

    row_sel = new QCheckBox( buttonGroup1_2, "row_sel" );

    buttonGroup1_2Layout->addWidget( row_sel, 1, 0 );

    row_un = new QCheckBox( buttonGroup1_2, "row_un" );

    buttonGroup1_2Layout->addWidget( row_un, 2, 0 );
    layout9->addWidget( buttonGroup1_2 );

    buttonGroup1_2_2 = new QButtonGroup( this, "buttonGroup1_2_2" );
    buttonGroup1_2_2->setExclusive( TRUE );
    buttonGroup1_2_2->setColumnLayout(0, Qt::Vertical );
    buttonGroup1_2_2->layout()->setSpacing( 6 );
    buttonGroup1_2_2->layout()->setMargin( 11 );
    buttonGroup1_2_2Layout = new QGridLayout( buttonGroup1_2_2->layout() );
    buttonGroup1_2_2Layout->setAlignment( Qt::AlignTop );

    col_sel = new QCheckBox( buttonGroup1_2_2, "col_sel" );

    buttonGroup1_2_2Layout->addWidget( col_sel, 1, 0 );

    col_un = new QCheckBox( buttonGroup1_2_2, "col_un" );

    buttonGroup1_2_2Layout->addWidget( col_un, 2, 0 );

    col_all = new QCheckBox( buttonGroup1_2_2, "col_all" );
    col_all->setChecked( TRUE );

    buttonGroup1_2_2Layout->addWidget( col_all, 0, 0 );
    layout9->addWidget( buttonGroup1_2_2 );

    buttonGroup3 = new QButtonGroup( this, "buttonGroup3" );
    buttonGroup3->setExclusive( TRUE );
    buttonGroup3->setColumnLayout(0, Qt::Vertical );
    buttonGroup3->layout()->setSpacing( 6 );
    buttonGroup3->layout()->setMargin( 11 );
    buttonGroup3Layout = new QGridLayout( buttonGroup3->layout() );
    buttonGroup3Layout->setAlignment( Qt::AlignTop );

    space = new QCheckBox( buttonGroup3, "space" );

    buttonGroup3Layout->addWidget( space, 1, 0 );

    comma = new QCheckBox( buttonGroup3, "comma" );

    buttonGroup3Layout->addWidget( comma, 2, 0 );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 

    other = new QCheckBox( buttonGroup3, "other" );
    layout7->addWidget( other );

    otherEdit = new QLineEdit( buttonGroup3, "otherEdit" );
    otherEdit->setEnabled( FALSE );
    layout7->addWidget( otherEdit );

    buttonGroup3Layout->addLayout( layout7, 3, 0 );

    tab = new QCheckBox( buttonGroup3, "tab" );
    tab->setChecked( TRUE );

    buttonGroup3Layout->addWidget( tab, 0, 0 );
    layout9->addWidget( buttonGroup3 );

    textExportLayout->addLayout( layout9, 1, 0 );
    languageChange();
    resize( QSize(436, 242).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( browse, SIGNAL( clicked() ), this, SLOT( browseSlot() ) );
    connect( other, SIGNAL( toggled(bool) ), this, SLOT( otherClickedSlot(bool) ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
textExport::~textExport()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void textExport::languageChange()
{
    setCaption( tr( "Text Export" ) );
    textLabel1->setText( tr( "File Name" ) );
    browse->setText( tr( "../" ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    buttonGroup1_2->setTitle( tr( "Rows" ) );
    row_all->setText( tr( "All" ) );
    row_sel->setText( tr( "Selected" ) );
    row_un->setText( tr( "Un-Selected" ) );
    buttonGroup1_2_2->setTitle( tr( "Columns" ) );
    col_sel->setText( tr( "Selected" ) );
    col_un->setText( tr( "Un-Selected" ) );
    col_all->setText( tr( "All" ) );
    buttonGroup3->setTitle( tr( "Delimiter" ) );
    space->setText( tr( "Space" ) );
    comma->setText( tr( "comma" ) );
    other->setText( tr( "Other" ) );
    tab->setText( tr( "Tab" ) );
}

