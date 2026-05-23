#include "SocketClient.h"

#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

SocketClient::SocketClient(string ip, int port)
    : serverIP(ip), port(port), sockFd(-1) {}

string SocketClient::sendRequest(string jsonPayload) {

    // 1. Buat socket
    sockFd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockFd < 0) {
        return "{\"status\":\"ERROR\",\"message\":\"Socket gagal dibuat\"}";
    }

    // 2. Resolve hostname Pinggy
    struct addrinfo hints {};
    struct addrinfo* result = nullptr;

    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    string portStr = to_string(port);

    int status = getaddrinfo(
        serverIP.c_str(),
        portStr.c_str(),
        &hints,
        &result
    );

    if (status != 0) {
        close(sockFd);
        return "{\"status\":\"ERROR\",\"message\":\"Host tidak ditemukan\"}";
    }

    // 3. Connect ke Pinggy
    if (connect(sockFd, result->ai_addr, result->ai_addrlen) < 0) {

        freeaddrinfo(result);
        close(sockFd);

        return "{\"status\":\"ERROR\",\"message\":\"Connect gagal\"}";
    }

    freeaddrinfo(result);

    // 4. Kirim JSON
    send(
        sockFd,
        jsonPayload.c_str(),
        jsonPayload.size(),
        0
    );

    // 5. Terima response
    char buffer[4096] = {0};

    read(
        sockFd,
        buffer,
        sizeof(buffer)
    );

    // 6. Tutup socket
    close(sockFd);

    return string(buffer);
}