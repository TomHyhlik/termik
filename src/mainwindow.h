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
#include "outputfile.h"
#include "runscript.h"
#include "communication.h"
#include "uilog.h"
#include "outputfile.h"
#include "form_termio.h"
#include "fastcmdshandler.h"

enum {
    PLAT_LINUX, PLAT_MAC, PLAT_WINDOWS
};

////////////////////////////////////////////////////////////
#define VERSION_CODE            "0.1.0"

#define MAINWINDOWTITLE         "Termik"


#define PLATFORM    PLAT_WINDOWS


#define STR_STYLESHEET_COLOR_BCKGCOLOR  "color: %1; background-color: %2"

#define DIGIT_NUM_HEX   2
#define DIGIT_NUM_DEC   3
#define DIGIT_NUM_BIN   8

#define RXDATAEVENT_TIMEOUT 50

#define SUFFIX_DEFAULT      "\n"

#define TIME_FORMAT "yyyy/MM/dd-hh:mm:ss.zzz"

#define AUTOCLEAR_VAL_DEFAULT   1000
#define SCRIPT_TXPERIOD_DEFAULT 1000

#define COLOR_BLACK     "black"
#define COLOR_WHITE     "white"
#define COLOR_DATA_RX      "DeepSkyBlue"
#define COLOR_DATA_TX      "lime"
#define COLOR_ERROR     "Tomato"
#define COLOR_PREAMBLE      "#949494"
#define COLOR_GREEN     "#005000"//"green"
#define COLOR_RED       "#500000"//"red"
#define COLOR_TOPLINE   "#A0A0A0"
#define COLOR_GRAY0     "#404040"
#define COLOR_GRAY1     "#303030"
#define COLOR_GRAY2     "#202020"
#define COLOR_GRAY3     "#101010"
#define COLOR_GRAY4     "#050505"

#define TITLE_DATA_ASCII    "ASCII"
#define TITLE_DATA_HEX      "HEX"
#define TITLE_BUTTON_SCRIPT_RUN "Run"
#define TITLE_BUTTON_SCRIPT_STOP "Stop"
#define TITLE_HELPTABLE_SHORTCUT        "Shortcut"
#define TITLE_HELPTABLE_DESCRIPTION     "Description"

#define TABWIDGET_TABCNT        3

#define TABWIDGET_SETTINGS_INDEX_GENERAL     0
#define TABWIDGET_SETTINGS_INDEX_SCRIPT      1

#define LOCATION_DEFAULT    "~/"

#define STATMESSAGE_ERR_NOTCONNECTED "Can't transmit. No connection established"



enum dataToDisplay {
     data_Rx, data_Tx
};

enum addLine{
    before, after, beforeAndAfter
};

const QList <QString> title_dataFormat
{
    TITLE_DATA_ASCII, TITLE_DATA_HEX
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

    Form_termIO termIO[TABWIDGET_TABCNT];

    QTextEdit textEdit_out;
    QLineEdit lineEdit_in;

    FastCmdsHandler* fastCmdsHandler;

    const QList <QList <QString>> SHORTCUTS_CONTENT_MAINWINDOW =
    {
        { "CTRL + P" , "Show connection settongs"},
        { "CTRL + D" , "Connect/Disconnect toggle"},
        { "CTRL + ," , "Show main settongs"},
        { "CTRL + O" , "Open a file \"script\"to run in terminal later"},
        { "CTRL + R" , "Run/Stop transmission of the selected \"script\""},
        { "CTRL + L" , "Move cursor to the end of the terminal output"},
        { "CTRL + SHIFT + L" , "Clear terminal output"},
        { "CTRL + 1" , "Set focus to ASCII tab"},
        { "CTRL + 2" , "Set focus to Hex tab"},
        { "CTRL + 3" , "Set focus to DEC tab"},
        { "CTRL + S" , "Open location where the terminal output shall be saved"},
        { "Esc"      , "Hide evrything"},
        { "CTRL + Q" , "Quit uiThis app"},
        { "F1"       , "Open help"}
    };


public:
    explicit MainWindow(int argc, char** argv, QWidget *parent = nullptr);
    ~MainWindow();

private slots:   
    void pressedKey_esc();
    void moveCursorToEnd();

    void terminalInputSetFocus();
    int terminalInputHasFocus();
    void showConnectionSettings();

    void clearOutput();
    void focus_0();
    void focus_1();
    void focus_2();
    void focus_termIO(int index);
    void uiResize_minus();
    void uiResize_plus();

    void toggleShowSettings();
    void showSettings();
    void hideSettings();
    void toggleShowHelp();
    void showHelp();
    void hideHelp();
    void showFastCommands();

    void pressedKey_up();
    void pressedKey_down();
    void pressedKey_enter();

    void Tx(QByteArray);
    void Tx_fromDataInput(int);

    void historyTxUpdate();
    void openScript();

    void terminalOutUpdate(int, QByteArray);

    void currentAppConfig_loadSaved();
    void fastCmds_save();
    void fastCmds_load();
    void runScript_finished();
    void connectionToggle();

    void on_checkBox_prefix_stateChanged(int arg1);
    void on_checkBox_suffix_stateChanged(int arg1);
    void on_lineEdit_suffix_textChanged(const QString &arg1);
    void on_lineEdit_prefix_textChanged(const QString &arg1);
    void on_checkBox_timeLog_stateChanged(int arg1);    
    void on_checkBox_clearOutputLine_stateChanged(int arg1);
    void on_checkBox_outputSave_stateChanged(int arg1);
    void on_spinBox_scriptTransmissionPeriod_valueChanged(int arg1);
    void on_pushButton_scriptRun_clicked();
    void on_checkBox_scriptRepeatEnable_stateChanged(int arg1);
    void on_pushButton_save_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_lineEdit_save_textChanged(const QString &arg1);
    void on_checkBox_autoclear_stateChanged(int arg1);
    void on_spinBox_autoclear_maxCharCnt_valueChanged(int arg1);
    void on_comboBox_scriptDataFormat_currentTextChanged(const QString &arg1);
    void on_lineEdit_scriptPath_textChanged(const QString &arg1);


public slots:   


private:
    Ui::MainWindow *ui;
    Communication* communic;
    std::unique_ptr <OutputFile> outputFile = nullptr;
    std::unique_ptr <RunScript> script = nullptr;

    QElapsedTimer sinceLastTermOutUpdate;

    QList <QByteArray> history_out;
    int history_out_ptr;

    void InitAppParams();
    void InitColors();
    void InitUi();
    void InitCommunicationWorker();
    void InitShortcuts();

    void TxHistory_add(QByteArray data);

    bool stringList_find(QList<QString> list, QString data);

    void portSet_fillMaps();

    void writeToTextedit(QTextEdit* textEdit, QString color, QString data);
    void shortenTextEdit(QTextEdit* textEdit);

    void terminalOut_addPreamble(int);
    QString getDataColor(int);
    QString terminalOutGetPreamble(int);


signals:
    void fastCmds_addCmd();


};

#endif // MAINWINDOW_H
