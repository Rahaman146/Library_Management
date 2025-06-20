#include "Account.h"
#include <iostream>
#include "Book.h"
#include <ctime>
#include <limits>

using namespace std;

Account::Account(int id) : userID(id), fine(0) {}

int Account::getUserID() const
{
    return userID;
}

void Account::borrowBook(int bookId, int daysLimit)
{
    BorrowRecord record = {bookId, time(0) + daysLimit * 60};
    borrowedRecords.push_back(record);
}

void Account::returnBook(int bookId, int finePerDay)
{

    for (auto it = borrowedRecords.begin(); it != borrowedRecords.end(); ++it)
    {
        if (it->bookId == bookId)
        {
            time_t now = time(0);

            if (now > it->borrowTime)
            {
                int overdueDays = (now - it->borrowTime) / 60;
                fine += overdueDays * finePerDay;

                cout << "Overdue! Days Overdue: " << overdueDays << " | Fine Applied: " << (overdueDays * finePerDay) << "\n";
            }

            borrowedRecords.erase(it);

            break;
        }
    }
}

void Account::viewBorrowedBooks(const std::vector<Book> &books) const
{
    std::cout << "\nBorrowed Books for User ID: " << userID << ":\n";
    bool found = false;

    for (const auto &record : borrowedRecords)
    {
        for (const Book &book : books)
        {
            if (book.getId() == record.bookId)
            {
                book.display();
                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        std::cout << "No borrowed books.\n";
    }
}

double Account::getFine() const
{
    return fine;
}

void Account::payFine(std::vector<Account> &accounts)
{
    fine = 0;

    for (Account &acc : accounts)
    {
        if (acc.getUserID() == userID)
        {
            acc.fine = 0;
            break;
        }
    }

    Account::saveToFile(accounts, "data/accounts.txt");
}

bool Account::hasBorrowedBook(int bookId) const
{
    for (const auto &record : borrowedRecords)
    {
        if (record.bookId == bookId)
            return true;
    }
    return false;
}

bool Account::hasOverdueBooks(int maxOverdueDays) const
{
    time_t now = time(0);
    for (const auto &record : borrowedRecords)
    {
        if (now - record.borrowTime > maxOverdueDays * 86400)
        {
            return true;
        }
    }
    return false;
}

int Account::getBorrowedCount() const
{
    return borrowedRecords.size();
}

void Account::saveToFile(const vector<Account> &accounts, const string &filename)
{
    ofstream file(filename);
    if (!file)
    {
        cout << "Error saving accounts to file!" << endl;
        return;
    }

    for (const Account &account : accounts)
    {

        file << account.userID << "," << account.fine << "," << account.borrowedRecords.size();

        for (const auto &record : account.borrowedRecords)
        {
            file << "," << record.bookId << "," << record.borrowTime;
        }

        file << endl;
    }

    file.close();
}

vector<Account> Account::loadFromFile(const string &filename)
{
    vector<Account> accounts;
    ifstream file(filename);
    if (!file)
    {
        cout << "Error loading accounts from file. Starting with an empty list." << endl;
        return accounts;
    }

    int userID, borrowedCount, bookId;
    double fine;
    time_t borrowTime;

    while (file >> userID && file.ignore(1, ',') >> fine && file.ignore(1, ',') >> borrowedCount)
    {

        Account account(userID);
        account.fine = fine;

        for (int i = 0; i < borrowedCount; i++)
        {
            if (!(file.ignore(1, ',') >> bookId && file.ignore(1, ',') >> borrowTime))
            {
                cout << "Error reading book data for UserID: " << userID << " (Book ID: " << bookId << ")" << endl;
                file.clear();
                file.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            account.borrowedRecords.push_back({bookId, borrowTime});
        }

        accounts.push_back(account);
    }

    file.close();
    return accounts;
}
