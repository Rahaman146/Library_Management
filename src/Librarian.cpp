#include "Librarian.h"
#include "Student.h"
#include "Faculty.h"
#include <iostream>
#include <fstream>
#include "Book.h"

using namespace std;

Librarian::Librarian(int id, string username, string password, string name) : User(id, username, password, "Librarian", name) {}

void Librarian::borrowBook(vector<Book> &, int bookID, vector<Account> &accounts)
{
    cout << "Librarians cannot borrow books!\n";
}

void Librarian::returnBook(vector<Book> &, int bookID, vector<Account> &accounts)
{
    cout << "Librarians do not return books!\n";
}

void Librarian::viewBorrowedBooks(const vector<Book> &books) const
{
    cout << "Librarians do not borrow books, so they have no borrowed books.\n";
}

void Librarian::dashboard(vector<Book> &books, vector<User *> &users, vector<Account> &accounts)
{
    int choice;
    do
    {
        cout << "\n--- LIBRARIAN DASHBOARD (" << name << ") ---\n";
        cout << "1. Add a Book\n";
        cout << "2. Remove a Book\n";
        cout << "3. Update a Book\n";
        cout << "4. View All Books\n";
        cout << "5. Add a User\n";
        cout << "6. Remove a User\n";
        cout << "7. View All Users\n";
        cout << "8. Change Password\n";
        cout << "9. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            addBook(books);
        }
        else if (choice == 2)
        {
            removeBook(books);
        }
        else if (choice == 3)
        {
            updateBook(books);
        }
        else if (choice == 4)
        {
            for (const Book &book : books)
            {
                book.display();
            }
        }
        else if (choice == 5)
        {
            addUser(users);
        }
        else if (choice == 6)
        {
            removeUser(users);
        }
        else if (choice == 7)
        {
            viewUsers(users);
        }
        else if (choice == 8)
        {
            changePassword(users, id);
            break;
        }
        else if (choice == 9)
        {
            Account::saveToFile(accounts, "data/accounts.txt");
            cout << "Logout successful!\n";
        }
    } while (choice != 9);
}
void Librarian::addBook(vector<Book> &books)
{
    int id, year;
    string title, author, publisher, isbn, status = "Available";

    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Publisher: ";
    getline(cin, publisher);
    cout << "Enter Year: ";
    cin >> year;
    cin.ignore();
    cout << "Enter ISBN: ";
    getline(cin, isbn);

    books.push_back(Book(id, title, author, publisher, year, isbn, status));
    Book::saveToFile(books, "data/books.txt");
    cout << "Book added successfully!\n";
}

void Librarian::removeBook(vector<Book> &books)
{
    int bookID;
    cout << "Enter Book ID to remove: ";
    cin >> bookID;

    for (auto it = books.begin(); it != books.end(); ++it)
    {
        if (it->getId() == bookID)
        {
            books.erase(it);
            Book::saveToFile(books, "data/books.txt");
            cout << "Book removed successfully!\n";
            return;
        }
    }
    cout << "Book ID not found!\n";
}

void Librarian::updateBook(vector<Book> &books)
{
    int bookID;
    cout << "Enter Book ID to update: ";
    cin >> bookID;

    for (Book &book : books)
    {
        if (book.getId() == bookID)
        {
            int year;
            string title, author, publisher, isbn;

            cout << "Enter New Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter New Author: ";
            getline(cin, author);
            cout << "Enter New Publisher: ";
            getline(cin, publisher);
            cout << "Enter New Year: ";
            cin >> year;
            cin.ignore();
            cout << "Enter New ISBN: ";
            getline(cin, isbn);

            book.updateBookDetails(title, author, publisher, year, isbn);
            Book::saveToFile(books, "data/books.txt");
            cout << "Book updated successfully!\n";
            return;
        }
    }
    cout << "Book ID not found!\n";
}

void Librarian::addUser(vector<User *> &users)
{
    int id;
    string name, username, password, role;

    cout << "Enter User ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Role (Student/Faculty/Librarian): ";
    getline(cin, role);
    cout << "Enter Username: ";
    getline(cin, username);
    cout << "Enter Password: ";
    getline(cin, password);

    if (role == "Student")
    {
        users.push_back(new Student(id, username, password, name));
    }
    else if (role == "Faculty")
    {
        users.push_back(new Faculty(id, username, password, name));
    }
    else if (role == "Librarian")
    {
        users.push_back(new Librarian(id, username, password, name));
    }
    else
    {
        cout << "Invalid role! User not added.\n";
        return;
    }

    User::saveToFile(users, "data/users.txt");
    cout << "User added successfully!\n";
}

void Librarian::removeUser(vector<User *> &users)
{
    int id;
    cout << "Enter User ID to remove: ";
    cin >> id;

    for (auto it = users.begin(); it != users.end(); ++it)
    {
        if ((*it)->getId() == id)
        {
            delete *it;
            users.erase(it);
            User::saveToFile(users, "data/users.txt");
            cout << "User removed successfully!\n";
            return;
        }
    }
    cout << "User not found!\n";
}

void Librarian::viewUsers(const vector<User *> &users)
{
    cout << "\nList of Users:\n";
    for (const User *user : users)
    {
        cout << "ID: " << user->getId() << " | Username: " << user->getUsername() << " | Password: " << user->getPassword() << " | Name: " << user->getName()
             << " | Role: " << user->getRole() << endl;
    }
}
