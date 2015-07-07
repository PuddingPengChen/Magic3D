/****************************************************************************
** Meta object code from reading C++ file 'mainbutton.h'
**
** Created: Tue Jun 2 12:24:25 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Interface/mainbutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      28,   11,   11,   11, 0x05,
      46,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   11,   11,   11, 0x08,
      87,   11,   11,   11, 0x08,
     112,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainButton[] = {
    "MainButton\0\0Sig_ModelMode()\0"
    "Sig_SupportMode()\0Sig_PrintMode()\0"
    "on_ModelButton_clicked()\0"
    "on_SupportMode_clicked()\0"
    "on_PrintMode_clicked()\0"
};

void MainButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainButton *_t = static_cast<MainButton *>(_o);
        switch (_id) {
        case 0: _t->Sig_ModelMode(); break;
        case 1: _t->Sig_SupportMode(); break;
        case 2: _t->Sig_PrintMode(); break;
        case 3: _t->on_ModelButton_clicked(); break;
        case 4: _t->on_SupportMode_clicked(); break;
        case 5: _t->on_PrintMode_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainButton::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainButton,
      qt_meta_data_MainButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainButton))
        return static_cast<void*>(const_cast< MainButton*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MainButton::Sig_ModelMode()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainButton::Sig_SupportMode()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainButton::Sig_PrintMode()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
