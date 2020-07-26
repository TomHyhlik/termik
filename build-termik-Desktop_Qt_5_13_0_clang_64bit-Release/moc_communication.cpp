/****************************************************************************
** Meta object code from reading C++ file 'communication.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/communication.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'communication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Communication_t {
    QByteArrayData data[14];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Communication_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Communication_t qt_meta_stringdata_Communication = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Communication"
QT_MOC_LITERAL(1, 14, 9), // "connected"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "disconnected"
QT_MOC_LITERAL(4, 38, 11), // "displayData"
QT_MOC_LITERAL(5, 50, 19), // "established_success"
QT_MOC_LITERAL(6, 70, 18), // "established_failed"
QT_MOC_LITERAL(7, 89, 9), // "establish"
QT_MOC_LITERAL(8, 99, 17), // "communicationType"
QT_MOC_LITERAL(9, 117, 21), // "establishPrintResults"
QT_MOC_LITERAL(10, 139, 7), // "success"
QT_MOC_LITERAL(11, 147, 4), // "type"
QT_MOC_LITERAL(12, 152, 12), // "dataTransmit"
QT_MOC_LITERAL(13, 165, 11) // "dataArrived"

    },
    "Communication\0connected\0\0disconnected\0"
    "displayData\0established_success\0"
    "established_failed\0establish\0"
    "communicationType\0establishPrintResults\0"
    "success\0type\0dataTransmit\0dataArrived"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Communication[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    2,   66,    2, 0x06 /* Public */,
       5,    0,   71,    2, 0x06 /* Public */,
       6,    0,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   73,    2, 0x0a /* Public */,
       7,    1,   74,    2, 0x0a /* Public */,
       9,    2,   77,    2, 0x0a /* Public */,
      12,    1,   82,    2, 0x0a /* Public */,
      13,    1,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QByteArray,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 8,   10,   11,
    QMetaType::Bool, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,

       0        // eod
};

void Communication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Communication *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->displayData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 3: _t->established_success(); break;
        case 4: _t->established_failed(); break;
        case 5: _t->establish(); break;
        case 6: _t->establish((*reinterpret_cast< communicationType(*)>(_a[1]))); break;
        case 7: _t->establishPrintResults((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< communicationType(*)>(_a[2]))); break;
        case 8: { bool _r = _t->dataTransmit((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->dataArrived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Communication::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Communication::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Communication::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Communication::disconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Communication::*)(int , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Communication::displayData)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Communication::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Communication::established_success)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Communication::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Communication::established_failed)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Communication::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Communication.data,
    qt_meta_data_Communication,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Communication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Communication::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Communication.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Communication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Communication::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Communication::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Communication::displayData(int _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Communication::established_success()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Communication::established_failed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
