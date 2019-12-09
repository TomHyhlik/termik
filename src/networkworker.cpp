#include "networkworker.h"

NetworkWorker::NetworkWorker(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(read()));
}

//////////////////////////////////////////////////
bool NetworkWorker::open()
{
    close();
    return udpSocket->bind(param.IpAddr_Rx, param.port_Rx);
}
//////////////////////////////////////////////////
void  NetworkWorker::close()
{
    if (udpSocket->isOpen())
        udpSocket->close();
}
//////////////////////////////////////////////////
void NetworkWorker::send(QByteArray data)
{
    udpSocket->writeDatagram(data, param.IpAddr_Tx, param.port_Tx);
    // socket->writeDatagram(data, QHostAddress::LocalHost, 11999);
}

//////////////////////////////////////////////////
void NetworkWorker::send(QString IPaddress, quint16 port, QByteArray data)
{
    udpSocket->writeDatagram(data, QHostAddress(IPaddress), port);
    // socket->writeDatagram(data, QHostAddress::LocalHost, 11999);
}

//////////////////////////////////////////////////
void NetworkWorker::read()
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;

    buffer.resize(int(udpSocket->pendingDatagramSize()));
    udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    RxData.append(buffer);
    QString message = QString(buffer);
//    qDebug() << "_____________________________________";
//    qDebug() << "sender: " << sender;
//    qDebug() << "sender port: " << senderPort;
//    qDebug() << "message: " << message;

//    emit packetArrived(sender.toString(), senderPort, message);
    emit dataReceived();
}

//////////////////////////////////////////////////
QList <QString> NetworkWorker::getAll_iPaddr_rx()
{
    QList <QString> myIPaddresses;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            myIPaddresses.append(address.toString());
        }
    }
    return myIPaddresses;
}

//////////////////////////////////////////////////
QByteArray NetworkWorker::ReadAllRx()
{
    QByteArray out;
    while (!RxData.isEmpty()) {
        out.append(RxData.first());
        RxData.pop_front();
    }
    return out;
}
//////////////////////////////////////////////////
//////////////////////////////////////////////////
