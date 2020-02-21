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



    communicationType connType;     // todo make private

    NetworkWorker* network;
    SerialWorker* serial;


    void establishToggle();
    bool isEstablished();

    communicationType getConnType() { return connType; }


    NetworkWorkerParameters getParameters_network() {
        return  network->param;
    }
//    SerialWorkerParameters getParameters_serial() {       // todo rm
//        return serial->param;
//    }
    void setParameters_network(NetworkWorkerParameters val) {
        network->param = val;
    }
//    void setParameters_serial(SerialWorkerParameters val) {    // todo rm
//        serial->param = val;
//    }

public slots:

    void establish();
    void establish(communicationType);

private slots:
    void dataArrived();



signals:
    void connected();
    void disconnected();

    void displayData(int, QByteArray);

    void connectionEstablished(bool, QString);

};

#endif // COMMUNICATION_H
