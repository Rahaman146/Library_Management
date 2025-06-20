#include "Faculty.h"
#include "Book.h"
#include <iostream>
#include <algorithm>

using namespace std;

Faculty::Faculty(int id, string username, string password, string name) : User(id, username, password, "Faculty", name) {}

void Faculty::borrowBook(vector<Book> &books, int bookID, vector<Account> &accounts)
{
    if (account.hasOverdueBooks(overdueLimit))
    {
        cout << "Cannot borrow books due to overdue book(s) exceeding " << overdueLimit << " days.\n";
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

                Book::saveToFile(books, "data/books.txt");
                Account::saveToFile(accounts, "data/accounts.txt");

                cout << "Done " << name << " borrowed: " << book.getTitle() << endl;
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

void Faculty::returnBook(vector<Book> &books, int bookID, vector<Account> &accounts)
{
    auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookID);
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
            account.returnBook(bookID, 0);

            for (Account &acc : accounts)
            {
                if (acc.getUserID() == account.getUserID())
                {
                    acc = account;
                    break;
                }
            }

            Book::saveToFile(books, "data/books.txt");
            Account::saveToFile(accounts, "data/accounts.txt");

            cout << "Done " << name << " returned: " << book.getTitle() << endl;
            return;
        }
    }
    cout << "Book ID not found!\n";
}

void Faculty::viewBorrowedBooks(const vector<Book> &books) const
{
    cout << "\nBorrowed Books for " << name << ":\n";
    account.viewBorrowedBooks(books);
}

void Faculty::dashboard(vector<Book> &books, vector<User *> &users, vector<Account> &accounts)
{
    int choice;
    do
    {
        cout << "\n--- FACULTY DASHBOARD (" << name << ") ---\n";
        cout << "1. View Available Books\n";
        cout << "2. Borrow a Book\n";
        cout << "3. Return a Book\n";
        cout << "4. View Borrowed Books\n";
        cout << "5. Change Password\n";
        cout << "6. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\nAvailable Books:\n";
            for (const Book &book : books)
            {
                if (book.getStatus() == "Available")
                {
                    book.display();
                }
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
            changePassword(users, id);
            break;
        }
        else if (choice == 6)
        {
            Account::saveToFile(accounts, "data/accounts.txt");
            cout << "Logout successful!\n";
        }
    } while (choice != 6);
}
