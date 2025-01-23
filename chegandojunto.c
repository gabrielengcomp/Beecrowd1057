#include <stdio.h>
#include <string.h>

#define MAX_N 12
#define MAX_FILA (MAX_N * MAX_N * MAX_N * 100)


typedef struct {
    int x, y;
} coordenadas;

typedef struct {
    coordenadas A, B, C;
    int moves;
} estado;

char map[MAX_N][MAX_N];
int vis[MAX_N][MAX_N][MAX_N][MAX_N][MAX_N][MAX_N];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int N;

coordenadas A, B, C;
coordenadas a, b, c;

estado Fila[MAX_FILA];
int inicio, fim;

void inicializarFila() {
    inicio = fim = 0;
}

int filaVazia() {
    return inicio == fim;
}

void enfileira(estado val) {
    Fila[fim++] = val;
    if (fim >= MAX_FILA) fim = 0;  
}

estado desinfileira() {
    estado val = Fila[inicio++];
    if (inicio >= MAX_FILA) inicio = 0;
    return val;
}

int podeir(coordenadas aux) {
    return aux.x >= 0 && aux.x < N && aux.y >= 0 && aux.y < N && map[aux.x][aux.y] != '#';
}

int chegou() {
    return map[a.x][a.y] == 'X' && map[b.x][b.y] == 'X' && map[c.x][c.y] == 'X';
}

void BFS(int t) {
    inicializarFila();
    memset(vis, 0, sizeof(vis));

    estado atual;
    atual.A = A;
    atual.B = B;
    atual.C = C;
    atual.moves = 0;

    enfileira(atual);
    vis[A.x][A.y][B.x][B.y][C.x][C.y] = 1;

    while (!filaVazia()) {
        atual = desinfileira();
        a = atual.A;
        b = atual.B;
        c = atual.C;
        
        if (chegou()) {
            printf("Case %d: %d\n", t, atual.moves);
            return;
        }

        for (int i = 0; i < 4; i++) {
            coordenadas novoA = {a.x + dx[i], a.y + dy[i]};
            coordenadas novoB = {b.x + dx[i], b.y + dy[i]};
            coordenadas novoC = {c.x + dx[i], c.y + dy[i]};
            
            // Verificar se as novas posições são válidas
            if (!podeir(novoA)) novoA = a;
            if (!podeir(novoB)) novoB = b;
            if (!podeir(novoC)) novoC = c;

            // Verificar se as entidades colidem nas novas posições
            if (novoA.x == novoB.x && novoA.y == novoB.y) {
                novoA = a;  // Se A e B colidirem, não se movem.
                novoB = b;
            }
            if (novoA.x == novoC.x && novoA.y == novoC.y) {
                novoA = a;  // Se A e C colidirem, não se movem.
                novoC = c;
            }
            if (novoB.x == novoC.x && novoB.y == novoC.y) {
                novoB = b;  // Se B e C colidirem, não se movem.
                novoC = c;
            }

            // Verificar colisões de troca de posição
            if ((novoA.x == b.x && novoA.y == b.y && novoB.x == a.x && novoB.y == a.y) ||  // A troca com B
                (novoA.x == c.x && novoA.y == c.y && novoC.x == a.x && novoC.y == a.y) ||  // A troca com C
                (novoB.x == c.x && novoB.y == c.y && novoC.x == b.x && novoC.y == b.y)) {  // B troca com C
                continue;  // Ignorar este movimento.
            }

            // Verificar se já visitamos essa combinação de posições
            if (!vis[novoA.x][novoA.y][novoB.x][novoB.y][novoC.x][novoC.y]) {
                vis[novoA.x][novoA.y][novoB.x][novoB.y][novoC.x][novoC.y] = 1;

                if ((novoA.x == novoB.x && novoA.y == novoB.y) || 
                (novoA.x == novoC.x && novoA.y == novoC.y) || 
                (novoB.x == novoC.x && novoB.y == novoC.y)) {
                continue;  // Posição inválida.
                }

                estado novo = {novoA, novoB, novoC, atual.moves + 1};
                enfileira(novo);
            }
        }   
    }

    printf("Case %d: trapped\n", t);
}


int main() {
    int T;
    scanf("%d", &T); //Armazena o número de casos

    for (int t = 1; t <= T; t++) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) { //Lê e armazena o mapa
            for (int j = 0; j < N; j++) {
                scanf(" %c", &map[i][j]);
                if (map[i][j] == 'A') {
                    A.x = i;
                    A.y = j;
                } else if (map[i][j] == 'B') {
                    B.x = i;
                    B.y = j;
                } else if (map[i][j] == 'C') {
                    C.x = i;
                    C.y = j;
                }
            }
        }
        BFS(t);
    }

    return 0;
}
