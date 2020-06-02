#ifndef PROTOKOL_TCP_H
#define PROTOKOL_TCP_H

#include "networkprotocol.h"

#include "tcpclient.h"

class protocol_tcp : public NetworkProtocol
{
    Q_OBJECT

    std::unique_ptr <TcpClient> tcpClient;

public:
    protocol_tcp();

    bool open() override;
    bool write(QByteArray) override;
    void close() override;


signals:

};

#endif // PROTOKOL_TCP_H
