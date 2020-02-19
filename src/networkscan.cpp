#include "networkscan.h"

#include <QNetworkInterface>

NetworkScan::NetworkScan()
{

}


//////////////////////////////////////////////////
void NetworkScan::scanNetwork_addHost(QHostInfo host)
{
    bool isHere = false;
    for (int i = 0; i < addrs_devAll.size(); i++) {
        if (addrs_devAll.at(i).hostName() == host.hostName()) {
            isHere = true;
            break;
        }
    }
    if (!isHere) {
        addrs_devAll.append(host);
    }
}

//////////////////////////////////////////////////
void NetworkScan::start()
{
    for (const QHostInfo& addr_devThis : get_addrs_devThis())
    {
        for (quint32 addrLastByte = 0; addrLastByte < 255; addrLastByte++)
        {
            quint32 addr = addr_devThis.addresses().first().toIPv4Address();
            addr = (addr & ADDRSCAN_MASK) | addrLastByte;
            searchedLast = QHostAddress(addr);
            QHostInfo::lookupHost(QHostAddress(addr).toString(),
                                  this, SLOT(scanNetwork_printResults(QHostInfo)));
            //                    QHostInfo::lookupHost(QString("10.0.0.%1").arg(i, 0, 10), // todo select ip addr
            //                                          this, SLOT(scanNetwork_printResults(QHostInfo)));

        }
    }
}

//////////////////////////////////////////////////
void NetworkScan::scanNetwork_printResults(QHostInfo host)
{
    if (host.error() == QHostInfo::NoError) {

        QList <QHostAddress> addrs = host.addresses();

        if (!addrs.isEmpty()) {
            //            QHostAddress addr = host.addresses().first();
            QHostAddress a(host.hostName());
            if (a.isNull()) {
                // qDebug() << "Addr: " << addrs.first().toString() << "Name: " << host.hostName();
                scanNetwork_addHost(host);
            }

            if (a ==searchedLast) {
                emit finished();
            }
        }
    } else {
        qDebug() << "Lookup failed:" << host.errorString();
    }

    //    const auto addresses = host.addresses();
    //    for (const QHostAddress &address : addresses) {
    //        qDebug() << "Found address:" << address.toString();
    //    }
}


//////////////////////////////////////////////////
QList <QHostInfo> NetworkScan::get_addrs_devThis()
{
    QList <QHostInfo> myIPaddresses;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            myIPaddresses.append(QHostInfo::fromName(address.toString()));
        }
    }
    return myIPaddresses;
}
//////////////////////////////////////////////////
QList <QHostInfo> NetworkScan::get_addrs_devAll()
{
    return addrs_devAll;
}

//////////////////////////////////////////////////
