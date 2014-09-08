/****************************************************************************
** Meta object code from reading C++ file 'xboardprotocol.h'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/proto/xboardprotocol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xboardprotocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__XBoardProtocol[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x0a,
      32,   24,   24,   24, 0x0a,
      51,   44,   24,   24, 0x0a,
      74,   68,   24,   24, 0x0a,
      91,   68,   24,   24, 0x0a,
     110,   68,   24,   24, 0x0a,
     143,  130,   24,   24, 0x0a,
     166,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Knights__XBoardProtocol[] = {
    "Knights::XBoardProtocol\0\0init()\0"
    "startGame()\0winner\0setWinner(Color)\0"
    "offer\0makeOffer(Offer)\0acceptOffer(Offer)\0"
    "declineOffer(Offer)\0depth,memory\0"
    "setDifficulty(int,int)\0readError()\0"
};

void Knights::XBoardProtocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        XBoardProtocol *_t = static_cast<XBoardProtocol *>(_o);
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->startGame(); break;
        case 2: _t->setWinner((*reinterpret_cast< Color(*)>(_a[1]))); break;
        case 3: _t->makeOffer((*reinterpret_cast< const Offer(*)>(_a[1]))); break;
        case 4: _t->acceptOffer((*reinterpret_cast< const Offer(*)>(_a[1]))); break;
        case 5: _t->declineOffer((*reinterpret_cast< const Offer(*)>(_a[1]))); break;
        case 6: _t->setDifficulty((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->readError(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::XBoardProtocol::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::XBoardProtocol::staticMetaObject = {
    { &ComputerProtocol::staticMetaObject, qt_meta_stringdata_Knights__XBoardProtocol,
      qt_meta_data_Knights__XBoardProtocol, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::XBoardProtocol::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::XBoardProtocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::XBoardProtocol::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__XBoardProtocol))
        return static_cast<void*>(const_cast< XBoardProtocol*>(this));
    return ComputerProtocol::qt_metacast(_clname);
}

int Knights::XBoardProtocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ComputerProtocol::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
