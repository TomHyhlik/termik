#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>

#include <QtCore>
#include <QtNetwork>

class TcpServer : public QObject
{
    Q_OBJECT

    QTcpServer *server;
    QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
    QHash<QTcpSocket*, qint32*> sizes; //We need to store the size to verify if a block has received completely


    QTcpSocket *currentSocket;

private slots:
    void newConnection();
    void disconnected();
    void readyRead();


public:
    explicit TcpServer(QObject *parent = 0);
    bool send(QByteArray);
    bool listen(QHostAddress, quint16);
    bool isListening();
    void close();

signals:
    void received(QByteArray);



};


#endif // TCPSERVER_H
