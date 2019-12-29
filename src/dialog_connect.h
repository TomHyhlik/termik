#ifndef DIALOG_CONNECT_H
#define DIALOG_CONNECT_H

#include <QDialog>
#include <QMap>
#include <QSerialPort>
#include <QTimer>
#include <QTableWidget>

#include "mainwindow.h"

#define PORT_RANGE  65535
#define TITLE_THIS_WINDOW   "Connect"
#define TITLE_TAB_SERIAL    "Serial"
#define TITLE_TAB_NETWORK    "Network"

#define SERIALPORT_REFRESH_PERIOD  1000// 300

#define NETWORKPROTOCOL_UDP     "UDP"
#define NETWORKPROTOCOL_TCP     "TCP"

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

    void showEvent(QShowEvent *event);

    void setSw(SerialWorker * val){
        sw = val;
    }
    void setNw(NetworkWorker * val){
        nw = val;
    }

    void init();
    void timerRefresh_start();
    void timerRefresh_stop();


private:
    Ui::Dialog_connect *ui;
    SerialWorker* sw;
    NetworkWorker* nw;

    int currentTab;

    void initColors();

    int getFirstMapVal(QMap<int,QString> m, QString label);
    QString getSecondMapVal(QMap<int,QString> m, int val);

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

    QTimer *timer_updatePorts;

    void configurationSave();

    int getProductIdentifier(QString portName);
    QString getSerialPortName(int);
    int getSelectedNetworkProtocol();
    void table_init();
    void table_addHost(QTableWidget* table, QHostInfo host);
    void table_clear(QTableWidget* table);

    QString table_getHost(QTableWidget* table, int column);


private slots:
    void networkHosts_refresh();
    void serialPort_nameRefresh();
    void refreshDevices();
    void on_comboBox_portName_currentTextChanged(const QString &arg1);


    void on_tabWidget_currentChanged(int index);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void focus_1();
    void focus_2();
    void refreshParameters();
    void EscPressed();


    void on_tableWidget_addr_tx_cellClicked(int row, int column);

    void on_tableWidget_addr_rx_cellClicked(int row, int column);

signals:

    void connectVia_serial(QString serialPortName);
    void tryConnect(int);
    void log(int, QString);



};

#endif // DIALOG_CONNECT_H
