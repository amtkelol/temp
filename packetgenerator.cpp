#include "packetgenerator.h"

PacketGenerator::PacketGenerator()
{

}

void PacketGenerator::generatePacket()
{
    p.version = 0;
    p.checksum = 0xffff;
    size_t packet_length = sizeof(p.version) + sizeof(p.length) + sizeof(p.checksum);
    p.length = set_uint(packet_length, rand() % 255);
}

void PacketGenerator::serializePacket(QByteArray &arr)
{
    generatePacket();

    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream << p.version
           << p.length
           << p.checksum;
}

quint16 PacketGenerator::set_uint(quint8 lower, quint8 upper)
{
    uint16_t x = 0;
    x = (x & 0xff00) | lower;
    x = (x & 0x00ff) | (upper << 8);
    return x;
}

