#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMap>
#include <QTimer>
#include <QList>

#include "serialworker.h"
#include "networkworker.h"


#define DIGIT_NUM_HEX   2
#define DIGIT_NUM_DEC   3
#define DIGIT_NUM_BIN   8

typedef enum {
    Dark, Light
} theme_t;

typedef enum {
    error, note, info
} logType_t;

typedef enum {
     usbRx, usbTx
} terminalData_t;

typedef enum {
    before, after, beforeAndAfter
} addLine_t;

typedef enum {
    data_ascii, data_hex, data_dec, data_bin
} dataFormat_t;



/* connectionType */
enum {
    serial, network, none
};

class colorTheme {
public:
    QString back0;
    QString back1;
    QString back2;
    QString back3;
    QString back4;
    QString text;

    colorTheme(){
        back0 = "#404040";          // the very background
        back1 = "#202020";          // groupboxes & statusBar
        back2 = "#505050";          // menuBar
        back3 = "#101010";
        back4 = "#050505";          // text background
        text = "white";             // text
    }
};


/////////////////////////////////////////////////////////
namespace Ui {
class MainWindow;
}

class Dialog_connect;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int connectionType;


private slots:   
    void dataArrived();
    void EscPressed();
    void moveCursorToEnd();
    void changeTheme();
    void showFindUi();
    void hideFindUi();
    void showSaveSettings();
    void hideSaveSettings();
    void terminalInputSetFocus();



    void clearOutput();
    void focus_1();
    void focus_2();
    void focus_3();


    void showWrap();
    void hideWrap();
    void showHelp();
    void hideHelp();

    void keyUpPressed();
    void keyDownPressed();
    void keyEnterPressed();

    void on_pushButton_save_clicked();
    void saveToFile(QString data);


private:
    Ui::MainWindow *ui;
    SerialWorker *sw;
    NetworkWorker *nw;
    Dialog_connect* dialog_connect;

    QFile file;

    dataFormat_t fileDataFormat;

    QList <QByteArray> history_out;
    quint16 history_out_pointer;

    void log(logType_t logType, QString data);

//    /* tab port init */
//    void tab_port_init();
//    QMap<int,QString> baudRateS;    // create maps
//    QMap<int,QString> dataBitsS;
//    QMap<int,QString> parityS;
//    QMap<int,QString> stopBitsS;
//    QMap<int,QString> flowControlS;
//    void fillBaudRate();            // fill maps
//    void fillDataBits();
//    void fillParity();
//    void fillstopBits();
//    void fillflowControl();

    void terminalOutUpdate(terminalData_t, QByteArray);

    int getFirstMapVal(QMap<int,QString> m, QString label);

    bool stringList_find(QList<QString> list, QString data);

    void fillShortcutsTable();
    void shortcutTable_addItem(QList<QString> element);

    void portSet_fillMaps();


};

#endif // MAINWINDOW_H
