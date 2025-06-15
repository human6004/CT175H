#include <stdio.h>
#define max 100
typedef int ElementType;
int mark[max];
typedef struct
{
    int n, m;
    int A[max][max];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++)
    {
        for (int v = 1; v <= n; v++)
        {
            pG->A[u][v] = 0;
        }
    }
}

void add_edge(Graph *pG, int u, int v)
{
    pG->A[u][v] = 1;
    pG->A[v][u] = 1;
    pG->m++;
}

int adjacent(Graph *pG, int u, int v)
{
    return pG->A[u][v] > 0;
}

// Dựng cây duyệt đồ thị theo chiều sâu dùng đệ quy
void DFS(Graph *pG, int u,int v)
{
    // 1. đánh dấu u đã duyệt
    mark[u] = 1;
    // 2. xét các đỉnh kè của u
    for (int v = 1; v <= pG->n; v++)
        if (adjacent(pG, u, v) && mark[v] == 0)
            DFS(pG, v, u);
}

int connected(Graph *pG)
{
    for (int u = 1; u <= pG->n; u++)
        mark[u] = 0;
    DFS(pG,1,-1);
    for (int u = 1; u <= pG->n; u++)
        if (mark[u] == 0)
            return 0; // đồ thì ko liên thông
    return 1;         // đồ thị liên thông
}
int main()
{
    Graph G;
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (int e = 0; e < m; e++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    for (int i = 1; i <= G.n; i++)
        mark[i] = 0;

    if (connected(&G) == 1)
        printf("YES");
    else
        printf("NO");
    return 0;
}
/*
4 3
1 2
2 3
3 4
YES
*/

/*	
4 2
3 4
1 2
NO
*/