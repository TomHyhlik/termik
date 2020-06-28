#include "protocol_udp.h"

#include "networkwparam.h"

#include <memory>

//////////////////////////////////////////////////
protocol_udp::protocol_udp()
{
}

//////////////////////////////////////////////////
bool protocol_udp::isOpen()
{
    return (udpSocket != nullptr);
}

//////////////////////////////////////////////////
bool protocol_udp::open()
{
    udpSocket = std::unique_ptr <QUdpSocket> (new QUdpSocket());

    bool binded = udpSocket->bind(NetworkWParam::get().IpAddr_Rx,
                           NetworkWParam::get().port_Rx);

    if (binded) {
        connect(udpSocket.get(), &QUdpSocket::readyRead,
                this, &protocol_udp::on_dataReceived);
        return true;
    } else {
        udpSocket = nullptr;
        return false;
    }
}

//////////////////////////////////////////////////
bool protocol_udp::write(QByteArray data)
{

    return udpSocket->writeDatagram(data, NetworkWParam::get().IpAddr_Tx,
                                   NetworkWParam::get().port_Tx);
}

//////////////////////////////////////////////////
void protocol_udp::close()
{
    udpSocket = nullptr;
}

//////////////////////////////////////////////////
void protocol_udp::on_dataReceived()
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;

    buffer.resize(int(udpSocket->pendingDatagramSize()));
    udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
//    qDebug() << "_____________________________________";
//    qDebug() << "sender: " << sender;
//    qDebug() << "sender port: " << senderPort;
//    qDebug() << "message: " << buffer;
    emit received(buffer);
}

//////////////////////////////////////////////////
