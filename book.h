#ifndef BOOK_H
#define BOOK_H

typedef struct book{
    int bookId;
    char* name; 
    char* author;  
    int year;
    char* genre;  
    char* resume; 
    int quantity;
}book;

book newBookFromArray(char** atributeArray){
    book newBook; 
    newBook.name = atributeArray[0];
    newBook.author = atributeArray[1];
    int year = atoi(atributeArray[2]);
    newBook.year = year;
    newBook.genre = atributeArray[3];
    newBook.resume = atributeArray[4];
    newBook.quantity = atoi(atributeArray[5]);
    
    return newBook;
}
#endif 