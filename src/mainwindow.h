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
#include "logfile.h"
#include "runscript.h"
#include "communication.h"



#define DIGIT_NUM_HEX   2
#define DIGIT_NUM_DEC   3
#define DIGIT_NUM_BIN   8

#define RXDATAEVENT_TIMEOUT 50

#define SUFFIX_DEFAULT      "\r\n"

#define TIME_FORMAT "dd.MM.yyyy, hh:mm:ss"

#define AUTOCLEAR_VAL_DEFAULT   100

#define SCRIPT_TXPERIOD_DEFAULT 1000

#define COLOR_BLACK     "black"
#define COLOR_WHITE     "white"

#define COLOR_DATA_RX      "DeepSkyBlue"
#define COLOR_DATA_TX      "lime"
#define COLOR_ERROR     "Tomato"
#define COLOR_PREAMBLE      "#949494"

#define COLOR_GREEN     "green"
#define COLOR_RED       "red"


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

enum logType {
    error, note, info
};

enum dataToDisplay {
     data_Rx, data_Tx
};

enum addLine{
    before, after, beforeAndAfter
};

enum dataFormat {
    data_ascii, data_hex, data_dec, //data_bin
};




class appConfiguration {
public:

//    int connectionType;       todo: rmLater

    bool timeLogEnabled;

    bool suffix_tx_enabled;
    bool prefix_tx_enabled;

    QByteArray suffix_tx;
    QByteArray prefix_tx;

    bool timeInfoEnabled;
    bool clearOutputLine;

    bool saveTerminalOutToFile;

    bool autoclerTermOut;
    int autoclerTermOut_maxChars;


};




/////////////////////////////////////////////////////////
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    int lastTerminalData;

    void closeEvent(QCloseEvent *event);


public:
    explicit MainWindow(QStringList arguments,QWidget *parent = nullptr);
    ~MainWindow();

private slots:   
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

    void on_Tx(QByteArray);
    void Tx_fromDataInput(int);


    void historyTxUpdate();
    void selectScript();

    void terminalOutUpdate(int, QByteArray);


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
    void on_lineEdit_save_textChanged(const QString &arg1);

    void moveCursorToTerminalInputLine();

    void currentAppConfig_save();
    void currentAppConfig_load();



    void connectOrDisconnect();

    void on_checkBox_autoclear_stateChanged(int arg1);
    void on_spinBox_autoclear_maxCharCnt_valueChanged(int arg1);

    void on_connectionEstablished(bool success, QString deviceName);


public slots:


private:
    Ui::MainWindow *ui;

    Communication* communic;
    LogFile* logFile;
    appConfiguration config;
    runScript* script;

    qint64 tick_lastRx;
    QElapsedTimer tick;


    QList <QByteArray> history_out;
    int history_out_ptr;

    void configInit();

    void showMessage(int, QString);

    void TxHistory_add(QByteArray data);

    bool stringList_find(QList<QString> list, QString data);

    void fillShortcutsTable();
    void shortcutTable_addItem(QList<QString> element);

    void portSet_fillMaps();
    void uiInit();

    void writeToTextedit(QTextEdit* textEdit, QString color, QString data);
    void shortenTextEdit(QTextEdit* textEdit);

    void setupShortcuts();

    void saveToFile_init();


    void pushButton_runScript_setColor_green();
    void pushButton_runScript_setColor_red();

    bool preambleShouldBeAddrd(int);
    void preambleAdd(int);
    QString getDataColor(int);
    QString terminalOutGetPreamble(int);
    bool checkboxChecked(int);

};

#endif // MAINWINDOW_H
