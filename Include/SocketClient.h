#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <string>

using namespace std;

class SocketClient {

private:
    int sockFd;

    string serverIP;
    int port;

public:

    SocketClient(string ip, int port);

    string sendRequest(string jsonPayload);
};

#endif