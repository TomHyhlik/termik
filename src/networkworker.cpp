
#include "networkworker.h"
#include "tcpworker.h"


NetworkWorker::NetworkWorker(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(read()));



    s = new Server();
    connect(s, SIGNAL(dataReceived(QByteArray)), this, SLOT(on_dataReceived(QByteArray)));


    c = new Client();


}

void NetworkWorker::on_dataReceived(QByteArray data)
{
    RxData.append(data);
    emit dataReceived();
}
//////////////////////////////////////////////////

bool NetworkWorker::isConnected()
{
    return false;
}

//////////////////////////////////////////////////
bool NetworkWorker::connectDevice()
{

    bool opened = false;
    switch (param.protocolType) {
    case UDP:
        opened = udpSocket->bind(param.IpAddr_Rx, param.port_Rx);
        break;
    case TCP:
        opened = c->connectToHost(QHostAddress::LocalHost);
        break;
    }
    return opened;
}
//////////////////////////////////////////////////
void  NetworkWorker::disconnect()
{
    switch (param.protocolType) {
    case UDP:
        if (udpSocket->isOpen())
            udpSocket->close();
        break;
    case TCP:

        qDebug() << "TODO:435793";


        break;
    }
}
//////////////////////////////////////////////////
bool NetworkWorker::write(QByteArray data)
{
    switch (param.protocolType) {
    case UDP:
        udpSocket->writeDatagram(data, param.IpAddr_Tx, param.port_Tx);
        break;
    case TCP:

        c->writeData(data);


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

        qDebug() << "ERRROR: 3242, not implemented";

        break;
    }

    RxData.append(buffer);
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
