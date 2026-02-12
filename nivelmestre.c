#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5
#define TOTAL_MISSOES 5

// ============================
// Estrutura Territorio
// ============================
typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;


// ============================
// Função para limpar buffer
// ============================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// ============================
// Exibir Mapa
// ============================
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n========== MAPA DO MUNDO ==========\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %-10s (%-10s) - Tropas: %d\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
    printf("===================================\n");
}


// ============================
// Atribuir Missão
// (passagem por referência)
// ============================
void atribuirMissao(char* destino, char* missoes[], int total) {
    int sorteio = rand() % total;
    strcpy(destino, missoes[sorteio]);
}


// ============================
// Exibir Missão
// (passagem por valor)
// ============================
void exibirMissao(char missao[]) {
    printf("\n===== SUA MISSÃO SECRETA =====\n");
    printf("%s\n", missao);
    printf("==============================\n");
}


// ============================
// Verificar Missão
// ============================
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    // Missões de eliminação
    for (int i = 0; i < tamanho; i++) {

        if (strstr(missao, mapa[i].cor) != NULL) {
            for (int j = 0; j < tamanho; j++) {
                if (strcmp(mapa[j].cor, mapa[i].cor) == 0)
                    return 0;
            }
            return 1;
        }
    }

    // Missão: Conquistar 3 territórios
    if (strstr(missao, "3 territorios") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            int contador = 0;
            for (int j = 0; j < tamanho; j++) {
                if (strcmp(mapa[i].cor, mapa[j].cor) == 0)
                    contador++;
            }
            if (contador >= 3)
                return 1;
        }
    }

    return 0;
}


// ============================
// Sistema de Ataque
// ============================
void atacar(Territorio* atacante, Territorio* defensor) {

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\n--- BATALHA ---\n");
    printf("Atacante (%s - %s) tirou: %d\n",
           atacante->nome, atacante->cor, dadoA);
    printf("Defensor (%s - %s) tirou: %d\n",
           defensor->nome, defensor->cor, dadoD);

    if (dadoA > dadoD) {

        printf("VITORIA DO ATAQUE!\n");

        int metade = atacante->tropas / 2;

        if (metade < 1)
            metade = 1;

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = metade;
        atacante->tropas -= metade;

    } else {
        printf("DERROTA DO ATAQUE! Atacante perdeu 1 tropa.\n");
        atacante->tropas--;
    }
}


// ============================
// Liberar Memória
// ============================
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}


// ============================
// MENU
// ============================
int menu() {
    int op;
    printf("\n===== MENU =====\n");
    printf("1 - Atacar\n");
    printf("2 - Ver Missao\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &op);
    limparBuffer();
    return op;
}


// ============================
// MAIN
// ============================
int main() {

    srand(time(NULL));

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) calloc(TOTAL_TERRITORIOS, sizeof(Territorio));

    printf("--- CADASTRO DOS TERRITORIOS ---\n");

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {

        printf("\nTerritorio %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Exercito (cor): ");
        fgets(mapa[i].cor, 15, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        do {
            printf("Quantidade de tropas (>=1): ");
            scanf("%d", &mapa[i].tropas);
            limparBuffer();
        } while (mapa[i].tropas < 1);
    }


    // ============================
    // MISSÕES
    // ============================
    char* missoes[TOTAL_MISSOES] = {
        "Eliminar o exercito Verde",
        "Eliminar o exercito Azul",
        "Eliminar o exercito Vermelho",
        "Eliminar o exercito Amarelo",
        "Conquistar 3 territorios"
    };

    char* missaoJogador = (char*) malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador, missoes, TOTAL_MISSOES);

    exibirMissao(missaoJogador);

    int opcao, at, def;

    // ============================
    // LOOP PRINCIPAL
    // ============================
    while (1) {

        exibirMapa(mapa, TOTAL_TERRITORIOS);

        opcao = menu();

        if (opcao == 0) {
            printf("Jogo encerrado.\n");
            break;
        }

        if (opcao == 2) {
            exibirMissao(missaoJogador);
            continue;
        }

        if (opcao == 1) {

            printf("Territorio atacante: ");
            scanf("%d", &at);
            limparBuffer();

            printf("Territorio defensor: ");
            scanf("%d", &def);
            limparBuffer();

            at--;
            def--;

            if (at < 0 || at >= TOTAL_TERRITORIOS ||
                def < 0 || def >= TOTAL_TERRITORIOS) {
                printf("Territorio invalido.\n");
                continue;
            }

            if (mapa[at].tropas <= 1) {
                printf("Ataque invalido: minimo 2 tropas.\n");
                continue;
            }

            if (strcmp(mapa[at].cor, mapa[def].cor) == 0) {
                printf("Ataque invalido: mesmo exercito.\n");
                continue;
            }

            atacar(&mapa[at], &mapa[def]);

            if (verificarMissao(missaoJogador, mapa, TOTAL_TERRITORIOS)) {
                printf("\n🏆 MISSAO CUMPRIDA! VOCE VENCEU! 🏆\n");
                break;
            }
        }
    }

    liberarMemoria(mapa, missaoJogador);

    return 0;
}
