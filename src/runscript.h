#ifndef RUNSCRIPT_H
#define RUNSCRIPT_H

#include <QObject>
#include <QTimer>
#include <iostream>
#include <memory>

#define SCRIPTTIMEOUT_DEFAULT 1000

class dataConverter;


class RunScript : public QObject
{
    Q_OBJECT

    std::shared_ptr <QTimer> timer;

    QList <QByteArray> fileContent; // each ByteArray is line

    void readFile();


public:
    explicit RunScript(QObject *parent = nullptr);

    void timeoutUpdate(int);
    int getTimeout();

    void start();
    void stop();
    bool isRunning();

signals:

    void Tx(QByteArray data);
    void log(int, QString);

public slots:


private slots:
    void timeouted();
};

#endif // RUNSCRIPT_H
