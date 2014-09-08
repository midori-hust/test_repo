/****************************************************************************
** Meta object code from reading C++ file 'gamemanager.h'
**
** Created: Thu Sep 26 16:52:37 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/gamemanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__Manager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   18,   17,   17, 0x05,
      63,   54,   17,   17, 0x05,
      82,   54,   17,   17, 0x05,
     106,  101,   17,   17, 0x05,
     130,  123,   17,   17, 0x05,
     157,   17,   17,   17, 0x05,
     178,  172,   17,   17, 0x05,
     205,  198,   17,   17, 0x05,
     225,   17,   17,   17, 0x05,
     242,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     262,   17,   17,   17, 0x08,
     280,  101,   17,   17, 0x0a,
     301,  101,   17,   17, 0x0a,
     319,  101,   17,   17, 0x0a,
     347,   17,   17,   17, 0x0a,
     371,  198,   17,   17, 0x0a,
     387,   17,   17,   17, 0x0a,
     413,  396,   17,   17, 0x0a,
     459,  445,   17,   17, 0x2a,
     494,  487,   17,   17, 0x2a,
     516,  172,   17,   17, 0x0a,
     543,  533,   17,   17, 0x0a,
     575,   17,   17,   17, 0x0a,
     588,   17,   17,   17, 0x0a,
     595,   17,   17,   17, 0x0a,
     602,   17,   17,   17, 0x0a,
     614,   17,   17,   17, 0x0a,
     624,   17,   17,   17, 0x0a,
     640,  632,   17,   17, 0x0a,
     667,  661,   17,   17, 0x0a,
     729,  706,   17,   17, 0x0a,
     761,  752,   17,   17, 0x0a,
     788,  752,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Knights__Manager[] = {
    "Knights::Manager\0\0color,time\0"
    "timeChanged(Color,QTime)\0possible\0"
    "undoPossible(bool)\0redoPossible(bool)\0"
    "move\0pieceMoved(Move)\0player\0"
    "activePlayerChanged(Color)\0initComplete()\0"
    "offer\0notification(Offer)\0winner\0"
    "winnerNotify(Color)\0historyChanged()\0"
    "playerNameChanged()\0sendPendingMove()\0"
    "moveByProtocol(Move)\0moveByBoard(Move)\0"
    "moveByExternalControl(Move)\0"
    "protocolInitSuccesful()\0gameOver(Color)\0"
    "resign()\0action,player,id\0"
    "sendOffer(GameAction,Color,int)\0"
    "action,player\0sendOffer(GameAction,Color)\0"
    "action\0sendOffer(GameAction)\0"
    "sendOffer(Offer)\0id,result\0"
    "setOfferResult(int,OfferAction)\0"
    "initialize()\0undo()\0redo()\0offerDraw()\0"
    "adjourn()\0abort()\0running\0"
    "setTimeRunning(bool)\0level\0"
    "levelChanged(const KgDifficultyLevel*)\0"
    "searchDepth,memorySize\0setDifficulty(int,int)\0"
    "filename\0saveGameHistoryAs(QString)\0"
    "loadGameHistoryFrom(QString)\0"
};

void Knights::Manager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Manager *_t = static_cast<Manager *>(_o);
        switch (_id) {
        case 0: _t->timeChanged((*reinterpret_cast< Color(*)>(_a[1])),(*reinterpret_cast< const QTime(*)>(_a[2]))); break;
        case 1: _t->undoPossible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->redoPossible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->pieceMoved((*reinterpret_cast< const Move(*)>(_a[1]))); break;
        case 4: _t->activePlayerChanged((*reinterpret_cast< Color(*)>(_a[1]))); break;
        case 5: _t->initComplete(); break;
        case 6: _t->notification((*reinterpret_cast< const Offer(*)>(_a[1]))); break;
        case 7: _t->winnerNotify((*reinterpret_cast< Color(*)>(_a[1]))); break;
        case 8: _t->historyChanged(); break;
        case 9: _t->playerNameChanged(); break;
        case 10: _t->sendPendingMove(); break;
        case 11: _t->moveByProtocol((*reinterpret_cast< const Move(*)>(_a[1]))); break;
        case 12: _t->moveByBoard((*reinterpret_cast< const Move(*)>(_a[1]))); break;
        case 13: _t->moveByExternalControl((*reinterpret_cast< const Move(*)>(_a[1]))); break;
        case 14: _t->protocolInitSuccesful(); break;
        case 15: _t->gameOver((*reinterpret_cast< Color(*)>(_a[1]))); break;
        case 16: _t->resign(); break;
        case 17: _t->sendOffer((*reinterpret_cast< GameAction(*)>(_a[1])),(*reinterpret_cast< Color(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 18: _t->sendOffer((*reinterpret_cast< GameAction(*)>(_a[1])),(*reinterpret_cast< Color(*)>(_a[2]))); break;
        case 19: _t->sendOffer((*reinterpret_cast< GameAction(*)>(_a[1]))); break;
        case 20: _t->sendOffer((*reinterpret_cast< const Offer(*)>(_a[1]))); break;
        case 21: _t->setOfferResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< OfferAction(*)>(_a[2]))); break;
        case 22: _t->initialize(); break;
        case 23: _t->undo(); break;
        case 24: _t->redo(); break;
        case 25: _t->offerDraw(); break;
        case 26: _t->adjourn(); break;
        case 27: _t->abort(); break;
        case 28: _t->setTimeRunning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->levelChanged((*reinterpret_cast< const KgDifficultyLevel*(*)>(_a[1]))); break;
        case 30: _t->setDifficulty((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 31: _t->saveGameHistoryAs((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 32: _t->loadGameHistoryFrom((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::Manager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::Manager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Knights__Manager,
      qt_meta_data_Knights__Manager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::Manager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::Manager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::Manager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__Manager))
        return static_cast<void*>(const_cast< Manager*>(this));
    return QObject::qt_metacast(_clname);
}

int Knights::Manager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void Knights::Manager::timeChanged(Color _t1, const QTime & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Knights::Manager::undoPossible(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Knights::Manager::redoPossible(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Knights::Manager::pieceMoved(const Move & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Knights::Manager::activePlayerChanged(Color _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Knights::Manager::initComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Knights::Manager::notification(const Offer & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Knights::Manager::winnerNotify(Color _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Knights::Manager::historyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void Knights::Manager::playerNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
