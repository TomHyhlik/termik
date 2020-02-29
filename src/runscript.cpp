#include <QFile>
#include <memory>


#include "runscript.h"
#include "mainwindow.h"
#include "dataconverter.h"
#include "runscriptparam.h"
#include "log.h"


/////////////////////////////////////////////////////////////////
RunScript::RunScript()
{
}

/////////////////////////////////////////////////////////////////
void RunScript::run()
{
    isRunning = true;

    log(info, QString("Reading file content: %1")
        .arg(RunScriptParam::get().fileName));

    QList <QByteArray> fileContent;

    if (!readFileContent(&fileContent)) {
        log(error, QString("Failed to read the file content"));
        return;
    }

    log(info, "Transmitting the script...");

    do {
        for (const QByteArray& line : fileContent) {
            if (!isRunning) return;
            Tx(line);
            this->msleep(RunScriptParam::get().timeout);
        }
    } while (RunScriptParam::get().repeat);
}

/////////////////////////////////////////////////////////////////
bool RunScript::readFileContent(QList <QByteArray> * fileContent)
{    
    QFile file(RunScriptParam::get().fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }

    QTextStream textStream(&file);

    QString line;

    while (textStream.readLineInto(&line))
    {
        dataConverter dataConv;
        switch (RunScriptParam::get().dFormat)
        {
        case data_ascii:
            dataConv.setStrAscii(line);
            break;
        case data_hex:
            dataConv.setStrHex(line);
            break;
        default:
            LOG_T(error, "Selected invalid file format");
            return false;
        }
        fileContent->append(dataConv.getByteArray());
    }
    file.close();
    return true;
}

/////////////////////////////////////////////////////////////////
void RunScript::stop()
{
    isRunning = false;
}

/////////////////////////////////////////////////////////////////
void RunScript::setTimeout(int val)
{
    RunScriptParam::get().timeout = val;
}

/////////////////////////////////////////////////////////////////
void RunScript::timeoutUpdate(int msecs)
{
    RunScriptParam::get().timeout = msecs;
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
