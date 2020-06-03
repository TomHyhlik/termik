#include "tcpclient.h"


TcpClient::TcpClient()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), SLOT(on_readyRead()));

}

void TcpClient::on_readyRead()
{
    QByteArray data = socket->readAll();
//    qDebug() << "Client Rx: " << data.toHex(' ').toUpper();
    emit received(data);
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
//        qDebug() << "Client Tx: " << data.toHex(' ').toUpper();
        socket->write(data);
        return socket->waitForBytesWritten();
    }
    else
        return false;
}
