#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "modules.h/animais_desaparecidos.h"
#include "modules.h/usuarios.h"
#include "modules.h/login.h"
#include "modules.h/animais.h"
#include "modules.h/realizar_adocao.h"




int main() {

    Animal* inicioAnimal = NULL;
    Animal* fimAnimal = NULL;
    AnimalDesaparecido* inicioAni = NULL;
    AnimalDesaparecido* fimAni = NULL;
    Usuario* inicioUser = NULL;
    Usuario* fimUser = NULL;
    InformacaoDeUsuario usuarios[MAX_USUARIOS];
    InformacaoDeAnimal animais[MAX_ANIMAIS];
    int numUsuarios = carregarUsuarios(usuarios);
    int numAnimais = carregarAnimais(animais);
    



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

    while (opcao != 8) {
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
                        char fechar;
                        printf("\nDeseja continuar? (s/n): ");
                        while (getchar() != '\n');  // Limpar o buffer 
                        scanf("%c", &fechar);
                        if(fechar == 'n'){
                            system("cls");
                            break;
                        }     
                        Sleep(1000);
                        system("cls");
                        cadastrarUsuario(&inicioUser, &fimUser);
                        printf("\033[1;32mUsuario cadastrado com sucesso!\n\033[0m");
                        
                        char see;
                        printf("\033[1;32mDeseja visualizar usuarios cadastrados? (s): \033[0m");
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
                        system("cls");
                        printf("\033[1;32m\nCadastro de animais para adocao...\n\033[0m");
                        Sleep(1000);
                        system("cls");
                        cadastrarAnimal(&inicioAnimal, &fimAnimal);
                        printf("Animal cadastrado com sucesso!\n");
                    
                    }else{
                        system("cls");
                        printf("\033[1;32m\nCadastro de animais desaparecidos...\n\033[0m");
                        desaparecimentoAnimal(&inicioAni, &fimAni);
                        Sleep(1000);
                        system("cls");
                        printf("Desaparecimento cadastrado com sucesso!\n");
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
                system("cls");
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
                system("cls");
                printf("\033[1;32m\nFuncao de busca por animais disponiveis...\n\033[0m");
                lerAnimais();
                char fecharLeitura;
                printf("Fechar? (s): ");
                getchar(); 
                scanf("%c", &fecharLeitura);
                if(fecharLeitura == 's'){
                    system("cls");
                    break;
                }

            case 6:
                system("cls");
                printf("\033[1;32m\nFuncao de realizar adocao...\n\033[0m");
                realizarAdocao();
                char fecharAdocoes;
                printf("\nFechar? (s): ");
                while (getchar() != '\n');  // Limpar o buffer 
                scanf("%c", &fecharAdocoes);
                if(fecharAdocoes == 's'){
                    system("cls");
                    break;
                }        
            
            case 7:
                system("cls");
                printf("\033[1;32m\nFuncao de busca por adocoes...\n\033[0m");
                lerAdocoes(usuarios, numUsuarios, animais, numAnimais);
                char fecharLeituraAdocoes;
                printf("\nFechar? (s): ");
                while (getchar() != '\n');  // Limpar o buffer 
                scanf("%c", &fecharLeituraAdocoes);
                if(fecharLeituraAdocoes == 's'){
                    system("cls");
                    break;
                }        
               
            case 8:
                system("cls");
                printf("\033[1;32m\nSaindo do sistema. Ate mais!\n\033[0m");
                Sleep(2000);
                system("cls");
                exit(0);


                //Volta para a parte de login ao sair do sistema
                /*while (!loginSucesso) {
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
                break;*/

            default:
                system("cls");
                printf("\033[1;31m\nOpcao invalida! Escolha uma das demonstradas no menu!\n\033[0m");
                Sleep(2000);
                system("cls");
                break;
        }
    }
    return 0;
}