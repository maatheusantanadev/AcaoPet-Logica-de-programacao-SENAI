#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um animal
typedef struct Animal {
    int idAnimal;
    char nomeAnimal[50];
    int idadeAnimal;
    char especie[30];
    char cidadeAnimal[50];
    char condicoesAdocao[100];
    struct Animal* prox;
    struct Animal* ant;
} Animal;

// Função para criar um novo animal
Animal* criarAnimalAdocao(int id, char nome[], int idade, char especie[], char cidade[], char condicoes[]) {
    Animal* novo = (Animal*)malloc(sizeof(Animal));
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    novo->idAnimal = id;
    strcpy(novo->nomeAnimal, nome);
    novo->idadeAnimal = idade;
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

    fprintf(arquivo, "ID: %d\n", animal->idAnimal);
    fprintf(arquivo, "Nome: %s\n", animal->nomeAnimal);
    fprintf(arquivo, "Idade: %d\n", animal->idadeAnimal);
    fprintf(arquivo, "Especie: %s\n", animal->especie);
    fprintf(arquivo, "Cidade: %s\n", animal->cidadeAnimal);
    fprintf(arquivo, "Condicoes de Adocao: %s\n", animal->condicoesAdocao);
    fprintf(arquivo, "-------------------------\n");

    fclose(arquivo);
    printf("\033[1;32m\nAnimal salvo no arquivo com sucesso!\n\033[0m");
}

// Função para cadastrar um novo animal na lista encadeada
void cadastrarAnimal(Animal** inicio, Animal** fim) {
    int id, idade;
    char nome[50], especie[30], cidade[50], condicoes[100];

    printf("\033[1;32m\nCadastro de Novo Animal:\n\n\033[0m");

    printf("\033[1;34mID do Animal: ");
    scanf("%d", &id);
    getchar();

    printf("Nome do Animal: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Idade do Animal: ");
    scanf("%d", &idade);
    getchar();

    printf("Especie do Animal: ");
    fgets(especie, sizeof(especie), stdin);
    especie[strcspn(especie, "\n")] = '\0';

    printf("Cidade do Animal: ");
    fgets(cidade, sizeof(cidade), stdin);
    cidade[strcspn(cidade, "\n")] = '\0';

    printf("Condicoes de Adocao: ");
    fgets(condicoes, sizeof(condicoes), stdin);
    condicoes[strcspn(condicoes, "\n")] = '\0';

    Animal* novo = criarAnimalAdocao(id, nome, idade, especie, cidade, condicoes);

    if (*inicio == NULL) { 
        *inicio = novo;
        *fim = novo;
    } else { 
        (*fim)->prox = novo;
        novo->ant = *fim;
        *fim = novo;
    }

    salvarAnimal(novo); 
}

// Função para ler os dados dos animais do arquivo
void lerAnimais() {
    FILE* arquivo = fopen("animais.txt", "r");
    if (arquivo == NULL) {
        printf("\033[1;31m\nNao ha animais cadastrados!\033[0m\n");
        return;
    }

    char linha[256];
    printf("\033[1;32m\nAnimais Registrados:\033[0m\n");
    printf("----------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
    printf("----------------------------------------------------\n");
}
