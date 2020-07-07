#include "dialog_connect.h"
#include "ui_dialog_connect.h"
#include "mainwindow.h"


#include <QMap>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QShortcut>
#include <QtDebug>
#include <QElapsedTimer>

#include "networkscan.h"
#include "serialwparam.h"

void table_addItem(QTableWidget* table, QStringList element);
void table_clear(QTableWidget* table);

///////////////////////////////////////////////////////////////////
Dialog_connect::Dialog_connect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_connect)
{
    ui->setupUi(this);

    shortcuts_init();
    table_network_init();
    table_serial_init();
    initWindow();
    initColors();
    initScan();
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
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::loadParametersToUi()
{
    ui->lineEdit_serialPortName->setText(SerialWParam::get().portName);
    ui->comboBox_baudRate->setCurrentText(map_baudRate.value(SerialWParam::get().baudRate));
    ui->comboBox_dataBits->setCurrentText(map_dataBits.value(SerialWParam::get().dataBits));
    ui->comboBox_parity->setCurrentText(map_parity.value(SerialWParam::get().parity));
    ui->comboBox_stopBits->setCurrentText(map_stopBits.value(SerialWParam::get().stopBits));
    ui->comboBox_flowControl->setCurrentText(map_flowControl.value(SerialWParam::get().flowControl));

    ui->lineEdit_selectedAddr_rx->setText(NetworkWParam::get().IpAddr_Rx.toString());
    ui->lineEdit_selectedAddr_tx->setText(NetworkWParam::get().IpAddr_Tx.toString());

    ui->spinBox_ipPort_Tx->setValue(NetworkWParam::get().port_Tx);
    ui->spinBox_ipPort_Rx->setValue(NetworkWParam::get().port_Rx);

    ui->comboBox_networkProtocol->setCurrentText(map_networkProtocol.value(NetworkWParam::get().protocolType));
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::refreshDevices()
{
    serialPort_nameRefresh();

    if (ui->checkBox_enableNetworkScan->isChecked())
        networkScan->startScan_addrs_devAll();

    networkScan->startScan_addrs_devThis();
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::table_addHost(QTableWidget* tableWidget, const QHostInfo host)
{
    QStringList element;
    element << host.addresses().first().toString() << host.hostName();
    table_addItem(tableWidget, element);
}

bool Dialog_connect::table_includesHost(QTableWidget* tableWidget, const QHostInfo host)
{
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        if (tableWidget->item(i, 0)->text()
                == host.addresses().first().toString())
        {
            return true;
        }
    }
    return false;
}

void Dialog_connect::table_addHostIfNotIncluded(QTableWidget* tableWidget, const QHostInfo host)
{
    if (!table_includesHost(tableWidget, host))
    {
        table_addHost(tableWidget, host);
    }
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::table_updateHosts(QTableWidget* tableWidget,
                                       const QList <QHostInfo> hosts)
{
    /* remove missing */
    for (int i = 0; i < tableWidget->rowCount(); i++)
    {
        bool isHere = false;
        for (const QHostInfo& host : hosts)
        {
            if (tableWidget->item(i, 0)->text()
                    == host.addresses().first().toString())
            {
                isHere = true;
                break;
            }
        }
        if (!isHere)
            tableWidget->removeRow(i);
    }

    /* add new from the list */
    for (const QHostInfo& host : hosts)
    {
        table_addHostIfNotIncluded(tableWidget, host);
    }
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::serialPort_nameRefresh()
{
    QElapsedTimer t;
    t.start();

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

//    ui->tabWidget->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
//                                 .arg(COLOR_WHITE).arg(COLOR_GRAY3));

#if PLATFORM_WINDOWS
    ui->tabWidget->tabBar()->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                           .arg(COLOR_BLACK).arg(COLOR_BLACK));

    ui->tableWidget_serialPorts->horizontalHeader()->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                                   .arg(COLOR_BLACK).arg(COLOR_GRAY0));
    ui->tableWidget_serialPorts->verticalHeader()->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                                 .arg(COLOR_BLACK).arg(COLOR_GRAY0));

    ui->tableWidget_addr_rx->horizontalHeader()->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                               .arg(COLOR_BLACK).arg(COLOR_GRAY0));
    ui->tableWidget_addr_rx->verticalHeader()->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                             .arg(COLOR_BLACK).arg(COLOR_GRAY0));

    ui->tableWidget_addr_tx->horizontalHeader()->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                               .arg(COLOR_BLACK).arg(COLOR_GRAY0));
    ui->tableWidget_addr_tx->verticalHeader()->setStyleSheet(QString(STR_STYLESHEET_COLOR_BCKGCOLOR)
                                                             .arg(COLOR_BLACK).arg(COLOR_GRAY0));

#endif

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
    SerialWParam::get().portName = ui->lineEdit_serialPortName->text();
    SerialWParam::get().baudRate = map_baudRate.key(ui->comboBox_baudRate->currentText());
    SerialWParam::get().dataBits = map_dataBits.key(ui->comboBox_dataBits->currentText());
    SerialWParam::get().parity = map_parity.key(ui->comboBox_parity->currentText());
    SerialWParam::get().stopBits = map_stopBits.key(ui->comboBox_stopBits->currentText());
    SerialWParam::get().flowControl = map_flowControl.key(ui->comboBox_flowControl->currentText());

    NetworkWParam::get().IpAddr_Rx = QHostAddress(ui->lineEdit_selectedAddr_rx->text());
    NetworkWParam::get().IpAddr_Tx = QHostAddress(ui->lineEdit_selectedAddr_tx->text());
    NetworkWParam::get().port_Rx = quint16(ui->spinBox_ipPort_Rx->value());
    NetworkWParam::get().port_Tx = quint16(ui->spinBox_ipPort_Tx->value());
    NetworkWParam::get().protocolType = map_networkProtocol.key(ui->comboBox_networkProtocol->currentText());

    emit tryConnect(communicationType(ui->tabWidget->currentIndex()));
    this->close();
}

