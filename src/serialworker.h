#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QSerialPort>
#include <QList>
#include <QSerialPortInfo>

#include "communicationworker.h"


#define DBG_EXCHANGEDDATA   0


class SerialWorkerParameters {
public:
    /* init the default parameters */
    SerialWorkerParameters()
    {
        baudRate = QSerialPort::Baud115200;
        dataBits = QSerialPort::Data8;
        parity = QSerialPort::NoParity;
        stopBits = QSerialPort::OneStop;
        flowControl = QSerialPort::NoFlowControl;
    }


    QString portName;
    qint32 baudRate;
    int dataBits;
    int parity;
    int stopBits;
    int flowControl;
};


/////////////////////////////////////////////////////////////////////////
class SerialWorker : public CommunicationWorker
{
    Q_OBJECT
public:
    explicit SerialWorker();

    bool open() override;
    bool close() override;
    bool isOpen() override;
    QByteArray readAllRx() override;

    SerialWorkerParameters param;

private:

    QSerialPort* serial;

public slots:
    void on_dataReceived() override;
    bool write(QByteArray) override;

signals:


};




#endif // SERIALWORKER_H
