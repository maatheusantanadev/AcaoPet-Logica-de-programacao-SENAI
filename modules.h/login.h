#include <stdio.h>
#include <string.h>
#include <conio.h>


int login(Usuario* usuario) {         
    char email[100], senha[50];
    FILE* arquivo;
    int opcao;

    while (1) {

        printf("\033[1;34m=====================================\n");  // Azul para a borda
        printf("      \033[1;32mBem-vindo ao AcaoPet!\033[1;34m\n");  // Verde para o título
        printf("=====================================\n");
        printf("\033[1;33m1. Login\n");  // Amarelo para a opção Login
        printf("2. Cadastro\n");
        printf("\033[1;34m=====================================\n");  // Azul novamente para a borda
        printf("\033[1;32mEscolha uma opcao: \033[0m");  // Branco para o texto de entrada
        
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
        case 1:
                system("cls");
                printf("\033[1;34m=====================================\n"); // Azul para a borda superior
                printf("      \033[1;32mLogin no AcaoPet!\033[1;34m\n");    // Verde para o título
                printf("=====================================\n");
                printf("\033[1;33m- Por favor, insira suas credenciais para continuar -\033[0m\n"); // Amarelo para instruções
                printf("\033[1;34m=====================================\n"); // Azul novamente

                printf("\033[1;36m\nDigite seu e-mail: \033[0m"); // Ciano para o prompt de entrada
                scanf("%s", email);

                printf("\033[1;36m\nDigite sua senha: \033[0m"); // Ciano novamente

                
                int i = 0;
                while (1) {
                    char ch = getch();
                    if (ch == 13) {
                        senha[i] = '\0';
                        break;
                    } else if (ch == 8 && i > 0) {
                        i--;
                        printf("\b \b");
                    } else {
                        senha[i] = ch;
                        i++;
                        printf("*");
                    }
                }

                 if (strlen(senha) < 8) {
                    printf("\033[1;31m\n\nA senha deve conter pelo menos 8 digitos.\n\033[0m");
                    Sleep(2000);
                    system("cls");
                    continue;
                }

                if (strcmp(email, "admin@pet.com") == 0 && strcmp(senha, "admin123") == 0) {
                        usuario->isAdmin = 1; // Administrador
                        printf("\033[1;32m\n\nLogin realizado com sucesso como Administrador!\n\033[0m");
                        return opcao = 0;
                } 
                

                // Abrir o arquivo para leitura
                arquivo = fopen("usuarios.txt", "r");
                if (arquivo == NULL) {
                    printf("\nErro ao abrir o arquivo de usuarios.\n");
                }

                char nomeArquivo[50], emailArquivo[100], senhaArquivo[50], cpfArquivo[20];
                char ruaArquivo[50], bairroArquivo[30], cidadeArquivo[30];
                int encontrou = 0;

                while (fscanf(arquivo, "Nome: %[^\n]\nEmail: %[^\n]\nSenha: %[^\n]\nCPF: %[^\n]\nRua: %[^\n]\nBairro: %[^\n]\nCidade: %[^\n]\n-------------------------\n", nomeArquivo, emailArquivo, senhaArquivo, cpfArquivo, ruaArquivo, bairroArquivo, cidadeArquivo) != EOF) {

                    // Comparar as credenciais
                    if (strcmp(email, emailArquivo) == 0 && strcmp(senha, senhaArquivo) == 0) {
                        encontrou = 1;
                        break;
                    }
                }
                fclose(arquivo);    

                if (encontrou) {
                        usuario->isAdmin = 0; // Usuário comum
                        printf("\033[1;32m\n\nLogin realizado com sucesso!\n\033[0m");
                        return opcao = 0; // Login bem-sucedido
                } else {
                    printf("\033[1;31m\nCredenciais invalidas! Tente novamente.\n\033[0m");
                    Sleep(1000);
                    system("cls");
                }
                break;

        default:
            printf("\033[1;31m\nOpcao invalida! Escolha uma das demonstradas no menu!\n\033[0m");
            Sleep(1000);
            system("cls");
            break;
            }
    }
    return opcao = 0; // Login falhou
}


void exibirMenu(int isAdmin) {
    printf("\n");
    printf("\033[1;32m");
    printf("|-----------------------------------------------|\n");
    printf("|            * Sistema de Adocao Pet *          |\n");
    printf("|-----------------------------------------------|\n");
    printf("\033[1;33m");

    if (isAdmin) {
        printf("| 1 - Cadastro de Usuarios                      |\n");
        printf("| 2 - Cadastro de Animais para Adocao           |\n");
        printf("| 3 - Cadastro de Animais Desaparecidos         |\n");
    }

    printf("| 4 - Buscar por Animais Desaparecidos          |\n");
    printf("| 5 - Buscar por Animais Disponiveis            |\n");
    printf("| 6 - Realizar Adocao                           |\n");

    if (isAdmin) {
        printf("| 7 - Vizualizar historico de adocoes           |\n");
    }
    printf("| 8 - Sair                                      |\n");
    printf("|-----------------------------------------------|\n");
    printf("\033[0m");
    printf("\033[1;32mEscolha uma opcao: \033[0m");
}



