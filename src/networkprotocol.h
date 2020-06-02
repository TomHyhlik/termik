#ifndef NETWORKPROTOCOL_H
#define NETWORKPROTOCOL_H

#include <QObject>

class NetworkProtocol : public QObject
{
    Q_OBJECT
public:
    NetworkProtocol();


    virtual bool write(QByteArray) = 0;
    virtual void close() = 0;
    virtual bool open() = 0;

signals:
    void received(QByteArray);

};

#endif // NETWORKPROTOCOL_H
