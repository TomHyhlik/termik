#include "cliarghandler.h"

#include "serialwparam.h"
#include "networkwparam.h"

//////////////////////////////////////////////////////////////////////
/// \brief MainWindow::handleAppArguments
/// \param arguments is the QStringList of terminal passed arguments
///     This function is called in MainWindow initialization
///     it controls the syntax of app terminal arguments and calls
///      setParam() to use these parameters
void CliArgHandler::handleAppArguments(QStringList arguments)
{
    /* the first argument is the cmd of calling the app */
    arguments.removeFirst();

    /* now look at the pairs of arguments */
    while (!arguments.isEmpty())
    {
        QString command, passedData;

        command = arguments.at(0);
        arguments.removeFirst();

        /* check if the command starts with "-" */
        if (command.at(0) == ARG_PREFIX_SHORT) {
            command.remove(0, 1); // remove "-" at the beginning
            /* read the passed data to the argument */
            if (!arguments.isEmpty()) {
                passedData = arguments.at(0);
                arguments.removeFirst();
                if (!setParam(command, passedData)) {
                    printHelp();
                    return;
                }
            } else {
                qDebug() << "ERROR: No passed data for command " << command;
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

    if (communic->getLastConnType() != comType_none) {
        qDebug() << "Trying to connect automatically";
        communic->establish();
    }
}

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

void CliArgHandler::printHelp_wrap(QString cmd, QString argTitle)
{
    printf("\t\t%s%s\t\t%s\n" ,
           QString(ARG_PREFIX_SHORT).toStdString().c_str(),
           cmd.toStdString().c_str(),
           argTitle.toStdString().c_str());

    //    qDebug() << "\t\t" << QString(ARG_PREFIX_SHORT).toStdString().c_str() <<
    //                           cmd.toStdString().c_str()  << "\t" << argTitle;


    //    qDebug() << "\t\t"
    //             << QString(ARG_PREFIX_SHORT).toStdString().c_str()
    //             << cmd.toStdString().c_str()
    //             << "\t\t"
    //             << argTitle.toStdString().c_str();
}


bool CliArgHandler::setParam(QString command, QString passedData)
{
    bool ok = true;

    AppArgs appargs;

    switch (appargs.indexOf(command))
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
            communic->lastComType = comType_serial;
        }
        else if (passedData == ARG_CONNECTIONTYPE_NETWORK) {
            communic->lastComType = comType_network;
        }
        else {
            qDebug() << "Failed to handle arguments: " << command << " " << passedData;
            ok = false;
        }
        break;
    case ARG_INDEX_HELP:
    case ARG_INDEX_HELP_LONG:
        printHelp();
        close();
        break;

    default:
        qDebug() << "ERROR: Unknown command " << ARG_PREFIX_SHORT
                 << command;
        ok = false;
    }

    if (ok) {
        qDebug() << "Setting" << command << " to " << passedData;
    }

    return ok;
}

QStringList CliArgHandler::getValidArgs()
{
    QStringList validArgs;

    validArgs.append(ARG_CONNECTIONTYPE);

    validArgs.append(ARG_NETWORK_IPADDR);
    validArgs.append(ARG_NETWORK_TXPORT);
    validArgs.append(ARG_NETWORK_RXPORT);
    validArgs.append(ARG_NETWORK_PROTOCOLTYPE);

    validArgs.append(ARG_SERIAL_PORTNAME);
    validArgs.append(ARG_SERIAL_BAUDRATE);
    validArgs.append(ARG_SERIAL_DATABITS);
    validArgs.append(ARG_SERIAL_PARITY);
    validArgs.append(ARG_SERIAL_STOPBITS);
    validArgs.append(ARG_SERIAL_FLOWCONTROL);

    validArgs.append(ARG_PREFIX_SHORT);
    validArgs.append(ARG_HELP);
    validArgs.append(ARG_HELP_LONG);

    return validArgs;

}



