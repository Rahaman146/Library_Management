#include "User.h"
#include "Student.h"
#include "Faculty.h"
#include "Librarian.h"
#include <iostream>
#include "Book.h"
#include "Account.h"
using namespace std;

int User::getId() const
{
    return id;
}
string User::getUsername() const { return username; }

string User::getPassword() const { return password; }

std::string User::getName() const
{
    return name;
}

std::string User::getRole() const
{
    return role;
}
User::User(int id, string username, string password, string role, string name)
    : id(id), username(username), password(password), role(role), name(name), account(id) {}

void User::setAccount(const Account &acc)
{
    account = acc;
}
void User::viewBorrowedBooks(const std::vector<Book> &books) const
{
    account.viewBorrowedBooks(books);
}

bool User::hasUnpaidFines() const
{
    return account.getFine() > 0;
}

void User::payFine(vector<Account> &accounts)
{
    account.payFine(accounts);
}
bool User::checkUsername(const string &inputUsername) const
{
    return inputUsername == username;
}
bool User::checkPassword(const string &inputPassword) const
{
    return inputPassword == password;
}

void User::changePassword(vector<User *> &users, int userId)
{
    string oldPassword, newPassword, confirmPassword;

    for (User *user : users)
    {
        if (user->getId() == userId)
        {
            cout << "Enter current password: ";
            cin >> oldPassword;

            if (oldPassword != user->getPassword())
            {
                cout << "Incorrect password!" << endl;
                return;
            }

            cout << "Enter new password: ";
            cin >> newPassword;
            cout << "Confirm new password: ";
            cin >> confirmPassword;

            if (newPassword != confirmPassword)
            {
                cout << "Passwords do not match!" << endl;
                return;
            }

            user->getPassword() = newPassword;
            cout << "Password updated successfully!" << endl;

            ofstream uoutfile("./data/users.txt");
            for (auto usr : users)
            {
                uoutfile << usr->getId() << "," << usr->getUsername() << "," << usr->getPassword() << "," << usr->getRole() << "," << usr->getName() << "\n";
            }
            uoutfile.close();
            return;
        }
    }
    cout << "User not found!" << endl;
}

void User::saveToFile(const vector<User *> &users, const string &filename)
{
    ofstream file(filename);
    if (!file)
    {
        cout << "Error saving users to file!" << endl;
        return;
    }
    for (const User *user : users)
    {
        file << user->id << "," << user->username << "," << user->password << "," << user->role << "," << user->name << endl;
    }
    file.close();
}

vector<User *> User::loadFromFile(const string &filename, vector<Account> &accounts)
{
    vector<User *> users;
    ifstream file(filename);
    if (!file)
    {
        cout << "Error loading users from file. Starting with an empty list." << endl;
        return users;
    }

    int id;
    string name, username, password, role;
    while (file >> id && file.ignore(1, ',') &&
           getline(file, username, ',') &&
           getline(file, password, ',') &&
           getline(file, role, ',') &&
           getline(file, name))
    {
        User *user = nullptr;

        if (role == "Student")
            user = new Student(id, username, password, name);
        else if (role == "Faculty")
            user = new Faculty(id, username, password, name);
        else if (role == "Librarian")
            user = new Librarian(id, username, password, name);

        if (user)
        {
            for (Account &acc : accounts)
            {
                if (acc.getUserID() == id)
                {
                    user->setAccount(acc);

                    break;
                }
            }
            users.push_back(user);
        }
    }

    file.close();
    return users;
}
