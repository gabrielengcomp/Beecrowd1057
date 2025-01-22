#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int xA, yA, xB, yB, xC, yC, moves;
} State;

typedef struct fila {
    State *dados;
    int inicio, fim, tamanho;
} Fila;

Fila* criaFila(int capacidade) {
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->dados = (State *)malloc(capacidade * sizeof(State));
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = capacidade;
    return fila;
}

int filaVazia(Fila *fila) {
    return fila->inicio == fila->fim;
}

void enfileira(Fila *fila, State estado) {
    fila->dados[fila->fim] = estado;
    fila->fim = (fila->fim + 1) % fila->tamanho;
}

State desenfileira(Fila *fila) {
    State estado = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->tamanho;
    return estado;
}

int Chegaram(int xA, int yA, int xB, int yB, int xC, int yC, int N, char map[N][N]) {
    return map[xA][yA] == 'X' && map[xB][yB] == 'X' && map[xC][yC] == 'X';
}

int posicoesDistintas(int xA, int yA, int xB, int yB, int xC, int yC) {
    return !(xA == xB && yA == yB) &&
           !(xA == xC && yA == yC) &&
           !(xB == xC && yB == yC);
}

int BFS(int N, char map[N][N], int xA, int yA, int xB, int yB, int xC, int yC) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int visitado[N][N][N][N][N][N];
    memset(visitado, 0, sizeof(visitado));

    Fila *fila = criaFila(100000);
    State inicial = {xA, yA, xB, yB, xC, yC, 0};
    enfileira(fila, inicial);
    visitado[xA][yA][xB][yB][xC][yC] = 1;

    while (!filaVazia(fila)) {
        State atual = desenfileira(fila);

        if (Chegaram(atual.xA, atual.yA, atual.xB, atual.yB, atual.xC, atual.yC, N, map)) {
            free(fila->dados);
            free(fila);
            return atual.moves;
        }

        for (int i = 0; i < 4; i++) {
            int nxA = atual.xA + dx[i];
            int nyA = atual.yA + dy[i];
            int nxB = atual.xB + dx[i];
            int nyB = atual.yB + dy[i];
            int nxC = atual.xC + dx[i];
            int nyC = atual.yC + dy[i];

            // Verifica limites e obstáculos
            if (nxA < 0 || nxA >= N || nyA < 0 || nyA >= N || map[nxA][nyA] == '#') {
                nxA = atual.xA;
                nyA = atual.yA;
            }
            if (nxB < 0 || nxB >= N || nyB < 0 || nyB >= N || map[nxB][nyB] == '#') {
                nxB = atual.xB;
                nyB = atual.yB;
            }
            if (nxC < 0 || nxC >= N || nyC < 0 || nyC >= N || map[nxC][nyC] == '#') {
                nxC = atual.xC;
                nyC = atual.yC;
            }

            // Verifica se as posições são válidas
            if (posicoesDistintas(nxA, nyA, nxB, nyB, nxC, nyC) &&
                !visitado[nxA][nyA][nxB][nyB][nxC][nyC]) {
                visitado[nxA][nyA][nxB][nyB][nxC][nyC] = 1;
                State novo = {nxA, nyA, nxB, nyB, nxC, nyC, atual.moves + 1};
                enfileira(fila, novo);
            }
        }
    }

    free(fila->dados);
    free(fila);
    return -1;
}

void lerMatriz(int N, char map[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &map[i][j]);
        }
    }
}

void scanMatriz(int N, char map[N][N], int *xA, int *yA, int *xB, int *yB, int *xC, int *yC) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 'A') {
                *xA = i;
                *yA = j;
            } else if (map[i][j] == 'B') {
                *xB = i;
                *yB = j;
            } else if (map[i][j] == 'C') {
                *xC = i;
                *yC = j;
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        int N;
        scanf("%d", &N);
        char map[N][N];
        int xA, yA, xB, yB, xC, yC;

        lerMatriz(N, map);
        scanMatriz(N, map, &xA, &yA, &xB, &yB, &xC, &yC);

        int resultado = BFS(N, map, xA, yA, xB, yB, xC, yC);
        if (resultado != -1) {
            printf("Case %d: %d\n", t, resultado);
        } else {
            printf("Case %d: trapped\n", t);
        }
    }

    return 0;
}
