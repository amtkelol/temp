#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "packetgenerator.h"
#include <QtNetwork>

class TcpSocket : public QObject
{
    Q_OBJECT
public:
    TcpSocket();
    void connectSocket(const QString &adress, quint16 port);
    void disconnectSocket();
private slots:
    void socketError();
    void socketConnected();
    void socketBytesWritten(qint64 bytes);
signals:
    void bytesWrittenSignal(qint64 bytes);
    void socketStateSignal(QAbstractSocket::SocketState);
    void socketErrorSignal(QString err);
private:
    QTcpSocket *socket;
    PacketGenerator p_gen;
    QTimer *timer;
    void sendDatagram();
};

#endif // TCPSOCKET_H
