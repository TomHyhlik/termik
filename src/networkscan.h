#ifndef NETWORKSCAN_H
#define NETWORKSCAN_H

#include <QObject>

#include <QHostInfo>

class NetworkScan : public QObject
{
    Q_OBJECT

    void scanNetwork_addHost(QHostInfo host);


    QList <QHostInfo> addrs_devAll;
    QList <QHostInfo> addrs_devThis;


    QHostAddress searchedLast;

public:
    NetworkScan();

    void start();

    QList <QHostInfo> get_addrs_devAll();
    QList <QHostInfo> get_addrs_devThis();

private slots:
    void scanNetwork_printResults(QHostInfo host);


signals:
    void finished();

};

#endif // NETWORKSCAN_H
