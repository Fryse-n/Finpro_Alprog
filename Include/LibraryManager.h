#pragma once
#include <bits/stdc++.h>
#include "LinkedList.h"
#include "LibraryItem.h"
#include "BorrowRecord.h"
#include "Book.h"
#include "Journal.h"
#include "JSONParser.h"

class LibraryManager {
private:
    LinkedList<LibraryItem> catalog;
    LinkedList<BorrowRecord> records;

    std::vector<LibraryItem*> mergeSort(std::vector<LibraryItem*> arr, std::string sortBy);
    std::vector<LibraryItem*> merge(std::vector<LibraryItem*>& L,
                                    std::vector<LibraryItem*>& R,
                                    std::string sortBy);

    std::vector<Book*> mergeSortBooksByISBN(std::vector<Book*> arr);
    std::vector<Book*> mergeBooksByISBN(std::vector<Book*>& L,
                                        std::vector<Book*>& R);
    Book* binarySearchBookByISBN(std::vector<Book*>& arr, std::string isbn);

    std::vector<LibraryItem*> linearSearchByTitle(std::string keyword);

    LibraryItem* findItemById(std::string itemId);
    BorrowRecord* findBorrowRecord(std::string userId, std::string itemId);

    std::string itemToJson(LibraryItem* item);
    std::string getCurrentDate();
    std::string getDueDate(int daysLater);

public:
    void addBook(Book* b);
    void addJournal(Journal* j);

    std::vector<LibraryItem*> getSortedByTitle();
    LibraryItem* findByISBN(std::string isbn);
    std::vector<LibraryItem*> findByTitle(std::string kw);

    std::string handleGetAll();
    std::string handleSearch(std::string jsonRequest);
    std::string handleBorrow(std::string jsonRequest);
    std::string handleReturn(std::string jsonRequest);
};