#ifndef TCPWORKER_H
#define TCPWORKER_H

#include <QObject>

#include <QtCore>
#include <QtNetwork>





class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

public slots:
    bool connectToHost(QHostAddress host);
    bool writeData(QByteArray data);
    void on_readyRead();

private:
    QTcpSocket *socket;
};



class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void send(QByteArray);

signals:
    void dataReceived(QByteArray);

private slots:
    void newConnection();
    void disconnected();
    void on_readyRead();

private:
    QTcpServer *server;
    QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
    QHash<QTcpSocket*, qint32*> sizes; //We need to store the size to verify if a block has received completely
};





#endif // TCPWORKER_H
