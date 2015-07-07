/****************************************************************************
** Meta object code from reading C++ file 'modeledit.h'
**
** Created: Tue Jun 2 12:24:26 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Interface/modeledit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modeledit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModelEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      26,   10,   10,   10, 0x05,
      47,   10,   10,   10, 0x05,
      71,   65,   10,   10, 0x05,
      94,   10,   10,   10, 0x05,
     114,   10,   10,   10, 0x05,
     129,   10,   10,   10, 0x05,
     149,   10,   10,   10, 0x05,
     165,   10,   10,   10, 0x05,
     181,   10,   10,   10, 0x05,
     199,   10,   10,   10, 0x05,
     216,   10,   10,   10, 0x05,
     236,   10,   10,   10, 0x05,
     252,   10,   10,   10, 0x05,
     268,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     284,   10,   10,   10, 0x0a,
     306,   10,   10,   10, 0x08,
     334,   10,   10,   10, 0x08,
     367,   10,   10,   10, 0x08,
     398,   10,   10,   10, 0x08,
     428,   10,   10,   10, 0x08,
     461,   10,   10,   10, 0x08,
     488,   10,   10,   10, 0x08,
     516,   10,   10,   10, 0x08,
     545,   10,   10,   10, 0x08,
     574,   10,   10,   10, 0x08,
     605,   10,   10,   10, 0x08,
     630,   10,   10,   10, 0x08,
     664,   10,   10,   10, 0x08,
     697,   10,   10,   10, 0x08,
     730,   10,   10,   10, 0x08,
     763,   10,   10,   10, 0x08,
     795,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ModelEdit[] = {
    "ModelEdit\0\0Sig_AddModel()\0"
    "Sig_DuplicateModel()\0Sig_RemoveModel()\0"
    "scale\0Sig_ScaleModel(double)\0"
    "Sig_SelectedModel()\0Sig_RotModel()\0"
    "Sig_ResetRotModel()\0Sig_SnapModel()\0"
    "Sig_MoveModel()\0Sig_ExportModel()\0"
    "Sig_ModelColor()\0Sig_SupZ(QVector3D)\0"
    "Sig_RotX(float)\0Sig_RotY(float)\0"
    "Sig_RotZ(float)\0IsModelSelected(bool)\0"
    "on_AddModelButton_clicked()\0"
    "on_DuplicateModeButton_clicked()\0"
    "on_RemoveModelButton_clicked()\0"
    "on_ModelScaleButton_clicked()\0"
    "on_ModelSelectedButton_clicked()\0"
    "on_RestRotButton_clicked()\0"
    "on_ModelRotButton_clicked()\0"
    "on_ModelSnapButton_clicked()\0"
    "on_ModelMoveButton_clicked()\0"
    "on_ModelExportButton_clicked()\0"
    "on_ColorButton_clicked()\0"
    "on_lineEdit_scale_returnPressed()\0"
    "on_lineEdit_rotx_returnPressed()\0"
    "on_lineEdit_roty_returnPressed()\0"
    "on_lineEdit_rotz_returnPressed()\0"
    "on_SupZ_linedit_returnPressed()\0"
    "on_SupZ_clicked()\0"
};

void ModelEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModelEdit *_t = static_cast<ModelEdit *>(_o);
        switch (_id) {
        case 0: _t->Sig_AddModel(); break;
        case 1: _t->Sig_DuplicateModel(); break;
        case 2: _t->Sig_RemoveModel(); break;
        case 3: _t->Sig_ScaleModel((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->Sig_SelectedModel(); break;
        case 5: _t->Sig_RotModel(); break;
        case 6: _t->Sig_ResetRotModel(); break;
        case 7: _t->Sig_SnapModel(); break;
        case 8: _t->Sig_MoveModel(); break;
        case 9: _t->Sig_ExportModel(); break;
        case 10: _t->Sig_ModelColor(); break;
        case 11: _t->Sig_SupZ((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 12: _t->Sig_RotX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 13: _t->Sig_RotY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->Sig_RotZ((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 15: _t->IsModelSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->on_AddModelButton_clicked(); break;
        case 17: _t->on_DuplicateModeButton_clicked(); break;
        case 18: _t->on_RemoveModelButton_clicked(); break;
        case 19: _t->on_ModelScaleButton_clicked(); break;
        case 20: _t->on_ModelSelectedButton_clicked(); break;
        case 21: _t->on_RestRotButton_clicked(); break;
        case 22: _t->on_ModelRotButton_clicked(); break;
        case 23: _t->on_ModelSnapButton_clicked(); break;
        case 24: _t->on_ModelMoveButton_clicked(); break;
        case 25: _t->on_ModelExportButton_clicked(); break;
        case 26: _t->on_ColorButton_clicked(); break;
        case 27: _t->on_lineEdit_scale_returnPressed(); break;
        case 28: _t->on_lineEdit_rotx_returnPressed(); break;
        case 29: _t->on_lineEdit_roty_returnPressed(); break;
        case 30: _t->on_lineEdit_rotz_returnPressed(); break;
        case 31: _t->on_SupZ_linedit_returnPressed(); break;
        case 32: _t->on_SupZ_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModelEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModelEdit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ModelEdit,
      qt_meta_data_ModelEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModelEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModelEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModelEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModelEdit))
        return static_cast<void*>(const_cast< ModelEdit*>(this));
    return QWidget::qt_metacast(_clname);
}

int ModelEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void ModelEdit::Sig_AddModel()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ModelEdit::Sig_DuplicateModel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ModelEdit::Sig_RemoveModel()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ModelEdit::Sig_ScaleModel(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ModelEdit::Sig_SelectedModel()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ModelEdit::Sig_RotModel()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void ModelEdit::Sig_ResetRotModel()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void ModelEdit::Sig_SnapModel()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void ModelEdit::Sig_MoveModel()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void ModelEdit::Sig_ExportModel()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void ModelEdit::Sig_ModelColor()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void ModelEdit::Sig_SupZ(QVector3D _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ModelEdit::Sig_RotX(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ModelEdit::Sig_RotY(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ModelEdit::Sig_RotZ(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_END_MOC_NAMESPACE
