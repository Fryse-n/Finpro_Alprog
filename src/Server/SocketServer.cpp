#include "SocketServer.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

SocketServer::SocketServer(LibraryManager& manager, int port)
    : serverFd(-1), port(port), manager(manager) {}

void SocketServer::start() {
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd < 0) {
        cout << "Gagal membuat socket server\n";
        return;
    }

    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(serverFd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        cout << "Gagal bind port\n";
        close(serverFd);
        return;
    }

    if (listen(serverFd, 5) < 0) {
        cout << "Gagal listen\n";
        close(serverFd);
        return;
    }

    cout << "Server berjalan di port " << port << endl;

    while (true) {
        int clientFd = accept(serverFd, nullptr, nullptr);
        if (clientFd < 0) {
            cout << "Gagal accept client\n";
            continue;
        }
        handleClient(clientFd);
    }
}

void SocketServer::handleClient(int clientFd) {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    int bytesRead = read(clientFd, buffer, sizeof(buffer) - 1);
    if (bytesRead <= 0) {
        close(clientFd);
        return;
    }

    string request(buffer);
    string response = processRequest(request);

    send(clientFd, response.c_str(), response.size(), 0);
    close(clientFd);
}

string SocketServer::processRequest(string jsonRequest) {
    string action = JSONParser::getValue(jsonRequest, "action");

    if (action == "GET_ALL") return manager.handleGetAll();
    if (action == "SEARCH_TITLE") return manager.handleSearch(jsonRequest);
    if (action == "BORROW") return manager.handleBorrow(jsonRequest);
    if (action == "RETURN") return manager.handleReturn(jsonRequest);

    return JSONParser::error("Unknown action");
}