#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <ctime>
#include <fstream>
#include "Book.h"

using namespace std;

struct BorrowRecord
{
    int bookId;
    time_t borrowTime;
};

class Account
{
private:
    int userID;
    vector<BorrowRecord> borrowedRecords;
    double fine;

public:
    Account(int userID);
    void borrowBook(int bookId, int daysLimit);
    void returnBook(int bookId, int finePerDay);

    double getFine() const;
    void payFine(vector<Account> &accounts);

    bool hasBorrowedBook(int bookId) const;
    bool hasOverdueBooks(int maxOverdueDays) const;
    int getBorrowedCount() const;
    int getUserID() const;
    void viewBorrowedBooks(const vector<Book> &books) const;

    static void saveToFile(const vector<Account> &accounts, const string &filename);
    static vector<Account> loadFromFile(const string &filename);
};

#endif
