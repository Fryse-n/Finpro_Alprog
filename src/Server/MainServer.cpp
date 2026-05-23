#include "SocketServer.h"
#include "Book.h"
#include "Journal.h"
#include <iostream>

using namespace std;

int main() {
    LibraryManager manager;

    // Data awal contoh
    manager.addBook(new Book("B001", "Algoritma dan Struktur Data",
                             "Rinaldi Munir", "978-602-xxx", 2020, 3));

    manager.addBook(new Book("B002", "Pemrograman C++",
                             "Budi Santoso", "978-123-abc", 2021, 2));

    manager.addJournal(new Journal("J001", "IEEE Transactions on Computing",
                                   "IEEE", "0018-9340", 2024, 72, 4));

    SocketServer server(manager, 8080);
    server.start();

    return 0;
}