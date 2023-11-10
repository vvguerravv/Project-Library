#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct chainedBook_t {
    book_t book;
    struct chainedBook_t *next;
} chainedBook_t;

typedef struct chainedReader_t{
    reader_t login;
    struct chainedReader_t *next;
}chainedReader_t;

int alloc_book(book_t *book, int size_name_book) {
    book->book_name = (char*) calloc(size_name_book, sizeof(char));
    book->author = (char*) calloc(256, sizeof(char));
    if (book->book_name == NULL || book->author == NULL) {
        return 0;
    }
    return 1;
}

int alloc_login(reader_t *login)
{
    login->email = (char*) malloc(sizeof(char));
    login->password = (char*) malloc(sizeof(char));
    login->user = (char*) malloc(sizeof(char));

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

int main() {
    chainedBook_t *library = NULL;
    book_t book;
    chainedReader_t *account;
    reader_t login;
    int escolha = 1;



    while (escolha != 0) {
        printf("Digite 1 para fazer login!\nDigite 2 para cadastrar um livro!\nDigite 3 para criar uma conta!\nDigite 4 para procurar um livro!\n"
               "Digite 5 para visualizar os livros na biblioteca!\nDigite 0 para sair!\n");
        scanf("%d", &escolha);
        getchar();

        switch (escolha) {
            case 1:

                break;

            case 2:
                if (!alloc_book(&book, 256)) {
                    printf("Erro para ler o nome!!\n");
                    return 1;
                }

                printf("Digite o nome do livro: ");
                fgets(book.book_name, 255, stdin);
                book.book_name[strcspn(book.book_name, "\n")] = '\0';
                printf("Digite o nome do autor: ");
                fgets(book.author, 255, stdin);
                book.author[strcspn(book.author, "\n")] = '\0';
                printf("Digite o número de páginas: ");
                scanf("%d", &book.pages);
                getchar();
                new_book(&library, &book);
                break;

            case 3:
                if(!alloc_login(&login)){
                    printf("Erro de memória\n");
                    return 1;
                }
                printf("Digite seu email: ");
                fgets(login.email,255,stdin);
                login.email[strcspn(login.email,"\n")] = '\0';
                printf("Digite o nome de usuário: ");
                fgets(login.user,255,stdin);
                login.user[strcspn(login.user,"\n")] = '\0';
                printf(("Digite sua senha: "));
                fgets(login.password,255,stdin);
                login.password[strcspn(login.password,"\n")] = '\0';
                new_login(&account,&login);

                break;

            case 4:

                break;

            case 5:


            case 0:

                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }


    chainedBook_t *current = library;
    while (current != NULL) {
        printf("Nome: %s\n", current->book.book_name);
        printf("Autor: %s\n", current->book.author);
        printf("Páginas: %d\n", current->book.pages);
        current = current->next;
    }

    current = library;
    while (current != NULL) {
        chainedBook_t *temp = current;
        current = current->next;
        free(temp->book.book_name);
        free(temp->book.author);
        free(temp);
    }

    return 0;
}
