
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
//////////////////////////////////////////////////
void NetworkWorker::scanNetwork_printResults(QHostInfo host)
{
    //    qDebug() << "FOUND HOST: " << host.hostName();

    if (host.error() == QHostInfo::NoError) {

        QList <QHostAddress> addrs = host.addresses();

        if (!addrs.isEmpty()) {
            //            QHostAddress addr = host.addresses().first();
            QHostAddress a(host.hostName());
            if (a.isNull()) {
                //                qDebug() << "Addr: " << addrs.first().toString() << "Name: " << host.hostName();
                scanNetwork_addHost(host);
            }
        }
    } else {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }


    //    const auto addresses = host.addresses();
    //    for (const QHostAddress &address : addresses) {
    //        qDebug() << "Found address:" << address.toString();
    //    }
}
//////////////////////////////////////////////////
void NetworkWorker::scanNetwork_addHost(QHostInfo host)
{
    bool isHere = false;
    for (int i = 0; i < param.allHosts.size(); i++) {
        if (param.allHosts.at(i).hostName() == host.hostName()) {
            isHere = true;
            break;
        }
    }
    if (!isHere) {
        param.allHosts.append(host);
    }
}

//////////////////////////////////////////////////
void NetworkWorker::scanNetwork()
{
    //    param.allHosts.clear();
    QList <QHostInfo> addresses = getAll_iPaddr_rx();

    for (int j = 0; j < addresses.size(); j++) {
        QList <QHostAddress> as = addresses.at(j).addresses();
        if (!as.isEmpty()) {
            QHostAddress a = as.first();
//            if (!a.isLoopback()) {
                for (quint32 i = 0; i < 255; i++) {
                    quint32 val = a.toIPv4Address();
                    val = val & 0xFFFFFF00;
                    QHostAddress searched(val | i);

                    QHostInfo::lookupHost(searched.toString(), // todo select ip addr
                                          this, SLOT(scanNetwork_printResults(QHostInfo)));

                    //                    QHostInfo::lookupHost(QString("10.0.0.%1").arg(i, 0, 10), // todo select ip addr
                    //                                          this, SLOT(scanNetwork_printResults(QHostInfo)));
                }
//            }
        }
    }
}

//////////////////////////////////////////////////
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
QList <QHostInfo> NetworkWorker::getAll_iPaddr_rx()
{
    QList <QHostInfo> myIPaddresses;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            myIPaddresses.append(QHostInfo::fromName(address.toString()));
        }
    }
    return myIPaddresses;
}
//////////////////////////////////////////////////
QList <QHostInfo> NetworkWorker::getAll_iPaddr_tx()
{
    return param.allHosts;
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
