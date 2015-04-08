/****************************************************************************
** Form implementation generated from reading ui file 'fpDialog.ui'
**
** Created: Wed Aug 17 12:31:40 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "fpDialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qframe.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "fpDialog.ui.h"
static const unsigned char image0_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x04,
    0x95, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0xa5, 0xd5, 0x5b, 0x6c, 0x14,
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
    0xd7, 0xb6, 0x8c, 0xaa, 0x86, 0x92, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
    0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};


/*
 *  Constructs a fpDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
fpDialog::fpDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    QImage img;
    img.loadFromData( image0_data, sizeof( image0_data ), "PNG" );
    image0 = img;
    if ( !name )
	setName( "fpDialog" );
    setSizeGripEnabled( TRUE );
    fpDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "fpDialogLayout"); 

    layout213 = new QVBoxLayout( 0, 0, 6, "layout213"); 

    tabWidget2 = new QTabWidget( this, "tabWidget2" );

    tab = new QWidget( tabWidget2, "tab" );
    tabLayout = new QGridLayout( tab, 1, 1, 11, 6, "tabLayout"); 

    layout158 = new QVBoxLayout( 0, 0, 6, "layout158"); 

    layout157 = new QVBoxLayout( 0, 0, 6, "layout157"); 

    textLabel5 = new QLabel( tab, "textLabel5" );
    textLabel5->setTextFormat( QLabel::RichText );
    textLabel5->setAlignment( int( QLabel::WordBreak | QLabel::AlignVCenter ) );
    layout157->addWidget( textLabel5 );

    layout156 = new QVBoxLayout( 0, 0, 6, "layout156"); 

    layout155 = new QVBoxLayout( 0, 0, 6, "layout155"); 

    layout154 = new QVBoxLayout( 0, 0, 6, "layout154"); 

    line4 = new QFrame( tab, "line4" );
    line4->setFrameShape( QFrame::HLine );
    line4->setFrameShadow( QFrame::Sunken );
    line4->setFrameShape( QFrame::HLine );
    layout154->addWidget( line4 );
    layout155->addLayout( layout154 );

    layout15 = new QHBoxLayout( 0, 0, 6, "layout15"); 

    sdLoadSelect = new QPushButton( tab, "sdLoadSelect" );
    sdLoadSelect->setMaximumSize( QSize( 32, 32767 ) );
    layout15->addWidget( sdLoadSelect );

    textLabel1 = new QLabel( tab, "textLabel1" );
    layout15->addWidget( textLabel1 );

    sdLoadFile = new QLineEdit( tab, "sdLoadFile" );
    layout15->addWidget( sdLoadFile );
    layout155->addLayout( layout15 );
    layout156->addLayout( layout155 );

    layout16 = new QHBoxLayout( 0, 0, 6, "layout16"); 

    fpSaveSelect = new QPushButton( tab, "fpSaveSelect" );
    fpSaveSelect->setMaximumSize( QSize( 32, 32767 ) );
    layout16->addWidget( fpSaveSelect );

    textLabel1_3 = new QLabel( tab, "textLabel1_3" );
    layout16->addWidget( textLabel1_3 );

    fpSaveFile = new QLineEdit( tab, "fpSaveFile" );
    layout16->addWidget( fpSaveFile );
    layout156->addLayout( layout16 );
    layout157->addLayout( layout156 );
    layout158->addLayout( layout157 );

    layout152 = new QVBoxLayout( 0, 0, 6, "layout152"); 

    layout140 = new QVBoxLayout( 0, 0, 6, "layout140"); 

    line3 = new QFrame( tab, "line3" );
    line3->setFrameShape( QFrame::HLine );
    line3->setFrameShadow( QFrame::Sunken );
    line3->setFrameShape( QFrame::HLine );
    layout140->addWidget( line3 );

    layout139 = new QHBoxLayout( 0, 0, 6, "layout139"); 
    spacer22 = new QSpacerItem( 71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout139->addItem( spacer22 );

    Build = new QPushButton( tab, "Build" );
    Build->setPaletteForegroundColor( QColor( 0, 85, 0 ) );
    layout139->addWidget( Build );
    spacer21 = new QSpacerItem( 81, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout139->addItem( spacer21 );
    layout140->addLayout( layout139 );
    layout152->addLayout( layout140 );
    spacer24 = new QSpacerItem( 20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout152->addItem( spacer24 );
    layout158->addLayout( layout152 );

    tabLayout->addLayout( layout158, 0, 0 );
    tabWidget2->insertTab( tab, QString("") );

    tab_2 = new QWidget( tabWidget2, "tab_2" );
    tabLayout_2 = new QGridLayout( tab_2, 1, 1, 11, 6, "tabLayout_2"); 

    layout170 = new QVBoxLayout( 0, 0, 6, "layout170"); 

    layout167 = new QVBoxLayout( 0, 0, 6, "layout167"); 

    layout166 = new QVBoxLayout( 0, 0, 6, "layout166"); 

    layout165 = new QVBoxLayout( 0, 0, 6, "layout165"); 

    layout114 = new QVBoxLayout( 0, 0, 6, "layout114"); 

    textLabel3 = new QLabel( tab_2, "textLabel3" );
    textLabel3->setTextFormat( QLabel::RichText );
    layout114->addWidget( textLabel3 );

    line10 = new QFrame( tab_2, "line10" );
    line10->setFrameShape( QFrame::HLine );
    line10->setFrameShadow( QFrame::Sunken );
    line10->setFrameShape( QFrame::HLine );
    layout114->addWidget( line10 );
    layout165->addLayout( layout114 );

    layout23 = new QVBoxLayout( 0, 0, 6, "layout23"); 

    layout18 = new QVBoxLayout( 0, 0, 6, "layout18"); 

    layout4_2 = new QHBoxLayout( 0, 0, 6, "layout4_2"); 

    textLabel1_2 = new QLabel( tab_2, "textLabel1_2" );
    layout4_2->addWidget( textLabel1_2 );

    fpTrainFile1 = new QLineEdit( tab_2, "fpTrainFile1" );
    layout4_2->addWidget( fpTrainFile1 );

    fpLoadSelect1 = new QPushButton( tab_2, "fpLoadSelect1" );
    fpLoadSelect1->setMaximumSize( QSize( 32, 32767 ) );
    layout4_2->addWidget( fpLoadSelect1 );
    layout18->addLayout( layout4_2 );

    layout4_2_3 = new QHBoxLayout( 0, 0, 6, "layout4_2_3"); 

    textLabel1_2_4 = new QLabel( tab_2, "textLabel1_2_4" );
    layout4_2_3->addWidget( textLabel1_2_4 );

    fpTestFile1 = new QLineEdit( tab_2, "fpTestFile1" );
    layout4_2_3->addWidget( fpTestFile1 );

    fpLoadSelect1_3 = new QPushButton( tab_2, "fpLoadSelect1_3" );
    fpLoadSelect1_3->setMaximumSize( QSize( 32, 32767 ) );
    layout4_2_3->addWidget( fpLoadSelect1_3 );
    layout18->addLayout( layout4_2_3 );
    layout23->addLayout( layout18 );

    line7 = new QFrame( tab_2, "line7" );
    line7->setFrameShape( QFrame::HLine );
    line7->setFrameShadow( QFrame::Sunken );
    line7->setFrameShape( QFrame::HLine );
    layout23->addWidget( line7 );
    layout165->addLayout( layout23 );
    layout166->addLayout( layout165 );

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 

    textLabel2 = new QLabel( tab_2, "textLabel2" );
    layout8->addWidget( textLabel2 );

    minProbEdit = new QLineEdit( tab_2, "minProbEdit" );
    layout8->addWidget( minProbEdit );
    layout166->addLayout( layout8 );

    layout8_2 = new QHBoxLayout( 0, 0, 6, "layout8_2"); 

    textLabel2_2 = new QLabel( tab_2, "textLabel2_2" );
    layout8_2->addWidget( textLabel2_2 );

    descNumEdit = new QLineEdit( tab_2, "descNumEdit" );
    layout8_2->addWidget( descNumEdit );
    layout166->addLayout( layout8_2 );
    layout167->addLayout( layout166 );

    layout130 = new QVBoxLayout( 0, 0, 6, "layout130"); 

    line9 = new QFrame( tab_2, "line9" );
    line9->setFrameShape( QFrame::HLine );
    line9->setFrameShadow( QFrame::Sunken );
    line9->setFrameShape( QFrame::HLine );
    layout130->addWidget( line9 );

    layout129 = new QHBoxLayout( 0, 0, 6, "layout129"); 
    spacer19 = new QSpacerItem( 161, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout129->addItem( spacer19 );

    testModel = new QPushButton( tab_2, "testModel" );
    testModel->setPaletteForegroundColor( QColor( 0, 85, 0 ) );
    layout129->addWidget( testModel );
    spacer18 = new QSpacerItem( 110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout129->addItem( spacer18 );
    layout130->addLayout( layout129 );
    layout167->addLayout( layout130 );
    layout170->addLayout( layout167 );

    layout169 = new QVBoxLayout( 0, 0, 6, "layout169"); 

    line1 = new QFrame( tab_2, "line1" );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );
    layout169->addWidget( line1 );

    layout45 = new QVBoxLayout( 0, 0, 6, "layout45"); 

    layout31 = new QVBoxLayout( 0, 0, 6, "layout31"); 

    layout29 = new QHBoxLayout( 0, 0, 6, "layout29"); 

    textLabel4 = new QLabel( tab_2, "textLabel4" );
    textLabel4->setMinimumSize( QSize( 280, 0 ) );
    layout29->addWidget( textLabel4 );

    hitRate = new QLineEdit( tab_2, "hitRate" );
    hitRate->setMinimumSize( QSize( 50, 0 ) );
    layout29->addWidget( hitRate );
    layout31->addLayout( layout29 );

    layout29_2 = new QHBoxLayout( 0, 0, 6, "layout29_2"); 

    textLabel4_3 = new QLabel( tab_2, "textLabel4_3" );
    textLabel4_3->setMinimumSize( QSize( 280, 0 ) );
    layout29_2->addWidget( textLabel4_3 );

    hitRate_3 = new QLineEdit( tab_2, "hitRate_3" );
    layout29_2->addWidget( hitRate_3 );
    layout31->addLayout( layout29_2 );
    layout45->addLayout( layout31 );

    layout29_2_2 = new QHBoxLayout( 0, 0, 6, "layout29_2_2"); 

    textLabel4_3_2 = new QLabel( tab_2, "textLabel4_3_2" );
    textLabel4_3_2->setMinimumSize( QSize( 280, 0 ) );
    layout29_2_2->addWidget( textLabel4_3_2 );

    hitRate_3_2 = new QLineEdit( tab_2, "hitRate_3_2" );
    layout29_2_2->addWidget( hitRate_3_2 );
    layout45->addLayout( layout29_2_2 );
    layout169->addLayout( layout45 );
    layout170->addLayout( layout169 );

    tabLayout_2->addLayout( layout170, 0, 0 );
    spacer27 = new QSpacerItem( 20, 71, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout_2->addItem( spacer27, 1, 0 );
    tabWidget2->insertTab( tab_2, QString("") );

    TabPage = new QWidget( tabWidget2, "TabPage" );
    TabPageLayout = new QGridLayout( TabPage, 1, 1, 11, 6, "TabPageLayout"); 

    layout204 = new QVBoxLayout( 0, 0, 6, "layout204"); 

    line5_3 = new QFrame( TabPage, "line5_3" );
    line5_3->setFrameShape( QFrame::HLine );
    line5_3->setFrameShadow( QFrame::Sunken );
    line5_3->setFrameShape( QFrame::HLine );
    layout204->addWidget( line5_3 );

    layout96 = new QHBoxLayout( 0, 0, 6, "layout96"); 

    layout95 = new QVBoxLayout( 0, 0, 6, "layout95"); 

    textLabel4_2 = new QLabel( TabPage, "textLabel4_2" );
    textLabel4_2->setMinimumSize( QSize( 275, 0 ) );
    textLabel4_2->setTextFormat( QLabel::AutoText );
    layout95->addWidget( textLabel4_2 );

    textLabel4_2_2 = new QLabel( TabPage, "textLabel4_2_2" );
    textLabel4_2_2->setMinimumSize( QSize( 275, 0 ) );
    textLabel4_2_2->setTextFormat( QLabel::AutoText );
    layout95->addWidget( textLabel4_2_2 );

    textLabel4_2_4 = new QLabel( TabPage, "textLabel4_2_4" );
    textLabel4_2_4->setMinimumSize( QSize( 275, 0 ) );
    textLabel4_2_4->setTextFormat( QLabel::RichText );
    layout95->addWidget( textLabel4_2_4 );
    layout96->addLayout( layout95 );

    layout76 = new QVBoxLayout( 0, 0, 6, "layout76"); 

    hitRate_2 = new QLineEdit( TabPage, "hitRate_2" );
    hitRate_2->setMaximumSize( QSize( 30000, 32767 ) );
    layout76->addWidget( hitRate_2 );

    hitRate_2_2 = new QLineEdit( TabPage, "hitRate_2_2" );
    hitRate_2_2->setMaximumSize( QSize( 32767, 32767 ) );
    layout76->addWidget( hitRate_2_2 );

    hitRate_2_3 = new QLineEdit( TabPage, "hitRate_2_3" );
    hitRate_2_3->setMaximumSize( QSize( 32767, 32767 ) );
    layout76->addWidget( hitRate_2_3 );
    layout96->addLayout( layout76 );
    layout204->addLayout( layout96 );

    TabPageLayout->addLayout( layout204, 2, 0 );

    layout201 = new QVBoxLayout( 0, 0, 6, "layout201"); 

    line5 = new QFrame( TabPage, "line5" );
    line5->setFrameShape( QFrame::HLine );
    line5->setFrameShadow( QFrame::Sunken );
    line5->setFrameShape( QFrame::HLine );
    layout201->addWidget( line5 );

    layout200 = new QHBoxLayout( 0, 0, 6, "layout200"); 

    layout199 = new QHBoxLayout( 0, 0, 6, "layout199"); 

    testModel_2 = new QPushButton( TabPage, "testModel_2" );
    testModel_2->setPaletteForegroundColor( QColor( 0, 85, 0 ) );
    layout199->addWidget( testModel_2 );

    layout196 = new QHBoxLayout( 0, 0, 6, "layout196"); 

    textLabel1_4 = new QLabel( TabPage, "textLabel1_4" );
    textLabel1_4->setMinimumSize( QSize( 145, 0 ) );
    layout196->addWidget( textLabel1_4 );

    numResults = new QLineEdit( TabPage, "numResults" );
    numResults->setMaximumSize( QSize( 50, 32767 ) );
    layout196->addWidget( numResults );
    layout199->addLayout( layout196 );
    layout200->addLayout( layout199 );
    spacer20 = new QSpacerItem( 70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout200->addItem( spacer20 );
    layout201->addLayout( layout200 );

    TabPageLayout->addLayout( layout201, 1, 0 );

    layout209 = new QVBoxLayout( 0, 0, 6, "layout209"); 

    layout190 = new QVBoxLayout( 0, 0, 6, "layout190"); 

    layout184 = new QHBoxLayout( 0, 0, 6, "layout184"); 

    textLabel1_2_2 = new QLabel( TabPage, "textLabel1_2_2" );
    layout184->addWidget( textLabel1_2_2 );

    fpActive = new QLineEdit( TabPage, "fpActive" );
    layout184->addWidget( fpActive );

    fpLoadSelect2 = new QPushButton( TabPage, "fpLoadSelect2" );
    fpLoadSelect2->setMaximumSize( QSize( 32, 32767 ) );
    layout184->addWidget( fpLoadSelect2 );
    layout190->addLayout( layout184 );

    layout183 = new QHBoxLayout( 0, 0, 6, "layout183"); 

    textLabel1_2_2_2 = new QLabel( TabPage, "textLabel1_2_2_2" );
    layout183->addWidget( textLabel1_2_2_2 );

    testFile2 = new QLineEdit( TabPage, "testFile2" );
    layout183->addWidget( testFile2 );

    fpLoadSelect2_2 = new QPushButton( TabPage, "fpLoadSelect2_2" );
    fpLoadSelect2_2->setMaximumSize( QSize( 32, 32767 ) );
    layout183->addWidget( fpLoadSelect2_2 );
    layout190->addLayout( layout183 );

    line5_2 = new QFrame( TabPage, "line5_2" );
    line5_2->setFrameShape( QFrame::HLine );
    line5_2->setFrameShadow( QFrame::Sunken );
    line5_2->setFrameShape( QFrame::HLine );
    layout190->addWidget( line5_2 );
    layout209->addLayout( layout190 );

    layout208 = new QVBoxLayout( 0, 0, 6, "layout208"); 

    layout207 = new QVBoxLayout( 0, 0, 6, "layout207"); 

    buttonGroup1 = new QButtonGroup( TabPage, "buttonGroup1" );
    buttonGroup1->setMinimumSize( QSize( 0, 80 ) );

    radioLocal = new QRadioButton( buttonGroup1, "radioLocal" );
    radioLocal->setGeometry( QRect( 11, 22, 180, 21 ) );
    radioLocal->setChecked( TRUE );

    radioZinc = new QRadioButton( buttonGroup1, "radioZinc" );
    radioZinc->setEnabled( TRUE );
    radioZinc->setGeometry( QRect( 11, 49, 330, 21 ) );
    radioZinc->setChecked( FALSE );
    layout207->addWidget( buttonGroup1 );

    line12 = new QFrame( TabPage, "line12" );
    line12->setFrameShape( QFrame::HLine );
    line12->setFrameShadow( QFrame::Sunken );
    line12->setFrameShape( QFrame::HLine );
    layout207->addWidget( line12 );
    layout208->addLayout( layout207 );

    layout23_2 = new QHBoxLayout( 0, 0, 6, "layout23_2"); 

    fpLoadLocal = new QPushButton( TabPage, "fpLoadLocal" );
    fpLoadLocal->setEnabled( TRUE );
    fpLoadLocal->setMaximumSize( QSize( 32, 32767 ) );
    layout23_2->addWidget( fpLoadLocal );

    textLabel6 = new QLabel( TabPage, "textLabel6" );
    textLabel6->setEnabled( TRUE );
    layout23_2->addWidget( textLabel6 );

    localFile = new QLineEdit( TabPage, "localFile" );
    localFile->setEnabled( TRUE );
    layout23_2->addWidget( localFile );
    layout208->addLayout( layout23_2 );
    layout209->addLayout( layout208 );

    TabPageLayout->addLayout( layout209, 0, 0 );
    tabWidget2->insertTab( TabPage, QString("") );
    layout213->addWidget( tabWidget2 );

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonHelp = new QPushButton( this, "buttonHelp" );
    buttonHelp->setAutoDefault( TRUE );
    buttonHelp->setIconSet( QIconSet( image0 ) );
    Layout1->addWidget( buttonHelp );
    Horizontal_Spacing2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );
    layout213->addLayout( Layout1 );

    fpDialogLayout->addLayout( layout213, 0, 0 );
    languageChange();
    resize( QSize(442, 486).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( sdLoadSelect, SIGNAL( clicked() ), this, SLOT( sdLoadSelectSlot() ) );
    connect( fpSaveSelect, SIGNAL( clicked() ), this, SLOT( fpSaveSelectSlot() ) );
    connect( fpLoadSelect1, SIGNAL( clicked() ), this, SLOT( fpLoadSelectSlot() ) );
    connect( fpLoadSelect2, SIGNAL( clicked() ), this, SLOT( fpLoadSelect2Slot() ) );
    connect( fpLoadLocal, SIGNAL( clicked() ), this, SLOT( fpLoadLocalSlot() ) );
    connect( Build, SIGNAL( clicked() ), this, SLOT( fpBuildSlot() ) );
    connect( fpSaveFile, SIGNAL( textChanged(const QString&) ), this, SLOT( fpSaveChangedSlot(const QString&) ) );
    connect( testModel, SIGNAL( clicked() ), this, SLOT( testModelSlot() ) );
    connect( testModel_2, SIGNAL( clicked() ), this, SLOT( seachLibrarySlot() ) );
    connect( fpLoadSelect1_3, SIGNAL( clicked() ), this, SLOT( testFile2Slot() ) );
    connect( buttonHelp, SIGNAL( clicked() ), this, SLOT( helpSlot() ) );
    connect( radioZinc, SIGNAL( toggled(bool) ), this, SLOT( zincSlot(bool) ) );
    connect( fpLoadSelect2_2, SIGNAL( clicked() ), this, SLOT( fpLoadSelect2_2Slot() ) );
    connect( radioZinc, SIGNAL( clicked() ), this, SLOT( dbClickedSlot() ) );

    // tab order
    setTabOrder( tabWidget2, fpLoadSelect2_2 );
    setTabOrder( fpLoadSelect2_2, buttonHelp );
    setTabOrder( buttonHelp, buttonOk );
    setTabOrder( buttonOk, sdLoadSelect );
    setTabOrder( sdLoadSelect, sdLoadFile );
    setTabOrder( sdLoadFile, fpSaveSelect );
    setTabOrder( fpSaveSelect, fpSaveFile );
    setTabOrder( fpSaveFile, Build );
    setTabOrder( Build, fpTrainFile1 );
    setTabOrder( fpTrainFile1, fpLoadSelect1 );
    setTabOrder( fpLoadSelect1, fpTestFile1 );
    setTabOrder( fpTestFile1, fpLoadSelect1_3 );
    setTabOrder( fpLoadSelect1_3, minProbEdit );
    setTabOrder( minProbEdit, descNumEdit );
    setTabOrder( descNumEdit, testModel );
    setTabOrder( testModel, hitRate );
    setTabOrder( hitRate, radioLocal );
    setTabOrder( radioLocal, fpLoadLocal );
    setTabOrder( fpLoadLocal, localFile );
    setTabOrder( localFile, testModel_2 );
    setTabOrder( testModel_2, hitRate_2 );
    setTabOrder( hitRate_2, testFile2 );
    setTabOrder( testFile2, fpActive );
    setTabOrder( fpActive, fpLoadSelect2 );
}

/*
 *  Destroys the object and frees any allocated resources
 */
