#include <stdio.h>
#include <string.h>

#define MAX_N 12
#define MAX_QUEUE (MAX_N * MAX_N * MAX_N * 100)
#define INF 0x3F3F3F3F

typedef struct {
    int x, y;
} dvd;

typedef struct {
    dvd A, B, C;
    int tempo;
} cd;

char lab[MAX_N][MAX_N];
int vis[MAX_N][MAX_N][MAX_N][MAX_N][MAX_N][MAX_N];
int dx[] = {-1, 0, 0, 1}, dy[] = {0, -1, 1, 0};
int N;

dvd A, B, C;
dvd a, b, c;

cd queue[MAX_QUEUE];
int front, rear;

void init_queue() {
    front = rear = 0;
}

int is_empty() {
    return front == rear;
}

void enqueue(cd val) {
    queue[rear++] = val;
    if (rear >= MAX_QUEUE) rear = 0;  // Circular queue
}

cd dequeue() {
    cd val = queue[front++];
    if (front >= MAX_QUEUE) front = 0;  // Circular queue
    return val;
}

int podeir(dvd aux) {
    return aux.x >= 0 && aux.x < N && aux.y >= 0 && aux.y < N && lab[aux.x][aux.y] != '#';
}

int chegou() {
    return lab[a.x][a.y] == 'X' && lab[b.x][b.y] == 'X' && lab[c.x][c.y] == 'X';
}

void solve(int t) {
    init_queue();
    memset(vis, 0, sizeof(vis));

    cd atual;
    atual.A = A;
    atual.B = B;
    atual.C = C;
    atual.tempo = 0;

    enqueue(atual);
    vis[A.x][A.y][B.x][B.y][C.x][C.y] = 1;

    while (!is_empty()) {
        atual = dequeue();
        a = atual.A;
        b = atual.B;
        c = atual.C;
        
        if (chegou()) {
            printf("Case %d: %d\n", t, atual.tempo);
            return;
        }

        for (int i = 0; i < 4; i++) {
            dvd aa = {a.x + dx[i], a.y + dy[i]};
            dvd bb = {b.x + dx[i], b.y + dy[i]};
            dvd cc = {c.x + dx[i], c.y + dy[i]};

            
            // Verificar se as novas posições são válidas
            if (!podeir(aa)) aa = a;
            if (!podeir(bb)) bb = b;
            if (!podeir(cc)) cc = c;

            // Verificar se as entidades colidem nas novas posições
            if (aa.x == bb.x && aa.y == bb.y) {
                aa = a;  // Se A e B colidirem, não se movem.
                bb = b;
            }
            if (aa.x == cc.x && aa.y == cc.y) {
                aa = a;  // Se A e C colidirem, não se movem.
                cc = c;
            }
            if (bb.x == cc.x && bb.y == cc.y) {
                bb = b;  // Se B e C colidirem, não se movem.
                cc = c;
            }


            // Verificar se já visitamos essa combinação de posições
            if (!vis[aa.x][aa.y][bb.x][bb.y][cc.x][cc.y]) {
                vis[aa.x][aa.y][bb.x][bb.y][cc.x][cc.y] = 1;
                cd novo = {aa, bb, cc, atual.tempo + 1};
                enqueue(novo);
            }
        }
    }

    printf("Case %d: trapped\n", t);
}


int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                scanf(" %c", &lab[i][j]);
                if (lab[i][j] == 'A') {
                    A.x = i;
                    A.y = j;
                } else if (lab[i][j] == 'B') {
                    B.x = i;
                    B.y = j;
                } else if (lab[i][j] == 'C') {
                    C.x = i;
                    C.y = j;
                }
            }
        }
        solve(t);
    }

    return 0;
}
