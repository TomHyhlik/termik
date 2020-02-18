#ifndef COMMUNICATIONWORKER_H
#define COMMUNICATIONWORKER_H

#include <QObject>

class CommunicationWorker : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationWorker(QObject *parent = nullptr);

    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool isOpen() = 0;

    QList <QByteArray> RxData;

    virtual QByteArray readAllRx() = 0;


public slots:
    virtual bool write(QByteArray) = 0;
    virtual void on_dataReceived() = 0;


signals:
    void dataReceived();



};

#endif // COMMUNICATIONWORKER_H