fpDialog::~fpDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void fpDialog::languageChange()
{
    setCaption( tr( "FingerPrint Dialog" ) );
    textLabel5->setText( tr( "<b> Step 1</b> <br>\n"
"Calculate all fingerprint files here:  training set, test set, and database.\n"
"<br>\n"
"All structure files must be in 3D SDF (<font color=\"#aa0000\">*.sdf</font>) format.\n"
"<br><br>\n"
"\n"
"<b>Step 2</b> <br>\n"
"Test out model parameters on a 1000 compound diverse set.  <br>\n"
"\n"
"<br>\n"
"<b> Step 3</b> <br>\n"
"Seach for similar compounds against  database" ) );
    sdLoadSelect->setText( tr( "./" ) );
    textLabel1->setText( tr( "Load SD File (*.sdf)" ) );
    fpSaveSelect->setText( tr( "./" ) );
    textLabel1_3->setText( tr( "Save Fingerprint File (file.fp)" ) );
    fpSaveFile->setText( tr( "training.fp" ) );
    Build->setText( tr( "Build Fingerprint File" ) );
    tabWidget2->changeTab( tab, tr( "1) Build Fingerprints" ) );
    textLabel3->setText( tr( "<p align=\"center\"><p align=\"center\">Test Parameters on 1000 Compound Diverse Subset of the ZINC Database</p>" ) );
    textLabel1_2->setText( tr( "Load Fingerprint Training File" ) );
    fpTrainFile1->setText( tr( "training.fp" ) );
    fpLoadSelect1->setText( tr( "./" ) );
    textLabel1_2_4->setText( tr( "Load Fingerprint Test File" ) );
    fpTestFile1->setText( tr( "test.fp" ) );
    fpLoadSelect1_3->setText( tr( "./" ) );
    textLabel2->setText( tr( "Minimum Occurance Probability" ) );
    minProbEdit->setText( tr( "0.1" ) );
    textLabel2_2->setText( tr( "Maximum Descriptors to Select" ) );
    descNumEdit->setText( tr( "40" ) );
    testModel->setText( tr( "Test Model" ) );
    textLabel4->setText( tr( "Percent of <font color=\"#aa0000\">Training</font> Found in Top 100 Hits" ) );
    textLabel4_3->setText( tr( "Percent of <font color=\"#aa0000\">Test</font> Found in Top 100 Hits" ) );
    textLabel4_3_2->setText( tr( "Percent of <font color=\"#aa0000\">Actives</font> Found in Top 100 Hits" ) );
    tabWidget2->changeTab( tab_2, tr( "2) Test Model" ) );
    textLabel4_2->setText( tr( "Percent of <font color=\"#aa0000\">Training</font> Found in Top 100 Hits" ) );
    textLabel4_2_2->setText( tr( "Percent of <font color=\"#aa0000\">Test</font> Found in Top 100 Hits" ) );
    textLabel4_2_4->setText( tr( "Percent of <font color=\"#aa0000\">Actives</font> Found in Top 100 Hits" ) );
    testModel_2->setText( tr( "Find Similars" ) );
    textLabel1_4->setText( tr( "Return {<i>n</i>} Results" ) );
    numResults->setText( tr( "100" ) );
    textLabel1_2_2->setText( tr( "Load Active Compound Fingerprint File" ) );
    fpActive->setText( tr( "active.fp" ) );
    fpLoadSelect2->setText( tr( "./" ) );
    textLabel1_2_2_2->setText( tr( "Load Test Compound Fingerprint File" ) );
    testFile2->setText( QString::null );
    QToolTip::add( testFile2, tr( "Leave blank if you are not running a test set" ) );
    fpLoadSelect2_2->setText( tr( "./" ) );
    buttonGroup1->setTitle( tr( "Search Type" ) );
    radioLocal->setText( tr( "Local FingerPrint File" ) );
    radioZinc->setText( tr( "ZINC Commercially Available (~1.8 Million)" ) );
    fpLoadLocal->setText( tr( "./" ) );
    textLabel6->setText( tr( "Enter Local Fingerprint File (*.fp)" ) );
    localFile->setText( tr( "local.fp" ) );
    tabWidget2->changeTab( TabPage, tr( "3) Search For Hits" ) );
    buttonHelp->setText( QString::null );
    buttonHelp->setAccel( QKeySequence( QString::null ) );
    buttonOk->setText( tr( "Done" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
}

