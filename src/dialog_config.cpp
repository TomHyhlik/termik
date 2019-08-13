#include "dialog_config.h"
#include "ui_dialog_config.h"

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
/////////////////////////////////////////////////////////////////

SerialWorker *dialog_config::getSw() const
{
    return sw;
}
void dialog_config::setSw(SerialWorker *value)
{
    sw = value;
}
/////////////////////////////////////////////////////////////////
dialog_config::dialog_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_config)
{
    ui->setupUi(this);
    this->setWindowTitle("Terminal configuration");     // set name of this dialog

    tab_port_init();

    ui->checkBox_splitFactor->setChecked(true);
    ui->checkBox_autoClearIn->setChecked(false);


}
/////////////////////////////////////////////////////////////////
/// \brief dialog_config::tab_input_init
/// initialize tab named input
void dialog_config::tab_input_init()
{
    /* set format options */
    ui->comboBox_format->addItem("ASCII");
    ui->comboBox_format->addItem("HEX");

    ui->comboBox_prefix->addItem("HEX");
    ui->comboBox_suffix->addItem("HEX");

    /* read the suffix from the SerialWorker class */
    ui->lineEdit_suffix->setText(QString::fromUtf8(sw->suffix.toHex()));

}
/////////////////////////////////////////////////////////////////
void dialog_config::tab_output_init()
{
    ui->comboBox_splitFactor->addItem("HEX");
    ui->lineEdit_splitFactor->setText(QString::fromUtf8(sw->splitFactor.toHex()));
}
/////////////////////////////////////////////////////////////////
void dialog_config::tab_port_init()
{
    /* fill maps of comboboxes */
    fillBaudRate();
    fillDataBits();
    fillParity();
    fillstopBits();
    fillflowControl();

    /* fill comboboxes */
    for (auto e :  baudRateS.toStdMap() ) {
        ui->comboBox_2->addItem(e.second);
    }
    for (auto e :  dataBitsS.toStdMap() ) {
        ui->comboBox_3->addItem(e.second);
    }
    for (auto e :  parityS.toStdMap() ) {
        ui->comboBox_4->addItem(e.second);
    }
    for (auto e :  stopBitsS.toStdMap() ) {
        ui->comboBox_5->addItem(e.second);
    }
    for (auto e :  flowControlS.toStdMap() ) {
        ui->comboBox_6->addItem(e.second);
    }
    ui->comboBox_2->setCurrentText("9600");
    ui->comboBox_3->setCurrentText("8");
}
///////////////////////////////////////////////////////////////////
//////////////////////////////////////// Set the new configuration
///////////////////////////////////////////////////////////////////
void dialog_config::on_buttonBox_accepted()
{
    sw->close();        // closses if it is open

    /* read port configuration */
    sw->portName = ui->comboBox_portName->currentText();
    sw->baudRate = getFirstMapVal(baudRateS, ui->comboBox_2->currentText());
    sw->dataBits = getFirstMapVal(dataBitsS, ui->comboBox_3->currentText());
    sw->parity = getFirstMapVal(parityS, ui->comboBox_4->currentText());
    sw->stopBits = getFirstMapVal(stopBitsS, ui->comboBox_5->currentText());
    sw->flowControl = getFirstMapVal(flowControlS, ui->comboBox_6->currentText());

    /* set the prefix, suffix and split factor */
    sw->prefix = QByteArray::fromHex(ui->lineEdit_prefix->text().toUpper().toUtf8());
    sw->suffix = QByteArray::fromHex(ui->lineEdit_suffix->text().toUpper().toUtf8());
    sw->splitFactor = QByteArray::fromHex(ui->lineEdit_splitFactor->text().toUpper().toUtf8());
    sw->splitFactor_enable = ui->checkBox_splitFactor->isChecked();

    autoClearIn = ui->checkBox_autoClearIn->isChecked();


    /* pass arguments to MainWindow to display it */
    emit portConfigDisplay(ui->comboBox_portName->currentText(), ui->comboBox_2->currentText(),
                 ui->comboBox_3->currentText(), ui->comboBox_4->currentText(),
                 ui->comboBox_5->currentText(), ui->comboBox_6->currentText());

    /* set the status bar of MainWindow */
    if(sw->open()){
        emit connected(true);
    } else {
        emit connected(false);
    }
}

/////////////////////////////////////////////////////////////////
void dialog_config::on_buttonBox_rejected()
{

}
/////////////////////////////////////////////////////////////////
void dialog_config::fillBaudRate()
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
void dialog_config::fillDataBits()
{
    dataBitsS.insert(QSerialPort::Data5 , "5");
    dataBitsS.insert(QSerialPort::Data6 , "6");
    dataBitsS.insert(QSerialPort::Data7 , "7");
    dataBitsS.insert(QSerialPort::Data8 , "8");
}
/////////////////////////////////////////////////////////////////
void dialog_config::fillParity()
{
    parityS.insert(QSerialPort::NoParity , "none");
    parityS.insert(QSerialPort::EvenParity , "even");
    parityS.insert(QSerialPort::OddParity , "odd");
    parityS.insert(QSerialPort::SpaceParity , "space");
    parityS.insert(QSerialPort::MarkParity , "mark");
}
/////////////////////////////////////////////////////////////////
void dialog_config::fillstopBits()
{
    stopBitsS.insert(QSerialPort::OneStop , "1");
    stopBitsS.insert(QSerialPort::OneAndHalfStop , "1.5");
    stopBitsS.insert(QSerialPort::TwoStop , "2");
}
/////////////////////////////////////////////////////////////////
void dialog_config::fillflowControl()
{
    flowControlS.insert(QSerialPort::NoFlowControl , "none");
    flowControlS.insert(QSerialPort::HardwareControl , "HW");
    flowControlS.insert(QSerialPort::SoftwareControl , "SW");
}
/////////////////////////////////////////////////////////////////
/// \brief dialog_config::getFirstMapVal return the opposite value
/// of the map
/// \param m: map
/// \param label the second value of the map
/// \return tohe opposite value
int dialog_config::getFirstMapVal(QMap<int,QString> m, QString label)
{
    for(auto e : m.toStdMap())
    {
        if(label == e.second)
            return e.first;
    }
    return 0;
}

/////////////////////////////////////////////////////////////////
/// \brief Read information about selected port
/// \param arg1: the port name from the combobox
void dialog_config::on_comboBox_portName_currentTextChanged(const QString &arg1)
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(info.portName() == arg1)
        {
            ui->label_description->setText(QString("Description: %1")
                                           .arg(info.description()));
            ui->label_manufacturer->setText(QString("Manufacturer: %1")
                                            .arg(info.manufacturer()));

            ui->label_serialNumber->setText(QString("Serial number: %1")
                                            .arg(info.serialNumber()));
            ui->label_location->setText(QString("Location: %1")
                                        .arg(info.systemLocation()));

            ui->label_vendorIdentifier->setText(QString("Vendor identifier: %1")
                                                .arg(info.vendorIdentifier()));
            ui->label_productIdentifier->setText(QString("productIdentifier: %1")
                                                 .arg(info.productIdentifier()));
        }
    }
}
/////////////////////////////////////////////////////////////////
/// \brief refresh available ports
void dialog_config::on_pushButton_refresh_clicked()
{
    ui->comboBox_portName->clear();
    /* read and add available ports to the combobox */
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboBox_portName->addItem(info.portName());
    }
}
/////////////////////////////////////////////////////////////////
dialog_config::~dialog_config()
{
    delete ui;
}
/////////////////////////////////////////////////////////////////
