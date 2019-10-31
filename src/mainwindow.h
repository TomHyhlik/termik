#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMap>
#include <QTimer>
#include <QList>
#include <QElapsedTimer>


#include "serialworker.h"
#include "networkworker.h"
#include "handlearguments.h"
#include "logfile.h"
#include "runscript.h"



#define DIGIT_NUM_HEX   2
#define DIGIT_NUM_DEC   3
#define DIGIT_NUM_BIN   8

#define RXDATAEVENT_TIMEOUT 100

#define SUFFIX_DEFAULT      "\r\n"

#define TIME_FORMAT "dd.MM.yyyy, hh:mm:ss"


enum logType {
    error, note, info
};

enum terminalData {
     data_Rx, data_Tx
};

enum addLine{
    before, after, beforeAndAfter
};

enum dataFormat {
    data_ascii, data_hex, data_dec, //data_bin
};

enum connectionType {
    serial, network, none
};



class appConfiguration {
public:

    int connectionType;

    bool timeLogEnabled;

    bool suffix_tx_enabled;
    bool prefix_tx_enabled;

    QByteArray suffix_tx;
    QByteArray prefix_tx;

    bool timeInfoEnabled;
    bool clearOutputLine;

    bool saveTerminalOutToFile;


};

#define COLOR_BLACK     "black"
#define COLOR_WHITE     "white"

#define COLOR_DATA_RX      "DeepSkyBlue"
#define COLOR_DATA_TX      "lime"
#define COLOR_ERROR     "Tomato"
#define COLOR_DATA      "#949494"

#define COLOR_GREEN     "green"
#define COLOR_RED     "red"


#define COLOR_TOPLINE   "#A0A0A0"
#define COLOR_GRAY0     "#404040"
#define COLOR_GRAY1     "#202020"
#define COLOR_GRAY2     "#151515"
#define COLOR_GRAY3     "#101010"
#define COLOR_GRAY4     "#050505"

#define MAINWINDOWTITLE "Termik"

#define LOGTIMEOUT_ERROR    300*1000
#define LOGTIMEOUT_NOTE     60*1000
#define LOGTIMEOUT_INFO     30*1000

#define TITLE_DATA_ASCII    "ASCII"
#define TITLE_DATA_HEX      "HEX"

#define TITLE_BUTTON_SCRIPT_RUN "Run"
#define TITLE_BUTTON_SCRIPT_STOP "Stop"

#define LOCATION_DEFAULT    "~/"

/////////////////////////////////////////////////////////
namespace Ui {
class MainWindow;
}

class Dialog_connect;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int lastTerminalData;

    void closeEvent(QCloseEvent *event);


public:
    explicit MainWindow(QStringList arguments,QWidget *parent = nullptr);
    ~MainWindow();

private slots:   
    void dataArrived();
    void EscPressed();
    void moveCursorToEnd();
    void showFindUi();
    void hideFindUi();
    void terminalInputSetFocus();

    void showConnectionSettings();

    void clearOutput();
    void focus_1();
    void focus_2();
    void focus_3();


    void toggleShowSettings();
    void showHelp();
    void hideHelp();

    void showScriptUi();
    void hideScriptUi();

    void keyUpPressed();
    void keyDownPressed();
    void keyEnterPressed();

    void Tx(QByteArray);
    void Tx_fromDataInput(int);


    void historyTxUpdate();
    void selectScript();

    void on_checkBox_prefix_stateChanged(int arg1);
    void on_checkBox_suffix_stateChanged(int arg1);
    void on_lineEdit_suffix_textChanged(const QString &arg1);
    void on_lineEdit_prefix_textChanged(const QString &arg1);
    void on_checkBox_timeLog_stateChanged(int arg1);    
    void on_checkBox_clearOutputLine_stateChanged(int arg1);
    void on_checkBox_outputSave_stateChanged(int arg1);
    void on_lineEdit_script_textChanged(const QString &arg1);
    void on_spinBox_script_period_valueChanged(int arg1);
    void on_pushButton_script_run_clicked();
    void on_comboBox_script_dataType_editTextChanged(const QString &arg1);
    void on_checkBox_script_repeat_stateChanged(int arg1);
    void on_pushButton_save_clicked();
    void on_tabWidget_currentChanged(int index);

    void moveCursorToTerminalInputLine();


    void currentAppConfig_save();
    void currentAppConfig_load();


    void on_lineEdit_save_textChanged(const QString &arg1);

public slots:
    void tryConnectDevice(int);

private:
    Ui::MainWindow *ui;
    SerialWorker *sw;
    NetworkWorker *nw;
    Dialog_connect* dialog_connect;
    LogFile* logFile;
    appConfiguration config;
    runScript* script;

    qint64 tick_lastRx;
    QElapsedTimer tick;


    QList <QByteArray> history_out;
    int history_out_ptr;

    void configInit();

    void log(int logType, QString data);

    void terminalOutUpdate(int, QByteArray);
    void TxHistory_add(QByteArray data);

    bool stringList_find(QList<QString> list, QString data);

    void fillShortcutsTable();
    void shortcutTable_addItem(QList<QString> element);

    void portSet_fillMaps();
    void uiInit();
    void handleAppArguments(QStringList arguments);
    void handleAppArguments_printHelp();
    void handleAppArguments_printHelp_wrap(char argData, QString argTitle);
    bool handleAppArguments_setParam(QString command, QString passedData);

    void writeToTextedit(QTextEdit *textEdit, QString color, QString data);

    void setupShortcuts();

    void saveToFile_init();


    void pushButton_runScript_setColor_green();
    void pushButton_runScript_setColor_red();

};

#endif // MAINWINDOW_H
