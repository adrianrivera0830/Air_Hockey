//
// Created by Cuent on 2/9/2025.
//

#include "../Headers/NetworkManager.h"
#include "../Headers/NetworkHeaders.h"
#include "../Headers/PacketManager.h"
#include <chrono>
#include <thread>


void NetworkManager::Host() {
    sockaddr_in from;
    socklen_t len = sizeof(from);
    Buffer buffer(1024);
    while (true) {
        int bytesReceived = m_peer.ReceiveFrom((char *)buffer.m_buffer, 1024, (sockaddr *) &from, &len);
        if (bytesReceived > 0) {
            PacketHeader header;
            header.ReadFromBufferToStruct(buffer);

            if (GetType(header.packet_id) == PacketID::CONNECT) {
                break;
            }
        }
    }
    std::cout << "Se unio un jugador!\n";
    rival = from;

    int opcion = 0;
    while (opcion != 1) {
        std::cout << "Ingresa (1) para empezar el juego\n";
        std::cin >> opcion;
    }

    PacketHeader sendHeader;
    sendHeader.packet_id = PacketTypeToInt(PacketID::START);

    Buffer sendBuffer(1024);
    sendHeader.WriteFromStructToBuffer(sendBuffer);



    auto startTime = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(1)) {
        m_peer.SendTo((char *)sendBuffer.m_buffer, sendBuffer.m_size, (sockaddr *)&from, len);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pequeña pausa para no saturar la red
    }

    std::cout << "JUEGO INICIADO!\n";

    game = new Game();
    std::thread newThread([this]() {
    this->CommunicationLoop();
});
newThread.detach();
    game->Initialize();

    game->GameLoop();



}

void NetworkManager::Join(std::string address,int port) {
    sockaddr_in peerAddr;
    peerAddr.sin_port = htons(port);
    peerAddr.sin_family = AF_INET;

    if (inet_pton(AF_INET, address.c_str(), &peerAddr.sin_addr) <= 0) {
        std::cerr << "Error: Direccion IP invalida\n";
        exit(EXIT_FAILURE); // Termina el programa con un codigo de error
    }
    socklen_t len = sizeof(peerAddr);

    PacketHeader header;
    header.packet_id = PacketTypeToInt(PacketID::CONNECT);
    Buffer buffer(1024);

    header.WriteFromStructToBuffer(buffer);

    m_peer.SendTo((char *)buffer.m_buffer,buffer.m_size,(sockaddr *)&peerAddr,len);


    Buffer receiveBuffer(1024);
    sockaddr_in from;
    while (true) {
        int bytesReceived = m_peer.ReceiveFrom((char *)receiveBuffer.m_buffer, receiveBuffer.m_size, (sockaddr *) &from, &len);
        if (bytesReceived > 0) {
            PacketHeader receiveHeader;
            receiveHeader.ReadFromBufferToStruct(receiveBuffer);


            if (GetType(receiveHeader.packet_id) == PacketID::START) {
                break;

            }

        }
    }

    std::cout << "JUEGO INICIADO!\n";
    rival = from;

    // CommunicationLoop();

}

void NetworkManager::CommunicationLoop() {
    //Game game;
    while (true) {
        //std::cout << "gol" << std::endl;
        if (game != nullptr && game->pusher != nullptr) { // ✅ Verifica que pusher también esté inicializado
            std::cout << game->pusher->GetX() << std::endl;
        }
    }
    // while (true) {
    //     PacketHeader moveHeader;
    //     moveHeader.packet_id = 6;
    //     PacketMove packet_move;
    //     packet_move.vector_2d.x = 0;
    //
    //     packet_move.vector_2d.y = 0;
    //
    //     moveHeader.payload_size = sizeof(packet_move);
    //     Buffer send_buffer(1024);
    //
    //     moveHeader.WriteFromStructToBuffer(send_buffer);
    //     packet_move.WriteFromStructToBuffer(send_buffer);
    //
    //     int bytes_sent = m_peer.SendTo((char *)send_buffer.m_buffer,send_buffer.m_size,(sockaddr *)&rival,sizeof(rival));
    //     sockaddr from;
    //     socklen_t fromLen = sizeof(from);
    //     Buffer receive_buffer(1024);
    //     int bytesReceived = m_peer.ReceiveFrom((char *)receive_buffer.m_buffer, receive_buffer.m_size, &from, &fromLen);
    //
    //     if (bytesReceived > 0) {
    //         PacketHeader receiveHeader;
    //         receiveHeader.ReadFromBufferToStruct(receive_buffer);
    //         std::cout << receiveHeader.packet_id << std::endl;
    //
    //
    //         if (receiveHeader.packet_id == 6) {
    //             PacketMove receiveMOVE;
    //             receiveMOVE.ReadFromBufferToStruct(receive_buffer);
    //
    //         }
    //
    //     }
    // }
}
