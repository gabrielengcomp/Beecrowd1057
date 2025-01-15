#include <stdio.h>
#include <stdlib.h>

typedef struct fila {
    int *dadosX;
    int *dadosY;
    int inicio, fim, tamanho;
} Fila;

typedef struct status {
    int xA, yA;
    int xB, yB;
    int xC, yC;
} Status;

void lerMatriz(int N, char map[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &map[i][j]);
        }
    }
}

void scanMatriz(int N, char map[N][N], Status *coord) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char atual = map[i][j];
            if (atual == 'A') {
                coord->xA = i;
                coord->yA = j;
            }
            if (atual == 'B') {
                coord->xB = i;
                coord->yB = j;
            }
            if (atual == 'C') {
                coord->xC = i;
                coord->yC = j;
            }
        }
    }
}

Fila* criaFila(int capacidade) {
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->dadosX = (int *)malloc(capacidade * sizeof(int));
    fila->dadosY = (int *)malloc(capacidade * sizeof(int));
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = capacidade;
    return fila;
}

int filaVazia(Fila *fila) {
    return fila->inicio == fila->fim;
}

void enfileira(Fila *fila, int x, int y) {
    fila->dadosX[fila->fim] = x;
    fila->dadosY[fila->fim] = y;
    fila->fim = (fila->fim + 1) % fila->tamanho;
}

void desenfileira(Fila *fila, int *x, int *y) {
    *x = fila->dadosX[fila->inicio];
    *y = fila->dadosY[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->tamanho;
}

int BFS(int N, char map[N][N], Status *coord) {
    int movX[] = {-1, 1, 0, 0};
    int movY[] = {0, 0, -1, 1};
    
    Fila *fila = criaFila(N * N);
    int visitado[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visitado[i][j] = 0;
        }
    }

    // Enfileira as posições iniciais A, B e C
    enfileira(fila, coord->xA, coord->yA);
    enfileira(fila, coord->xB, coord->yB);
    enfileira(fila, coord->xC, coord->yC);

    visitado[coord->xA][coord->yA] = 1;
    visitado[coord->xB][coord->yB] = 1;
    visitado[coord->xC][coord->yC] = 1;

    // BFS
    int moves = 0;
    int maxMoves = 0; // Variável para armazenar o maior número de movimentos
    while (!filaVazia(fila)) {
        int tamanhoFila = fila->fim - fila->inicio;
        if (tamanhoFila < 0) tamanhoFila += fila->tamanho;
        
        // Processa todos os elementos na fila no nível atual
        for (int i = 0; i < tamanhoFila; i++) {
            int x, y;
            desenfileira(fila, &x, &y);

            // Verifica se encontrou o objetivo 'X'
            if (map[x][y] == 'X') {
                maxMoves = moves > maxMoves ? moves : maxMoves;
            }

            // Explorar as posições vizinhas
            for (int j = 0; j < 4; j++) {
                int newX = x + movX[j];
                int newY = y + movY[j];

                if (newX >= 0 && newX < N && newY >= 0 && newY < N && !visitado[newX][newY] && map[newX][newY] != '#') {
                    enfileira(fila, newX, newY);
                    visitado[newX][newY] = 1;
                }
            }
        }
        moves++;
    }

    return maxMoves;  // Retorna o maior número de movimentos entre A, B e C
}


int main() {
    int N, T, i=0;
    Status coord;
    scanf("%d", &T);  // Não está sendo usado, mas pode ser útil em outro contexto
    while(i<T){
        scanf("%d", &N);
        char Mapa[N][N];
        lerMatriz(N, Mapa);
        scanMatriz(N, Mapa, &coord);

        int mov = BFS(N, Mapa, &coord);
        if(mov!=0) printf("Case %d: %d\n",T, mov);
        else printf("Case %d: trapped", T);
        i++;
    }
    return 0;
}
