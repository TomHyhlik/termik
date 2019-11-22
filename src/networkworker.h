#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkInterface>


class NetworkWorkerParameters {
public:
    QHostAddress IpAddr_Tx;
    QHostAddress IpAddr_Rx;

    quint16 port_Tx;
    quint16 port_Rx;
};


class NetworkWorker : public QObject
{
    Q_OBJECT
    QUdpSocket *socket;

public:
    explicit NetworkWorker(QObject *parent = nullptr);


    NetworkWorkerParameters param;

    QList <QString> getAll_iPaddr_rx();
    QList <QString> getAll_iPaddr_tx();

    void send(QString IPaddress, quint16 port, QByteArray data);
    void send(QByteArray data);

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
