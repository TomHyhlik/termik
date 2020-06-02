#ifndef PROTOCOL_UDP_H
#define PROTOCOL_UDP_H

#include "networkprotocol.h"

#include <QUdpSocket>


class protocol_udp : public NetworkProtocol
{
    Q_OBJECT

    std::unique_ptr <QUdpSocket> udpSocket;


public:

    protocol_udp();

    bool write(QByteArray) override;
    bool open() override;
    void close() override;

private slots:

    void on_dataReceived();


signals:

};

#endif // PROTOCOL_UDP_H
