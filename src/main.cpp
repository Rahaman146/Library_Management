#include "Student.h"
#include "Faculty.h"
#include "Librarian.h"
#include "Book.h"
#include "User.h"
#include <iostream>
#include "Account.h"
#include <vector>

using namespace std;

int main()
{
    vector<Book> books = Book::loadFromFile("data/books.txt");
    vector<Account> accounts = Account::loadFromFile("data/accounts.txt");
    vector<User *> users = User::loadFromFile("data/users.txt", accounts);

    string username;
    cout << "Enter username: ";
    cin >> username;

    string password;
    cout << "Enter password: ";
    cin >> password;

    bool check = false;

    for (User *user : users)
    {
        if ((user->getUsername() == username) && (user->getPassword() == password))
        {
            check = true;
            if (Student *student = dynamic_cast<Student *>(user))
            {
                student->dashboard(books, users, accounts);
            }
            else if (Faculty *faculty = dynamic_cast<Faculty *>(user))
            {
                faculty->dashboard(books, users, accounts);
            }
            else if (Librarian *librarian = dynamic_cast<Librarian *>(user))
            {
                librarian->dashboard(books, users, accounts);
            }
            else
            {
                cout << "Unknown user role.\n";
            }
            break;
        }
    }
    if (!check)
    {
        cout << "Invalid credentials!" << endl;
    }
    Book::saveToFile(books, "data/books.txt");
    User::saveToFile(users, "data/users.txt");

    for (User *user : users)
        delete user;

    return 0;
}
