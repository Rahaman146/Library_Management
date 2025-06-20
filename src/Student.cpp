#include "Student.h"
#include "Book.h"
#include "Account.h"
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

Student::Student(int id, std::string username, std::string password, std::string name)
    : User(id, username, password, "Student", name) {}

void Student::borrowBook(vector<Book> &books, int bookID, vector<Account> &accounts)
{
    if (account.getFine() > 0)
    {
        cout << "Cannot borrow books until fine is paid.\n";
        return;
    }

    if (account.getBorrowedCount() >= maxBooks)
    {
        cout << "Cannot borrow more than " << maxBooks << " books!\n";
        return;
    }

    for (Book &book : books)
    {
        if (book.getId() == bookID)
        {
            if (book.getStatus() == "Available")
            {
                book.updateStatus("NotAvailable");
                account.borrowBook(bookID, borrowDays);

                for (Account &acc : accounts)
                {
                    if (acc.getUserID() == account.getUserID())
                    {
                        acc = account;
                        break;
                    }
                }
                cout << "Done " << name << " borrowed: " << book.getTitle() << endl;
                Book::saveToFile(books, "data/books.txt");
                Account::saveToFile(accounts, "data/accounts.txt");
                return;
            }
            else
            {
                cout << "Book is already borrowed!\n";
                return;
            }
        }
    }
    cout << "Book ID not found!\n";
}

void Student::returnBook(vector<Book> &books, int bookID, vector<Account> &accounts)
{
    if (!account.hasBorrowedBook(bookID))
    {
        cout << "You have not borrowed this book!\n";
        return;
    }

    for (Book &book : books)
    {
        if (book.getId() == bookID)
        {
            book.updateStatus("Available");
            account.returnBook(bookID, finePerDay);

            for (Account &acc : accounts)
            {
                if (acc.getUserID() == account.getUserID())
                {
                    acc = account;
                    break;
                }
            }
            cout << "Done " << name << " returned: " << book.getTitle() << endl;
            Book::saveToFile(books, "data/books.txt");
            Account::saveToFile(accounts, "data/accounts.txt");
            return;
        }
    }
    cout << "Book ID not found!\n";
}

void Student::viewBorrowedBooks(const vector<Book> &books) const
{
    account.viewBorrowedBooks(books);
}

void Student::dashboard(vector<Book> &books, vector<User *> &users, vector<Account> &accounts)
{
    int choice;
    do
    {
        cout << "\n--- STUDENT DASHBOARD (" << name << ") ---\n";
        cout << "1. View Available Books\n";
        cout << "2. Borrow a Book\n";
        cout << "3. Return a Book\n";
        cout << "4. View Borrowed Books\n";
        cout << "5. Check Fine Amount\n";
        cout << "6. Pay Fine\n";
        cout << "7. Change Password\n";
        cout << "8. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            bool check = true;
            cout << "\nAvailable Books:\n";
            for (const Book &book : books)
            {
                if (book.getStatus() == "Available")
                {
                    check = false;
                    book.display();
                }
            }
            if (check)
            {
                cout << "\nNo Avaliable Books\n";
            }
        }
        else if (choice == 2)
        {
            int bookID;
            cout << "Enter Book ID to borrow: ";
            cin >> bookID;
            borrowBook(books, bookID, accounts);
        }
        else if (choice == 3)
        {
            int bookID;
            cout << "Enter Book ID to return: ";
            cin >> bookID;
            returnBook(books, bookID, accounts);
        }
        else if (choice == 4)
        {
            viewBorrowedBooks(books);
        }
        else if (choice == 5)
        {
            cout << "Outstanding Fine: Rs " << account.getFine() << endl;
        }
        else if (choice == 6)
        {
            account.payFine(accounts);
            cout << "Fine paid successfully! You can now borrow books.\n";
        }
        else if (choice == 7)
        {
            changePassword(users, id);
            break;
        }
        else if (choice == 8)
        {
            Account::saveToFile(accounts, "data/accounts.txt");
            cout << "Logout successful!\n";
        }
    } while (choice != 8);
}
