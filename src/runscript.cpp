#include <QTimer>
#include <QFile>

#include "runscript.h"
#include "mainwindow.h"
#include "dataconverter.h"
#include "runscriptparam.h"
#include <memory>


/////////////////////////////////////////////////////////////////
RunScript::RunScript(QObject *parent) : QObject(parent)
{
    timer = std::unique_ptr <QTimer> (new QTimer);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(timeouted()));

}
bool RunScript::isRunning()
{
    return timer->isActive();
}

/////////////////////////////////////////////////////////////////
void RunScript::start()
{
    log(note, QString("Starting script: %1")
        .arg(RunScriptParam::get().fileName));
    readFile();
    timer->start(RunScriptParam::get().timeout);
}

void RunScript::stop()
{
    timer->stop();
    fileContent.clear();
}

/////////////////////////////////////////////////////////////////
void RunScript::timeouted()
{
    if (!fileContent.isEmpty()) {
        Tx(fileContent.at(0));
        fileContent.removeFirst();
    } else {
        timer->stop();
        if (RunScriptParam::get().repeat) {
            qDebug() << "Repeating script";
            start();
        }
    }
}

/////////////////////////////////////////////////////////////////
void RunScript::readFile()
{
    fileContent.clear();

    qDebug() << "reading file" << RunScriptParam::get().fileName;

    QFile file(RunScriptParam::get().fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString e = "Unable to open script file";
        log(error, e);
        qDebug() << e;
        return;
    }

    QTextStream textStream(&file);


    while (1) {
        QString line = QString(textStream.readLine());
        if (!line.isEmpty()) {
            dataConverter dataConv;
            switch (RunScriptParam::get().dFormat) {
            case data_ascii:
                dataConv.setStrAscii(line);
                break;
            case data_hex:
                dataConv.setStrHex(line);
                break;
            default:
                qDebug() << "ERROR: unitialized data format of the script";
                return;
            }
            fileContent.append(dataConv.getByteArray());
        } else {
            break;
        }

    }
    file.close();
}
/////////////////////////////////////////////////////////////////
void RunScript::timeoutUpdate(int msecs)
{
    RunScriptParam::get().timeout = msecs;

    if (timer->isActive()) {
        timer->stop();
        timer->start(RunScriptParam::get().timeout);
    }
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
