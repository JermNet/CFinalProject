#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "book.h"
// This defines maximum number of books that can be in the array. This isn't required but makes it so c isn't using a crazy amount of memory.
#define TOTAL_BOOKS 500

// This is the pointer so the array can be dynamically allocated
static Book *books = NULL;
// This is the number of books that are in the collection
static int numOfBooks = 0;

// Checks the length of the ISBN
bool checkISBNLength(const char *isbn)
{
    return (strlen(isbn) == 13);
}

void addBook()
{
    // Checks the max books and stops to function if it's true
    if (numOfBooks > TOTAL_BOOKS)
    {
        printf("The book list is full! Please remove some books if you want to add more!\n");
        return;
    }

    // This allocates the memory for a new book using malloc to get a block of memory out of the heap
    Book *book = (Book *)malloc(sizeof(Book));

    // Error handling, ideally this bit of code never runs
    if (book == NULL)
    {
        printf("Memory could not be allocated, please try again!\n");
        return;
    }

    // This gets the user input for the title. "%500[^\n]%*c" reads up to 500 characters, ignoring \n (new line escape sequence) and gets rid of the \n that is left in the input buffer
    // book->title puts the input in said variable in the header struct
    printf("Please enter the title of your book: \n");
    scanf(" %500[^\n]%*c", book->title);

    // This gets the user input for the author
    printf("Please enter the author of your book: \n");
    scanf(" %500[^\n]%*c", book->author);

    // This gets the user input for the ISBN, the input is still 500 because things get weird if it's not and I would have to check if the ISBN was less than 13 anyway
    printf("Please enter the ISBN of your book (should be 13 characters): \n");
    scanf(" %500[^\n]%*c", book->isbn);

    // This calls a function to check if ISBN is the length it should be
    if (!checkISBNLength(book->isbn))
    {
        printf("The ISBN should be exactly 13 characters! Please try again!\n");
        free(book);
        return;
    }

    // This loops through the array to see if the ISBN already exists, canceling the book creation and freeing the memory if that's the case
    for (int i = 0; i < numOfBooks; i++)
    {
        // This uses the strcmp method (string compare) to match the ISBNs
        if (strcmp(books[i].isbn, book->isbn) == 0)
        {
            printf("There is a book with that ISBN already so it has not been added. Please try again.\n");

            // This frees the memory that has been allocated
            free(book);
            return;
        }
    }

    // This gets the user input for the year. Since it is not a char array (which is a pointer) like the others, newBook->year must be prefaced with a "&" to let know it is a pointer
    printf("Please enter the year of your book: \n");
    scanf("%d", &book->year);

    // I originally had getchar under every input but that resulted in the user having to press enter twice after each input so it's like this instead
    while (getchar() != '\n');

    // This resizes the array of books to allow for the new book using the realloc method combined with the sizeof method and the total books + 1 to get the space that is needed
    books = (Book *)realloc(books, (numOfBooks + 1) * sizeof(Book));

    // More error handling. Once again, ideally this code never runs
    if (books == NULL)
    {
        printf("Memory could not be allocated, please try again!\n");

        // This frees the memory that was just created in case something goes awry
        free(book);
        return;
    }

    // This adds the book with all the information the user just entered to the array with the memcpy method
    memcpy(&books[numOfBooks], book, sizeof(Book));

    // Frees the memory that was created earlier now that the book has been copied into the array
    free(book);

    // Increases the number I used as the index for the array so that, the next time the user uses this method, this book is not overwritten
    numOfBooks++;
    printf("Your book has been added!\n");
}

