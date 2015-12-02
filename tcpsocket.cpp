#include "tcpsocket.h"

TcpSocket::TcpSocket()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("google.com", 80);

    timer = new QTimer(this);
    timer->setInterval(5000);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &TcpSocket::sendDatagram);

    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(socketBytesWritten(qint64)));
    connect(socket, &QTcpSocket::stateChanged, this, [this]() {
        emit socketStateSignal(socket->state());
    });
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
    if (timer->isActive()) {
        timer->stop();
    }
}

void TcpSocket::socketBytesWritten(qint64 bytes)
{
    qDebug() << "bytes written:" << bytes;
    emit bytesWrittenSignal(bytes);
    timer->start();
}
