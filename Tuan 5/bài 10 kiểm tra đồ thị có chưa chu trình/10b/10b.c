#include <stdio.h>

/* Khai báo CTDL Graph*/
#define MAX_N 100
typedef struct {
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int u = 1 ; u <= n; u++)
        for (int v = 1 ; v <= n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v) {
    pG->A[u][v] += 1;
    //if (u != v)
    //    pG->A[v][u] += 1;
        
    if (pG->A[u][v] > 1)
        printf("da cung (%d, %d)\n", u, v);
    if (u == v)
        printf("khuyen %d\n", u);
    
    
    pG->m++;
}

int adjacent(Graph *pG, int u, int v) {
    return pG->A[u][v] > 0;
}

#define WHITE 0
#define GRAY  1
#define BLACK 2

int color[MAX_N];		//Lưu trạng thái của các đỉnh
int parent[MAX_N];		//Lưu trạng thái của các đỉnh
int has_circle;		//Đồ thị chứa trình hay không
int start, end;

void DFS(Graph *pG, int u, int p) {								
	//1. Tô màu dang duyệt cho u
	color[u] = GRAY;
	parent[u] = p;

	//2. Xét các đỉnh kề của u
	for (int v = 1; v <= pG->n; v++)
		if (adjacent(pG, u, v)) {
			if (color[v] == WHITE) 		//2a. Nếu v chưa duyệt
				DFS(pG, v, u);   		//gọi đệ quy duyệt nó
			else if (color[v] == GRAY) { //2b. v đang duyệt
				has_circle = 1;   	//chứa chu trình
				start = u;
				end = v;
			}
		}

	//3. Tô màu duyệt xong cho u
	color[u] = BLACK;
}


int main() {
	//1. Khai báo đồ thị G
	Graph G;
	//2. Đọc dữ liệu và dựng đồ thị
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

    if (has_circle) {
        int A[100], i = 0;
        A[0] = start;
        int u = start;
        do {
            u = parent[u];
            i++;
            A[i] = u;
        } while (u != v);
        
        for (int j = i; j >= 0; j--)
            printf("%d ", A[j]);

        printf("%d\n", A[i]);
    } else
        printf("-1\n");
    
    return 0;
}

