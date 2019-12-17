#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QNetworkInterface>

#include <QDebug>

#include "tcpworker.h"


class NetworkWorkerParameters {
public:


    QHostAddress IpAddr_Tx;
    QHostAddress IpAddr_Rx;

    quint16 port_Tx;
    quint16 port_Rx;
    int protocolType;

};

enum protocolType {
    UDP, TCP
};

class NetworkWorker : public QObject
{
    Q_OBJECT
    QUdpSocket* udpSocket;
    QTcpSocket* tcpSocket;

    bool tcpConnected;

public:
    explicit NetworkWorker(QObject *parent = nullptr);


    NetworkWorkerParameters param;

    QList <QString> getAll_iPaddr_rx();
    QList <QString> getAll_iPaddr_tx();

//    void send(QString IPaddress, quint16 port, QByteArray data);
    bool write(QByteArray data);

    bool connectDevice();
    void disconnect();
    bool isConnected();

    QByteArray readAllRx();

    QList <QByteArray> RxData;

    bool tcpIsConnected();



    TcpServer *s;
    TcpClient *c;

signals:

    void packetArrived(QString, quint32,  QString);
    void dataReceived();


public slots:

    void read();

    void connected();
    void disconnected();
    void on_dataReceived(QByteArray);


};

#endif // NETWORKWORKER_H
