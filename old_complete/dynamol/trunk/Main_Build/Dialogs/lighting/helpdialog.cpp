/****************************************************************************
** Form implementation generated from reading ui file 'helpdialog.ui'
**
** Created: Sat Nov 20 11:30:31 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.2   edited Nov 24 13:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "helpdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a helpDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
helpDialog::helpDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "helpDialog" );
    setMinimumSize( QSize( 450, 525 ) );
    setMaximumSize( QSize( 450, 525 ) );
    setSizeGripEnabled( TRUE );

    QWidget* privateLayoutWidget = new QWidget( this, "Layout1" );
    privateLayoutWidget->setGeometry( QRect( 10, 460, 430, 40 ) );
    Layout1 = new QHBoxLayout( privateLayoutWidget, 0, 6, "Layout1"); 

    buttonOk = new QPushButton( privateLayoutWidget, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( privateLayoutWidget, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    textEdit1 = new QTextEdit( this, "textEdit1" );
    textEdit1->setGeometry( QRect( 10, 10, 430, 440 ) );
    textEdit1->setWordWrap( QTextEdit::WidgetWidth );
    languageChange();
    resize( QSize(450, 525).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
helpDialog::~helpDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void helpDialog::languageChange()
{
    setCaption( tr( "Lighting Explained" ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    textEdit1->setText( tr( "Set the various RGB (Red, Green, Blue) light properties\n"
"\n"
"Ambient:\n"
"Ambient light appears to come from everywhere.  Mathmetically speaking ambient light has been scattered and reflected so much that it becomes impossible to determine where it came from.\n"
"\n"
"Diffuse:\n"
"Diffuse light is the amount of light coming from a particular direction which disperses uniformaly when it hits the object.  When you specify the x,y,z postion of the light the difuse component will determine how much of each of the RGB components is diffused upon contact with the object.\n"
"\n"
"Specular:\n"
"Specular like diffuse comes from a particluar direction, but it reflects in a particular direction.\n"
"\n"
"\n"
"" ) );
}

