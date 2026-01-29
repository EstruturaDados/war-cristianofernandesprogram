#include <stdio.h>
#include <string.h>

/*
    Struct que representa um território do jogo War
*/
struct Territorio {
    char nome[30];
    char cor[15];
    int tropas;
};

int main() {
    struct Territorio territorios[5];
    int i;

    // Cadastro dos territórios
    for (i = 0; i < 5; i++) { 
        printf("**Cadastrando Território %d**\n", i + 1);

        printf("Nome do território: ");
        scanf("%s", territorios[i].nome);

        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição no formato do mapa
    printf("========================================\n");
    printf("     MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("========================================\n\n");

    for (i = 0; i < 5; i++) {
        printf("TERRITÓRIO %d:\n", i + 1);
        printf(" - Nome: %s\n", territorios[i].nome);
        printf(" - Dominado por: Exército %s\n", territorios[i].cor);
        printf(" - Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}
