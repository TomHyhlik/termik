#include "serialworker.h"

#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QThread>




///////////////////////////////////////////////////////////////////////////////
SerialWorker::SerialWorker(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);

    connect(serial, &QIODevice::readyRead, this, &SerialWorker::readData);

    splitFactor_enabled = false;
}

///////////////////////////////////////////////////////////////////////////////
bool SerialWorker::open()
{
    serial->setPortName(param.portName);
    serial->setBaudRate(QSerialPort::BaudRate(param.baudRate));
    serial->setFlowControl(QSerialPort::FlowControl(param.flowControl));
    serial->setDataBits(QSerialPort::DataBits(param.dataBits));
    serial->setStopBits(QSerialPort::StopBits(param.stopBits));
    serial->setParity(QSerialPort::Parity(param.parity));

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
    Rx_buffer.append(data.data());
    emit dataReceived();
}
///////////////////////////////////////////////////////////////////////////////











