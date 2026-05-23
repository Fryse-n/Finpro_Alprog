#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu(SocketClient& client) : client(client) {}

string Menu::buildGetAllRequest(const string& userId) {
    return string("{\"action\":\"GET_ALL\",\"userId\":\"") + userId + "\"}";
}

string Menu::buildSearchRequest(const string& keyword) {
    return string("{\"action\":\"SEARCH_TITLE\",\"keyword\":\"") + keyword + "\"}";
}

string Menu::buildBorrowRequest(const string& userId, const string& itemId) {
    return string("{\"action\":\"BORROW\",\"userId\":\"") + userId + "\",\"itemId\":\"" + itemId + "\"}";
}

string Menu::buildReturnRequest(const string& userId, const string& itemId) {
    return string("{\"action\":\"RETURN\",\"userId\":\"") + userId + "\",\"itemId\":\"" + itemId + "\"}";
}

void Menu::show() {
    while (true) {
        cout << "\n=== MENU CLIENT ===\n";
        cout << "1. Lihat semua data\n";
        cout << "2. Cari judul\n";
        cout << "3. Pinjam buku\n";
        cout << "4. Kembalikan buku\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";

        int pilihan;
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 0) break;

        string request;

        if (pilihan == 1) {
            string userId;
            cout << "Masukkan userId: ";
            getline(cin, userId);
            request = buildGetAllRequest(userId);
        } else if (pilihan == 2) {
            string keyword;
            cout << "Masukkan keyword judul: ";
            getline(cin, keyword);
            request = buildSearchRequest(keyword);
        } else if (pilihan == 3) {
            string userId, itemId;
            cout << "Masukkan userId: ";
            getline(cin, userId);
            cout << "Masukkan itemId: ";
            getline(cin, itemId);
            request = buildBorrowRequest(userId, itemId);
        } else if (pilihan == 4) {
            string userId, itemId;
            cout << "Masukkan userId: ";
            getline(cin, userId);
            cout << "Masukkan itemId: ";
            getline(cin, itemId);
            request = buildReturnRequest(userId, itemId);
        } else {
            cout << "Pilihan tidak valid.\n";
            continue;
        }

        string response = client.sendRequest(request);
        cout << "\nResponse server:\n" << response << endl;
    }
}