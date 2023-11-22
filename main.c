#include "app.c"

int main() {
    chainedBook_t *library = NULL;
    book_t book;
    chainedReader_t *account = NULL;
    reader_t login;
    int escolha = 1;


    printf("📕Bem vindo a Guerra's Library!📕\nO que vamos fazer hoje?\n");
    printf("====================\n");

    while (escolha != 0) {
        printf("Digite 1 para fazer login!\nDigite 2 para cadastrar um livro!\nDigite 3 para criar uma conta!\nDigite 4 para procurar um livro!\n"
               "Digite 5 para visualizar os livros na biblioteca!\nDigite 0 para sair!\n");
        scanf("%d", &escolha);
        getchar();

        printf("====================\n");
        switch (escolha) {
            case 1:
                if (account == NULL) {
                    printf("Para fazer login, por favor, crie uma conta!!\n");
                } else {
                    printf("Digite seu email: ");
                    fgets(login.email, 255, stdin);
                    login.email[strcspn(login.email, "\n")] = '\0';
                    printf("Digite sua senha: ");
                    fgets(login.password, 255, stdin);
                    while (1) {
                        login.password[strcspn(login.password, "\n")] = '\0';

                        if (!sigin(&account, login)) {
                            if (strcmp(account->login.email, login.email) != 0) {
                                printf("Email não encontrado. Digite novamente seus dados ou crie uma conta!\n");
                                break;
                            } else if (strcmp(account->login.password, login.password) != 0) {
                                printf("Senha incorreta, digite novamente!\n");
                                printf("Digite sua senha: ");
                                fgets(login.password, 255, stdin);
                                continue;
                            }
                        } else {
                            printf("Login efetuado com sucesso!!\n");
                            printf("====================\n");
                            break;
                        }
                    }
                }
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
                printf("====================\n");
                break;

            case 3:
                if (!alloc_login(&login)) {
                    printf("Erro de memória\n");
                    return 1;
                }
                FILE *arq = fopen("logins.txt","a");
                if(arq == NULL){
                    printf("Não foi possível abrir o arquivo para salvar o login!!\n");
                }


                printf("Digite seu email: ");
                fgets(login.email, 255, stdin);
                login.email[strcspn(login.email, "\n")] = '\0';
                chainedReader_t *current1 = account;
                while(current1 != NULL){
                    if(strcmp(current1->login.email,login.email) == 0){
                        printf("Email já cadastrado, selecione outro: ");
                        fgets(login.email, 255, stdin);
                        login.email[strcspn(login.email, "\n")] = '\0';
                        current1 = account;
                    } else{
                        current1 = current1->next;
                    }
                }
                printf("Digite o nome de usuário: ");
                fgets(login.user, 255, stdin);
                login.user[strcspn(login.user, "\n")] = '\0';
                chainedReader_t *current2 = account;
                while (current2 != NULL) {
                    if (strcmp(current2->login.user, login.user) == 0) {
                        printf("Usuário já existe, selecione outro: ");
                        fgets(login.user, 255, stdin);
                        login.user[strcspn(login.user, "\n")] = '\0';
                        current2 = account;
                    } else {
                        current2 = current2->next;
                    }
                }

                printf(("Digite sua senha: "));
                fgets(login.password, 255, stdin);
                login.password[strcspn(login.password, "\n")] = '\0';
                new_login(&account, &login);
                fprintf(arq,"%s %s\n",login.email,login.password);
                printf("====================\n");
                break;

            case 4:
                printf("Digite o nome do livro (ex: As crônicas de Nárnia): ");
                fgets(book.book_name, 255, stdin);
                book.book_name[strcspn(book.book_name, "\n")] = '\0';

                if (!searchBook(&library, book)) {
                    printf("O livro não está contido na biblioteca, por favor, procure por outro livro!!\n");
                    printf("====================\n");
                } else {

                    int esc = 0;

                    while (esc != 3) {
                        printf("O que você deseja fazer com o livro \"%s\":\n1- Abrir o livro\n2 - Verificar informações do livro"
                               "(Nome do autor e número de páginas)\n3 - Sair da busca de livros\n", book.book_name);
                        scanf("%d", &esc);
                        switch (esc) {
                            case 1: {
                                printf("O livro foi aberto!!\n");
                                int i = 1;
                                char action[3] = {};
                                getchar();

                                while (strcasecmp(action, "S\n") != 0) {
                                    printf("Pressione \"P\" para ir para a próxima página, \"A\" para voltar uma página"
                                           " ou \"S\" para fechar o livro\n");

                                    fgets(action, sizeof(action), stdin);

                                    if (strcasecmp(action, "P\n") == 0) {
                                        i++;
                                        printf("Página %d\n", i);
                                    } else if (strcasecmp(action, "A\n") == 0) {
                                        if (i == 1) {
                                            char temp[5];
                                            printf("Tem certeza de que deseja fechar o livro? (Sim ou Não) ");
                                            fgets(temp, sizeof(temp), stdin);

                                            if (strcasecmp(temp, "Sim\n") == 0) {
                                                break;
                                            } else if (strcasecmp(temp, "Nao\n") == 0) {
                                            } else {
                                                printf("Digite uma opção válida!!\n");
                                            }
                                        } else {
                                            i--;
                                            printf("Página: %d\n", i);
                                        }
                                    } else if (strcasecmp(action, "S\n") == 0) {
                                        esc = 0;
                                        break;
                                    } else {
                                        printf("Digite uma opção válida!!\n");
                                    }
                                }
                                printf("====================\n");
                                break;
                            }


                            case 2:
                                printf("Nome do autor: %s\n", book.author);
                                printf("Número de páginas: %d\n", book.pages);
                                esc = 1;
                                printf("====================\n");
                                break;

                            default:
                                printf("Opção inválida. Tente novamente.\n");
                                esc = 1;
                                printf("====================\n");
                                break;
                            case 3:
                                printf("====================\n");
                                break;
                        }
                    }
                }
                break;
            case 5:
                printf("Livros disponíveis:\n");
                int i = 1;
                chainedBook_t *current = library;
                while (current != NULL){
                    printf("%d - Nome do livro: %s\tNome do autor: %s\tNúmero de páginas: %d\n",i,current->book.book_name,current->book.author,current->book.pages);
                    current = current->next;
                    i++;
                }
                printf("====================\n");
                break;

            case 0:
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                printf("====================\n");
        }
        printf("\n");
    }

    printf("📕Obrigado por usar o sistema!Volte sempre e até logo!📕\n");
    destructNodeReader(account);
    destructNodeBook(library);

    return 0;
}
