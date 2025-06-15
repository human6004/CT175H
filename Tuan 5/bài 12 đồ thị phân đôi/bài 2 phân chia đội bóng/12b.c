#include <stdio.h>

/* Khai báo CTDL Graph */
#define MAX_N 100
typedef struct {
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int u = 1 ; u <= n; u++)
        for (int v = 1 ; v <= n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v) {
    pG->A[u][v] += 1;
    pG->A[v][u] += 1;
    pG->m++;
}

int adjacent(Graph *pG, int u, int v) {
    return pG->A[u][v] > 0;
}

#define NO_COLOR 0
#define BLUE     1
#define RED      2

int color[MAX_N];	// Lưu trạng thái màu của các đỉnh
int conflict = 0;	// Cờ kiểm tra đụng độ màu

void colorize(Graph *pG, int u, int c) {
    color[u] = c;
    for (int v = 1; v <= pG->n; v++) {
        if (adjacent(pG, u, v)) {
            if (color[v] == NO_COLOR)
                colorize(pG, v, 3 - c);
            else if (color[v] == color[u])
                conflict = 1;
        }
    }
}

int main() {
    Graph G;
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (int e = 0; e < m; e++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    for (int i = 1; i <= G.n; i++)
        color[i] = NO_COLOR;
    conflict = 0;

    for (int i = 1; i <= G.n; i++)
        if (color[i] == NO_COLOR)
            colorize(&G, i, BLUE);

    if (conflict) {
        printf("IMPOSSIBLE\n");
    } else {
        // In nhóm BLUE trước (vì đỉnh 1 được tô màu BLUE từ đầu)
        for (int i = 1; i <= G.n; i++)
            if (color[i] == BLUE)
                printf("%d ", i);
        printf("\n");
        for (int i = 1; i <= G.n; i++)
            if (color[i] == RED)
                printf("%d ", i);
        printf("\n");
    }

    return 0;
}
