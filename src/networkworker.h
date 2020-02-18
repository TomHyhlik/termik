#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QThread>

#include <QDebug>

#include "tcpworker.h"

#include "communicationworker.h"


class NetworkWorkerParameters {
public:


    QHostAddress IpAddr_Tx;
    QHostAddress IpAddr_Rx;

    quint16 port_Tx;
    quint16 port_Rx;
    int protocolType;

    QList <QHostInfo> allHosts;

};

enum protocolType {
    UDP, TCP
};

/////////////////////////////////////////////////////////////////////////
class NetworkWorker : public CommunicationWorker
{
    Q_OBJECT
    QUdpSocket* udpSocket;

    TcpServer *tcpServer;
    TcpClient *tcpClient;

    bool tcpConnected;

    void scanNetwork_addHost(QHostInfo host);

public:
    explicit NetworkWorker();


    NetworkWorkerParameters param;

    QList <QHostInfo> getAll_iPaddr_rx();
    QList <QHostInfo> getAll_iPaddr_tx();

//    void send(QString IPaddress, quint16 port, QByteArray data);

    bool open() override;
    bool close() override;
    bool isOpen() override;
    QByteArray readAllRx() override;

    bool tcpIsConnected();
    void scanNetwork();

signals:

    void packetArrived(QString, quint32,  QString);



public slots:

    void on_dataReceived() override;

    void connected();
    void disconnected();
    void on_dataReceived(QByteArray);

    void scanNetwork_printResults(QHostInfo);
    bool write(QByteArray data) override;


};
////////////////////////////////////////////////////////////




//class NetworkScan : public QThread    // todo
//{
//    Q_OBJECT

//    void run() override
//    {





//    }


//signals:



//};





















#endif // NETWORKWORKER_H
