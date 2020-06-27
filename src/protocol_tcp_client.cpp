#include "protocol_tcp_client.h"
#include "networkwparam.h"

protocol_tcp_client::protocol_tcp_client()
{
    tcpClient = std::unique_ptr <TcpClient> (new TcpClient());

    connect(tcpClient.get(), &TcpClient::received,
            this, &protocol_tcp_client::received);
}

//////////////////////////////////////////////////
bool protocol_tcp_client::isOpen()
{
    return true; // todo
}
//////////////////////////////////////////////////
bool protocol_tcp_client::open()
{
    return tcpClient->connectToHost(NetworkWParam::get().IpAddr_Tx,
                                      NetworkWParam::get().port_Tx);
}

//////////////////////////////////////////////////
bool protocol_tcp_client::write(QByteArray data)
{
    return tcpClient->writeData(data);
}

//////////////////////////////////////////////////
void protocol_tcp_client::close()
{
    tcpClient = nullptr;
}

//////////////////////////////////////////////////
