#include <stdio.h>
#define max 100
typedef int ElementType;
int mark[max];

typedef struct {
    int n, m;
    int A[max][max];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v) {
    pG->A[u][v] = 1;
    pG->A[v][u] = 1;
    pG->m++;
}

int adjacent(Graph *pG, int u, int v) {
    return pG->A[u][v] > 0;
}
//duyệt theo chiều sâu bằng phương pháp đệ 
void DFS(Graph *pG, int u){
    printf("%d\n", u);
    mark[u]=1;
    for(int v = 1; v <= pG->n; v++)
        if(adjacent(pG,u,v) && mark[v] == 0)
            DFS(pG,v);
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
        mark[i] = 0;
        
     DFS(&G, 1);


    return 0;
}
//Đồ thị đơn giản
// 6 6
// 1 2
// 1 3
// 2 4
// 3 5
// 4 6
// 5 6

// 1
// 3
// 5
// 6
// 4
// 2

// Đồ thị liên thông hình chuỗi
//  5 4
// 1 2
// 2 3
// 3 4
// 4 5
// 1
// 2
// 3
// 4
// 5

/*
Đồ thị không liên thông
6 3
1 2
2 3
4 5
1
2
3
*/

/*
Đồ thị có chu trình
4 5
1 2
2 3
3 4
4 1
2 4

1
4
3
2
*/