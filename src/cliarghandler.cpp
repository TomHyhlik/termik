#include "cliarghandler.h"

#include "serialwparam.h"
#include "networkwparam.h"

//////////////////////////////////////////////////////////////////////
CliArgHandler::CliArgHandler(int argc, char** argv)
{
    setComType = comType_none;

    /* the first argument is the cmd of calling the app */
    int currentArg = 1;

    /* now look at the pairs of arguments */
    while (currentArg < argc)
    {
        QString command(argv[currentArg++]);
        /* check if the command starts with "-" */
        if (command.at(0) == ARG_PREFIX_SHORT) {
            command.remove(0, 1); // remove "-" at the beginning
            /* read the passed data to the argument */
            if (currentArg < argc) {
                QString passedData(argv[currentArg++]);
                if (setParam(command, passedData)) {
                    qDebug() << "Setting" << command << " to " << passedData;
                } else {
                    qDebug() << "ERROR: failed to set" << command << " to " << passedData;
                }
            } else {
                qDebug() << "ERROR: No passed data to the command " << command;
                printHelp();
                return;
            }
        } else {
            qDebug() << "ERROR: Failed to handle input arguments, "
                        "the command does not start with \"-\"";
            printHelp();
            return;
        }
    }
}

//////////////////////////////////////////////////////////////////////
void CliArgHandler::printHelp()
{

    printf("*** OPTIONS\n");

    printf("\n\tSelect connection type to connect automatically: \n");
    printHelp_wrap(ARG_CONNECTIONTYPE,      "serial or network");

    printf("\n\tParameters for connection via serial: \n");
    printHelp_wrap(ARG_SERIAL_PORTNAME,      "serial port name");
    printHelp_wrap(ARG_SERIAL_BAUDRATE,      "baud rate");
    printHelp_wrap(ARG_SERIAL_DATABITS,      "data bits");
    printHelp_wrap(ARG_SERIAL_PARITY,        "parity");
    printHelp_wrap(ARG_SERIAL_STOPBITS,      "stop bits");
    printHelp_wrap(ARG_SERIAL_FLOWCONTROL,   "flow control");

    printf("\n\tParameters for connection via network: \n");
    printHelp_wrap(ARG_NETWORK_PROTOCOLTYPE,   "Protocol type");
    printHelp_wrap(ARG_NETWORK_IPADDR,   "IP address");
    printHelp_wrap(ARG_NETWORK_TXPORT,   "Tx port");
    printHelp_wrap(ARG_NETWORK_RXPORT,   "Rx port");

    printf("\n\n");
}

//////////////////////////////////////////////////////////////////////
void CliArgHandler::printHelp_wrap(QString cmd, QString argTitle)
{
    printf("\t\t%s%s\t\t%s\n" ,
           QString(ARG_PREFIX_SHORT).toStdString().c_str(),
           cmd.toStdString().c_str(),
           argTitle.toStdString().c_str());
}

//////////////////////////////////////////////////////////////////////
bool CliArgHandler::setParam(QString command, QString passedData)
{
    bool ok = true;

    switch (validArgs.indexOf(command))
    {
    case ARG_INDEX_NETWORK_IPADDR:
        NetworkWParam::get().IpAddr_Tx = QHostAddress(passedData);
        if (NetworkWParam::get().IpAddr_Tx.isNull())
            ok = false;
        break;
    case ARG_INDEX_NETWORK_TXPORT:
        NetworkWParam::get().port_Tx = quint16(passedData.toInt(&ok, 10));
        break;
    case ARG_INDEX_NETWORK_RXPORT:
        NetworkWParam::get().port_Rx = quint16(passedData.toInt(&ok, 10));
        break;

    case ARG_INDEX_SERIAL_PORTNAME:
        SerialWParam::get().portName = passedData;
        break;
    case ARG_INDEX_SERIAL_BAUDRATE:
        SerialWParam::get().baudRate = passedData.toInt(&ok, 10);
        break;
    case ARG_INDEX_SERIAL_DATABITS:
        SerialWParam::get().dataBits = passedData.toInt(&ok, 10);
        break;
    case ARG_INDEX_SERIAL_PARITY:
        SerialWParam::get().parity = passedData.toInt(&ok, 10);
        break;
    case ARG_INDEX_SERIAL_STOPBITS:
        SerialWParam::get().stopBits = passedData.toInt(&ok, 10);
        break;
    case ARG_INDEX_SERIAL_FLOWCONTROL:
        SerialWParam::get().flowControl = passedData.toInt(&ok, 10);
        break;
    case ARG_INDEX_CONNECTIONTYPE:
        if (passedData == ARG_CONNECTIONTYPE_SERIAL) {
            setComType = comType_serial;
        }
        else if (passedData == ARG_CONNECTIONTYPE_NETWORK) {
            setComType = comType_network;
        }
        else {
            qDebug() << "Failed to handle arguments: " << command << " " << passedData;
            ok = false;
        }
        break;
    case ARG_INDEX_HELP:
    case ARG_INDEX_HELP_LONG:
        printHelp();
        break;

    default:
        qDebug() << "ERROR: Unrecognized command " << ARG_PREFIX_SHORT
                 << command;
        ok = false;
    }

    return ok;
}

//////////////////////////////////////////////////////////////////////

