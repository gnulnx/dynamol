/****************************************************************************
** Form implementation generated from reading ui file 'sysHelpDialog.ui'
**
** Created: Sun Apr 3 16:19:35 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "sysHelpDialog.h"

#include <qvariant.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a sysHelpDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
sysHelpDialog::sysHelpDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "sysHelpDialog" );
    setSizeGripEnabled( TRUE );

    QWidget* privateLayoutWidget = new QWidget( this, "layout40" );
    privateLayoutWidget->setGeometry( QRect( 20, 10, 470, 260 ) );
    layout40 = new QVBoxLayout( privateLayoutWidget, 11, 6, "layout40"); 

    textEdit1 = new QTextEdit( privateLayoutWidget, "textEdit1" );
    textEdit1->setWordWrap( QTextEdit::WidgetWidth );
    layout40->addWidget( textEdit1 );

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonOk = new QPushButton( privateLayoutWidget, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );
    layout40->addLayout( Layout1 );
    languageChange();
    resize( QSize(511, 282).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
sysHelpDialog::~sysHelpDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void sysHelpDialog::languageChange()
{
    setCaption( tr( "Help Dialog" ) );
    textEdit1->setText( tr( "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:10pt;font-family:Sans\">\n"
"<p><span style=\"font-weight:600\">Overview </span><br />A systematic conformational search explores conformational space in a systematic way by performing rotations about user specified rotable bonds. A systematic search is really only acceptable when the number of bonds allowed to rotate is very small. In addition it is a bad choice if you need to explore various ring conformations. <br /><br /><span style=\"font-weight:600\">Energy Setup </span><br />\n"
"The cutoff value determines the maximum allowable van der Walls energy in the initial stage of the search.<br>\n"
"If the minimization box is check the initial stage will be followed by a full molecular mechanics minimization using  the general amber force field (gaff) for small organic molecules and the amber 2003 force field for proteins. <br />You can help control the number of conformations which are returned by lowering the acceptable energy cutoff value. You may also want to minimize the resulting conformations. The enregy convergence criteria can be set in by clicking on the Energy Setup Button. At this time all energy calculations are done with a dielectric constant of 1.</p>\n"
"</body></html>\n"
"" ) );
    buttonOk->setText( tr( "Done" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
}

























