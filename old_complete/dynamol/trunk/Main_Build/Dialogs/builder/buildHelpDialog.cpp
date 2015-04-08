/****************************************************************************
** Form implementation generated from reading ui file 'buildHelpDialog.ui'
**
** Created: Sun Apr 3 16:19:11 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "buildHelpDialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a buildHelpDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
buildHelpDialog::buildHelpDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "buildHelpDialog" );
    setSizeGripEnabled( TRUE );
    buildHelpDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "buildHelpDialogLayout"); 

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buildHelpDialogLayout->addLayout( Layout1, 1, 0 );

    textEdit1 = new QTextEdit( this, "textEdit1" );
    textEdit1->setTextFormat( QTextEdit::RichText );
    textEdit1->setWordWrap( QTextEdit::WidgetWidth );

    buildHelpDialogLayout->addWidget( textEdit1, 0, 0 );
    languageChange();
    resize( QSize(406, 815).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
buildHelpDialog::~buildHelpDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void buildHelpDialog::languageChange()
{
    setCaption( tr( "Build Help" ) );
    buttonOk->setText( tr( "Done" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    textEdit1->setText( tr( "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:14pt;font-family:Helvetica\">\n"
"<p>The Dynamol build utility is designed to be as intuitive as possible. There are three basic modes of operation. <br /><br />1) Build Mode. <br />2) Retype Mode. <br />3) Delete Mode. <br /><br /><span style=\"font-size:21pt;font-weight:600\">Build Mode</span> <br />Build mode had two modes of operation. <br /><br />1) Sketch Mode.<br />2) Ring Mode.<br /><br /><span style=\"font-weight:600\">Sketch Mode</span><br />While in sketch mode the user selects an atom and a bond type and then simply points and clicks to add a new atom. While in sketch mode you can cycle through single/double/triple bond orders by clicking on a bond. <br /><br /><span style=\"font-weight:600\">Ring Mode</span><br />Ring mode allows the user to add a set of predetermined rings to the system. To enter ring mode simply click on one of the rings and then point to the atom or bond that you would like to add the ring. <br /><br /><span style=\"font-size:21pt;font-weight:600\">Retype Mode </span><br />Retype mode allows the user to change atom types. Simply select a new atom type and then click on the atom you want to change. <br /><br /><span style=\"font-size:21pt;font-weight:600\">Delete Mode</span><br />While in delete mode the user may point and click at individual atoms to delete. If many deletions are required then you may find it beneficial to close out the builder and perform the deletions in the regular view mode.</p>\n"
"</body></html>\n"
"" ) );
}

