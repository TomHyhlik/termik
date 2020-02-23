#include "serialworker.h"
#include "serialwparam.h"

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

    serial->setPortName(SerialWParam::get().portName);
    serial->setBaudRate(QSerialPort::BaudRate(SerialWParam::get().baudRate));
    serial->setDataBits(QSerialPort::DataBits(SerialWParam::get().dataBits));
    serial->setParity(QSerialPort::Parity(SerialWParam::get().parity));
    serial->setStopBits(QSerialPort::StopBits(SerialWParam::get().stopBits));
    serial->setFlowControl(QSerialPort::FlowControl(SerialWParam::get().flowControl));

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

    emit dataReceived(data);
}

///////////////////////////////////////////////////////////////////////////////







