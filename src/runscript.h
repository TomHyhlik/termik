#ifndef RUNSCRIPT_H
#define RUNSCRIPT_H

#include <QObject>
#include <QTimer>



#define SCRIPTTIMEOUT_DEFAULT 1000

class dataConverter;

class ScriptConfig {
public:
    QString fileName;

    QList <QByteArray> fileLines;
    bool repeat;
    int timeout;
    int dataFormat;
};



class runScript : public QObject
{
    Q_OBJECT
    ScriptConfig config;
    QTimer  timer;


    void readFile();


public:
    explicit runScript(QObject *parent = nullptr);

    void setFile(QString arg) {
        config.fileName = arg;
    }

    void setTimeout(int);
    void start();

signals:

    void Tx(QByteArray data);
    void log(int, QString);

public slots:


private slots:
    void timeouted();
};

#endif // RUNSCRIPT_H
