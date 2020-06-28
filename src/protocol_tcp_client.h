#ifndef PROTOKOL_TCP_H
#define PROTOKOL_TCP_H

#include "networkprotocol.h"

#include <QTcpSocket>

class protocol_tcp_client : public NetworkProtocol
{
    Q_OBJECT

    std::unique_ptr <QTcpSocket> socket;

public:
    protocol_tcp_client();

    bool open() override;
    bool write(QByteArray) override;
    void close() override;
    bool isOpen() override;


 public slots:
    void on_readyRead();


signals:

};

#endif // PROTOKOL_TCP_H
