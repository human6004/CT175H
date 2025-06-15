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
    if (u != v)
        pG->A[v][u] += 1;
        
    if (pG->A[u][v] > 1)
        printf("da cung (%d, %d)\n", u, v);
    if (u == v)
        printf("khuyen %d\n", u);
    
    
    pG->m++;
}

int adjacent(Graph *pG, int u, int v) {
    return pG->A[u][v] > 0;
}

#define NO_COLOR 0
#define BLUE     1
#define RED      2

//Các biến hỗ trợ
int color[MAX_N];		//Lưu trạng thái của các đỉnh
int conflict;		//Có đụng độ trong khi tô màu không

//Tô màu các đỉnh của đồ thị bắt đầu từ đỉnh u với màu c
void colorize(Graph *pG, int u, int c) {							
	//1. Tô màu c cho u
	color[u] = c; 			
	//2. Xét các đỉnh kề của u
	for (int v = 1; v <= pG->n; v++)
		if (adjacent(pG, u, v)) {
			if (color[v] == NO_COLOR)	 //2a. Nếu v chưa có màu
				colorize(pG, v, 3 - c);	 //tô màu nó ngược với c
			else if (color[v] == color[u]) //2b. u và v  cùng màu
				conflict = 1;   		 //đụng độ, không tô được
		}
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
		color[u] = NO_COLOR; 								
	//2. Khởi tạo biến conflict
	conflict = 0;										
	//3. Duyệt toàn bộ đồ thị để kiểm tra chu trình					
	for (int u = 1; u <= G.n; u++)							
		if (color[u] == NO_COLOR)	//u chưa duyệt				
			colorize(&G, u, BLUE);		//gọi DFS(&G, u) để duyệt từ u
	//4. Kiểm tra cònlfict	

    if (conflict)
        printf("NO\n");
    else
        printf("YES\n");
    
    return 0;
}

