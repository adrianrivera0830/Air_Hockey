//
// Created by Cuent on 2/7/2025.
//

#include "Peer.h"

Peer::Peer() {
    if (!Initialize()) return;
    Bind();
}

bool Peer::Initialize() {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Error en WSAStartup: " << WSAGetLastError() << std::endl;
        return false;
    }
#endif
    m_socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

    if (!ISVALIDSOCKET(m_socket)) {
        std::cerr << "Error al crear el socket: " << GETSOCKETERRNO() << std::endl;
        return false;
    }

    if (!setSocketNonBlocking(m_socket)) {
        std::cerr << "Error al setear el socket a no bloqueante: " << GETSOCKETERRNO() << std::endl;
        return false;
    }

    return true;
}

bool Peer::Bind() {
    if (!ISVALIDSOCKET(m_socket)) return false;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(0); // Puerto aleatorio

    if (bind(m_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Error al bindear el socket: " << GETSOCKETERRNO() << std::endl;
        return false;
    }

    addrinfo hints, *addrList;
    memset(&hints, 0, sizeof(hints));  // Limpia la estructura antes de usarla

    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_DGRAM;

    char localHostname[NI_MAXHOST];

    if (gethostname(localHostname, sizeof(localHostname)) == SOCKET_ERROR) {
        std::cerr << "Error al obtener el nombre del host: " << GETSOCKETERRNO() << std::endl;
        return false;
    }

    if (getaddrinfo(localHostname, nullptr, &hints, &addrList) != 0) {
        std::cerr << "Error en getaddrinfo: " << GETSOCKETERRNO() << std::endl;
        return false;
    }

    if (!addrList) {
        std::cerr << "getaddrinfo no devolvió direcciones IP\n";
        return false;
    }

    for (addrinfo *currentAddr = addrList; currentAddr != nullptr; currentAddr = currentAddr->ai_next) {
        sockaddr_in *ipAddress = reinterpret_cast<sockaddr_in *>(currentAddr->ai_addr);
        char ipStr[INET_ADDRSTRLEN];

        if (inet_ntop(AF_INET, &ipAddress->sin_addr, ipStr, sizeof(ipStr)) == nullptr) {
            std::cerr << "Error al convertir la dirección IP\n";
            continue; // Saltar esta dirección si hay un problema
        }

        std::cout << ipStr << "\n";
    }

    sockaddr_in boundedAddress;
    socklen_t boundedLen = sizeof(boundedAddress);
    if (getsockname(m_socket, reinterpret_cast<sockaddr *>(&boundedAddress), &boundedLen)) return false;
    std::cout << "Puerto privado: " << ntohs(boundedAddress.sin_port) << "\n\n";

    freeaddrinfo(addrList); // Liberar memoria de `getaddrinfo`
    return true;
}

bool Peer::CloseSocket() {
    return true;
}

int Peer::SendTo(char *buffer, int bufferLen, sockaddr *to, socklen_t toLen) {
    int bytes_sent = sendto(m_socket, buffer, bufferLen, 0, to, toLen);

    return bytes_sent;
}

int Peer::ReceiveFrom(char *buffer, int bufferLen, sockaddr *from, socklen_t *fromLen) {
    int bytes_received = recvfrom(m_socket,  buffer, bufferLen, 0, from, fromLen);


    if (bytes_received > 0 && bytes_received < bufferLen) {
        buffer[bytes_received] = '\0';
    }

    return bytes_received;
}

bool Peer::IsSocketValid() {
    return ISVALIDSOCKET(m_socket);
}

Peer::~Peer() {
    CLOSESOCKET(m_socket);
#ifdef _WIN32
    WSACleanup();
#endif
}
