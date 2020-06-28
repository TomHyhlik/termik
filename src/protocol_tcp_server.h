#ifndef PROTOCOL_TCP_SERVER_H
#define PROTOCOL_TCP_SERVER_H


#include <QtNetwork>


#include "networkprotocol.h"

class protocol_tcp_server : public NetworkProtocol
{
    Q_OBJECT



    QTcpServer *server;
    QHash <QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
    QHash <QTcpSocket*, qint32*> sizes; //We need to store the size to verify if a block has received completely


    QTcpSocket *currentSocket;


public:
    protocol_tcp_server();

    bool open() override;
    bool write(QByteArray) override;
    void close() override;

    bool isOpen() override;



private slots:
    void newConnection();
    void disconnected();
    void readyRead();


};

#endif // PROTOCOL_TCP_SERVER_H
