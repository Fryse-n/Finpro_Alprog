#pragma once
#include "LibraryItem.h"

class Book : public LibraryItem {
private:
    std::string pengarang;
    std::string isbn;
    int stok;
    bool tersedia;

public:
    Book(std::string id, std::string title, std::string pengarang,
         std::string isbn, int tahun, int stok);

    std::string getPengarang() const;
    std::string getISBN() const;
    int getStok() const;
    bool isTersedia() const;
    void setStok(int s);

    std::string getDetail() const override;
    std::string getType() const override;
};