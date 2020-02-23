#ifndef SERIALWORKER_H
#define SERIALWORKER_H

#include <QObject>
#include <QSerialPort>
#include <QList>
#include <QSerialPortInfo>
#include <QDebug>
#include "communicationworker.h"


#define DBG_EXCHANGEDDATA   0


/////////////////////////////////////////////////////////////////////////
class SerialWorker : public CommunicationWorker
{
    Q_OBJECT
public:
    explicit SerialWorker();

    bool open() override;
    bool close() override;
    bool isOpen() override;

    //    SerialWorkerParameters param;

private:

    QSerialPort* serial;

public slots:
    void on_dataReceived() override;
    bool write(QByteArray) override;

signals:


};




#endif // SERIALWORKER_H
