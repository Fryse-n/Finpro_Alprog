#include "SocketClient.h"
#include "Menu.h"
#include <iostream>

using namespace std;

int main() {
    SocketClient client("127.0.0.1", 8080);
    Menu menu(client);
    menu.show();
    return 0;
}