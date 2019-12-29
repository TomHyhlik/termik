#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QThread>

#include <QDebug>

#include "tcpworker.h"


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

class NetworkWorker : public QObject
{
    Q_OBJECT
    QUdpSocket* udpSocket;

    TcpServer *tcpServer;
    TcpClient *tcpClient;

    bool tcpConnected;

    void scanNetwork_addHost(QHostInfo host);

public:
    explicit NetworkWorker(QObject *parent = nullptr);


    NetworkWorkerParameters param;

    QList <QHostInfo> getAll_iPaddr_rx();
    QList <QHostInfo> getAll_iPaddr_tx();

//    void send(QString IPaddress, quint16 port, QByteArray data);
    bool write(QByteArray data);

    bool connectDevice();
    void disconnect();
    bool isConnected();

    QByteArray readAllRx();

    QList <QByteArray> RxData;

    bool tcpIsConnected();
    void scanNetwork();

signals:

    void packetArrived(QString, quint32,  QString);
    void dataReceived();


public slots:

    void udpRead();

    void connected();
    void disconnected();
    void on_dataReceived(QByteArray);

    void scanNetwork_printResults(QHostInfo);


};
////////////////////////////////////////////////////////////




class NetworkScan : public QThread
{
    Q_OBJECT

    void run() override
    {





    }


signals:



};





















#endif // NETWORKWORKER_H
