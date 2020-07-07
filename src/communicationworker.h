#ifndef COMMUNICATIONWORKER_H
#define COMMUNICATIONWORKER_H

#include <QObject>

class CommunicationWorker : public QObject
{
    Q_OBJECT
public:

    virtual bool open() = 0;
    virtual void close() = 0;
    virtual bool isOpen() = 0;


public slots:
    virtual bool write(QByteArray) = 0;


signals:
    void received(QByteArray);



};

#endif // COMMUNICATIONWORKER_H