void deleteBook()
{
    // This is one more character than the expected 13 to account for the null terminator character
    char deleteISBN[14];

    // This will be used later for if a book with the matching ISBN is found. The default value is false but this makes it more clear as to what is going on
    bool foundISBN = false;

    // This checks if the books array is empty, not doing anything if it is
    if (numOfBooks == 0)
    {
        printf("There are no books to be deleted!\n");
        return;
    }

    // This gets the user input for the ISBN that is to be deleted
    printf("Please enter the ISBN of the book that you would like to delete: \n");

    // Same as in the add book method
    scanf("%500[^\n]%*c", deleteISBN);
    if (!checkISBNLength(deleteISBN))
    {
        printf("The ISBN should be exactly 13 characters! Please try again!\n");
        return;
    }

    // This loops through the books array, finding the book with a matching ISBN so it can be deleted
    for (int i = 0; i < numOfBooks; i++)
    {

        // This is the same as in the add books method but with deleteISBN instead
        if (strcmp(books[i].isbn, deleteISBN) == 0)
        {

            // This is for later so that it can be told to the user if no ISBN was found
            foundISBN = true;

            // This shifts all of the books after the one that was deleted to the left which overwrites the one that is intended to be deleted
            for (int j = i; j < numOfBooks - 1; j++)
            {
                memcpy(&books[j], &books[j + 1], sizeof(Book));
            }

            // This decreases the number of books now that one has been deleted
            numOfBooks--;

            // This reallocates the memory now that the array has one less element
            books = (Book *)realloc(books, numOfBooks * sizeof(Book));

            // This tells the user that the book as been deleted
            printf("The book with the ISBN %s has been deleted!\n", deleteISBN);
            break;
        }
    }

    // This tells the user that an ISBN was not found if that's the case
    if (!foundISBN)
    {
        printf("There was no book with the ISBN %s found!\n", deleteISBN);
    }
}

void searchBook()
{
    // This is the array for the user's search
    char search[500];

    // Same purpose as deleteBook
    bool foundBook = false;

    // Used so that there's a specific listing of the books when they're displayed
    int currentBookNumber = 1;

    // This gets the user's input for the search
    printf("Please enter your text string to search for a book or books (can be title, author or ISBN): \n");
    scanf("%500[^\n]%*c", search);

    // This loops through the array to get all the books that match what the user typed in some way; very similar in concept to the loop in deleteBook
    for (int i = 0; i < numOfBooks; i++)
    {
        // Checks against what the user entered, can match any one of the three variables
        if (strcmp(books[i].title, search) == 0 || strcmp(books[i].author, search) == 0 || strcmp(books[i].isbn, search) == 0)
        {
            // This prints the information of the book(s)
            printf("Here is book #%d: \n", currentBookNumber);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("ISBN: %s\n", books[i].isbn);
            printf("Year: %d\n", books[i].year);
            printf("\n");
            foundBook = true;
            currentBookNumber ++;
        }
    }

    if (!foundBook)
    {
        printf("No such book exists!\n");
    }
}

void listBooks()
{
    if (numOfBooks == 0)
    {
        printf("There are no books to be listed!\n");
        return;
    }

    // Lists through the books
    for (int i = 0; i < numOfBooks; i++)
    {
        printf("Here is book #%d: \n", i+1);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("ISBN: %s\n", books[i].isbn);
        printf("Year: %d\n", books[i].year);
        printf("\n");
    }
}

void saveBooks()
{
    // wb is write in binary
    FILE *file = fopen("books.dat", "wb");

    // This checks if the file pointer is empty, resulting in the function ending
    if (file == NULL)
    {
        printf("The file could not be opened to write to! Please try again!\n");
    }

    // This writes the numOfBooks variable to the dat file
    fwrite(&numOfBooks, sizeof(int), 1, file);

    // This loops through the array and writes each book to the dat file
    for (int i = 0; i < numOfBooks; i++)
    {
        fwrite(&books[i], sizeof(Book), 1, file);
    }

    // This closes the file (not required but good practice)
    fclose(file);

    // This tells the user that everything worked
    printf("The books and/or number of books have been written to books.dat!\n");
}

void loadBooks()
{
    // rb is read from binary
    FILE *file = fopen("books.dat", "rb");

    // This is the same as saveBooks
    if (file == NULL)
    {
        printf("The file could not be opened to read from! Please try again!\n");
        return;
    }

    // This reads the number of books
    fread(&numOfBooks, sizeof(int), 1, file);

    // Allocates the memory and checks if it worked
    books = (Book *)malloc(numOfBooks * sizeof(Book));
    if (books == NULL)
    {
        printf("Memory could not be allocated, please try again!\n");
        fclose(file);
        return;
    }

    // This reads the books from the file and puts them in the array
    fread(books, sizeof(Book), numOfBooks, file);
    fclose(file);
    printf("The books have been read from books.dat!\n");
}