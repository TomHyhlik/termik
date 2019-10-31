#include <QTimer>
#include <QFile>

#include "runscript.h"
#include "mainwindow.h"
#include "dataconverter.h"
/////////////////////////////////////////////////////////////////
runScript::runScript(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeouted()));

    setDataFormat(data_ascii);


}
bool runScript::isRunning()
{
    return timer->isActive();
}

/////////////////////////////////////////////////////////////////
void runScript::start()
{
    log(note, QString("Starting script: %1").arg(getfile()));
    readFile();
    timer->start(config.timeout);
}

void runScript::stop()
{
    timer->stop();
    fileContent.clear();
}

/////////////////////////////////////////////////////////////////
void runScript::timeouted()
{
    if (!fileContent.isEmpty()) {
        Tx(fileContent.at(0));
        fileContent.removeFirst();
    } else {
        timer->stop();
        if (config.repeat) {
            qDebug() << "Repeating script";
            start();
        }
    }
}

/////////////////////////////////////////////////////////////////
void runScript::readFile()
{
    fileContent.clear();

    qDebug() << "reading file" << config.fileName;

    QFile file(config.fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString e = "Unable to open script file";
        log(error, e);
        qDebug() << e;
        return;
    }

    QTextStream textStream(&file);


    while (1) {
        QString line = QString(textStream.readLine());
        if (line.isEmpty()) {
            break;
        } else {
            dataConverter dataConv;
            switch (config.dataFormat) {
            case data_ascii:
                dataConv.setStrAscii(line);
                break;
            case data_hex:
                dataConv.setStrHex(line);
                break;
            default:
                qDebug() << "ERROR: unitialized data format for the script";
                return;
            }
            fileContent.append(dataConv.getByteArray());
        }

    }
    file.close();
}
/////////////////////////////////////////////////////////////////
void runScript::setTimeout(int msecs)
{
    config.timeout = msecs;

    if (timer->isActive()) {
        timer->stop();
        timer->start(config.timeout);
    }
}
int runScript::getTimeout()
{
    return config.timeout;
}

/////////////////////////////////////////////////////////////////
void runScript::setDataFormat(int format) {
    if (format == data_ascii || format == data_hex) {
        config.dataFormat = format;
    } else {
        qDebug() << "Invalid data format";
    }
}
int runScript::getDataFormat()
{
    return config.dataFormat;
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
