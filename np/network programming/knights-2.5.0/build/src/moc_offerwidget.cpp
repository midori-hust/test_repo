/****************************************************************************
** Meta object code from reading C++ file 'offerwidget.h'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/offerwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'offerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__OfferWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   21,   21,   21, 0x08,
      71,   21,   21,   21, 0x08,
      88,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Knights__OfferWidget[] = {
    "Knights::OfferWidget\0\0id,action\0"
    "close(int,OfferAction)\0acceptClicked()\0"
    "declineClicked()\0closeClicked()\0"
};

void Knights::OfferWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OfferWidget *_t = static_cast<OfferWidget *>(_o);
        switch (_id) {
        case 0: _t->close((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< OfferAction(*)>(_a[2]))); break;
        case 1: _t->acceptClicked(); break;
        case 2: _t->declineClicked(); break;
        case 3: _t->closeClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::OfferWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::OfferWidget::staticMetaObject = {
    { &KMessageWidget::staticMetaObject, qt_meta_stringdata_Knights__OfferWidget,
      qt_meta_data_Knights__OfferWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::OfferWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::OfferWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::OfferWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__OfferWidget))
        return static_cast<void*>(const_cast< OfferWidget*>(this));
    return KMessageWidget::qt_metacast(_clname);
}

int Knights::OfferWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KMessageWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Knights::OfferWidget::close(int _t1, OfferAction _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
