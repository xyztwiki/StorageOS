#include "logical.c"
#include "terrain.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50

// Structure to represent a book
typedef struct {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int year;
    int pages;
} Book;

// Structure to represent a trilogy
typedef struct {
    char series_name[MAX_TITLE_LENGTH];
    Book books[3];
} Trilogy;

// Function to initialize a book
void init_book(Book* book, const char* title, const char* author, int year, int pages) {
    strncpy(book->title, title, MAX_TITLE_LENGTH - 1);
    book->title[MAX_TITLE_LENGTH - 1] = '\0';
    strncpy(book->author, author, MAX_AUTHOR_LENGTH - 1);
    book->author[MAX_AUTHOR_LENGTH - 1] = '\0';
    book->year = year;
    book->pages = pages;
}

// Function to initialize a trilogy
void init_trilogy(Trilogy* trilogy, const char* series_name) {
    strncpy(trilogy->series_name, series_name, MAX_TITLE_LENGTH - 1);
    trilogy->series_name[MAX_TITLE_LENGTH - 1] = '\0';
}

// Function to add a book to the trilogy
void add_book_to_trilogy(Trilogy* trilogy, int index, const Book* book) {
    if (index >= 0 && index < 3) {
        trilogy->books[index] = *book;
    } else {
        printf("Error: Invalid book index for trilogy.\n");
    }
}

// Function to display a book's information
void display_book(const Book* book) {
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("Year: %d\n", book->year);
    printf("Pages: %d\n", book->pages);
}

// Function to display the entire trilogy
void display_trilogy(const Trilogy* trilogy) {
    printf("Trilogy: %s\n", trilogy->series_name);
    for (int i = 0; i < 3; i++) {
        printf("Book %d:\n", i + 1);
        display_book(&trilogy->books[i]);
        printf("\n");
    }
}

