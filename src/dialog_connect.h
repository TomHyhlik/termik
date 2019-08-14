#ifndef DIALOG_CONNECT_H
#define DIALOG_CONNECT_H

#include <QDialog>
#include <QMap>
#include <QSerialPort>
#include <QTimer>

#include "mainwindow.h"


#define SERIALPORT_REFRESH_PERIOD 100


#define UDP_PORT_RANGE  65535
#define TITLE_THIS_WINDOW   "Connect"
#define TITLE_TAB_SERIAL    "Serial"
#define TITLE_TAB_NETWORK    "Network"

#define SERIALPORT_REFRESH_PERIOD   100 // ms

#define FILE_savedPortInfo "connectionConfiguration.txt"


#define FAILED -1



namespace Ui {
class Dialog_connect;
}

class SerialWorker;
class NetworkWorker;

class Dialog_connect : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_connect(QWidget *parent = nullptr);
    ~Dialog_connect();

    int getCurrentTab(){
        return currentTab;
    }

    void setSw(SerialWorker * val){
        sw = val;
    }
    void setNw(NetworkWorker * val){
        nw = val;
    }

    int configurationRead();
    void init();


private:
    Ui::Dialog_connect *ui;
    SerialWorker* sw;
    NetworkWorker* nw;

    int currentTab;

    void initColors();

    int getFirstMapVal(QMap<int,QString> m, QString label);
    void blockAllsignals(bool state);

    /* tab port init */
    void tab_port_init();
    QMap<int,QString> baudRateS;    // create maps
    QMap<int,QString> dataBitsS;
    QMap<int,QString> parityS;
    QMap<int,QString> stopBitsS;
    QMap<int,QString> flowControlS;
    void fillBaudRate();            // fill maps
    void fillDataBits();
    void fillParity();
    void fillstopBits();
    void fillflowControl();
    void setDefaultUiParameters();

    QTimer *timer_updatePorts;

    void configurationSave();

    int getProductIdentifier(QString portName);
    QString getSerialPortName(int);


private slots:
    void serialPort_nameRefresh();
    void on_comboBox_portName_currentTextChanged(const QString &arg1);


    void on_tabWidget_currentChanged(int index);
    void on_buttonBox_accepted();
    void on_pushButton_autoconnect_clicked();



signals:
    void connectVia_serial();
    void connectVia_serial(QString serialPortName);
    void connectVia_network();
    void log(int, QString);
};

#endif // DIALOG_CONNECT_H
