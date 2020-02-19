#include "dialog_connect.h"
#include "ui_dialog_connect.h"
#include "mainwindow.h"


#include <QMap>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QShortcut>
#include <QtDebug>

#define TITLE_NAME      "Name"
#define TITLE_ADDR      "Address"

Dialog_connect::Dialog_connect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_connect)
{
    ui->setupUi(this);


    shortcuts_init();

    table_network_init();
    table_serial_init();
    setWindowTitle(TITLE_THIS_WINDOW);
    ui->tabWidget->setTabText(0, TITLE_TAB_SERIAL);
    ui->tabWidget->setTabText(1, TITLE_TAB_NETWORK);
    ui->spinBox_ipPort_Tx->setMaximum(PORT_RANGE);
    ui->spinBox_ipPort_Rx->setMaximum(PORT_RANGE);
    ui->comboBox_networkProtocol->addItem(NETWORKPROTOCOL_UDP);
    ui->comboBox_networkProtocol->addItem(NETWORKPROTOCOL_TCP);

    initColors();
    tab_port_init();

    ui->tabWidget->setCurrentIndex(0);

    timer_updatePorts = QSharedPointer <QTimer> (new QTimer);
    connect(timer_updatePorts.data(), SIGNAL(timeout()), this, SLOT(refreshDevices()));

    timer_updatePorts.data()->start(SERIALPORT_REFRESH_PERIOD);

}

/////////////////////////////////////////////////////////////////
void Dialog_connect::shortcuts_init()
{
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_1), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_2), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(EscPressed()));
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::EscPressed()
{
        this->close();
}

/////////////////////////////////////////////////////////////////
/// \brief Dialog_connect::closeEvent
///  /// called when the dialog is closed
void Dialog_connect::closeEvent(QCloseEvent *event)
{
//    timer_updatePorts.data()->stop();

    QWidget::closeEvent(event);

    this->deleteLater();
}

