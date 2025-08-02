#include <stdio.h>
#define max 100
typedef int ElementType;
int mark[max];
int nb_u;
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
    nb_u++;
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

    int max_cnt = 0;
    //duyệt toàn bộ đồ thị để đếm số BPLTBPLT
    for(int u = 1; u <= G.n; u++)
        if(mark[u]==0){
            nb_u = 0;
            DFS(&G, u, -1);// u chưa duyệt
            if(nb_u > max_cnt)
                max_cnt = nb_u;
        }

    printf("%d",max_cnt);
    return 0;
}
/*
	
13 14
1 2
1 12
3 7
3 12
4 6
4 7
5 8
5 9
6 7
6 13
8 9
10 11
10 12
11 12

10
*/