#include "communication.h"


#include "serialworker.h"
#include "networkworker.h"


//////////////////////////////////////////////////////////////////////
Communication::Communication(QObject *parent) : QObject(parent)
{

    serial = new SerialWorker(this);
    connect(serial, SIGNAL(dataReceived()), this, SLOT(dataArrived()));

    network = new NetworkWorker(this);
    connect(network, SIGNAL(dataReceived()), this, SLOT(dataArrived()));


}

//////////////////////////////////////////////////////////////////////
void Communication::establishToggle()
{
    switch (config.connectionType)
    {
    case serial:
        sw->close();
        config.connectionType = none;
        break;
    case network:
        nw->disconnect();
        config.connectionType = none;
        break;
    case none:
        showConnectionSettings();
        break;
    default:
        config.connectionType = none;
    }
}

//////////////////////////////////////////////////////////////////////
