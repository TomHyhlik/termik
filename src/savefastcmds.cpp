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

        for (int i = 0; i < 20; i++)
        {
            QJsonObject jObj_script = jObj.value(QString(JSONTITLE_FCMD_ID).arg(i)).toObject();
            if (jObj_script.isEmpty()) {
                qDebug() << "CMD: " << i << "HERE";
            }
            else
            {
                qDebug() << "CMD: " << i << "NOT HERE";

            }
//            RunScriptParam::get().fileName = jObj_script.value(JSONTITLE_SCRIPT_FILENAME).toString();

        }
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
        jObj_cmd.insert(JSONTITLE_FCMD_NAME, QJsonValue::fromVariant(fastCmdData.name));
        jObj_cmd.insert(JSONTITLE_FCMD_DATA, QJsonValue::fromVariant(fastCmdData.cmd));
        jObj_cmd.insert(JSONTITLE_FCMD_FORMAT, QJsonValue::fromVariant(fastCmdData.format));
        jObj.insert(QString(JSONTITLE_FCMD_ID).arg(ctr++), jObj_cmd);
    }

    QJsonDocument doc(jObj);
    QByteArray jsonEncodedData = doc.toJson();


    return jsonEncodedData;
}

//////////////////////////////////////////////////////////////////////////////


