#include "networkscan.h"

void addrAdd(QList <QHostInfo> * addrs, QHostInfo host);


//////////////////////////////////////////////////
NetworkScan::NetworkScan()
{

    ScanAddrDevThis_running = false;
    ScanAddrDevAll_running = false;
}

//////////////////////////////////////////////////
void NetworkScan::startScan_addrs_devThis()
{
    if (ScanAddrDevThis_running) return;

    ScanAddrDevThis_running = true;

    ScanAddrDevThis* scan = new ScanAddrDevThis();

    qRegisterMetaType<QHostInfo>("QHostInfo");
    connect(scan, &ScanAddr::foundAddr,
            this, &NetworkScan::addrs_devThis_add);

    connect(scan, &ScanAddr::finished,
            this, &NetworkScan::devThis_finished);

    connect(scan, &ScanAddr::finished,
            this, &NetworkScan::ScanAddrDevThis_finished);

    connect(scan, &ScanAddr::finished,
            scan, &QObject::deleteLater);

    scan->start();
}

//////////////////////////////////////////////////
void NetworkScan::ScanAddrDevThis_finished()
{
    ScanAddrDevThis_running = false;
}


//////////////////////////////////////////////////
void NetworkScan::startScan_addrs_devAll()
{
    if (ScanAddrDevAll_running) return;

    ScanAddrDevAll_running = true;

    ScanAddrDevAll* scan = new ScanAddrDevAll(addrs_devThis);

    qRegisterMetaType<QHostInfo>("QHostInfo");
    connect(scan, &ScanAddr::foundAddr,
            this, &NetworkScan::addrs_devAll_add);

    connect(scan, &ScanAddr::finished,
            this, &NetworkScan::devAll_finished);

    connect(scan, &ScanAddr::finished,
            this, &NetworkScan::ScanAddrDevAll_finished);

    connect(scan, &ScanAddr::finished,
            scan, &QObject::deleteLater);

    scan->start();
}

//////////////////////////////////////////////////
void NetworkScan::ScanAddrDevAll_finished()
{
    ScanAddrDevAll_running = false;
}

//////////////////////////////////////////////////
void NetworkScan::addrs_devThis_add(QHostInfo host) {
    addrAdd(&addrs_devThis, host);
}
void NetworkScan::addrs_devAll_add(QHostInfo host) {
    addrAdd(&addrs_devAll, host);
}


//////////////////////////////////////////////////
void addrAdd(QList <QHostInfo> * addrs, QHostInfo host)
{
    bool isHere = false;
    for (QHostInfo addr : *addrs)
    {
        if (addr.addresses().first() == host.addresses().first())
        {
            isHere = true;
            break;
        }
    }
    if (!isHere)
        addrs->append(host);
}

//////////////////////////////////////////////////
