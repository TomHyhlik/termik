#include "dialog_connect.h"
#include "ui_dialog_connect.h"
#include "mainwindow.h"


#include <QMap>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QShortcut>

Dialog_connect::Dialog_connect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_connect)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(serial);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), this, SLOT(focus_2()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_1), this, SLOT(focus_1()));
    new QShortcut(QKeySequence(Qt::ALT + Qt::Key_2), this, SLOT(focus_2()));

}

/////////////////////////////////////////////////////////////////
/// \brief Dialog_connect::showEvent
/// called when the dialog is shown
void Dialog_connect::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );

    refreshParameters();
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::refreshParameters()
{
    ui->comboBox_baudRate->setCurrentText(getSecondMapVal(baudRateS, sw->param.baudRate));
    ui->comboBox_dataBits->setCurrentText(getSecondMapVal(dataBitsS, sw->param.dataBits));
    ui->comboBox_parity->setCurrentText(getSecondMapVal(parityS, sw->param.parity));
    ui->comboBox_stopBits->setCurrentText(getSecondMapVal(stopBitsS, sw->param.stopBits));
    ui->comboBox_flowControl->setCurrentText(getSecondMapVal(flowControlS, sw->param.flowControl));

    QStringList ipAddrs_rx = nw->getAll_iPaddr_rx();
    for (int i = 0; i < ipAddrs_rx.size(); i++)
        ui->comboBox_ipAddr_rx->addItem(ipAddrs_rx.at(i));

    if (!nw->param.IpAddr_Rx.toString().isEmpty())
        ui->comboBox_ipAddr_rx->setCurrentText(nw->param.IpAddr_Rx.toString());
    if (!nw->param.IpAddr_Tx.toString().isEmpty())
        ui->comboBox_ipAddr_tx->setCurrentText(nw->param.IpAddr_Tx.toString());

    ui->spinBox_ipPort_Tx->setValue(nw->param.port_Tx);
    ui->spinBox_ipPort_Rx->setValue(nw->param.port_Rx);
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::blockAllsignals(bool state)
{
    ui->comboBox_baudRate->blockSignals(state);
    ui->comboBox_parity->blockSignals(state);
    ui->comboBox_dataBits->blockSignals(state);
    ui->comboBox_portName->blockSignals(state);
    ui->comboBox_stopBits->blockSignals(state);
    ui->comboBox_flowControl->blockSignals(state);
}
/////////////////////////////////////////////////////////////////
void Dialog_connect::init()
{
    setWindowTitle(TITLE_THIS_WINDOW);
    ui->tabWidget->setTabText(serial, TITLE_TAB_SERIAL);
    ui->tabWidget->setTabText(network, TITLE_TAB_NETWORK);
    ui->spinBox_ipPort_Tx->setMaximum(PORT_RANGE);
    ui->spinBox_ipPort_Rx->setMaximum(PORT_RANGE);

    ui->comboBox_networkProtocol->addItem(NETWORKPROTOCOL_UDP);
    ui->comboBox_networkProtocol->addItem(NETWORKPROTOCOL_TCP);

    initColors();
    tab_port_init();

    timer_updatePorts = new QTimer(this);
    connect(timer_updatePorts, SIGNAL(timeout()), this, SLOT(serialPort_nameRefresh()));
    timer_updatePorts->start(SERIALPORT_REFRESH_PERIOD);

    ui->comboBox_portName->setFocus();
    currentTab = ui->tabWidget->currentIndex();
    //    configurationRead(); << todo
}
/////////////////////////////////////////////////////////////////
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
    ui->comboBox_portName->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_stopBits->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));

    ui->spinBox_ipPort_Tx->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->spinBox_ipPort_Rx->setStyleSheet(QString("color: %1; background-color: %2")
                                         .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_ipAddr_rx->setStyleSheet(QString("color: %1; background-color: %2")
                                          .arg(COLOR_WHITE).arg(COLOR_BLACK));
    ui->comboBox_ipAddr_tx->setStyleSheet(QString("color: %1; background-color: %2")
                                          .arg(COLOR_WHITE).arg(COLOR_BLACK));

}

