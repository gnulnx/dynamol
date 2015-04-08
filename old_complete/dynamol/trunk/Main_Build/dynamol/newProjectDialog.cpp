/****************************************************************************
** Form implementation generated from reading ui file 'newProjectDialog.ui'
**
** Created: Thu Nov 18 12:10:25 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "newProjectDialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include <iostream>

using namespace std;

/*
 *  Constructs a newProject as a child of 'parent', with the
 *  name 'name' && widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
newProject::newProject( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "newProject" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 500, 450 ) );
    setMaximumSize( QSize( 500, 450 ) );
    setSizeGripEnabled( TRUE );

    QWidget* privateLayoutWidget = new QWidget( this, "Layout1" );
    privateLayoutWidget->setGeometry( QRect( 10, 400, 476, 33 ) );
    Layout1 = new QHBoxLayout( privateLayoutWidget, 0, 6, "Layout1"); 

    buttonHelp = new QPushButton( privateLayoutWidget, "buttonHelp" );
    buttonHelp->setAutoDefault( TRUE );
    Layout1->addWidget( buttonHelp );
    Horizontal_Spacing2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( privateLayoutWidget, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( privateLayoutWidget, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    

   

    QWidget* privateLayoutWidget_2 = new QWidget( this, "layout8" );
    privateLayoutWidget_2->setGeometry( QRect( 20, 10, 135, 98 ) );
    layout8 = new QVBoxLayout( privateLayoutWidget_2, 11, 6, "layout8"); 

    Name = new QLabel( privateLayoutWidget_2, "Name" );
    layout8->addWidget( Name );

    author = new QLabel( privateLayoutWidget_2, "author" );
    layout8->addWidget( author );

    date = new QLabel( privateLayoutWidget_2, "date" );
    layout8->addWidget( date );

    description = new QLabel( this, "description" );
    description->setGeometry( QRect( 20, 130, 300, 21 ) );
    
    nameEdit = new QLineEdit( this, "nameEdit" );
    ////////////cout <<"Nameedit created " << nameEdit->text() << endl;
    nameEdit->setGeometry( QRect( 162, 10, 290, 28 ) );
    
    authoredit = new QLineEdit( this, "authoredit" );
    authoredit->setGeometry( QRect( 162, 45, 290, 28 ) );
    
    dateEdit = new QLineEdit( this, "dateEdit" );
    dateEdit->setGeometry( QRect( 162, 80, 290, 28 ) );
    
    descEdit = new QTextEdit( this, "descEdit" );
    descEdit->setGeometry( QRect( 10, 160, 471, 220 ) );

    

    
    languageChange();
    resize( QSize(500, 450).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals && slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );

    // buddies
    Name->setBuddy( nameEdit );
    author->setBuddy( authoredit );
    date->setBuddy( dateEdit );
}

/*
 *  Destroys the object && frees any allocated resources
 */
newProject::~newProject()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void newProject::languageChange()
{
    setCaption( tr( "New Project Setup" ) );
    buttonHelp->setText( tr( "&Help" ) );
    buttonHelp->setAccel( QKeySequence( tr( "F1" ) ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    Name->setText( tr( "Project Name" ) );
    author->setText( tr( "Author" ) );
    date->setText( tr( "Date" ) );
    description->setText( tr( "Project Description" ) );
    authoredit->setText( QString::null );
}






































