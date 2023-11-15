#ifndef PROJECT_LIBRARY_APP_H
#define PROJECT_LIBRARY_APP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *user;
    char *email;
    char *password;
} reader_t;

typedef struct {
    char *author;
    char *book_name;
    int pages;
} book_t;

typedef struct chainedBook {
    book_t book;
    struct chainedBook *next;
} chainedBook_t;

typedef struct chainedReader{
    reader_t login;
    struct chainedReader *next;
}chainedReader_t;

int alloc_book(book_t *book, int size_name_book);
int alloc_login(reader_t *login);
void new_login(chainedReader_t **start, reader_t *login);
void new_book(chainedBook_t **start, book_t *book);
bool sigin(chainedReader_t **no,reader_t login);
bool searchBook(chainedBook_t **no, book_t book);
void destructBook(book_t *book);
void destructReader(reader_t *login);
void destructNodeReader(chainedReader_t *node);
void destructNodeBook(chainedBook_t *node);




#endif //PROJECT_LIBRARY_APP_H
