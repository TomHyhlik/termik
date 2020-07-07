#include "communicworkerfactory.h"

CommunicWorkerFactory::CommunicWorkerFactory()
{

}


//////////////////////////////////////////////////////////////////////
CommunicationWorker* CommunicWorkerFactory::create(communicationType type)
{
    CommunicationWorker* out;

    switch (type)
    {
    case comType_serial:
        out = new SerialWorker();
        break;
    case comType_network:
        out = new NetworkWorker();
        break;
    case comType_none:
        out = nullptr;
    }
    return out;
}
