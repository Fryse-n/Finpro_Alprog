#pragma once
#include <bits/stdc++.h>

class BorrowRecord {
private:
    std::string id;
    std::string userId;
    std::string itemId;
    std::string tanggalPinjam;
    std::string tanggalKembali;
    bool returned;

public:
    BorrowRecord(std::string id, std::string userId, std::string itemId,
                 std::string tanggalPinjam, std::string tanggalKembali);

    std::string getId() const;
    std::string getUserId() const;
    std::string getItemId() const;
    std::string getTanggalPinjam() const;
    std::string getTanggalKembali() const;
    bool isReturned() const;
    void setReturned(bool r);

    std::string getDetail() const;
};