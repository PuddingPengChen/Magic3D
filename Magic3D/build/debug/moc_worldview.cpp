/****************************************************************************
** Meta object code from reading C++ file 'worldview.h'
**
** Created: Tue Jun 2 14:24:24 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Interface/worldview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worldview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WorldView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   11,   10,   10, 0x05,
      39,   11,   10,   10, 0x05,
      61,   11,   10,   10, 0x05,
      83,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     107,   10,   10,   10, 0x0a,
     120,   10,   10,   10, 0x0a,
     130,   10,   10,   10, 0x0a,
     142,   10,   10,   10, 0x0a,
     154,   10,   10,   10, 0x0a,
     165,   10,   10,   10, 0x0a,
     176,   10,   10,   10, 0x0a,
     195,  189,   10,   10, 0x0a,
     221,  215,   10,   10, 0x0a,
     252,  248,   10,   10, 0x0a,
     275,  270,   10,   10, 0x0a,
     291,   11,   10,   10, 0x0a,
     311,   11,   10,   10, 0x0a,
     331,   11,   10,   10, 0x0a,
     354,  351,   10,   10, 0x0a,
     373,   10,   10,   10, 0x0a,
     393,   10,   10,   10, 0x0a,
     410,   10,   10,   10, 0x0a,
     428,  423,   10,   10, 0x0a,
     453,   10,  445,   10, 0x0a,
     463,   10,   10,   10, 0x0a,
     480,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WorldView[] = {
    "WorldView\0\0angle\0xRotationChanged(int)\0"
    "yRotationChanged(int)\0zRotationChanged(int)\0"
    "Sig_modelSelected(bool)\0CenterView()\0"
    "TopView()\0RightView()\0FrontView()\0"
    "BackView()\0LeftView()\0BottomView()\0"
    "persp\0SetPerpective(bool)\0point\0"
    "SetRevolvePoint(QVector3D)\0pan\0"
    "SetPan(QVector3D)\0zoom\0SetZoom(double)\0"
    "setXRotation(float)\0setYRotation(float)\0"
    "setZRotation(float)\0la\0setLayerValue(int)\0"
    "UpdatePlasmaFence()\0UpdateVisSlice()\0"
    "UpdateTick()\0tool\0SetTool(QString)\0"
    "QString\0GetTool()\0ExitToolAction()\0"
    "AutoSupport()\0"
};

void WorldView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WorldView *_t = static_cast<WorldView *>(_o);
        switch (_id) {
        case 0: _t->xRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->yRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->zRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->Sig_modelSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->CenterView(); break;
        case 5: _t->TopView(); break;
        case 6: _t->RightView(); break;
        case 7: _t->FrontView(); break;
        case 8: _t->BackView(); break;
        case 9: _t->LeftView(); break;
        case 10: _t->BottomView(); break;
        case 11: _t->SetPerpective((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->SetRevolvePoint((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 13: _t->SetPan((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 14: _t->SetZoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->setXRotation((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 16: _t->setYRotation((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 17: _t->setZRotation((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 18: _t->setLayerValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->UpdatePlasmaFence(); break;
        case 20: _t->UpdateVisSlice(); break;
        case 21: _t->UpdateTick(); break;
        case 22: _t->SetTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: { QString _r = _t->GetTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 24: _t->ExitToolAction(); break;
        case 25: _t->AutoSupport(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WorldView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WorldView::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_WorldView,
      qt_meta_data_WorldView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WorldView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WorldView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WorldView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WorldView))
        return static_cast<void*>(const_cast< WorldView*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int WorldView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void WorldView::xRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WorldView::yRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WorldView::zRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WorldView::Sig_modelSelected(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
