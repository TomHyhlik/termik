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


    NetworkWorker* network;
    SerialWorker* serial;



public:
    explicit Communication(QObject *parent = nullptr);

    void establishToggle();

    void isEstablished();



signals:
    void connected();
    void disconnected();

};

#endif // COMMUNICATION_H
