#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"
#include "Book.h"
#include <vector>

using namespace std;

class Librarian : public User
{
public:
    Librarian(int id, string username, string password, std::string name);
    void dashboard(vector<Book> &books, vector<User *> &users, vector<Account> &accounts) override;

    void borrowBook(vector<Book> &books, int bookID, vector<Account> &accounts) override;
    void returnBook(vector<Book> &books, int bookID, vector<Account> &accounts) override;
    void viewBorrowedBooks(const vector<Book> &books) const override;

    void addBook(std::vector<Book> &books);
    void removeBook(std::vector<Book> &books);
    void updateBook(std::vector<Book> &books);

    void addUser(std::vector<User *> &users);
    void removeUser(std::vector<User *> &users);
    void viewUsers(const std::vector<User *> &users);
};

#endif
