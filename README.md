# Library Management System

## Overview
This Library Management System is a C++ application that allows students, faculty, and librarians to manage books and user accounts efficiently. It supports borrowing, returning, overdue fine calculation, and user management functionalities.

## Features
- **Student Features**
  - View available books
  - Borrow books (up to 3 books for 15 days)
  - Return books (overdue fine: ₹10 per day)
  - Check fine and pay if applicable
  
- **Faculty Features**
  - View available books
  - Borrow books (up to 5 books for 30 days)
  - Return books (cannot borrow if overdue for 60+ days)
  
- **Librarian Features**
  - Add, remove, or update books
  - Add or remove users
  - Manage user borrowing records

## File Structure
```
Library_assignment/
├── src/
│   ├── main.cpp
│   ├── Account.cpp
│   ├── Book.cpp
│   ├── User.cpp
│   ├── Student.cpp
│   ├── Faculty.cpp
│   ├── Librarian.cpp
│   ├── Library.cpp
├── include/
│   ├── Account.h
│   ├── Book.h
│   ├── User.h
│   ├── Student.h
│   ├── Faculty.h
│   ├── Librarian.h
│   ├── Library.h
├── data/
│   ├── books.txt
│   ├── users.txt
│   ├── accounts.txt
├── Makefile
├── README.md
```

## Installation and Compilation
### **Using Makefile** (Recommended)
1. Open a terminal or command prompt in the project directory.
2. Run the following command to compile:
   ```sh
   mingw32-make
   ```
3. Run the executable:
   ```sh
   library_management.exe
   ```

### **Manual Compilation** (Without Makefile)
If `mingw32-make` is not installed, compile manually:
```sh
g++ -std=c++11 -I include -o library_management src/*.cpp
```
Then run:
```sh
library_management.exe
```

## Usage
1. **Run the program**
   ```sh
   library_management.exe
   ```
2. **Choose user type** (Student, Faculty, or Librarian).
3. **Log in** using credentials from `users.txt`.
4. **Perform actions** such as borrowing, returning books, managing users, and paying fines.

## Data Storage
- `books.txt` → Stores book details.
- `users.txt` → Stores user details.
- `accounts.txt` → Stores borrowing records and fines.

## Cleaning the Project
To remove compiled files and reset the project:
```sh
mingw32-make clean
```
This deletes the executable and object files.

## Contributions
Contributions are welcome! If you find bugs or want to improve features, feel free to submit a pull request.

## License
This project is open-source under the MIT License.
