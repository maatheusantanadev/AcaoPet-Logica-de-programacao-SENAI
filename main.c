#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "modules.h/animais_desaparecidos.h"
#include "modules.h/usuarios.h"
#include "modules.h/login.h"




int main() {

    AnimalDesaparecido* inicioAni = NULL;
    AnimalDesaparecido* fimAni = NULL;
    Usuario* inicioUser = NULL;
    Usuario* fimUser = NULL;

    

    Usuario usuarioAtual = { "", "", "", "", "", "", "", 0, NULL, NULL };
    int loginSucesso = 0;

    while (!loginSucesso) {
        loginSucesso = login(&usuarioAtual);
        int opcaoLogin;
        opcaoLogin = loginSucesso;
        if (opcaoLogin == 1){
            system("cls");
            printf("\033[1;32m\nCadastro de usuarios...\n\033[0m");
            Sleep(1000);
            system("cls");
            cadastrarUsuario(&inicioUser, &fimUser);
            printf("\033[1;32mUsuario cadastrado com sucesso!\n\033[0m");        
            loginSucesso = 0;
            Sleep(1000);
            system("cls");
        }else{
            break;
        }
    }
    int opcao = 0;

    Sleep(3000);
    system("cls");

    while (opcao != 7) {
        // Exibe o menu de acordo com o tipo de usuário
        exibirMenu(usuarioAtual.isAdmin);
        opcao = 0;
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:                    
            case 2:
            case 3:
                if (usuarioAtual.isAdmin) {
                    printf("\033[1;32m\nFuncao de cadastro disponivel para administradores.\n\033[0m");
                    Sleep(1000);
                    
                    if(opcao == 1){
                        system("cls");
                        printf("\033[1;32m\nCadastro de usuarios...\n\033[0m");
                        Sleep(1000);
                        system("cls");
                        cadastrarUsuario(&inicioUser, &fimUser);
                        printf("Usuario cadastrado com sucesso!\n");
                        
                        char see;
                        printf("Deseja visualizar usuarios cadastrados? (s): ");
                        fflush(stdin);
                        scanf(" %c", &see);
                        if (see == 's') {
                            Sleep(1000);
                            system("cls");
                            lerUsuariosDoArquivo();
                        }
                        system("pause");
                        system("cls");
                        break;
                    }else if (opcao == 2) {
                        // Cadastro de animais para adoção
                    }else{
                        printf("\033[1;32m\nCadastro de animais desaparecidos...\n\033[0m");
                        desaparecimentoAnimal(&inicioAni, &fimAni);
                    }
                    Sleep(2000);
                    system("cls");
                } else {
                    printf("\033[1;31m\nAcesso negado! Apenas administradores podem acessar esta funcao.\n\033[0m");
                    Sleep(2000);
                    system("cls");
                }
                break;
                

            case 4:
                printf("\033[1;32m\nFuncao de busca por animais desaparecidos...\n\033[0m");
                lerAnimaisDoArquivo();
                char fechar;
                printf("Fechar? (s): ");
                getchar(); 
                scanf("%c", &fechar);
                if(fechar == 's'){
                    system("cls");
                    break;
                }

            case 5:
                 printf("\033[1;32m\nFuncao de busca por animais disponiveis...\n\033[0m");
                Sleep(2000);
                system("cls");
                break;

            case 6:
                printf("\033[1;32m\nFuncao de realizar adocao...\n\033[0m");
                Sleep(2000);
                system("cls");
                break;
            
            case 7:
                printf("\033[1;32m\nSaindo do sistema. Ate mais!\n\033[0m");
                Sleep(2000);
                system("cls");

                while (!loginSucesso) {
                    loginSucesso = login(&usuarioAtual);
                    int opcaoLogin;
                    opcaoLogin = loginSucesso;
                    if (opcaoLogin == 1){
                        system("cls");
                        printf("\033[1;32m\nCadastro de usuarios...\n\033[0m");
                        Sleep(1000);
                        system("cls");
                        cadastrarUsuario(&inicioUser, &fimUser);
                        printf("\033[1;32mUsuario cadastrado com sucesso!\n\033[0m");        
                        loginSucesso = 0;
                        Sleep(1000);
                        system("cls");
                    }else{
                        Sleep(1000);
                        system("cls");
                        break;
                    }
                }
                opcao = 0;
                break;

            default:
                printf("\033[1;31m\nOpcao invalida! Escolha uma das demonstradas no menu!\n\033[0m");
                Sleep(2000);
                system("cls");
                break;
        }
    }

    return 0;
}