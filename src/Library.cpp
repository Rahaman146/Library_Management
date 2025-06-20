#include "Library.h"
#include "Student.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Library::Library() {}

Library::~Library()
{
    for (auto u : users)
        delete u;
}

void Library::loadData()
{
}

void Library::displayAvailableBooks()
{
    cout << "\nAvailable Books:\n";
    for (auto &book : books)
    {
        if (book.getStatus() == "Available")
        {
            book.display();
        }
    }
}

Book *Library::findBookById(int id)
{
    for (auto &book : books)
    {
        if (book.getId() == id)
            return &book;
    }
    return nullptr;
}
