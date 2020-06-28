#include "tcpserver.h"
#include "log.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
}


bool TcpServer::listen(QHostAddress addr, quint16 port)
{
    currentSocket = nullptr;

    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
//    qDebug() << "Listening:" << server->listen(QHostAddress::Any, 1024);
    qDebug() << "Listening:" << server->listen(addr, port);
    return isListening();
}

bool TcpServer::isListening()
{
    return server->isListening();
}

void TcpServer::close()
{
    server->close();
    //    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    //    socket->close();
}

void TcpServer::newConnection()
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

void TcpServer::disconnected()
{
    LOG_T(note, "TCP Client disconnected from server");
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    socket->deleteLater();

    currentSocket = nullptr;
}

void TcpServer::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    while (socket->bytesAvailable() > 0)
    {
        QByteArray data = socket->readAll();
        emit received(data);
        qDebug() << "server Rx: " << data.toHex(' ').toUpper();

    }
}

bool TcpServer::send(QByteArray data)
{  
    if (currentSocket != nullptr && currentSocket->isOpen())
    {
        return currentSocket->write(data);
    }

    LOG("The TCP client is not connected");
    return false;
}
