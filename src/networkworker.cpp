#include "networkworker.h"

NetworkWorker::NetworkWorker(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);

    connect(socket, SIGNAL(readyRead()),this, SLOT(read()));

}
//////////////////////////////////////////////////
bool NetworkWorker::open()
{
    socket->close();

    return socket->bind(QHostAddress(getMyLocalIpAddress()), param.port_Rx);
}
//////////////////////////////////////////////////
void  NetworkWorker::close()
{
    socket->close();
}
//////////////////////////////////////////////////
void NetworkWorker::send(QByteArray data)
{
    socket->writeDatagram(data, param.targetIpAddr, param.port_Tx);
    // socket->writeDatagram(data, QHostAddress::LocalHost, 11999);
}

//////////////////////////////////////////////////
void NetworkWorker::send(QString IPaddress, quint16 port, QByteArray data)
{
    socket->writeDatagram(data, QHostAddress(IPaddress), port);
    // socket->writeDatagram(data, QHostAddress::LocalHost, 11999);
}

//////////////////////////////////////////////////
void NetworkWorker::read()
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;

    buffer.resize(int(socket->pendingDatagramSize()));
    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    Rx_buffer.append(buffer);
    QString message = QString(buffer);
//    qDebug() << "_____________________________________";
//    qDebug() << "sender: " << sender;
//    qDebug() << "sender port: " << senderPort;
//    qDebug() << "message: " << message;

    emit packetArrived(sender.toString(), senderPort, message);
    emit dataReceived();
}

//////////////////////////////////////////////////
QString NetworkWorker::getMyLocalIpAddress()
{
    QString myIPaddress;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
                            address != QHostAddress(QHostAddress::LocalHost))
            myIPaddress = address.toString();
    }
    return myIPaddress;
}
//////////////////////////////////////////////////
void NetworkWorker::setTargetIpAddress(QString addr)
{
    param.targetIpAddr = QHostAddress(addr);
}

//////////////////////////////////////////////////
void NetworkWorker::setTargetIpPort_Tx(quint16 port)
{
    param.port_Tx = port;
}
//////////////////////////////////////////////////
void NetworkWorker::setTargetIpPort_Rx(quint16 port)
{
    param.port_Rx = port;
}
//////////////////////////////////////////////////
QByteArray NetworkWorker::readAllRx()
{
    QByteArray data = Rx_buffer.data();
    Rx_buffer.clear();
    return data;
}
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
