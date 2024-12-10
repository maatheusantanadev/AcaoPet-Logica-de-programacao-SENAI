
#include <stdio.h>
#include <string.h>
#include <sys/stat.h> // Para obter informações do arquivo
#include <time.h>     // Para lidar com timestamps
#include <unistd.h>   // Para função sleep (no Windows use Sleep)
#define MAX_USUARIOS 50
#define MAX_ANIMAIS 50
#define MAX_ADOCOES 50

typedef struct {
    char nomeUsuario[50];
    char email[50];
    char senha[50];
    char cpf[15];
    char rua[50];
    char bairro[50];
    char cidadeUsuario[50];
} InformacaoDeUsuario;

typedef struct {
    int idAnimal;
    char nome[50];
    int idade;
    char especie[30];
    char cidade[50];
    char condicoes[100];
} InformacaoDeAnimal;

typedef struct {
    char cpfUsuario[15];
    int idAnimal;
} Adocao;

// Função para carregar os usuários do arquivo
int carregarUsuarios(InformacaoDeUsuario usuarios[]) {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return 0;
    }

    int count = 0;
    char linha[150];

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "Nome: ")) {
            sscanf(linha, "Nome: %[^\n]", usuarios[count].nomeUsuario);
        } else if (strstr(linha, "Email: ")) {
            sscanf(linha, "Email: %[^\n]", usuarios[count].email);
        } else if (strstr(linha, "Senha: ")) {
            sscanf(linha, "Senha: %[^\n]", usuarios[count].senha);
        } else if (strstr(linha, "CPF: ")) {
            sscanf(linha, "CPF: %[^\n]", usuarios[count].cpf);
        } else if (strstr(linha, "Rua: ")) {
            sscanf(linha, "Rua: %[^\n]", usuarios[count].rua);
        } else if (strstr(linha, "Bairro: ")) {
            sscanf(linha, "Bairro: %[^\n]", usuarios[count].bairro);
        } else if (strstr(linha, "Cidade: ")) {
            sscanf(linha, "Cidade: %[^\n]", usuarios[count].cidadeUsuario);
        } else if (strstr(linha, "-------------------------")) {
            count++; // Usuário completo, incrementa o índice
        }
    }

    fclose(arquivo);
    return count;
}

// Função para carregar os animais do arquivo
int carregarAnimais(InformacaoDeAnimal animais[]) {
    FILE *arquivo = fopen("animais.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de animais.\n");
        return 0;
    }

    int count = 0;
    char linha[150];

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "ID: ")) {
            sscanf(linha, "ID: %d", &animais[count].idAnimal);
        } else if (strstr(linha, "Nome: ")) {
            sscanf(linha, "Nome: %[^\n]", animais[count].nome);
        } else if (strstr(linha, "Idade: ")) {
            sscanf(linha, "Idade: %d", &animais[count].idade);
        } else if (strstr(linha, "Especie: ")) {
            sscanf(linha, "Especie: %[^\n]", animais[count].especie);
        } else if (strstr(linha, "Cidade: ")) {
            sscanf(linha, "Cidade: %[^\n]", animais[count].cidade);
        } else if (strstr(linha, "Condicoes de Adocao: ")) {
            sscanf(linha, "Condicoes de Adocao: %[^\n]", animais[count].condicoes);
        } else if (strstr(linha, "-------------------------")) {
            count++; // Animal completo, incrementa o índice
        }
    }

    fclose(arquivo);
    return count;
}

// Função para verificar o CPF
int verificarUsuario(char cpf[], InformacaoDeUsuario usuarios[], int numUsuarios, InformacaoDeUsuario *usuarioEncontrado) {
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            *usuarioEncontrado = usuarios[i];
            return 1;
        }
    }
    return 0;
}

// Função para verificar o ID do animal
int verificarAnimal(int id, InformacaoDeAnimal animais[], int numAnimais, InformacaoDeAnimal *animalEncontrado) {
    for (int i = 0; i < numAnimais; i++) {
        printf("Comparando ID: %d com %d\n", id, animais[i].idAnimal); // Debug
        if (animais[i].idAnimal == id) {
            *animalEncontrado = animais[i];
            return 1;
        }
    }
    return 0;
}

