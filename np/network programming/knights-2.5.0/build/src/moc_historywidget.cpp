/****************************************************************************
** Meta object code from reading C++ file 'historywidget.h'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/historywidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'historywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__HistoryWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      47,   38,   23,   23, 0x08,
      91,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Knights__HistoryWidget[] = {
    "Knights::HistoryWidget\0\0updateModel()\0"
    "notation\0updateModelStandardNotation(Move::Notation)\0"
    "saveHistory()\0"
};

void Knights::HistoryWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HistoryWidget *_t = static_cast<HistoryWidget *>(_o);
        switch (_id) {
        case 0: _t->updateModel(); break;
        case 1: _t->updateModelStandardNotation((*reinterpret_cast< Move::Notation(*)>(_a[1]))); break;
        case 2: _t->saveHistory(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::HistoryWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::HistoryWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Knights__HistoryWidget,
      qt_meta_data_Knights__HistoryWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::HistoryWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::HistoryWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::HistoryWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__HistoryWidget))
        return static_cast<void*>(const_cast< HistoryWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Knights::HistoryWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
