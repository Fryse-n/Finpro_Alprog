#include "SocketClient.h"
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

SocketClient::SocketClient(string ip, int port)
    : sockFd(-1), serverIP(ip), port(port) {}

string SocketClient::sendRequest(string jsonPayload) {
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        return "{\"status\":\"ERROR\",\"message\":\"Gagal membuat socket\"}";
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, serverIP.c_str(), &addr.sin_addr) <= 0) {
        close(sockFd);
        return "{\"status\":\"ERROR\",\"message\":\"IP server tidak valid\"}";
    }

    if (connect(sockFd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sockFd);
        return "{\"status\":\"ERROR\",\"message\":\"Gagal connect ke server\"}";
    }

    send(sockFd, jsonPayload.c_str(), jsonPayload.size(), 0);

    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    int bytesRead = read(sockFd, buffer, sizeof(buffer) - 1);
    close(sockFd);

    if (bytesRead <= 0) {
        return "{\"status\":\"ERROR\",\"message\":\"Tidak ada response dari server\"}";
    }

    return string(buffer);
}