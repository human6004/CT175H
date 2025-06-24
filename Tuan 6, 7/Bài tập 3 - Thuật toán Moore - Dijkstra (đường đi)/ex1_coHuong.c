#include <stdio.h>
#define MAX_N 100
#define NO_EDGE -1
#define oo 999999

typedef struct
{
    int n, m;
    int W[MAX_N][MAX_N];
} Graph;

// ham khoi tao
void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
            pG->W[u][v] = NO_EDGE;
}

// them cung vao do thi
void add_edge(Graph *pG, int u, int v, int W)
{
    pG->W[u][v] = W;
    // pG->W[v][u] = W;
    pG->m++;
}

int mark[MAX_N];
int pi[MAX_N]; // chiều dài từ đỉnh s đến u
int p[MAX_N];  // đỉnh trước của u

void MooreDijkstra(Graph *pG, int s)
{
    int u, v, it;
    for (u = 1; u <= pG->n; u++)
    {
        pi[u] = oo;
        mark[u] = 0;
    }

    pi[s] = 0;
    p[s] = -1;

    // lap n-1
    for (it = 1; it < pG->n; it++)
    {
        int j, min_pi = oo;
        for (j = 1; j <= pG->n; j++)
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                min_pi = pi[j];
                u = j;
            }
        mark[u] = 1; // danh dau da duyet

        for (v = 1; v <= pG->n; v++)
            if (pG->W[u][v] != NO_EDGE && mark[v] == 0)
                if (pi[u] + pG->W[u][v] < pi[v])
                {
                    pi[v] = pi[u] + pG->W[u][v];
                    p[v] = u; // gắn cha cho v
                }
    }
}

int main()
{
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (int e = 0; e < m; e++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    int start, end;
    scanf("%d %d", &start, &end);
    MooreDijkstra(&G, start);

    // tìm đường đi ngắn nhất
    int path[MAX_N];   // lưu các đỉnh trên đường đi
    int k = 0;         // biến đếm
    int current = end; // lần ngược theo p để lấy đường đi
    while (current != -1)
    {
        path[k] = current;
        k++;
        current = p[current];
    }
    printf("%d", path[k-1]);
    for(int u = k-2; u >= 0; u--)
        printf(" -> %d", path[u]);
    return 0;
}