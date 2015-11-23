#ifndef PACKETGENERATOR_H
#define PACKETGENERATOR_H
#include <QDataStream>

class PacketGenerator
{
public:
    PacketGenerator();
    void serializePacket(QByteArray &arr);
private:
#pragma pack(push, 1)
    struct packet {
        quint8 version;
        quint16 length;
        quint16 checksum;
        quint8 data[32];
    };
#pragma pack(pop)

    packet p;
    void generatePacket();
    quint16 set_uint(quint8 lower, quint8 upper);
};

#endif // PACKETGENERATOR_H
