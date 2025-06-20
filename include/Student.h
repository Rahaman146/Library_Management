#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

using namespace std;

class Student : public User
{
public:
    static const int maxBooks = 3;
    static const int borrowDays = 15;
    static const int finePerDay = 10;

    Student(int id, string username, string password, string name);
    void borrowBook(vector<Book> &books, int bookID, vector<Account> &accounts) override;
    void returnBook(vector<Book> &books, int bookID, vector<Account> &accounts) override;

    void viewBorrowedBooks(const vector<Book> &books) const override;
    void dashboard(vector<Book> &books, vector<User *> &users, vector<Account> &accounts) override;
};

#endif
