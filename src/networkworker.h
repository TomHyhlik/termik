#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QNetworkInterface>

#include <QDebug>

#include "tcpworker.h"

#include "communicationworker.h"
#include "networkwparam.h"


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


public:
    explicit NetworkWorker();

//    void send(QString IPaddress, quint16 port, QByteArray data);

    bool open() override;
    bool close() override;
    bool isOpen() override;

    bool tcpIsConnected();

signals:
    void packetArrived(QString, quint32,  QString);



public slots:

    void on_dataReceived() override;

    void connected();
    void disconnected();
    void on_dataReceived(QByteArray);
    bool write(QByteArray data) override;


};
////////////////////////////////////////////////////////////


#endif // NETWORKWORKER_H
