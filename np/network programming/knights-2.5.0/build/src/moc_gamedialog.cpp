/****************************************************************************
** Meta object code from reading C++ file 'gamedialog.h'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/gamedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__GameDialog[] = {

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
      21,   20,   20,   20, 0x08,
      46,   39,   20,   20, 0x08,
      93,   20,   20,   20, 0x08,
     107,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Knights__GameDialog[] = {
    "Knights::GameDialog\0\0updateTimeEdits()\0"
    "status\0changeNetworkStatus(Solid::Networking::Status)\0"
    "loadEngines()\0showEngineConfigDialog()\0"
};

void Knights::GameDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GameDialog *_t = static_cast<GameDialog *>(_o);
        switch (_id) {
        case 0: _t->updateTimeEdits(); break;
        case 1: _t->changeNetworkStatus((*reinterpret_cast< Solid::Networking::Status(*)>(_a[1]))); break;
        case 2: _t->loadEngines(); break;
        case 3: _t->showEngineConfigDialog(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Knights::GameDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::GameDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Knights__GameDialog,
      qt_meta_data_Knights__GameDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::GameDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::GameDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::GameDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__GameDialog))
        return static_cast<void*>(const_cast< GameDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int Knights::GameDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
