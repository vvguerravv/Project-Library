#include "app.h"

int alloc_book(book_t *book, int size_name_book) {
    book->book_name = (char*) calloc(size_name_book, sizeof(char));
    book->author = (char*) calloc(256, sizeof(char));
    if (book->book_name == NULL || book->author == NULL) {
        return 0;
    }
    return 1;
}

int alloc_login(reader_t *login) {
    login->email = (char*) malloc(256 * sizeof(char));
    login->password = (char*) malloc(256 * sizeof(char));
    login->user = (char*) malloc(256 * sizeof(char));

    if(login->user == NULL || login->password == NULL || login->email == NULL){
        return 0;
    }
    return 1;
}


void new_login(chainedReader_t **start, reader_t *login)
{

    chainedReader_t *new = (chainedReader_t*) malloc(sizeof(chainedReader_t));
    new->login.email = (char*) malloc(strlen(login->email) + 1);
    new->login.password = (char*) malloc(strlen(login->password) + 1);
    new->login.user = (char*) malloc(strlen(login->user) + 1);

    strcpy(new->login.email,login->email);
    strcpy(new->login.password,login->password);
    strcpy(new->login.user, login->user);
    new->next = NULL;

    if (*start == NULL) {
        *start = new;
    } else {
        chainedReader_t *current = *start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

void new_book(chainedBook_t **start, book_t *book) {
    chainedBook_t *new = (chainedBook_t *)malloc(sizeof(chainedBook_t));
    new->book.book_name = (char*)malloc(strlen(book->book_name) + 1);
    new->book.author = (char*)malloc(strlen(book->author) + 1);

    strcpy(new->book.book_name, book->book_name);
    strcpy(new->book.author, book->author);
    new->book.pages = book->pages;
    new->next = NULL;

    if (*start == NULL) {
        *start = new;
    } else {
        chainedBook_t *current = *start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

bool sigin(chainedReader_t **no,reader_t login)
{
    chainedReader_t *current = *no;
    while (current != NULL){
        if(strcmp(current->login.email, login.email) == 0){
            if(strcmp(current->login.password,login.password) == 0){
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

bool searchBook(chainedBook_t **no, book_t book)
{
    chainedBook_t *current = *no;
    while(current != NULL){
        if(strcmp(current->book.book_name,book.book_name) == 0){
            return true;
        }
        current = current->next;
    }
    return false;
}

void destructBook(book_t *book) {
    if(book->book_name != NULL){
        free(book->book_name);
    }
    if(book->author != NULL){
        free(book->author);
    }
}

void destructReader(reader_t *login) {
    if(login->email != NULL){
        free(login->email);
    }
    if(login->password != NULL){
        free(login->password);
    }
    if(login->user != NULL){
        free(login->user);
    }
}


void destructNodeReader(chainedReader_t *node)
{
    if(node != NULL){
        destructReader(&node->login);
        free(node);
    }
}

void destructNodeBook(chainedBook_t *node)
{
    if(node != NULL){
        destructBook(&node->book);
        free(node);
    }
}