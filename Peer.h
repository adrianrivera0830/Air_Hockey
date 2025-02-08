//
// Created by Cuent on 2/7/2025.
//

#ifndef PEER_H
#define PEER_H
#include "NetworkHeaders.h"

class Peer {
public:
    bool Initialize();
    bool Bind();
    bool CloseSocket();
    int SendTo(char *buffer, int bufferLen, sockaddr *to, socklen_t toLen);
    int ReceiveFrom(char *buffer, int bufferLen, sockaddr *from, socklen_t *fromLen);
    ~Peer();

private:
    SOCKET m_socket = -1;
};



#endif //PEER_H
