
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Estrutura para representar um animal desaparecido
typedef struct AnimalDesaparecido {
    char nomeAnimal[50];
    char idadeAnimal[20];
    char especieAnimal[20];
    char detalhesDesaparecimento[200];
    struct AnimalDesaparecido* prox;
    struct AnimalDesaparecido* ant;
} AnimalDesaparecido;

// Função para criar um novo nó
AnimalDesaparecido* criarAnimal(char nome[], char idade[], char especie[], char detalhes[]) {
    AnimalDesaparecido* novo = (AnimalDesaparecido*)malloc(sizeof(AnimalDesaparecido));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(novo->nomeAnimal, nome);
    strcpy(novo->idadeAnimal, idade);
    strcpy(novo->especieAnimal, especie);
    strcpy(novo->detalhesDesaparecimento, detalhes);
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

// Função para salvar os dados do animal em um arquivo
void salvarAnimalNoArquivo(AnimalDesaparecido* animal) {
    FILE* arquivo = fopen("animais_desaparecidos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    fprintf(arquivo, "Nome: %s\n", animal->nomeAnimal);
    fprintf(arquivo, "Idade: %s\n", animal->idadeAnimal);
    fprintf(arquivo, "Especie: %s\n", animal->especieAnimal);
    fprintf(arquivo, "Detalhes: %s\n", animal->detalhesDesaparecimento);
    fprintf(arquivo, "-------------------------\n");

    fclose(arquivo);
    printf("\033[1;32m\nAnimal salvo no arquivo com sucesso!\n\033[0m");
}

// Função para cadastrar um novo animal desaparecido na lista encadeada
void desaparecimentoAnimal(AnimalDesaparecido** inicio, AnimalDesaparecido** fim) {
    char nome[50], especie[20], detalhes[200], idade[30];

    printf("\033[1;32m\nCadastro de Animal Desaparecido\n\n\033[0m");

    // Garantindo que o buffer de entrada seja limpo
    getchar();  // Limpar o buffer de entrada

    // Usando fgets para ler strings com espaços
    printf("\033[1;34mNome do Animal: \033[0m");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;  // Remover o caractere de nova linha

    printf("\033[1;34mIdade do Animal: \033[0m");
    fgets(idade, sizeof(idade), stdin);
    idade[strcspn(idade, "\n")] = 0;  // Remover o caractere de nova linha

    printf("\033[1;34mEspecie do Animal: \033[0m");
    fgets(especie, sizeof(especie), stdin);
    especie[strcspn(especie, "\n")] = 0;  // Remover o caractere de nova linha

    printf("\033[1;34mDetalhes do desaparecimento: \033[0m");
    fgets(detalhes, sizeof(detalhes), stdin);
    detalhes[strcspn(detalhes, "\n")] = 0;  // Remover o caractere de nova linha

    AnimalDesaparecido* novo = criarAnimal(nome, idade, especie, detalhes);

    if (*inicio == NULL) { 
        *inicio = novo;
        *fim = novo;
    } else { 
        (*fim)->prox = novo;
        novo->ant = *fim;
        *fim = novo;
    }

    salvarAnimalNoArquivo(novo); 
}

void lerAnimaisDoArquivo() {
    FILE* arquivo = fopen("animais_desaparecidos.txt", "r");
    if (arquivo == NULL) {
        printf("\033[1;31m\nNao ha animais desaparecidos!\033[0m\n");
        return;
    }

    char linha[256];
    printf("\033[1;33m\nAnimais Desaparecidos Registrados:\033[0m\n");
    printf("----------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
    printf("----------------------------------------------------\n");
}