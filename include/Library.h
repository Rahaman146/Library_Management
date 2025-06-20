#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <vector>

class Library
{
public:
    vector<Book> books;
    vector<User *> users;

    Library();
    ~Library();
    void loadData();
    void saveData();
    void displayAvailableBooks();
    Book *findBookById(int id);
};

#endif
