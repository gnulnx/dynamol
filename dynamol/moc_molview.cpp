/****************************************************************************
** Meta object code from reading C++ file 'molview.h'
**
** Created: Sat Mar 1 08:56:50 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "molview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'molview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dynamol__molView[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x09,
      33,   17,   17,   17, 0x09,
      45,   17,   17,   17, 0x09,
      59,   55,   17,   17, 0x09,
      81,   77,   17,   17, 0x09,
     119,  101,   17,   17, 0x09,
     184,  154,   17,   17, 0x09,
     233,  215,   17,   17, 0x09,
     270,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dynamol__molView[] = {
    "dynamol::molView\0\0initializeGL()\0"
    "InitSetup()\0paintGL()\0w,h\0resizeGL(int,int)\0"
    "x,y\0ReCenter(int&,int&)\0x,y,xFloat,yFloat\0"
    "selectObjects(int,int,float,float)\0"
    "newX,newY,newXFloat,newYFloat\0"
    "selectBox(int,int,float,float)\0"
    "x,y,xScale,yScale\0"
    "SweepPickSelect(int,int,float,float)\0"
    "FPS_Slot()\0"
};

const QMetaObject dynamol::molView::staticMetaObject = {
    { &molViewControl::staticMetaObject, qt_meta_stringdata_dynamol__molView,
      qt_meta_data_dynamol__molView, 0 }
};

const QMetaObject *dynamol::molView::metaObject() const
{
    return &staticMetaObject;
}

void *dynamol::molView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dynamol__molView))
	return static_cast<void*>(const_cast< molView*>(this));
    return molViewControl::qt_metacast(_clname);
}

int dynamol::molView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = molViewControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: initializeGL(); break;
        case 1: InitSetup(); break;
        case 2: paintGL(); break;
        case 3: resizeGL((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: ReCenter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: selectObjects((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 6: selectBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 7: SweepPickSelect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 8: FPS_Slot(); break;
        }
        _id -= 9;
    }
    return _id;
}
