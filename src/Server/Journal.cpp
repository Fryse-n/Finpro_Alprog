#include "Journal.h"

using namespace std;

Journal::Journal(string id, string title, string penerbit,
                 string issn, int tahun, int volume, int edisi)
    : LibraryItem(id, title, tahun),
      penerbit(penerbit), issn(issn),
      volume(volume), edisi(edisi) {}

string Journal::getPenerbit() const { return penerbit; }
string Journal::getISSN() const { return issn; }
int Journal::getVolume() const { return volume; }
int Journal::getEdisi() const { return edisi; }

void Journal::setVolume(int v) {
    volume = v;
}

string Journal::getDetail() const {
    return "[JURNAL] " + title + " | " + penerbit +
           " | Vol." + to_string(volume) + " Ed." + to_string(edisi);
}

string Journal::getType() const {
    return "JOURNAL";
}