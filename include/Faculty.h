#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"

using namespace std;

class Faculty : public User
{
public:
    static const int maxBooks = 5;
    static const int borrowDays = 30;
    static const int overdueLimit = 60;

    Faculty(int id, string username, string password, string name);

    void borrowBook(vector<Book> &books, int bookID, vector<Account> &accounts) override;
    void returnBook(vector<Book> &books, int bookID, vector<Account> &accounts) override;

    void viewBorrowedBooks(const vector<Book> &books) const override;
    void dashboard(vector<Book> &books, vector<User *> &users, vector<Account> &accounts) override;
};

#endif
