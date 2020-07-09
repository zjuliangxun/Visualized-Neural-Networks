/****************************************************************************
** Meta object code from reading C++ file 'visualized_neural_networks.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Visualized_Neural_Networks/visualized_neural_networks.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visualized_neural_networks.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Visualized_Neural_Networks_t {
    QByteArrayData data[8];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Visualized_Neural_Networks_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Visualized_Neural_Networks_t qt_meta_stringdata_Visualized_Neural_Networks = {
    {
QT_MOC_LITERAL(0, 0, 26), // "Visualized_Neural_Networks"
QT_MOC_LITERAL(1, 27, 13), // "AddNeuronNone"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 16), // "AddNeuronSigmoid"
QT_MOC_LITERAL(4, 59, 13), // "AddNeuronRelu"
QT_MOC_LITERAL(5, 73, 13), // "AddNeuronTanh"
QT_MOC_LITERAL(6, 87, 15), // "AddNeuronTarget"
QT_MOC_LITERAL(7, 103, 6) // "Select"

    },
    "Visualized_Neural_Networks\0AddNeuronNone\0"
    "\0AddNeuronSigmoid\0AddNeuronRelu\0"
    "AddNeuronTanh\0AddNeuronTarget\0Select"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Visualized_Neural_Networks[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Visualized_Neural_Networks::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Visualized_Neural_Networks *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddNeuronNone(); break;
        case 1: _t->AddNeuronSigmoid(); break;
        case 2: _t->AddNeuronRelu(); break;
        case 3: _t->AddNeuronTanh(); break;
        case 4: _t->AddNeuronTarget(); break;
        case 5: _t->Select(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Visualized_Neural_Networks::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Visualized_Neural_Networks.data,
    qt_meta_data_Visualized_Neural_Networks,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Visualized_Neural_Networks::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Visualized_Neural_Networks::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Visualized_Neural_Networks.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Visualized_Neural_Networks::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
