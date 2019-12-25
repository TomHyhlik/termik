#ifndef APPARGS_H
#define APPARGS_H

#include <QObject>

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

////////////////////////////////////////////////
#define ARG_PREFIX_SHORT        "-"

#define ARG_CONNECTIONTYPE_SERIAL   "serial"
#define ARG_CONNECTIONTYPE_NETWORK  "network"


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



class AppArgs : public QStringList
{
public:
    AppArgs();


};

#endif // APPARGS_H
