#include "protocol_tcp_server.h"

#include "networkwparam.h"

//////////////////////////////////////////////////
protocol_tcp_server::protocol_tcp_server()
{
    tcpServer = std::unique_ptr <TcpServer> (new TcpServer());

    connect(tcpServer.get(), &TcpServer::received,
            this, &protocol_tcp_server::received);
}

//////////////////////////////////////////////////
bool protocol_tcp_server::isOpen()
{
   return tcpServer->isListening();
}

//////////////////////////////////////////////////
bool protocol_tcp_server::open()
{
    return tcpServer->listen(NetworkWParam::get().IpAddr_Rx,
                                      NetworkWParam::get().port_Tx);
}

//////////////////////////////////////////////////
bool protocol_tcp_server::write(QByteArray data)
{
    return tcpServer->send(data);
}

//////////////////////////////////////////////////
void protocol_tcp_server::close()
{
    tcpServer->close();
    tcpServer = nullptr;
}

//////////////////////////////////////////////////
