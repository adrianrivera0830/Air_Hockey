//
// Created by Cuent on 2/7/2025.
//

#include "LobbyManager.h"
#include <iostream>
#include <string>
void LobbyManager::Host() {
    Peer peer;
    std::cout << "HOSTING\n";
    std::cout << "Esperando jugadores...\n";

    sockaddr from;
    socklen_t len = sizeof(from);
    char buffer[1024];
    while (true) {
        int bytesReceived = peer.ReceiveFrom(buffer,1024,&from,&len);
        if (bytesReceived > 0) {
            break;
        }
    }
    std::cout << "Listo";

}

void LobbyManager::Join() {
    std::cout << "Ingresa la direccion IP: ";

    std::string ip;
    std::cin >> ip;
    std::cout << "Ingresa el puerto: ";
    int puerto;
    std::cin >> puerto;

    Peer peer;

    char *buffer = "hola papus";
    sockaddr_in peerAddr;
    peerAddr.sin_port = htons(puerto);
    peerAddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip.c_str(),&peerAddr.sin_addr);

    socklen_t len = sizeof(peerAddr);

    peer.SendTo(buffer,strlen(buffer),(sockaddr *)&peerAddr,len);

    while (true) {

    }

}
