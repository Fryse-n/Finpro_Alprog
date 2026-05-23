#pragma once
#include <string>

class SocketClient {
private:
    int sockFd;
    std::string serverIP;
    int port;

public:
    SocketClient(std::string ip, int port);

    std::string sendRequest(std::string jsonPayload);
};