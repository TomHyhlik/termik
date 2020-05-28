#include "dialog_connect.h"
#include "ui_dialog_connect.h"
#include "mainwindow.h"


#include <QMap>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QShortcut>
#include <QtDebug>

#include "networkscan.h"
#include "serialwparam.h"

void table_addItem(QTableWidget* table, QStringList element);
void table_clear(QTableWidget* table);


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

    networkScan = QSharedPointer <NetworkScan> (new NetworkScan);
    connect(networkScan.data(), SIGNAL(finished()), this, SLOT(networkScanFinished()));
    timer_updatePorts->start(SERIALPORT_REFRESH_PERIOD);

    refreshDevices();
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::pressedKeyUp()
{
    switch (ui->tabWidget->currentIndex())
    {
    case TAB_INDEX_SERIAL:
        table_makeAction(ui->tableWidget_serialPorts, tableAction_up);
        break;
    case TAB_INDEX_NETWORK:
        if (ui->tableWidget_addr_tx->hasFocus())
            table_makeAction(ui->tableWidget_addr_tx, tableAction_up);
//        else if (ui->tableWidget_addr_tx->hasFocus())
        else
            table_makeAction(ui->tableWidget_addr_rx, tableAction_up);

        break;
    }
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::pressedKeyDown()
{
    switch (ui->tabWidget->currentIndex())
    {
    case TAB_INDEX_SERIAL:
        table_makeAction(ui->tableWidget_serialPorts, tableAction_down);
        break;
    case TAB_INDEX_NETWORK:
        if (ui->tableWidget_addr_tx->hasFocus())
            table_makeAction(ui->tableWidget_addr_tx, tableAction_down);
//        else if (ui->tableWidget_addr_tx->hasFocus())
        else
            table_makeAction(ui->tableWidget_addr_rx, tableAction_down);

        break;
    }
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::pressedKeyLeft()
{
    switch (ui->tabWidget->currentIndex())
    {
    case TAB_INDEX_NETWORK:
        ui->tableWidget_addr_rx->setFocus();
        break;
    }
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::pressedKeyRight()
{
    switch (ui->tabWidget->currentIndex())
    {
    case TAB_INDEX_NETWORK:
        ui->tableWidget_addr_tx->setFocus();
        break;
    }
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::table_makeAction(QTableWidget* tableWidget, int actionType)
{
    switch (actionType)
    {
    case tableAction_up:
        if (tableWidget->currentRow() > 0)
            tableWidget->selectRow(tableWidget->currentRow() - 1);
        break;
    case tableAction_down:
        if (tableWidget->currentRow() < tableWidget->rowCount())
            tableWidget->selectRow(tableWidget->currentRow() + 1);
        break;
    }
}
/////////////////////////////////////////////////////////////////
void Dialog_connect::lineEdit_updateToTableRow(QLineEdit* lineEdit, QTableWidget *table, int row)
{
    QString name = table->item(row, 0)->text();
    lineEdit->setText(name);
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::shortcuts_init()
{
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_1), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_2), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(EscPressed()));

    new QShortcut(QKeySequence(Qt::Key_Up), this, SLOT(pressedKeyUp()));
    new QShortcut(QKeySequence(Qt::Key_Down), this, SLOT(pressedKeyDown()));
    new QShortcut(QKeySequence(Qt::Key_Left), this, SLOT(pressedKeyLeft()));
    new QShortcut(QKeySequence(Qt::Key_Right), this, SLOT(pressedKeyRight()));

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
    ui->comboBox_baudRate->setCurrentText(getSecondMapVal(baudRateS, SerialWParam::get().baudRate));
    ui->comboBox_dataBits->setCurrentText(getSecondMapVal(dataBitsS, SerialWParam::get().dataBits));
    ui->comboBox_parity->setCurrentText(getSecondMapVal(parityS, SerialWParam::get().parity));
    ui->comboBox_stopBits->setCurrentText(getSecondMapVal(stopBitsS, SerialWParam::get().stopBits));
    ui->comboBox_flowControl->setCurrentText(getSecondMapVal(flowControlS, SerialWParam::get().flowControl));

    if (!NetworkWParam::get().IpAddr_Rx.toString().isEmpty())
        ui->lineEdit_selectedAddr_rx->setText(NetworkWParam::get().IpAddr_Rx.toString());
    if (!NetworkWParam::get().IpAddr_Tx.toString().isEmpty())
        ui->lineEdit_selectedAddr_tx->setText(NetworkWParam::get().IpAddr_Tx.toString());

    ui->spinBox_ipPort_Tx->setValue(NetworkWParam::get().port_Tx);
    ui->spinBox_ipPort_Rx->setValue(NetworkWParam::get().port_Rx);
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
    this->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                        .arg(COLOR_WHITE).arg(COLOR_GRAY1));

    ui->tab_serial->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                  .arg(COLOR_WHITE).arg(COLOR_GRAY2));
    ui->tab_network->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                   .arg(COLOR_WHITE).arg(COLOR_GRAY2));

    ui->comboBox_baudRate->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_dataBits->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_flowControl->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                            .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_parity->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                       .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_serialPortName->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                               .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_stopBits->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_networkProtocol->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->spinBox_ipPort_Tx->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->spinBox_ipPort_Rx->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->tableWidget_serialPorts->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                               .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->tableWidget_addr_rx->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                           .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->tableWidget_addr_tx->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                           .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_selectedAddr_rx->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->lineEdit_selectedAddr_tx->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                .arg(COLOR_WHITE).arg(COLOR_BLACK));
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::refreshDevices()
{
    serialPort_nameRefresh();
    networkScan->start();
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::table_addHost(QTableWidget* tableWidget, QHostInfo host)
{
    QStringList element;
    element << host.addresses().first().toString() << host.hostName();
    table_addItem(tableWidget, element);
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::table_updateHosts(QTableWidget* tableWidget,
                                       const QList <QHostInfo> hosts)
{
    bool isHere;

    /* remove missing*/
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        for (const QHostInfo& host : hosts)
        {
            if (tableWidget->item(i, 0)->text()
                    == host.addresses().first().toString())
            {
                isHere = true;
                break;
            }
        }
        if (!isHere) {
            tableWidget->removeRow(i);
        }
    }
    /* add new */
    isHere= false;
    for (const QHostInfo& host : hosts)
    {
        for (int i = 0; i < tableWidget->rowCount(); i++)
        {
            if (tableWidget->item(i, 0)->text()
                    == host.addresses().first().toString())
            {
                isHere = true;
                break;
            }
        }
        if (!isHere) {
            table_addHost(tableWidget, host);
        }
    }
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::networkScanFinished()
{
    table_updateHosts(ui->tableWidget_addr_rx, networkScan->get_addrs_devThis());
    table_updateHosts(ui->tableWidget_addr_tx, networkScan->get_addrs_devAll());
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
    qDebug() << "\n Dialog_connect destroyed \n";
    delete ui;
}

//////////////////////////////////////////////////////////////////////////////
/// \brief Dialog_connect::on_buttonBox_accepted
///     read all parameters from the UI
void Dialog_connect::on_buttonBox_accepted()
{
    /* load the  port configuration to the sw class */
    SerialWParam::get().portName = ui->lineEdit_serialPortName->text();
    SerialWParam::get().baudRate = getFirstMapVal(baudRateS, ui->comboBox_baudRate->currentText());
    SerialWParam::get().dataBits = getFirstMapVal(dataBitsS, ui->comboBox_dataBits->currentText());
    SerialWParam::get().parity = getFirstMapVal(parityS, ui->comboBox_parity->currentText());
    SerialWParam::get().stopBits = getFirstMapVal(stopBitsS, ui->comboBox_stopBits->currentText());
    SerialWParam::get().flowControl = getFirstMapVal(flowControlS, ui->comboBox_flowControl->currentText());

    NetworkWParam::get().IpAddr_Rx = QHostAddress(ui->lineEdit_selectedAddr_rx->text());
    NetworkWParam::get().IpAddr_Tx = QHostAddress(ui->lineEdit_selectedAddr_tx->text());
    NetworkWParam::get().port_Rx = quint16(ui->spinBox_ipPort_Rx->value());
    NetworkWParam::get().port_Tx = quint16(ui->spinBox_ipPort_Tx->value());
    NetworkWParam::get().protocolType = getSelectedNetworkProtocol();

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
    this->close();
}
/////////////////////////////////////////////////////////////////////
void Dialog_connect::on_buttonBox_rejected()
{
    this->close();
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
void Dialog_connect::on_tableWidget_addr_rx_currentCellChanged(int row, int column)
{
    lineEdit_updateToTableRow(ui->lineEdit_selectedAddr_rx, ui->tableWidget_addr_rx, row);
    (void)column;
}

void Dialog_connect::on_tableWidget_addr_tx_currentCellChanged(int row, int column)
{
    lineEdit_updateToTableRow(ui->lineEdit_selectedAddr_tx, ui->tableWidget_addr_tx, row);
    (void)column;
}

void Dialog_connect::on_tableWidget_serialPorts_currentCellChanged(int row, int column)
{
    lineEdit_updateToTableRow(ui->lineEdit_serialPortName, ui->tableWidget_serialPorts, row);
    (void)column;
}
//////////////////////////////////////////////////////////////////////////////
