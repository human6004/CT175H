#include <stdio.h>
#define max 100
typedef int ElementType;
int mark[max];
int parent[max];

typedef struct{
    int n,m;
    int A[max][max];
}Graph;

void init_graph (Graph *pG, int n){
    pG->n = n;
    pG-> m = 0;
    for (int u = 1; u <= n; u++){
        for (int v = 1; v <= n; v++){
            pG->A[u][v] = 0;
        }
    }
}

void add_edge(Graph *pG, int u, int v){
    pG->A[u][v] = 1;
    pG->A[v][u] = 1;
    pG->m++;
}

int adjacent(Graph *pG, int u, int v){
    return pG->A[u][v] > 0;
}

//duyệt đồ thị theo chiều sau
void DFS(Graph *pG, int u, int p){
    mark[u]=1;
    parent[u]=p;
    for(int v = 1; v <= pG->n; v++){
        if(adjacent(pG,u,v) && mark[v]==0 )
        DFS(pG,v,u);
    }
    
}
int main (){
    Graph G;
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
	
    for (int e = 0; e < m; e++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    //khởi tạo mảng mark[u]=0
    for (int u = 1; u <= G.n; u++)
    mark[u] = 0;
    //khởi tạo biến đếm 
    int cnt = 0;
    //duyệt toàn bộ đồ thị để đếm số BPLTBPLT
    for(int u = 1; u <= G.n; u++)
        if(mark[u]==0){
            DFS(&G,u,-1);// u chưa duyệt
            cnt++;
        }

    printf("%d",cnt);
    return 0;
}

/*
4 3
2 1
1 3
2 4

4
*/