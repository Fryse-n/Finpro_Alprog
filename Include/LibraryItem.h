#pragma once
#include <bits/stdc++.h>

class LibraryItem {
protected:
    std::string id;
    std::string title;
    int tahun;

public:
    LibraryItem(std::string id, std::string title, int tahun)
        : id(id), title(title), tahun(tahun) {}

    std::string getId() const { return id; }
    std::string getTitle() const { return title; }
    int getTahun() const { return tahun; }
    void setTitle(std::string t) { title = t; }

    virtual std::string getDetail() const = 0;
    virtual std::string getType() const = 0;

    virtual ~LibraryItem() {}
};