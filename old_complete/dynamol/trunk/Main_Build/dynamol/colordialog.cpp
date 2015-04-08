/****************************************************************************
** Form implementation generated from reading ui file 'colordialog.ui'
**
** Created: Wed Feb 22 22:52:28 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "colordialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "colordialog.ui.h"

/*
 *  Constructs a colorDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
colorDialog::colorDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "colorDialog" );
    colorDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "colorDialogLayout"); 

    buttonGroup1 = new QButtonGroup( this, "buttonGroup1" );
    buttonGroup1->setColumnLayout(0, Qt::Vertical );
    buttonGroup1->layout()->setSpacing( 6 );
    buttonGroup1->layout()->setMargin( 11 );
    buttonGroup1Layout = new QGridLayout( buttonGroup1->layout() );
    buttonGroup1Layout->setAlignment( Qt::AlignTop );

    layout28 = new QVBoxLayout( 0, 0, 6, "layout28"); 

    layout19 = new QHBoxLayout( 0, 0, 6, "layout19"); 

    Label1 = new QLabel( buttonGroup1, "Label1" );
    layout19->addWidget( Label1 );

    pushButton1 = new QPushButton( buttonGroup1, "pushButton1" );
    layout19->addWidget( pushButton1 );
    layout28->addLayout( layout19 );

    layout19_2 = new QHBoxLayout( 0, 0, 6, "layout19_2"); 

    Label2 = new QLabel( buttonGroup1, "Label2" );
    layout19_2->addWidget( Label2 );

    pushButton2 = new QPushButton( buttonGroup1, "pushButton2" );
    layout19_2->addWidget( pushButton2 );
    layout28->addLayout( layout19_2 );

    layout19_2_2 = new QHBoxLayout( 0, 0, 6, "layout19_2_2"); 

    Label3 = new QLabel( buttonGroup1, "Label3" );
    layout19_2_2->addWidget( Label3 );

    pushButton3 = new QPushButton( buttonGroup1, "pushButton3" );
    layout19_2_2->addWidget( pushButton3 );
    layout28->addLayout( layout19_2_2 );

    layout19_2_2_2 = new QHBoxLayout( 0, 0, 6, "layout19_2_2_2"); 

    Label4 = new QLabel( buttonGroup1, "Label4" );
    layout19_2_2_2->addWidget( Label4 );

    pushButton4 = new QPushButton( buttonGroup1, "pushButton4" );
    layout19_2_2_2->addWidget( pushButton4 );
    layout28->addLayout( layout19_2_2_2 );

    layout19_2_2_2_2 = new QHBoxLayout( 0, 0, 6, "layout19_2_2_2_2"); 

    Label5 = new QLabel( buttonGroup1, "Label5" );
    layout19_2_2_2_2->addWidget( Label5 );

    pushButton5 = new QPushButton( buttonGroup1, "pushButton5" );
    layout19_2_2_2_2->addWidget( pushButton5 );
    layout28->addLayout( layout19_2_2_2_2 );

    layout19_2_2_2_2_2 = new QHBoxLayout( 0, 0, 6, "layout19_2_2_2_2_2"); 

    Label6 = new QLabel( buttonGroup1, "Label6" );
    layout19_2_2_2_2_2->addWidget( Label6 );

    pushButton6 = new QPushButton( buttonGroup1, "pushButton6" );
    layout19_2_2_2_2_2->addWidget( pushButton6 );
    layout28->addLayout( layout19_2_2_2_2_2 );

    layout19_2_2_2_2_2_2 = new QHBoxLayout( 0, 0, 6, "layout19_2_2_2_2_2_2"); 

    Label7 = new QLabel( buttonGroup1, "Label7" );
    layout19_2_2_2_2_2_2->addWidget( Label7 );

    pushButton7 = new QPushButton( buttonGroup1, "pushButton7" );
    layout19_2_2_2_2_2_2->addWidget( pushButton7 );
    layout28->addLayout( layout19_2_2_2_2_2_2 );

    layout19_2_2_2_2_2_2_2 = new QHBoxLayout( 0, 0, 6, "layout19_2_2_2_2_2_2_2"); 

    Label8 = new QLabel( buttonGroup1, "Label8" );
    layout19_2_2_2_2_2_2_2->addWidget( Label8 );

    pushButton8 = new QPushButton( buttonGroup1, "pushButton8" );
    layout19_2_2_2_2_2_2_2->addWidget( pushButton8 );
    layout28->addLayout( layout19_2_2_2_2_2_2_2 );

    layout19_2_2_2_2_2_2_2_2 = new QHBoxLayout( 0, 0, 6, "layout19_2_2_2_2_2_2_2_2"); 

    Label9 = new QLabel( buttonGroup1, "Label9" );
    layout19_2_2_2_2_2_2_2_2->addWidget( Label9 );

    pushButton9 = new QPushButton( buttonGroup1, "pushButton9" );
    layout19_2_2_2_2_2_2_2_2->addWidget( pushButton9 );
    layout28->addLayout( layout19_2_2_2_2_2_2_2_2 );

    buttonGroup1Layout->addLayout( layout28, 0, 0 );

    colorDialogLayout->addWidget( buttonGroup1, 0, 0 );

    groupBox1 = new QGroupBox( this, "groupBox1" );
    groupBox1->setColumnLayout(0, Qt::Vertical );
    groupBox1->layout()->setSpacing( 6 );
    groupBox1->layout()->setMargin( 11 );
    groupBox1Layout = new QGridLayout( groupBox1->layout() );
    groupBox1Layout->setAlignment( Qt::AlignTop );

    layout16 = new QHBoxLayout( 0, 0, 6, "layout16"); 

    layout15 = new QVBoxLayout( 0, 0, 6, "layout15"); 

    Label10 = new QLabel( groupBox1, "Label10" );
    layout15->addWidget( Label10 );

    Label11 = new QLabel( groupBox1, "Label11" );
    layout15->addWidget( Label11 );

    Label12 = new QLabel( groupBox1, "Label12" );
    layout15->addWidget( Label12 );

    Label13 = new QLabel( groupBox1, "Label13" );
    layout15->addWidget( Label13 );

    Label14 = new QLabel( groupBox1, "Label14" );
    layout15->addWidget( Label14 );

    Label15 = new QLabel( groupBox1, "Label15" );
    layout15->addWidget( Label15 );

    Label16 = new QLabel( groupBox1, "Label16" );
    layout15->addWidget( Label16 );
    layout16->addLayout( layout15 );

    layout14 = new QVBoxLayout( 0, 0, 6, "layout14"); 

    pushButton10 = new QPushButton( groupBox1, "pushButton10" );
    layout14->addWidget( pushButton10 );

    pushButton11 = new QPushButton( groupBox1, "pushButton11" );
    layout14->addWidget( pushButton11 );

    pushButton12 = new QPushButton( groupBox1, "pushButton12" );
    layout14->addWidget( pushButton12 );

    pushButton13 = new QPushButton( groupBox1, "pushButton13" );
    layout14->addWidget( pushButton13 );

    pushButton14 = new QPushButton( groupBox1, "pushButton14" );
    layout14->addWidget( pushButton14 );

    pushButton15 = new QPushButton( groupBox1, "pushButton15" );
    layout14->addWidget( pushButton15 );

    pushButton16 = new QPushButton( groupBox1, "pushButton16" );
    layout14->addWidget( pushButton16 );
    layout16->addLayout( layout14 );

    groupBox1Layout->addLayout( layout16, 0, 0 );

    pushButton17 = new QPushButton( groupBox1, "pushButton17" );

    groupBox1Layout->addWidget( pushButton17, 1, 0 );

    colorDialogLayout->addWidget( groupBox1, 0, 1 );
    languageChange();
    resize( QSize(342, 393).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( pushButton1, SIGNAL( clicked() ), this, SLOT( cs_1_Slot() ) );
    connect( pushButton2, SIGNAL( clicked() ), this, SLOT( cs_2_Slot() ) );
    connect( pushButton3, SIGNAL( clicked() ), this, SLOT( cs_3_Slot() ) );
    connect( pushButton4, SIGNAL( clicked() ), this, SLOT( cs_4_Slot() ) );
    connect( pushButton5, SIGNAL( clicked() ), this, SLOT( cs_5_Slot() ) );
    connect( pushButton6, SIGNAL( clicked() ), this, SLOT( cs_6_Slot() ) );
    connect( pushButton7, SIGNAL( clicked() ), this, SLOT( cs_7_Slot() ) );
    connect( pushButton8, SIGNAL( clicked() ), this, SLOT( cs_8_Slot() ) );
    connect( pushButton9, SIGNAL( clicked() ), this, SLOT( cs_9_Slot() ) );
    connect( pushButton10, SIGNAL( clicked() ), this, SLOT( us_1_Slot() ) );
    connect( pushButton11, SIGNAL( clicked() ), this, SLOT( us_2_Slot() ) );
    connect( pushButton12, SIGNAL( clicked() ), this, SLOT( us_3_Slot() ) );
    connect( pushButton13, SIGNAL( clicked() ), this, SLOT( us_4_Slot() ) );
    connect( pushButton14, SIGNAL( clicked() ), this, SLOT( us_5_Slot() ) );
    connect( pushButton15, SIGNAL( clicked() ), this, SLOT( us_6_Slot() ) );
    connect( pushButton16, SIGNAL( clicked() ), this, SLOT( us_7_Slot() ) );
    connect( pushButton17, SIGNAL( clicked() ), this, SLOT( saveColorSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
colorDialog::~colorDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void colorDialog::languageChange()
{
    setCaption( tr( "Atom Color Diaog" ) );
    buttonGroup1->setTitle( tr( "Pre-Defined" ) );
    Label1->setText( tr( "<tt><b><font color=\"#ffaa00\">C</font><font color=\"#fe7fbe\">O</font><font color=\"#0055ff\">N</font><font color=\"#ffffff\">H</font><font color=\"#aa0000\">S</font><font color=\"#55ff7f\">P</font></b></tt>" ) );
    pushButton1->setText( tr( "Select" ) );
    Label2->setText( tr( "<tt><b><font color=\"#10da3c\">C</font><font color=\"#e60000\">O</font><font color=\"#3ba3f8\">N</font><font color=\"#ffffff\">H</font><font color=\"#ffaa7f\">S</font><font color=\"#ffff7f\">P</font></b></tt></font>" ) );
    pushButton2->setText( tr( "Select" ) );
    Label3->setText( tr( "<tt><b><font color=\"#ffff7f\">C</font><font color=\"#e60000\">O</font><font color=\"#3ba3f8\">N</font><font color=\"#ffffff\">H</font><font color=\"#ffaa00\">S</font><font color=\"#aa0000\">P</font></b></tt></font>" ) );
    pushButton3->setText( tr( "Select" ) );
    Label4->setText( tr( "<tt><b><font color=\"#f373ff\">C</font><font color=\"#e60000\">O</font><font color=\"#3ba3f8\">N</font><font color=\"#ffffff\">H</font><font color=\"#aa0000\">S</font><font color=\"#55ff7f\">P</font></b></tt></font>" ) );
    pushButton4->setText( tr( "Select" ) );
    Label5->setText( tr( "<tt><b><font color=\"#aa55ff\">C<font color=\"#e60000\">O</font><font color=\"#3ba3f8\">N</font><font color=\"#ffffff\">H</font><font color=\"#aa0000\">S</font><font color=\"#55ff7f\">P</font></b></tt></font>" ) );
    pushButton5->setText( tr( "Select" ) );
    Label6->setText( tr( "<tt><b><font color=\"#ffaa00\">C</font><font color=\"#e60000\">O</font><font color=\"#0055ff\">N</font><font color=\"#ffffff\">H</font><font color=\"#ffff7f\">S</font><font color=\"#55ff7f\">P</font></b></tt></font>" ) );
    pushButton6->setText( tr( "Select" ) );
    Label7->setText( tr( "<tt><b><font color=\"#2ecece\">C</font><font color=\"#e60000\">O</font><font color=\"#0055ff\">N</font><font color=\"#ffffff\">H</font><font color=\"#ffff7f\">S</font><font color=\"#55ff7f\">P</font></b></tt></font>" ) );
    pushButton7->setText( tr( "Select" ) );
    Label8->setText( tr( "<tt><b><font color=\"#bbcceb\">C</font><font color=\"#e60000\">O</font><font color=\"#0055ff\">N</font><font color=\"#ffffff\">H</font><font color=\"#ffff7f\">S</font><font color=\"#55ff7f\">P</font></b></tt></font>" ) );
    pushButton8->setText( tr( "Select" ) );
    Label9->setText( tr( "<tt><b><font color=\"#97aca2\">C</font><font color=\"#e60000\">O</font><font color=\"#0055ff\">N</font><font color=\"#ffffff\">H</font><font color=\"#ffff7f\">S</font><font color=\"#55ff7f\">P</font></b></tt></font>" ) );
    pushButton9->setText( tr( "Select" ) );
    groupBox1->setTitle( tr( "Custom" ) );
    Label10->setText( tr( "<font color=\"#ffaa00\">C</font>" ) );
    Label11->setText( tr( "<font color=\"#ff5500\">O</font>" ) );
    Label12->setText( tr( "<font color=\"#0055ff\">N</font>" ) );
    Label13->setText( tr( "<font color=\"#ffffff\">H</font>" ) );
    Label14->setText( tr( "<font color=\"#ffff00\">S</font>" ) );
    Label15->setText( tr( "<font color=\"#55ff00\">P</font>" ) );
    Label16->setText( tr( "<font color=\"#b1aeaf\">X<</font>" ) );
    pushButton10->setText( tr( "Select" ) );
    pushButton11->setText( tr( "Select" ) );
    pushButton12->setText( tr( "Select" ) );
    pushButton13->setText( tr( "Select" ) );
    pushButton14->setText( tr( "Select" ) );
    pushButton15->setText( tr( "Select" ) );
    pushButton16->setText( tr( "Select" ) );
    pushButton17->setText( tr( "Save Color" ) );
}

