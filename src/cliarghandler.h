#ifndef CLIARGHANDLER_H
#define CLIARGHANDLER_H

#include <QObject>
#include "communication.h"

////////////////////////////////////////////////

#define ARG_CONNECTIONTYPE      "conn"

#define ARG_NETWORK_IPADDR      "addr"
#define ARG_NETWORK_TXPORT      "ptx"
#define ARG_NETWORK_RXPORT      "prx"
#define ARG_NETWORK_PROTOCOLTYPE "ptype"

#define ARG_SERIAL_PORTNAME    "pname"
#define ARG_SERIAL_BAUDRATE    "baud"
#define ARG_SERIAL_DATABITS    "dbits"
#define ARG_SERIAL_PARITY      "par"
#define ARG_SERIAL_STOPBITS    "sbits"
#define ARG_SERIAL_FLOWCONTROL "fcontr"

#define ARG_HELP               "h"
#define ARG_HELP_LONG          "help"

////////////////////////////////////////////////
#define ARG_PREFIX_SHORT        "-"

#define ARG_CONNECTIONTYPE_SERIAL   "serial"
#define ARG_CONNECTIONTYPE_NETWORK  "network"

////////////////////////////////////////////////


enum {
    ARG_INDEX_CONNECTIONTYPE,
    ARG_INDEX_NETWORK_IPADDR,
    ARG_INDEX_NETWORK_TXPORT,
    ARG_INDEX_NETWORK_RXPORT,
    ARG_INDEX_NETWORK_PROTOCOLTYPE,

    ARG_INDEX_SERIAL_PORTNAME,
    ARG_INDEX_SERIAL_BAUDRATE,
    ARG_INDEX_SERIAL_DATABITS,
    ARG_INDEX_SERIAL_PARITY,
    ARG_INDEX_SERIAL_STOPBITS,
    ARG_INDEX_SERIAL_FLOWCONTROL,

    ARG_INDEX_HELP,
    ARG_INDEX_HELP_LONG,
};

#define ARG_ERROR       "ERROR: Failed to handle arguments."

////////////////////////////////////////////////

class CliArgHandler : public QObject
{
    Q_OBJECT

    QStringList arguments;
    communicationType setComType;

    const QList <QString> validArgs =
    {
        {ARG_CONNECTIONTYPE},

        {ARG_NETWORK_IPADDR},
        {ARG_NETWORK_TXPORT},
        {ARG_NETWORK_RXPORT},
        {ARG_NETWORK_PROTOCOLTYPE},

        {ARG_SERIAL_PORTNAME},
        {ARG_SERIAL_BAUDRATE},
        {ARG_SERIAL_DATABITS},
        {ARG_SERIAL_PARITY},
        {ARG_SERIAL_STOPBITS},
        {ARG_SERIAL_FLOWCONTROL},

        {ARG_PREFIX_SHORT},
        {ARG_HELP},
        {ARG_HELP_LONG},
    };

public:
    explicit CliArgHandler(QStringList val);


    communicationType getComType() { return setComType; }
    void handleAppArguments(QStringList);
    void printHelp();
    void printHelp_wrap(QString cmd, QString argTitle);
    bool setParam(QString command, QString passedData);


signals:

};

#endif // CLIARGHANDLER_H
