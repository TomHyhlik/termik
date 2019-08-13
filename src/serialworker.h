#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QSerialPort>
#include <QList>


class parameters {
public:
    QString portName;
    qint32 baudRate;
    int dataBits;
    int parity;
    int stopBits;
    int flowControl;
};


/////////////////////////////////////////////////////////////////////////
class SerialWorker : public QObject
{
    Q_OBJECT
public:
    explicit SerialWorker(QObject *parent = nullptr);

    bool open();
    bool close();
    bool isOpen();

    bool suffix_enabled = true;
    bool prefix_enabled = false;
    QByteArray suffix = "\r\n";
    QByteArray prefix = "";

    QByteArray splitFactor = "\r\n";
    bool splitFactor_enabled = false;

    parameters param;

    QByteArray Rx_buffer;

    QByteArray readAllRx();

private:

    QSerialPort* serial;
    QByteArray buffer;

public slots:
    void readData();
    bool write(QByteArray);

signals:
    void dataReceived();

};




#endif // SERIALWORKER_H
