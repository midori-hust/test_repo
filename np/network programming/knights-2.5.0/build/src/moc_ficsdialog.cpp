/****************************************************************************
** Meta object code from reading C++ file 'ficsdialog.h'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/proto/ficsdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ficsdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__FicsDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   21,   20,   20, 0x05,
      62,   20,   20,   20, 0x05,
      83,   78,   20,   20, 0x05,
     111,  104,   20,   20, 0x05,
     137,  104,   20,   20, 0x05,
     169,  162,   20,   20, 0x05,
     197,  185,   20,   20, 0x05,
     218,  185,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     240,   20,   20,   20, 0x0a,
     267,  261,   20,   20, 0x0a,
     298,  295,   20,   20, 0x0a,
     329,  319,   20,   20, 0x0a,
     357,  295,   20,   20, 0x0a,
     378,   20,   20,   20, 0x0a,
     392,   20,   20,   20, 0x0a,
     401,   20,   20,   20, 0x0a,
     415,  411,   20,   20, 0x0a,
     438,   20,   20,   20, 0x0a,
     458,   20,   20,   20, 0x0a,
     477,  470,   20,   20, 0x0a,
     504,   20,   20,   20, 0x0a,
     532,  519,   20,   20, 0x0a,
     563,  556,   20,   20, 0x2a,
     589,  582,   20,   20, 0x0a,
     617,  611,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Knights__FicsDialog[] = {
    "Knights::FicsDialog\0\0username,password\0"
    "login(QString,QString)\0createAccount()\0"
    "seek\0seekingChanged(bool)\0needed\0"
    "declineButtonNeeded(bool)\0"
    "acceptButtonNeeded(bool)\0seekId\0"
    "acceptSeek(int)\0challengeId\0"
    "acceptChallenge(int)\0declineChallenge(int)\0"
    "slotSessionStarted()\0offer\0"
    "addGameOffer(FicsGameOffer)\0id\0"
    "removeGameOffer(int)\0challenge\0"
    "addChallenge(FicsChallenge)\0"
    "removeChallenge(int)\0clearOffers()\0"
    "accept()\0decline()\0tab\0currentTabChanged(int)\0"
    "slotCreateAccount()\0slotLogin()\0widget\0"
    "setConsoleWidget(QWidget*)\0focusOnLogin()\0"
    "status,error\0setStatus(QString,bool)\0"
    "status\0setStatus(QString)\0enable\0"
    "setLoginEnabled(bool)\0state\0"
    "rememberCheckBoxChanged(int)\0"
};

void Knights::FicsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FicsDialog *_t = static_cast<FicsDialog *>(_o);
        switch (_id) {
        case 0: _t->login((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->createAccount(); break;
        case 2: _t->seekingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->declineButtonNeeded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->acceptButtonNeeded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->acceptSeek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->acceptChallenge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->declineChallenge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slotSessionStarted(); break;
        case 9: _t->addGameOffer((*reinterpret_cast< const FicsGameOffer(*)>(_a[1]))); break;
        case 10: _t->removeGameOffer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->addChallenge((*reinterpret_cast< const FicsChallenge(*)>(_a[1]))); break;
        case 12: _t->removeChallenge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->clearOffers(); break;
        case 14: _t->accept(); break;
        case 15: _t->decline(); break;
        case 16: _t->currentTabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->slotCreateAccount(); break;
        case 18: _t->slotLogin(); break;
        case 19: _t->setConsoleWidget((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 20: _t->focusOnLogin(); break;
        case 21: _t->setStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 22: _t->setStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->setLoginEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->rememberCheckBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::FicsDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::FicsDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Knights__FicsDialog,
      qt_meta_data_Knights__FicsDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::FicsDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::FicsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::FicsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__FicsDialog))
        return static_cast<void*>(const_cast< FicsDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int Knights::FicsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void Knights::FicsDialog::login(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Knights::FicsDialog::createAccount()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Knights::FicsDialog::seekingChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Knights::FicsDialog::declineButtonNeeded(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Knights::FicsDialog::acceptButtonNeeded(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Knights::FicsDialog::acceptSeek(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Knights::FicsDialog::acceptChallenge(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Knights::FicsDialog::declineChallenge(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
