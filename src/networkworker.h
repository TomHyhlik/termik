#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QNetworkInterface>

#include <QDebug>

#include "communicationworker.h"
#include "networkwparam.h"
#include "networkprotocol.h"


enum protocolType {
    networkProtocolType_udp, networkProtocolType_tcp_client, networkProtocolType_tcp_server
};

/////////////////////////////////////////////////////////////////////////
class NetworkWorker : public CommunicationWorker
{
    Q_OBJECT

    bool tcpConnected;

    std::unique_ptr <NetworkProtocol> communicProtocol;

public:
    explicit NetworkWorker();

    bool open() override;
    void close() override;
    bool isOpen() override;

    bool tcpIsConnected();

signals:
    void packetArrived(QString, quint32,  QString);


public slots:

    bool write(QByteArray data) override;



};
////////////////////////////////////////////////////////////


#endif // NETWORKWORKER_H