/////////////////////////////////////////////////////////////////
/// \brief Dialog_connect::showEvent
/// called when the dialog is shown
void Dialog_connect::showEvent( QShowEvent* event )
{
    QWidget::showEvent(event);

    loadParametersToUi();

//    qDebug() << "Dialog_connect SHOW";
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::loadParametersToUi()
{
    ui->comboBox_baudRate->setCurrentText(getSecondMapVal(baudRateS, param_sw->baudRate));
    ui->comboBox_dataBits->setCurrentText(getSecondMapVal(dataBitsS, param_sw->dataBits));
    ui->comboBox_parity->setCurrentText(getSecondMapVal(parityS, param_sw->parity));
    ui->comboBox_stopBits->setCurrentText(getSecondMapVal(stopBitsS, param_sw->stopBits));
    ui->comboBox_flowControl->setCurrentText(getSecondMapVal(flowControlS, param_sw->flowControl));

    if (!param_nw->IpAddr_Rx.toString().isEmpty())
        ui->lineEdit_selectedAddr_rx->setText(param_nw->IpAddr_Rx.toString());
    if (!param_nw->IpAddr_Tx.toString().isEmpty())
        ui->lineEdit_selectedAddr_tx->setText(param_nw->IpAddr_Tx.toString());

    ui->spinBox_ipPort_Tx->setValue(param_nw->port_Tx);
    ui->spinBox_ipPort_Rx->setValue(param_nw->port_Rx);
}
/////////////////////////////////////////////////////////////////
void Dialog_connect::table_network_init()
{
    QList <QString> titles;
    titles << TITLE_ADDR << TITLE_NAME;

    ui->tableWidget_addr_rx->setColumnCount(titles.size());
    ui->tableWidget_addr_rx->setHorizontalHeaderLabels(titles);

    ui->tableWidget_addr_tx->setColumnCount(titles.size());
    ui->tableWidget_addr_tx->setHorizontalHeaderLabels(titles);
}
/////////////////////////////////////////////////////////////////
void Dialog_connect::table_serial_init()
{
    QList <QString> titles;
    titles << TITLE_TAB_SERIAL_NAME << TITLE_TAB_SERIAL_DESCRIPTION
           << TITLE_TAB_SERIAL_MANUFACTURER << TITLE_TAB_SERIAL_SERIALNUMBER
           << TITLE_TAB_SERIAL_LOCATION << TITLE_TAB_SERIAL_VENDORIDENTIFIER
           << TITLE_TAB_SERIAL_PRODUCTIDENTIFIER;

    ui->tableWidget_serialPorts->setColumnCount(titles.size());
    ui->tableWidget_serialPorts->setHorizontalHeaderLabels(titles);

}
/////////////////////////////////////////////////////////////////
void Dialog_connect::table_addHost(QTableWidget* tableWidget, QHostInfo host)
{

}

/////////////////////////////////////////////////////////////////
void Dialog_connect::blockAllsignals(bool state)
{
    ui->comboBox_baudRate->blockSignals(state);
    ui->comboBox_parity->blockSignals(state);
    ui->comboBox_dataBits->blockSignals(state);
    ui->lineEdit_serialPortName->blockSignals(state);
    ui->comboBox_stopBits->blockSignals(state);
    ui->comboBox_flowControl->blockSignals(state);
}
///////////////////////////////////////////////////////////
void Dialog_connect::initColors()
{
    this->setStyleSheet(QString("color: %1; background-color: %2")
                        .arg(COLOR_WHITE).arg(COLOR_GRAY1));

    ui->tab_serial->setStyleSheet(QString("color: %1; background-color: %2")
                                  .arg(COLOR_WHITE).arg(COLOR_GRAY2));
    ui->tab_network->setStyleSheet(QString("color: %1; background-color: %2")
                                   .arg(COLOR_WHITE).arg(COLOR_GRAY2));

    ui->comboBox_baudRate->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_dataBits->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_flowControl->setStyleSheet(QString("color: %1; background-color: %2")
                                            .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_parity->setStyleSheet(QString("color: %1; background-color: %2")
                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_serialPortName->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_stopBits->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_networkProtocol->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->spinBox_ipPort_Tx->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->spinBox_ipPort_Rx->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->tableWidget_serialPorts->setStyleSheet(QString("color: %1; background-color: %2")
                                          .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->tableWidget_addr_rx->setStyleSheet(QString("color: %1; background-color: %2")
                                          .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->tableWidget_addr_tx->setStyleSheet(QString("color: %1; background-color: %2")
                                          .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_selectedAddr_rx->setStyleSheet(QString("color: %1; background-color: %2")
                                          .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_selectedAddr_tx->setStyleSheet(QString("color: %1; background-color: %2")
                                          .arg(COLOR_WHITE).arg(COLOR_BLACK));

}
/////////////////////////////////////////////////////////////////
void Dialog_connect::refreshDevices()
{
    serialPort_nameRefresh();
    networkHosts_refresh();
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::networkHosts_refresh()
{
    table_clear(ui->tableWidget_addr_rx);
    table_clear(ui->tableWidget_addr_tx);

//    nw->scanNetwork();                            // todo
//    QList <QHostInfo> ipAddrs_rx = nw->getAll_iPaddr_rx();
//    for (int i = 0; i < ipAddrs_rx.size(); i++) {

//        QHostInfo host = ipAddrs_rx.at(i);
//        QStringList element;
//        if (!host.addresses().isEmpty()) {
//            element << host.addresses().first().toString();
//        }
//        element << host.hostName();
//        table_addItem(ui->tableWidget_addr_rx, element);
//    }

//    QList <QHostInfo> ipAddrs_tx = nw->getAll_iPaddr_tx();
//    for (int i = 0; i < ipAddrs_tx.size(); i++) {
//        QHostInfo host = ipAddrs_tx.at(i);
//        QStringList element;
//        if (!host.addresses().isEmpty()) {
//            element << host.addresses().first().toString();
//        }
//        element << host.hostName();
//        table_addItem(ui->tableWidget_addr_tx, element);
//    }
}
///////////////////////////////////////////////////////////////////////
void Dialog_connect::table_clear(QTableWidget* table)
{
    table->clearContents();
    while (table->rowCount()) {
        table->removeRow(0);
    }
    /* set column size to widget size */
    table->horizontalHeader()->setStretchLastSection(true);
}
/////////////////////////////////////////////////////////////////
void Dialog_connect::serialPort_nameRefresh()
{
    QList <QSerialPortInfo> currentAvailablePorts = QSerialPortInfo::availablePorts();

    /* delete ports which were plugged out */
    for (int i = 0; i < ui->tableWidget_serialPorts->rowCount(); i++) {
        bool isHere = false;
        for (int j = 0; j < currentAvailablePorts.size(); j++) {
            if (ui->tableWidget_serialPorts->item(i, 0)->text() == currentAvailablePorts.at(j).portName()) {
                isHere = true;
                break;
            }
        }
        if(!isHere){
            ui->tableWidget_serialPorts->removeRow(i);
        }
    }

    /* add ports which were plugged in */
    for (int j = 0; j < currentAvailablePorts.size(); j++) {
        bool isHere = false;
        for(int i = 0; i < ui->tableWidget_serialPorts->rowCount(); i++){
            if(currentAvailablePorts.at(j).portName() == ui->tableWidget_serialPorts->item(i,0)->text()){
                isHere = true;
                break;
            }
        }
        if(!isHere){
            table_serial_add(currentAvailablePorts.at(j));
        }
    }
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::table_serial_add(QSerialPortInfo serialPort)
{
    QStringList element;
    element << serialPort.portName()
            << serialPort.description()
            << serialPort.manufacturer()
            << serialPort.serialNumber()
            << serialPort.systemLocation()
            << QString("%1").arg(serialPort.vendorIdentifier())
            << QString("%1").arg(serialPort.productIdentifier());


    table_addItem(ui->tableWidget_serialPorts, element);
}
/////////////////////////////////////////////////////////////////
void Dialog_connect::table_addItem(QTableWidget* table, QStringList element)
{
    table->insertRow(table->rowCount());
    /* get number of the new row */
    int newRow =  table->rowCount() - 1;

    /* for each element in the row */
    for (int column = 0; column < element.size(); column++){
        /* create new item to the table */
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(element.at(column)));
        /* make the item non-editable */
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        item->setTextAlignment(Qt::AlignVCenter);
        /* add the item to specified column and row */
        table->setItem(newRow, column, item);
    }
    /* resize the columns to be optimized for the content */
    for (int i = 0; i <  table->columnCount(); i++){
         table->resizeColumnToContents(i);
    }
}
/////////////////////////////////////////////////////////////////
void Dialog_connect::tab_port_init()
{
    /* fill maps of comboboxes */
    fillBaudRate();
    fillDataBits();
    fillParity();
    fillstopBits();
    fillflowControl();

    /* fill comboboxes */
    for (auto e :  baudRateS.toStdMap() ) {
        ui->comboBox_baudRate->addItem(e.second);
    }
    for (auto e :  dataBitsS.toStdMap() ) {
        ui->comboBox_dataBits->addItem(e.second);
    }
    for (auto e :  parityS.toStdMap() ) {
        ui->comboBox_parity->addItem(e.second);
    }
    for (auto e :  stopBitsS.toStdMap() ) {
        ui->comboBox_stopBits->addItem(e.second);
    }
    for (auto e :  flowControlS.toStdMap() ) {
        ui->comboBox_flowControl->addItem(e.second);
    }
    ui->comboBox_baudRate->setCurrentText("115200");
    ui->comboBox_dataBits->setCurrentText("8");

}
/////////////////////////////////////////////////////////////////
void Dialog_connect::fillBaudRate()
{
    baudRateS.insert(QSerialPort::Baud1200 , "1200");
    baudRateS.insert(QSerialPort::Baud2400 , "2400");
    baudRateS.insert(QSerialPort::Baud4800 , "4800");
    baudRateS.insert(QSerialPort::Baud9600 , "9600");
    baudRateS.insert(QSerialPort::Baud19200 , "19200");
    baudRateS.insert(QSerialPort::Baud38400 , "38400");
    baudRateS.insert(QSerialPort::Baud57600 , "57600");
    baudRateS.insert(QSerialPort::Baud115200 , "115200");
}
/////////////////////////////////////////////////////////////////
/// The number of data bits in each character
void Dialog_connect::fillDataBits()
{
    dataBitsS.insert(QSerialPort::Data5 , "5");
    dataBitsS.insert(QSerialPort::Data6 , "6");
    dataBitsS.insert(QSerialPort::Data7 , "7");
    dataBitsS.insert(QSerialPort::Data8 , "8");
}
/////////////////////////////////////////////////////////////////
void Dialog_connect::fillParity()
{
    parityS.insert(QSerialPort::NoParity , "none");
    parityS.insert(QSerialPort::EvenParity , "even");
    parityS.insert(QSerialPort::OddParity , "odd");
    parityS.insert(QSerialPort::SpaceParity , "space");
    parityS.insert(QSerialPort::MarkParity , "mark");
}
/////////////////////////////////////////////////////////////////
void Dialog_connect::fillstopBits()
{
    stopBitsS.insert(QSerialPort::OneStop , "1");
    stopBitsS.insert(QSerialPort::OneAndHalfStop , "1.5");
    stopBitsS.insert(QSerialPort::TwoStop , "2");
}
/////////////////////////////////////////////////////////////////
void Dialog_connect::fillflowControl()
{
    flowControlS.insert(QSerialPort::NoFlowControl , "none");
    flowControlS.insert(QSerialPort::HardwareControl , "HW");
    flowControlS.insert(QSerialPort::SoftwareControl , "SW");
}

/////////////////////////////////////////////////////////////////
int Dialog_connect::getFirstMapVal(QMap<int,QString> m, QString label)
{
    for (auto e : m.toStdMap())
    {
        if (label == e.second)
            return e.first;
    }
    return 0;
}
/////////////////////////////////////////////////////////////////
QString Dialog_connect::getSecondMapVal(QMap<int,QString> m, int val)
{
    for (auto e : m.toStdMap())
    {
        if (val == e.first)
            return e.second;
    }
    return nullptr;
}
///////////////////////////////////////////////////////////////////////
Dialog_connect::~Dialog_connect()
{
    delete ui;
}

//////////////////////////////////////////////////////////////////////////////
/// \brief Dialog_connect::on_buttonBox_accepted
///     read all parameters from the UI
void Dialog_connect::on_buttonBox_accepted()
{
    /* load the  port configuration to the sw class */
    param_sw->portName = ui->lineEdit_serialPortName->text();
    param_sw->baudRate = getFirstMapVal(baudRateS, ui->comboBox_baudRate->currentText());
    param_sw->dataBits = getFirstMapVal(dataBitsS, ui->comboBox_dataBits->currentText());
    param_sw->parity = getFirstMapVal(parityS, ui->comboBox_parity->currentText());
    param_sw->stopBits = getFirstMapVal(stopBitsS, ui->comboBox_stopBits->currentText());
    param_sw->flowControl = getFirstMapVal(flowControlS, ui->comboBox_flowControl->currentText());

    param_nw->IpAddr_Rx = QHostAddress(ui->lineEdit_selectedAddr_rx->text());
    param_nw->IpAddr_Tx = QHostAddress(ui->lineEdit_selectedAddr_tx->text());
    param_nw->port_Rx = quint16(ui->spinBox_ipPort_Rx->value());
    param_nw->port_Tx = quint16(ui->spinBox_ipPort_Tx->value());
    param_nw->protocolType = getSelectedNetworkProtocol();


    /* connect */
    switch (ui->tabWidget->currentIndex())
    {
    case 0:
        emit tryConnect(comType_serial);
        break;
    case 1:
        emit tryConnect(comType_network);
        break;
    }
}
/////////////////////////////////////////////////////////////////////
void Dialog_connect::on_buttonBox_rejected()
{
}
/////////////////////////////////////////////////////////////////////
int Dialog_connect::getSelectedNetworkProtocol()
{
    if (ui->comboBox_networkProtocol->currentText() == NETWORKPROTOCOL_UDP) {
        return UDP;
    }
    else if (ui->comboBox_networkProtocol->currentText() == NETWORKPROTOCOL_TCP) {
        return TCP;
    } else {
        return TCP;
    }
}

/////////////////////////////////////////////////////////////////////
/// \brief Dialog_connect::getProductIdentifier
///         search in available ports to the port and return it's productIdentifier
///         if the port name was not found, return -1
int Dialog_connect::getProductIdentifier(QString portName)
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.portName() == portName) {
            return int(info.productIdentifier());
        }
    }
    return -1;
}
//////////////////////////////////////////////////////////////////////////////
QString Dialog_connect::getSerialPortName(int productIdentifier)
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.productIdentifier() == productIdentifier) {
            return info.portName();
        }
    }
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////
void Dialog_connect::focus_1()
{
    ui->tabWidget->setCurrentIndex(0);
}
//////////////////////////////////////////////////////////////////////////////
void Dialog_connect::focus_2()
{
    ui->tabWidget->setCurrentIndex(1);
}

//////////////////////////////////////////////////////////////////////////////
void Dialog_connect::on_tableWidget_addr_rx_cellClicked(int row, int column)
{
    QString hostName = ui->tableWidget_addr_rx->item(row, 0)->text();
    ui->lineEdit_selectedAddr_rx->setText(hostName);
}

void Dialog_connect::on_tableWidget_addr_tx_cellClicked(int row, int column)
{
    QString hostName = ui->tableWidget_addr_tx->item(row, 0)->text();
    ui->lineEdit_selectedAddr_tx->setText(hostName);
}
//////////////////////////////////////////////////////////////////////////////

void Dialog_connect::on_tableWidget_serialPorts_cellClicked(int row, int column)
{
    QString portName = ui->tableWidget_serialPorts->item(row, 0)->text();
    ui->lineEdit_serialPortName->setText(portName);
}
//////////////////////////////////////////////////////////////////////////////
