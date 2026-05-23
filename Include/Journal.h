#pragma once
#include "LibraryItem.h"

class Journal : public LibraryItem {
private:
    std::string penerbit;
    std::string issn;
    int volume;
    int edisi;

public:
    Journal(std::string id, std::string title, std::string penerbit,
            std::string issn, int tahun, int volume, int edisi);

    std::string getPenerbit() const;
    std::string getISSN() const;
    int getVolume() const;
    int getEdisi() const;
    void setVolume(int v);

    std::string getDetail() const override;
    std::string getType() const override;
};