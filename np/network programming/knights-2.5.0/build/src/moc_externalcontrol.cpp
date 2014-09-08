/****************************************************************************
** Meta object code from reading C++ file 'externalcontrol.h'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/externalcontrol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'externalcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__ExternalControl[] = {

 // content:
       6,       // revision
       0,       // classname
       1,   14, // classinfo
       9,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
      41,   25,

 // signals: signature, parameters, type, tag, flags
      63,   58,   57,   57, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,   58,   57,   57, 0x0a,
     100,   57,   57,   57, 0x0a,
     112,   57,   57,   57, 0x0a,
     125,   57,   57,   57, 0x0a,
     132,   57,   57,   57, 0x0a,
     144,   57,   57,   57, 0x0a,
     154,   57,   57,   57, 0x0a,
     162,   58,   57,   57, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Knights__ExternalControl[] = {
    "Knights::ExternalControl\0org.kde.Knights\0"
    "D-Bus Interface\0\0move\0moveMade(QString)\0"
    "movePiece(QString)\0pauseGame()\0"
    "resumeGame()\0undo()\0offerDraw()\0"
    "adjourn()\0abort()\0slotMoveMade(Move)\0"
};

void Knights::ExternalControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ExternalControl *_t = static_cast<ExternalControl *>(_o);
        switch (_id) {
        case 0: _t->moveMade((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->movePiece((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->pauseGame(); break;
        case 3: _t->resumeGame(); break;
        case 4: _t->undo(); break;
        case 5: _t->offerDraw(); break;
        case 6: _t->adjourn(); break;
        case 7: _t->abort(); break;
        case 8: _t->slotMoveMade((*reinterpret_cast< const Move(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::ExternalControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::ExternalControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Knights__ExternalControl,
      qt_meta_data_Knights__ExternalControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::ExternalControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::ExternalControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::ExternalControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__ExternalControl))
        return static_cast<void*>(const_cast< ExternalControl*>(this));
    return QObject::qt_metacast(_clname);
}

int Knights::ExternalControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Knights::ExternalControl::moveMade(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
