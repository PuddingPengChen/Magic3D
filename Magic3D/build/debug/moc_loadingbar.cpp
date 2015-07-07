/****************************************************************************
** Meta object code from reading C++ file 'loadingbar.h'
**
** Created: Tue Jun 2 12:24:24 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Interface/loadingbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loadingbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoadingBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x0a,
      32,   28,   11,   11, 0x0a,
      48,   44,   11,   11, 0x0a,
      66,   62,   11,   11, 0x0a,
     105,   90,   11,   11, 0x0a,
     136,  132,   11,   11, 0x0a,
     162,   11,  158,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoadingBar[] = {
    "LoadingBar\0\0max\0setMax(int)\0min\0"
    "setMin(int)\0val\0setValue(int)\0str\0"
    "setDescription(QString)\0fraction,total\0"
    "setProgress(qint64,qint64)\0use\0"
    "useCancelButton(bool)\0int\0GetValue()\0"
};

void LoadingBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoadingBar *_t = static_cast<LoadingBar *>(_o);
        switch (_id) {
        case 0: _t->setMax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setMin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setDescription((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->setProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: _t->useCancelButton((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: { int _r = _t->GetValue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LoadingBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoadingBar::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LoadingBar,
      qt_meta_data_LoadingBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoadingBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoadingBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoadingBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoadingBar))
        return static_cast<void*>(const_cast< LoadingBar*>(this));
    return QDialog::qt_metacast(_clname);
}

int LoadingBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
