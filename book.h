#ifndef BOOK_H
#define BOOK_H

typedef struct book{
    int bookId;
    char name; 
    char author;  
    int year;
    char genre;  
    char resume; 
    int quantity;
}book;
book newBook(
    int pBookId,
    char pName, 
    char pAuthor, 
    int pYear, 
    char pGenre, 
    char pResume){

        book newBook;
        newBook.bookId = pBookId;
        newBook.name = pName;
        newBook.author = pAuthor;
        newBook.year = pYear;
        newBook.genre = pGenre;
        newBook.resume = pResume;
    
        return newBook;
}
#endif 