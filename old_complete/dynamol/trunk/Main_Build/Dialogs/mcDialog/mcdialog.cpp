/****************************************************************************
** Form implementation generated from reading ui file 'mcdialog.ui'
**
** Created: Sun Apr 17 14:18:10 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "mcdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "mcdialog.ui.h"
static const unsigned char image0_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x04,
    0x95, 0x49, 0x44, 0x41, 0x54, 0x38, 0x8d, 0xa5, 0xd5, 0x5b, 0x6c, 0x14,
    0x55, 0x18, 0xc0, 0xf1, 0xff, 0x9c, 0x33, 0x3b, 0xb3, 0x6d, 0xb7, 0xdd,
    0x6e, 0x5b, 0x7a, 0x6f, 0x41, 0xa0, 0x54, 0xbc, 0x54, 0xa1, 0x8a, 0x66,
    0x42, 0x6a, 0x31, 0xd5, 0xac, 0xd5, 0x10, 0x94, 0x34, 0x6a, 0x7d, 0xb0,
    0x44, 0x88, 0x12, 0x8d, 0x98, 0x08, 0xe1, 0x01, 0x35, 0x31, 0x2a, 0xe2,
    0x83, 0x4f, 0x1a, 0xf4, 0x49, 0x7d, 0xf1, 0x41, 0x0c, 0x4d, 0x95, 0x60,
    0x6a, 0x6d, 0xac, 0x10, 0xb3, 0x6a, 0x21, 0x12, 0x40, 0x2e, 0xa5, 0x57,
    0xba, 0xa5, 0x6b, 0x2f, 0x6c, 0xf7, 0xd2, 0xee, 0xad, 0x3b, 0x33, 0x3e,
    0x14, 0xbb, 0xa9, 0x05, 0x5e, 0x3c, 0xc9, 0x24, 0x27, 0x33, 0x73, 0x7e,
    0xf3, 0xcd, 0x37, 0xdf, 0x7c, 0x47, 0xf1, 0xf9, 0x7c, 0xdc, 0x6e, 0x18,
    0x86, 0x61, 0xff, 0xf7, 0x9c, 0xcf, 0xe7, 0x53, 0x6e, 0xbb, 0x08, 0x50,
    0x6e, 0x06, 0x1b, 0x86, 0x61, 0xab, 0x3a, 0x48, 0x1d, 0xf4, 0x1c, 0xd0,
    0x72, 0xc0, 0x91, 0xbd, 0x70, 0xcd, 0x4c, 0x42, 0x2a, 0x06, 0xa9, 0x30,
    0xc4, 0x22, 0xb7, 0x7e, 0x88, 0xba, 0x0c, 0x6d, 0x30, 0x6c, 0x3d, 0x0f,
    0xd6, 0xd7, 0x97, 0xd2, 0xe4, 0x6d, 0x64, 0x43, 0xdd, 0x46, 0x4a, 0x8b,
    0xab, 0x10, 0x0a, 0x0c, 0x8c, 0xf7, 0xd2, 0x37, 0x7c, 0x86, 0x01, 0x7f,
    0x3f, 0x81, 0x91, 0x19, 0xc6, 0x2f, 0xa5, 0x68, 0x7a, 0xdc, 0xb0, 0xbb,
    0xbb, 0x96, 0xe3, 0x4b, 0xe0, 0x86, 0x06, 0xc3, 0x76, 0x15, 0x40, 0xdb,
    0x2b, 0xdb, 0x78, 0x7e, 0xfb, 0x4e, 0xaa, 0x4a, 0xd7, 0x11, 0x8c, 0x06,
    0xf0, 0x5f, 0xbb, 0xc2, 0xc5, 0x2b, 0x67, 0x89, 0x31, 0x85, 0xea, 0x94,
    0x54, 0x54, 0x16, 0xe0, 0x2a, 0x30, 0x29, 0x59, 0x3b, 0x8b, 0xff, 0xdc,
    0x3c, 0xcd, 0xcf, 0x34, 0xd8, 0x3f, 0xb4, 0x9f, 0x54, 0x6e, 0x0a, 0x1b,
    0x37, 0xd0, 0x37, 0xdf, 0xde, 0xc5, 0xeb, 0x2f, 0xbe, 0x4f, 0x3c, 0x11,
    0x66, 0x70, 0xe4, 0x12, 0x9d, 0x5d, 0x9d, 0xf4, 0xf7, 0x0d, 0x50, 0x5e,
    0x5e, 0xc2, 0xf0, 0xb5, 0x21, 0x66, 0xe2, 0x63, 0xb8, 0xcb, 0x4c, 0xdc,
    0xe5, 0x16, 0x2e, 0xb7, 0xe0, 0xce, 0xcd, 0x92, 0xbc, 0x42, 0x89, 0x77,
    0xeb, 0x16, 0xbb, 0xf3, 0xfb, 0x1e, 0x65, 0x09, 0x6c, 0x18, 0x0b, 0xaf,
    0xbf, 0x63, 0xf7, 0x36, 0xde, 0x68, 0xfb, 0x80, 0x78, 0x32, 0xc2, 0xb5,
    0xc9, 0x61, 0x7e, 0xec, 0xea, 0xe4, 0xee, 0x75, 0xf5, 0x1c, 0x3c, 0x70,
    0x78, 0x31, 0x92, 0x93, 0xbf, 0x1f, 0x67, 0xef, 0x7b, 0x6d, 0xa0, 0xa6,
    0xc8, 0x2f, 0x15, 0x68, 0xba, 0x46, 0xcd, 0x26, 0x48, 0x47, 0x04, 0x4d,
    0x4d, 0x4d, 0x76, 0x77, 0x77, 0xb7, 0x02, 0x20, 0x00, 0x54, 0x7d, 0x21,
    0xa7, 0xad, 0x2d, 0x2f, 0x93, 0x48, 0xcd, 0x12, 0x8c, 0x04, 0xf8, 0xa5,
    0xa7, 0x9b, 0xea, 0xb2, 0x1a, 0x5e, 0x68, 0x79, 0x89, 0x70, 0x34, 0xc8,
    0x47, 0x9f, 0xee, 0xe3, 0xec, 0x45, 0x1f, 0x0d, 0x0f, 0x3f, 0xc9, 0xab,
    0x6d, 0xfb, 0x09, 0x8e, 0xa5, 0x31, 0x53, 0x16, 0x02, 0x15, 0x29, 0x54,
    0x36, 0x3d, 0xe1, 0xa1, 0xa8, 0x32, 0x93, 0x59, 0x01, 0x0b, 0x5f, 0xff,
    0x31, 0xef, 0x23, 0xac, 0xae, 0xa8, 0x25, 0x34, 0x17, 0x60, 0x2a, 0x32,
    0x4a, 0x60, 0x7a, 0x14, 0x3d, 0xdb, 0x41, 0x38, 0x1a, 0x64, 0xcf, 0x5b,
    0xcf, 0x71, 0xf4, 0xa7, 0xcf, 0x39, 0x74, 0x78, 0x2f, 0x00, 0x2b, 0xab,
    0xd6, 0x90, 0x88, 0x9b, 0x98, 0x26, 0x60, 0x2d, 0x30, 0xd9, 0xf9, 0x92,
    0xf5, 0xf5, 0x85, 0x78, 0xbd, 0x5e, 0x1b, 0x40, 0x18, 0x86, 0x61, 0xeb,
    0x39, 0xb0, 0xb1, 0xee, 0x01, 0x82, 0x73, 0x13, 0x4c, 0x47, 0xfd, 0x4c,
    0x86, 0x87, 0x28, 0xa8, 0xb6, 0xe9, 0x38, 0xf1, 0x19, 0x8d, 0xdb, 0x6b,
    0xb8, 0xec, 0xff, 0x8d, 0x58, 0x3c, 0xc1, 0xae, 0xd6, 0x7d, 0x00, 0x5c,
    0xf5, 0xf7, 0x23, 0x1d, 0x26, 0xb6, 0x75, 0xc3, 0x45, 0x92, 0x30, 0x53,
    0xdc, 0xb5, 0xa1, 0x18, 0xcb, 0xb2, 0x32, 0x11, 0x6b, 0x39, 0x50, 0x5e,
    0x56, 0x4d, 0x30, 0x3c, 0xca, 0x44, 0x70, 0x80, 0x89, 0xd0, 0x30, 0x71,
    0x26, 0x29, 0x5a, 0x9d, 0x66, 0x65, 0x3d, 0xcc, 0x5b, 0x09, 0x5a, 0x9a,
    0xdb, 0x78, 0xd4, 0x78, 0x9a, 0x50, 0x78, 0x8a, 0x2f, 0x8f, 0x7c, 0x4c,
    0x4e, 0x21, 0xa4, 0xb1, 0xb0, 0x00, 0x5b, 0x11, 0x24, 0x52, 0x16, 0x77,
    0xd4, 0xe6, 0x23, 0x84, 0xc8, 0xc0, 0x7a, 0x36, 0xa0, 0x58, 0xfc, 0x1d,
    0x1a, 0x24, 0x10, 0x1a, 0x66, 0x3a, 0x3a, 0x4a, 0x34, 0x1e, 0x20, 0x6e,
    0x06, 0x99, 0x9d, 0x99, 0xa3, 0x38, 0x77, 0x15, 0x7b, 0x76, 0x1c, 0x04,
    0x60, 0xdf, 0x87, 0xcf, 0x32, 0x93, 0x9c, 0x44, 0x73, 0x81, 0x22, 0x00,
    0x21, 0x40, 0x4a, 0xb0, 0x25, 0x25, 0x95, 0x9e, 0xa5, 0xe5, 0x66, 0x01,
    0xfd, 0xe3, 0xbd, 0x24, 0xcc, 0x08, 0xd3, 0x91, 0x51, 0x22, 0xf1, 0x00,
    0x71, 0x33, 0x42, 0x9a, 0x04, 0xd7, 0x03, 0x26, 0xef, 0xec, 0xde, 0x4f,
    0xbe, 0x7b, 0x05, 0x5f, 0x7d, 0x7b, 0x88, 0x3f, 0x2e, 0xf4, 0x50, 0x58,
    0x05, 0x0e, 0x1d, 0x70, 0x08, 0x6c, 0x29, 0x40, 0x48, 0x34, 0xa7, 0x46,
    0x3c, 0x22, 0x51, 0x55, 0x35, 0x03, 0x9b, 0x49, 0xe8, 0x1b, 0xfa, 0x93,
    0xec, 0x7c, 0x8d, 0x70, 0x7c, 0x9c, 0x58, 0x32, 0x42, 0x2a, 0x1d, 0xc7,
    0x66, 0x1e, 0xac, 0x34, 0x9e, 0xbc, 0x42, 0x00, 0x3a, 0x4f, 0x7c, 0x83,
    0xcb, 0x03, 0xaa, 0x53, 0x45, 0xd1, 0x25, 0x9a, 0x43, 0x45, 0x73, 0x38,
    0x10, 0x52, 0xe0, 0xce, 0xcd, 0x62, 0x7c, 0x30, 0x9a, 0x49, 0x85, 0xcf,
    0xe7, 0x53, 0x52, 0x31, 0x18, 0x1a, 0x1d, 0x20, 0x34, 0x37, 0x4e, 0x2c,
    0x11, 0xc5, 0xb4, 0x93, 0x28, 0xc2, 0x42, 0x95, 0x92, 0xfc, 0x32, 0x95,
    0xe3, 0x3d, 0x5f, 0xf3, 0xee, 0x27, 0x3b, 0x09, 0x4c, 0x8c, 0xa3, 0xe7,
    0xa8, 0x68, 0x9a, 0xc4, 0xa1, 0xe9, 0xa8, 0x4e, 0x0d, 0xa1, 0x69, 0x48,
    0x55, 0x63, 0x45, 0x9e, 0x87, 0x81, 0xf3, 0xa1, 0x45, 0x58, 0x85, 0x85,
    0x86, 0x32, 0x3e, 0x32, 0x4d, 0x6e, 0xc9, 0x3c, 0xd2, 0x01, 0x90, 0xc6,
    0xa1, 0x0a, 0xb0, 0x04, 0xa5, 0x6b, 0x34, 0x4e, 0xf7, 0x7f, 0x47, 0x32,
    0x09, 0x4a, 0x16, 0xe4, 0xe6, 0x49, 0xa4, 0xee, 0x40, 0xd3, 0x9c, 0xe8,
    0xba, 0x13, 0x29, 0x55, 0x0a, 0xdc, 0x3a, 0x6e, 0x51, 0xc9, 0xf9, 0xd3,
    0xbd, 0x4b, 0xe1, 0x58, 0x04, 0xc6, 0x2e, 0x9a, 0x94, 0xd4, 0xce, 0xe2,
    0x2e, 0x54, 0x71, 0x48, 0x15, 0xa1, 0x08, 0xd0, 0x34, 0x26, 0x47, 0x52,
    0x3c, 0xb4, 0xb6, 0x85, 0x5c, 0x57, 0x3e, 0xe1, 0xd9, 0x10, 0xbd, 0x83,
    0xc7, 0x70, 0xad, 0xca, 0x46, 0xcf, 0x72, 0x22, 0x55, 0x8d, 0xac, 0x2c,
    0x95, 0xd5, 0x25, 0x15, 0x9c, 0x3a, 0x16, 0xc4, 0x3f, 0x18, 0xa6, 0xbd,
    0xbd, 0x3d, 0xf3, 0xe7, 0xf9, 0x7c, 0x3e, 0xe5, 0xfa, 0xd5, 0x34, 0xa3,
    0x67, 0x4c, 0xac, 0x94, 0x85, 0x22, 0x2d, 0xa4, 0x26, 0x90, 0x42, 0x25,
    0x3a, 0x01, 0xcd, 0x8d, 0xad, 0x1c, 0x78, 0xed, 0x30, 0x4f, 0x35, 0xb6,
    0x32, 0x77, 0x5d, 0x45, 0xd3, 0x9c, 0x38, 0xa4, 0x13, 0xa7, 0xa6, 0x52,
    0x5b, 0x59, 0xce, 0xf4, 0x79, 0x0f, 0x5d, 0xed, 0x17, 0x50, 0x94, 0x4c,
    0x1f, 0x12, 0xff, 0x4e, 0xba, 0x3b, 0x7d, 0xca, 0xd0, 0x29, 0x13, 0xff,
    0x05, 0x0b, 0x21, 0x61, 0xb1, 0xbb, 0x2b, 0x02, 0x50, 0x16, 0x6f, 0x57,
    0xa4, 0x8a, 0xaa, 0x3a, 0x70, 0xe7, 0x3a, 0xb8, 0x77, 0xe5, 0x2a, 0x22,
    0x97, 0x8b, 0x39, 0xf2, 0xc5, 0x29, 0x42, 0xc1, 0x24, 0x47, 0x8f, 0x1e,
    0x5d, 0x94, 0x97, 0x35, 0x7a, 0xef, 0xd6, 0x2d, 0x76, 0xdd, 0xe6, 0x1c,
    0x1e, 0x6c, 0xf6, 0xa0, 0xe5, 0x28, 0x8c, 0x5c, 0x9e, 0xc5, 0x7f, 0x25,
    0x41, 0x78, 0xda, 0xc2, 0x53, 0xac, 0x51, 0x5d, 0x93, 0xcb, 0x3d, 0xf7,
    0x97, 0xe3, 0xd1, 0x2a, 0xf8, 0xeb, 0xd7, 0x30, 0x3f, 0x1f, 0xeb, 0x5b,
    0x86, 0xde, 0x14, 0x06, 0x68, 0x6a, 0x6a, 0xb2, 0x8b, 0x2a, 0x55, 0x6a,
    0xef, 0x2b, 0x64, 0x5d, 0x9d, 0x87, 0xb2, 0x6a, 0x37, 0x9e, 0x22, 0x17,
    0xb1, 0x88, 0x60, 0x6a, 0x34, 0x8e, 0x7f, 0x20, 0x4a, 0xdf, 0xb9, 0x29,
    0xc6, 0x86, 0x23, 0x48, 0x29, 0x97, 0xa1, 0xb7, 0x84, 0x17, 0xa3, 0xf7,
    0x7a, 0x6d, 0xcb, 0xb2, 0x32, 0xb5, 0x29, 0xc4, 0x92, 0xa3, 0xa3, 0xa3,
    0xe3, 0x96, 0x7b, 0xdf, 0x6d, 0xe1, 0xff, 0x33, 0xfe, 0x01, 0xbe, 0x1e,
    0xd7, 0xb6, 0xbb, 0x8c, 0xca, 0x08, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
    0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};


/*
 *  Constructs a mcDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
mcDialog::mcDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    QImage img;
    img.loadFromData( image0_data, sizeof( image0_data ), "PNG" );
    image0 = img;
    if ( !name )
	setName( "mcDialog" );
    setSizeGripEnabled( TRUE );
    mcDialogLayout = new QVBoxLayout( this, 11, 6, "mcDialogLayout"); 

    layout24 = new QVBoxLayout( 0, 0, 6, "layout24"); 

    layout21 = new QVBoxLayout( 0, 0, 6, "layout21"); 

    layout19 = new QHBoxLayout( 0, 0, 6, "layout19"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    layout19->addWidget( textLabel1 );

    jobName = new QLineEdit( this, "jobName" );
    layout19->addWidget( jobName );
    spacer7 = new QSpacerItem( 121, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout19->addItem( spacer7 );
    layout21->addLayout( layout19 );

    layout20 = new QHBoxLayout( 0, 0, 6, "layout20"); 

    textLabel2 = new QLabel( this, "textLabel2" );
    layout20->addWidget( textLabel2 );

    outFile = new QLineEdit( this, "outFile" );
    layout20->addWidget( outFile );

    browse = new QPushButton( this, "browse" );
    layout20->addWidget( browse );
    spacer6 = new QSpacerItem( 71, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout20->addItem( spacer6 );
    layout21->addLayout( layout20 );
    layout24->addLayout( layout21 );

    layout23 = new QVBoxLayout( 0, 0, 6, "layout23"); 

    layout17 = new QHBoxLayout( 0, 0, 6, "layout17"); 

    buttonGroup1 = new QButtonGroup( this, "buttonGroup1" );
    buttonGroup1->setColumnLayout(0, Qt::Vertical );
    buttonGroup1->layout()->setSpacing( 6 );
    buttonGroup1->layout()->setMargin( 11 );
    buttonGroup1Layout = new QGridLayout( buttonGroup1->layout() );
    buttonGroup1Layout->setAlignment( Qt::AlignTop );

    force = new QRadioButton( buttonGroup1, "force" );

    buttonGroup1Layout->addWidget( force, 2, 0 );

    regular = new QRadioButton( buttonGroup1, "regular" );
    regular->setChecked( FALSE );

    buttonGroup1Layout->addWidget( regular, 1, 0 );

    torsional = new QRadioButton( buttonGroup1, "torsional" );
    torsional->setChecked( TRUE );

    buttonGroup1Layout->addWidget( torsional, 0, 0 );
    layout17->addWidget( buttonGroup1 );

    layout14 = new QVBoxLayout( 0, 0, 6, "layout14"); 

    layout10 = new QHBoxLayout( 0, 0, 6, "layout10"); 

    textLabel4 = new QLabel( this, "textLabel4" );
    layout10->addWidget( textLabel4 );
    spacer5 = new QSpacerItem( 71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout10->addItem( spacer5 );

    temp = new QLineEdit( this, "temp" );
    layout10->addWidget( temp );
    layout14->addLayout( layout10 );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 

    textLabel5 = new QLabel( this, "textLabel5" );
    layout7->addWidget( textLabel5 );

    dieMethod = new QComboBox( FALSE, this, "dieMethod" );
    layout7->addWidget( dieMethod );
    layout14->addLayout( layout7 );

    layout11 = new QHBoxLayout( 0, 0, 6, "layout11"); 

    textLabel6 = new QLabel( this, "textLabel6" );
    layout11->addWidget( textLabel6 );
    spacer4 = new QSpacerItem( 51, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout11->addItem( spacer4 );

    dieValue = new QLineEdit( this, "dieValue" );
    layout11->addWidget( dieValue );
    layout14->addLayout( layout11 );

    layout12 = new QHBoxLayout( 0, 0, 6, "layout12"); 

    textLabel4_2 = new QLabel( this, "textLabel4_2" );
    layout12->addWidget( textLabel4_2 );
    spacer3 = new QSpacerItem( 81, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout12->addItem( spacer3 );

    steps = new QLineEdit( this, "steps" );
    layout12->addWidget( steps );
    layout14->addLayout( layout12 );

    layout13 = new QHBoxLayout( 0, 0, 6, "layout13"); 

    textLabel4_3 = new QLabel( this, "textLabel4_3" );
    layout13->addWidget( textLabel4_3 );
    spacer2 = new QSpacerItem( 41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout13->addItem( spacer2 );

    output = new QSpinBox( this, "output" );
    output->setMaxValue( 10000000 );
    output->setMinValue( 1 );
    output->setValue( 100 );
    layout13->addWidget( output );
    layout14->addLayout( layout13 );
    layout17->addLayout( layout14 );
    layout23->addLayout( layout17 );

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonHelp = new QPushButton( this, "buttonHelp" );
    buttonHelp->setMinimumSize( QSize( 82, 40 ) );
    buttonHelp->setPixmap( image0 );
    buttonHelp->setAutoDefault( TRUE );
    Layout1->addWidget( buttonHelp );
    Horizontal_Spacing2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setMinimumSize( QSize( 82, 28 ) );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );
    layout23->addLayout( Layout1 );
    layout24->addLayout( layout23 );
    mcDialogLayout->addLayout( layout24 );
    languageChange();
    resize( QSize(394, 292).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( dieMethod, SIGNAL( activated(const QString&) ), this, SLOT( dieSlot(const QString&) ) );
    connect( browse, SIGNAL( clicked() ), this, SLOT( outFileSlot() ) );
    connect( buttonHelp, SIGNAL( clicked() ), this, SLOT( helpSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
mcDialog::~mcDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void mcDialog::languageChange()
{
    setCaption( tr( "Monte Carlo Setup" ) );
    textLabel1->setText( tr( "Job Name" ) );
    jobName->setText( tr( "Monte Carlo" ) );
    textLabel2->setText( tr( "Output SD File" ) );
    outFile->setText( tr( "mc.sdf" ) );
    browse->setText( tr( "Browse" ) );
    buttonGroup1->setTitle( tr( "Method" ) );
    force->setText( tr( "Force Biased" ) );
    regular->setText( tr( "Standard" ) );
    torsional->setText( tr( "Torsional" ) );
    textLabel4->setText( tr( "Temp (Kelvin)" ) );
    temp->setText( tr( "300" ) );
    textLabel5->setText( tr( "Dielectric" ) );
    dieMethod->clear();
    dieMethod->insertItem( tr( "Constant" ) );
    dieMethod->insertItem( tr( "Distant Dependant" ) );
    textLabel6->setText( tr( "Dielectric Value" ) );
    dieValue->setText( tr( "80" ) );
    textLabel4_2->setText( tr( "Max Steps" ) );
    steps->setText( tr( "10000" ) );
    textLabel4_3->setText( tr( "Output evey {n} Steps" ) );
    buttonHelp->setText( QString::null );
    buttonHelp->setAccel( QKeySequence( QString::null ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
}

