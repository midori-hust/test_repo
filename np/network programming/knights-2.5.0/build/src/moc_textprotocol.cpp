/****************************************************************************
** Meta object code from reading C++ file 'textprotocol.h'
**
** Created: Thu Sep 26 16:52:37 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/proto/textprotocol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'textprotocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__TextProtocol[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x09,
      45,   40,   22,   22, 0x09,
      60,   40,   22,   22, 0x09,
      79,   40,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Knights__TextProtocol[] = {
    "Knights::TextProtocol\0\0readFromDevice()\0"
    "text\0write(QString)\0write(const char*)\0"
    "writeCheckMoves(QString)\0"
};

void Knights::TextProtocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TextProtocol *_t = static_cast<TextProtocol *>(_o);
        switch (_id) {
        case 0: _t->readFromDevice(); break;
        case 1: _t->write((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->write((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 3: _t->writeCheckMoves((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::TextProtocol::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::TextProtocol::staticMetaObject = {
    { &Protocol::staticMetaObject, qt_meta_stringdata_Knights__TextProtocol,
      qt_meta_data_Knights__TextProtocol, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::TextProtocol::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::TextProtocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::TextProtocol::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__TextProtocol))
        return static_cast<void*>(const_cast< TextProtocol*>(this));
    return Protocol::qt_metacast(_clname);
}

int Knights::TextProtocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Protocol::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
