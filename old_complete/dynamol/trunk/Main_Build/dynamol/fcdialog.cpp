/****************************************************************************
** Form implementation generated from reading ui file 'fcdialog.ui'
**
** Created: Fri Feb 24 08:05:56 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "fcdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a fcDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
fcDialog::fcDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "fcDialog" );
    setSizeGripEnabled( TRUE );
    fcDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "fcDialogLayout"); 

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonHelp = new QPushButton( this, "buttonHelp" );
    buttonHelp->setAutoDefault( TRUE );
    Layout1->addWidget( buttonHelp );
    Horizontal_Spacing2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    fcDialogLayout->addMultiCellLayout( Layout1, 2, 2, 0, 1 );

    textEdit7 = new QTextEdit( this, "textEdit7" );
    textEdit7->setWordWrap( QTextEdit::WidgetWidth );

    fcDialogLayout->addMultiCellWidget( textEdit7, 0, 1, 1, 1 );

    groupBox8 = new QGroupBox( this, "groupBox8" );
    groupBox8->setColumnLayout(0, Qt::Vertical );
    groupBox8->layout()->setSpacing( 6 );
    groupBox8->layout()->setMargin( 11 );
    groupBox8Layout = new QGridLayout( groupBox8->layout() );
    groupBox8Layout->setAlignment( Qt::AlignTop );

    layout32 = new QVBoxLayout( 0, 0, 6, "layout32"); 

    layout31 = new QHBoxLayout( 0, 0, 6, "layout31"); 

    textLabel2 = new QLabel( groupBox8, "textLabel2" );
    layout31->addWidget( textLabel2 );

    dynIter = new QSpinBox( groupBox8, "dynIter" );
    dynIter->setMaxValue( 100000 );
    dynIter->setMinValue( 1 );
    dynIter->setValue( 1000 );
    layout31->addWidget( dynIter );
    layout32->addLayout( layout31 );

    layout30 = new QVBoxLayout( 0, 0, 6, "layout30"); 

    layout28 = new QHBoxLayout( 0, 0, 6, "layout28"); 

    textLabel1_3 = new QLabel( groupBox8, "textLabel1_3" );
    layout28->addWidget( textLabel1_3 );

    annealPercent = new QSpinBox( groupBox8, "annealPercent" );
    annealPercent->setMaxValue( 100 );
    annealPercent->setMinValue( 1 );
    annealPercent->setLineStep( 1 );
    annealPercent->setValue( 1 );
    layout28->addWidget( annealPercent );
    layout30->addLayout( layout28 );

    layout29 = new QHBoxLayout( 0, 0, 6, "layout29"); 

    textLabel2_2 = new QLabel( groupBox8, "textLabel2_2" );
    layout29->addWidget( textLabel2_2 );

    rmseCoords = new QLineEdit( groupBox8, "rmseCoords" );
    layout29->addWidget( rmseCoords );
    layout30->addLayout( layout29 );
    layout32->addLayout( layout30 );

    groupBox8Layout->addLayout( layout32, 0, 0 );

    fcDialogLayout->addWidget( groupBox8, 0, 0 );

    groupBox7 = new QGroupBox( this, "groupBox7" );
    groupBox7->setColumnLayout(0, Qt::Vertical );
    groupBox7->layout()->setSpacing( 6 );
    groupBox7->layout()->setMargin( 11 );
    groupBox7Layout = new QGridLayout( groupBox7->layout() );
    groupBox7Layout->setAlignment( Qt::AlignTop );

    layout26 = new QHBoxLayout( 0, 0, 6, "layout26"); 

    layout25 = new QVBoxLayout( 0, 0, 6, "layout25"); 

    textLabel1 = new QLabel( groupBox7, "textLabel1" );
    layout25->addWidget( textLabel1 );

    textLabel1_2 = new QLabel( groupBox7, "textLabel1_2" );
    layout25->addWidget( textLabel1_2 );

    textLabel1_2_2 = new QLabel( groupBox7, "textLabel1_2_2" );
    layout25->addWidget( textLabel1_2_2 );
    layout26->addLayout( layout25 );

    layout24 = new QVBoxLayout( 0, 0, 6, "layout24"); 

    rmse = new QLineEdit( groupBox7, "rmse" );
    layout24->addWidget( rmse );

    maxForce = new QLineEdit( groupBox7, "maxForce" );
    layout24->addWidget( maxForce );

    minEChange = new QLineEdit( groupBox7, "minEChange" );
    layout24->addWidget( minEChange );
    layout26->addLayout( layout24 );

    groupBox7Layout->addLayout( layout26, 0, 0 );

    fcDialogLayout->addWidget( groupBox7, 1, 0 );
    languageChange();
    resize( QSize(681, 393).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
fcDialog::~fcDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void fcDialog::languageChange()
{
    setCaption( tr( "Dynamic/Mechanics Termination Control" ) );
    buttonHelp->setText( tr( "&Help" ) );
    buttonHelp->setAccel( QKeySequence( tr( "F1" ) ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    textEdit7->setText( tr( "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:10pt;font-family:Sans\">\n"
"<p><span style=\"font-weight:600\">Dynamics</span><br />During the course of the Dynamics simulation the average energy is calculated for a specified iteration interval. When the current interval average is higher than the previous interval average the simulation stops a proceeds with minimization. A larger interval takes longer to run but the search is &quot;more&quot; complete. <br /><br /><span style=\"font-weight:600\">Minimization</span><br />There are four criteria which can be used to determine minimization convergence. Any of these methods can be disabled by setting the value to zero. At a bare minimum it is recommended that you at least monitor the RMSE of the Atomic Forces. </p>\n"
"</body></html>\n"
"" ) );
    groupBox8->setTitle( tr( "Dynamics Termination" ) );
    textLabel2->setText( tr( "Anneal Interval" ) );
    textLabel1_3->setText( tr( "Anneal Percent" ) );
    textLabel2_2->setText( tr( "RMSE of Coords" ) );
    rmseCoords->setText( tr( "1.0" ) );
    groupBox7->setTitle( tr( "Minimization Termination" ) );
    textLabel1->setText( tr( "Minimum RMSE of Atomic Forces" ) );
    textLabel1_2->setText( tr( "Maximum Atomic Force" ) );
    textLabel1_2_2->setText( tr( "Minimum Energy Change" ) );
    rmse->setText( tr( "0.0005" ) );
    maxForce->setText( tr( "0.0001" ) );
    minEChange->setText( tr( "0.0001" ) );
}

