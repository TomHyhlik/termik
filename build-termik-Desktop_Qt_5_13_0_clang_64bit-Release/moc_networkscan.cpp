/****************************************************************************
** Meta object code from reading C++ file 'networkscan.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/networkscan.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkscan.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetworkScan_t {
    QByteArrayData data[10];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkScan_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkScan_t qt_meta_stringdata_NetworkScan = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NetworkScan"
QT_MOC_LITERAL(1, 12, 15), // "devAll_finished"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "devThis_finished"
QT_MOC_LITERAL(4, 46, 24), // "ScanAddrDevThis_finished"
QT_MOC_LITERAL(5, 71, 23), // "ScanAddrDevAll_finished"
QT_MOC_LITERAL(6, 95, 17), // "addrs_devThis_add"
QT_MOC_LITERAL(7, 113, 9), // "QHostInfo"
QT_MOC_LITERAL(8, 123, 4), // "host"
QT_MOC_LITERAL(9, 128, 16) // "addrs_devAll_add"

    },
    "NetworkScan\0devAll_finished\0\0"
    "devThis_finished\0ScanAddrDevThis_finished\0"
    "ScanAddrDevAll_finished\0addrs_devThis_add\0"
    "QHostInfo\0host\0addrs_devAll_add"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkScan[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x08 /* Private */,
       9,    1,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void NetworkScan::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkScan *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->devAll_finished(); break;
        case 1: _t->devThis_finished(); break;
        case 2: _t->ScanAddrDevThis_finished(); break;
        case 3: _t->ScanAddrDevAll_finished(); break;
        case 4: _t->addrs_devThis_add((*reinterpret_cast< QHostInfo(*)>(_a[1]))); break;
        case 5: _t->addrs_devAll_add((*reinterpret_cast< QHostInfo(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHostInfo >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHostInfo >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetworkScan::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkScan::devAll_finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NetworkScan::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkScan::devThis_finished)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NetworkScan::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_NetworkScan.data,
    qt_meta_data_NetworkScan,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NetworkScan::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkScan::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkScan.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetworkScan::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void NetworkScan::devAll_finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NetworkScan::devThis_finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_ScanAddr_t {
    QByteArrayData data[4];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanAddr_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanAddr_t qt_meta_stringdata_ScanAddr = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ScanAddr"
QT_MOC_LITERAL(1, 9, 9), // "foundAddr"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 9) // "QHostInfo"

    },
    "ScanAddr\0foundAddr\0\0QHostInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanAddr[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void ScanAddr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScanAddr *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->foundAddr((*reinterpret_cast< QHostInfo(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHostInfo >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScanAddr::*)(QHostInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanAddr::foundAddr)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScanAddr::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_ScanAddr.data,
    qt_meta_data_ScanAddr,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScanAddr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanAddr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScanAddr.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ScanAddr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ScanAddr::foundAddr(QHostInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ScanAddrDevThis_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanAddrDevThis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanAddrDevThis_t qt_meta_stringdata_ScanAddrDevThis = {
    {
QT_MOC_LITERAL(0, 0, 15) // "ScanAddrDevThis"

    },
    "ScanAddrDevThis"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanAddrDevThis[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ScanAddrDevThis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ScanAddrDevThis::staticMetaObject = { {
    &ScanAddr::staticMetaObject,
    qt_meta_stringdata_ScanAddrDevThis.data,
    qt_meta_data_ScanAddrDevThis,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScanAddrDevThis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanAddrDevThis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScanAddrDevThis.stringdata0))
        return static_cast<void*>(this);
    return ScanAddr::qt_metacast(_clname);
}

int ScanAddrDevThis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ScanAddr::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ScanAddrDevAll_t {
    QByteArrayData data[6];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanAddrDevAll_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanAddrDevAll_t qt_meta_stringdata_ScanAddrDevAll = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ScanAddrDevAll"
QT_MOC_LITERAL(1, 15, 8), // "finished"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 17), // "lookupHost_result"
QT_MOC_LITERAL(4, 43, 9), // "QHostInfo"
QT_MOC_LITERAL(5, 53, 4) // "host"

    },
    "ScanAddrDevAll\0finished\0\0lookupHost_result\0"
    "QHostInfo\0host"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanAddrDevAll[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   25,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void ScanAddrDevAll::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScanAddrDevAll *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->lookupHost_result((*reinterpret_cast< QHostInfo(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHostInfo >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ScanAddrDevAll::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScanAddrDevAll::finished)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScanAddrDevAll::staticMetaObject = { {
    &ScanAddr::staticMetaObject,
    qt_meta_stringdata_ScanAddrDevAll.data,
    qt_meta_data_ScanAddrDevAll,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScanAddrDevAll::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanAddrDevAll::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScanAddrDevAll.stringdata0))
        return static_cast<void*>(this);
    return ScanAddr::qt_metacast(_clname);
}

int ScanAddrDevAll::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ScanAddr::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ScanAddrDevAll::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
