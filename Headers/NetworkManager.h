//
// Created by Cuent on 2/9/2025.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include "Peer.h"


class NetworkManager {
public:
    void Host();
    void Join(std::string address, int port);


private:
    sockaddr_in rival;

    Peer m_peer;
};



#endif //NETWORKMANAGER_H
