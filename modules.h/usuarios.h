#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Estrutura para representar um usuário
typedef struct Usuario {
    char nomeUsuario[50];
    char email[50];
    char senha[20];
    char cpf[15];
    char rua[50];
    char bairro[30];
    char cidadeUsuario[30];
    int isAdmin;
    struct Usuario* prox;
    struct Usuario* ant;
} Usuario;

// Função para criar um novo usuário
Usuario* criarUsuario(char nome[], char email[], char senha[], char cpf[], char rua[], char bairro[], char cidade[]) {
    Usuario* novo = (Usuario*)malloc(sizeof(Usuario));
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    strcpy(novo->nomeUsuario, nome);
    strcpy(novo->email, email);
    strcpy(novo->senha, senha);
    strcpy(novo->cpf, cpf);
    strcpy(novo->rua, rua);
    strcpy(novo->bairro, bairro);
    strcpy(novo->cidadeUsuario, cidade);
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

// Função para salvar os dados do usuário em um arquivo
void salvarUsuarioNoArquivo(Usuario* usuario) {
    FILE* arquivo = fopen("usuarios.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    fprintf(arquivo, "Nome: %s\n", usuario->nomeUsuario);
    fprintf(arquivo, "Email: %s\n", usuario->email);
    fprintf(arquivo, "Senha: %s\n", usuario->senha);
    fprintf(arquivo, "CPF: %s\n", usuario->cpf);
    fprintf(arquivo, "Rua: %s\n", usuario->rua);
    fprintf(arquivo, "Bairro: %s\n", usuario->bairro);
    fprintf(arquivo, "Cidade: %s\n", usuario->cidadeUsuario);
    fprintf(arquivo, "-------------------------\n");

    fclose(arquivo);
    printf("\033[1;32m\nUsuario salvo no arquivo com sucesso!\n\033[0m");
}

// Função para cadastrar um novo usuário na lista encadeada
void cadastrarUsuario(Usuario** inicio, Usuario** fim) {
    char nome[50], email[50], senha[20], cpf[15], rua[50], bairro[30], cidade[30];
    int tamanhoMax = 20;   

    printf("\033[1;32m\nCadastro de Novo Usuario:\n\n\033[0m");


    fflush(stdin);  



    printf("\033[1;34mNome do Usuario: \033[0m");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;  

    printf("\033[1;34mEmail do Usuario: \033[0m");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    while (1) {
        printf("\033[1;34mSenha do Usuario (deve conter 8 digitos): \033[0m");
        int i = 0;
        while (1) {
            char ch = getch(); // Captura o caractere sem exibi-lo
            if (ch == 13) { // Enter pressionado
                senha[i] = '\0'; // Finaliza a string
                break;
            } else if (ch == 8 && i > 0) { // Backspace pressionado
                i--;
                printf("\b \b"); // Remove o último caractere exibido
            } else if (i < tamanhoMax - 1) { // Limite de caracteres
                senha[i] = ch;
                i++;
                printf("*"); // Exibe um asterisco
            }
        }
        
        printf("\n");

        // Valida o tamanho da senha
        if (strlen(senha) < 8) {
            printf("\033[1;31m\nA senha deve conter pelo menos 8 caracteres.\n\033[0m");
        
        }else{
        senha[strcspn(senha, "\n")] = 0;
        break;
        }
    }    
    
   
    while(1){
    printf("\033[1;34mCPF do Usuario: \033[0m");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    if (strlen(cpf) != 11) {
        printf("\033[1;31m\n\nO CPF deve conter exatamente 11 digitos.\n\033[0m");
    }else{
    // Garantir que todos os caracteres sejam números
            int valido = 1;
            for (int i = 0; i < 11; i++) {
                if (cpf[i] < '0' || cpf[i] > '9') {
                    valido = 0;
                    break;
                }
            }
            if (valido) {
                break;  // CPF válido, sai do loop
            } else {
                printf("\033[1;31m\n\nO CPF deve conter apenas digitos numericos.\n\033[0m");
            }
        }
    }

    printf("\033[1;34mRua: \033[0m");
    fgets(rua, sizeof(rua), stdin);
    rua[strcspn(rua, "\n")] = 0;

    printf("\033[1;34mBairro: \033[0m");
    fgets(bairro, sizeof(bairro), stdin);
    bairro[strcspn(bairro, "\n")] = 0;

    printf("\033[1;34mCidade: \033[0m");
    fgets(cidade, sizeof(cidade), stdin);
    cidade[strcspn(cidade, "\n")] = 0;

    Usuario* novo = criarUsuario(nome, email, senha, cpf, rua, bairro, cidade);

    if (*inicio == NULL) { 
        *inicio = novo;
        *fim = novo;
    } else { 
        (*fim)->prox = novo;
        novo->ant = *fim;
        *fim = novo;
    }

    salvarUsuarioNoArquivo(novo); 
}

// Função para ler os dados dos usuários do arquivo
void lerUsuariosDoArquivo() {
    FILE* arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("\033[1;31m\nNao ha usuarios cadastrados!\033[0m\n");
        return;
    }

    char linha[256];
    printf("\033[1;32m\nUsuarios Registrados:\033[0m\n");
    printf("----------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
    printf("----------------------------------------------------\n");
}