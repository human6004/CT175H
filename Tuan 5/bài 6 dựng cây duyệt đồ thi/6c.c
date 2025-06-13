#include <stdio.h>
#define max 100
typedef int ElementType;
int mark[max];
int parent[max];
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

typedef struct
{
    ElementType data[max];
    int top_idx;
} Stack;

// kkhởi tạo hàm rỗng
void make_null_stack(Stack *pS)
{
    pS->top_idx = -1;
}

// thêm phần tử u vào đỉnh ngăn xếp
void push(Stack *pS, ElementType u)
{
    pS->top_idx++;
    pS->data[pS->top_idx] = u;
}

// xem phần từ trên đầu đỉnh ngăn xếp
ElementType top(Stack *pS)
{
    return pS->data[pS->top_idx];
}

// xóa phần tử trên đỉnh ngăn xếp
void pop(Stack *pS)
{
    pS->top_idx--;
}

// kiểm tra ngăn xếp rỗng
int empty(Stack *pS)
{
    return pS->top_idx == -1;
}

// Dựng cây duyệt đồ thị theo chiều sâu dùng đệ quy
void DFS(Graph *pG, int u, int p)
{
    // 1. đánh dấu u đã duyệt
    mark[u] = 1;
    parent[u] = p;

    // 2. xét các đỉnh kè của u
    for (int v = 1; v <= pG->n; v++)
        if (adjacent(pG, u, v) && mark[v] == 0)
            DFS(pG, v, u);
            
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

    for (int i = 1; i <= G.n; i++)
    {
        if (mark[i] == 0)
        {
            DFS(&G, i, -1);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        printf("%d %d\n", i, parent[i]);
    }
    return 0;
}