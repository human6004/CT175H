#include <stdio.h>

#define MAX 100

//---------------------Graph-------------------
typedef struct{
	int n,m;
	int A[MAX][MAX];
}Graph;

void init_graph(Graph* pG, int n){
	pG->n = n;
	pG->m = 0;
	for(int i=0; i<=n;i++){
		for(int j=0; j<=n;j++){
			pG->A[i][j] = 0;
		}
	}
}

void add_edge(Graph* pG, int u, int v){
	pG->A[u][v] = 1;
	if(u!=v){
		pG->A[v][u] = 1;
	}
	
	pG->m++;
}

int adj(Graph* pG, int u, int v){
	return pG->A[u][v] > 0;
}

//---------Group-------
//----------------DFS--------------
#define NO_COLOR 0
#define RED 1
#define BLUE 2
#define SUM 3

int visited[MAX];
int color[MAX];
int is_conflict = 0;

void DFS(Graph* pG, int u, int color_u){
//	visited[u] = 1;
//	printf("%d ", u);
	color[u] = color_u; 
	for(int v=1; v<=pG->n; v++){

		//xet cac dinh ke cua u
		if(adj(pG,u,v)){
			int color_v = color[v];
			if(color_v==NO_COLOR){
				DFS(pG, v, SUM - color_u);
			} else if(color_v==color_u){
				is_conflict = 1;
			}
		}
	}
}

int main(){
	Graph G;
	int n, m;
	scanf("%d%d", &n,&m);
	
	init_graph(&G,n);
	
	for(int i = 0; i < m; i++){
		int u,v;
		scanf("%d %d", &u, &v);
		add_edge(&G, u, v);	
	}
	
	for(int i = 0; i <= G.n; i++){
		visited[i] = 0;
		color[i] = NO_COLOR;
	}
	
	DFS(&G,1,BLUE);
	
	if(is_conflict){
		printf("NO");
	}else{
		printf("YES");
	}
	
}