#include "packetgenerator.h"

PacketGenerator::PacketGenerator()
{

}

void PacketGenerator::generatePacket()
{
    p.version = 0;

    for (quint8 &d : p.data) {
        d = rand() % 255;
    }

    size_t data_length = sizeof(p.data) / sizeof(quint8);
    quint8 checksum = std::accumulate(p.data, p.data + data_length, 0) % 0xffff;
    if (data_length % 2) {
        p.checksum = set_uint(0, checksum);
    } else {
        p.checksum = set_uint(1, checksum);
    }

    size_t packet_length = sizeof(p.version) + sizeof(p.length) + sizeof(p.checksum) + sizeof(p.data);
    p.length = set_uint(packet_length, rand() % 255);
}

void PacketGenerator::serializePacket(QByteArray &arr)
{
    generatePacket();

    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream << p.version
           << p.length
           << p.checksum;

    for (const quint8 &d : p.data) {
        stream << d;
    }
}

quint16 PacketGenerator::set_uint(quint8 lower, quint8 upper)
{
    uint16_t x = 0;
    x = (x & 0xff00) | lower;
    x = (x & 0x00ff) | (upper << 8);
    return x;
}