// Função para salvar a adoção em um arquivo
void salvarAdocao(Adocao adocao) {
    FILE *arquivo = fopen("adocoes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de adocoes.\n");
        return;
    }

    fprintf(arquivo, "CPF do Usuário: %s\n", adocao.cpfUsuario);
    fprintf(arquivo, "ID do Animal: %d\n", adocao.idAnimal);
    fprintf(arquivo, "-------------------------\n");

    fclose(arquivo);
}


// Função para ler as adoções registradas no arquivo e exibir os dados
void lerAdocoes(InformacaoDeUsuario usuarios[], int numUsuarios, InformacaoDeAnimal animais[], int numAnimais) {
    FILE *arquivo = fopen("adocoes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de adoções.\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "CPF do Usuário: ")) {
            char cpfUsuario[15];
            sscanf(linha, "CPF do Usuário: %[^\n]", cpfUsuario);

            int idAnimal;
            fgets(linha, sizeof(linha), arquivo);
            sscanf(linha, "ID do Animal: %d", &idAnimal);

            // Verifica o usuário e o animal
            InformacaoDeUsuario usuarioEncontrado;
            if (!verificarUsuario(cpfUsuario, usuarios, numUsuarios, &usuarioEncontrado)) {
                printf("Usuário não encontrado: %s\n", cpfUsuario);
                continue;
            }

            InformacaoDeAnimal animalEncontrado;
            if (!verificarAnimal(idAnimal, animais, numAnimais, &animalEncontrado)) {
                printf("Animal não encontrado: %d\n", idAnimal);
                continue;
            }

            // Exibe os dados
            printf("\n=== Dados da Adoção ===\n");
            printf("CPF do Usuário: %s\n", cpfUsuario);
            printf("ID do Animal: %d\n", idAnimal);

            printf("\n=== Dados do Usuário ===\n");
            printf("Nome: %s\n", usuarioEncontrado.nomeUsuario);
            printf("CPF: %s\n", usuarioEncontrado.cpf);
            printf("Email: %s\n", usuarioEncontrado.email);

            printf("\n=== Dados do Animal ===\n");
            printf("ID: %d\n", animalEncontrado.idAnimal);
            printf("Nome: %s\n", animalEncontrado.nome);
            printf("Espécie: %s\n", animalEncontrado.especie);
            printf("Condições: %s\n", animalEncontrado.condicoes);
            printf("-------------------------\n");
        }
    }

    fclose(arquivo);
}


// Função para realizar a adoção
void realizarAdocao() {
    InformacaoDeUsuario usuarios[MAX_USUARIOS];
    InformacaoDeAnimal animais[MAX_ANIMAIS];
    InformacaoDeUsuario usuarioEncontrado;
    InformacaoDeAnimal animalEncontrado;
    Adocao adocao;

    int numUsuarios = carregarUsuarios(usuarios);
    int numAnimais = carregarAnimais(animais);

    if (numUsuarios == 0 || numAnimais == 0) {
        printf("Nao foi possivel carregar os dados necessarios.\n");
        return;
    }

    printf("=== Sistema de Adocao ===\n");

    char cpf[15];
    printf("Digite o CPF do usuario: ");
    scanf("%s", cpf);

    if (!verificarUsuario(cpf, usuarios, numUsuarios, &usuarioEncontrado)) {
        printf("Usuario nao encontrado.\n");
        return;
    }

    int idAnimal;
    printf("Digite o ID do animal: ");
    scanf("%d", &idAnimal);

    if (!verificarAnimal(idAnimal, animais, numAnimais, &animalEncontrado)) {
        printf("Animal nao encontrado.\n");
        return;
    }

    // Preencher os dados da adoção
    strcpy(adocao.cpfUsuario, cpf);
    adocao.idAnimal = idAnimal;

    // Salvar a adoção
    salvarAdocao(adocao);

    // Confirmação da adoção
    printf("\nAdocao realizada com sucesso!\n");
    printf("=== Dados do Usuario ===\n");
    printf("Nome: %s\n", usuarioEncontrado.nomeUsuario);
    printf("CPF: %s\n", usuarioEncontrado.cpf);

    printf("\n=== Dados do Animal ===\n");
    printf("ID: %d\n", animalEncontrado.idAnimal);
    printf("Nome: %s\n", animalEncontrado.nome);
    printf("Especie: %s\n", animalEncontrado.especie);
    printf("Condicoes: %s\n", animalEncontrado.condicoes);
}