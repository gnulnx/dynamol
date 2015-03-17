/****************************************************************************
** Meta object code from reading C++ file 'scriptengine.h'
**
** Created: Sat Mar 1 08:56:48 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scriptengine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scriptengine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dynamol__ScriptEngine[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      29,   23,   22,   22, 0x0a,
      55,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dynamol__ScriptEngine[] = {
    "dynamol::ScriptEngine\0\0event\0"
    "keyPressEvent(QKeyEvent*)\0CheckText()\0"
};

const QMetaObject dynamol::ScriptEngine::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_dynamol__ScriptEngine,
      qt_meta_data_dynamol__ScriptEngine, 0 }
};

const QMetaObject *dynamol::ScriptEngine::metaObject() const
{
    return &staticMetaObject;
}

void *dynamol::ScriptEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dynamol__ScriptEngine))
	return static_cast<void*>(const_cast< ScriptEngine*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int dynamol::ScriptEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: CheckText(); break;
        }
        _id -= 2;
    }
    return _id;
}
