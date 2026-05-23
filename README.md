# Finpro_Alprog

Aplikasi Perpustakaan Digital (Library Management)
//Deskripsi: Sistem peminjaman buku berbasis client-server. Server menyimpan katalog buku, client (mahasiswa) bisa mencari, meminjam, dan mengembalikan buku.

Penjelasan dan Penggunaan Program:
---

## 📖 1. Lihat Semua Data
Menu ini berfungsi sebagai katalog utama yang menampilkan seluruh koleksi buku yang terdaftar di dalam sistem perpustakaan.

**Fitur yang Termuat:**
* **Tampilan Tabel Terstruktur:** Data buku disajikan dalam format tabel yang rapi, mencakup informasi seperti `ID Buku`, `Judul`, `Penulis`, `Penerbit`, `Tahun`, dan `Status` (Tersedia/Dipinjam).
* **Informasi Ketersediaan Real-Time:** Status buku akan selalu *up-to-date* menyesuaikan dengan transaksi peminjaman dan pengembalian terbaru.

---

## 🔍 2. Cari Judul
Menu ini dirancang untuk memudahkan pengguna dalam menemukan buku spesifik tanpa harus melihat seluruh daftar buku secara manual.

**Fitur yang Termuat:**
* **Pencarian Fleksibel (Partial Matching):** Pengguna tidak perlu mengetikkan judul secara utuh. Memasukkan sebagian kata (misal: "Harry") akan memunculkan semua buku yang mengandung kata tersebut (contoh: "Harry Potter").
* **Case-Insensitive:** Pencarian tidak terpengaruh oleh huruf besar atau kecil. Input `PYTHON`, `python`, atau `PyThoN` akan memberikan hasil pencarian yang sama.
* **Validasi Hasil Kosong:** Jika kata kunci yang dicari tidak ada di pangkalan data, sistem akan memberikan umpan balik (feedback) yang informatif seperti, *"Maaf, buku dengan judul tersebut tidak ditemukan."*

---

## 📤 3. Pinjam Buku
Menu ini adalah fungsionalitas utama untuk memproses transaksi peminjaman buku oleh *client*. 

**Fitur yang Termuat:**
* **Verifikasi ID Buku:** Sistem akan meminta pengguna memasukkan `ID Buku`. Jika ID tidak valid atau salah ketik, sistem akan meminta input ulang.
* **Pengecekan Status Otomatis:** Sistem akan mengecek apakah buku tersebut sedang "Tersedia". Jika buku berstatus "Dipinjam" oleh orang lain, sistem akan menolak proses peminjaman.
---

## 📥 4. Kembalikan Buku
Menu ini digunakan untuk menyelesaikan transaksi peminjaman dan mengembalikan buku ke dalam sistem.

**Fitur yang Termuat:**
* **Validasi Kepemilikan Transaksi:** Sistem memastikan bahwa `ID Buku` yang dimasukkan benar-benar sedang dalam status "Dipinjam".
