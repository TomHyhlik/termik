#include "communication.h"


#include "serialworker.h"
#include "networkworker.h"

#include "mainwindow.h"
#include "serialwparam.h"

//////////////////////////////////////////////////////////////////////
Communication::Communication(QObject *parent) : QObject(parent)
{
    communicWorker = nullptr;
}
/////////////////////////////////////////////////////////////////
void Communication::dataArrived(QByteArray rxData)
{
    emit displayData(data_Rx, rxData);
}

//////////////////////////////////////////////////////////////////////
bool Communication::dataTransmit(QByteArray txData)
{
    emit displayData(data_Tx, txData);
    return communicWorker->write(txData);
}

//////////////////////////////////////////////////////////////////////
bool Communication::isEstablished()
{
    return communicWorker != nullptr;
}

//////////////////////////////////////////////////////////////////////
void Communication::establish()
{
    establish(lastComType);
}
//////////////////////////////////////////////////////////////////////
void Communication::establish(communicationType type)
{
    bool EstablishedSuccessful = false;
    QString deviceName;

    switch (type)
    {
    case comType_serial:
        communicWorker = std::unique_ptr <SerialWorker> (new SerialWorker());
        EstablishedSuccessful = communicWorker->open();
        deviceName = SerialWParam::get().portName;
        break;
    case comType_network:
        communicWorker = std::unique_ptr <NetworkWorker> (new NetworkWorker());
        EstablishedSuccessful = communicWorker->open();
        deviceName = QString("%1 : %2")
                .arg(NetworkWParam::get().IpAddr_Tx.toString())
                .arg(QString::number(int(NetworkWParam::get().port_Tx)));
        break;
    case comType_none:
        suspend();
        return;
    }

    connect(communicWorker.get(), SIGNAL(dataReceived(QByteArray)), this,
            SLOT(dataArrived(QByteArray)));

    if (EstablishedSuccessful) {    lastComType = type; }

    emit connectionEstablished(EstablishedSuccessful, deviceName);
}

//////////////////////////////////////////////////////////////////////
void Communication::suspend()
{
    if (communicWorker != nullptr)  communicWorker = nullptr;
}
//////////////////////////////////////////////////////////////////////
void Communication::establishToggle()
{

    /* todo */



}

//////////////////////////////////////////////////////////////////////
