#ifndef SAVECONFIGURATION_H
#define SAVECONFIGURATION_H

#include <QObject>
#include "serialworker.h"
#include "networkworker.h"
#include "mainwindow.h"
#include "logfile.h"
#include "serialwparam.h"


#define SAVECFG_FILENAME "./termik_cfg.json"

#define JSONTITLE_SERIAL                "Serial"
#define JSONTITLE_SERIAL_PORTNAME       "Port name"
#define JSONTITLE_SERIAL_BAUDRATE       "Baud rate"
#define JSONTITLE_SERIAL_DATABITS       "Data bits"
#define JSONTITLE_SERIAL_PARITY         "Parity"
#define JSONTITLE_SERIAL_STOPBITS       "Stop bits"
#define JSONTITLE_SERIAL_FLOWCONTROL    "Flow control"

#define JSONTITLE_NETWORK                "Network"
#define JSONTITLE_NETWORK_IPADDRESS_RX  "IP address Rx"
#define JSONTITLE_NETWORK_IPADDRESS_TX  "IP address Tx"
#define JSONTITLE_NETWORK_PORTTX        "Port Tx"
#define JSONTITLE_NETWORK_PORTRX        "Port Rx"

#define JSONTITLE_APP                   "Application"
#define JSONTITLE_APP_CONNECTIONTYPE    "Connection type"
#define JSONTITLE_APP_TIMELOGENABLED    "Time log enabled"
#define JSONTITLE_APP_SUFFIXTXENABLED   "Suffix Tx enabled"
#define JSONTITLE_APP_PREFIXTXENABLED   "Prefix Tx enabled"
#define JSONTITLE_APP_SUFFIXTXDATA      "Suffix Tx data"
#define JSONTITLE_APP_PREFIXTXDATA      "Prefix Tx data"
#define JSONTITLE_APP_TIMEINFOENABLED   "Time info enabled"
#define JSONTITLE_APP_SAVEOUTPUTTOFILE  "Save terminal output to file"

#define JSONTITLE_LOG_DIRECTORY         "Log files directory"

#define JSONTITLE_SCRIPT                "Script"
#define JSONTITLE_SCRIPT_FILENAME       "File name"
#define JSONTITLE_SCRIPT_REPEAT         "Repeat"
#define JSONTITLE_SCRIPT_TIMEOUT        "Timeout"
#define JSONTITLE_SCRIPT_DATAFORMAT     "Data format"



//////////////////////////////////////////////////////////////////////////////
class SaveConfigurationData {
public:
    SerialWParam& serial = SerialWParam::get();
    NetworkWorkerParameters network;
    appConfiguration app;
    QString LogFileDir;
    ScriptConfig script;

};



//////////////////////////////////////////////////////////////////////////////
class SaveConfiguration : public QObject
{
    Q_OBJECT

    bool jsonData_parse(QByteArray);
    QByteArray jsonData_make();

public:
    explicit SaveConfiguration(QObject *parent = nullptr);


    bool read();
    bool write();

    SaveConfigurationData data;

signals:

public slots:
};

#endif // SAVECONFIGURATION_H
