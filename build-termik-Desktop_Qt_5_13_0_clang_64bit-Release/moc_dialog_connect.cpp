/****************************************************************************
** Meta object code from reading C++ file 'dialog_connect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/dialog_connect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_connect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_connect_t {
    QByteArrayData data[23];
    char stringdata0[372];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_connect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_connect_t qt_meta_stringdata_Dialog_connect = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Dialog_connect"
QT_MOC_LITERAL(1, 15, 17), // "connectVia_serial"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 14), // "serialPortName"
QT_MOC_LITERAL(4, 49, 10), // "tryConnect"
QT_MOC_LITERAL(5, 60, 3), // "log"
QT_MOC_LITERAL(6, 64, 20), // "networkHosts_refresh"
QT_MOC_LITERAL(7, 85, 22), // "serialPort_nameRefresh"
QT_MOC_LITERAL(8, 108, 14), // "refreshDevices"
QT_MOC_LITERAL(9, 123, 39), // "on_comboBox_portName_currentT..."
QT_MOC_LITERAL(10, 163, 4), // "arg1"
QT_MOC_LITERAL(11, 168, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(12, 196, 5), // "index"
QT_MOC_LITERAL(13, 202, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(14, 224, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(15, 246, 7), // "focus_1"
QT_MOC_LITERAL(16, 254, 7), // "focus_2"
QT_MOC_LITERAL(17, 262, 17), // "refreshParameters"
QT_MOC_LITERAL(18, 280, 10), // "EscPressed"
QT_MOC_LITERAL(19, 291, 34), // "on_tableWidget_addr_tx_cellCl..."
QT_MOC_LITERAL(20, 326, 3), // "row"
QT_MOC_LITERAL(21, 330, 6), // "column"
QT_MOC_LITERAL(22, 337, 34) // "on_tableWidget_addr_rx_cellCl..."

    },
    "Dialog_connect\0connectVia_serial\0\0"
    "serialPortName\0tryConnect\0log\0"
    "networkHosts_refresh\0serialPort_nameRefresh\0"
    "refreshDevices\0on_comboBox_portName_currentTextChanged\0"
    "arg1\0on_tabWidget_currentChanged\0index\0"
    "on_buttonBox_accepted\0on_buttonBox_rejected\0"
    "focus_1\0focus_2\0refreshParameters\0"
    "EscPressed\0on_tableWidget_addr_tx_cellClicked\0"
    "row\0column\0on_tableWidget_addr_rx_cellClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_connect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       5,    2,  100,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  105,    2, 0x08 /* Private */,
       7,    0,  106,    2, 0x08 /* Private */,
       8,    0,  107,    2, 0x08 /* Private */,
       9,    1,  108,    2, 0x08 /* Private */,
      11,    1,  111,    2, 0x08 /* Private */,
      13,    0,  114,    2, 0x08 /* Private */,
      14,    0,  115,    2, 0x08 /* Private */,
      15,    0,  116,    2, 0x08 /* Private */,
      16,    0,  117,    2, 0x08 /* Private */,
      17,    0,  118,    2, 0x08 /* Private */,
      18,    0,  119,    2, 0x08 /* Private */,
      19,    2,  120,    2, 0x08 /* Private */,
      22,    2,  125,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   21,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   21,

       0        // eod
};

void Dialog_connect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dialog_connect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectVia_serial((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->tryConnect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->log((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->networkHosts_refresh(); break;
        case 4: _t->serialPort_nameRefresh(); break;
        case 5: _t->refreshDevices(); break;
        case 6: _t->on_comboBox_portName_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_buttonBox_accepted(); break;
        case 9: _t->on_buttonBox_rejected(); break;
        case 10: _t->focus_1(); break;
        case 11: _t->focus_2(); break;
        case 12: _t->refreshParameters(); break;
        case 13: _t->EscPressed(); break;
        case 14: _t->on_tableWidget_addr_tx_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->on_tableWidget_addr_rx_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialog_connect::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_connect::connectVia_serial)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Dialog_connect::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_connect::tryConnect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Dialog_connect::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_connect::log)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog_connect::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Dialog_connect.data,
    qt_meta_data_Dialog_connect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Dialog_connect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_connect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_connect.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog_connect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Dialog_connect::connectVia_serial(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Dialog_connect::tryConnect(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Dialog_connect::log(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
