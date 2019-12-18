#ifndef TCPWORKER_H
#define TCPWORKER_H

#include <QObject>

#include <QtCore>
#include <QtNetwork>





class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = 0);

public slots:
    bool connectToHost(QHostAddress host, quint16 port);
    bool writeData(QByteArray data);
    void on_readyRead();

private:
    QTcpSocket *socket;
};



class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    void send(QByteArray);
    bool listen(QHostAddress, quint16);
    bool isListening();
    void close();

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
