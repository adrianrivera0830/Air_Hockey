// Created by Cuent on 2/8/2025.

#include "../Headers/PacketManager.h"
#include <iostream>

// PacketID GetPacketType(int id) {
//     switch (id) {
//         case 1: return PacketID::CONNECT;
//         case 2: return PacketID::ACK;
//         case 3: return PacketID::PING;
//         case 4: return PacketID::DISCONNECT;
//         case 5: return PacketID::START;
//         default:
//             std::cerr << " Error: ID de paquete inválido (" << id << ").\n";
//             return PacketID::DISCONNECT; // Devuelve un valor seguro por defecto
//     }
// }

PacketID GetType(int id) {
    switch (id) {
        case 1: return PacketID::CONNECT;
        case 2: return PacketID::ACK;
        case 3: return PacketID::PING;
        case 4: return PacketID::DISCONNECT;
        case 5: return PacketID::START;
        default:
            return PacketID::DISCONNECT; // Devuelve un valor seguro por defecto
    }
}

int PacketTypeToInt(PacketID type) {
    switch (type) {
        case PacketID::CONNECT: return 1;
        case PacketID::ACK: return 2;
        case PacketID::PING: return 3;
        case PacketID::DISCONNECT: return 4;
        case PacketID::START: return 5;
        default:
            return -1; // Valor inválido
    }
}


void WriteInt(Buffer &buffer, uint32_t data) {
    if (buffer.index + 4 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Write UInt32 OVERFLOW");
    }

    uint32_t data_network = htonl(data);
    std::memcpy(buffer.m_buffer + buffer.index, &data_network, 4);

    buffer.index += 4;
}

void WriteInt(Buffer &buffer, uint16_t data) {
    if (buffer.index + 2 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Write UInt16 OVERFLOW");
    }

    uint16_t data_network = htons(data);
    std::memcpy(buffer.m_buffer + buffer.index, &data_network, 2);

    buffer.index += 2;
}

void WriteInt(Buffer &buffer, uint8_t data) {
    if (buffer.index + 1 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Write UInt8 OVERFLOW");
    }

    buffer.m_buffer[buffer.index] = data;  // Copiar directamente
    buffer.index += 1;
}

void WriteInt(Buffer &buffer, int32_t data) {
    if (buffer.index + 4 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Write Int32 OVERFLOW");
    }

    uint32_t data_network = htonl(static_cast<uint32_t>(data));
    std::memcpy(buffer.m_buffer + buffer.index, &data_network, 4);

    buffer.index += 4;
}

void WriteInt(Buffer &buffer, int16_t data) {
    if (buffer.index + 2 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Write Int16 OVERFLOW");
    }

    uint16_t data_network = htons(static_cast<uint16_t>(data));
    std::memcpy(buffer.m_buffer + buffer.index, &data_network, 2);

    buffer.index += 2;
}

void WriteInt(Buffer &buffer, int8_t data) {
    if (buffer.index + 1 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Write Int8 OVERFLOW");
    }

    buffer.m_buffer[buffer.index] = static_cast<uint8_t>(data); // Copiar directamente
    buffer.index += 1;
}

void ReadInt(Buffer &buffer, uint32_t &out) {
    if (buffer.index + 4 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Read UInt32 OVERFLOW");
    }

    uint32_t data_network;
    std::memcpy(&data_network, buffer.m_buffer + buffer.index, 4);
    out = ntohl(data_network);

    buffer.index += 4;
}

void ReadInt(Buffer &buffer, uint16_t &out) {
    if (buffer.index + 2 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Read UInt16 OVERFLOW");
    }

    uint16_t data_network;
    std::memcpy(&data_network, buffer.m_buffer + buffer.index, 2);
    out = ntohs(data_network);

    buffer.index += 2;
}

void ReadInt(Buffer &buffer, uint8_t &out) {
    if (buffer.index + 1 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Read UInt8 OVERFLOW");
    }

    std::memcpy(&out, buffer.m_buffer + buffer.index, 1);
    buffer.index += 1;
}

void ReadInt(Buffer &buffer, int32_t &out) {
    if (buffer.index + 4 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Read Int32 OVERFLOW");
    }

    uint32_t data_network;
    std::memcpy(&data_network, buffer.m_buffer + buffer.index, 4);
    out = static_cast<int32_t>(ntohl(data_network));

    buffer.index += 4;
}

void ReadInt(Buffer &buffer, int16_t &out) {
    if (buffer.index + 2 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Read Int16 OVERFLOW");
    }

    uint16_t data_network;
    std::memcpy(&data_network, buffer.m_buffer + buffer.index, 2);
    out = static_cast<int16_t>(ntohs(data_network));

    buffer.index += 2;
}

void ReadInt(Buffer &buffer, int8_t &out) {
    if (buffer.index + 1 > buffer.m_size) {
        throw std::runtime_error("Buffer ERROR: Read Int8 OVERFLOW");
    }

    std::memcpy(&out, buffer.m_buffer + buffer.index, 1);
    buffer.index += 1;
}

void PacketHeader::WriteFromStructToBuffer(Buffer& buffer) {
    WriteInt(buffer, packet_id);
    WriteInt(buffer, packet_sequence);
    WriteInt(buffer, checksum);
    WriteInt(buffer, timestamp);
    WriteInt(buffer, ack_bitfield);
    WriteInt(buffer, payload_size);
}

void PacketHeader::ReadFromBufferToStruct(Buffer& buffer) {
    ReadInt(buffer, packet_id);
    ReadInt(buffer, packet_sequence);
    ReadInt(buffer, checksum);
    ReadInt(buffer, timestamp);
    ReadInt(buffer, ack_bitfield);
    ReadInt(buffer, payload_size);
}

void PacketHeader::Print() {
    std::cout << "PacketHeader:" << std::endl;
    std::cout << "  packet_id: " << packet_id << std::endl;
    std::cout << "  packet_sequence: " << packet_sequence << std::endl;
    std::cout << "  checksum: " << checksum << std::endl;
    std::cout << "  timestamp: " << timestamp << std::endl;
    std::cout << "  ack_bitfield: " << ack_bitfield << std::endl;
    std::cout << "  payload_size: " << payload_size << std::endl;
}

void PacketMove::WriteFromStructToBuffer(Buffer &buffer) {
    WriteInt(buffer,vector_2d.x);
    WriteInt(buffer,vector_2d.y);

}

void PacketMove::ReadFromBufferToStruct(Buffer &buffer) {
    ReadInt(buffer,vector_2d.x);
    ReadInt(buffer,vector_2d.y);

}


