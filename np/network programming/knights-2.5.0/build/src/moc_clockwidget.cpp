/****************************************************************************
** Meta object code from reading C++ file 'clockwidget.h'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/clockwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clockwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__ClockWidget[] = {

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
      33,   22,   21,   21, 0x0a,
      65,   59,   21,   21, 0x0a,
     102,   91,   21,   21, 0x0a,
     131,   22,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Knights__ClockWidget[] = {
    "Knights::ClockWidget\0\0color,time\0"
    "setTimeLimit(Color,QTime)\0color\0"
    "setDisplayedPlayer(Color)\0color,name\0"
    "setPlayerName(Color,QString)\0"
    "setCurrentTime(Color,QTime)\0"
};

void Knights::ClockWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClockWidget *_t = static_cast<ClockWidget *>(_o);
        switch (_id) {
        case 0: _t->setTimeLimit((*reinterpret_cast< Color(*)>(_a[1])),(*reinterpret_cast< const QTime(*)>(_a[2]))); break;
        case 1: _t->setDisplayedPlayer((*reinterpret_cast< Color(*)>(_a[1]))); break;
        case 2: _t->setPlayerName((*reinterpret_cast< Color(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->setCurrentTime((*reinterpret_cast< Color(*)>(_a[1])),(*reinterpret_cast< const QTime(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::ClockWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::ClockWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Knights__ClockWidget,
      qt_meta_data_Knights__ClockWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::ClockWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::ClockWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::ClockWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__ClockWidget))
        return static_cast<void*>(const_cast< ClockWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Knights::ClockWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
