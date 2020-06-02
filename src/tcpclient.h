#ifndef TCPCLIENT_H
#define TCPCLIENT_H

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

signals:
    void dataReceived(QByteArray);
};


#endif // TCPCLIENT_H
