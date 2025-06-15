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
    pG->A[v][u] = 1;
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


void DFS(Graph *pG, int u, int p) {								
	//1. Tô màu dang duyệt cho u
	color[u] = GRAY; 			

	//2. Xét các đỉnh kề của u
	for (int v = 1; v <= pG->n; v++)
		if (adjacent(pG, u, v)) {
			if (v == p) 		//2a. Nếu v == p
				continue;   		//bỏ qua
				
			if (color[v] == WHITE) 		//2a. Nếu v chưa duyệt
				DFS(pG, v, u);   		//gọi đệ quy duyệt nó
			else if (color[v] == GRAY)	//2b. v đang duyệt
				has_circle = 1;   	//chứa chu trình
		}

	//3. Tô màu duyệt xong cho u
	color[u] = BLACK;
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

	for (int u = 1; u <= G.n; u++)							
		color[u] = WHITE; 								
	//2. Khởi tạo biến has_circle								
	has_circle = 0;										
	//3. Duyệt toàn bộ đồ thị để kiểm tra chu trình					
	for (int u = 1; u <= G.n; u++)							
		if (color[u] == WHITE)	//u chưa duyệt				
			DFS(&G, u, -1);		//gọi DFS(&G, u) để duyệt từ u
	//4. Kiểm tra has_circle	

    if (has_circle)
        printf("CIRCLED\n");
    else
        printf("NO CIRCLE\n");
    
    return 0;
}

