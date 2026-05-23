#include "SocketClient.h"
#include "Menu.h"
#include <iostream>

using namespace std;

int main() {
    SocketClient client("//ttlbo-180-252-147-167.run.pinggy-free.link", 42835);
    Menu menu(client);
    menu.show();
    return 0;
}