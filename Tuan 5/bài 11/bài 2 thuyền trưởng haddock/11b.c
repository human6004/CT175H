#include <stdio.h>
#define max 100
typedef int ElementType;

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
    // pG->A[v][u] = 1;
    pG->m++;
}

int adjacent(Graph *pG, int u, int v)
{
    return pG->A[u][v] > 0;
}

/* kiểm tra đồ thị có chứa chu trình*/
#define WHITE 0
#define GRAY 1
#define BLACK 2

int color[max];// lưu trạng thái cùa các đỉnh
int has_circle;// đồ thị chứa chu trình hay không   

void DFS(Graph *pG, int u){
    //1. tô màu đang duyệt cho u
    color[u] = GRAY;

    //2. xét các đỉnh kề của u
    for(int v = 1; v <= pG->n; v++)
        if(adjacent(pG, u,v)){
            if(color[v] == WHITE)  // 2a. nếu v chưa duyệt
                DFS(pG,v);         // gọi đề quy duyệt nó
            else if(color[v] == GRAY)// 2b. nếu v đang duyệt
                has_circle = 1; //chứa chu trình
        }
    
    // 3. tô màu đã duyệt xong cho u;
    color[u] = BLACK;
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
    //1. khoi taoj mang color[u] = WHITE
    for(int u = 1; u <= G.n; u++)
        color[u] = WHITE;
    
    //2. khoi tao bien has_cricle
    has_circle = 0;

    //3. duyet toan bo do thi de kiem tra chu chinh
    for(int u = 1; u <= G.n ; u++)
        if(color[u] == WHITE)
            DFS(&G,u);
    if(has_circle == 1)
        printf("NO");// có chu trình thì sẽ ko say
    else
        printf("YES");// ko có chu trình thì sẽ say
    return 0;
}
