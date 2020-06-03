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
    if (isEstablished()) {
        emit displayData(data_Tx, txData);
        return communicWorker->write(txData);
    } else {
        return false;
    }
}

//////////////////////////////////////////////////////////////////////
bool Communication::isEstablished()
{
    return (communicWorker != nullptr);
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

    LOG("Attempt to establish communication");

    switch (type)
    {
    case comType_serial:
        communicWorker = std::unique_ptr <SerialWorker> (new SerialWorker());
        EstablishedSuccessful = communicWorker->open();
        break;
    case comType_network:
        communicWorker = std::unique_ptr <NetworkWorker> (new NetworkWorker());
        EstablishedSuccessful = communicWorker->open();
        break;
    case comType_none:
        return;
    }

    connect(communicWorker.get(), &SerialWorker::received,
            this, &Communication::dataArrived);

    if (EstablishedSuccessful)
    {
        lastComType = type;
        switch (type)
        {
        case comType_serial:
            LOG_T(note, QString("Opened Serial posrt: %1")
                  .arg(SerialWParam::get().portName));
            break;
        case comType_network:
            switch (NetworkWParam::get().protocolType)
            {
            case networkProtocolType_udp:
                LOG(QString("Rx: %1 : %2")
                        .arg(NetworkWParam::get().IpAddr_Rx.toString())
                        .arg(QString::number(int(NetworkWParam::get().port_Rx))));
                LOG(QString("Tx: %1 : %2")
                        .arg(NetworkWParam::get().IpAddr_Tx.toString())
                        .arg(QString::number(int(NetworkWParam::get().port_Tx))));
                LOG_T(note, "Opened UDP port");
                break;
            case networkProtocolType_tcp_client:
                LOG_T(note, QString("Connected to TCP server: %1 : %2")
                        .arg(NetworkWParam::get().IpAddr_Tx.toString())
                        .arg(QString::number(int(NetworkWParam::get().port_Tx))));
                break;
            case networkProtocolType_tcp_server:
                LOG_T(note, QString("TCP Server listening at: %1 : %2")
                        .arg(NetworkWParam::get().IpAddr_Rx.toString())
                        .arg(QString::number(int(NetworkWParam::get().port_Rx))));
                break;
            }
            break;
        case comType_none:
            return;
        }
    } else {
        LOG_T(error, "Failed to establish communication");
    }

    EstablishedSuccessful ? emit established_success() : emit established_failed();
}

//////////////////////////////////////////////////////////////////////
void Communication::suspend()
{
    if (communicWorker != nullptr) {
        communicWorker = nullptr;
        LOG_T(note, "Communication suspended");
    }
}

//////////////////////////////////////////////////////////////////////
void Communication::establishToggle()
{
    if (isEstablished()) {
        suspend();
    } else {
        if (lastComType != comType_none) {
            establish();
        }
    }
}

//////////////////////////////////////////////////////////////////////
