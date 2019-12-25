
#include "networkworker.h"
#include "tcpworker.h"


NetworkWorker::NetworkWorker(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(udpRead()));

    tcpServer = new TcpServer();
    connect(tcpServer, SIGNAL(dataReceived(QByteArray)),
            this, SLOT(on_dataReceived(QByteArray)));
    tcpClient = new TcpClient();
}

void NetworkWorker::on_dataReceived(QByteArray data)
{
    RxData.append(data);
    emit dataReceived();
}
//////////////////////////////////////////////////

bool NetworkWorker::isConnected()
{
    return tcpServer->isListening();
}

//////////////////////////////////////////////////
bool NetworkWorker::connectDevice()
{
    if (isConnected()) {
        disconnect();
    }
    bool opened = false;
    switch (param.protocolType) {
    case UDP:
        opened = udpSocket->bind(param.IpAddr_Rx, param.port_Rx);
        break;
    case TCP:
        opened = tcpServer->listen(param.IpAddr_Rx, param.port_Rx);
        if (opened) {
            opened = tcpClient->connectToHost(param.IpAddr_Tx, param.port_Tx);
        }
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
        tcpServer->close();
        break;
    }
}
//////////////////////////////////////////////////
bool NetworkWorker::write(QByteArray data)
{
    bool success = false;
    switch (param.protocolType) {
    case UDP:
        success = udpSocket->writeDatagram(data, param.IpAddr_Tx, param.port_Tx);
        break;
    case TCP:
        success = tcpClient->writeData(data);
        break;
    }
    return success;
}

//////////////////////////////////////////////////
void NetworkWorker::udpRead()
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;


    buffer.resize(int(udpSocket->pendingDatagramSize()));
    udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    RxData.append(buffer);
    //    qDebug() << "_____________________________________";
    //    qDebug() << "sender: " << sender;
    //    qDebug() << "sender port: " << senderPort;
    //    qDebug() << "message: " << message;
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
