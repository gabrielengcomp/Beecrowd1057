#include <stdio.h>
#include <stdlib.h>

typedef struct fila {
    char *dados;
    int inicio, fim, tamanho;
}Fila;

typedef struct status {
    int xA,yA;
    int xB,yB;
    int xC,yC;
    int moves;
}Status;

void lerMatriz(int N, char map[N][N]){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            scanf(" %c ", &map[i][j]);
        }    
    }
}

void printMapa(int N, char map[N][N]){ //para fins de teste
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            printf("%c ", map[i][j]);
        }
        printf("\n");    
    }
}

void scanMatriz(int N, char map[N][N], Status coord){
    char atual;

    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            atual = map[i][j];
            if (atual == 'A'){ 
                coord.xA=i;
                coord.yA=j;
            }
            if (atual == 'B'){ 
                coord.xB=i;
                coord.yB=j;
            }
            if (atual == 'C'){ 
                coord.xC=i;
                coord.yC=j;
            }

        }
    }
}

Fila* criaFila(int capacidade) {
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->dados = (char *)malloc(capacidade * sizeof(char));
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = capacidade;
    return fila;
}

int filaVazia(Fila *fila) {
    return fila->inicio == fila->fim;
}

void enfileira(Fila *fila, char valor) {
    fila->dados[fila->fim] = valor;
    fila->fim = (fila->fim + 1) % fila->tamanho;
}

char desenfileira(Fila *fila) {
    char valor = fila->dados[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->tamanho;
    return valor;
}

int bfs(int N, char mapa[N][N], Status *coord) {
    // Movimentos possíveis (direções: cima, baixo, esquerda, direita)
    int movX[] = {-1, 1, 0, 0};
    int movY[] = {0, 0, -1, 1};

    // Fila para BFS
    Fila *fila = criaFila(N * N);
    
    // Marcando as posições visitadas
    int visitado[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visitado[i][j] = 0;
        }
    }

    // Adicionando a posição inicial de A
    enfileira(fila, coord->xA);
    enfileira(fila, coord->yA);
    visitado[coord->xA][coord->yA] = 1;

    // BFS
    int moves = 0;
    while (!filaVazia(fila)) {
        int x = desenfileira(fila);
        int y = desenfileira(fila);
        
        // Verificar se chegou ao objetivo C
        if (mapa[x][y] == 'X') {
            return moves;
        }

        // Explorar as posições vizinhas
        for (int i = 0; i < 4; i++) {
            int newX = x + movX[i];
            int newY = y + movY[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N && !visitado[newX][newY] && mapa[newX][newY] != '#') {
                enfileira(fila, newX);
                enfileira(fila, newY);
                visitado[newX][newY] = 1;
            }
        }

        moves++;
    }

    // Se não encontrar caminho
    return -1;
}

void main(){
    int N, T;
    scanf("%d", &T);
    scanf("%d", &N);
    char Mapa[N][N];
    lerMatriz(N, Mapa);
    printMapa(N, Mapa); 
}
