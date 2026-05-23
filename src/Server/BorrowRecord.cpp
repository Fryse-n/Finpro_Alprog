#include "BorrowRecord.h"

using namespace std;

BorrowRecord::BorrowRecord(string id, string userId, string itemId,
                           string tanggalPinjam, string tanggalKembali)
    : id(id), userId(userId), itemId(itemId),
      tanggalPinjam(tanggalPinjam), tanggalKembali(tanggalKembali),
      returned(false) {}

string BorrowRecord::getId() const { return id; }
string BorrowRecord::getUserId() const { return userId; }
string BorrowRecord::getItemId() const { return itemId; }
string BorrowRecord::getTanggalPinjam() const { return tanggalPinjam; }
string BorrowRecord::getTanggalKembali() const { return tanggalKembali; }
bool BorrowRecord::isReturned() const { return returned; }

void BorrowRecord::setReturned(bool r) {
    returned = r;
}

string BorrowRecord::getDetail() const {
    return "[BORROW] " + id + " | " + userId + " | " + itemId +
           " | pinjam: " + tanggalPinjam + " | kembali: " + tanggalKembali +
           " | returned: " + (returned ? "true" : "false");
}