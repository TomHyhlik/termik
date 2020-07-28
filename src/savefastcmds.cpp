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
bool SaveFastCmds::jsonData_parse(QByteArray parsingData)
{
    QJsonDocument jDoc = QJsonDocument::fromJson(parsingData);
    if (jDoc.isObject()) {

        QJsonObject jObj = jDoc.object();

        for (int i = 0; i < FCMD_MAXCNT; i++)
        {
            QJsonObject jObj_cmd = jObj.value(QString(JSONTITLE_FCMD_ID).arg(i)).toObject();
            if (jObj_cmd.isEmpty())
                break;
            FastCmdData cmdData;
            cmdData.name = jObj_cmd.value(JSONTITLE_FCMD_NAME).toString();
            cmdData.cmd = jObj_cmd.value(JSONTITLE_FCMD_DATA).toString();
            cmdData.format = jObj_cmd.value(JSONTITLE_FCMD_FORMAT).toInt();
            cmdDataList.append(cmdData);
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


