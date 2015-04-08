/****************************************************************************
** Form implementation generated from reading ui file 'labeldialog.ui'
**
** Created: Thu Mar 17 09:20:36 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "labeldialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "labeldialog.ui.h"

#include <qobject.h>
/*
 *  Constructs a labelDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
labelDialog::labelDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "labelDialog" );
    setSizeGripEnabled( TRUE );
    setModal( FALSE );
    labelDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "labelDialogLayout"); 

    layout20 = new QVBoxLayout( 0, 0, 6, "layout20"); 

    layout19 = new QVBoxLayout( 0, 0, 6, "layout19"); 

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 

    frame3 = new QFrame( this, "frame3" );
    frame3->setFrameShape( QFrame::StyledPanel );
    frame3->setFrameShadow( QFrame::Raised );
    frame3Layout = new QGridLayout( frame3, 1, 1, 11, 6, "frame3Layout"); 

    layout3 = new QVBoxLayout( 0, 0, 6, "layout3"); 

    symbol = new QCheckBox( frame3, "symbol" );
    layout3->addWidget( symbol );

    type = new QCheckBox( frame3, "type" );
    layout3->addWidget( type );

    charge = new QCheckBox( frame3, "charge" );
    layout3->addWidget( charge );

    frame3Layout->addLayout( layout3, 0, 0 );
    layout8->addWidget( frame3 );

    frame4 = new QFrame( this, "frame4" );
    frame4->setFrameShape( QFrame::StyledPanel );
    frame4->setFrameShadow( QFrame::Raised );
    frame4Layout = new QGridLayout( frame4, 1, 1, 11, 6, "frame4Layout"); 

    layout2 = new QVBoxLayout( 0, 0, 6, "layout2"); 

    atomNum = new QCheckBox( frame4, "atomNum" );
    layout2->addWidget( atomNum );

    resName = new QCheckBox( frame4, "resName" );
    layout2->addWidget( resName );

    resNum = new QCheckBox( frame4, "resNum" );
    layout2->addWidget( resNum );

    frame4Layout->addLayout( layout2, 0, 0 );
    layout8->addWidget( frame4 );
    layout19->addLayout( layout8 );

    frame5 = new QFrame( this, "frame5" );
    frame5->setFrameShape( QFrame::StyledPanel );
    frame5->setFrameShadow( QFrame::Raised );
    frame5Layout = new QGridLayout( frame5, 1, 1, 11, 6, "frame5Layout"); 

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    custom = new QCheckBox( frame5, "custom" );
    layout4->addWidget( custom );

    customEdit = new QLineEdit( frame5, "customEdit" );
    customEdit->setEnabled( FALSE );
    layout4->addWidget( customEdit );

    frame5Layout->addLayout( layout4, 0, 0 );
    layout19->addWidget( frame5 );
    layout20->addLayout( layout19 );

    layout18 = new QHBoxLayout( 0, 0, 6, "layout18"); 

    clear = new QPushButton( this, "clear" );
    clear->setAutoDefault( TRUE );
    layout18->addWidget( clear );

    apply = new QPushButton( this, "apply" );
    apply->setAutoDefault( TRUE );
    layout18->addWidget( apply );
    Horizontal_Spacing2 = new QSpacerItem( 140, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout18->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    layout18->addWidget( buttonOk );
    layout20->addLayout( layout18 );

    labelDialogLayout->addLayout( layout20, 0, 0 );
    languageChange();
    resize( QSize(429, 281).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( custom, SIGNAL( toggled(bool) ), this, SLOT( customSlot(bool) ) );
    connect( clear, SIGNAL( clicked() ), this, SLOT( clearSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
labelDialog::~labelDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void labelDialog::languageChange()
{
    setCaption( tr( "Labels" ) );
    symbol->setText( tr( "Atom Symbol" ) );
    type->setText( tr( "Atom Type" ) );
    charge->setText( tr( "Charge" ) );
    atomNum->setText( tr( "Atom Number" ) );
    resName->setText( tr( "Mol/Residue Name" ) );
    resNum->setText( tr( "Mol/Residue Number" ) );
    custom->setText( tr( "Custom" ) );
    clear->setText( tr( "Clear" ) );
    clear->setAccel( QKeySequence( QString::null ) );
    apply->setText( tr( "Apply" ) );
    apply->setAccel( QKeySequence( QString::null ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
}



























