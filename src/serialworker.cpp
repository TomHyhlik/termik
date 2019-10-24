#include "serialworker.h"

#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QThread>

#include <QDebug>


///////////////////////////////////////////////////////////////////////////////
SerialWorker::SerialWorker(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
    connect(serial, &QIODevice::readyRead, this, &SerialWorker::readData);

    setDefaultParameters();
}
///////////////////////////////////////////////////////////////////////////////
void SerialWorker::setDefaultParameters()
{
    param.baudRate = QSerialPort::Baud115200;
    param.dataBits = QSerialPort::Data8;
    param.parity = QSerialPort::NoParity;
    param.stopBits = QSerialPort::OneStop;
    param.flowControl = QSerialPort::NoFlowControl;
}
///////////////////////////////////////////////////////////////////////////////
bool SerialWorker::open()
{
    if (serial->isOpen()) {
        serial->close();
    }

    serial->setPortName(param.portName);
    serial->setBaudRate(QSerialPort::BaudRate(param.baudRate));
    serial->setDataBits(QSerialPort::DataBits(param.dataBits));
    serial->setParity(QSerialPort::Parity(param.parity));
    serial->setStopBits(QSerialPort::StopBits(param.stopBits));
    serial->setFlowControl(QSerialPort::FlowControl(param.flowControl));

    serial->open(QIODevice::ReadWrite);

    if (serial->isOpen() && serial->isWritable()){
        return true;
    } else {
        return false;
    }
}
///////////////////////////////////////////////////////////////////////////////
bool SerialWorker::close()
{
    if (serial->isOpen()){
        serial->close();
        return true;
    } else {
        return false;
    }
}
///////////////////////////////////////////////////////////////////////////////
bool SerialWorker::isOpen(){
    if (serial->isOpen() && serial->isWritable()){         // debug
        return true;                // sPort opened
    }
    else{
        return false;               // sPort not open
    }
}

///////////////////////////////////////////////////////////////////////////////
bool SerialWorker::write(QByteArray data)
{
    serial->write(data);          // send over USB
//    serial->waitForBytesWritten(50);

//    qDebug() << "TX: " << data.toHex();


    if(serial->flush()){          // check if data were send to serial port
        return true;
    } else {
        return false;
    }    
}
///////////////////////////////////////////////////////////////////////////////
void SerialWorker::readData()
{
    QByteArray data = serial->readAll();
    RxData.append(data);
    emit dataReceived();

//    qDebug() << "RX: " << data.toHex();
}
///////////////////////////////////////////////////////////////////////////////
QByteArray SerialWorker::ReadAllRx()
{
    QByteArray out;
    while (!RxData.isEmpty()) {
        out.append(RxData.first());
        RxData.pop_front();
    }
    return out;
}










