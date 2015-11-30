#include "tcpsocket.h"

TcpSocket::TcpSocket()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("google.com", 80);

    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void TcpSocket::sendDatagram()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "sending data";
        QByteArray data;
        p_gen.serializePacket(data);
        socket->write(data);
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

void TcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << "bytes written:" << bytes;
    QTimer::singleShot(5000, this, [this]() { sendDatagram(); });
}
