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


#define DIGIT_NUM_HEX   2
#define DIGIT_NUM_DEC   3
#define DIGIT_NUM_BIN   8

#define RXDATAEVENT_TIMEOUT 100

#define SUFFIX_DEFAULT      "\r\n"

#define TIME_FORMAT "dd.MM.yyyy, hh:mm:ss"



typedef enum {
    Dark, Light
} theme_t;

typedef enum {
    error, note, info
} logType_t;

typedef enum {
     data_Rx, data_Tx
} terminalData_t;

typedef enum {
    before, after, beforeAndAfter
} addLine_t;

typedef enum {
    data_ascii, data_hex, data_dec, //data_bin
} dataFormat_t;

/* connectionType */
typedef enum {
    serial, network, none
} connectionType_t;


class swConfiguration {
public:

    connectionType_t connectionType;

    bool timeLogEnabled;

    bool suffix_tx_enabled;
    bool prefix_tx_enabled;

    QByteArray suffix_tx;
    QByteArray prefix_tx;

    bool timeInfoEnabled;
    bool clearOutputLine;

    bool saveTerminalOutToFile;

    terminalData_t lastTerminalData;
};

#define COLOR_BLACK     "black"
#define COLOR_WHITE     "white"

#define COLOR_DATA_RX      "DeepSkyBlue"
#define COLOR_DATA_TX      "lime"
#define COLOR_ERROR     "Tomato"
#define COLOR_DATA      "#949494"

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

/////////////////////////////////////////////////////////
namespace Ui {
class MainWindow;
}

class Dialog_connect;

class MainWindow : public QMainWindow
{
    Q_OBJECT

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

    void on_pushButton_save_clicked();

    void on_tabWidget_currentChanged(int index);

    void Tx(dataFormat_t);

    void on_checkBox_prefix_stateChanged(int arg1);
    void on_checkBox_suffix_stateChanged(int arg1);
    void on_lineEdit_suffix_textChanged(const QString &arg1);
    void on_lineEdit_prefix_textChanged(const QString &arg1);
    void on_checkBox_timeLog_stateChanged(int arg1);

    void historyTxUpdate();

    void selectScript();

    void on_checkBox_clearOutputLine_stateChanged(int arg1);
    void on_checkBox_outputSave_stateChanged(int arg1);
    void moveCursorToTerminalInputLine();

public slots:
    void tryConnectDevice(connectionType_t);

private:
    Ui::MainWindow *ui;
    SerialWorker *sw;
    NetworkWorker *nw;
    Dialog_connect* dialog_connect;
    LogFile* logFile;
    swConfiguration config;

    qint64 tick_lastRx;
    QElapsedTimer tick;


    QList <QByteArray> history_out;
    int history_out_ptr;

    void configInit();

    void log(logType_t logType, QString data);

    void terminalOutUpdate(terminalData_t, QByteArray);
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


};

#endif // MAINWINDOW_H
