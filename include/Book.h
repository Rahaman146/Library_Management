#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Book
{
private:
    int id;
    string title, author, publisher, isbn;
    int year;
    string status;

public:
    Book();
    Book(int id, string title, string author, string publisher, int year, string isbn, string status = "Available");

    void display() const;
    int getId() const;
    string Get_Book_Name() const;
    string getTitle() const;
    string Get_Publisher() const;
    string Get_ISBN() const;
    string getStatus() const;
    void updateStatus(string newStatus);

    void updateBookDetails(string t, string a, string p, int y, string i);

    static void saveToFile(const vector<Book> &books, const string &filename);
    static vector<Book> loadFromFile(const string &filename);
};

#endif
