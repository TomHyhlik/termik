#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>

#include "serialworker.h"
#include "networkworker.h"


enum communicationType {
    comType_none, comType_serial, comType_network
};


class Communication : public QObject
{
    Q_OBJECT





public:
    explicit Communication(QObject *parent = nullptr);


    NetworkWorker* network;
    SerialWorker* serial;


    void establishToggle();

    bool isEstablished();

    communicationType connType;



    NetworkWorkerParameters getParameters_network() {
        return  network->param;
    }
    SerialWorkerParameters getParameters_serial() {
        return serial->param;
    }
    void setParameters_network(NetworkWorkerParameters val) {
        network->param = val;
    }
    void setParameters_serial(SerialWorkerParameters val) {
        serial->param = val;
    }

public slots:

    void establish();
    void establish(communicationType);

private slots:
    void dataArrived();



signals:
    void connected();
    void disconnected();

    void displayData(int, QByteArray);

};

#endif // COMMUNICATION_H
