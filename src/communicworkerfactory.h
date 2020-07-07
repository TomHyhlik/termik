#ifndef COMMUNICWORKERFACTORY_H
#define COMMUNICWORKERFACTORY_H

#include <QObject>

class CommunicWorkerFactory : public QObject
{
    Q_OBJECT
public:
    explicit CommunicWorkerFactory(QObject *parent = nullptr);

signals:

};

#endif // COMMUNICWORKERFACTORY_H
