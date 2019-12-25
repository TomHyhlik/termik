#include "appargs.h"

AppArgs::AppArgs()
{

    this->append(ARG_CONNECTIONTYPE);

    this->append(ARG_NETWORK_IPADDR);
    this->append(ARG_NETWORK_TXPORT);
    this->append(ARG_NETWORK_RXPORT);
    this->append(ARG_NETWORK_PROTOCOLTYPE);

    this->append(ARG_SERIAL_PORTNAME);
    this->append(ARG_SERIAL_BAUDRATE);
    this->append(ARG_SERIAL_DATABITS);
    this->append(ARG_SERIAL_PARITY);
    this->append(ARG_SERIAL_STOPBITS);
    this->append(ARG_SERIAL_FLOWCONTROL);

    this->append(ARG_PREFIX_SHORT);
    this->append(ARG_HELP);
    this->append(ARG_HELP_LONG);

}
