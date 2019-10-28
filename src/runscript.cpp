#include <QTimer>
#include <QFile>

#include "runscript.h"
#include "mainwindow.h"
#include "dataconverter.h"
/////////////////////////////////////////////////////////////////
runScript::runScript(QObject *parent) : QObject(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &runScript::timeouted);

}

/////////////////////////////////////////////////////////////////
void runScript::start()
{
    readFile();
    timer.start();
}

/////////////////////////////////////////////////////////////////
void runScript::timeouted()
{
    if (!config.fileLines.isEmpty()) {
        Tx(config.fileLines.at(0));
        config.fileLines.removeFirst();
    } else {
        timer.stop();
        if (config.repeat) {
            start();
        }
    }
}

/////////////////////////////////////////////////////////////////
void runScript::readFile()
{
    config.fileLines.clear();

    QFile file(config.fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        log(error, "Unable to open script file");
        return;
    }

    while (1) {
        QString line = QString(file.readLine());
        if (line.isNull()) {
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
                return;
            }
            config.fileLines.append(dataConv.getByteArray());
        }
    }

    file.close();
}
/////////////////////////////////////////////////////////////////
void runScript::setTimeout(int msecs)
{
    config.timeout = msecs;

    if (timer.isActive()) {
        timer.stop();
        timer.start(config.timeout);
    }
}

/////////////////////////////////////////////////////////////////
