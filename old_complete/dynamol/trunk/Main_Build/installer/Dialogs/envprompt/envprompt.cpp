/****************************************************************************
** Form implementation generated from reading ui file 'envprompt.ui'
**
** Created: Mon Feb 21 15:47:30 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "envprompt.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a envprompt as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
envprompt::envprompt( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "envprompt" );
    setSizeGripEnabled( TRUE );

    QWidget* privateLayoutWidget = new QWidget( this, "layout5" );
    privateLayoutWidget->setGeometry( QRect( 20, 11, 550, 540 ) );
    layout5 = new QVBoxLayout( privateLayoutWidget, 11, 6, "layout5"); 

    textEdit1 = new QTextEdit( privateLayoutWidget, "textEdit1" );
    textEdit1->setWordWrap( QTextEdit::WidgetWidth );
    layout5->addWidget( textEdit1 );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    checkBox = new QCheckBox( privateLayoutWidget, "checkBox" );
    layout3->addWidget( checkBox );
    spacer2 = new QSpacerItem( 61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout3->addItem( spacer2 );
    layout5->addLayout( layout3 );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    buttonOk = new QPushButton( privateLayoutWidget, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    layout4->addWidget( buttonOk );
    spacer3 = new QSpacerItem( 101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout4->addItem( spacer3 );
    layout5->addLayout( layout4 );
    languageChange();
    resize( QSize(581, 572).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
envprompt::~envprompt()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void envprompt::languageChange()
{
    setCaption( tr( "Environment Variables" ) );
    textEdit1->setText( tr( "Some environment variables need to be set in order for the Dynamol software to work.  If you are using the BASH shell then the installer can perform these functions for you.  The process involves modifying the .bash_profile and .bashrc files in each of the directories found in /home.  It also involves modifying the /etc/bashrc file.  All of the respective files will be backed up and saved  (ex.  .bashrc.backup)  before any modification is done.  You will also have to perform the install as root to have /etc/bashrc modified.\n"
"\n"
"If you choose to not have the installer do this for you then you will need to set  environment variables according to the following conventions.\n"
"\n"
"If you are using the BASH shell (check by typing 'echo $SHELL' at the command prompt) and you choose the following install path: /usr/local\n"
"Then you would need to set the following variables\n"
"\n"
"export DYNAMOL=/usr/local/dynamol\n"
"export PATH=$PATH:/usr/local/dynamol/bin\n"
"\n"
"It is reccomended that you append the above lines to the .bashrc and .bash_profile files in your home directories.  This will prevent you from having to reset these variables each time you login.\n"
"\n"
"If you are using a different shell then you will need to set the environment variables according to your shells specifications.  For instance if you are using the tcsh shell then you would replace the 'export' command with 'set env'" ) );
    checkBox->setText( tr( "Check Box to Perform Auto Update" ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
}

