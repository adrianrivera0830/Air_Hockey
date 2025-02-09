//
// Created by Cuent on 2/8/2025.
//

#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H
#include <cstdint>
#include <cstdlib>  // Para exit()
#include <iostream>
#include "NetworkHeaders.h"

enum class PacketID {
    CONNECT = 1,
    ACK = 2,
    PING = 3,
    DISCONNECT = 4,
    START = 5
};


PacketID GetType(int id);

int PacketTypeToInt(PacketID tpye);
struct Buffer {
    uint8_t *m_buffer;
    int index;
    int m_size;

    Buffer(int size) : m_size(size), index(0) {
        m_buffer = new uint8_t[size]();
    }

    ~Buffer() {
        delete[] m_buffer;
    }

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

};

void WriteInt(Buffer& buffer, uint32_t data);
void WriteInt(Buffer& buffer, uint16_t data);
void WriteInt(Buffer& buffer, uint8_t data);
void WriteInt(Buffer& buffer, int32_t data);
void WriteInt(Buffer& buffer, int16_t data);
void WriteInt(Buffer& buffer, int8_t data);

void ReadInt(Buffer& buffer, uint32_t& out);
void ReadInt(Buffer& buffer, uint16_t& out);
void ReadInt(Buffer& buffer, uint8_t& out);
void ReadInt(Buffer& buffer, int32_t& out);
void ReadInt(Buffer& buffer, int16_t& out);
void ReadInt(Buffer& buffer, int8_t& out);

struct PacketHeader {
    uint16_t packet_id;
    uint16_t packet_sequence;
    uint16_t checksum;
    uint16_t timestamp;
    uint32_t ack_bitfield;
    uint16_t payload_size;

    void WriteFromStructToBuffer(Buffer &buffer);
    void ReadFromBufferToStruct(Buffer &buffer);

    void Print();
};

PacketHeader GetPacketHeader(
    uint8_t packet_id,
    uint16_t packet_sequence,
    uint16_t checksum,
    uint16_t timestamp,
    uint32_t ack_bitfield,
    uint16_t payload_size);


struct PacketStart {
    void WriteFromStructToBuffer();
    void ReadFromBufferToStruct();
};




#endif //PACKETMANAGER_H
