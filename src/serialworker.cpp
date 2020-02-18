#include "serialworker.h"

#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QThread>

#include <QDebug>


///////////////////////////////////////////////////////////////////////////////
SerialWorker::SerialWorker()
{
    serial = new QSerialPort(this);
    connect(serial, &QIODevice::readyRead, this, &SerialWorker::on_dataReceived);

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
    if (serial->isOpen() && serial->isWritable()){
        return true;
    }
    else{
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
bool SerialWorker::write(QByteArray data)
{
#if DBG_EXCHANGEDDATA
    qDebug() << "TX: " << data.toHex();
#endif

    serial->write(data);
//    serial->waitForBytesWritten(50);

    if(serial->flush()){
        return true;
    } else {
        return false;
    }    
}

///////////////////////////////////////////////////////////////////////////////
void SerialWorker::on_dataReceived()
{
    QByteArray data = serial->readAll();

#if DBG_EXCHANGEDDATA
    qDebug() << "RX: " << data.toHex();
#endif

    RxData.append(data);
    emit dataReceived();
}

///////////////////////////////////////////////////////////////////////////////
QByteArray SerialWorker::readAllRx()
{
    QByteArray out;
    while (!RxData.isEmpty()) {
        out.append(RxData.first());
        RxData.pop_front();
    }
    return out;
}

///////////////////////////////////////////////////////////////////////////////







