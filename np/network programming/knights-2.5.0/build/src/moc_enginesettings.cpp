/****************************************************************************
** Meta object code from reading C++ file 'enginesettings.h'
**
** Created: Thu Sep 26 16:52:38 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/enginesettings.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'enginesettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Knights__EngineSettings[] = {

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
      25,   24,   24,   24, 0x0a,
      38,   24,   24,   24, 0x0a,
      54,   24,   24,   24, 0x0a,
      71,   24,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Knights__EngineSettings[] = {
    "Knights::EngineSettings\0\0addClicked()\0"
    "removeClicked()\0checkInstalled()\0"
    "writeConfig()\0"
};

void Knights::EngineSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EngineSettings *_t = static_cast<EngineSettings *>(_o);
        switch (_id) {
        case 0: _t->addClicked(); break;
        case 1: _t->removeClicked(); break;
        case 2: _t->checkInstalled(); break;
        case 3: _t->writeConfig(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Knights::EngineSettings::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Knights::EngineSettings::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Knights__EngineSettings,
      qt_meta_data_Knights__EngineSettings, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Knights::EngineSettings::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Knights::EngineSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Knights::EngineSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Knights__EngineSettings))
        return static_cast<void*>(const_cast< EngineSettings*>(this));
    return QWidget::qt_metacast(_clname);
}

int Knights::EngineSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
