#include "protocol_tcp_server.h"

#include "networkwparam.h"
#include "uilog.h"

//////////////////////////////////////////////////
protocol_tcp_server::protocol_tcp_server()
{
}

//////////////////////////////////////////////////
bool protocol_tcp_server::isOpen()
{
    return server->isListening();
}

//////////////////////////////////////////////////
bool protocol_tcp_server::open()
{
    currentSocket = nullptr;

    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
//    qDebug() << "Listening:" << server->listen(QHostAddress::Any, 1024);
    return server->listen(NetworkWParam::get().IpAddr_Rx,
                                               NetworkWParam::get().port_Tx);

}

//////////////////////////////////////////////////
bool protocol_tcp_server::write(QByteArray data)
{
    if (currentSocket != nullptr && currentSocket->isOpen())
    {
        return currentSocket->write(data);
    }

    LOG("The TCP client is not connected");
    return false;
}

//////////////////////////////////////////////////
void protocol_tcp_server::close()
{
    server->close();
}

//////////////////////////////////////////////////
void protocol_tcp_server::newConnection()
{
    while (server->hasPendingConnections())
    {
        LOG_T(note, "New TCP Client was connected");

        QTcpSocket *socket = server->nextPendingConnection();
        currentSocket = socket;

        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
        QByteArray *buffer = new QByteArray();
        qint32 *s = new qint32(0);
        buffers.insert(socket, buffer);
        sizes.insert(socket, s);
    }
}

//////////////////////////////////////////////////
void protocol_tcp_server::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    while (socket->bytesAvailable() > 0)
    {
        QByteArray data = socket->readAll();
        emit received(data);
//        qDebug() << "server Rx: " << data.toHex(' ').toUpper();

    }
}

//////////////////////////////////////////////////
void protocol_tcp_server::disconnected()
{
    LOG_T(note, "TCP Client disconnected from server");
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    socket->deleteLater();

    currentSocket = nullptr;
}


//////////////////////////////////////////////////
