#include <stdio.h>

#define MAX_BOOKS 100
#define MAX_BORROWED 100
#define LATE_FINE 10 // Rs. 10 per day late

// Define the structure for a Book
struct Book {
    int bookID;
    char title[100];
    char author[100];
    int isBorrowed; // 0: available, 1: borrowed
};

// Define the structure for Borrowed Book information
struct BorrowedBook {
    int studentID;
    int bookID;
};

// Declare an array of books and borrowed books
struct Book library[MAX_BOOKS];
struct BorrowedBook borrowedBooks[MAX_BORROWED];

int bookCount = 0;          // Keep track of the number of books in the library
int borrowedCount = 0;      // Keep track of borrowed books

// Function to copy strings without using string.h
void copyString(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; // Null-terminate the string
}

// Function to compare two strings (returns 0 if equal)
int compareStrings(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i]; // Return difference if unequal
        }
        i++;
    }
    return str1[i] - str2[i]; // Check if one string is longer
}

// Function to add a new book to the library
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    struct Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.bookID);
    getchar();  // Clear the newline character left by scanf

    printf("Enter Book Title: ");
    fgets(newBook.title, 100, stdin);
    int i = 0;
    while (newBook.title[i] != '\n' && newBook.title[i] != '\0') i++;
    newBook.title[i] = '\0';  // Remove the trailing newline

    printf("Enter Book Author: ");
    fgets(newBook.author, 100, stdin);
    i = 0;
    while (newBook.author[i] != '\n' && newBook.author[i] != '\0') i++;
    newBook.author[i] = '\0';  // Remove the trailing newline

    newBook.isBorrowed = 0;  // Set book as available
    library[bookCount] = newBook;
    bookCount++;

    printf("Book added successfully!\n");
}

// Function to borrow a book
void borrowBook() {
    int studentID, bookID, found = 0;

    printf("Enter Student ID: ");
    scanf("%d", &studentID);
    printf("Enter Book ID: ");
    scanf("%d", &bookID);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].bookID == bookID) {
            found = 1;
            if (library[i].isBorrowed == 1) {
                printf("Book is already borrowed.\n");
            } else {
                library[i].isBorrowed = 1;
                borrowedBooks[borrowedCount].studentID = studentID;
                borrowedBooks[borrowedCount].bookID = bookID;
                borrowedCount++;
                printf("Book borrowed successfully by Student %d.\n", studentID);
            }
            break;
        }
    }

    if (!found) {
        printf("Book not found in the library.\n");
    }
}

// Function to return a book
void returnBook() {
    int studentID, bookID, daysLate, found = 0;

    printf("Enter Student ID: ");
    scanf("%d", &studentID);
    printf("Enter Book ID: ");
    scanf("%d", &bookID);
    printf("Enter Number of Days Late (0 if returned on time): ");
    scanf("%d", &daysLate);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].bookID == bookID && library[i].isBorrowed == 1) {
            found = 1;
            library[i].isBorrowed = 0;

            if (daysLate > 0) {
                int fine = daysLate * LATE_FINE;
                printf("Fine of Rs. %d Applied.\n", fine);
            }

            for (int j = 0; j < borrowedCount; j++) {
                if (borrowedBooks[j].bookID == bookID && borrowedBooks[j].studentID == studentID) {
                    // Remove the record of the borrowed book
                    borrowedBooks[j] = borrowedBooks[borrowedCount - 1];
                    borrowedCount--;
                    break;
                }
            }

            printf("Book returned successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Book not found or not borrowed.\n");
    }
}

// Function to display all available books in the library
void displayAvailableBooks() {
    printf("List of All Available Books:\n");
    for (int i = 0; i < bookCount; i++) {
        if (library[i].isBorrowed == 0) {
            printf("Book ID: %d, Title: \"%s\", Author: \"%s\"\n", library[i].bookID, library[i].title, library[i].author);
        }
    }
}

// Function to display all borrowed books
void displayBorrowedBooks() {
    printf("List of All Borrowed Books:\n");
    for (int i = 0; i < borrowedCount; i++) {
        for (int j = 0; j < bookCount; j++) {
            if (library[j].bookID == borrowedBooks[i].bookID) {
                printf("Student ID: %d, Borrowed: \"%s\"\n", borrowedBooks[i].studentID, library[j].title);
                break;
            }
        }
    }
}

// Main function to interact with the user
int main() {
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add a Book\n");
        printf("2. Borrow a Book\n");
        printf("3. Return a Book\n");
        printf("4. Generate Reports\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                printf("\n--- Reports ---\n");
                displayAvailableBooks();
                displayBorrowedBooks();
                break;
            case 5:
                printf("Exiting the system.\n");
                return 0;
            default:
                printf("Invalid choice! Please enter again.\n");
        }
    }

    return 0;
}
