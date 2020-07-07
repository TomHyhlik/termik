#ifndef COMMUNICWORKERFACTORY_H
#define COMMUNICWORKERFACTORY_H

#include <QObject>


#include "serialworker.h"
#include "networkworker.h"
#include "communication.h"

class CommunicWorkerFactory : public QObject
{
    Q_OBJECT
public:
    explicit CommunicWorkerFactory();

    CommunicationWorker* create(communicationType type);

signals:

};

#endif // COMMUNICWORKERFACTORY_H
