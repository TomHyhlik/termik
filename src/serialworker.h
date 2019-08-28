#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QSerialPort>
#include <QList>

#define SUFFIX_DEFAULT      "\r\n"

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

    bool suffix_enabled;
    bool prefix_enabled;
    QByteArray suffix;
    QByteArray prefix;

    QByteArray splitFactor;
    bool splitFactor_enabled;

    parameters param;

    QByteArray Rx_buffer;

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
