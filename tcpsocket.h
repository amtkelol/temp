#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "packetgenerator.h"
#include <QtNetwork>


class TcpSocket : public QObject
{
    Q_OBJECT
public:
    TcpSocket();
    void sendDatagram();
public slots:
    void socketError();
    void socketConnected();
private:
    QTcpSocket *socket;
    PacketGenerator p_gen;
};

#endif // TCPSOCKET_H
