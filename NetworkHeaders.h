//
// Created by Cuent on 1/30/2025.
//

#ifndef NETWORKHEADERS_H
#define NETWORKHEADERS_H

#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <errno.h>
#endif

#include <iostream>
#include <cstring>

#if defined(_WIN32)
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())
typedef int socklen_t;
#define WOULD_BLOCK WSAEWOULDBLOCK
#else
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)
#define SOCKET_ERROR -1
#define WOULD_BLOCK EWOULDBLOCK
#endif

/**
 * @brief Configura un socket en modo no bloqueante.
 * @param socket El socket a modificar.
 * @return `true` si la operación fue exitosa, `false` en caso de error.
 */
inline bool setSocketNonBlocking(SOCKET socket) {
#if defined(_WIN32)
    u_long mode = 1;
    return ioctlsocket(socket, FIONBIO, &mode) == 0;
#else
    int flags = fcntl(socket, F_GETFL, 0);
    if (flags == -1) {
        return false;
    }
    return fcntl(socket, F_SETFL, flags | O_NONBLOCK) != -1;
#endif
}

#endif // NETWORKHEADERS_H
