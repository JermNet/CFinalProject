// Header file for a book that will be implemented in book.c
#ifndef BOOK_H
#define BOOK_H

typedef struct
{
    char title[256];
    char author[100];
    char isbn[13];
    int year;

} Book;

void addBook();
void deleteBook();
void searchBook();
void listBooks();
void saveBooks();
void loadBooks();

#endif