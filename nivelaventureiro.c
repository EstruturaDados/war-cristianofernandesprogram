#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL 5

typedef struct {
    char nome[20];
    char cor[20];
    int tropas;
} Territorio;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void esperarEnter() {
    printf("\nPressione Enter para continuar para o proximo turno...");
    limparBuffer();
}

void mostrarMapa(Territorio t[]) {
    printf("\n--- MAPA DO MUNDO ---\n");
    for (int i = 0; i < TOTAL; i++) {
        printf("%d. %s (%s) - Tropas: %d\n",
               i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

void atacar(Territorio *a, Territorio *d) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\n--- BATALHA ---\n");
    printf("Atacante (%s - %s) tirou: %d\n", a->nome, a->cor, dadoA);
    printf("Defensor (%s - %s) tirou: %d\n", d->nome, d->cor, dadoD);

    if (dadoA > dadoD) {
        d->tropas--;
        printf("VITORIA DO ATAQUE! Defensor perdeu 1 tropa.\n");

        if (d->tropas == 0) {
            printf("CONQUISTA! %s agora pertence ao exercito %s.\n",
                   d->nome, a->cor);

            strcpy(d->cor, a->cor);
            d->tropas = 1;
            a->tropas--;
        }
    } else {
        a->tropas--;
        printf("DERROTA DO ATAQUE! Atacante perdeu 1 tropa.\n");
    }
}

int main() {
    srand(time(NULL));

    Territorio t[TOTAL];
    int at, def;

    /* CADASTRO DOS TERRITORIOS */
    printf("--- CADASTRO DOS TERRITORIOS ---\n");
    for (int i = 0; i < TOTAL; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Nome: ");
        fgets(t[i].nome, 20, stdin);
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0';

        printf("Exercito (cor): ");
        fgets(t[i].cor, 20, stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        do {
            printf("Quantidade de tropas (>=1): ");
            scanf("%d", &t[i].tropas);
            limparBuffer();
        } while (t[i].tropas < 1);
    }

    /* LOOP DO JOGO */
    while (1) {
        mostrarMapa(t);

        printf("\nEscolha o territorio atacante (1 a %d, 0 para sair): ", TOTAL);
        scanf("%d", &at);
        limparBuffer();

        if (at == 0) {
            printf("\nJogo encerrado.\n");
            break;
        }

        printf("Escolha o territorio defensor (1 a %d): ", TOTAL);
        scanf("%d", &def);
        limparBuffer();

        at--;
        def--;

        if (at < 0 || at >= TOTAL || def < 0 || def >= TOTAL) {
            printf("\nTerritorio invalido.\n");
            esperarEnter();
            continue;
        }

        if (t[at].tropas <= 1) {
            printf("\nAtaque invalido: precisa ter mais de 1 tropa.\n");
            esperarEnter();
            continue;
        }

        if (strcmp(t[at].cor, t[def].cor) == 0) {
            printf("\nAtaque invalido: mesmo exercito.\n");
            esperarEnter();
            continue;
        }

        atacar(&t[at], &t[def]);
        esperarEnter();
    }

    return 0;
}
