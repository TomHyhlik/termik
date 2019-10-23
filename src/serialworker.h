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

    parameters param;

    QList <QByteArray> RxData;

    QByteArray ReadAllRx();

private:

    QSerialPort* serial;
    QByteArray buffer;
    void setDefaultParameters();

public slots:
    void readData();
    bool write(QByteArray);

signals:
    void dataReceived();

};




#endif // SERIALWORKER_H
