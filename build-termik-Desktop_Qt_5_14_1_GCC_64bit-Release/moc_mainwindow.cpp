/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
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
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[49];
    char stringdata0[1058];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "EscPressed"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "moveCursorToEnd"
QT_MOC_LITERAL(4, 39, 10), // "showFindUi"
QT_MOC_LITERAL(5, 50, 10), // "hideFindUi"
QT_MOC_LITERAL(6, 61, 21), // "terminalInputSetFocus"
QT_MOC_LITERAL(7, 83, 22), // "showConnectionSettings"
QT_MOC_LITERAL(8, 106, 11), // "clearOutput"
QT_MOC_LITERAL(9, 118, 7), // "focus_1"
QT_MOC_LITERAL(10, 126, 7), // "focus_2"
QT_MOC_LITERAL(11, 134, 7), // "focus_3"
QT_MOC_LITERAL(12, 142, 18), // "toggleShowSettings"
QT_MOC_LITERAL(13, 161, 8), // "showHelp"
QT_MOC_LITERAL(14, 170, 8), // "hideHelp"
QT_MOC_LITERAL(15, 179, 12), // "showScriptUi"
QT_MOC_LITERAL(16, 192, 12), // "hideScriptUi"
QT_MOC_LITERAL(17, 205, 12), // "keyUpPressed"
QT_MOC_LITERAL(18, 218, 14), // "keyDownPressed"
QT_MOC_LITERAL(19, 233, 15), // "keyEnterPressed"
QT_MOC_LITERAL(20, 249, 5), // "on_Tx"
QT_MOC_LITERAL(21, 255, 16), // "Tx_fromDataInput"
QT_MOC_LITERAL(22, 272, 15), // "historyTxUpdate"
QT_MOC_LITERAL(23, 288, 12), // "selectScript"
QT_MOC_LITERAL(24, 301, 17), // "terminalOutUpdate"
QT_MOC_LITERAL(25, 319, 29), // "moveCursorToTerminalInputLine"
QT_MOC_LITERAL(26, 349, 26), // "currentAppConfig_loadSaved"
QT_MOC_LITERAL(27, 376, 18), // "runScript_finished"
QT_MOC_LITERAL(28, 395, 19), // "connectOrDisconnect"
QT_MOC_LITERAL(29, 415, 31), // "on_checkBox_prefix_stateChanged"
QT_MOC_LITERAL(30, 447, 4), // "arg1"
QT_MOC_LITERAL(31, 452, 31), // "on_checkBox_suffix_stateChanged"
QT_MOC_LITERAL(32, 484, 30), // "on_lineEdit_suffix_textChanged"
QT_MOC_LITERAL(33, 515, 30), // "on_lineEdit_prefix_textChanged"
QT_MOC_LITERAL(34, 546, 32), // "on_checkBox_timeLog_stateChanged"
QT_MOC_LITERAL(35, 579, 40), // "on_checkBox_clearOutputLine_s..."
QT_MOC_LITERAL(36, 620, 35), // "on_checkBox_outputSave_stateC..."
QT_MOC_LITERAL(37, 656, 37), // "on_spinBox_script_period_valu..."
QT_MOC_LITERAL(38, 694, 32), // "on_pushButton_script_run_clicked"
QT_MOC_LITERAL(39, 727, 43), // "on_comboBox_script_dataType_e..."
QT_MOC_LITERAL(40, 771, 38), // "on_checkBox_script_repeat_sta..."
QT_MOC_LITERAL(41, 810, 26), // "on_pushButton_save_clicked"
QT_MOC_LITERAL(42, 837, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(43, 865, 5), // "index"
QT_MOC_LITERAL(44, 871, 28), // "on_lineEdit_save_textChanged"
QT_MOC_LITERAL(45, 900, 34), // "on_checkBox_autoclear_stateCh..."
QT_MOC_LITERAL(46, 935, 44), // "on_spinBox_autoclear_maxCharC..."
QT_MOC_LITERAL(47, 980, 46), // "on_comboBox_script_dataType_c..."
QT_MOC_LITERAL(48, 1027, 30) // "on_lineEdit_script_textChanged"

    },
    "MainWindow\0EscPressed\0\0moveCursorToEnd\0"
    "showFindUi\0hideFindUi\0terminalInputSetFocus\0"
    "showConnectionSettings\0clearOutput\0"
    "focus_1\0focus_2\0focus_3\0toggleShowSettings\0"
    "showHelp\0hideHelp\0showScriptUi\0"
    "hideScriptUi\0keyUpPressed\0keyDownPressed\0"
    "keyEnterPressed\0on_Tx\0Tx_fromDataInput\0"
    "historyTxUpdate\0selectScript\0"
    "terminalOutUpdate\0moveCursorToTerminalInputLine\0"
    "currentAppConfig_loadSaved\0"
    "runScript_finished\0connectOrDisconnect\0"
    "on_checkBox_prefix_stateChanged\0arg1\0"
    "on_checkBox_suffix_stateChanged\0"
    "on_lineEdit_suffix_textChanged\0"
    "on_lineEdit_prefix_textChanged\0"
    "on_checkBox_timeLog_stateChanged\0"
    "on_checkBox_clearOutputLine_stateChanged\0"
    "on_checkBox_outputSave_stateChanged\0"
    "on_spinBox_script_period_valueChanged\0"
    "on_pushButton_script_run_clicked\0"
    "on_comboBox_script_dataType_editTextChanged\0"
    "on_checkBox_script_repeat_stateChanged\0"
    "on_pushButton_save_clicked\0"
    "on_tabWidget_currentChanged\0index\0"
    "on_lineEdit_save_textChanged\0"
    "on_checkBox_autoclear_stateChanged\0"
    "on_spinBox_autoclear_maxCharCnt_valueChanged\0"
    "on_comboBox_script_dataType_currentTextChanged\0"
    "on_lineEdit_script_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  239,    2, 0x08 /* Private */,
       3,    0,  240,    2, 0x08 /* Private */,
       4,    0,  241,    2, 0x08 /* Private */,
       5,    0,  242,    2, 0x08 /* Private */,
       6,    0,  243,    2, 0x08 /* Private */,
       7,    0,  244,    2, 0x08 /* Private */,
       8,    0,  245,    2, 0x08 /* Private */,
       9,    0,  246,    2, 0x08 /* Private */,
      10,    0,  247,    2, 0x08 /* Private */,
      11,    0,  248,    2, 0x08 /* Private */,
      12,    0,  249,    2, 0x08 /* Private */,
      13,    0,  250,    2, 0x08 /* Private */,
      14,    0,  251,    2, 0x08 /* Private */,
      15,    0,  252,    2, 0x08 /* Private */,
      16,    0,  253,    2, 0x08 /* Private */,
      17,    0,  254,    2, 0x08 /* Private */,
      18,    0,  255,    2, 0x08 /* Private */,
      19,    0,  256,    2, 0x08 /* Private */,
      20,    1,  257,    2, 0x08 /* Private */,
      21,    1,  260,    2, 0x08 /* Private */,
      22,    0,  263,    2, 0x08 /* Private */,
      23,    0,  264,    2, 0x08 /* Private */,
      24,    2,  265,    2, 0x08 /* Private */,
      25,    0,  270,    2, 0x08 /* Private */,
      26,    0,  271,    2, 0x08 /* Private */,
      27,    0,  272,    2, 0x08 /* Private */,
      28,    0,  273,    2, 0x08 /* Private */,
      29,    1,  274,    2, 0x08 /* Private */,
      31,    1,  277,    2, 0x08 /* Private */,
      32,    1,  280,    2, 0x08 /* Private */,
      33,    1,  283,    2, 0x08 /* Private */,
      34,    1,  286,    2, 0x08 /* Private */,
      35,    1,  289,    2, 0x08 /* Private */,
      36,    1,  292,    2, 0x08 /* Private */,
      37,    1,  295,    2, 0x08 /* Private */,
      38,    0,  298,    2, 0x08 /* Private */,
      39,    1,  299,    2, 0x08 /* Private */,
      40,    1,  302,    2, 0x08 /* Private */,
      41,    0,  305,    2, 0x08 /* Private */,
      42,    1,  306,    2, 0x08 /* Private */,
      44,    1,  309,    2, 0x08 /* Private */,
      45,    1,  312,    2, 0x08 /* Private */,
      46,    1,  315,    2, 0x08 /* Private */,
      47,    1,  318,    2, 0x08 /* Private */,
      48,    1,  321,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QByteArray,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   43,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::QString,   30,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->EscPressed(); break;
        case 1: _t->moveCursorToEnd(); break;
        case 2: _t->showFindUi(); break;
        case 3: _t->hideFindUi(); break;
        case 4: _t->terminalInputSetFocus(); break;
        case 5: _t->showConnectionSettings(); break;
        case 6: _t->clearOutput(); break;
        case 7: _t->focus_1(); break;
        case 8: _t->focus_2(); break;
        case 9: _t->focus_3(); break;
        case 10: _t->toggleShowSettings(); break;
        case 11: _t->showHelp(); break;
        case 12: _t->hideHelp(); break;
        case 13: _t->showScriptUi(); break;
        case 14: _t->hideScriptUi(); break;
        case 15: _t->keyUpPressed(); break;
        case 16: _t->keyDownPressed(); break;
        case 17: _t->keyEnterPressed(); break;
        case 18: _t->on_Tx((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 19: _t->Tx_fromDataInput((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->historyTxUpdate(); break;
        case 21: _t->selectScript(); break;
        case 22: _t->terminalOutUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 23: _t->moveCursorToTerminalInputLine(); break;
        case 24: _t->currentAppConfig_loadSaved(); break;
        case 25: _t->runScript_finished(); break;
        case 26: _t->connectOrDisconnect(); break;
        case 27: _t->on_checkBox_prefix_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->on_checkBox_suffix_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->on_lineEdit_suffix_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 30: _t->on_lineEdit_prefix_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 31: _t->on_checkBox_timeLog_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->on_checkBox_clearOutputLine_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->on_checkBox_outputSave_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->on_spinBox_script_period_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->on_pushButton_script_run_clicked(); break;
        case 36: _t->on_comboBox_script_dataType_editTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 37: _t->on_checkBox_script_repeat_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->on_pushButton_save_clicked(); break;
        case 39: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->on_lineEdit_save_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: _t->on_checkBox_autoclear_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->on_spinBox_autoclear_maxCharCnt_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->on_comboBox_script_dataType_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 44: _t->on_lineEdit_script_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
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
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 45)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 45;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
