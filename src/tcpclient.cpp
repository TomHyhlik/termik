#include "tcpclient.h"

static inline QByteArray IntToArray(qint32 source);


TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), SLOT(on_readyRead()));

}

void TcpClient::on_readyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << "Client received: " << data;
    emit dataReceived(data);
}

bool TcpClient::connectToHost(QHostAddress host, quint16 port)
{
    socket->connectToHost(host, port);
    return socket->waitForConnected();
}

bool TcpClient::writeData(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(IntToArray(data.size())); //write size of data
        socket->write(data); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}


QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}





