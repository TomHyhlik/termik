#ifndef NETWORKWPARAM_H
#define NETWORKWPARAM_H

#include <QNetworkInterface>



class NetworkWParam
{
    NetworkWParam(){}

    static NetworkWParam s_Instance;

public:
    NetworkWParam(const NetworkWParam&) = delete;
    static NetworkWParam& get() { return s_Instance; }

    /* the data */
    QHostAddress IpAddr_Tx;
    QHostAddress IpAddr_Rx;
    quint16 port_Tx;
    quint16 port_Rx;
    int protocolType;

};



#endif // NETWORKWPARAM_H
