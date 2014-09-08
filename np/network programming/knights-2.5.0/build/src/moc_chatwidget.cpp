/****************************************************************************
** Meta object code from reading C++ file 'chatwidget.h'
**
** Created: Thu Sep 26 16:52:37 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/proto/chatwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__ChatWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       1,   49, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   21,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   44,   20,   20, 0x0a,
      83,   44,   20,   20, 0x0a,
     123,  115,   20,   20, 0x0a,
     147,  140,   20,   20, 0x0a,
     169,   20,   20,   20, 0x08,
     189,   20,   20,   20, 0x08,

 // enums: name, flags, count, data
     205, 0x0,    9,   53,

 // enum data: key, value
     217, uint(Knights::ChatWidget::AccountMessage),
     232, uint(Knights::ChatWidget::SeekMessage),
     244, uint(Knights::ChatWidget::ChallengeMessage),
     261, uint(Knights::ChatWidget::ChatMessage),
     273, uint(Knights::ChatWidget::GreetMessage),
     286, uint(Knights::ChatWidget::StatusMessage),
     300, uint(Knights::ChatWidget::GeneralMessage),
     315, uint(Knights::ChatWidget::ErrorMessage),
     328, uint(Knights::ChatWidget::MoveMessage),

       0        // eod
};

static const char qt_meta_stringdata_Knights__ChatWidget[] = {
    "Knights::ChatWidget\0\0text\0sendText(QString)\0"
    "text,type\0addText(QString,MessageType)\0"
    "addText(QByteArray,MessageType)\0message\0"
    "addText(Message)\0pwMode\0setPasswordMode(bool)\0"
    "sendButtonClicked()\0buttonClicked()\0"
    "MessageType\0AccountMessage\0SeekMessage\0"
    "ChallengeMessage\0ChatMessage\0GreetMessage\0"
    "StatusMessage\0GeneralMessage\0ErrorMessage\0"
    "MoveMessage\0"
};

void Knights::ChatWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ChatWidget *_t = static_cast<ChatWidget *>(_o);
        switch (_id) {
        case 0: _t->sendText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->addText((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< MessageType(*)>(_a[2]))); break;
        case 2: _t->addText((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< MessageType(*)>(_a[2]))); break;
        case 3: _t->addText((*reinterpret_cast< const Message(*)>(_a[1]))); break;
        case 4: _t->setPasswordMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->sendButtonClicked(); break;
        case 6: _t->buttonClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::ChatWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::ChatWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Knights__ChatWidget,
      qt_meta_data_Knights__ChatWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::ChatWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::ChatWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::ChatWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__ChatWidget))
        return static_cast<void*>(const_cast< ChatWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Knights::ChatWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Knights::ChatWidget::sendText(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
