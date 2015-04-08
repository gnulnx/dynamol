/****************************************************************************
** Form implementation generated from reading ui file 'lighting.ui'
**
** Created: Sun Feb 20 18:09:35 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.2   edited Nov 24 13:47 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "lighting.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qframe.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "lighting.ui.h"
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
 *  Constructs a Lighting as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
Lighting::Lighting( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    QImage img;
    img.loadFromData( image0_data, sizeof( image0_data ), "PNG" );
    image0 = img;
    if ( !name )
	setName( "Lighting" );
    setMinimumSize( QSize( 450, 380 ) );
    setMaximumSize( QSize( 450, 380 ) );
    setSizeGripEnabled( TRUE );

    ribbons = new QTabWidget( this, "ribbons" );
    ribbons->setGeometry( QRect( 10, 10, 425, 365 ) );
    ribbons->setMinimumSize( QSize( 425, 365 ) );
    ribbons->setMaximumSize( QSize( 425, 365 ) );

    Widget8 = new QWidget( ribbons, "Widget8" );

    QWidget* privateLayoutWidget = new QWidget( Widget8, "layout7" );
    privateLayoutWidget->setGeometry( QRect( 10, 280, 400, 50 ) );
    layout7 = new QHBoxLayout( privateLayoutWidget, 11, 6, "layout7"); 

    buttonApply = new QPushButton( privateLayoutWidget, "buttonApply" );
    buttonApply->setMinimumSize( QSize( 80, 35 ) );
    buttonApply->setMaximumSize( QSize( 80, 35 ) );
    buttonApply->setAutoDefault( TRUE );
    buttonApply->setDefault( TRUE );
    layout7->addWidget( buttonApply );
    Horizontal_Spacing2 = new QSpacerItem( 130, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout7->addItem( Horizontal_Spacing2 );

    buttonOk = new QPushButton( privateLayoutWidget, "buttonOk" );
    buttonOk->setMinimumSize( QSize( 80, 35 ) );
    buttonOk->setMaximumSize( QSize( 80, 35 ) );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    layout7->addWidget( buttonOk );

    buttonCancel = new QPushButton( privateLayoutWidget, "buttonCancel" );
    buttonCancel->setMinimumSize( QSize( 80, 35 ) );
    buttonCancel->setMaximumSize( QSize( 80, 35 ) );
    buttonCancel->setAutoDefault( TRUE );
    layout7->addWidget( buttonCancel );

    genLighSpecHelp_2 = new QPushButton( privateLayoutWidget, "genLighSpecHelp_2" );
    genLighSpecHelp_2->setMinimumSize( QSize( 80, 35 ) );
    genLighSpecHelp_2->setIconSet( QIconSet( image0 ) );
    layout7->addWidget( genLighSpecHelp_2 );

    frame3 = new QFrame( Widget8, "frame3" );
    frame3->setGeometry( QRect( 10, 10, 400, 101 ) );
    frame3->setFrameShape( QFrame::StyledPanel );
    frame3->setFrameShadow( QFrame::Raised );

    genLightPosLabel = new QLabel( frame3, "genLightPosLabel" );
    genLightPosLabel->setGeometry( QRect( 20, 20, 113, 62 ) );

    QWidget* privateLayoutWidget_2 = new QWidget( frame3, "layout47" );
    privateLayoutWidget_2->setGeometry( QRect( 160, 10, 200, 80 ) );
    layout47 = new QGridLayout( privateLayoutWidget_2, 1, 1, 11, 6, "layout47"); 

    genLightPosZ = new QSpinBox( privateLayoutWidget_2, "genLightPosZ" );
    genLightPosZ->setMinimumSize( QSize( 50, 25 ) );
    genLightPosZ->setMaximumSize( QSize( 50, 25 ) );
    genLightPosZ->setPaletteBackgroundColor( QColor( 255, 255, 0 ) );

    layout47->addWidget( genLightPosZ, 1, 2 );

    genLightPosY = new QSpinBox( privateLayoutWidget_2, "genLightPosY" );
    genLightPosY->setMinimumSize( QSize( 50, 25 ) );
    genLightPosY->setMaximumSize( QSize( 50, 25 ) );
    genLightPosY->setPaletteBackgroundColor( QColor( 255, 255, 0 ) );

    layout47->addWidget( genLightPosY, 1, 1 );

    textLabel1_2_2 = new QLabel( privateLayoutWidget_2, "textLabel1_2_2" );
    textLabel1_2_2->setMinimumSize( QSize( 40, 25 ) );
    textLabel1_2_2->setMaximumSize( QSize( 40, 25 ) );

    layout47->addWidget( textLabel1_2_2, 0, 2 );

    textLabel1 = new QLabel( privateLayoutWidget_2, "textLabel1" );
    textLabel1->setMinimumSize( QSize( 40, 25 ) );
    textLabel1->setMaximumSize( QSize( 40, 25 ) );

    layout47->addWidget( textLabel1, 0, 0 );

    genLightPosX = new QSpinBox( privateLayoutWidget_2, "genLightPosX" );
    genLightPosX->setMinimumSize( QSize( 50, 25 ) );
    genLightPosX->setMaximumSize( QSize( 50, 25 ) );
    genLightPosX->setPaletteBackgroundColor( QColor( 255, 255, 0 ) );
    genLightPosX->setMaxValue( 99 );

    layout47->addWidget( genLightPosX, 1, 0 );

    textLabel1_2 = new QLabel( privateLayoutWidget_2, "textLabel1_2" );
    textLabel1_2->setMinimumSize( QSize( 40, 25 ) );
    textLabel1_2->setMaximumSize( QSize( 40, 25 ) );

    layout47->addWidget( textLabel1_2, 0, 1 );

    frame4 = new QFrame( Widget8, "frame4" );
    frame4->setGeometry( QRect( 10, 130, 400, 141 ) );
    frame4->setFrameShape( QFrame::StyledPanel );
    frame4->setFrameShadow( QFrame::Raised );

    QWidget* privateLayoutWidget_3 = new QWidget( frame4, "layout9" );
    privateLayoutWidget_3->setGeometry( QRect( 10, 20, 380, 101 ) );
    layout9 = new QVBoxLayout( privateLayoutWidget_3, 11, 6, "layout9"); 

    layout23 = new QHBoxLayout( 0, 0, 6, "layout23"); 

    genLightAmbLabel = new QLabel( privateLayoutWidget_3, "genLightAmbLabel" );
    layout23->addWidget( genLightAmbLabel );
    spacer3 = new QSpacerItem( 81, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout23->addItem( spacer3 );

    genLightAmbR = new QSpinBox( privateLayoutWidget_3, "genLightAmbR" );
    genLightAmbR->setMinimumSize( QSize( 50, 25 ) );
    genLightAmbR->setMaximumSize( QSize( 50, 25 ) );
    genLightAmbR->setPaletteBackgroundColor( QColor( 255, 0, 0 ) );
    layout23->addWidget( genLightAmbR );

    genLightAmbG = new QSpinBox( privateLayoutWidget_3, "genLightAmbG" );
    genLightAmbG->setMinimumSize( QSize( 50, 25 ) );
    genLightAmbG->setMaximumSize( QSize( 50, 25 ) );
    genLightAmbG->setPaletteBackgroundColor( QColor( 0, 170, 0 ) );
    layout23->addWidget( genLightAmbG );

    genLightAmbB = new QSpinBox( privateLayoutWidget_3, "genLightAmbB" );
    genLightAmbB->setMinimumSize( QSize( 50, 25 ) );
    genLightAmbB->setMaximumSize( QSize( 50, 25 ) );
    genLightAmbB->setPaletteBackgroundColor( QColor( 0, 0, 255 ) );
    layout23->addWidget( genLightAmbB );
    layout9->addLayout( layout23 );

    layout24 = new QHBoxLayout( 0, 0, 6, "layout24"); 

    genLightDifLabel = new QLabel( privateLayoutWidget_3, "genLightDifLabel" );
    layout24->addWidget( genLightDifLabel );
    spacer4 = new QSpacerItem( 91, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout24->addItem( spacer4 );

    genLightDifR = new QSpinBox( privateLayoutWidget_3, "genLightDifR" );
    genLightDifR->setMinimumSize( QSize( 50, 25 ) );
    genLightDifR->setMaximumSize( QSize( 50, 25 ) );
    genLightDifR->setPaletteBackgroundColor( QColor( 255, 0, 0 ) );
    layout24->addWidget( genLightDifR );

    genLightDifG = new QSpinBox( privateLayoutWidget_3, "genLightDifG" );
    genLightDifG->setMinimumSize( QSize( 50, 25 ) );
    genLightDifG->setMaximumSize( QSize( 50, 25 ) );
    genLightDifG->setPaletteBackgroundColor( QColor( 0, 170, 0 ) );
    layout24->addWidget( genLightDifG );

    genLightDifB = new QSpinBox( privateLayoutWidget_3, "genLightDifB" );
    genLightDifB->setMinimumSize( QSize( 50, 25 ) );
    genLightDifB->setMaximumSize( QSize( 50, 25 ) );
    genLightDifB->setPaletteBackgroundColor( QColor( 0, 0, 255 ) );
    layout24->addWidget( genLightDifB );
    layout9->addLayout( layout24 );

    layout25 = new QHBoxLayout( 0, 0, 6, "layout25"); 

    genLightSpecLabel = new QLabel( privateLayoutWidget_3, "genLightSpecLabel" );
    layout25->addWidget( genLightSpecLabel );
    spacer5 = new QSpacerItem( 91, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout25->addItem( spacer5 );

    genLightSpecR = new QSpinBox( privateLayoutWidget_3, "genLightSpecR" );
    genLightSpecR->setMinimumSize( QSize( 50, 25 ) );
    genLightSpecR->setMaximumSize( QSize( 50, 25 ) );
    genLightSpecR->setPaletteBackgroundColor( QColor( 255, 0, 0 ) );
    layout25->addWidget( genLightSpecR );

    genLightSpecG = new QSpinBox( privateLayoutWidget_3, "genLightSpecG" );
    genLightSpecG->setMinimumSize( QSize( 50, 25 ) );
    genLightSpecG->setMaximumSize( QSize( 50, 25 ) );
    genLightSpecG->setPaletteBackgroundColor( QColor( 0, 170, 0 ) );
    layout25->addWidget( genLightSpecG );

    genLightSpecB = new QSpinBox( privateLayoutWidget_3, "genLightSpecB" );
    genLightSpecB->setMinimumSize( QSize( 50, 25 ) );
    genLightSpecB->setMaximumSize( QSize( 50, 25 ) );
    genLightSpecB->setPaletteBackgroundColor( QColor( 85, 0, 255 ) );
    layout25->addWidget( genLightSpecB );
    layout9->addLayout( layout25 );
    ribbons->insertTab( Widget8, QString("") );

    Widget9 = new QWidget( ribbons, "Widget9" );

    QWidget* privateLayoutWidget_4 = new QWidget( Widget9, "layout7_3" );
    privateLayoutWidget_4->setGeometry( QRect( 10, 280, 400, 50 ) );
    layout7_3 = new QHBoxLayout( privateLayoutWidget_4, 11, 6, "layout7_3"); 

    buttonApply_3 = new QPushButton( privateLayoutWidget_4, "buttonApply_3" );
    buttonApply_3->setMinimumSize( QSize( 80, 35 ) );
    buttonApply_3->setMaximumSize( QSize( 80, 35 ) );
    buttonApply_3->setAutoDefault( TRUE );
    buttonApply_3->setDefault( TRUE );
    layout7_3->addWidget( buttonApply_3 );
    Horizontal_Spacing2_3 = new QSpacerItem( 130, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout7_3->addItem( Horizontal_Spacing2_3 );

    buttonOk_3 = new QPushButton( privateLayoutWidget_4, "buttonOk_3" );
    buttonOk_3->setMinimumSize( QSize( 80, 35 ) );
    buttonOk_3->setMaximumSize( QSize( 80, 35 ) );
    buttonOk_3->setAutoDefault( TRUE );
    buttonOk_3->setDefault( TRUE );
    layout7_3->addWidget( buttonOk_3 );

    buttonCancel_3 = new QPushButton( privateLayoutWidget_4, "buttonCancel_3" );
    buttonCancel_3->setMinimumSize( QSize( 80, 35 ) );
    buttonCancel_3->setMaximumSize( QSize( 80, 35 ) );
    buttonCancel_3->setAutoDefault( TRUE );
    layout7_3->addWidget( buttonCancel_3 );

    genLighSpecHelp_2_3 = new QPushButton( privateLayoutWidget_4, "genLighSpecHelp_2_3" );
    genLighSpecHelp_2_3->setMinimumSize( QSize( 80, 35 ) );
    genLighSpecHelp_2_3->setIconSet( QIconSet( image0 ) );
    layout7_3->addWidget( genLighSpecHelp_2_3 );

    frame3_3 = new QFrame( Widget9, "frame3_3" );
    frame3_3->setGeometry( QRect( 10, 10, 400, 101 ) );
    frame3_3->setFrameShape( QFrame::StyledPanel );
    frame3_3->setFrameShadow( QFrame::Raised );

    genLightPosLabel_3 = new QLabel( frame3_3, "genLightPosLabel_3" );
    genLightPosLabel_3->setGeometry( QRect( 20, 20, 113, 62 ) );

    QWidget* privateLayoutWidget_5 = new QWidget( frame3_3, "layout46" );
    privateLayoutWidget_5->setGeometry( QRect( 160, 10, 200, 80 ) );
    layout46 = new QGridLayout( privateLayoutWidget_5, 1, 1, 11, 6, "layout46"); 

    genLightPosZ_3 = new QSpinBox( privateLayoutWidget_5, "genLightPosZ_3" );
    genLightPosZ_3->setMinimumSize( QSize( 50, 25 ) );
    genLightPosZ_3->setMaximumSize( QSize( 50, 25 ) );
    genLightPosZ_3->setPaletteBackgroundColor( QColor( 255, 255, 0 ) );

    layout46->addWidget( genLightPosZ_3, 1, 2 );

    genLightPosY_3 = new QSpinBox( privateLayoutWidget_5, "genLightPosY_3" );
    genLightPosY_3->setMinimumSize( QSize( 50, 25 ) );
    genLightPosY_3->setMaximumSize( QSize( 50, 25 ) );
    genLightPosY_3->setPaletteBackgroundColor( QColor( 255, 255, 0 ) );

    layout46->addWidget( genLightPosY_3, 1, 1 );

    textLabel1_2_4 = new QLabel( privateLayoutWidget_5, "textLabel1_2_4" );
    textLabel1_2_4->setMinimumSize( QSize( 40, 25 ) );
    textLabel1_2_4->setMaximumSize( QSize( 40, 25 ) );

    layout46->addWidget( textLabel1_2_4, 0, 1 );

    textLabel1_2_2_3 = new QLabel( privateLayoutWidget_5, "textLabel1_2_2_3" );
    textLabel1_2_2_3->setMinimumSize( QSize( 40, 25 ) );
    textLabel1_2_2_3->setMaximumSize( QSize( 40, 25 ) );

    layout46->addWidget( textLabel1_2_2_3, 0, 2 );

    textLabel1_4 = new QLabel( privateLayoutWidget_5, "textLabel1_4" );
    textLabel1_4->setMinimumSize( QSize( 40, 25 ) );
    textLabel1_4->setMaximumSize( QSize( 40, 25 ) );

    layout46->addWidget( textLabel1_4, 0, 0 );

    genLightPosX_3 = new QSpinBox( privateLayoutWidget_5, "genLightPosX_3" );
    genLightPosX_3->setMinimumSize( QSize( 50, 25 ) );
    genLightPosX_3->setMaximumSize( QSize( 50, 25 ) );
    genLightPosX_3->setPaletteBackgroundColor( QColor( 255, 255, 0 ) );
    genLightPosX_3->setMaxValue( 99 );

    layout46->addWidget( genLightPosX_3, 1, 0 );

    frame4_3 = new QFrame( Widget9, "frame4_3" );
    frame4_3->setGeometry( QRect( 10, 130, 400, 141 ) );
    frame4_3->setFrameShape( QFrame::StyledPanel );
    frame4_3->setFrameShadow( QFrame::Raised );

    QWidget* privateLayoutWidget_6 = new QWidget( frame4_3, "layout9_3" );
    privateLayoutWidget_6->setGeometry( QRect( 10, 20, 380, 101 ) );
    layout9_3 = new QVBoxLayout( privateLayoutWidget_6, 11, 6, "layout9_3"); 

    layout23_3 = new QHBoxLayout( 0, 0, 6, "layout23_3"); 

    genLightAmbLabel_3 = new QLabel( privateLayoutWidget_6, "genLightAmbLabel_3" );
    layout23_3->addWidget( genLightAmbLabel_3 );
    spacer3_3 = new QSpacerItem( 81, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout23_3->addItem( spacer3_3 );

    genLightAmbR_3 = new QSpinBox( privateLayoutWidget_6, "genLightAmbR_3" );
    genLightAmbR_3->setMinimumSize( QSize( 50, 25 ) );
    genLightAmbR_3->setMaximumSize( QSize( 50, 25 ) );
    genLightAmbR_3->setPaletteBackgroundColor( QColor( 255, 0, 0 ) );
    layout23_3->addWidget( genLightAmbR_3 );

    genLightAmbG_3 = new QSpinBox( privateLayoutWidget_6, "genLightAmbG_3" );
    genLightAmbG_3->setMinimumSize( QSize( 50, 25 ) );
    genLightAmbG_3->setMaximumSize( QSize( 50, 25 ) );
    genLightAmbG_3->setPaletteBackgroundColor( QColor( 0, 170, 0 ) );
    layout23_3->addWidget( genLightAmbG_3 );

    genLightAmbB_3 = new QSpinBox( privateLayoutWidget_6, "genLightAmbB_3" );
    genLightAmbB_3->setMinimumSize( QSize( 50, 25 ) );
    genLightAmbB_3->setMaximumSize( QSize( 50, 25 ) );
    genLightAmbB_3->setPaletteBackgroundColor( QColor( 0, 0, 255 ) );
    layout23_3->addWidget( genLightAmbB_3 );
    layout9_3->addLayout( layout23_3 );

    layout24_3 = new QHBoxLayout( 0, 0, 6, "layout24_3"); 

    genLightDifLabel_3 = new QLabel( privateLayoutWidget_6, "genLightDifLabel_3" );
    layout24_3->addWidget( genLightDifLabel_3 );
    spacer4_3 = new QSpacerItem( 91, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout24_3->addItem( spacer4_3 );

    genLightDifR_3 = new QSpinBox( privateLayoutWidget_6, "genLightDifR_3" );
    genLightDifR_3->setMinimumSize( QSize( 50, 25 ) );
    genLightDifR_3->setMaximumSize( QSize( 50, 25 ) );
    genLightDifR_3->setPaletteBackgroundColor( QColor( 255, 0, 0 ) );
    layout24_3->addWidget( genLightDifR_3 );

    genLightDifG_3 = new QSpinBox( privateLayoutWidget_6, "genLightDifG_3" );
    genLightDifG_3->setMinimumSize( QSize( 50, 25 ) );
    genLightDifG_3->setMaximumSize( QSize( 50, 25 ) );
    genLightDifG_3->setPaletteBackgroundColor( QColor( 0, 170, 0 ) );
    layout24_3->addWidget( genLightDifG_3 );

    genLightDifB_3 = new QSpinBox( privateLayoutWidget_6, "genLightDifB_3" );
    genLightDifB_3->setMinimumSize( QSize( 50, 25 ) );
    genLightDifB_3->setMaximumSize( QSize( 50, 25 ) );
    genLightDifB_3->setPaletteBackgroundColor( QColor( 0, 0, 255 ) );
    layout24_3->addWidget( genLightDifB_3 );
    layout9_3->addLayout( layout24_3 );

    layout25_3 = new QHBoxLayout( 0, 0, 6, "layout25_3"); 

    genLightSpecLabel_3 = new QLabel( privateLayoutWidget_6, "genLightSpecLabel_3" );
    layout25_3->addWidget( genLightSpecLabel_3 );
    spacer5_3 = new QSpacerItem( 91, 21, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout25_3->addItem( spacer5_3 );

    genLightSpecR_3 = new QSpinBox( privateLayoutWidget_6, "genLightSpecR_3" );
    genLightSpecR_3->setMinimumSize( QSize( 50, 25 ) );
    genLightSpecR_3->setMaximumSize( QSize( 50, 25 ) );
    genLightSpecR_3->setPaletteBackgroundColor( QColor( 255, 0, 0 ) );
    layout25_3->addWidget( genLightSpecR_3 );

    genLightSpecG_3 = new QSpinBox( privateLayoutWidget_6, "genLightSpecG_3" );
    genLightSpecG_3->setMinimumSize( QSize( 50, 25 ) );
    genLightSpecG_3->setMaximumSize( QSize( 50, 25 ) );
    genLightSpecG_3->setPaletteBackgroundColor( QColor( 0, 170, 0 ) );
    layout25_3->addWidget( genLightSpecG_3 );

    genLightSpecB_3 = new QSpinBox( privateLayoutWidget_6, "genLightSpecB_3" );
    genLightSpecB_3->setMinimumSize( QSize( 50, 25 ) );
    genLightSpecB_3->setMaximumSize( QSize( 50, 25 ) );
    genLightSpecB_3->setPaletteBackgroundColor( QColor( 85, 0, 255 ) );
    layout25_3->addWidget( genLightSpecB_3 );
    layout9_3->addLayout( layout25_3 );
    ribbons->insertTab( Widget9, QString("") );
    languageChange();
    resize( QSize(450, 380).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonApply, SIGNAL( clicked() ), this, SLOT( applySlot() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonApply_3, SIGNAL( clicked() ), this, SLOT( applySlot() ) );
    connect( buttonOk_3, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel_3, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( genLighSpecHelp_2_3, SIGNAL( clicked() ), this, SLOT( helpSlot() ) );
    connect( genLighSpecHelp_2, SIGNAL( clicked() ), this, SLOT( helpSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
Lighting::~Lighting()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Lighting::languageChange()
{
    setCaption( tr( "LIghting and Materials" ) );
    buttonApply->setText( tr( "&Apply" ) );
    buttonApply->setAccel( QKeySequence( tr( "Alt+A" ) ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    genLighSpecHelp_2->setText( QString::null );
    genLightPosLabel->setText( tr( "Light Position" ) );
    textLabel1_2_2->setText( tr( "<b>Z</b>" ) );
    textLabel1->setText( tr( "<b>X</b>" ) );
    textLabel1_2->setText( tr( "<b>Y</b>" ) );
    genLightAmbLabel->setText( tr( "Light Ambiance" ) );
    genLightDifLabel->setText( tr( "Light Diffuse" ) );
    genLightSpecLabel->setText( tr( "Light Specular" ) );
    ribbons->changeTab( Widget8, tr( "General" ) );
    buttonApply_3->setText( tr( "&Apply" ) );
    buttonApply_3->setAccel( QKeySequence( tr( "Alt+A" ) ) );
    buttonOk_3->setText( tr( "&OK" ) );
    buttonOk_3->setAccel( QKeySequence( QString::null ) );
    buttonCancel_3->setText( tr( "&Cancel" ) );
    buttonCancel_3->setAccel( QKeySequence( QString::null ) );
    genLighSpecHelp_2_3->setText( QString::null );
    genLightPosLabel_3->setText( tr( "Light Position" ) );
    textLabel1_2_4->setText( tr( "<b>Y</b>" ) );
    textLabel1_2_2_3->setText( tr( "<b>Z</b>" ) );
    textLabel1_4->setText( tr( "<b>X</b>" ) );
    genLightAmbLabel_3->setText( tr( "Light Ambiance" ) );
    genLightDifLabel_3->setText( tr( "Light Diffuse" ) );
    genLightSpecLabel_3->setText( tr( "Light Specular" ) );
    ribbons->changeTab( Widget9, tr( "Ribbons" ) );
}

