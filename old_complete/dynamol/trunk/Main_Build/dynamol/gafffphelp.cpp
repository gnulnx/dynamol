/****************************************************************************
** Form implementation generated from reading ui file 'gafffphelp.ui'
**
** Created: Mon Oct 17 13:19:31 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "gafffphelp.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a gafffpHelp as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
gafffpHelp::gafffpHelp( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "gafffpHelp" );
    setSizeGripEnabled( TRUE );
    gafffpHelpLayout = new QGridLayout( this, 1, 1, 11, 6, "gafffpHelpLayout"); 

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    gafffpHelpLayout->addLayout( Layout1, 1, 0 );

    textEdit1 = new QTextEdit( this, "textEdit1" );
    textEdit1->setTextFormat( QTextEdit::RichText );
    textEdit1->setWordWrap( QTextEdit::WidgetWidth );

    gafffpHelpLayout->addWidget( textEdit1, 0, 0 );
    languageChange();
    resize( QSize(505, 448).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( close() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
gafffpHelp::~gafffpHelp()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void gafffpHelp::languageChange()
{
    setCaption( tr( "Help" ) );
    buttonOk->setText( tr( "Done" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    textEdit1->setText( tr( "For a complete introduction to the gaff atom environment fingerprints please consult the user manual.  This help dialog only covers the options present in the dialog box\n"
"\n"
"<BR><BR>\n"
"<b>Step 1.  Search or Build</b>\n"
"<BR>\n"
"Dynamol supports two modes of operation:  1) Searching the Dynamol databases of commercially available compounds, 2) searching a local database.  If you will be searching the Dynamol databases then you should proceed to step two.  In order to search a local database you need to construct a database of fingerprint files.  \n"
"<br><br>\n"
"<i>Note:  The non-commercial version of dynamol limits local searches to fingerprint files of less than 100,000 entries.  The commercial version does not limit you in any way.  Visit http://www.dynamol.com to inquire about a commercial license.</i>\n"
"\n"
"<BR>\n"
"<BR>\n"
"<b>Step 2.  Trainging and Test Sets</b>\n"
"<BR>\n"
"In Step two you are required to supply a set of query compounds to use for the search.  The query structures can come from an SD (*.sdf) file or from molecules in the MolView window.  In addition you may supply an SD (*.sdf) file of test set compounds.   \n"
"\n"
"\n"
"<BR><BR>\n"
"<b>Step 3.  Screen for Hits</b>\n"
"The final step is to screen a database.  You can choose a Dynamol database or alternatively you can use a local file which you have created fingerprints for.  At this time Dynamol is hosting a unique subset of the ZINC database.  This subset is ~1.8 million compounds.  Once you have selected your database of choice then simply press the \"Find Hits\" button and wait.  Dynamol database serach results will be displayed in a small color coded table.  The actual structures with vendor information will also be proved in a Table format.  You should contact the vendors (not Dynamol) about purchasing these compounds.  Local searches do not return the compounds in a table.  \n"
"\n"
"<br><br>\n"
"<b>Color Coding </b>\n"
"Query  =  Grey\n"
"Test    =  Green\n"
"Hits     =  Yellow \n"
"\n"
"\n"
"<br><br>\n"
"<i>Note:  The non-commercial version of dynamol limits local searches to fingerprint files of less than 100,000 entries.  The commercial version does not limit you in any way.  Visit http://www.dynamol.com to inquire about a commercial license.</i>\n"
"\n"
"<br><br>\n"
"<i>Note: ZINC is a free database of commercially available compounds that John Irwin and Brain Schoicet are maintaining.  For more information on the ZINC database go to http://blaster.docking.org/zinc/\n"
"<br><br>\n"
"You might also want to check out: <br>\n"
"Irwin and Shoichet, J. Chem. Inf. Model. 2005;45(1):177-82</i> " ) );
}


