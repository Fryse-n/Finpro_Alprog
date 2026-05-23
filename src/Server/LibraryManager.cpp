#include "LibraryManager.h"
#include <sstream>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;

static string escapeJson(const string& s) {
    string out;
    for (char c : s) {
        if (c == '\\') out += "\\\\";
        else if (c == '"') out += "\\\"";
        else if (c == '\n') out += "\\n";
        else if (c == '\r') {}
        else out += c;
    }
    return out;
}

void LibraryManager::addBook(Book* b) {
    catalog.pushBack(b);
}

void LibraryManager::addJournal(Journal* j) {
    catalog.pushBack(j);
}

vector<LibraryItem*> LibraryManager::mergeSort(vector<LibraryItem*> arr, string sortBy) {
    if (arr.size() <= 1) return arr;

    int mid = arr.size() / 2;
    vector<LibraryItem*> left(arr.begin(), arr.begin() + mid);
    vector<LibraryItem*> right(arr.begin() + mid, arr.end());

    left = mergeSort(left, sortBy);
    right = mergeSort(right, sortBy);

    return merge(left, right, sortBy);
}

vector<LibraryItem*> LibraryManager::merge(vector<LibraryItem*>& L,
                                           vector<LibraryItem*>& R,
                                           string sortBy) {
    vector<LibraryItem*> result;
    int i = 0, j = 0;

    while (i < (int)L.size() && j < (int)R.size()) {
        bool leftFirst = false;

        if (sortBy == "title") {
            leftFirst = L[i]->getTitle() <= R[j]->getTitle();
        } else {
            leftFirst = L[i]->getTahun() <= R[j]->getTahun();
        }

        if (leftFirst) result.push_back(L[i++]);
        else result.push_back(R[j++]);
    }

    while (i < (int)L.size()) result.push_back(L[i++]);
    while (j < (int)R.size()) result.push_back(R[j++]);

    return result;
}

vector<Book*> LibraryManager::mergeSortBooksByISBN(vector<Book*> arr) {
    if (arr.size() <= 1) return arr;

    int mid = arr.size() / 2;
    vector<Book*> left(arr.begin(), arr.begin() + mid);
    vector<Book*> right(arr.begin() + mid, arr.end());

    left = mergeSortBooksByISBN(left);
    right = mergeSortBooksByISBN(right);

    return mergeBooksByISBN(left, right);
}

vector<Book*> LibraryManager::mergeBooksByISBN(vector<Book*>& L,
                                               vector<Book*>& R) {
    vector<Book*> result;
    int i = 0, j = 0;

    while (i < (int)L.size() && j < (int)R.size()) {
        if (L[i]->getISBN() <= R[j]->getISBN()) result.push_back(L[i++]);
        else result.push_back(R[j++]);
    }

    while (i < (int)L.size()) result.push_back(L[i++]);
    while (j < (int)R.size()) result.push_back(R[j++]);

    return result;
}

Book* LibraryManager::binarySearchBookByISBN(vector<Book*>& arr, string isbn) {
    int lo = 0;
    int hi = (int)arr.size() - 1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (arr[mid]->getISBN() == isbn) return arr[mid];
        if (arr[mid]->getISBN() < isbn) lo = mid + 1;
        else hi = mid - 1;
    }

    return nullptr;
}

vector<LibraryItem*> LibraryManager::linearSearchByTitle(string keyword) {
    vector<LibraryItem*> hasil;
    Node<LibraryItem>* curr = catalog.getHead();

    while (curr) {
        if (curr->data->getTitle().find(keyword) != string::npos) {
            hasil.push_back(curr->data);
        }
        curr = curr->next;
    }

    return hasil;
}

LibraryItem* LibraryManager::findItemById(string itemId) {
    Node<LibraryItem>* curr = catalog.getHead();
    while (curr) {
        if (curr->data->getId() == itemId) return curr->data;
        curr = curr->next;
    }
    return nullptr;
}

BorrowRecord* LibraryManager::findBorrowRecord(string userId, string itemId) {
    Node<BorrowRecord>* curr = records.getHead();
    while (curr) {
        if (curr->data->getUserId() == userId &&
            curr->data->getItemId() == itemId &&
            !curr->data->isReturned()) {
            return curr->data;
        }
        curr = curr->next;
    }
    return nullptr;
}

string LibraryManager::itemToJson(LibraryItem* item) {
    ostringstream oss;

    if (item->getType() == "BOOK") {
        Book* b = dynamic_cast<Book*>(item);
        oss << "{"
            << "\"id\":\"" << escapeJson(b->getId()) << "\","
            << "\"type\":\"BOOK\","
            << "\"title\":\"" << escapeJson(b->getTitle()) << "\","
            << "\"pengarang\":\"" << escapeJson(b->getPengarang()) << "\","
            << "\"isbn\":\"" << escapeJson(b->getISBN()) << "\","
            << "\"tahun\":" << b->getTahun() << ","
            << "\"stok\":" << b->getStok()
            << "}";
    } else if (item->getType() == "JOURNAL") {
        Journal* j = dynamic_cast<Journal*>(item);
        oss << "{"
            << "\"id\":\"" << escapeJson(j->getId()) << "\","
            << "\"type\":\"JOURNAL\","
            << "\"title\":\"" << escapeJson(j->getTitle()) << "\","
            << "\"penerbit\":\"" << escapeJson(j->getPenerbit()) << "\","
            << "\"issn\":\"" << escapeJson(j->getISSN()) << "\","
            << "\"tahun\":" << j->getTahun() << ","
            << "\"volume\":" << j->getVolume() << ","
            << "\"edisi\":" << j->getEdisi()
            << "}";
    } else {
        oss << "{\"id\":\"" << escapeJson(item->getId()) << "\","
            << "\"type\":\"UNKNOWN\","
            << "\"title\":\"" << escapeJson(item->getTitle()) << "\","
            << "\"tahun\":" << item->getTahun()
            << "}";
    }

    return oss.str();
}

