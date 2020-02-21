#include "communication.h"


#include "serialworker.h"
#include "networkworker.h"

#include "mainwindow.h"
#include "serialwparam.h"

//////////////////////////////////////////////////////////////////////
Communication::Communication(QObject *parent) : QObject(parent)
{
    connType = comType_none;


    serial = new SerialWorker();
    connect(serial, SIGNAL(dataReceived()), this, SLOT(dataArrived()));

    network = new NetworkWorker();
    connect(network, SIGNAL(dataReceived()), this, SLOT(dataArrived()));

}
/////////////////////////////////////////////////////////////////
void Communication::dataArrived()
{
    /* get the data from apropriate class */
    switch (connType)
    {
    case comType_serial:
        displayData(data_Rx, serial->readAllRx());
        break;
    case comType_network:
        displayData(data_Rx, network->readAllRx());
        break;
    case comType_none:
        break;
    }
}
//////////////////////////////////////////////////////////////////////
void Communication::establish()
{
    establish(connType);
}
//////////////////////////////////////////////////////////////////////
void Communication::establish(communicationType type)
{
    bool connectedSuccessfully = false;
    QString deviceName;

    switch (type)
    {
    case comType_serial:
        connectedSuccessfully = serial->open();
        deviceName = SerialWParam::get().portName;
        break;
    case comType_network:
        connectedSuccessfully = network->open();
        deviceName = QString("%1:%2")
                .arg(network->param.IpAddr_Tx.toString())
                .arg(QString::number(int(network->param.port_Tx)));
        break;
    case comType_none:
        break;
    }

    if (connectedSuccessfully) {    connType = type; }

    emit connectionEstablished(connectedSuccessfully, deviceName);
}

//////////////////////////////////////////////////////////////////////
void Communication::establishToggle()
{
//    switch (config.connectionType)
//    {
//    case serial:
//        sw->close();
//        config.connectionType = none;
//        break;
//    case network:
//        nw->disconnect();
//        config.connectionType = none;
//        break;
//    case none:
//        showConnectionSettings();
//        break;
//    default:
//        config.connectionType = none;
//    }
}

//////////////////////////////////////////////////////////////////////
