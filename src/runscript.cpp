#include <QTimer>
#include <QFile>

#include "runscript.h"
#include "mainwindow.h"
#include "dataconverter.h"
#include "runscriptparam.h"
#include <memory>


/////////////////////////////////////////////////////////////////
RunScript::RunScript()
{
}

/////////////////////////////////////////////////////////////////
void RunScript::run()
{
    isRunning = true;

    do {
        QList <QByteArray> fileContent;

        if (readFileContent(&fileContent)) {
            while (!fileContent.isEmpty() && isRunning) {
                Tx(fileContent.takeFirst());
                this->msleep(RunScriptParam::get().timeout);
            }
        } else {
            log(error, QString("Failed to read script content from: %1")
                                    .arg(RunScriptParam::get().fileName));
            break;
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
            log(error, "Selected invalid file format");
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
