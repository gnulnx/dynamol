/****************************************************************************
** Form implementation generated from reading ui file 'gafffphelp.ui'
**
** Created: Wed Aug 17 12:31:41 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
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
"<b>Step 1.  Building the Fingerprints</b>\n"
"<BR>\n"
"\n"
"Before any similarity calculation can be performed fingerprint files must be constructed.  Fingerprint files are constructed by providing a set of molecules in the (*.sdf) file format.  All molecule should be in 3D with hydrogens added.  \n"
"<BR>\n"
"If you are going to screen against a local set of compounds then you should calculate a fingerprint file for those compounds as well.  \n"
"<br><br>\n"
"<i>Note:  The non-commercial version of dynamol limits local searches to fingerprint files of less than 100,000 entries.  The commercial version does not limit you in any way.  Visit http://www.dynamol.com to inquire about a commercial license.</i>\n"
"\n"
"<BR>\n"
"<BR>\n"
"<b>Step 2.  Testing Model</b>\n"
"<BR>\n"
"As mentioned in the gafffp theory section of the user manual there are two basic parameters that can be manipulated.  The maximum number of selected descriptors and the minimum occurrence probability of selected descriptors in the training set.  It is a good idea to test these parameters on a small subset first.  Dynamol has provided a diverse set of 1000 fingerprints ($DYNAMOL/FingerPrint/div.fp).  There is no guarantee that the best parameters used on the diverse set will be the best on the final set.  However, experience shows that a max of 40 descriptors and a 10% minimum occurrence probability works well for a wide variety of datasets. \n"
"<BR><BR>\n"
"To test the parameters provide both training and test set fingerprint files (*.fp) and set the adjustable parameters.  When you hit the test model button Dynamol will build a model on the training set supplied and will return the hit rate of the test set.  Note:  The hit rate is the percentage of test set compounds found in the top 100 returned results.  Obviously the more compounds screened the lower the expected hit rate.  \n"
"\n"
"<BR><BR>\n"
"<b>Step 3.  Screen for Hits</b>\n"
"The final step is to screen a database for new compounds.  There are two basic modes of operation.  The first option is to screen a local database of compounds for which you have built a fingerprint file.\n"
"<br><br>\n"
"<i>Note:  The non-commercial version of dynamol limits local searches to fingerprint files of less than 100,000 entries.  The commercial version does not limit you in any way.  Visit http://www.dynamol.com to inquire about a commercial license.</i>\n"
"<BR><BR>\n"
"The second mode of operation is to screen a large database of commercially available compounds from the Dynamol Servers (~1.8 million).  At this time the database is a subset of chemically unique compounds from the ZINC database.  In order to screen the ZINC database a commercial license is required.\n"
"\n"
"<br><br>\n"
"<i>Note: ZINC is a free database of commercially available compounds that John Irwin and Brain Schoicet are maintaining.  For more information on the ZINC database go to http://blaster.docking.org/zinc/\n"
"<br><br>\n"
"You might also want to check out: <br>\n"
"Irwin and Shoichet, J. Chem. Inf. Model. 2005;45(1):177-82</i> " ) );
}

