#ifndef PROTOCOL_TCP_SERVER_H
#define PROTOCOL_TCP_SERVER_H

#include "networkprotocol.h"

#include "tcpserver.h"

class protocol_tcp_server : public NetworkProtocol
{
    Q_OBJECT

    std::unique_ptr <TcpServer> tcpServer;

public:
    protocol_tcp_server();

    bool open() override;
    bool write(QByteArray) override;
    void close() override;

    bool isOpen() override;

};

#endif // PROTOCOL_TCP_SERVER_H
