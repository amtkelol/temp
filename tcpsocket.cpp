#include "tcpsocket.h"

TcpSocket::TcpSocket()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("google.com", 80);

    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()));
}

void TcpSocket::sendDatagram()
{
    QByteArray data;
    p_gen.serializePacket(data);

    while (true) {
        qint64 b = socket->write(data);
        qDebug() << "Bytes written:" << b;

        if(!socket->waitForBytesWritten(5000)) {
           break;
        }
    }
}

void TcpSocket::socketConnected()
{
    qDebug() << "connected";
    sendDatagram();
}

void TcpSocket::socketError()
{
    qDebug() << socket->errorString();
}
