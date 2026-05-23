#pragma once
#include <string>
#include "SocketClient.h"

class Menu {
private:
    SocketClient& client;

    std::string buildGetAllRequest(const std::string& userId);
    std::string buildSearchRequest(const std::string& keyword);
    std::string buildBorrowRequest(const std::string& userId, const std::string& itemId);
    std::string buildReturnRequest(const std::string& userId, const std::string& itemId);

public:
    Menu(SocketClient& client);
    void show();
};