
#include "networkworker.h"

NetworkWorker::NetworkWorker(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(read()));

    tcpConnected = false;
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(connected()),this, SLOT(connected()));
    connect(tcpSocket, SIGNAL(disconnected()),this, SLOT(disconnected()));
//    connect(tcpSocket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(tcpSocket, SIGNAL(readyRead()),this, SLOT(read()));

}

//////////////////////////////////////////////////
bool NetworkWorker::open()
{
    close();
    bool opened = false;
    switch (param.protocolType) {
    case UDP:
        opened = udpSocket->bind(param.IpAddr_Rx, param.port_Rx);
        break;
    case TCP:
       tcpSocket->connectToHost(param.IpAddr_Rx, param.port_Rx);
        break;
    }
    return opened;
}
//////////////////////////////////////////////////
void  NetworkWorker::close()
{
    switch (param.protocolType) {
    case UDP:
        if (udpSocket->isOpen())
            udpSocket->close();
        break;
    case TCP:
        if (tcpSocket->isOpen())
            udpSocket->close();
        break;
    }
}
//////////////////////////////////////////////////
void NetworkWorker::send(QByteArray data)
{
    switch (param.protocolType) {
    case UDP:
        udpSocket->writeDatagram(data, param.IpAddr_Tx, param.port_Tx);
        break;
    case TCP:
//        tcpSocket->writeDatagram(data, param.IpAddr_Tx, param.port_Tx);
        break;
    }
}

//////////////////////////////////////////////////
void NetworkWorker::send(QString IPaddress, quint16 port, QByteArray data)
{
    switch (param.protocolType) {
    case UDP:
        udpSocket->writeDatagram(data, QHostAddress(IPaddress), port);
        break;
    case TCP:
        tcpSocket->write(data);
        break;
    }
}

//////////////////////////////////////////////////
void NetworkWorker::read()
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;

    switch (param.protocolType) {
    case UDP:
        buffer.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
        break;
    case TCP:
        buffer = tcpSocket->readAll();
        break;
    }

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
QByteArray NetworkWorker::readAllRx()
{
    QByteArray out;
    while (!RxData.isEmpty()) {
        out.append(RxData.first());
        RxData.pop_front();
    }
    return out;
}
//////////////////////////////////////////////////
void NetworkWorker::connected()
{
    tcpConnected = true;
}
void NetworkWorker::disconnected()
{
    tcpConnected = false;
}
bool NetworkWorker::tcpIsConnected()
{
    return tcpConnected;
}
//////////////////////////////////////////////////
