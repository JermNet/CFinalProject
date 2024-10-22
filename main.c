#include <stdio.h>
#include "book.c"
#include <stdbool.h>

int main()
{
    int input;

    // Using this to do the loop the more "Java" way so to speak
    while (true)
    {
        printf("\n--- Book Management System ---\n");
        printf("1. Add Book\n2. Delete Book\n3. Search Book\n4. List Books\n5. Save Books\n6. Load Books\n7. Quit\n");
        scanf("%d", &input);
        getchar();

        // Using an if statement because I like that way better
        if (input == 1)
        {
            addBook();
        }
        else if (input == 2)
        {
            deleteBook();
        }
        else if (input == 3)
        {
            searchBook();
        }
        else if (input == 4)
        {
            listBooks();
        }
        else if (input == 5)
        {
            saveBooks();
        }
        else if (input == 6)
        {
            loadBooks();
        }
        else if (input == 7)
        {
            printf("Thank you for using the program!\n");
            break;
        }
        else
        {
            printf("That is not a valid option!\n");
        }
    }

    return 0;
}