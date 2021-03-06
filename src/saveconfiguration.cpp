#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "mainwindow.h"
#include "saveconfiguration.h"
#include "serialwparam.h"
#include "runscriptparam.h"
#include "dataconverter.h"
#include "uilog.h"

SaveConfiguration::SaveConfiguration(QObject *parent) : QObject(parent)
{
}

//////////////////////////////////////////////////////////////////////////////
bool SaveConfiguration::read()
{
    const QString filename = SAVECFG_FILENAME;
    if (QFile::exists(filename)) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray fileContent = file.readAll();
            file.close();
            if (jsonData_parse(fileContent)) {
                return true;
            }
        } else {
            LOG_T(error, tr("Failed to read configuration from %1")
                  .arg(SAVECFG_FILENAME));
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////
bool SaveConfiguration::write()
{
    const QString filename = SAVECFG_FILENAME;
    QFile file(filename);

    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        file.resize(0);
        QByteArray jsonData = jsonData_make();
        QTextStream dataStream(&file);
        dataStream << jsonData;
        file.flush();
        file.close();
        return true;
    }

    LOG(tr("Failed to save configuration to: %1").arg(filename));

    return false;
}

//////////////////////////////////////////////////////////////////////////////
bool SaveConfiguration::jsonData_parse(QByteArray parsingData)
{
    QJsonDocument jDoc = QJsonDocument::fromJson(parsingData);
    if (jDoc.isObject()) {

        QJsonObject jObj = jDoc.object();

        QJsonObject jObj_serial = jObj.value(QString(JSONTITLE_SERIAL)).toObject();
        SerialWParam::get().portName = jObj_serial.value(QString(JSONTITLE_SERIAL_PORTNAME)).toString();
        SerialWParam::get().baudRate = jObj_serial.value(QString(JSONTITLE_SERIAL_BAUDRATE)).toInt();
        SerialWParam::get().dataBits = jObj_serial.value(QString(JSONTITLE_SERIAL_DATABITS)).toInt();
        SerialWParam::get().parity = jObj_serial.value(QString(JSONTITLE_SERIAL_PARITY)).toInt();
        SerialWParam::get().stopBits = jObj_serial.value(QString(JSONTITLE_SERIAL_STOPBITS)).toInt();
        SerialWParam::get().flowControl = jObj_serial.value(QString(JSONTITLE_SERIAL_FLOWCONTROL)).toInt();

        QJsonObject jObj_network = jObj.value(QString(JSONTITLE_NETWORK)).toObject();
        NetworkWParam::get().IpAddr_Rx = QHostAddress(jObj_network.value(QString(JSONTITLE_NETWORK_IPADDRESS_RX)).toString());
        NetworkWParam::get().IpAddr_Tx = QHostAddress(jObj_network.value(QString(JSONTITLE_NETWORK_IPADDRESS_TX)).toString());
        NetworkWParam::get().port_Tx = quint16(jObj_network.value(QString(JSONTITLE_NETWORK_PORTTX)).toInt());
        NetworkWParam::get().port_Rx = quint16(jObj_network.value(QString(JSONTITLE_NETWORK_PORTRX)).toInt());
        NetworkWParam::get().protocolType = quint16(jObj_network.value(QString(JSONTITLE_NETWORK_PROTOCOL)).toInt());

        QJsonObject jObj_app = jObj.value(QString(JSONTITLE_APP)).toObject();
//        data.app.connectionType = jObj_app.value(QString(JSONTITLE_APP_CONNECTIONTYPE)).toBool(); // todo
        data.app.timeLogEnabled = jObj_app.value(QString(JSONTITLE_APP_TIMELOGENABLED)).toBool();
        data.app.suffix_tx_enabled = jObj_app.value(QString(JSONTITLE_APP_SUFFIXTXENABLED)).toBool();
        data.app.prefix_tx_enabled = jObj_app.value(QString(JSONTITLE_APP_PREFIXTXENABLED)).toBool();
        data.app.suffix_tx = jObj_app.value(QString(JSONTITLE_APP_SUFFIXTXDATA)).toString().toUtf8();
        data.app.prefix_tx = jObj_app.value(QString(JSONTITLE_APP_PREFIXTXDATA)).toString().toUtf8();
        data.app.timeInfoEnabled = jObj_app.value(QString(JSONTITLE_APP_TIMEINFOENABLED)).toBool();
//        data.app.saveTerminalOutToFile = jObj_app.value(QString(JSONTITLE_APP_SAVEOUTPUTTOFILE)).toBool(); todo rm
        data.app.outputFileDir = jObj_app.value(QString(JSONTITLE_APP_LOGDIRECTORY)).toString();

        QJsonObject jObj_script = jObj.value(QString(JSONTITLE_SCRIPT)).toObject();
        RunScriptParam::get().fileName = jObj_script.value(JSONTITLE_SCRIPT_FILENAME).toString();
        RunScriptParam::get().repeat = jObj_script.value(JSONTITLE_SCRIPT_REPEAT).toBool();
        RunScriptParam::get().timeout = jObj_script.value(JSONTITLE_SCRIPT_TIMEOUT).toInt();
        RunScriptParam::get().dFormat = dataFormat(jObj_script.value(JSONTITLE_SCRIPT_DATAFORMAT).toInt());

        return true;
    } else {
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////
QByteArray SaveConfiguration::jsonData_make()
{
    QJsonObject jObj;

    QJsonObject jObj_serial;
    jObj_serial.insert(JSONTITLE_SERIAL_PORTNAME ,
                       QJsonValue::fromVariant(SerialWParam::get().portName));
    jObj_serial.insert(JSONTITLE_SERIAL_BAUDRATE ,
                       QJsonValue::fromVariant(SerialWParam::get().baudRate));
    jObj_serial.insert(JSONTITLE_SERIAL_DATABITS ,
                       QJsonValue::fromVariant(SerialWParam::get().dataBits));
    jObj_serial.insert(JSONTITLE_SERIAL_PARITY ,
                       QJsonValue::fromVariant(SerialWParam::get().parity));
    jObj_serial.insert(JSONTITLE_SERIAL_STOPBITS ,
                       QJsonValue::fromVariant(SerialWParam::get().stopBits));
    jObj_serial.insert(JSONTITLE_SERIAL_FLOWCONTROL ,
                       QJsonValue::fromVariant(SerialWParam::get().flowControl));
    jObj.insert(JSONTITLE_SERIAL, jObj_serial);

    QJsonObject jObj_network;
    jObj_network.insert(JSONTITLE_NETWORK_IPADDRESS_RX ,
                        QJsonValue::fromVariant(NetworkWParam::get().IpAddr_Rx.toString()));
    jObj_network.insert(JSONTITLE_NETWORK_IPADDRESS_TX ,
                        QJsonValue::fromVariant(NetworkWParam::get().IpAddr_Tx.toString()));
    jObj_network.insert(JSONTITLE_NETWORK_PORTTX ,
                        QJsonValue::fromVariant(NetworkWParam::get().port_Tx));
    jObj_network.insert(JSONTITLE_NETWORK_PORTRX ,
                        QJsonValue::fromVariant(NetworkWParam::get().port_Rx));
    jObj_network.insert(JSONTITLE_NETWORK_PROTOCOL ,
                        QJsonValue::fromVariant(NetworkWParam::get().protocolType));
    jObj.insert(JSONTITLE_NETWORK, jObj_network);

    QJsonObject jObj_app;
//    jObj_app.insert(JSONTITLE_APP_CONNECTIONTYPE ,
//                    QJsonValue::fromVariant(data.app.connectionType)); // todo
    jObj_app.insert(JSONTITLE_APP_TIMELOGENABLED ,
                    QJsonValue::fromVariant(data.app.timeLogEnabled));
    jObj_app.insert(JSONTITLE_APP_SUFFIXTXENABLED ,
                    QJsonValue::fromVariant(data.app.suffix_tx_enabled));
    jObj_app.insert(JSONTITLE_APP_PREFIXTXENABLED ,
                    QJsonValue::fromVariant(data.app.prefix_tx_enabled));
    jObj_app.insert(JSONTITLE_APP_SUFFIXTXDATA ,
                    QJsonValue::fromVariant(data.app.suffix_tx));
    jObj_app.insert(JSONTITLE_APP_PREFIXTXDATA ,
                    QJsonValue::fromVariant(data.app.prefix_tx));
    jObj_app.insert(JSONTITLE_APP_TIMEINFOENABLED ,
                    QJsonValue::fromVariant(data.app.prefix_tx_enabled));
//    jObj_app.insert(JSONTITLE_APP_SAVEOUTPUTTOFILE ,
//                    QJsonValue::fromVariant(data.app.saveTerminalOutToFile));  todo rm
    jObj.insert(QString(JSONTITLE_APP_LOGDIRECTORY),
                QJsonValue::fromVariant(data.app.outputFileDir));
    jObj.insert(JSONTITLE_APP, jObj_app);

    QJsonObject jObj_script;
    jObj_script.insert(JSONTITLE_SCRIPT_FILENAME ,
                       QJsonValue::fromVariant(data.script.fileName));
    jObj_script.insert(JSONTITLE_SCRIPT_REPEAT ,
                       QJsonValue::fromVariant(data.script.repeat));
    jObj_script.insert(JSONTITLE_SCRIPT_TIMEOUT ,
                       QJsonValue::fromVariant(data.script.timeout));
    jObj_script.insert(JSONTITLE_SCRIPT_DATAFORMAT ,
                       QJsonValue::fromVariant(int(data.script.dFormat)));
    jObj.insert(JSONTITLE_SCRIPT, jObj_script);

    QJsonDocument doc(jObj);
    QByteArray jsonEncodedData = doc.toJson();

    return jsonEncodedData;
}

//////////////////////////////////////////////////////////////////////////////