string LibraryManager::getCurrentDate() {
    time_t now = time(nullptr);
    tm* local = localtime(&now);

    ostringstream oss;
    oss << (local->tm_year + 1900) << "-";
    if (local->tm_mon + 1 < 10) oss << "0";
    oss << (local->tm_mon + 1) << "-";
    if (local->tm_mday < 10) oss << "0";
    oss << local->tm_mday;

    return oss.str();
}

string LibraryManager::getDueDate(int daysLater) {
    time_t now = time(nullptr);
    now += (time_t)daysLater * 24 * 60 * 60;
    tm* local = localtime(&now);

    ostringstream oss;
    oss << (local->tm_year + 1900) << "-";
    if (local->tm_mon + 1 < 10) oss << "0";
    oss << (local->tm_mon + 1) << "-";
    if (local->tm_mday < 10) oss << "0";
    oss << local->tm_mday;

    return oss.str();
}

vector<LibraryItem*> LibraryManager::getSortedByTitle() {
    vector<LibraryItem*> arr = catalog.toVector();
    return mergeSort(arr, "title");
}

LibraryItem* LibraryManager::findByISBN(string isbn) {
    vector<Book*> books;
    Node<LibraryItem>* curr = catalog.getHead();

    while (curr) {
        if (curr->data->getType() == "BOOK") {
            books.push_back(dynamic_cast<Book*>(curr->data));
        }
        curr = curr->next;
    }

    books = mergeSortBooksByISBN(books);
    return binarySearchBookByISBN(books, isbn);
}

vector<LibraryItem*> LibraryManager::findByTitle(string kw) {
    return linearSearchByTitle(kw);
}

string LibraryManager::handleGetAll() {
    ostringstream oss;
    oss << "{\"status\":\"OK\",\"data\":[";
    Node<LibraryItem>* curr = catalog.getHead();
    bool first = true;

    while (curr) {
        if (!first) oss << ",";
        oss << itemToJson(curr->data);
        first = false;
        curr = curr->next;
    }

    oss << "]}";
    return oss.str();
}

string LibraryManager::handleSearch(string jsonRequest) {
    string keyword = JSONParser::getValue(jsonRequest, "keyword");
    vector<LibraryItem*> hasil = findByTitle(keyword);

    ostringstream oss;
    oss << "{\"status\":\"OK\",\"data\":[";
    for (int i = 0; i < (int)hasil.size(); i++) {
        if (i > 0) oss << ",";
        oss << itemToJson(hasil[i]);
    }
    oss << "]}";

    return oss.str();
}

string LibraryManager::handleBorrow(string jsonRequest) {
    string userId = JSONParser::getValue(jsonRequest, "userId");
    string itemId = JSONParser::getValue(jsonRequest, "itemId");

    LibraryItem* item = findItemById(itemId);
    if (!item) return JSONParser::error("Item tidak ditemukan");

    if (item->getType() != "BOOK") {
        return JSONParser::error("Hanya buku yang bisa dipinjam");
    }

    Book* book = dynamic_cast<Book*>(item);
    if (!book || book->getStok() <= 0) {
        return JSONParser::error("Stok buku habis");
    }

    book->setStok(book->getStok() - 1);

    string recordId = "R" + to_string(records.getSize() + 1);
    string tanggalPinjam = getCurrentDate();
    string tanggalKembali = getDueDate(7);

    records.pushBack(new BorrowRecord(recordId, userId, itemId, tanggalPinjam, tanggalKembali));

    ostringstream oss;
    oss << "{"
        << "\"status\":\"OK\","
        << "\"message\":\"Buku berhasil dipinjam\","
        << "\"tanggalKembali\":\"" << tanggalKembali << "\""
        << "}";

    return oss.str();
}

string LibraryManager::handleReturn(string jsonRequest) {
    string userId = JSONParser::getValue(jsonRequest, "userId");
    string itemId = JSONParser::getValue(jsonRequest, "itemId");

    BorrowRecord* rec = findBorrowRecord(userId, itemId);
    if (!rec) return JSONParser::error("Data peminjaman tidak ditemukan");

    LibraryItem* item = findItemById(itemId);
    if (!item || item->getType() != "BOOK") {
        return JSONParser::error("Item tidak valid");
    }

    Book* book = dynamic_cast<Book*>(item);
    book->setStok(book->getStok() + 1);
    rec->setReturned(true);

    return JSONParser::success("Buku berhasil dikembalikan");
}