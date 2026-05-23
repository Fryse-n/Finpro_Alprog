#pragma once
#include <bits/stdc++.h>
#include "LibraryManager.h"
#include "SocketServer.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class SocketServer {
private:
    int serverFd;
    int port;
    LibraryManager& manager;

public:
    SocketServer(LibraryManager& manager, int port);

    void start();

private:
    void handleClient(int clientFd);
    std::string processRequest(std::string jsonRequest);
};