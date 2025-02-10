//
// Created by Cuent on 2/9/2025.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include "Game.h"
#include "Peer.h"


class NetworkManager {
public:
    void Host();
    void Join(std::string address, int port);
    void CommunicationLoop();

private:
    Game* game = nullptr;
    sockaddr_in rival;
    Peer m_peer;
};



#endif //NETWORKMANAGER_H