/////////////////////////////////////////////////////////////////
void Dialog_connect::serialPort_nameRefresh()
{
    QList <QSerialPortInfo> currentAvailablePorts = QSerialPortInfo::availablePorts();


    /* delete ports which were plugged out */
    for (int i = 0; i < ui->comboBox_portName->count(); i++) {
        bool isHere = false;
        for (int j = 0; j < currentAvailablePorts.size(); j++) {
            if (ui->comboBox_portName->itemText(i) == currentAvailablePorts.at(j).portName()) {
                isHere = true;
                break;
            }
        }
        if(!isHere){
            ui->comboBox_portName->removeItem(i);
        }

    }

    /* add ports which were plugged in */
    if (ui->comboBox_portName->count() != currentAvailablePorts.size()) {
        for (int j = 0; j < currentAvailablePorts.size(); j++) {
            bool isHere = false;
            for(int i = 0; i < ui->comboBox_portName->count(); i++){
                if(currentAvailablePorts.at(j).portName() == ui->comboBox_portName->itemText(i)){
                    isHere = true;
                    break;
                }
            }
            if(!isHere){
                ui->comboBox_portName->addItem(currentAvailablePorts.at(j).portName());
            }
        }
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
///////////////////////////////////////////////////////////////////////
void Dialog_connect::on_tabWidget_currentChanged(int index)
{
    currentTab = index;
}

///////////////////////////////////////////////////////////////////////
/// \brief Read information about selected port and put it to the QLabels
///         and update the port name in SerialWorker class
/// \param arg1: the port name from the combobox
void Dialog_connect::on_comboBox_portName_currentTextChanged(const QString &arg1)
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        /* if the port name is known, print info */
        if(info.portName() == arg1){
            ui->label_portDescription->setText(QString("Description: %1")
                                               .arg(info.description()));
            ui->label_manufacturer->setText(QString("Manufacturer: %1")
                                            .arg(info.manufacturer()));
            ui->label_serialNumber->setText(QString("Serial number: %1")
                                            .arg(info.serialNumber()));
            ui->label_location->setText(QString("Location: %1")
                                        .arg(info.systemLocation()));
            ui->label_vendorIdentifier->setText(QString("Vendor identifier: %1")
                                                .arg(info.vendorIdentifier()));
            ui->label_productIdentifier->setText(QString("Product identifier: %1")
                                                 .arg(info.productIdentifier()));
            return;
        }
    }
    /* othervise leave it empty */
    ui->label_portDescription->setText(QString("Description: "));
    ui->label_manufacturer->setText(QString("Manufacturer: "));
    ui->label_serialNumber->setText(QString("Serial number: "));
    ui->label_location->setText(QString("Location: "));
    ui->label_vendorIdentifier->setText(QString("Vendor identifier: "));
    ui->label_productIdentifier->setText(QString("Product identifier: "));

}
//////////////////////////////////////////////////////////////////////////////
/// \brief Dialog_connect::on_buttonBox_accepted
///     read all parameters from the UI
void Dialog_connect::on_buttonBox_accepted()
{
    /* load the  port configuration to the sw class */
    sw->param.portName = ui->comboBox_portName->currentText();
    sw->param.baudRate = getFirstMapVal(baudRateS, ui->comboBox_baudRate->currentText());
    sw->param.dataBits = getFirstMapVal(dataBitsS, ui->comboBox_dataBits->currentText());
    sw->param.parity = getFirstMapVal(parityS, ui->comboBox_parity->currentText());
    sw->param.stopBits = getFirstMapVal(stopBitsS, ui->comboBox_stopBits->currentText());
    sw->param.flowControl = getFirstMapVal(flowControlS, ui->comboBox_flowControl->currentText());

    nw->param.IpAddr_Rx = QHostAddress(ui->comboBox_ipAddr_rx->currentText());
    nw->param.IpAddr_Tx = QHostAddress(ui->comboBox_ipAddr_tx->currentText());
    nw->param.port_Rx = quint16(ui->spinBox_ipPort_Rx->value());
    nw->param.port_Tx = quint16(ui->spinBox_ipPort_Tx->value());
    nw->param.protocolType = getSelectedNetworkProtocol();


    /* connect */
    switch (ui->tabWidget->currentIndex())
    {
    case serial:
        emit tryConnect(serial);
        break;
    case network:
        emit tryConnect(network);
        break;
    }
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
