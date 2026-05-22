#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

class Book {

private:

    int bookid;
    string title;
    string author;
    bool available;

public:

    // Add Book
    void addbooks() {

        ofstream file("librarymanagementsystem.txt", ios::app);

        cout << "Enter Book ID: ";
        cin >> bookid;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        // Book available by default
        available = true;

        // Store book details in file
        file << bookid << "|"
             << title << "|"
             << author << "|"
             << available << endl;

        file.close();

        cout << "Book added successfully.\n";
    }

    // View All Books
    void viewbooks() {

        ifstream file("librarymanagementsystem.txt");

        // File check
        if (!file) {
            cout << "File not found.\n";
            return;
        }

        while (file >> bookid) {

            file.ignore();

            getline(file, title, '|');
            getline(file, author, '|');

            file >> available;

            cout << bookid << " | "
                 << title << " | "
                 << author << " | ";

            // Show status
            if (available == 1)
                cout << "Available";
            else
                cout << "Issued";

            cout << endl;
        }

        file.close();
    }

    // Search Book
    void searchbook() {

        ifstream file("librarymanagementsystem.txt");

        // File check
        if (!file) {
            cout << "File not found.\n";
            return;
        }

        string searchtitle;
        bool found = false;

        cin.ignore();

        cout << "Enter Title to search: ";
        getline(cin, searchtitle);

        while (file >> bookid) {

            file.ignore();

            getline(file, title, '|');
            getline(file, author, '|');

            file >> available;

            // Check title
            if (searchtitle == title) {

                found = true;

                cout << bookid << " | "
                     << title << " | "
                     << author << " | ";

                // Show status
                if (available == 1)
                    cout << "Available";
                else
                    cout << "Issued";

                cout << endl;
            }
        }

        // If book not found
        if (!found) {
            cout << "Book not found.\n";
        }

        file.close();
    }

    // Issue Book
    void issuebook() {

        ifstream file("librarymanagementsystem.txt");

        // File check
        if (!file) {
            cout << "File not found.\n";
            return;
        }

        ofstream temp("temp.txt");

        int searchbookid;
        bool found = false;

        cout << "Enter Book ID to Issue: ";
        cin >> searchbookid;

        while (file >> bookid) {

            file.ignore();

            getline(file, title, '|');
            getline(file, author, '|');

            file >> available;

            // Check Book ID
            if (searchbookid == bookid) {

                found = true;

                // If book available
                if (available == 1) {

                    available = 0;

                    cout << "Book Issued Successfully\n";
                }
                else {

                    cout << "Book Already Issued\n";
                }
            }

            // Store updated data
            temp << bookid << "|"
                 << title << "|"
                 << author << "|"
                 << available << endl;
        }

        file.close();
        temp.close();

        // Replace old file
        remove("librarymanagementsystem.txt");
        rename("temp.txt", "librarymanagementsystem.txt");

        if (!found) {
            cout << "Book not found.\n";
        }
    }

    // Return Book
    void returnbook() {

        ifstream file("librarymanagementsystem.txt");

        // File check
        if (!file) {
            cout << "File not found.\n";
            return;
        }

        ofstream temp("temp.txt");

        int searchbookid;
        bool found = false;

        cout << "Enter Book ID to Return: ";
        cin >> searchbookid;

        while (file >> bookid) {

            file.ignore();

            getline(file, title, '|');
            getline(file, author, '|');

            file >> available;

            // Check Book ID
            if (searchbookid == bookid) {

                found = true;

                // Return only if issued
                if (available == 0) {

                    available = 1;

                    cout << "Book Returned Successfully\n";
                }
                else {

                    cout << "Book is already available\n";
                }
            }

            // Store updated data
            temp << bookid << "|"
                 << title << "|"
                 << author << "|"
                 << available << endl;
        }

        file.close();
        temp.close();

        // Replace original file
        remove("librarymanagementsystem.txt");
        rename("temp.txt", "librarymanagementsystem.txt");

        if (!found) {
            cout << "Book not found.\n";
        }
    }
};

int main() {

    Book b;
    int choice;

    while (true) {

        // Menu
        cout << "\n===== Library Management System =====\n";

        cout << "1. Add Books\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            b.addbooks();
            break;

        case 2:
            b.viewbooks();
            break;

        case 3:
            b.searchbook();
            break;

        case 4:
            b.issuebook();
            break;

        case 5:
            b.returnbook();
            break;

        case 6:
            return 0;

        default:
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}