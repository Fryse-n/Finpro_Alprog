#include "Book.h"
using namespace std;

Book::Book(string id, string title, string pengarang,
           string isbn, int tahun, int stok)
    : LibraryItem(id, title, tahun),
      pengarang(pengarang), isbn(isbn),
      stok(stok), tersedia(stok > 0) {}

string Book::getPengarang() const { return pengarang; }
string Book::getISBN() const { return isbn; }
int Book::getStok() const { return stok; }
bool Book::isTersedia() const { return tersedia; }

void Book::setStok(int s) {
    stok = s;
    tersedia = (s > 0);
}

string Book::getDetail() const {
    return "[BUKU] " + title + " | " + pengarang +
           " | ISBN: " + isbn + " | Stok: " + to_string(stok);
}

string Book::getType() const {
    return "BOOK";
}