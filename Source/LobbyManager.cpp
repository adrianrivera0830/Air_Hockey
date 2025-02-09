// Created by Cuent on 2/7/2025.
//

#include "../Headers/LobbyManager.h"
#include <iostream>
#include <string>
#include <vector>
#include "../Headers/Peer.h"
#include <cstdlib> // Para exit()
#include "../Headers/PacketManager.h"

void LobbyManager::Host() {

    Peer peer;


    //SetPlayer(peer);

    std::cout << "HOSTING\n";
    std::cout << "Esperando jugadores...\n";

    sockaddr_in from;
    socklen_t len = sizeof(from);
    Buffer buffer(1024);
    while (true) {
        int bytesReceived = peer.ReceiveFrom((char *)buffer.m_buffer, 1024, (sockaddr *) &from, &len);
        if (bytesReceived > 0) {
            break;
        }
    }

    //GetPacketID(buffer);

    PacketHeader header;

    header.ReadFromBufferToStruct(buffer);

    while (true) {

    }

    // int sendResult = peer.SendTo((char *)buffer.m_buffer,buffer.m_size, (sockaddr *) &from, len);
    //
    // char *bufferToSend = "hola papus";
    //
    // // Enviar mensaje al primer cliente recibido
    // int sendResult = peer.SendTo(bufferToSend, strlen(bufferToSend), (sockaddr *) &from, len);
    //
    // while (true) {
    //     int confirmBytes = peer.ReceiveFrom(buffer, 1024, (sockaddr *) &from, &len);
    //     if (confirmBytes > 0) {
    //         std::cout << "Confirmacion recibida: " << buffer << "\n";
    //         break;
    //     }
    // }
    //
    // std::cout << "Conexion establecida correctamente!\n";
}

void LobbyManager::Join() {
    std::cout << "Ingresa la direccion IP: ";
    std::string ip;
    std::cin >> ip;

    std::cout << "Ingresa el puerto: ";
    int puerto;
    std::cin >> puerto;

    Peer peer;


    sockaddr_in peerAddr;
    peerAddr.sin_port = htons(puerto);
    peerAddr.sin_family = AF_INET;

    if (inet_pton(AF_INET, ip.c_str(), &peerAddr.sin_addr) <= 0) {
        std::cerr << "Error: Direccion IP invalida\n";
        exit(EXIT_FAILURE); // Termina el programa con un codigo de error
    }
    socklen_t len = sizeof(peerAddr);

    PacketHeader header = GetPacketHeader(10,2,3,4,5,1);
    Buffer buffer(1024);

    header.WriteFromStructToBuffer(buffer);


    int bytes_sent = peer.SendTo((char *) buffer.m_buffer, buffer.m_size, (sockaddr *) &peerAddr, len);
    while (true) {

}
    // // Enviar primer mensaje al host
    // int bytes_sent = peer.SendTo(buffer, strlen(buffer), (sockaddr *) &peerAddr, len);
    //
    // sockaddr_in from;
    // socklen_t fromLen = sizeof(from);
    // char bufferFrom[1024];
    //
    // // Esperar respuesta del host
    // while (true) {
    //     int bytesReceived = peer.ReceiveFrom(bufferFrom, 1024, (sockaddr *) &from, &fromLen);
    //     if (bytesReceived > 0) {
    //         bufferFrom[bytesReceived] = '\0'; // Asegurar terminacion de string
    //         std::cout << "Mensaje recibido del host: " << bufferFrom << "\n";
    //         break;
    //     }
    // }
    //
    // // Enviar confirmacion de conexion al host
    // char confirmMessage[] = "confirmado";
    // int confirmSent = peer.SendTo(confirmMessage, strlen(confirmMessage), (sockaddr *) &from, fromLen);
    //
    // std::cout << "Conexion establecida con exito!\n";
}
