#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "mainwindow.h"
#include "serialwparam.h"
#include "runscriptparam.h"
#include "dataconverter.h"
#include "uilog.h"

#include "savefastcmds.h"


//////////////////////////////////////////////////////////////////////////////
SaveFastCmds::SaveFastCmds()
{
    fileName = SAVEFASTCMDS_FILENAME;
}

//////////////////////////////////////////////////////////////////////////////
void SaveFastCmds::addCmdData(FastCmdData cmdData)
{
    cmdDataList.append(cmdData);
}

//////////////////////////////////////////////////////////////////////////////
bool SaveFastCmds::jsonData_parse(QByteArray parsingData)
{
    QJsonDocument jDoc = QJsonDocument::fromJson(parsingData);
    if (jDoc.isObject()) {

        QJsonObject jObj = jDoc.object();

//        QJsonObject jObj_script = jObj.value(QString(JSONTITLE_SCRIPT)).toObject();
//        RunScriptParam::get().fileName = jObj_script.value(JSONTITLE_SCRIPT_FILENAME).toString();
//        RunScriptParam::get().repeat = jObj_script.value(JSONTITLE_SCRIPT_REPEAT).toBool();
//        RunScriptParam::get().timeout = jObj_script.value(JSONTITLE_SCRIPT_TIMEOUT).toInt();
//        RunScriptParam::get().dFormat = dataFormat(jObj_script.value(JSONTITLE_SCRIPT_DATAFORMAT).toInt());

        return true;
    } else {
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////
QByteArray SaveFastCmds::jsonData_make()
{
    QJsonObject jObj;
    int ctr = 0;
    for (const FastCmdData &fastCmdData: cmdDataList)
    {

        QJsonObject jObj_cmd;
        jObj_cmd.insert("name", QJsonValue::fromVariant(fastCmdData.name));
        jObj_cmd.insert("data", QJsonValue::fromVariant(fastCmdData.cmd));
        jObj_cmd.insert("format", QJsonValue::fromVariant(fastCmdData.format));

        jObj.insert(QString("Cmd_%1").arg(ctr++), jObj_cmd);
    }

    QJsonDocument doc(jObj);
    QByteArray jsonEncodedData = doc.toJson();


    return jsonEncodedData;
}

//////////////////////////////////////////////////////////////////////////////


