/****************************************************************************
** Meta object code from reading C++ file 'protocol.h'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/proto/protocol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'protocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__Protocol[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       2,  109, // properties
       3,  115, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   19,   18,   18, 0x05,
      38,   18,   18,   18, 0x05,
      59,   52,   18,   18, 0x05,
      87,   75,   18,   18, 0x05,
     121,  115,   18,   18, 0x05,
     149,   18,   18,   18, 0x05,
     187,  165,   18,   18, 0x05,
     232,  222,   18,   18, 0x25,
     264,  259,   18,   18, 0x05,
     283,  259,   18,   18, 0x05,
     316,  307,   18,   18, 0x05,
     335,  307,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     354,   19,   18,   18, 0x0a,
     365,   18,   18,   18, 0x0a,
     372,   18,   18,   18, 0x0a,
     390,  384,   18,   18, 0x0a,
     407,  384,   18,   18, 0x0a,
     426,  384,   18,   18, 0x0a,
     446,   52,   18,   18, 0x0a,

 // properties: name, type, flags
     469,  463, 0x0009510b,
     483,  475, 0x0a095103,

 // enums: name, flags, count, data
     494, 0x0,   14,  127,
     502, 0x1,   14,  155,
     511, 0x0,    5,  183,

 // enum data: key, value
     521, uint(Knights::Protocol::NoFeatures),
     532, uint(Knights::Protocol::TimeLimit),
     542, uint(Knights::Protocol::SetTimeLimit),
     555, uint(Knights::Protocol::UpdateTime),
     566, uint(Knights::Protocol::Pause),
     572, uint(Knights::Protocol::History),
     580, uint(Knights::Protocol::Undo),
     585, uint(Knights::Protocol::GameOver),
     594, uint(Knights::Protocol::Draw),
     599, uint(Knights::Protocol::Adjourn),
     607, uint(Knights::Protocol::Resign),
     614, uint(Knights::Protocol::Abort),
     620, uint(Knights::Protocol::SetDifficulty),
     634, uint(Knights::Protocol::AdjustDifficulty),
     521, uint(Knights::Protocol::NoFeatures),
     532, uint(Knights::Protocol::TimeLimit),
     542, uint(Knights::Protocol::SetTimeLimit),
     555, uint(Knights::Protocol::UpdateTime),
     566, uint(Knights::Protocol::Pause),
     572, uint(Knights::Protocol::History),
     580, uint(Knights::Protocol::Undo),
     585, uint(Knights::Protocol::GameOver),
     594, uint(Knights::Protocol::Draw),
     599, uint(Knights::Protocol::Adjourn),
     607, uint(Knights::Protocol::Resign),
     614, uint(Knights::Protocol::Abort),
     620, uint(Knights::Protocol::SetDifficulty),
     634, uint(Knights::Protocol::AdjustDifficulty),
     651, uint(Knights::Protocol::NoError),
     659, uint(Knights::Protocol::UserCancelled),
     673, uint(Knights::Protocol::NetworkError),
     686, uint(Knights::Protocol::InstallationError),
     704, uint(Knights::Protocol::UnknownError),

       0        // eod
};

static const char qt_meta_stringdata_Knights__Protocol[] = {
    "Knights::Protocol\0\0m\0pieceMoved(Move)\0"
    "illegalMove()\0winner\0gameOver(Color)\0"
    "errorString\0errorStringChanged(QString)\0"
    "error\0errorCodeChanged(ErrorCode)\0"
    "initSuccesful()\0errorCode,errorString\0"
    "error(Protocol::ErrorCode,QString)\0"
    "errorCode\0error(Protocol::ErrorCode)\0"
    "time\0timeChanged(QTime)\0timeLimitChanged(QTime)\0"
    "possible\0undoPossible(bool)\0"
    "redoPossible(bool)\0move(Move)\0init()\0"
    "startGame()\0offer\0makeOffer(Offer)\0"
    "acceptOffer(Offer)\0declineOffer(Offer)\0"
    "setWinner(Color)\0Color\0color\0QString\0"
    "playerName\0Feature\0Features\0ErrorCode\0"
    "NoFeatures\0TimeLimit\0SetTimeLimit\0"
    "UpdateTime\0Pause\0History\0Undo\0GameOver\0"
    "Draw\0Adjourn\0Resign\0Abort\0SetDifficulty\0"
    "AdjustDifficulty\0NoError\0UserCancelled\0"
    "NetworkError\0InstallationError\0"
    "UnknownError\0"
};

void Knights::Protocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Protocol *_t = static_cast<Protocol *>(_o);
        switch (_id) {
        case 0: _t->pieceMoved((*reinterpret_cast< const Move(*)>(_a[1]))); break;
        case 1: _t->illegalMove(); break;
        case 2: _t->gameOver((*reinterpret_cast< Color(*)>(_a[1]))); break;
        case 3: _t->errorStringChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->errorCodeChanged((*reinterpret_cast< const ErrorCode(*)>(_a[1]))); break;
        case 5: _t->initSuccesful(); break;
        case 6: _t->error((*reinterpret_cast< const Protocol::ErrorCode(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->error((*reinterpret_cast< const Protocol::ErrorCode(*)>(_a[1]))); break;
        case 8: _t->timeChanged((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 9: _t->timeLimitChanged((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 10: _t->undoPossible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->redoPossible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->move((*reinterpret_cast< const Move(*)>(_a[1]))); break;
        case 13: _t->init(); break;
        case 14: _t->startGame(); break;
        case 15: _t->makeOffer((*reinterpret_cast< const Offer(*)>(_a[1]))); break;
        case 16: _t->acceptOffer((*reinterpret_cast< const Offer(*)>(_a[1]))); break;
        case 17: _t->declineOffer((*reinterpret_cast< const Offer(*)>(_a[1]))); break;
        case 18: _t->setWinner((*reinterpret_cast< Color(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::Protocol::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::Protocol::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Knights__Protocol,
      qt_meta_data_Knights__Protocol, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::Protocol::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::Protocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::Protocol::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__Protocol))
        return static_cast<void*>(const_cast< Protocol*>(this));
    return QObject::qt_metacast(_clname);
}

int Knights::Protocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Color*>(_v) = color(); break;
        case 1: *reinterpret_cast< QString*>(_v) = playerName(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setColor(*reinterpret_cast< Color*>(_v)); break;
        case 1: setPlayerName(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Knights::Protocol::pieceMoved(const Move & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Knights::Protocol::illegalMove()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Knights::Protocol::gameOver(Color _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Knights::Protocol::errorStringChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Knights::Protocol::errorCodeChanged(const ErrorCode & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Knights::Protocol::initSuccesful()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Knights::Protocol::error(const Protocol::ErrorCode & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 8
void Knights::Protocol::timeChanged(const QTime & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Knights::Protocol::timeLimitChanged(const QTime & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Knights::Protocol::undoPossible(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Knights::Protocol::redoPossible(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_END_MOC_NAMESPACE
