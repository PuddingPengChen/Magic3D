/****************************************************************************
** Meta object code from reading C++ file 'imageviewwidget.h'
**
** Created: Tue Jun 2 12:24:23 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Interface/imageviewwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageviewwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageViewWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      37,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   58,   16,   16, 0x08,
     105,   97,   16,   16, 0x08,
     139,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ImageViewWidget[] = {
    "ImageViewWidget\0\0Sig_printEditShow()\0"
    "Sig_SliderValue(int)\0value\0"
    "on_LayerSlider_valueChanged(int)\0"
    "storage\0ReceiveStroage(SliceDataStorage*)\0"
    "on_CloseButton_clicked()\0"
};

void ImageViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageViewWidget *_t = static_cast<ImageViewWidget *>(_o);
        switch (_id) {
        case 0: _t->Sig_printEditShow(); break;
        case 1: _t->Sig_SliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_LayerSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->ReceiveStroage((*reinterpret_cast< SliceDataStorage*(*)>(_a[1]))); break;
        case 4: _t->on_CloseButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImageViewWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImageViewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageViewWidget,
      qt_meta_data_ImageViewWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageViewWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageViewWidget))
        return static_cast<void*>(const_cast< ImageViewWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ImageViewWidget::Sig_printEditShow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ImageViewWidget::Sig_SliderValue(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
