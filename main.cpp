#include "tcpsocket.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TcpSocket s;
    s.sendDatagram();

    return a.exec();
}

