/****************************************************************************
** Meta object code from reading C++ file 'ficsprotocol.h'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/proto/ficsprotocol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ficsprotocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__FicsProtocol[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,
      40,   22,   22,   22, 0x05,
      56,   53,   22,   22, 0x05,
      84,   78,   22,   22, 0x05,
     127,  117,   22,   22, 0x05,
     160,   53,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     182,   22,   22,   22, 0x0a,
     189,   22,   22,   22, 0x0a,
     198,   22,   22,   22, 0x0a,
     212,   22,   22,   22, 0x0a,
     229,   53,   22,   22, 0x0a,
     245,   53,   22,   22, 0x0a,
     266,   53,   22,   22, 0x0a,
     306,  288,   22,   22, 0x0a,
     334,  329,   22,   22, 0x0a,
     352,   22,   22,   22, 0x0a,
     374,  369,   22,   22, 0x0a,
     391,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Knights__FicsProtocol[] = {
    "Knights::FicsProtocol\0\0sessionStarted()\0"
    "clearSeeks()\0id\0gameOfferRemoved(int)\0"
    "offer\0gameOfferReceived(FicsGameOffer)\0"
    "challenge\0challengeReceived(FicsChallenge)\0"
    "challengeRemoved(int)\0init()\0resign()\0"
    "socketError()\0dialogRejected()\0"
    "acceptSeek(int)\0acceptChallenge(int)\0"
    "declineChallenge(int)\0username,password\0"
    "login(QString,QString)\0text\0"
    "sendChat(QString)\0openGameDialog()\0"
    "seek\0setSeeking(bool)\0setupOptions()\0"
};

void Knights::FicsProtocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FicsProtocol *_t = static_cast<FicsProtocol *>(_o);
        switch (_id) {
        case 0: _t->sessionStarted(); break;
        case 1: _t->clearSeeks(); break;
        case 2: _t->gameOfferRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->gameOfferReceived((*reinterpret_cast< const FicsGameOffer(*)>(_a[1]))); break;
        case 4: _t->challengeReceived((*reinterpret_cast< const FicsChallenge(*)>(_a[1]))); break;
        case 5: _t->challengeRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->init(); break;
        case 7: _t->resign(); break;
        case 8: _t->socketError(); break;
        case 9: _t->dialogRejected(); break;
        case 10: _t->acceptSeek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->acceptChallenge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->declineChallenge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->login((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: _t->sendChat((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->openGameDialog(); break;
        case 16: _t->setSeeking((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->setupOptions(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::FicsProtocol::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::FicsProtocol::staticMetaObject = {
    { &TextProtocol::staticMetaObject, qt_meta_stringdata_Knights__FicsProtocol,
      qt_meta_data_Knights__FicsProtocol, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::FicsProtocol::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::FicsProtocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::FicsProtocol::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__FicsProtocol))
        return static_cast<void*>(const_cast< FicsProtocol*>(this));
    return TextProtocol::qt_metacast(_clname);
}

int Knights::FicsProtocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TextProtocol::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void Knights::FicsProtocol::sessionStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Knights::FicsProtocol::clearSeeks()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Knights::FicsProtocol::gameOfferRemoved(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Knights::FicsProtocol::gameOfferReceived(const FicsGameOffer & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Knights::FicsProtocol::challengeReceived(const FicsChallenge & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Knights::FicsProtocol::challengeRemoved(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
