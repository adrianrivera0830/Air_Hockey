//
// Created by Cuent on 2/8/2025.
//

#include "NetworkManager.h"
sockaddr_in rival;
Peer myPlayer;
void SetRival(sockaddr_in player) {
    rival = player;
}

void SetPlayer(Peer peer) {
    myPlayer = peer;
}
