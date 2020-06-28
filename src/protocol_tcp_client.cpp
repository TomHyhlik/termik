#include "protocol_tcp_client.h"
#include "networkwparam.h"

//////////////////////////////////////////////////
protocol_tcp_client::protocol_tcp_client()
{
    socket = std::unique_ptr <QTcpSocket> (new QTcpSocket());
    connect(socket.get(), SIGNAL(readyRead()), SLOT(on_readyRead()));

}

//////////////////////////////////////////////////
void protocol_tcp_client::on_readyRead()
{
    QByteArray data = socket->readAll();
//    qDebug() << "Client Rx: " << data.toHex(' ').toUpper();
    emit received(data);
}


//////////////////////////////////////////////////
bool protocol_tcp_client::isOpen()
{
    return (socket != nullptr);
}
//////////////////////////////////////////////////
bool protocol_tcp_client::open()
{
    socket->connectToHost(NetworkWParam::get().IpAddr_Tx,
                                      NetworkWParam::get().port_Tx);
    return socket->waitForConnected();
}

//////////////////////////////////////////////////
bool protocol_tcp_client::write(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
//        qDebug() << "Client Tx: " << data.toHex(' ').toUpper();
        socket->write(data);
        return socket->waitForBytesWritten();
    }
    else return false;
}

//////////////////////////////////////////////////
void protocol_tcp_client::close()
{
    socket = nullptr;
}

//////////////////////////////////////////////////
