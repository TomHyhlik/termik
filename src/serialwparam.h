#ifndef SERIALWPARAM_H
#define SERIALWPARAM_H

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>


class SerialWParam
{
    SerialWParam()
    {
        init_default();
    }

    static SerialWParam s_Instance;

    void init_default()
    {
        baudRate = QSerialPort::Baud115200;
        dataBits = QSerialPort::Data8;
        parity = QSerialPort::NoParity;
        stopBits = QSerialPort::OneStop;
        flowControl = QSerialPort::NoFlowControl;
    }

public:
    SerialWParam(const SerialWParam&) = delete;
    static SerialWParam& get() { return s_Instance; }

    /* the data */
    QString portName;
    qint32 baudRate;
    int dataBits;
    int parity;
    int stopBits;
    int flowControl;

};




#endif // SERIALWPARAM_H
