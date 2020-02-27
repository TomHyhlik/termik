#ifndef RUNSCRIPT_H
#define RUNSCRIPT_H

#include <QThread>
#include <iostream>
#include <memory>

#define SCRIPTTIMEOUT_DEFAULT 1000

class dataConverter;


class RunScript : public QThread
{
    Q_OBJECT

    bool readFileContent(QList <QByteArray> *fileContent);
    bool isRunning;

public:
    explicit RunScript();

    void run() override;

    void timeoutUpdate(int);

    void stop();
    void setTimeout(int);

signals:
    void Tx(QByteArray data);
    void log(int, QString);

public slots:



};

#endif // RUNSCRIPT_H