/////////////////////////////////////////////////////////////////////
void Dialog_connect::on_buttonBox_rejected()
{
    this->close();
}

//////////////////////////////////////////////////////////////////////////////
void Dialog_connect::focus_1()
{
    ui->tabWidget->setCurrentIndex(TAB_INDEX_SERIAL);
}
//////////////////////////////////////////////////////////////////////////////
void Dialog_connect::focus_2()
{
    ui->tabWidget->setCurrentIndex(TAB_INDEX_NETWORK);
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
void Dialog_connect::on_comboBox_networkProtocol_currentIndexChanged(int index)
{
    switch (index)
    {
    case networkProtocolType_udp:
    case networkProtocolType_tcp_client:
        ui->groupBox_network_tx->show();
        break;
    case networkProtocolType_tcp_server:
        ui->groupBox_network_tx->hide();
        break;
    }
}
//////////////////////////////////////////////////////////////////////////////
void Dialog_connect::initWindow()
{
    setWindowTitle(TITLE_THIS_WINDOW);
    ui->tabWidget->setTabText(0, TITLE_TAB_SERIAL);
    ui->tabWidget->setTabText(1, TITLE_TAB_NETWORK);
    ui->spinBox_ipPort_Tx->setMaximum(PORT_RANGE);
    ui->spinBox_ipPort_Rx->setMaximum(PORT_RANGE);

#if NETWORKSCAN_ENABLE_DEFAULT
    ui->checkBox_enableNetworkScan->setChecked(true);
#endif

    for (auto e :  map_baudRate.toStdMap())
        ui->comboBox_baudRate->addItem(e.second);
    for (auto e :  map_dataBits.toStdMap())
        ui->comboBox_dataBits->addItem(e.second);
    for (auto e :  map_parity.toStdMap())
        ui->comboBox_parity->addItem(e.second);
    for (auto e :  map_stopBits.toStdMap())
        ui->comboBox_stopBits->addItem(e.second);
    for (auto e :  map_flowControl.toStdMap())
        ui->comboBox_flowControl->addItem(e.second);
    for (auto e :  map_networkProtocol.toStdMap())
        ui->comboBox_networkProtocol->addItem(e.second);
}

//////////////////////////////////////////////////////////////////////////////
/// \brief Dialog_connect::initScan
/// Setup periodical scan of serial and network devices
void Dialog_connect::initScan()
{
    timer_updatePorts = QSharedPointer <QTimer> (new QTimer);
    connect(timer_updatePorts.data(), SIGNAL(timeout()), this, SLOT(refreshDevices()));

    networkScan = QSharedPointer <NetworkScan> (new NetworkScan);
    connect(networkScan.get(), &NetworkScan::devAll_finished, this, &Dialog_connect::addrUpdate_devAll);
    connect(networkScan.get(), &NetworkScan::devThis_finished, this,  &Dialog_connect::addrUpdate_devThis);

    networkHostsFirstRefresh = true;
    refreshDevices();
    timer_updatePorts->start(PERIOD_REFRESHDEVICES);
}

//////////////////////////////////////////////////////////////////////////////
void Dialog_connect::addrUpdate_devThis()
{
    table_updateHosts(ui->tableWidget_addr_rx, networkScan->get_addrs_devThis());
}

///////////////////////////////////////////////////////////////////
void Dialog_connect::addrUpdate_devAll()
{
    table_updateHosts(ui->tableWidget_addr_tx, networkScan->get_addrs_devAll());

    /* focus on the last address in the table */
    if (networkHostsFirstRefresh) {
        networkHostsFirstRefresh = false;
        if (ui->lineEdit_selectedAddr_rx->text().isEmpty())
            ui->tableWidget_addr_rx->selectRow(ui->tableWidget_addr_rx->rowCount() -1);
        if (ui->lineEdit_selectedAddr_tx->text().isEmpty())
            ui->tableWidget_addr_tx->selectRow(ui->tableWidget_addr_tx->rowCount() -1);
    }
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::pressedKeyArrowWertical(int tableAction)
{
    switch (ui->tabWidget->currentIndex())
    {
    case TAB_INDEX_SERIAL:
        table_makeAction(ui->tableWidget_serialPorts, tableAction);
        break;
    case TAB_INDEX_NETWORK:
        if (ui->tableWidget_addr_tx->hasFocus())
            table_makeAction(ui->tableWidget_addr_tx, tableAction);
        else
            table_makeAction(ui->tableWidget_addr_rx, tableAction);
        break;
    }
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::pressedKeyDown()
{
    pressedKeyArrowWertical(tableAction_down);
}

void Dialog_connect::pressedKeyUp()
{
    pressedKeyArrowWertical(tableAction_up);
}

/////////////////////////////////////////////////////////////////
void Dialog_connect::pressedKeyLeft()
{
    if (ui->tabWidget->currentIndex() == TAB_INDEX_NETWORK)
    {
        ui->tableWidget_addr_rx->setFocus();
    }
}

void Dialog_connect::pressedKeyRight()
{
    if (ui->tabWidget->currentIndex() == TAB_INDEX_NETWORK)
    {
        ui->tableWidget_addr_tx->setFocus();
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
