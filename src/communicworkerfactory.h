#ifndef COMMUNICWORKERFACTORY_H
#define COMMUNICWORKERFACTORY_H

#include "serialworker.h"
#include "networkworker.h"
#include "communication.h"

class CommunicWorkerFactory
{
public:
    CommunicationWorker* create(communicationType type)
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
};

#endif // COMMUNICWORKERFACTORY_H
