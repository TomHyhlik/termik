#ifndef DIALOG_CONNECT_H
#define DIALOG_CONNECT_H

#include <QDialog>
#include <QMap>
#include <QSerialPort>
#include <QTimer>
#include <QTableWidget>

#include "networkscan.h"
#include "mainwindow.h"

#define PORT_RANGE  65535
#define TITLE_THIS_WINDOW   "Connect"
#define TITLE_TAB_SERIAL    "Serial"
#define TITLE_TAB_NETWORK    "Network"


#define TITLE_TAB_SERIAL_NAME                      "Name"
#define TITLE_TAB_SERIAL_DESCRIPTION               "Description"
#define TITLE_TAB_SERIAL_MANUFACTURER              "Manufacturer"
#define TITLE_TAB_SERIAL_SERIALNUMBER              "Serial number"
#define TITLE_TAB_SERIAL_LOCATION                  "Location"
#define TITLE_TAB_SERIAL_VENDORIDENTIFIER          "Vendor identifier"
#define TITLE_TAB_SERIAL_PRODUCTIDENTIFIER         "Product identifier"

#define SERIALPORT_REFRESH_PERIOD  500

#define NETWORKPROTOCOL_UDP     "UDP"
#define NETWORKPROTOCOL_TCP     "TCP"

#define TITLE_NAME      "Name"
#define TITLE_ADDR      "Address"

#define TAB_INDEX_SERIAL        0
#define TAB_INDEX_NETWORK       1

enum {
  tableAction_up, tableAction_down
};


namespace Ui {
class Dialog_connect;
}

class SerialWorker;
class NetworkWorker;

class Dialog_connect : public QDialog
{
    Q_OBJECT

    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

public:
    explicit Dialog_connect(QWidget *parent = nullptr);
    ~Dialog_connect();

private:
    Ui::Dialog_connect *ui;

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

    QSharedPointer <QTimer> timer_updatePorts;
    QSharedPointer <NetworkScan> networkScan;

    void configurationSave();

    void shortcuts_init();
    int getProductIdentifier(QString portName);
    QString getSerialPortName(int);
    int getSelectedNetworkProtocol();
    void table_network_init();
    void table_serial_init();
    void table_addHost(QTableWidget* table, QHostInfo host);
    void table_serial_add(QSerialPortInfo);

    void table_updateHosts(QTableWidget* tableWidget, const QList <QHostInfo> hosts);


private slots:

    void serialPort_nameRefresh();
    void refreshDevices();

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void focus_1();
    void focus_2();
    void loadParametersToUi();
    void EscPressed();

    void networkScanFinished();

    void on_tableWidget_addr_tx_currentCellChanged(int row, int column);
    void on_tableWidget_addr_rx_currentCellChanged(int row, int column);
    void on_tableWidget_serialPorts_currentCellChanged(int row, int column);

    void pressedKeyUp();
    void pressedKeyDown();
    void table_makeAction(QTableWidget*, int);
    void lineEdit_updateToTableRow(QLineEdit* lineEdit, QTableWidget *table, int row);
    void pressedKeyLeft();
    void pressedKeyRight();



signals:

    void connectVia_serial(QString serialPortName);
    void tryConnect(communicationType);
    void log(int, QString);



};

#endif // DIALOG_CONNECT_H
