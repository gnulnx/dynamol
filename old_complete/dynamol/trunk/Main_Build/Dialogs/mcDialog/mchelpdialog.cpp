/****************************************************************************
** Form implementation generated from reading ui file 'mchelpdialog.ui'
**
** Created: Sun Apr 17 14:18:10 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "mchelpdialog.h"

#include <qvariant.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a mcHelpDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
mcHelpDialog::mcHelpDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "mcHelpDialog" );
    setSizeGripEnabled( TRUE );
    mcHelpDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "mcHelpDialogLayout"); 

    layout16 = new QVBoxLayout( 0, 0, 6, "layout16"); 

    textEdit1 = new QTextEdit( this, "textEdit1" );
    textEdit1->setWordWrap( QTextEdit::WidgetWidth );
    layout16->addWidget( textEdit1 );

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );
    layout16->addLayout( Layout1 );

    mcHelpDialogLayout->addLayout( layout16, 0, 0 );
    languageChange();
    resize( QSize(410, 377).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
mcHelpDialog::~mcHelpDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void mcHelpDialog::languageChange()
{
    setCaption( tr( "Monte Carlo Help Dialog" ) );
    textEdit1->setText( tr( "<b>Torsional Monte Carlo</b>\n"
"<br>\n"
"The Dynamol Torsional Monte Carlo algorithm works by fixing bond legnths and bond angles.  Torsional space is then explored by randomly rotating single (no ring bonds) through space.  In addition the The Metropolis Criteria is evaluated by exlucing the Non Bond terms to allow a more fluid rotation through space.\n"
"<br>\n"
"<br>\n"
"<b>Standard Monte Carlo</b>\n"
"<br>\n"
"The Standard Monte Carlo Simulator is a basic simulator which makes random changes to the atomic coordinates of a the current molecule.  It is not really a suitable simulation method for modelling molecular complexes as there is no molecular rotation operator.  Future versions will likely include a torsional MC as well as an engine more apt to deal with molecular complexes.\n"
"\n"
"<br><br>\n"
"<b>Force Bias Monte Carlo</b>\n"
"<br>\n"
"The force bias monte carlo algorithm works by making random changes along the direction of the force gradient.  This algorithm is often times more suited to local configuration space exploration than the basic MC algorithm.\n"
"\n"
"<br><br>\n"
"<b>References</b>\n"
"<br>\n"
"Andrew Leach has a great introductory book to molecular modeling which itslef has a great chapter on the various Monte Carlo algorithms\n"
"<br>\n"
"<br>\n"
"Molecular Modelling Principles and Applications, Andrew Leach, Addison Wesley Longman Limited 1996." ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
}

