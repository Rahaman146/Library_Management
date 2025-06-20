#include "Book.h"

Book::Book() : id(0), year(0), status("Available") {}

Book::Book(int id, string title, string author, string publisher, int year, string isbn, string status)
    : id(id), title(title), author(author), publisher(publisher), year(year), isbn(isbn), status(status) {}

void Book::display() const
{
    cout << id << ": " << title << " by " << author << " (" << year << ") - " << status << endl;
}

int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getStatus() const { return status; }

void Book::updateStatus(string newStatus)
{
    status = newStatus;
}
void Book::updateBookDetails(string t, string a, string p, int y, string i)
{
    title = t;
    author = a;
    publisher = p;
    year = y;
    isbn = i;
}
void Book::saveToFile(const vector<Book> &books, const string &filename)
{
    ofstream file(filename);
    if (!file)
    {
        cout << "Error saving books to file!" << endl;
        return;
    }
    for (const Book &book : books)
    {
        file << book.id << "," << book.title << "," << book.author << ","
             << book.publisher << "," << book.year << "," << book.isbn << ","
             << book.status << endl;
    }
    file.close();
}
vector<Book> Book::loadFromFile(const string &filename)
{
    vector<Book> books;
    ifstream file(filename);
    if (!file)
    {
        cout << "Error loading books from file. Starting with an empty list." << endl;
        return books;
    }

    int id, year;
    string title, author, publisher, isbn, status;
    while (file >> id && file.ignore(1, ',') &&
           getline(file, title, ',') &&
           getline(file, author, ',') &&
           getline(file, publisher, ',') &&
           file >> year && file.ignore(1, ',') &&
           getline(file, isbn, ',') &&
           getline(file, status))
    {
        books.push_back(Book(id, title, author, publisher, year, isbn, status));
    }

    file.close();

    return books;
}
