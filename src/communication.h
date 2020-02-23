#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>

#include "serialworker.h"
#include "networkworker.h"
#include "communicationworker.h"

enum communicationType {
    comType_none, comType_serial, comType_network
};


class Communication : public QObject
{
    Q_OBJECT

     std::unique_ptr <CommunicationWorker> communicWorker;


public:
    explicit Communication(QObject *parent = nullptr);


    void establishToggle();
    bool isEstablished();
    void suspend();

    communicationType getLastConnType() { return lastComType; }
    communicationType lastComType;


public slots:

    void establish();
    void establish(communicationType);
    bool dataTransmit(QByteArray);


private slots:
    void dataArrived(QByteArray);


signals:
    void connected();
    void disconnected();

    void displayData(int, QByteArray);

    void connectionEstablished(bool, QString);

};

#endif // COMMUNICATION_H
