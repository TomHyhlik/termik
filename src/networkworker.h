#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkInterface>

class NetworkWorker : public QObject
{
    Q_OBJECT
    QUdpSocket *socket;

    class parameters {
    public:
        QHostAddress targetIpAddr;
        quint16 port_Tx;
        quint16 port_Rx;
    }param;

public:
    explicit NetworkWorker(QObject *parent = nullptr);
    QString getMyLocalIpAddress();
    void send(QString IPaddress, quint16 port, QByteArray data);
    void send(QByteArray data);

    void setTargetIpAddress(QString addr);
    void setTargetIpPort_Tx(quint16 port);
    void setTargetIpPort_Rx(quint16 port);

    bool open();
    void close();

    QByteArray readAllRx();

    QByteArray ReadAllRx();

    QList <QByteArray> RxData;


signals:

    void packetArrived(QString, quint32,  QString);
    void dataReceived();


public slots:

    void read();



};

#endif // NETWORKWORKER_H
