#ifndef USER_H
#define USER_H

#include "Account.h"
#include <string>
#include <fstream>
#include <vector>
#include "Book.h"

using namespace std;

class User
{
protected:
    int id;
    string name, role;
    string username;
    string password;
    Account account;
    vector<int> borrowedBooks;

public:
    User();
    User(int id, string username, string password, string role, string name);

    virtual void dashboard(std::vector<Book> &books, std::vector<User *> &users, vector<Account> &accounts) = 0;

    int getId() const;
    std::string getName() const;
    std::string getRole() const;
    string getUsername() const;
    string getPassword() const;
    bool checkUsername(const string &inputUsername) const;
    bool checkPassword(const string &inputPassword) const;

    void changePassword(vector<User *> &users, int id);

    virtual void borrowBook(vector<Book> &books, int bookID, vector<Account> &accounts) = 0;
    virtual void returnBook(vector<Book> &books, int bookID, vector<Account> &accounts) = 0;
    virtual void viewBorrowedBooks(const vector<Book> &books) const = 0;
    bool hasUnpaidFines() const;
    void payFine(vector<Account> &accounts);
    void setAccount(const Account &acc);

    static void saveToFile(const vector<User *> &users, const string &filename);
    static vector<User *> loadFromFile(const string &filename, vector<Account> &accounts);
};

#endif
