
#include "networkworker.h"
#include "tcpworker.h"


NetworkWorker::NetworkWorker()
{
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(on_dataReceived()));

    tcpServer = new TcpServer();
    connect(tcpServer, SIGNAL(dataReceived(QByteArray)),
            this, SLOT(on_dataReceived(QByteArray)));
    tcpClient = new TcpClient();
    connect(tcpClient, &TcpClient::dataReceived, this, &NetworkWorker::dataReceived);


}

//////////////////////////////////////////////////
void NetworkWorker::on_dataReceived(QByteArray data)
{
    emit dataReceived(data);
}
//////////////////////////////////////////////////
bool NetworkWorker::isOpen()
{
    return tcpServer->isListening();
}

//////////////////////////////////////////////////
bool NetworkWorker::open()
{
    if (isOpen()) {
        disconnect();
    }
    bool opened = false;
    switch (NetworkWParam::get().protocolType) {
    case UDP:
        opened = udpSocket->bind(NetworkWParam::get().IpAddr_Rx, NetworkWParam::get().port_Rx);
        break;
    case TCP:
        opened = tcpServer->listen(NetworkWParam::get().IpAddr_Rx, NetworkWParam::get().port_Rx);
        if (opened) {
            opened = tcpClient->connectToHost(NetworkWParam::get().IpAddr_Tx, NetworkWParam::get().port_Tx);
        }
        break;
    }
    return opened;
}

//////////////////////////////////////////////////
bool  NetworkWorker::close()
{
    switch (NetworkWParam::get().protocolType) {
    case UDP:
        udpSocket->close();
        break;
    case TCP:
        tcpServer->close();
        break;
    }
    return true;
}
//////////////////////////////////////////////////
bool NetworkWorker::write(QByteArray data)
{
    bool success = false;
    switch (NetworkWParam::get().protocolType) {
    case UDP:
        success = udpSocket->writeDatagram(data, NetworkWParam::get().IpAddr_Tx, NetworkWParam::get().port_Tx);
        break;
    case TCP:
        success = tcpClient->writeData(data);
        break;
    }
    return success;
}

//////////////////////////////////////////////////
void NetworkWorker::on_dataReceived()
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;

    buffer.resize(int(udpSocket->pendingDatagramSize()));
    udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    qDebug() << "_____________________________________";
    qDebug() << "sender: " << sender;
    qDebug() << "sender port: " << senderPort;
    qDebug() << "message: " << buffer;
    emit dataReceived(buffer);
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
