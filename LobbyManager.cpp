//
// Created by Cuent on 2/7/2025.
//

#include "LobbyManager.h"
#include <iostream>
#include <string>
#include <vector>
#include "NetworkManager.h"
#include "Peer.h"

void LobbyManager::Host() {
    Peer peer;
    //SetPlayer(peer);

    std::cout << "HOSTING\n";
    std::cout << "Esperando jugadores...\n";

    sockaddr_in from;
    socklen_t len = sizeof(from);
    char buffer[1024];
    while (true) {
        int bytesReceived = peer.ReceiveFrom(buffer, 1024, (sockaddr *) &from, &len);
        if (bytesReceived > 0) {
            break;
        }
    }
    std::cout << "Se recibio un mensaje!\n";

    char *bufferToSend = "hola papus";

    // Enviar mensaje al primer cliente recibido
    int sendResult = peer.SendTo(bufferToSend, strlen(bufferToSend), (sockaddr *) &from, len);
    if (sendResult == -1) {
        perror("Error en sendto");
    }

    while (true) {
        int confirmBytes = peer.ReceiveFrom(buffer, 1024, (sockaddr *) &from, &len);
        if (confirmBytes > 0) {
            std::cout << "Confirmación recibida: " << buffer << "\n";
            break;
        }
    }

    std::cout << "Conexión establecida correctamente!\n";


}

void LobbyManager::Join() {
    std::cout << "Ingresa la dirección IP: ";
    std::string ip;
    std::cin >> ip;

    std::cout << "Ingresa el puerto: ";
    int puerto;
    std::cin >> puerto;

    Peer peer;

    char buffer[] = "hola papus";
    sockaddr_in peerAddr;
    peerAddr.sin_port = htons(puerto);
    peerAddr.sin_family = AF_INET;

    if (inet_pton(AF_INET, ip.c_str(), &peerAddr.sin_addr) <= 0) {
        std::cerr << "Error: Dirección IP inválida\n";
        return;
    }
    socklen_t len = sizeof(peerAddr);

    // Enviar primer mensaje al host
    int bytes_sent = peer.SendTo(buffer, strlen(buffer), (sockaddr *) &peerAddr, len);
    if (bytes_sent == -1) {
        perror("Error en sendto");
    }

    sockaddr_in from;
    socklen_t fromLen = sizeof(from);
    char bufferFrom[1024];

    // Esperar respuesta del host
    while (true) {
        int bytesReceived = peer.ReceiveFrom(bufferFrom, 1024, (sockaddr *) &from, &fromLen);
        if (bytesReceived > 0) {
            bufferFrom[bytesReceived] = '\0'; // Asegurar terminación de string
            std::cout << "Mensaje recibido del host: " << bufferFrom << "\n";
            break;
        }
    }

    // Enviar confirmación de conexión al host
    char confirmMessage[] = "confirmado";
    int confirmSent = peer.SendTo(confirmMessage, strlen(confirmMessage), (sockaddr *) &from, fromLen);
    if (confirmSent == -1) {
        perror("Error en sendto (confirmación)");
    }

    std::cout << "Conexión establecida con éxito!\n";
}
