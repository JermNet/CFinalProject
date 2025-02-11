# Video covering this project
https://youtu.be/2HE6-TJwt9U

# HOW TO RUN
To run this code, there are two options. You can either run the .exe file or you can run this: "if ($?) { gcc main.c -o main } ; if ($?) { .\main }" command in the directory that main.c is in. There are 5 files included here. book.c is the book manager, it has all the methods needed to manage an array of books (the methods will be gone over in more detail). book.h is the header file for book.c, it has a struct to represent a book and the outlines for the methods implemented in book.c. books.dat is a sample data file with three books that can be loaded using the loadBooks or overwritten with your own saved books with the saveBooks method. main.c is where all the methods are called and can be run as stated earlier. Finally, main.exe complies everything together into an executable file that can be easily run. The last thing of note is to make sure everything is in the same directory together.

# The "checkISBNLength" Method
This is a simple method that is meant to make sure the user inputs an ISBN that is exactly 13 characters long. I originally wasn't going to add this as a method but since I used the code in almost the exact same way twice, it made sense to make as a method.

# The "addBook" Method
This gets inputs from the user for title, author, ISBN and year, puts them into their proper place in the book struct. Then it adds that book to an array, dynamically allocating space with the realloc method and calculating the amount of space needed by multiplying the size of a book by the amount of books in the array.

# The "deleteBook" Method
This is much like the addBook method but with an extra piece. When a book is found to be deleted, it takes the half of the array after the selected book and shifts it with memcpy over the book to be deleted, overwriting it. Then the numOfBooks variable is decreased, and the memory is reallocated once more.

# The "searchBook" Method
Very simple. This lets the user enter a search term and then the method loops through the array to see if it matches a title, author or ISBN of a book (or books) and then returns every book's details that matched in some way.

# The "listBooks" Method
This is even more simple. All it does is loop through the array and print out the details of every book that is in the array.

# The "saveBooks" Method
This method uses the wb (write binary) parameter of the fopen function and the fwrite function to write the numOfBooks variable as well as every book currently in the array to a .dat file named "books.dat." There is also appropriate error handling. 

# The "loadBooks" Method
This method is almost the exact same as the saveBooks method, but it uses rb (read binary) and fread instead to fill in the array with all the data into the array in almost the same way as it was written.