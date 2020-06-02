#include "networkworker.h"

#include "protocol_udp.h"
#include "protocol_tcp.h"


NetworkWorker::NetworkWorker()
{
    communicProtocol = nullptr;
}

//////////////////////////////////////////////////
void NetworkWorker::close()
{
    if (communicProtocol != nullptr) {
        communicProtocol->close();
        communicProtocol = nullptr;
    }
}

//////////////////////////////////////////////////
bool NetworkWorker::isOpen()
{
    return communicProtocol != nullptr;
}

//////////////////////////////////////////////////
bool NetworkWorker::open()
{
    close();

    switch (NetworkWParam::get().protocolType)
    {
    case networkProtocolType_tcp:
        communicProtocol = std::unique_ptr <NetworkProtocol> (new protocol_tcp());
        break;
    case networkProtocolType_udp:
        communicProtocol = std::unique_ptr <NetworkProtocol> (new protocol_udp());
        break;
    }

    if (communicProtocol->open()) {
        connect(communicProtocol.get(), &NetworkProtocol::received,
                this, &NetworkWorker::received);
    } else {
        close();
    }

    return isOpen();
}

//////////////////////////////////////////////////
bool NetworkWorker::write(QByteArray data)
{
    if (isOpen())
        return communicProtocol->write(data);
    else return false;
}

