/****************************************************************************
** Meta object code from reading C++ file 'mousesensor.h'
**
** Created: Sat Mar 1 08:56:48 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mousesensor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mousesensor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_mouseSensor[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      63,   32,   12,   12, 0x05,
     136,  116,   12,   12, 0x05,
     217,  176,   12,   12, 0x05,
     284,  116,   12,   12, 0x05,
     325,  116,   12,   12, 0x05,
     366,  116,   12,   12, 0x05,
     410,   32,   12,   12, 0x05,
     470,  116,   12,   12, 0x05,
     511,  116,   12,   12, 0x05,
     553,  116,   12,   12, 0x05,
     592,  116,   12,   12, 0x05,
     632,  116,   12,   12, 0x05,
     673,  116,   12,   12, 0x05,
     714,  116,   12,   12, 0x05,
     756,   32,   12,   12, 0x05,
     820,  811,   12,   12, 0x05,
     839,  811,   12,   12, 0x05,
     863,  859,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     895,   12,   12,   12, 0x08,
     925,   12,   12,   12, 0x08,
     943,  937,   12,   12, 0x08,
     979,   12,   12,   12, 0x08,
    1008,   12,   12,   12, 0x08,
    1040,   12,   12,   12, 0x08,
    1065,   12,   12,   12, 0x08,
    1091,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_mouseSensor[] = {
    "mouseSensor\0\0rightButtonPress()\0"
    "x,y,scaledX,scaledY,shiftState\0"
    "leftButtonMove(int&,int&,float&,float&,button_state)\0"
    "x,y,scaledX,scaledY\0"
    "leftButtonMove(int&,int&,float&,float&)\0"
    "x,y,scaledX,scaledY,shiftState,ctrlState\0"
    "leftButtonPress(int&,int&,float&,float&,button_state,button_state)\0"
    "ShiftLeftMousePress(int,int,float,float)\0"
    "ShiftLeftButtonMove(int,int,float,float)\0"
    "ShiftLeftButtonRelease(int,int,float,float)\0"
    "leftButtonDoubleClick(int&,int&,float&,float&,button_state)\0"
    "rightButtonMove(int&,int&,float&,float&)\0"
    "rightButtonPress(int&,int&,float&,float&)\0"
    "midButtonMove(int&,int&,float&,float&)\0"
    "midButtonPress(int&,int&,float&,float&)\0"
    "leftButtonPress(int&,int&,float&,float&)\0"
    "midAndRightMove(int&,int&,float&,float&)\0"
    "midAndRightPress(int&,int&,float&,float&)\0"
    "midButtonRelease(int&,int&,float&,float&,button_state)\0"
    "rotation\0wheelForward(int&)\0"
    "wheelBackward(int&)\0x,y\0"
    "midButtonSingleClick(int&,int&)\0"
    "mousePressEvent(QMouseEvent*)\0timerDone()\0"
    "event\0mouseDoubleClickEvent(QMouseEvent*)\0"
    "mouseMoveEvent(QMouseEvent*)\0"
    "mouseReleaseEvent(QMouseEvent*)\0"
    "wheelEvent(QWheelEvent*)\0"
    "keyPressEvent(QKeyEvent*)\0"
    "keyReleaseEvent(QKeyEvent*)\0"
};

const QMetaObject mouseSensor::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_mouseSensor,
      qt_meta_data_mouseSensor, 0 }
};

const QMetaObject *mouseSensor::metaObject() const
{
    return &staticMetaObject;
}

void *mouseSensor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mouseSensor))
	return static_cast<void*>(const_cast< mouseSensor*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int mouseSensor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: rightButtonPress(); break;
        case 1: leftButtonMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< button_state(*)>(_a[5]))); break;
        case 2: leftButtonMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 3: leftButtonPress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< button_state(*)>(_a[5])),(*reinterpret_cast< button_state(*)>(_a[6]))); break;
        case 4: ShiftLeftMousePress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 5: ShiftLeftButtonMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 6: ShiftLeftButtonRelease((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 7: leftButtonDoubleClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< button_state(*)>(_a[5]))); break;
        case 8: rightButtonMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 9: rightButtonPress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 10: midButtonMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 11: midButtonPress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 12: leftButtonPress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 13: midAndRightMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 14: midAndRightPress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 15: midButtonRelease((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< button_state(*)>(_a[5]))); break;
        case 16: wheelForward((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: wheelBackward((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: midButtonSingleClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 20: timerDone(); break;
        case 21: mouseDoubleClickEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 22: mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 23: mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 24: wheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 25: keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 26: keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        }
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void mouseSensor::rightButtonPress()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void mouseSensor::leftButtonMove(int & _t1, int & _t2, float & _t3, float & _t4, button_state _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mouseSensor::leftButtonMove(int & _t1, int & _t2, float & _t3, float & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void mouseSensor::leftButtonPress(int & _t1, int & _t2, float & _t3, float & _t4, button_state _t5, button_state _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void mouseSensor::ShiftLeftMousePress(int _t1, int _t2, float _t3, float _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void mouseSensor::ShiftLeftButtonMove(int _t1, int _t2, float _t3, float _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void mouseSensor::ShiftLeftButtonRelease(int _t1, int _t2, float _t3, float _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void mouseSensor::leftButtonDoubleClick(int & _t1, int & _t2, float & _t3, float & _t4, button_state _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void mouseSensor::rightButtonMove(int & _t1, int & _t2, float & _t3, float & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void mouseSensor::rightButtonPress(int & _t1, int & _t2, float & _t3, float & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void mouseSensor::midButtonMove(int & _t1, int & _t2, float & _t3, float & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void mouseSensor::midButtonPress(int & _t1, int & _t2, float & _t3, float & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void mouseSensor::leftButtonPress(int & _t1, int & _t2, float & _t3, float & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void mouseSensor::midAndRightMove(int & _t1, int & _t2, float & _t3, float & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void mouseSensor::midAndRightPress(int & _t1, int & _t2, float & _t3, float & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void mouseSensor::midButtonRelease(int & _t1, int & _t2, float & _t3, float & _t4, button_state _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void mouseSensor::wheelForward(int & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void mouseSensor::wheelBackward(int & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void mouseSensor::midButtonSingleClick(int & _t1, int & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}
