#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>

#include "serialworker.h"
#include "networkworker.h"
#include "communicationworker.h"

enum communicationType {
    comType_serial, comType_network, comType_none
};

class Communication : public QObject
{
    Q_OBJECT

    communicationType lastComType;
    std::unique_ptr <CommunicationWorker> communicWorker;

public:
    explicit Communication(QObject *parent = nullptr);

    void establishToggle();
    bool isEstablished();
    void suspend();
    communicationType getLastComType() { return lastComType; }

public slots:
    void establish();
    void establish(communicationType);
    void establishPrintResults(bool success, communicationType type);
    bool dataTransmit(QByteArray);

private slots:
    void dataArrived(QByteArray);

signals:
    void connected();
    void disconnected();
    void displayData(int, QByteArray);

    void established_success();
    void established_failed();

};

#endif // COMMUNICATION_H
