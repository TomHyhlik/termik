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
#include "log.h"
#include "outputfile.h"


#define STR_STYLESHEET_COLOR_BCKGCOLOR  "color: %1; background-color: %2"

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

#define COLOR_GREEN     "#005000"//"green"
#define COLOR_RED       "#500000"//"red"


#define COLOR_TOPLINE   "#A0A0A0"
#define COLOR_GRAY0     "#404040"
#define COLOR_GRAY1     "#202020"
#define COLOR_GRAY2     "#151515"
#define COLOR_GRAY3     "#101010"
#define COLOR_GRAY4     "#050505"

#define MAINWINDOWTITLE "Termik"


#define TITLE_DATA_ASCII    "ASCII"
#define TITLE_DATA_HEX      "HEX"

#define TITLE_BUTTON_SCRIPT_RUN "Run"
#define TITLE_BUTTON_SCRIPT_STOP "Stop"

#define TITLE_HELPTABLE_SHORTCUT        "Shortcut"
#define TITLE_HELPTABLE_DESCRIPTION     "Description"



#define LOCATION_DEFAULT    "~/"



enum dataToDisplay {
     data_Rx, data_Tx
};

enum addLine{
    before, after, beforeAndAfter
};

enum dataFormat {
    data_ascii, data_hex, data_dec, //data_bin
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
    void currentAppConfig_save();



public:
    explicit MainWindow(QStringList arguments,QWidget *parent = nullptr);
    ~MainWindow();

private slots:   
    void pressedKey_esc();
    void moveCursorToEnd();
    void showFindUi();
    void hideFindUi();

    void terminalInputSetFocus();
    void showConnectionSettings();

    void clearOutput();
    void focus_0();
    void focus_1();
    void focus_2();

    void toggleShowSettings();
    void showSettings();
    void hideSettings();
    void toggleShowHelp();
    void showHelp();
    void hideHelp();

    void showScriptUi();
    void hideScriptUi();

    void pressedKey_up();
    void pressedKey_down();
    void pressedKey_enter();

    void on_Tx(QByteArray);
    void Tx_fromDataInput(int);

    void historyTxUpdate();
    void selectScript();

    void terminalOutUpdate(int, QByteArray);

    void moveCursorToTerminalInputLine();
    void currentAppConfig_loadSaved();
    void runScript_finished();
    void connectOrDisconnect();

    void on_checkBox_prefix_stateChanged(int arg1);
    void on_checkBox_suffix_stateChanged(int arg1);
    void on_lineEdit_suffix_textChanged(const QString &arg1);
    void on_lineEdit_prefix_textChanged(const QString &arg1);
    void on_checkBox_timeLog_stateChanged(int arg1);    
    void on_checkBox_clearOutputLine_stateChanged(int arg1);
    void on_checkBox_outputSave_stateChanged(int arg1);
    void on_spinBox_script_period_valueChanged(int arg1);
    void on_pushButton_script_run_clicked();
    void on_comboBox_script_dataType_editTextChanged(const QString &arg1);
    void on_checkBox_script_repeat_stateChanged(int arg1);
    void on_pushButton_save_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_lineEdit_save_textChanged(const QString &arg1);
    void on_checkBox_autoclear_stateChanged(int arg1);
    void on_spinBox_autoclear_maxCharCnt_valueChanged(int arg1);
    void on_comboBox_script_dataType_currentTextChanged(const QString &arg1);
    void on_lineEdit_script_textChanged(const QString &arg1);


public slots:


private:
    Ui::MainWindow *ui;
    Communication* communic;
    std::unique_ptr <OutputFile> outputFile;
    std::unique_ptr <RunScript> script;

    QElapsedTimer sinceLastTermOutUpdate;


    QList <QByteArray> history_out;
    int history_out_ptr;

    void configInit();


    void TxHistory_add(QByteArray data);

    bool stringList_find(QList<QString> list, QString data);

    void portSet_fillMaps();
    void uiInit();

    void writeToTextedit(QTextEdit* textEdit, QString color, QString data);
    void shortenTextEdit(QTextEdit* textEdit);

    void saveToFile_init();

    void terminalOut_addPreamble(int);
    QString getDataColor(int);
    QString terminalOutGetPreamble(int);


};

#endif // MAINWINDOW_H
