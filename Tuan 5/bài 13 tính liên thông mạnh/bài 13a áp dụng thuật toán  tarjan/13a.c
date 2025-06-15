#include <stdio.h>

#define MAX_SIZE 100

//----------------- Stack--------------------------
typedef int ElementType;

typedef struct {
    ElementType data[MAX_SIZE];
    int top_idx;
} Stack;

void init_stack(Stack* pS) {
    pS->top_idx = -1;
}

int is_empty(Stack* pS) {
    return pS->top_idx == -1;
}

void push(Stack* pS, int x) {
    pS->top_idx++;
    pS->data[pS->top_idx] = x;
}

void pop(Stack* pS) {
    pS->top_idx--;
}

ElementType top(Stack* pS) {
    return pS->data[pS->top_idx];
}

//------------------Graph--------------------------
typedef struct {
    int n, m;
    int A[MAX_SIZE][MAX_SIZE];
} Graph;

void init_graph(Graph* pG, int n) {
    pG->n = n;
    pG->m = 0;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            pG->A[i][j] = 0;
        }
    }
}

void add_edge(Graph* pG, int u, int v) {
    pG->A[u][v]++;
    // if (u != v) {
    //     pG->A[v][u]++;
    // }

    pG->m++;
}

int adj(Graph* pG, int u, int v) {
    return pG->A[u][v] > 0;
}

//------------------Strong connection-----------------
int num[MAX_SIZE];
int min_num[MAX_SIZE];
int k;
Stack S;
int on_stack[MAX_SIZE];

void SCC(Graph* pG, int u) {
    // 1. Đánh số và đưa vào stack
    num[u] = k;
    min_num[u] = k;
    k++;
    push(&S, u);
    on_stack[u] = 1;

    // 2.Duyệt các đỉnh kề
    for (int v = 1; v <= pG->n; v++) {
        if (adj(pG, u, v)) {
            // chưa duyệt
            if (num[v] < 0) {
                SCC(pG, v);
                min_num[u] = min_num[v] < min_num[u] ? min_num[v] : min_num[u];
            } else if (on_stack[v]) {
                min_num[u] = num[v] < min_num[u] ? num[v] : min_num[u];
            }
        }
    }

    // 3. so sánh num và min num
    if (num[u] == min_num[u]) {
        int w;
        do {
            w = top(&S);
            pop(&S);
            on_stack[w] = 0;
        } while (w != u);
    }
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Graph G;
    init_graph(&G, n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    init_stack(&S);
    k = 1;

    // chưa duyet
    for (int i = 0; i <= n; i++) {
        num[i] = -1;
    }

    for (int i = 1; i <= G.n; i++) {
        if (num[i] < 0) {
            SCC(&G, i);
        }
    }

    for (int i = 1; i <= G.n; i++) {
        printf("%d %d\n", num[i], min_num[i]);
    }
}