/****************************************************************************
** Form implementation generated from reading ui file 'surfdialog2.ui'
**
** Created: Mon Feb 6 13:32:34 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "surfdialog2.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qslider.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "surfdialog2.ui.h"
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
 *  Constructs a surfDialog2 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
surfDialog2::surfDialog2( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    QImage img;
    img.loadFromData( image0_data, sizeof( image0_data ), "PNG" );
    image0 = img;
    if ( !name )
	setName( "surfDialog2" );
    setSizeGripEnabled( TRUE );
    surfDialog2Layout = new QGridLayout( this, 1, 1, 11, 6, "surfDialog2Layout"); 

    layout5 = new QGridLayout( 0, 1, 1, 0, 6, "layout5"); 

    buttonHelp = new QPushButton( this, "buttonHelp" );
    buttonHelp->setAutoDefault( TRUE );
    buttonHelp->setIconSet( QIconSet( image0 ) );

    layout5->addWidget( buttonHelp, 0, 0 );

    Done = new QPushButton( this, "Done" );
    Done->setAutoDefault( TRUE );
    Done->setDefault( TRUE );

    layout5->addWidget( Done, 0, 3 );

    Apply = new QPushButton( this, "Apply" );
    Apply->setAutoDefault( TRUE );

    layout5->addWidget( Apply, 0, 2 );
    Horizontal_Spacing2 = new QSpacerItem( 231, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout5->addItem( Horizontal_Spacing2, 0, 1 );

    surfDialog2Layout->addLayout( layout5, 1, 0 );

    surfDialog = new QTabWidget( this, "surfDialog" );

    Widget8 = new QWidget( surfDialog, "Widget8" );
    Widget8Layout = new QGridLayout( Widget8, 1, 1, 11, 6, "Widget8Layout"); 

    quality = new QButtonGroup( Widget8, "quality" );
    quality->setExclusive( TRUE );
    quality->setColumnLayout(0, Qt::Vertical );
    quality->layout()->setSpacing( 6 );
    quality->layout()->setMargin( 11 );
    qualityLayout = new QGridLayout( quality->layout() );
    qualityLayout->setAlignment( Qt::AlignTop );

    checkBox8 = new QCheckBox( quality, "checkBox8" );

    qualityLayout->addWidget( checkBox8, 0, 0 );

    checkBox9 = new QCheckBox( quality, "checkBox9" );
    checkBox9->setChecked( FALSE );

    qualityLayout->addWidget( checkBox9, 1, 0 );

    checkBox10 = new QCheckBox( quality, "checkBox10" );
    checkBox10->setChecked( TRUE );

    qualityLayout->addWidget( checkBox10, 2, 0 );

    Widget8Layout->addWidget( quality, 1, 0 );

    groupBox1 = new QGroupBox( Widget8, "groupBox1" );
    groupBox1->setColumnLayout(0, Qt::Vertical );
    groupBox1->layout()->setSpacing( 6 );
    groupBox1->layout()->setMargin( 11 );
    groupBox1Layout = new QVBoxLayout( groupBox1->layout() );
    groupBox1Layout->setAlignment( Qt::AlignTop );

    layout1 = new QGridLayout( 0, 1, 1, 0, 6, "layout1"); 

    color = new QComboBox( FALSE, groupBox1, "color" );

    layout1->addWidget( color, 1, 0 );

    Color = new QPushButton( groupBox1, "Color" );

    layout1->addWidget( Color, 1, 1 );

    textLabel1 = new QLabel( groupBox1, "textLabel1" );

    layout1->addWidget( textLabel1, 0, 0 );

    trans = new QCheckBox( groupBox1, "trans" );

    layout1->addWidget( trans, 0, 1 );
    groupBox1Layout->addLayout( layout1 );

    Widget8Layout->addMultiCellWidget( groupBox1, 0, 0, 0, 1 );

    tightness = new QButtonGroup( Widget8, "tightness" );
    tightness->setExclusive( TRUE );
    tightness->setColumnLayout(0, Qt::Vertical );
    tightness->layout()->setSpacing( 6 );
    tightness->layout()->setMargin( 11 );
    tightnessLayout = new QGridLayout( tightness->layout() );
    tightnessLayout->setAlignment( Qt::AlignTop );

    checkBox11 = new QCheckBox( tightness, "checkBox11" );
    checkBox11->setChecked( TRUE );

    tightnessLayout->addWidget( checkBox11, 0, 0 );

    checkBox12 = new QCheckBox( tightness, "checkBox12" );
    checkBox12->setChecked( FALSE );

    tightnessLayout->addWidget( checkBox12, 1, 0 );

    checkBox13 = new QCheckBox( tightness, "checkBox13" );

    tightnessLayout->addWidget( checkBox13, 2, 0 );

    Widget8Layout->addWidget( tightness, 1, 1 );
    surfDialog->insertTab( Widget8, QString::fromLatin1("") );

    Widget9 = new QWidget( surfDialog, "Widget9" );
    Widget9Layout = new QGridLayout( Widget9, 1, 1, 11, 6, "Widget9Layout"); 

    groupBox5 = new QGroupBox( Widget9, "groupBox5" );
    groupBox5->setColumnLayout(0, Qt::Vertical );
    groupBox5->layout()->setSpacing( 6 );
    groupBox5->layout()->setMargin( 11 );
    groupBox5Layout = new QGridLayout( groupBox5->layout() );
    groupBox5Layout->setAlignment( Qt::AlignTop );

    fineQuality = new QSlider( groupBox5, "fineQuality" );
    fineQuality->setMinValue( 30 );
    fineQuality->setMaxValue( 70 );
    fineQuality->setValue( 35 );
    fineQuality->setOrientation( QSlider::Horizontal );
    fineQuality->setTickmarks( QSlider::Both );

    groupBox5Layout->addMultiCellWidget( fineQuality, 0, 0, 0, 2 );

    textLabel2 = new QLabel( groupBox5, "textLabel2" );

    groupBox5Layout->addWidget( textLabel2, 1, 0 );

    textLabel3 = new QLabel( groupBox5, "textLabel3" );

    groupBox5Layout->addWidget( textLabel3, 1, 2 );
    spacer2 = new QSpacerItem( 41, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    groupBox5Layout->addItem( spacer2, 1, 1 );

    Widget9Layout->addWidget( groupBox5, 0, 0 );

    groupBox6 = new QGroupBox( Widget9, "groupBox6" );
    groupBox6->setColumnLayout(0, Qt::Vertical );
    groupBox6->layout()->setSpacing( 6 );
    groupBox6->layout()->setMargin( 11 );
    groupBox6Layout = new QGridLayout( groupBox6->layout() );
    groupBox6Layout->setAlignment( Qt::AlignTop );

    textLabel4 = new QLabel( groupBox6, "textLabel4" );

    groupBox6Layout->addWidget( textLabel4, 1, 0 );

    textLabel5 = new QLabel( groupBox6, "textLabel5" );

    groupBox6Layout->addWidget( textLabel5, 1, 1 );

    fineTight = new QSlider( groupBox6, "fineTight" );
    fineTight->setAcceptDrops( FALSE );
    fineTight->setMinValue( 20 );
    fineTight->setMaxValue( 35 );
    fineTight->setPageStep( 10 );
    fineTight->setValue( 20 );
    fineTight->setOrientation( QSlider::Horizontal );
    fineTight->setTickmarks( QSlider::Both );
    fineTight->setTickInterval( 4 );

    groupBox6Layout->addMultiCellWidget( fineTight, 0, 0, 0, 1 );

    Widget9Layout->addWidget( groupBox6, 1, 0 );

    groupBox4 = new QGroupBox( Widget9, "groupBox4" );
    groupBox4->setColumnLayout(0, Qt::Vertical );
    groupBox4->layout()->setSpacing( 6 );
    groupBox4->layout()->setMargin( 11 );
    groupBox4Layout = new QGridLayout( groupBox4->layout() );
    groupBox4Layout->setAlignment( Qt::AlignTop );

    slider3 = new QSlider( groupBox4, "slider3" );
    slider3->setMinValue( 5 );
    slider3->setMaxValue( 100 );
    slider3->setValue( 100 );
    slider3->setOrientation( QSlider::Horizontal );
    slider3->setTickmarks( QSlider::Both );

    groupBox4Layout->addMultiCellWidget( slider3, 0, 0, 0, 3 );

    textLabel1_2 = new QLabel( groupBox4, "textLabel1_2" );

    groupBox4Layout->addWidget( textLabel1_2, 1, 0 );

    textLabel2_2 = new QLabel( groupBox4, "textLabel2_2" );

    groupBox4Layout->addWidget( textLabel2_2, 1, 3 );
    spacer3 = new QSpacerItem( 81, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    groupBox4Layout->addItem( spacer3, 1, 1 );

    Widget9Layout->addWidget( groupBox4, 2, 0 );
    surfDialog->insertTab( Widget9, QString::fromLatin1("") );

    surfDialog2Layout->addWidget( surfDialog, 0, 0 );
    languageChange();
    resize( QSize(319, 379).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( Done, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( Apply, SIGNAL( clicked() ), this, SLOT( applySlot() ) );
    connect( buttonHelp, SIGNAL( clicked() ), this, SLOT( helpSlot() ) );
    connect( Color, SIGNAL( clicked() ), this, SLOT( colorSlot() ) );
    connect( quality, SIGNAL( clicked(int) ), this, SLOT( qualitySlot(int) ) );
    connect( tightness, SIGNAL( clicked(int) ), this, SLOT( tightSlot(int) ) );
    connect( trans, SIGNAL( toggled(bool) ), this, SLOT( transSlot(bool) ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
surfDialog2::~surfDialog2()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void surfDialog2::languageChange()
{
    setCaption( tr( "Surface Control" ) );
    buttonHelp->setText( QString::null );
    buttonHelp->setAccel( QKeySequence( QString::null ) );
    Done->setText( tr( "&Done" ) );
    Done->setAccel( QKeySequence( tr( "Alt+D" ) ) );
    Apply->setText( tr( "Apply" ) );
    Apply->setAccel( QKeySequence( QString::null ) );
    quality->setTitle( tr( "Quality" ) );
    checkBox8->setText( tr( "High" ) );
    checkBox9->setText( tr( "Medium" ) );
    checkBox10->setText( tr( "Low" ) );
    groupBox1->setTitle( tr( "Surface Coloring" ) );
    color->clear();
    color->insertItem( tr( "Atom Color" ) );
    color->insertItem( tr( "AC-GS" ) );
    color->insertItem( tr( "Electrostatic" ) );
    color->insertItem( tr( "Solid" ) );
    Color->setText( tr( "Color" ) );
    textLabel1->setText( tr( "Color By" ) );
    trans->setText( tr( "Translucent" ) );
    tightness->setTitle( tr( "Tightness" ) );
    checkBox11->setText( tr( "Tight" ) );
    checkBox12->setText( tr( "Medium" ) );
    checkBox13->setText( tr( "Smooth" ) );
    surfDialog->changeTab( Widget8, tr( "Basic Control" ) );
    groupBox5->setTitle( tr( "Quality" ) );
    textLabel2->setText( tr( "Low" ) );
    textLabel3->setText( tr( "High" ) );
    groupBox6->setTitle( tr( "Tightness" ) );
    textLabel4->setText( tr( "Molecular Surface" ) );
    textLabel5->setText( tr( "Smooth Gaussian" ) );
    groupBox4->setTitle( tr( "Transparency" ) );
    textLabel1_2->setText( tr( "Clear" ) );
    textLabel2_2->setText( tr( "Solid" ) );
    surfDialog->changeTab( Widget9, tr( "Fine Control" ) );
}

