#ifndef NETWORKSCAN_H
#define NETWORKSCAN_H

#include <QObject>

#include <QHostInfo>

#define ADDRSCAN_MASK   0xFFFFFF00



class ScanAddrDevThis;
class ScanAddrDevAll;

/////////////////////////////////////////////////////////////////////
class NetworkScan : public QObject
{
    Q_OBJECT

    bool ScanAddrDevThis_running;
    bool ScanAddrDevAll_running;

    QList <QHostInfo> addrs_devThis;
    QList <QHostInfo> addrs_devAll;



public:

    NetworkScan();

    void startScan_addrs_devThis();
    void startScan_addrs_devAll();


    QList <QHostInfo> get_addrs_devThis() { return addrs_devThis; }
    QList <QHostInfo> get_addrs_devAll() { return addrs_devAll; }

public slots:
    void ScanAddrDevThis_finished();
    void ScanAddrDevAll_finished();


private slots:
    void addrs_devThis_add(QHostInfo host);
    void addrs_devAll_add(QHostInfo host);


signals:
    void devAll_finished();
    void devThis_finished();

};


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

#include <QThread>
#include <QNetworkInterface>

/////////////////////////////////////////////////////////////////////
class ScanAddr : public QThread
{
    Q_OBJECT

signals:
    void foundAddr(QHostInfo);
};

/////////////////////////////////////////////////////////////////////
class ScanAddrDevThis : public ScanAddr
{
    Q_OBJECT

public:

    void run() override
    {
        for (QHostAddress &address : QNetworkInterface::allAddresses())
        {
            if (address.protocol() == QAbstractSocket::IPv4Protocol)
            {
                emit foundAddr(QHostInfo::fromName(address.toString()));
            }
        }
    }

    ~ScanAddrDevThis()
    {
//        qDebug() << "Destroyed ScanAddrDevThis"; todo rm
    }

};

/////////////////////////////////////////////////////////////////////
class ScanAddrDevAll : public ScanAddr
{
    Q_OBJECT

    QHostAddress searchedLast;
    QList <QHostInfo> addrsDevThis;

public:

        ScanAddrDevAll(QList <QHostInfo> addrsThis)
            : addrsDevThis(addrsThis) {}

    void run() override
    {


        for (const QHostInfo& addr_devThis : addrsDevThis)
        {
            qDebug() << "looking at addr: " << addr_devThis.addresses().first().toString();

            for (quint32 addrLastByte = 0; addrLastByte < 0xFF; addrLastByte++)
            {
                quint32 addr = addr_devThis.addresses().first().toIPv4Address();
                addr = (addr & ADDRSCAN_MASK) | addrLastByte;
                searchedLast = QHostAddress(addr);
                QHostInfo::lookupHost(QHostAddress(addr).toString(),
                                      this, SLOT(lookupHost_result(QHostInfo)));
            }
        }
    }


    ~ScanAddrDevAll()
    {
//        qDebug() << "Destroyed ScanAddrDevAll";
    }


private slots:
    void lookupHost_result(QHostInfo host)
    {
        if (host.error() == QHostInfo::NoError) {

            QList <QHostAddress> addrs = host.addresses();

            if (!addrs.isEmpty()) {
                QHostAddress a(host.hostName());
                if (a.isNull())
                    foundAddr(host);
                if (a == searchedLast) {
                    emit finished();
                }
            }
        } else {
            qDebug() << "Lookup failed:" << host.errorString();
        }
    }
signals:
    void finished();


};

/////////////////////////////////////////////////////////////////////
#endif // NETWORKSCAN_H
