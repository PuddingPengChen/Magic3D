/****************************************************************************
** Meta object code from reading C++ file 'printedit.h'
**
** Created: Tue Jun 2 14:24:21 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Interface/printedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'printedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileTransmit_Thread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_FileTransmit_Thread[] = {
    "FileTransmit_Thread\0\0TransmitFinished()\0"
};

void FileTransmit_Thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileTransmit_Thread *_t = static_cast<FileTransmit_Thread *>(_o);
        switch (_id) {
        case 0: _t->TransmitFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData FileTransmit_Thread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FileTransmit_Thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FileTransmit_Thread,
      qt_meta_data_FileTransmit_Thread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileTransmit_Thread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileTransmit_Thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileTransmit_Thread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileTransmit_Thread))
        return static_cast<void*>(const_cast< FileTransmit_Thread*>(this));
    return QThread::qt_metacast(_clname);
}

int FileTransmit_Thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void FileTransmit_Thread::TransmitFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_PrintEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   11,   10,   10, 0x05,
      36,   10,   10,   10, 0x05,
      48,   10,   10,   10, 0x05,
      67,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      89,   10,   10,   10, 0x08,
     114,   10,   10,   10, 0x08,
     139,   10,   10,   10, 0x08,
     166,   10,   10,   10, 0x08,
     191,   10,   10,   10, 0x08,
     220,   10,   10,   10, 0x08,
     247,   10,   10,   10, 0x08,
     272,   10,   10,   10, 0x08,
     304,  301,  296,   10, 0x08,
     325,   10,   10,   10, 0x08,
     341,   10,   10,   10, 0x08,
     360,   10,   10,   10, 0x08,
     397,  380,  372,   10, 0x08,
     418,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PrintEdit[] = {
    "PrintEdit\0\0show\0Sig_ImageShow(bool)\0"
    "Sig_Slice()\0Sig_Thickness(int)\0"
    "Sig_ComError(QString)\0on_ImageButton_clicked()\0"
    "on_SliceButton_clicked()\0"
    "on_ConnectButton_clicked()\0"
    "on_PrintButton_clicked()\0"
    "on_StopPrintButton_clicked()\0"
    "on_RecoverButton_clicked()\0"
    "on_ResetButton_clicked()\0"
    "on_toolButton_clicked()\0bool\0ip\0"
    "IsIPaddress(QString)\0HostConnected()\0"
    "HostDisconnected()\0HostError()\0QString\0"
    "index,keyorvalue\0getcomm(int,QString)\0"
    "init_comm()\0"
};

void PrintEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PrintEdit *_t = static_cast<PrintEdit *>(_o);
        switch (_id) {
        case 0: _t->Sig_ImageShow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->Sig_Slice(); break;
        case 2: _t->Sig_Thickness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->Sig_ComError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->on_ImageButton_clicked(); break;
        case 5: _t->on_SliceButton_clicked(); break;
        case 6: _t->on_ConnectButton_clicked(); break;
        case 7: _t->on_PrintButton_clicked(); break;
        case 8: _t->on_StopPrintButton_clicked(); break;
        case 9: _t->on_RecoverButton_clicked(); break;
        case 10: _t->on_ResetButton_clicked(); break;
        case 11: _t->on_toolButton_clicked(); break;
        case 12: { bool _r = _t->IsIPaddress((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->HostConnected(); break;
        case 14: _t->HostDisconnected(); break;
        case 15: _t->HostError(); break;
        case 16: { QString _r = _t->getcomm((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: _t->init_comm(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PrintEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PrintEdit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PrintEdit,
      qt_meta_data_PrintEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PrintEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PrintEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PrintEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PrintEdit))
        return static_cast<void*>(const_cast< PrintEdit*>(this));
    return QWidget::qt_metacast(_clname);
}

int PrintEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void PrintEdit::Sig_ImageShow(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PrintEdit::Sig_Slice()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PrintEdit::Sig_Thickness(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PrintEdit::Sig_ComError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
