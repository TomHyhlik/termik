/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[47];
    char stringdata0[940];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "dataArrived"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "EscPressed"
QT_MOC_LITERAL(4, 35, 15), // "moveCursorToEnd"
QT_MOC_LITERAL(5, 51, 10), // "showFindUi"
QT_MOC_LITERAL(6, 62, 10), // "hideFindUi"
QT_MOC_LITERAL(7, 73, 21), // "terminalInputSetFocus"
QT_MOC_LITERAL(8, 95, 22), // "showConnectionSettings"
QT_MOC_LITERAL(9, 118, 11), // "clearOutput"
QT_MOC_LITERAL(10, 130, 7), // "focus_1"
QT_MOC_LITERAL(11, 138, 7), // "focus_2"
QT_MOC_LITERAL(12, 146, 7), // "focus_3"
QT_MOC_LITERAL(13, 154, 18), // "toggleShowSettings"
QT_MOC_LITERAL(14, 173, 8), // "showHelp"
QT_MOC_LITERAL(15, 182, 8), // "hideHelp"
QT_MOC_LITERAL(16, 191, 12), // "showScriptUi"
QT_MOC_LITERAL(17, 204, 12), // "hideScriptUi"
QT_MOC_LITERAL(18, 217, 12), // "keyUpPressed"
QT_MOC_LITERAL(19, 230, 14), // "keyDownPressed"
QT_MOC_LITERAL(20, 245, 15), // "keyEnterPressed"
QT_MOC_LITERAL(21, 261, 5), // "on_Tx"
QT_MOC_LITERAL(22, 267, 16), // "Tx_fromDataInput"
QT_MOC_LITERAL(23, 284, 15), // "historyTxUpdate"
QT_MOC_LITERAL(24, 300, 12), // "selectScript"
QT_MOC_LITERAL(25, 313, 31), // "on_checkBox_prefix_stateChanged"
QT_MOC_LITERAL(26, 345, 4), // "arg1"
QT_MOC_LITERAL(27, 350, 31), // "on_checkBox_suffix_stateChanged"
QT_MOC_LITERAL(28, 382, 30), // "on_lineEdit_suffix_textChanged"
QT_MOC_LITERAL(29, 413, 30), // "on_lineEdit_prefix_textChanged"
QT_MOC_LITERAL(30, 444, 32), // "on_checkBox_timeLog_stateChanged"
QT_MOC_LITERAL(31, 477, 40), // "on_checkBox_clearOutputLine_s..."
QT_MOC_LITERAL(32, 518, 35), // "on_checkBox_outputSave_stateC..."
QT_MOC_LITERAL(33, 554, 30), // "on_lineEdit_script_textChanged"
QT_MOC_LITERAL(34, 585, 37), // "on_spinBox_script_period_valu..."
QT_MOC_LITERAL(35, 623, 32), // "on_pushButton_script_run_clicked"
QT_MOC_LITERAL(36, 656, 43), // "on_comboBox_script_dataType_e..."
QT_MOC_LITERAL(37, 700, 38), // "on_checkBox_script_repeat_sta..."
QT_MOC_LITERAL(38, 739, 26), // "on_pushButton_save_clicked"
QT_MOC_LITERAL(39, 766, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(40, 794, 5), // "index"
QT_MOC_LITERAL(41, 800, 28), // "on_lineEdit_save_textChanged"
QT_MOC_LITERAL(42, 829, 29), // "moveCursorToTerminalInputLine"
QT_MOC_LITERAL(43, 859, 21), // "currentAppConfig_save"
QT_MOC_LITERAL(44, 881, 21), // "currentAppConfig_load"
QT_MOC_LITERAL(45, 903, 19), // "connectOrDisconnect"
QT_MOC_LITERAL(46, 923, 16) // "tryConnectDevice"

    },
    "MainWindow\0dataArrived\0\0EscPressed\0"
    "moveCursorToEnd\0showFindUi\0hideFindUi\0"
    "terminalInputSetFocus\0showConnectionSettings\0"
    "clearOutput\0focus_1\0focus_2\0focus_3\0"
    "toggleShowSettings\0showHelp\0hideHelp\0"
    "showScriptUi\0hideScriptUi\0keyUpPressed\0"
    "keyDownPressed\0keyEnterPressed\0on_Tx\0"
    "Tx_fromDataInput\0historyTxUpdate\0"
    "selectScript\0on_checkBox_prefix_stateChanged\0"
    "arg1\0on_checkBox_suffix_stateChanged\0"
    "on_lineEdit_suffix_textChanged\0"
    "on_lineEdit_prefix_textChanged\0"
    "on_checkBox_timeLog_stateChanged\0"
    "on_checkBox_clearOutputLine_stateChanged\0"
    "on_checkBox_outputSave_stateChanged\0"
    "on_lineEdit_script_textChanged\0"
    "on_spinBox_script_period_valueChanged\0"
    "on_pushButton_script_run_clicked\0"
    "on_comboBox_script_dataType_editTextChanged\0"
    "on_checkBox_script_repeat_stateChanged\0"
    "on_pushButton_save_clicked\0"
    "on_tabWidget_currentChanged\0index\0"
    "on_lineEdit_save_textChanged\0"
    "moveCursorToTerminalInputLine\0"
    "currentAppConfig_save\0currentAppConfig_load\0"
    "connectOrDisconnect\0tryConnectDevice"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  229,    2, 0x08 /* Private */,
       3,    0,  230,    2, 0x08 /* Private */,
       4,    0,  231,    2, 0x08 /* Private */,
       5,    0,  232,    2, 0x08 /* Private */,
       6,    0,  233,    2, 0x08 /* Private */,
       7,    0,  234,    2, 0x08 /* Private */,
       8,    0,  235,    2, 0x08 /* Private */,
       9,    0,  236,    2, 0x08 /* Private */,
      10,    0,  237,    2, 0x08 /* Private */,
      11,    0,  238,    2, 0x08 /* Private */,
      12,    0,  239,    2, 0x08 /* Private */,
      13,    0,  240,    2, 0x08 /* Private */,
      14,    0,  241,    2, 0x08 /* Private */,
      15,    0,  242,    2, 0x08 /* Private */,
      16,    0,  243,    2, 0x08 /* Private */,
      17,    0,  244,    2, 0x08 /* Private */,
      18,    0,  245,    2, 0x08 /* Private */,
      19,    0,  246,    2, 0x08 /* Private */,
      20,    0,  247,    2, 0x08 /* Private */,
      21,    1,  248,    2, 0x08 /* Private */,
      22,    1,  251,    2, 0x08 /* Private */,
      23,    0,  254,    2, 0x08 /* Private */,
      24,    0,  255,    2, 0x08 /* Private */,
      25,    1,  256,    2, 0x08 /* Private */,
      27,    1,  259,    2, 0x08 /* Private */,
      28,    1,  262,    2, 0x08 /* Private */,
      29,    1,  265,    2, 0x08 /* Private */,
      30,    1,  268,    2, 0x08 /* Private */,
      31,    1,  271,    2, 0x08 /* Private */,
      32,    1,  274,    2, 0x08 /* Private */,
      33,    1,  277,    2, 0x08 /* Private */,
      34,    1,  280,    2, 0x08 /* Private */,
      35,    0,  283,    2, 0x08 /* Private */,
      36,    1,  284,    2, 0x08 /* Private */,
      37,    1,  287,    2, 0x08 /* Private */,
      38,    0,  290,    2, 0x08 /* Private */,
      39,    1,  291,    2, 0x08 /* Private */,
      41,    1,  294,    2, 0x08 /* Private */,
      42,    0,  297,    2, 0x08 /* Private */,
      43,    0,  298,    2, 0x08 /* Private */,
      44,    0,  299,    2, 0x08 /* Private */,
      45,    0,  300,    2, 0x08 /* Private */,
      46,    1,  301,    2, 0x0a /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataArrived(); break;
        case 1: _t->EscPressed(); break;
        case 2: _t->moveCursorToEnd(); break;
        case 3: _t->showFindUi(); break;
        case 4: _t->hideFindUi(); break;
        case 5: _t->terminalInputSetFocus(); break;
        case 6: _t->showConnectionSettings(); break;
        case 7: _t->clearOutput(); break;
        case 8: _t->focus_1(); break;
        case 9: _t->focus_2(); break;
        case 10: _t->focus_3(); break;
        case 11: _t->toggleShowSettings(); break;
        case 12: _t->showHelp(); break;
        case 13: _t->hideHelp(); break;
        case 14: _t->showScriptUi(); break;
        case 15: _t->hideScriptUi(); break;
        case 16: _t->keyUpPressed(); break;
        case 17: _t->keyDownPressed(); break;
        case 18: _t->keyEnterPressed(); break;
        case 19: _t->on_Tx((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 20: _t->Tx_fromDataInput((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->historyTxUpdate(); break;
        case 22: _t->selectScript(); break;
        case 23: _t->on_checkBox_prefix_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_checkBox_suffix_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->on_lineEdit_suffix_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: _t->on_lineEdit_prefix_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 27: _t->on_checkBox_timeLog_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->on_checkBox_clearOutputLine_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->on_checkBox_outputSave_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->on_lineEdit_script_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 31: _t->on_spinBox_script_period_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_pushButton_script_run_clicked(); break;
        case 33: _t->on_comboBox_script_dataType_editTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 34: _t->on_checkBox_script_repeat_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->on_pushButton_save_clicked(); break;
        case 36: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->on_lineEdit_save_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 38: _t->moveCursorToTerminalInputLine(); break;
        case 39: _t->currentAppConfig_save(); break;
        case 40: _t->currentAppConfig_load(); break;
        case 41: _t->connectOrDisconnect(); break;
        case 42: _t->tryConnectDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 43)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 43;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
