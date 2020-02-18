#ifndef COMMUNICATIONWORKER_H
#define COMMUNICATIONWORKER_H

#include <QObject>

class CommunicationWorker : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationWorker(QObject *parent = nullptr);

signals:

};

#endif // COMMUNICATIONWORKER_H
