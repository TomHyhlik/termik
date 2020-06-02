#include "protocol_tcp.h"
#include "networkwparam.h"

protocol_tcp::protocol_tcp()
{
    tcpClient = std::make_unique <TcpClient> ();

    connect(tcpClient.get(), &TcpClient::dataReceived,
            this, &protocol_tcp::received);
}

//////////////////////////////////////////////////
bool protocol_tcp::open()
{
    return tcpClient->connectToHost(NetworkWParam::get().IpAddr_Tx,
                                      NetworkWParam::get().port_Tx);
}

//////////////////////////////////////////////////
bool protocol_tcp::write(QByteArray data)
{
    return tcpClient->writeData(data);
}

//////////////////////////////////////////////////
void protocol_tcp::close()
{
    tcpClient = nullptr;
}

//////////////////////////////////////////////////
