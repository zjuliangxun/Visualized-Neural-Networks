/****************************************************************************
** Meta object code from reading C++ file 'NetView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/view/NetView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NetView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetView_t {
    QByteArrayData data[17];
    char stringdata0[323];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetView_t qt_meta_stringdata_NetView = {
    {
QT_MOC_LITERAL(0, 0, 7), // "NetView"
QT_MOC_LITERAL(1, 8, 21), // "select_button_clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 21), // "neuron_button_clicked"
QT_MOC_LITERAL(4, 53, 22), // "sigmoid_button_clicked"
QT_MOC_LITERAL(5, 76, 19), // "relu_button_clicked"
QT_MOC_LITERAL(6, 96, 19), // "tanh_button_clicked"
QT_MOC_LITERAL(7, 116, 21), // "target_button_clicked"
QT_MOC_LITERAL(8, 138, 20), // "calc_forward_clicked"
QT_MOC_LITERAL(9, 159, 21), // "calc_gradient_clicked"
QT_MOC_LITERAL(10, 181, 21), // "prop_gradient_clicked"
QT_MOC_LITERAL(11, 203, 22), // "update_weights_clicked"
QT_MOC_LITERAL(12, 226, 16), // "backprop_clicked"
QT_MOC_LITERAL(13, 243, 21), // "delete_button_clicked"
QT_MOC_LITERAL(14, 265, 19), // "change_neuron_value"
QT_MOC_LITERAL(15, 285, 17), // "QPair<int,double>"
QT_MOC_LITERAL(16, 303, 19) // "change_weight_value"

    },
    "NetView\0select_button_clicked\0\0"
    "neuron_button_clicked\0sigmoid_button_clicked\0"
    "relu_button_clicked\0tanh_button_clicked\0"
    "target_button_clicked\0calc_forward_clicked\0"
    "calc_gradient_clicked\0prop_gradient_clicked\0"
    "update_weights_clicked\0backprop_clicked\0"
    "delete_button_clicked\0change_neuron_value\0"
    "QPair<int,double>\0change_weight_value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    1,   96,    2, 0x08 /* Private */,
      16,    1,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 15,    2,

       0        // eod
};

void NetView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->select_button_clicked(); break;
        case 1: _t->neuron_button_clicked(); break;
        case 2: _t->sigmoid_button_clicked(); break;
        case 3: _t->relu_button_clicked(); break;
        case 4: _t->tanh_button_clicked(); break;
        case 5: _t->target_button_clicked(); break;
        case 6: _t->calc_forward_clicked(); break;
        case 7: _t->calc_gradient_clicked(); break;
        case 8: _t->prop_gradient_clicked(); break;
        case 9: _t->update_weights_clicked(); break;
        case 10: _t->backprop_clicked(); break;
        case 11: _t->delete_button_clicked(); break;
        case 12: _t->change_neuron_value((*reinterpret_cast< QPair<int,double>(*)>(_a[1]))); break;
        case 13: _t->change_weight_value((*reinterpret_cast< QPair<int,double>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NetView::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_NetView.data,
    qt_meta_data_NetView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NetView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetView.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int NetView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
