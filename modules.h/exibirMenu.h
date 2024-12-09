// Função para exibir o menu conforme o tipo de usuário
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
    printf("| 7 - Sair                                      |\n");
    printf("|-----------------------------------------------|\n");
    printf("\033[0m");
    printf("\033[1;32mEscolha uma opcao: \033[0m");
}