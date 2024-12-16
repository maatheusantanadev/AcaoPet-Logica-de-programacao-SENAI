#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura para representar um animal
typedef struct Animal {
    char idAnimal[15];
    char nomeAnimal[50];
    char idadeAnimal[15];
    char especie[30];
    char cidadeAnimal[50];
    char condicoesAdocao[100];
    struct Animal* prox;
    struct Animal* ant;
} Animal;

// Função para criar um novo animal
Animal* criarAnimalAdocao(char id[], char nome[], char idade[], char especie[], char cidade[], char condicoes[]) {
    Animal* novo = (Animal*)malloc(sizeof(Animal));
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    strcpy(novo->idAnimal, id);
    strcpy(novo->nomeAnimal, nome);
    strcpy(novo->idadeAnimal, idade);
    strcpy(novo->especie, especie);
    strcpy(novo->cidadeAnimal, cidade);
    strcpy(novo->condicoesAdocao, condicoes);
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

// Função para salvar os dados do animal em um arquivo
void salvarAnimal(Animal* animal) {
    FILE* arquivo = fopen("animais.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    fprintf(arquivo, "ID: %s\n", animal->idAnimal);
    fprintf(arquivo, "Nome: %s\n", animal->nomeAnimal);
    fprintf(arquivo, "Idade: %s\n", animal->idadeAnimal);
    fprintf(arquivo, "Espécie: %s\n", animal->especie);
    fprintf(arquivo, "Cidade: %s\n", animal->cidadeAnimal);
    fprintf(arquivo, "Condições de Adoção: %s\n", animal->condicoesAdocao);
    fprintf(arquivo, "-------------------------\n");

    fclose(arquivo);
    printf("\033[1;32m\nAnimal salvo no arquivo com sucesso!\n\033[0m");
}

// Função para cadastrar um novo animal na lista encadeada
void cadastrarAnimal(Animal** inicio, Animal** fim) {
    char idade[15], id[15], nome[50], especie[30], cidade[50], condicoes[100];

    printf("\033[1;32m\nCadastro de Novo Animal:\n\n\033[0m");

    // Leitura do ID
     while (1) {
        printf("\033[1;34mId do Animal: \033[0m");
        fflush(stdin);
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0';

        if (strlen(id) == 0) {
            printf("\033[1;31m\n\nA idade nao pode estar vazia.\n\033[0m");
        } else {
            int valido = 1;
            for (size_t i = 0; i < strlen(id); i++) {
                if (!isdigit((unsigned char)id[i])) {
                    valido = 0;
                    break;
                }
            }
            if (valido) break;
            printf("\033[1;31m\n\nA id deve conter apenas digitos numericos.\n\033[0m");
        }
    }

    // Leitura do Nome
    printf("\033[1;34mNome do Animal: \033[0m");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    // Leitura da Idade
    while (1) {
        printf("\033[1;34mIdade do Animal: \033[0m");
        fgets(idade, sizeof(idade), stdin);
        idade[strcspn(idade, "\n")] = '\0';

        if (strlen(idade) == 0) {
            printf("\033[1;31m\n\nA idade nao pode estar vazia.\n\033[0m");
        }else{
            break;
        }
    }

    // Leitura da Espécie
    printf("\033[1;34mEspecie do Animal: \033[0m");
    fgets(especie, sizeof(especie), stdin);
    especie[strcspn(especie, "\n")] = '\0';

    // Leitura da Cidade
    printf("\033[1;34mCidade do Animal: \033[0m");
    fgets(cidade, sizeof(cidade), stdin);
    cidade[strcspn(cidade, "\n")] = '\0';

    // Leitura das Condições
    printf("\033[1;34mCondicoes de Adocao: \033[0m");
    fgets(condicoes, sizeof(condicoes), stdin);
    condicoes[strcspn(condicoes, "\n")] = '\0';

    // Criação do novo animal
    Animal* novo = criarAnimalAdocao(id, nome, idade, especie, cidade, condicoes);

    // Inserção na lista encadeada
    if (*inicio == NULL) {
        *inicio = novo;
        *fim = novo;
    } else {
        (*fim)->prox = novo;
        novo->ant = *fim;
        *fim = novo;
    }

    // Salvando o animal
    salvarAnimal(novo);
}

// Função para verificar se um ID está no arquivo de adoções
int animalJaAdotado(const char* idAnimal) {
    FILE* arquivoAdocoes = fopen("adocoes.txt", "r");
    if (arquivoAdocoes == NULL) {
        return 0; // Se o arquivo não existir, consideramos que o animal não foi adotado
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivoAdocoes) != NULL) {
        // Procura pela linha que contém "ID do Animal:"
        if (strncmp(linha, "ID do Animal:", 13) == 0) {
            char idAdotado[50];
            sscanf(linha, "ID do Animal: %s", idAdotado); 
            if (strcmp(idAdotado, idAnimal) == 0) {
                fclose(arquivoAdocoes);
                return 1;
            }
        }
    }

    fclose(arquivoAdocoes);
    return 0; // Animal não adotado
}

// Função para ler os dados dos animais do arquivo
void lerAnimais() {
    FILE* arquivo = fopen("animais.txt", "r");
    if (arquivo == NULL) {
        printf("\033[1;31m\nNao ha animais cadastrados!\033[0m\n");
        return;
    }

    char linha[256];
    int exibirAnimal = 0;
    char idAnimal[50];

    printf("\033[1;32m\nAnimais Disponiveis para Adocao:\033[0m\n");
    printf("----------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Verifica se a linha contém "ID:"
        if (strncmp(linha, "ID:", 3) == 0) {
            sscanf(linha, "ID: %s", idAnimal); // Extrai o ID do animal
            exibirAnimal = !animalJaAdotado(idAnimal); // Define se deve exibir o animal
        }

       
        if (exibirAnimal) {
            printf("%s", linha);
        }

        
        if (strncmp(linha, "-------------------------", 25) == 0) {
            exibirAnimal = 0;
        }
    }

    fclose(arquivo);
    printf("----------------------------------------------------\n");
}
