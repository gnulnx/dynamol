/****************************************************************************
** Form implementation generated from reading ui file 'minhelpdialog.ui'
**
** Created: Wed Nov 9 08:01:50 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "minhelpdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

static const unsigned char image0_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x04,
    0x50, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x75, 0x95, 0x4d, 0x68, 0x54,
    0x57, 0x14, 0xc7, 0x7f, 0x23, 0xaf, 0x70, 0x06, 0x46, 0xb8, 0x03, 0x11,
    0xe6, 0x85, 0x14, 0x72, 0x25, 0x0b, 0x27, 0x58, 0x70, 0xfc, 0xc2, 0x4c,
    0x54, 0x30, 0xa2, 0x0b, 0x85, 0x82, 0xb1, 0x16, 0x1a, 0xa1, 0x8b, 0x86,
    0x2e, 0x4a, 0xda, 0x2e, 0xaa, 0xdd, 0xb4, 0x42, 0x17, 0xba, 0xcd, 0xa6,
    0x55, 0xba, 0x92, 0x82, 0xc5, 0x6c, 0x24, 0x53, 0x68, 0xc8, 0x14, 0x2a,
    0x4e, 0x16, 0x65, 0x66, 0x4a, 0x93, 0xce, 0x08, 0x0d, 0xf3, 0xb2, 0x08,
    0x3c, 0xc1, 0x30, 0x6f, 0x20, 0x85, 0x77, 0xc1, 0x81, 0x1c, 0xe8, 0xc0,
    0x74, 0x31, 0x93, 0x68, 0xa2, 0xbe, 0xcd, 0x79, 0xe7, 0xf2, 0xde, 0xb9,
    0xbf, 0xf3, 0xe7, 0x7c, 0x24, 0x9a, 0x8d, 0x26, 0x38, 0xc0, 0x40, 0xe4,
    0x22, 0x7c, 0xe3, 0xef, 0xf2, 0x8f, 0xe5, 0x8f, 0x75, 0xd9, 0xf3, 0x34,
    0x2b, 0xcd, 0xc4, 0xdb, 0xbe, 0xdf, 0xf6, 0x13, 0xe5, 0x4a, 0x19, 0x6b,
    0x2c, 0xa1, 0x0b, 0x77, 0xec, 0x78, 0x7e, 0xbc, 0x8b, 0x07, 0x92, 0x02,
    0x04, 0x4c, 0xdf, 0xe2, 0x81, 0xb6, 0x01, 0x05, 0x75, 0xbd, 0xf7, 0x72,
    0xa5, 0x9c, 0xd8, 0xfb, 0xbf, 0x35, 0x96, 0x44, 0xb3, 0xd1, 0xdc, 0x75,
    0xd3, 0xe0, 0xd9, 0xc1, 0xae, 0x08, 0x4c, 0x9c, 0xca, 0x90, 0xbd, 0x30,
    0xc1, 0xe4, 0x99, 0x49, 0x54, 0xc0, 0x1a, 0x9f, 0xd2, 0x5a, 0x01, 0xdd,
    0xac, 0x51, 0x5a, 0x0d, 0xc0, 0x29, 0xb5, 0xaa, 0xc3, 0x3d, 0x83, 0x27,
    0xbf, 0xff, 0x9d, 0xd8, 0x4b, 0xbe, 0x8b, 0xf8, 0xfc, 0xd9, 0xf1, 0x2e,
    0x06, 0x66, 0xbe, 0x98, 0x64, 0xf2, 0xca, 0x27, 0xe4, 0x47, 0x26, 0x68,
    0xb4, 0xea, 0xa8, 0x8b, 0x29, 0x2d, 0x17, 0x49, 0x7b, 0x8e, 0xb0, 0x13,
    0x11, 0x77, 0x1c, 0xae, 0x1d, 0xa1, 0x6d, 0x25, 0xac, 0x3b, 0xc2, 0x15,
    0x61, 0xb1, 0xf0, 0x24, 0xf1, 0x1a, 0xf1, 0x0e, 0xa9, 0x81, 0xbb, 0xb3,
    0xb7, 0x99, 0xbe, 0x72, 0x0b, 0x04, 0x2a, 0x4f, 0x17, 0x09, 0xaa, 0x01,
    0xc5, 0x95, 0x25, 0xc6, 0x0e, 0xe5, 0x58, 0x5a, 0x2b, 0x62, 0xbc, 0x18,
    0x97, 0x52, 0x72, 0x87, 0x20, 0x6c, 0x2b, 0x36, 0x05, 0x95, 0x15, 0xa5,
    0xbe, 0x00, 0x4f, 0x7e, 0x2d, 0xef, 0x90, 0xef, 0x0b, 0x5d, 0xc8, 0x60,
    0x7e, 0xb0, 0x8b, 0xf4, 0x48, 0xa7, 0xae, 0xcc, 0x80, 0x40, 0x6d, 0xbd,
    0x44, 0xf1, 0x71, 0x11, 0xf1, 0xd3, 0xcc, 0x3f, 0x58, 0xe4, 0xe6, 0x37,
    0x77, 0x58, 0x7c, 0x50, 0x63, 0xe6, 0xd3, 0xbb, 0xc4, 0x21, 0xd4, 0xd7,
    0x1d, 0x00, 0x91, 0x42, 0xf6, 0xb8, 0x90, 0x3d, 0x2d, 0x8c, 0x5f, 0x1c,
    0xef, 0x86, 0x2e, 0x04, 0x03, 0xfb, 0xac, 0xb1, 0x20, 0x70, 0xe9, 0x54,
    0x86, 0x1b, 0xd7, 0x6e, 0x93, 0xdc, 0x9f, 0xa6, 0xb1, 0x51, 0x21, 0x5c,
    0x0e, 0xb0, 0x99, 0x51, 0xae, 0x5f, 0x9b, 0x86, 0x17, 0xf0, 0xf0, 0xc1,
    0x3d, 0xe2, 0x20, 0x22, 0x3f, 0x76, 0x99, 0x99, 0x8f, 0x6f, 0x60, 0x9c,
    0x80, 0x82, 0x35, 0x02, 0x1e, 0x5c, 0x9f, 0xca, 0x91, 0xc9, 0x08, 0xd6,
    0x58, 0x22, 0x17, 0xf5, 0x88, 0x45, 0x20, 0x7b, 0x61, 0x02, 0x3f, 0x3b,
    0x4a, 0xe3, 0x79, 0x85, 0x24, 0x50, 0x5d, 0xaf, 0x60, 0xfd, 0x61, 0xb6,
    0x5e, 0xc4, 0x4c, 0x7f, 0x77, 0x99, 0xd9, 0x47, 0x37, 0xf9, 0xfc, 0xc7,
    0xab, 0x00, 0xe4, 0x0f, 0x4f, 0x10, 0x44, 0x0a, 0x40, 0xe8, 0x14, 0x10,
    0x22, 0x42, 0x46, 0x4f, 0x18, 0x0e, 0x9e, 0x3c, 0xd8, 0xf5, 0x8d, 0xcf,
    0xbe, 0xf1, 0xfc, 0x78, 0x57, 0x04, 0x26, 0xcf, 0x4c, 0xb2, 0x15, 0xd5,
    0x48, 0x7b, 0x50, 0xdb, 0x28, 0x91, 0xcb, 0xf9, 0xdc, 0x5b, 0xf8, 0x9a,
    0x0f, 0x3e, 0x1c, 0x25, 0x08, 0x4b, 0xd0, 0x81, 0xe9, 0x8f, 0xbe, 0x05,
    0xa0, 0xb2, 0x5a, 0x42, 0x04, 0xb4, 0x03, 0xbe, 0x11, 0x00, 0xfc, 0x14,
    0x64, 0x8f, 0xf8, 0x08, 0xd2, 0xd3, 0x18, 0xfa, 0xf5, 0x9a, 0x02, 0xd7,
    0x51, 0x2a, 0xeb, 0x25, 0xe8, 0x84, 0x04, 0x71, 0x0d, 0x33, 0x02, 0x92,
    0x53, 0x14, 0x98, 0xbc, 0x30, 0xc5, 0xc4, 0xd8, 0x65, 0xb6, 0x5e, 0xc4,
    0xdc, 0x7f, 0x34, 0x0b, 0xe9, 0xdd, 0xc4, 0x8d, 0x4d, 0x65, 0xec, 0x44,
    0x1a, 0x45, 0x7b, 0x1a, 0x43, 0xaf, 0xf8, 0xad, 0xf1, 0xa9, 0x6d, 0x54,
    0x10, 0x20, 0x88, 0x42, 0x8c, 0x07, 0xda, 0x89, 0x30, 0x1d, 0xc5, 0xdf,
    0x9f, 0xe1, 0xd6, 0x57, 0xf7, 0x01, 0x98, 0xfd, 0xe1, 0x2a, 0x6e, 0xab,
    0x45, 0x76, 0x48, 0xc0, 0xd3, 0x1d, 0x8d, 0xed, 0xfe, 0x2c, 0x18, 0x83,
    0x78, 0xd2, 0xd3, 0x18, 0x7a, 0x1d, 0x55, 0x5c, 0x2d, 0x40, 0x27, 0xa4,
    0xfa, 0xbc, 0x84, 0xd3, 0x16, 0x81, 0x0b, 0x00, 0xa8, 0x07, 0xca, 0xed,
    0xcf, 0xee, 0x02, 0x50, 0x7a, 0xfc, 0x90, 0xb9, 0xea, 0x12, 0xe6, 0x5d,
    0x68, 0xa9, 0x82, 0x27, 0x84, 0xed, 0x5e, 0x9b, 0xb7, 0x3a, 0x2d, 0xd2,
    0xf4, 0x65, 0x31, 0x7e, 0x3f, 0xb0, 0x82, 0xc6, 0x35, 0xea, 0xcf, 0x03,
    0xcc, 0x3b, 0x49, 0xb6, 0x74, 0x0b, 0x3f, 0xa5, 0x28, 0x8a, 0x0f, 0xa4,
    0xfb, 0x33, 0xe2, 0xfe, 0xc2, 0x2c, 0x39, 0xdb, 0xcb, 0x70, 0x38, 0x23,
    0x88, 0x07, 0xd9, 0x81, 0x1e, 0x71, 0x76, 0x48, 0xa8, 0xd5, 0x1d, 0xe2,
    0xf5, 0x35, 0x2e, 0x57, 0xca, 0x09, 0x6d, 0x43, 0xe9, 0x69, 0xd0, 0x23,
    0xdd, 0xac, 0x01, 0x4a, 0xe8, 0x14, 0xf1, 0x60, 0xcb, 0x87, 0xe2, 0xd2,
    0x1c, 0x77, 0xbe, 0x9f, 0x26, 0x6a, 0x45, 0x44, 0x1d, 0x48, 0x8a, 0xd0,
    0x6a, 0x03, 0x22, 0x84, 0x0a, 0xd6, 0x4b, 0xa2, 0x1d, 0x43, 0xb0, 0x1a,
    0xbf, 0xd4, 0xd8, 0x1a, 0x8b, 0x3a, 0x10, 0xe7, 0x88, 0x5d, 0x8c, 0x4d,
    0x81, 0xa2, 0x64, 0x07, 0x04, 0x01, 0x8e, 0x1e, 0x31, 0xcc, 0x3f, 0x9b,
    0x23, 0x58, 0x9b, 0x43, 0xa5, 0x85, 0x1d, 0xea, 0x6b, 0x9a, 0x31, 0x88,
    0x08, 0x36, 0x9d, 0xc4, 0xa5, 0x85, 0xdc, 0x40, 0x9e, 0x60, 0xb9, 0xb5,
    0xa3, 0xb1, 0x17, 0xba, 0x10, 0x6d, 0x43, 0xa9, 0xaa, 0xe4, 0x87, 0x1c,
    0x81, 0x07, 0xa6, 0xaf, 0x9d, 0x88, 0x10, 0xac, 0x29, 0xf9, 0x91, 0x29,
    0x44, 0x0c, 0x79, 0x75, 0x3c, 0x5c, 0x2f, 0xe0, 0x0f, 0x1b, 0x22, 0x05,
    0x93, 0x4a, 0xe2, 0x3a, 0x70, 0x69, 0xc4, 0xa7, 0xf0, 0x73, 0x9d, 0x70,
    0x3d, 0x66, 0xbe, 0x30, 0x9f, 0xf0, 0x8d, 0xdf, 0x23, 0x6e, 0x56, 0x9a,
    0x09, 0xdd, 0x80, 0x70, 0x19, 0xac, 0xf4, 0x89, 0x0e, 0x08, 0x20, 0x18,
    0x15, 0xa6, 0xcf, 0x4d, 0x71, 0xeb, 0xcb, 0x7b, 0xe4, 0xce, 0x4d, 0xe1,
    0x77, 0x04, 0xf1, 0x84, 0xec, 0x40, 0x1a, 0x3c, 0x38, 0x77, 0x78, 0x8c,
    0xda, 0x1f, 0x86, 0xe2, 0x2f, 0x0d, 0x00, 0xac, 0xb1, 0x2f, 0x67, 0x05,
    0x06, 0x16, 0x8b, 0xe5, 0x44, 0xb8, 0x02, 0x95, 0x3f, 0x15, 0x3c, 0x88,
    0xe2, 0x57, 0xea, 0x34, 0x65, 0xfb, 0x4d, 0x60, 0xfb, 0x99, 0xf4, 0x49,
    0xdf, 0xb3, 0x04, 0x55, 0xa5, 0xf0, 0x53, 0x9d, 0xf8, 0x5f, 0xa5, 0x56,
    0xaa, 0x25, 0xb6, 0xe3, 0xbd, 0x36, 0x8f, 0x47, 0xdf, 0x3f, 0xd8, 0xcd,
    0x9e, 0x16, 0xae, 0x4f, 0xe5, 0x88, 0xfe, 0x0b, 0xd1, 0x96, 0x52, 0x59,
    0x51, 0xd2, 0x9b, 0x10, 0x1f, 0x80, 0x89, 0xe3, 0x06, 0x63, 0x7d, 0xb2,
    0x03, 0x79, 0x8a, 0xbf, 0x05, 0x2c, 0x2d, 0x34, 0x76, 0x82, 0xbe, 0x75,
    0x1e, 0xef, 0xcc, 0xe5, 0x8b, 0xe7, 0xbb, 0x26, 0x03, 0x47, 0x73, 0x19,
    0x86, 0x0f, 0xa7, 0xb1, 0xc3, 0x86, 0xe4, 0x81, 0x24, 0x19, 0x84, 0xea,
    0x3f, 0x31, 0xd1, 0xba, 0x12, 0xd4, 0x23, 0xa2, 0x8d, 0x5e, 0x56, 0xdb,
    0xa4, 0x6f, 0x9c, 0xc7, 0x6f, 0xda, 0x61, 0xa3, 0x27, 0x47, 0x5f, 0xee,
    0x3b, 0xaf, 0x67, 0xc4, 0x13, 0x14, 0x45, 0x3c, 0x61, 0xb1, 0xb0, 0xf8,
    0xda, 0xe6, 0xd8, 0xf6, 0xbd, 0xbd, 0x37, 0xbd, 0x6a, 0x1b, 0x7f, 0x35,
    0x5e, 0x23, 0x79, 0xd5, 0xfa, 0xc6, 0x7f, 0xe3, 0xb9, 0x35, 0x96, 0xff,
    0x01, 0xa2, 0x87, 0x5f, 0xdd, 0xf4, 0xd7, 0x03, 0x0b, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};


/*
 *  Constructs a minHelpDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
minHelpDialog::minHelpDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    QImage img;
    img.loadFromData( image0_data, sizeof( image0_data ), "PNG" );
    image0 = img;
    if ( !name )
	setName( "minHelpDialog" );
    setMinimumSize( QSize( 450, 525 ) );
    setMaximumSize( QSize( 450, 525 ) );
    setIcon( image0 );
    setSizeGripEnabled( TRUE );

    QWidget* privateLayoutWidget = new QWidget( this, "Layout1" );
    privateLayoutWidget->setGeometry( QRect( 10, 460, 430, 40 ) );
    Layout1 = new QHBoxLayout( privateLayoutWidget, 0, 6, "Layout1"); 

    buttonOk = new QPushButton( privateLayoutWidget, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    textEdit1 = new QTextEdit( this, "textEdit1" );
    textEdit1->setGeometry( QRect( 10, 10, 430, 440 ) );
    textEdit1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, textEdit1->sizePolicy().hasHeightForWidth() ) );
    textEdit1->setHScrollBarMode( QTextEdit::AlwaysOff );
    textEdit1->setTextFormat( QTextEdit::RichText );
    textEdit1->setWordWrap( QTextEdit::WidgetWidth );
    languageChange();
    resize( QSize(450, 525).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
minHelpDialog::~minHelpDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void minHelpDialog::languageChange()
{
    setCaption( tr( "Minimization Help" ) );
    buttonOk->setText( tr( "&Done" ) );
    buttonOk->setAccel( QKeySequence( tr( "Alt+D" ) ) );
    textEdit1->setText( tr( "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\"font-size:10pt;font-family:Sans\">\n"
"<p><span style=\"font-weight:600\">Molecular Mechanics</span> <br />Dyamol currently supports two complementary Amber force fields (FF): ff2003 and gaff. The Amber 2003 force field (ff2003) is used for proteins and has been parameterized from quantum calculations in a continuum dielectric to help mimic solvent polarization. ff2003 is essentially a modified Amber 99 force field. The general amber force field (gaff) is a small organic molecule force field that is parameterized to be compatible with the newer Amber force fields. Ideally charges for gaff should be obtained from the HF/6-31G* RESP method. However the AM1-BCC charges, which were designed to mimic the HF/6-31G* RESP charges, can also be used. <br /><br />When running an energy calculation Dynamol will default to gaff for small molecules and ff2003 for proteins. Dynamol will also default to the AM1-BCC charges when using the gaff. In addition Dynamol will try to obtain AM1-BCC charges for non-standard amino acid residues when using ff2003. It is possible to use gaff on proteins all though this method is not recommended. In addition three semi empirical based charge methods are currently possible when using gaff: MNDO, AM1, and PM3. These charges (as well as AM1-BCC) are limited to molecules with under 200 atoms. <br />\n"
"<br>\n"
"Two types of electrostatic treatment are supported with the force fields. Constant dielectric and distance dependant dielectric. The distant dependant dielectric function is a simple 1/r2 as opposed to 1/r for the Coulomb potential. <br />\n"
"<br>\n"
"There are four criteria which can be used to determine minimization convergence. Any of these methods can be disabled by setting the value to zero. At a bare minimum it is recommended that you at least monitor the RMSE of the Atomic Forces. \n"
"\n"
"<br><br>\n"
"<b>Semi Empirical</b>\n"
"<br>\n"
"Dynamol currently supports very simple semi empirical minimizations using three different Hamiltonians.  All of these methods are performed with the mopac 7 program which was installed with Dynamol.  In the future we may support more of the mopac 7 functionality.  In the mean time if you wish to make better usage of the mopac 7 program you can consult the user manual which can be found in the $DYNAMOL/Documentation/MOPAC directory and use the mopac and MOPAC7 programs directly which can be found in the $DYNAMOL/bin directory.\n"
"</p>\n"
"</body></html>\n"
"" ) );
}

